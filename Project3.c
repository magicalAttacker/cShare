#include <stdio.h>
#include <string.h>
#define MAX 100
#define STRLEN 9
#define M 32767
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
                G->edges[i][j] = M;
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
            if (G.edges[i][j] == M) {
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
        if (G->edges[i][j] != 0 && G->edges[i][j] != M && !visited[j]) {
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
void BFS_Core(MGraph *G, int i) {
    int qu[MAX], front = 0, rear = 0, j;
    visited[i] = 1;
    printf("-->%s", G->vexs[i]);
    rear = (rear + 1) % MAX;
    qu[rear] = i;
    while (front != rear) {
        front = (front + 1) % MAX;
        i = qu[front];
        for (j = 0; j < G->n; j++) {
            if (G->edges[i][j] != 0 && G->edges[i][j] != M && !visited[j]) {
                visited[j] = 1;
                printf("-->%s", G->vexs[j]);
                rear = (rear + 1) % MAX;
                qu[rear] = j;
            }
        }
    }
}
void BFS(MGraph *G, str vexs) {
    int i;
    int start = 0;
    for (i = 0; i < G->n; i++) {
        visited[i] = 0;
    }
    for (i = 0; i < G->n; i++) {
        if (strcmp(vexs, G->vexs[i]) == 0) {
            start = i;
            break;
        }
    }
    for (i = 0; i < G->n; i++) {
        if (!visited[i]) {
            BFS_Core(G, (start + i) % G->n);
        }
    }
}
void Prim(MGraph *G) {
    int i, j, k, min, lowcost[MAX], closest[MAX];
    for (i = 1; i < G->n; i++) {
        lowcost[i] = G->edges[0][i];
        closest[i] = 0;
    }
    closest[0] = -1;
    for (i = 1; i < G->n; i++) {
        min = M;
        k = i;
        for (j = 0; j < G->n; j++) {
            if (lowcost[j] < min && closest[j] != -1) {
                min = lowcost[j];
                k = j;
            }
        }
        printf("%s-->%s 权值%d\n", G->vexs[closest[k]], G->vexs[k], lowcost[k]);
        closest[k] = -1;
        for (j = 1; j < G->n; j++) {
            if (closest[j] != -1  && G->edges[k][j] < lowcost[j]) {
                lowcost[j] = G->edges[k][j];
                closest[j] = k;
            }
        }
    }
}
void Dijkstra(MGraph *G, int v) {
    int dist[MAX], path[MAX], s[MAX];
    int mindis, i, j, u, pre;
    for (i = 0; i < G->n; i++) {
        dist[i] = G->edges[v][i];
        s[i] = 0;
        if (G->edges[v][i] < M)
            path[i] = v;
        else
            path[i] = -1;
    }
    s[v] = 1;
    path[v] = 0;
    for (i = 0; i < G->n; i++) {
        mindis = M;
        u = -1;
        for (int j = 0; j < G->n; j++) {
            if (s[j] == 0 && dist[j] < mindis) {
                u = j;
                mindis = dist[j];
            }
        }
        if (u != -1) {
            s[u] = 1;
            for (j = 0; j < G->n; j++) {
                if (G->edges[u][j] < M && dist[u] + G->edges[u][j] < dist[j]) {
                    dist[j] = dist[u] + G->edges[u][j];
                    path[j] = u;
                }
            }
        }
    }
    printf("\nDijkstra算法求解如下：");
    for (i = 0; i < G->n; i++) {
        if (i != v) {
            printf("\n%d->%d:", v, i);
            if (s[i] == 1) {
                printf("路径长度为%2d，", dist[i]);
                pre = i;
                printf("路径逆序为：");
                while (pre != v) {
                    printf("%d，", pre);
                    pre = path[pre];
                }
                printf("%d", pre);
            } else
                printf("不存在路径");
        }
    }
}
void Floyd_Core(MGraph *G, int start, int end) {
    int i, j, k;
    int dist[MAX][MAX], path[MAX][MAX];
    for (i = 0; i < G->n; i++) {
        for (j = 0; j < G->n; j++) {
            dist[i][j] = G->edges[i][j];
            path[i][j] = j;
        }
    }
    for (k = 0; k < G->n; k++) {
        for (i = 0; i < G->n; i++) {
            for (j = 0; j < G->n; j++) {
                if ((dist[i][k] + dist[k][j]) < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    printf("%s-->%s = %d\n", G->vexs[start], G->vexs[end], dist[start][end]);
    printf("详细路径如下：\n");
    while (start != end) {
        printf("%s-->", G->vexs[start]);
        start = path[start][end];
    }
    printf("%s\n", G->vexs[end]);
}
void Floyd(MGraph *G) {
    int i, start, end;
    str str1, str2;
    printf("请输入开始城市和终止城市：");
    scanf("%s %s", str1, str2);
    for (i = 0; i < G->n; i++) {
        if (strcmp(str1, G->vexs[i]) == 0) {
            start = i;
        }
        if (strcmp(str2, G->vexs[i]) == 0) {
            end = i;
        }
    }
    Floyd_Core(G, start, end);
}
void Menu() {
    printf("\n------------------------简易城市交通网--------------------------");
    printf("\n||                    1.读取交通信息网                        ||");
    printf("\n||                    2.城市网信息维护                        ||");
    printf("\n||                    3.连通网信息维护                        ||");
    printf("\n||                    4.遍历交通信息网                        ||");
    printf("\n||                    5.路线最小生成树                        ||");
    printf("\n||                    6.两城间最短路径                        ||");
    printf("\n||                    7.源点找最短路径                        ||");
    printf("\n||                    0.退出信息网系统                        ||");
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
    CreateMGraph(&G);
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
                int method;
                printf("1.深度优先遍历\n");
                printf("2.广度优先遍历\n");
                printf("请选择遍历方式：");
                scanf("%d", &method);
                printf("请输入起点：");
                scanf("%s", st);
                if (method == 1)
                    DFS(&G, st);
                else {
                    BFS(&G, st);
                }
                break;
            }
            case 5: {
                printf("Prim大法好!\n");
                Prim(&G);
                break;
            }
            case 6: {
                Floyd(&G);
                break;
            }
            case 7: {
                Dijkstra(&G, 0);
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
