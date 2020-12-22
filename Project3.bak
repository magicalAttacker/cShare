#include <stdio.h>
#include <string.h>
#define MAX 100
#define STRLEN 9
int visited[MAX];
typedef char str[STRLEN];
typedef struct {
    int n, e;
    str vexs[MAX];
    int edges[MAX][MAX];
}MGraph;
void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    str str1, str2;
    printf("请输入顶点数：");
    scanf("%d", &G->n);
    printf("请输入边数：");
    scanf("%d", &G->e);
    printf("请输入各顶点信息");
    for (i = 0; i < G->n; i++) {
        getchar();
        printf("输入第%d个顶点：", i + 1);
        scanf("%s", G->vexs[i]);
    }
    for (i = 0; i < G->n; i++)
        for (j = 0; j < G->n; j++)
            G->edges[i][j] = 0;
    for (k = 0; k < G->e; k++) {
        getchar();
        printf("建立第%d条边：", k + 1);
        scanf("%s %s %d", str1, str2, &w);
        for (i = 0; i < G->n; i++)
            for (j = 0; j < G->n; j++)
                if (strcmp(str1, G->vexs[i]) == 0 && strcmp(str2, G->vexs[j]) == 0) {
                    G->edges[i][j] = w;
                    G->edges[j][i] = w;
                }
    }
}
void DispMGraph(MGraph G) {
    int i, j;
    printf("\n 图的邻接矩阵： \n");
    for (i = 0; i < G.n; i++) {
        for (j = 0; j <G.n; j++) {
            if (G.edges[i][j] == 0) {
                printf("\t∞");
            }
            else {
                printf("%5d", G.edges[i][j]);
            }
        }
        printf("\n");
    }
}
void DFS_Core(MGraph *G, int i) {
    int j;
    printf("-->%s", G->vexs[i]);
    visited[i] = 1;
    for (j = 0; j < G->n; j++) {
        if (G->edges[i][j] != 0 && !visited[j]) {
            DFS_Core(G, j);
        }
    }
}
void DFS(MGraph *G, str vexs) {
    int i;
    int start;
    for (i = 0; i < G->n; i++)
        visited[i] = 0;
    for (i = 0; i < G->n; i++) {
        if (strcmp(vexs, G->vexs[i]) == 0) {
            start = i;
            break;
        }
    }
    for (i = 0; i < G->n; i++) {
        if (!visited[i]) {
            DFS_Core(G, (start + i) % G->n);
        }
    }
}
void main() {
    MGraph G;
    str st;
    CreateMGraph(&G);
    DispMGraph(G);
    printf("请输入起点：");
    scanf("%s", st);
    DFS(&G, st);
}
