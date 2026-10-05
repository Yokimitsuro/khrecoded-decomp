#include "nitro/types.h"

typedef struct {
    int from;
    int to;
} SegmentLink;

typedef struct {
    u8 pad_00[0x18];
    int resolvedCount;
    u8 pad_1C[4];
    void **nodes;
    u8 pad_24[4];
    int linkCount;
    SegmentLink *links;
} SegmentGraph;

extern void *func_ov006_020a1338(SegmentGraph *graph, int from, int to);

void ResolveSegmentNodes(SegmentGraph *graph) {
    int i;

    for (i = 0; i < graph->linkCount; i++) {
        graph->nodes[i] = func_ov006_020a1338(graph, graph->links[i].from, graph->links[i].to);
    }
    graph->resolvedCount = graph->linkCount;
}
