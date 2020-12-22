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
    FILE *fp;
    fp = fopen("计科61905+30_Graph.txt", "r");
    if (fp != NULL) {
        int i, j, k, w;
        str str1, str2;
        printf("\n读取文件成功！\n");
        fscanf(fp, "%d", &G->n);
        fscanf(fp, "%d", &G->e);
        for (i = 0; i < G->n; i++) {
            fscanf(fp, "%s", G->vexs[i]);
        }
        for (i = 0; i < G->n; i++)
            for (j = 0; j < G->n; j++)
                G->edges[i][j] = 0;
        for (k = 0; k < G->e; k++) {
            fscanf(fp, "%s %s %d", str1, str2, &w);
            for (i = 0; i < G->n; i++)
                for (j = 0; j < G->n; j++)
                    if (strcmp(str1, G->vexs[i]) == 0 && strcmp(str2, G->vexs[j]) == 0) {
                        G->edges[i][j] = w;
                        G->edges[j][i] = w;
                    }
        }
    }
    else {
        printf("读取文件失败。");
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
void Menu() {
    printf("\n------------------------简易城市交通网--------------------------");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    4.遍历交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n--------------------------------------------------------------");
    printf("\n请输入选项：");
}
void wait() {
    printf("\n按回车键继续");
    getchar();
    getchar();
}
void main() {
    MGraph G;
    str st;
    int isContinue = 1;
    do {
        int selector;
        Menu();
        scanf("%d", &selector);
        switch (selector) {
            case 1: {
                CreateMGraph(&G);
                DispMGraph(G);
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                printf("请输入起点：");
                scanf("%s", st);
                DFS(&G, st);
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 0: {
                isContinue = 0;
                break;
            }
            default: {
                printf("输入错误，请重新输入");
            }
        }
        wait();
    } while (isContinue);
}
