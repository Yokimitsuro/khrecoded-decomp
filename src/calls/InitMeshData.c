#include "nitro/types.h"

typedef struct MeshNode {
    u8 pad_00[0xc];
    s32 parent;
    s32 children[4];
} MeshNode;

typedef struct MeshData {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x74 - 0x10];
    u16 flags;
    u8 pad_76[0x2];
    u16 offsetCount;
    u16 nodeCount;
    u16 quadFaceCount;
    u16 triFaceCount;
    u16 extraTriFaceCount;
    u8 pad_82[0x94 - 0x82];
    s32 unk_94;
    s32 *offsets;
    MeshNode *nodes;
    u8 *quadFaces;
    u8 *triFaces;
    u8 *extraTriFaces;
    u8 *namedEntries;
} MeshData;

extern void ComputeFacePlanes_02030308(void *unused, void *face);
extern void ComputeFacePlanes(void *unused, void *face);
extern u8 data_02060780;

/* Converts file offsets into pointers once. */
BOOL InitMeshData(MeshData *mesh)
{
    u8 *base = (u8 *)mesh;
    u16 count;
    int i;

    if ((mesh->flags & 0x8000) == 0) {
        mesh->unk_94 = (s32)(base + mesh->unk_94);
        mesh->offsets = (s32 *)(base + (s32)mesh->offsets);

        i = 0;
        count = mesh->offsetCount;
        if ((int)count > 0) {
            do {
                s32 *slot = &mesh->offsets[i];
                i = i + 1;
                *slot = (s32)(base + *slot);
            } while (i < (int)(u32)count);
        }

        i = 0;
        mesh->nodes = (MeshNode *)(base + (s32)mesh->nodes);
        mesh->quadFaces = base + (s32)mesh->quadFaces;
        mesh->triFaces = base + (s32)mesh->triFaces;
        mesh->extraTriFaces = base + (s32)mesh->extraTriFaces;
        mesh->namedEntries = base + (s32)mesh->namedEntries;

        count = mesh->quadFaceCount;
        if ((int)count > 0) {
            do {
                ComputeFacePlanes_02030308(mesh, mesh->quadFaces + i * 0x88);
                i = i + 1;
            } while (i < (int)(u32)count);
        }

        count = mesh->triFaceCount;
        i = 0;
        if ((int)count > 0) {
            do {
                ComputeFacePlanes(mesh, mesh->triFaces + i * 0x84);
                i = i + 1;
            } while (i < (int)(u32)count);
        }

        count = mesh->extraTriFaceCount;
        i = 0;
        if ((int)count > 0) {
            do {
                ComputeFacePlanes(mesh, mesh->extraTriFaces + i * 0x84);
                i = i + 1;
            } while (i < (int)(u32)count);
        }

        i = 0;
        count = mesh->nodeCount;
        if ((int)count > 0) {
            do {
                MeshNode *node = &mesh->nodes[i];
                s32 link;
                int k = 0;
                do {
                    link = node->children[k];
                    if (link != -1) {
                        link = (s32)&mesh->nodes[link];
                    } else {
                        link = 0;
                    }
                    node->children[k] = link;
                    k = k + 1;
                } while (k < 4);
                if (node->parent != -1) {
                    link = (s32)&mesh->nodes[node->parent];
                } else {
                    link = 0;
                }
                node->parent = link;
                i = i + 1;
            } while (i < (int)(u32)count);
        }

        mesh->unk_08 = 0;
        mesh->unk_04 = 0;
        mesh->unk_00 = 0;
        mesh->unk_0C = 0;
        mesh->flags = mesh->flags | 0x8000;
        mesh->flags = mesh->flags | 0x4000;
        data_02060780 = data_02060780 + 1;
    }
    return TRUE;
}
