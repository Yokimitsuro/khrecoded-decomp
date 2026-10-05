#include "nitro/types.h"

int GetLinkDistance(void *owner, s8 (*links)[4], int startNode, int goalNode) {
    int depth = 0;
    int distance[6];
    int node;

    for (node = 0; node < 6; node++) {
        distance[node] = -1;
    }
    distance[startNode] = 0;
    for (;;) {
        BOOL finished = TRUE;
        for (node = 0; node < 6; node++) {
            if (depth == distance[node]) {
                int direction;
                for (direction = 3; direction >= 0; direction--) {
                    int neighbor = links[node][direction];
                    if (neighbor >= 0) {
                        if (goalNode == neighbor) {
                            return depth + 1;
                        }
                        if (distance[neighbor] < 0) {
                            distance[neighbor] = depth + 1;
                            finished = FALSE;
                        }
                    }
                }
            }
        }
        if (finished) {
            break;
        }
        depth++;
    }
    return -1;
}
