#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <math.h>
#include <assert.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define ABSS(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
#define SWAP(type, a, b) { const type swapTmp = a; a = b; b = swapTmp; }

#define Yes() puts("Yes");
#define No() puts("No");
#define YesNo(condition) puts(condition ? "Yes" : "No");

int compare_zu_asc(const void* a, const void* b) {
    return *((size_t*)a) < *((size_t*)b) ? -1 : 1;
}

int compare_zu_desc(const void* a, const void* b) {
    return *((size_t*)a) > *((size_t*)b) ? -1 : 1;
}

int compare_i64_asc(const void* a, const void* b) {
    return *((int64_t*)a) < *((int64_t*)b) ? -1 : 1;
}

int compare_i64_desc(const void* a, const void* b) {
    return *((int64_t*)a) > *((int64_t*)b) ? -1 : 1;
}

int compare_u64_asc(const void* a, const void* b) {
    return *((uint64_t*)a) < *((uint64_t*)b) ? -1 : 1;
}

int compare_u64_desc(const void* a, const void* b) {
    return *((uint64_t*)a) > *((uint64_t*)b) ? -1 : 1;
}

int compare_c_asc(const void* a, const void* b) {
    return *((char*)a) < *((char*)b) ? -1 : 1;
}

int compare_c_desc(const void* a, const void* b) {
    return *((char*)a) > *((char*)b) ? -1 : 1;
}

int compare_dp_asc(const void* a, const void* b) {
    return *((double*)a) < *((double*)b) ? -1 : 1;
}

static uint64_t modinvU64(const uint64_t a, const uint64_t m) {
    int64_t aa = (int64_t)a;
    const int64_t mm = (int64_t)m;
    int64_t b = mm;
    int64_t u = 1;
    int64_t v = 0;

    while (b != 0) {
        const int64_t t = aa / b;

        aa -= t * b;
        SWAP(uint64_t, aa, b);
        u -= t * v;
        SWAP(uint64_t, u, v);
    }

    u %= mm;
    if (u < 0) {
        u += m;
    }

    return (uint64_t)u;
}

static size_t powZu(const size_t base, const size_t exp) {
    if (exp == 0) {
        return 1;
    }

    if (exp == 1) {
        return base;
    }

    if (exp % 2 == 0) {
        return powZu(base * base, exp / 2);
    }
    else {
        return base * powZu(base, exp - 1);
    }
}

static uint64_t powU64(const uint64_t base, const uint64_t exp) {
    if (exp == 0) {
        return 1;
    }

    if (exp == 1) {
        return base;
    }

    if (exp % 2 == 0) {
        return powU64(base * base, exp / 2);
    }
    else {
        return base * powU64(base, exp - 1);
    }
}

static uint64_t powU64WMod(uint64_t base, const uint64_t exp, const uint64_t m) {
    if (exp == 0) {
        return 1;
    }

    base %= m;

    if (exp == 1) {
        return base;
    }

    if (exp % 2 == 0) {
        return powU64WMod(base * base % m, exp / 2, m);
    }
    else {
        return base * powU64WMod(base, exp - 1, m) % m;
    }
}

static size_t combSz(const size_t n, const size_t r) {
    size_t result = 1;

    for (size_t i = 0; i < r; i++) {
        result *= n - i;
        result /= i + 1;
    }

    return result;
}

static uint64_t combU64(const uint64_t n, const uint64_t r) {
    uint64_t result = 1;

    for (uint64_t i = 0; i < r; i++) {
        result *= n - i;
        result /= i + 1;
    }

    return result;
}

static uint64_t combU64WMod(const uint64_t n, const uint64_t r, const uint64_t m) {
    uint64_t result = 1;
    uint64_t inv = 1;

    for (uint64_t i = 0; i < r; i++) {
        result = result * (n - i) % m;
        inv = inv * (i + 1) % m;
    }

    return result * modinvU64(inv, m) % m;
}

static uint64_t permU64(const uint64_t n) {
    uint64_t result = 1;

    for (uint64_t v = 2; v <= n; v++) {
        result *= v;
    }

    return result;
}

static uint64_t permU64WMod(const uint64_t n, const uint64_t m) {
    uint64_t result = 1;

    for (uint64_t v = 2; v <= n; v++) {
        result *= v;
        result %= m;
    }

    return result;
}

static size_t gcdZu(size_t m, size_t n) {
    size_t temp;

    while (m % n != 0) {
        temp = n;
        n = m % n;
        m = temp;
    }

    return n;
}

static uint64_t gcdU64(uint64_t m, uint64_t n)
{
    uint64_t temp;

    while (m % n != 0) {
        temp = n;
        n = m % n;
        m = temp;
    }

    return n;
}

static uint64_t popcntU64(uint64_t val) {
    uint64_t cnt = 0;

    while (val != 0) {
        if ((val & UINT64_C(0x1)) != 0) {
            cnt++;
        }

        val >>= UINT64_C(0x1);
    }

    return cnt;
}

#define BHEAP_INVALID_NODE (UINT64_C(10000000000000000))

typedef struct {
    uint64_t idx;
} BHeap_Node_t;

typedef struct {
    uint64_t maxSize;
    uint64_t size;
    int (*compare)(const uint64_t parentIdx, const uint64_t nodeIdx);
    BHeap_Node_t* node;
    uint64_t* idx2NodeMap;
} BHeap_Context_t;

static void bHeap_UpdateNodeLoc(const BHeap_Context_t* const ctx, const uint64_t nodeListSize, const uint64_t* const nodeList) {
    for (uint64_t i = 0; i < nodeListSize; i++) {
        ctx->idx2NodeMap[ctx->node[nodeList[i]].idx] = nodeList[i];
    }
}

static void bHeap_RemoveNodeLoc(const BHeap_Context_t* const ctx, const uint64_t nodeListSize, const uint64_t* const nodeList) {
    for (uint64_t i = 0; i < nodeListSize; i++) {
        ctx->idx2NodeMap[ctx->node[nodeList[i]].idx] = BHEAP_INVALID_NODE;
    }
}

static void bHeap_Swap(BHeap_Context_t* const ctx, const uint64_t node0, const uint64_t node1) {
    assert(node0 < ctx->size);
    assert(node1 < ctx->size);

    const uint64_t tmpIdx = ctx->node[node0].idx;
    ctx->node[node0].idx = ctx->node[node1].idx;
    ctx->node[node1].idx = tmpIdx;

    const uint64_t nodeList[2] = { node0, node1 };
    bHeap_UpdateNodeLoc(ctx, 2, nodeList);
}

static void bHeap_UpHeap(BHeap_Context_t* const ctx, const uint64_t nodeIdx) {
    if (nodeIdx == 0) {
        return;
    }

    const uint64_t parentNodeIdx = (nodeIdx + 1) / 2 - 1;

    const int compareResult = ctx->compare(ctx->node[parentNodeIdx].idx, ctx->node[nodeIdx].idx);

    if (0 < compareResult) {
        bHeap_Swap(ctx, nodeIdx, parentNodeIdx);

        if (parentNodeIdx != 0) {
            bHeap_UpHeap(ctx, parentNodeIdx);
        }
    }
}

static void bHeap_DownHeap(BHeap_Context_t* const ctx, const uint64_t nodeIdx) {
    if (ctx->size - 1 <= nodeIdx) {
        return;
    }

    const uint64_t idx = ctx->node[nodeIdx].idx;
    const uint64_t leftNodeIdx = 2 * (nodeIdx + 1) - 1;
    const uint64_t leftIdx = ctx->node[leftNodeIdx].idx;

    if (leftNodeIdx < ctx->size) {
        const int leftResult = ctx->compare(idx, leftIdx);

        uint64_t swapTarget = leftResult < 0 ? BHEAP_INVALID_NODE : leftNodeIdx;

        const uint64_t rightNodeIdx = leftNodeIdx + 1;
        const uint64_t rightIdx = ctx->node[rightNodeIdx].idx;

        if (rightNodeIdx < ctx->size) {
            const int rightResult = ctx->compare(idx, rightIdx);

            if (swapTarget == BHEAP_INVALID_NODE) {
                if (0 < rightResult) {
                    swapTarget = rightNodeIdx;
                }
            }
            else {
                if (0 < rightResult) {
                    const int rightLeftResult = ctx->compare(leftIdx, rightIdx);

                    if (0 < rightLeftResult) {
                        swapTarget = rightNodeIdx;
                    }
                }
            }
        }

        if (swapTarget != BHEAP_INVALID_NODE) {
            bHeap_Swap(ctx, nodeIdx, swapTarget);

            bHeap_DownHeap(ctx, swapTarget);
        }
    }
}

static void BHeap_Init(BHeap_Context_t* const ctx, const uint64_t size, int(*compare)(const uint64_t parentIdx, const uint64_t nodeIdx)) {
    ctx->maxSize = size;
    ctx->size = 0;
    ctx->compare = compare;
    ctx->node = (BHeap_Node_t*)malloc(sizeof(BHeap_Node_t) * (size_t)size);
    ctx->idx2NodeMap = (uint64_t*)malloc(sizeof(uint64_t) * (size_t)size);
    for (uint64_t i = 0; i < size; i++) {
        ctx->idx2NodeMap[i] = BHEAP_INVALID_NODE;
    }
}

static void BHeap_Add(BHeap_Context_t* const ctx, const uint64_t idx) {
    ctx->node[ctx->size].idx = idx;

    ctx->size++;

    const uint64_t node = ctx->size - 1;
    bHeap_UpdateNodeLoc(ctx, 1, &node);

    bHeap_UpHeap(ctx, ctx->size - 1);
}

static void BHeap_RemoveTop(BHeap_Context_t* const ctx) {
    if (ctx->size == 0) {
        return;
    }

    {
        const uint64_t node = 0;
        bHeap_RemoveNodeLoc(ctx, 1, &node);
    }

    if (ctx->size == 1) {
        ctx->size--;
        return;
    }

    ctx->node[0].idx = ctx->node[ctx->size - 1].idx;

    {
        const uint64_t node = 0;
        bHeap_UpdateNodeLoc(ctx, 1, &node);
    }

    ctx->size--;

    bHeap_DownHeap(ctx, 0);
}

static bool BHeap_IsInHeap(BHeap_Context_t* const ctx, const uint64_t idx) {
    return ctx->idx2NodeMap[idx] != BHEAP_INVALID_NODE;
}

static void BHeap_RemoveSpecificIdx(BHeap_Context_t* const ctx, const uint64_t idx) {
    assert(idx < ctx->maxSize);

    const uint64_t node = ctx->idx2NodeMap[idx];
    assert(node != BHEAP_INVALID_NODE);

    bHeap_RemoveNodeLoc(ctx, 1, &node);

    if (node == ctx->size - 1) {
        ctx->size--;
    }
    else {
        ctx->node[node].idx = ctx->node[ctx->size - 1].idx;

        bHeap_UpdateNodeLoc(ctx, 1, &node);

        ctx->size--;
        bHeap_DownHeap(ctx, node);
        bHeap_UpHeap(ctx, node);
    }
}

static uint64_t BHeap_GetTopIdx(const BHeap_Context_t* const ctx) {
    return ctx->size == 0 ? BHEAP_INVALID_NODE : ctx->node[0].idx;
}

typedef struct {
    uint64_t cnt;
    size_t* child;
    size_t numChild;
    size_t maxNumChild;
} Tree_Node;

#define TREE_INIT_ALLOC (128)

static Tree_Node tree_Node[200000];

static void tree_Init(const uint64_t N) {
    for (uint64_t i = 0; i < N; i++) {
        tree_Node[i].cnt = 0;
        tree_Node[i].numChild = 0;
        tree_Node[i].child = malloc(sizeof(size_t) * TREE_INIT_ALLOC);
        tree_Node[i].maxNumChild = TREE_INIT_ALLOC;
    }
}

static void tree_AddChild(const size_t parent, const size_t child) {
    if (tree_Node[parent].maxNumChild <= tree_Node[parent].numChild) {
        tree_Node[parent].child = realloc(tree_Node[parent].child, sizeof(size_t) * tree_Node[parent].maxNumChild * 2);
        tree_Node[parent].maxNumChild *= 2;
    }

    tree_Node[parent].child[tree_Node[parent].numChild] = child;
    tree_Node[parent].numChild++;
}

static int _bHeap_Compare_Asc(const uint64_t parentIdx, const uint64_t nodeIdx) {
    return parentIdx < nodeIdx ? -1 : 1;
}

#define UF_ROOT (UINT64_C(10000000000))

typedef struct {
    uint64_t parent;
    uint64_t size;
} UF_Node_t;

typedef struct {
    uint64_t size;
    UF_Node_t* node;
} UF_Context_t;

static void UF_Init(UF_Context_t* const ctx, const uint64_t size)
{
    ctx->node = (UF_Node_t*)malloc((size_t)(sizeof(UF_Node_t) * size));
    ctx->size = size;
    for (uint64_t i = 0; i < size; i++) {
        ctx->node[i].parent = UF_ROOT;
    }
}

static uint64_t UF_GetRoot(UF_Context_t* const ctx, const uint64_t idx) {
    if (ctx->node[idx].parent == UF_ROOT) {
        return idx;
    }

    const uint64_t root = UF_GetRoot(ctx, ctx->node[idx].parent);

    ctx->node[idx].parent = root;

    return root;
}

static void UF_Merge(UF_Context_t* const ctx, const uint64_t a, const uint64_t b) {
    const uint64_t aRoot = UF_GetRoot(ctx, a);
    const uint64_t bRoot = UF_GetRoot(ctx, b);

    if (aRoot != bRoot) {
        ctx->node[aRoot].parent = bRoot;

        ctx->node[bRoot].size += ctx->node[aRoot].size;
    }
}

static bool UF_IsRoot(const UF_Context_t* const ctx, const uint64_t idx)
{
    return ctx->node[idx].parent == UF_ROOT;
}

static uint64_t UF_GetSize(const UF_Context_t* const ctx, const uint64_t idx)
{
    return ctx->node[idx].size;
}

static void sha1_rotate(uint32_t* const h, const uint32_t* const w) {
    uint32_t a = h[0];
    uint32_t b = h[1];
    uint32_t c = h[2];
    uint32_t d = h[3];
    uint32_t e = h[4];

    for (uint64_t i = 0; i < 80; i++) {
        uint32_t f = 0;
        uint32_t k = 0;
        if (i < 20) {
            f = (b & c) | (~b & d);
            k = 0x5A827999;
        }
        else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        const uint32_t t = ((a << 5) | (a >> 27)) + f + e + k + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    h[0] = h[0] + a;
    h[1] = h[1] + b;
    h[2] = h[2] + c;
    h[3] = h[3] + d;
    h[4] = h[4] + e;
}

static void sha1(const char* str, uint64_t len, uint32_t* hash) {
    if (len == 0) {
        len = (uint64_t)strlen(str);
    }

    const uint64_t lastChunkLen = len % 64;
    uint32_t h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };

    for (uint64_t base = 0; base < len; base += 64) {
        const uint64_t chunkLen = MIN(64, len - base);
        uint32_t w[80];

        for (uint64_t i = 0; i < 16; i++) {
            w[i] = 0;
        }

        for (uint64_t ofs = 0; ofs < chunkLen; ofs++) {
            w[ofs / 4] |= (uint32_t)(str[base + ofs]) << ((3 - ofs % 4) * 8);
        }

        if (chunkLen < 64) {
            w[chunkLen / 4] |= UINT32_C(0x80) << ((3 - chunkLen % 4) * 8);
        }

        if (chunkLen < 56) {
            w[15] = (uint32_t)len * 8;
        }

        for (uint64_t i = 16; i < 80; i++) {
            const uint32_t v = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];
            w[i] = (v << 1) | (v >> 31);
        }

        sha1_rotate(h, w);
    }

    if (lastChunkLen == 0 || 56 <= lastChunkLen) {
        uint32_t w[80];

        for (uint64_t i = 0; i < 16; i++) {
            w[i] = 0;
        }

        if (lastChunkLen == 0) {
            w[0] = UINT32_C(0x80000000);
        }
        w[15] = (uint32_t)len * 8;

        for (uint64_t i = 16; i < 80; i++) {
            const uint32_t v = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];
            w[i] = (v << 1) | (v >> 31);
        }

        sha1_rotate(h, w);
    }

    hash[4] = h[4];
    hash[3] = h[3];
    hash[2] = h[2];
    hash[1] = h[1];
    hash[0] = h[0];
}

#define MAP_SIZE_DEFAULT (10000000)

typedef struct {
    uint64_t mapSize;
    uint64_t entrySize;
    uint64_t* maxNumEntries;
    uint64_t* numEntries;
    void** map;
} HashMap_Context_t;

void HashMap_Init(HashMap_Context_t* const ctx, const uint64_t entrySize) {
    ctx->mapSize = MAP_SIZE_DEFAULT;
    ctx->map = (void**)malloc(sizeof(void*) * (size_t)ctx->mapSize);
    ctx->maxNumEntries = (uint64_t*)malloc(sizeof(uint64_t) * (size_t)ctx->mapSize);
    ctx->numEntries = (uint64_t*)malloc(sizeof(uint64_t) * (size_t)ctx->mapSize);

    for (uint64_t i = 0; i < ctx->mapSize; i++) {
        ctx->map[i] = NULL;
        ctx->maxNumEntries[i] = 0;
        ctx->numEntries[i] = 0;
    }
}

#define MOD_VAL (UINT64_C(1000000007))

typedef struct tagLinkedList_t {
    uint64_t threadNo;
    struct tagLinkedList_t* prev;
    struct tagLinkedList_t* next;
} LinkedList_t;

static LinkedList_t ll[100000];
static LinkedList_t* llRoot;

#define GRAPH_NEIGHBOR_LIST_ALLOC_INIT (16)

#define GRAPH_PARENT_NONE (UINT64_MAX)

typedef struct {
    bool visited;
    bool traveling;
    uint64_t parent;
    uint64_t maxNumNeighbors;
    uint64_t numNeighbors;
    uint64_t* neighbor;
    uint64_t* cost;
} Graph_Node;

typedef struct {
    uint64_t numNodes;
    Graph_Node* node;
} Graph_Context_t;

static void Graph_Init(Graph_Context_t* const ctx, const uint64_t numNodes) {
    ctx->node = (Graph_Node*)malloc((size_t)(sizeof(Graph_Node) * numNodes));
    ctx->numNodes = numNodes;

    for (uint64_t n = 0; n < numNodes; n++) {
        ctx->node[n].visited = false;
        ctx->node[n].traveling = false;
        ctx->node[n].parent = GRAPH_PARENT_NONE;
        ctx->node[n].maxNumNeighbors = 0;
        ctx->node[n].numNeighbors = 0;
        ctx->node[n].neighbor = NULL;
        ctx->node[n].cost = NULL;
    }
}

static uint64_t Graph_GetNumNeighbors(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    return ctx->node[nodeIdx].numNeighbors;
}

static void Graph_MarkVisited(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    ctx->node[nodeIdx].visited = true;
}

static void Graph_UnMarkVisited(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    ctx->node[nodeIdx].visited = false;
}

static bool Graph_IsNodeVisited(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    return ctx->node[nodeIdx].visited;
}

static void Graph_MarkTraveling(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    ctx->node[nodeIdx].traveling = true;
}

static void Graph_UnMarkTraveling(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    ctx->node[nodeIdx].traveling = false;
}

static bool Graph_IsNodeTraveling(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    return ctx->node[nodeIdx].traveling;
}

static void Graph_SetParent(Graph_Context_t* const ctx, const uint64_t nodeIdx, const uint64_t parentNodeIdx) {
    ctx->node[nodeIdx].parent = parentNodeIdx;
}

static uint64_t Graph_GetParent(Graph_Context_t* const ctx, const uint64_t nodeIdx) {
    return ctx->node[nodeIdx].parent;
}

static uint64_t Graph_GetNeighbor(Graph_Context_t* const ctx, const uint64_t nodeIdx, const uint64_t ofs) {
    return ctx->node[nodeIdx].neighbor[ofs];
}

static void Graph_Connect(Graph_Context_t* const ctx, const uint64_t from, const uint64_t to, const uint64_t cost) {
    if (ctx->node[from].maxNumNeighbors == 0) {
        ctx->node[from].neighbor = (uint64_t*)malloc(sizeof(uint64_t) * GRAPH_NEIGHBOR_LIST_ALLOC_INIT);
        ctx->node[from].cost = (uint64_t*)malloc(sizeof(uint64_t) * GRAPH_NEIGHBOR_LIST_ALLOC_INIT);
        ctx->node[from].maxNumNeighbors = GRAPH_NEIGHBOR_LIST_ALLOC_INIT;
    }
    else if (ctx->node[from].numNeighbors == ctx->node[from].maxNumNeighbors) {
        ctx->node[from].neighbor = (uint64_t*)realloc(ctx->node[from].neighbor, (size_t)(sizeof(uint64_t) * ctx->node[from].maxNumNeighbors * 2));
        ctx->node[from].cost = (uint64_t*)realloc(ctx->node[from].cost, (size_t)(sizeof(uint64_t) * ctx->node[from].maxNumNeighbors * 2));
        ctx->node[from].maxNumNeighbors *= 2;
    }

    ctx->node[from].neighbor[ctx->node[from].numNeighbors] = to;
    ctx->node[from].cost[ctx->node[from].numNeighbors] = cost;
    ctx->node[from].numNeighbors++;
}

static void graph_ConstructTreeBody(Graph_Context_t* const ctx, const uint64_t nodeIdx, const uint64_t parentNodeIdx) {
    Graph_SetParent(ctx, nodeIdx, parentNodeIdx);

    const uint64_t numNeighbors = Graph_GetNumNeighbors(ctx, nodeIdx);
    bool parentFound = false;
    for (uint64_t i = 0; i < numNeighbors; i++) {
        const uint64_t neighbor = Graph_GetNeighbor(ctx, nodeIdx, i);
        if (neighbor != parentNodeIdx) {
            graph_ConstructTreeBody(ctx, neighbor, nodeIdx);
            if (parentFound) {
                ctx->node[nodeIdx].neighbor[i - 1] = neighbor;
            }
        }
        else {
            parentFound = true;
        }
    }
    if (parentFound) {
        ctx->node[nodeIdx].numNeighbors--;
    }
}

static void Graph_ConstructTree(Graph_Context_t* const ctx, const uint64_t root) {
    graph_ConstructTreeBody(ctx, root, GRAPH_PARENT_NONE);
}

typedef struct {
    uint64_t sum;
    uint64_t min;
    uint64_t max;
} SegTree_Val_t;

typedef struct {
    uint64_t numEntries;
    uint64_t treeSize;
    SegTree_Val_t* val;
} SegTree_Context_t;

static void SegTree_Init(SegTree_Context_t* const ctx, const uint64_t numEntries) {
    ctx->numEntries = numEntries;
    uint64_t treeSize = numEntries;

    treeSize--;
    treeSize |= treeSize >> 1;
    treeSize |= treeSize >> 2;
    treeSize |= treeSize >> 4;
    treeSize |= treeSize >> 8;
    treeSize |= treeSize >> 16;
    treeSize |= treeSize >> 32;
    treeSize++;

    treeSize <<= 1;

    ctx->val = (SegTree_Val_t*)malloc(sizeof(SegTree_Val_t) * (size_t)treeSize);
    for (uint64_t i = 0; i < treeSize; i++) {
        ctx->val[i].sum = 0;
        ctx->val[i].min = UINT64_MAX;
        ctx->val[i].max = 0;
    }

    ctx->treeSize = treeSize;
}

static void SegTree_Set(SegTree_Context_t* const ctx, uint64_t idx, const uint64_t setVal) {
    uint64_t f = ctx->treeSize >> 1;

    while (0 < f) {
        SegTree_Val_t* const val = &ctx->val[f + idx];

        if (f == (ctx->treeSize >> 1)) {
            val->sum = setVal;
            val->min = setVal;
            val->max = setVal;
        }
        else {
            val->sum = ctx->val[2 * (f + idx)].sum + ctx->val[2 * (f + idx) + 1].sum;
            val->min = MIN(ctx->val[2 * (f + idx)].min, ctx->val[2 * (f + idx) + 1].min);
            val->max = MAX(ctx->val[2 * (f + idx)].max, ctx->val[2 * (f + idx) + 1].max);
        }

        f >>= 1;
        idx >>= 1;
    }
}

static void SegTree_Inc(SegTree_Context_t* const ctx, uint64_t idx, const uint64_t incCnt) {
    uint64_t f = ctx->treeSize >> 1;

    while (0 < f) {
        SegTree_Val_t* const val = &ctx->val[f + idx];

        val->sum += incCnt;
        if (f == (ctx->treeSize >> 1)) {
            val->min = val->sum;
            val->max = val->sum;
        }
        else {
            val->min = MIN(ctx->val[2 * (f + idx)].min, ctx->val[2 * (f + idx) + 1].min);
            val->max = MAX(ctx->val[2 * (f + idx)].max, ctx->val[2 * (f + idx) + 1].max);
        }

        f >>= 1;
        idx >>= 1;
    }
}

static void SegTree_Dec(SegTree_Context_t* const ctx, uint64_t idx, const uint64_t decCnt) {
    uint64_t f = ctx->treeSize >> 1;

    while (0 < f) {
        SegTree_Val_t* const val = &ctx->val[f + idx];

        val->sum -= decCnt;
        if (f == (ctx->treeSize >> 1)) {
            val->min = val->sum;
            val->max = val->sum;
        }
        else {
            val->min = MIN(ctx->val[2 * (f + idx)].min, ctx->val[2 * (f + idx) + 1].min);
            val->max = MAX(ctx->val[2 * (f + idx)].max, ctx->val[2 * (f + idx) + 1].max);
        }

        f >>= 1;
        idx >>= 1;
    }
}

/**
 * @brief  [l,r]の値の総和を取得する。
 */
static uint64_t SegTree_GetRangeSum(SegTree_Context_t* const ctx, uint64_t l, uint64_t r) {
    uint64_t f = ctx->treeSize >> 1;

    uint64_t rSum = 0;
    r++;

    while (0 < f) {
        if ((r & UINT64_C(0x1)) != 0) {
            rSum += ctx->val[f + r - 1].sum;
        }

        f >>= 1;
        r >>= 1;
    }

    f = ctx->treeSize >> 1;

    uint64_t lSum = 0;

    while (0 < f) {
        if ((l & UINT64_C(0x1)) != 0) {
            lSum += ctx->val[f + l - 1].sum;
        }

        f >>= 1;
        l >>= 1;
    }

    return rSum - lSum;
}

static uint64_t segTree_GetRangeMax(SegTree_Context_t* const ctx, const uint64_t l, const uint64_t r, const uint64_t segL, const uint64_t segR, const uint64_t idx) {
    if (r < segL || segR < l) {
        return 0;
    }

    if (l <= segL && segR <= r) {
        return ctx->val[idx].max;
    }
    else {
        const uint64_t lm = segTree_GetRangeMax(ctx, l, r, segL, (segL + segR) / 2, 2 * idx);
        const uint64_t rm = segTree_GetRangeMax(ctx, l, r, (segL + segR) / 2 + 1, segR, 2 * idx + 1);
        return MAX(lm, rm);
    }
}

/**
 * @brief [l,r]の値のうち最大のものを取得する。
 */
static uint64_t SegTree_GetRangeMax(SegTree_Context_t* const ctx, const uint64_t l, const uint64_t r) {
    return segTree_GetRangeMax(ctx, l, r, 0, ctx->treeSize / 2 - 1, 1);
}

static uint64_t segTree_GetRangeMin(SegTree_Context_t* const ctx, const uint64_t l, const uint64_t r, const uint64_t segL, const uint64_t segR, const uint64_t idx) {
    if (r < segL || segR < l) {
        return UINT64_MAX;
    }

    if (l <= segL && segR <= r) {
        return ctx->val[idx].min;
    }
    else {
        const uint64_t lm = segTree_GetRangeMin(ctx, l, r, segL, (segL + segR) / 2, 2 * idx);
        const uint64_t rm = segTree_GetRangeMin(ctx, l, r, (segL + segR) / 2 + 1, segR, 2 * idx + 1);
        return MIN(lm, rm);
    }
}

/**
 * @brief [l,r]の値のうち最小のものを取得する。
 */
static uint64_t SegTree_GetRangeMin(SegTree_Context_t* const ctx, const uint64_t l, const uint64_t r) {
    return segTree_GetRangeMin(ctx, l, r, 0, ctx->treeSize / 2 - 1, 1);
}

int main(void) {
    uint64_t N;

    scanf("%"PRIu64, &N);
    uint64_t r = 0;
    for (uint64_t i = 0; i < N; i++) {
        uint64_t A;
        scanf("%"PRIu64, &A);

        r += A;
    }

    printf("%"PRIu64"\n", r);

    return 0;
}
