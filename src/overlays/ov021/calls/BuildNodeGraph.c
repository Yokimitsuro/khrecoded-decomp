#include "nitro/types.h"

typedef struct GraphNode {
    int link;
    int x;
    int y;
} GraphNode;

typedef struct NodeGraph {
    GraphNode *nodes[2];
    int nodeCount[2];
    GraphNode **refs[2];
    int refCount[2];
} NodeGraph;

typedef struct NodeGraphCounts {
    u16 nodeCount[2];
    u16 refCount[2];
} NodeGraphCounts;

typedef struct NodePoint {
    int x;
    int y;
} NodePoint;

typedef struct NodeGraphSource {
    NodePoint *points[2];
    int *refIndices[2];
} NodeGraphSource;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

void BuildNodeGraph(NodeGraph *graph, void *unused, NodeGraphCounts *counts, NodeGraphSource *source)
{
    NodePoint *point;
    int side;
    int i;

    for (side = 0; side < 2; side++) {
        graph->nodeCount[side] = counts->nodeCount[side];
        if (graph->nodeCount[side] > 0) {
            graph->nodes[side] = NNSi_FndAllocFromDefaultHeap(graph->nodeCount[side] * sizeof(GraphNode));
        }
        graph->refCount[side] = counts->refCount[side];
        if (counts->refCount[side] != 0) {
            graph->refs[side] = NNSi_FndAllocFromDefaultHeap(graph->refCount[side] * sizeof(GraphNode *));
        }
    }
    for (side = 0; side < 2; side++) {
        i = 0;
        point = source->points[side];
        for (; i < graph->nodeCount[side]; i++) {
            GraphNode *nodes = graph->nodes[side];
            nodes[i].x = point->x;
            nodes[i].y = point->y;
            nodes[i].link = 0;
            point++;
        }
    }
    for (side = 0; side < 2; side++) {
        int *index = source->refIndices[side];
        for (i = 0; i < graph->refCount[side]; i++) {
            graph->refs[side][i] = &graph->nodes[side][*index];
            index++;
        }
    }
}
