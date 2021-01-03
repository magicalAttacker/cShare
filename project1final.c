#include <stdio.h>
#define MAXLEN 100
#define STRLEN 13
#define CHALEN 5
typedef int DataType;
typedef char StringType;
typedef struct {
    DataType num;
    DataType id;
    StringType name[STRLEN];
    StringType sex[CHALEN];
    StringType faculty[STRLEN];
    DataType engMark;
    DataType matMark;
    DataType comMark;
    DataType total;
} BaseType;

typedef struct {
    BaseType data[MAXLEN];
    int Length;
}SeqList;

SeqList L;

void InitList(SeqList *L) {
    L->Length = 0;
}

void CreateList(SeqList *L) {
    int i;
    FILE *fp;
    fp = fopen("test.txt", "r");
    if (fp != NULL) {
        printf("读取成功！");
        for (i = 0; i < 9; i++) {
            fscanf(fp, "%s", L->data[0].name);
        }
        i = 0;
        while (!feof(fp)) {
            fscanf(fp, "%d", &L->data[i].num);
            fscanf(fp, "%d", &L->data[i].id);
            fscanf(fp, "%s", L->data[i].name);
            fscanf(fp, "%s", L->data[i].sex);
            fscanf(fp, "%s", L->data[i].faculty);
            fscanf(fp, "%d", &L->data[i].engMark);
            fscanf(fp, "%d", &L->data[i].matMark);
            fscanf(fp, "%d", &L->data[i].comMark);
            L->data[i].total = L->data[i].engMark + L->data[i].matMark + L->data[i].comMark;
            i++;
        }
        L->Length = i;
    } else
        printf("error");
}

int GetElem(SeqList *L, int i, BaseType *x) {
    if (i < 1 || i > L->Length)
        return 0;
    else {
        *x = L->data[i - 1];
        return 1;
    }
}

int Locate(SeqList *L, DataType t) {
    int i = 0;
    while(i < L->Length && L->data[i].id != t)
        i++;
    if (i >= L->Length)
        return 0;
    else
        return i;
}

int InsElem(SeqList *L, int i, BaseType *x) {
    int j;
    if (L->Length >= MAXLEN) {
        printf("顺序表已满!\n");
        return -1;
    }
    if (i < 1 || i > L->Length + 1) {
        printf("插入位置出错!");
        return 0;
    }
    if (i == L->Length + 1) {
        L->data[i - 1] = *x;
        L->Length++;
        return 1;
    }
    for (j = L->Length - 1; j >= i - 1; j--)
        L->data[j + 1] = L->data[j];
    L->data[i - 1] = *x;
    L->Length++;
    return 1;
}

int DelElem(SeqList *L, int i, BaseType *x) {
    int j;
    if (L->Length == 0) {
        printf("顺序表为空!");
        return 0;
    }
    if (i < 1 || i > L->Length) {
        printf("不存在第i个元素");
        return 0;
    }
    *x = L->data[i - 1];
    for (j = i; j < L->Length; j++)
        L->data[j - 1] = L->data[j];
    L->Length--;
    return 1;
}

void DispList(SeqList *L) {
    int i;
    printf("\n==============================================================================");
    printf("\n编号\t\t学号\t\t\t姓名\t\t性别\t\t系名\t\t\t英语\t\t数学\t\t计算机\t总分\n");
    for (i = 0; i < L->Length; i++) {
        printf("%d", L->data[i].num);
        printf("\t\t%d", L->data[i].id);
        printf("\t%-8s", L->data[i].name);
        printf("\t%s", L->data[i].sex);
        printf("\t\t%s", L->data[i].faculty);
        printf("\t\t\t%d", L->data[i].engMark);
        printf("\t\t%d", L->data[i].matMark);
        printf("\t\t%d", L->data[i].comMark);
        printf("\t\t%d\n", L->data[i].total);
    }
    printf("==============================================================================\n");
}

void UpdateInfo(SeqList *L, DataType i) {
    printf("\n请输入学生编号：");
    scanf("%d", &L->data[i].num);
    printf("\n请输入学生学号：");
    scanf("%d", &L->data[i].id);
    printf("\n请输入学生姓名：");
    scanf("%s", L->data[i].name);
    printf("\n请输入学生性别：");
    scanf("%s", L->data[i].sex);
    printf("\n请输入学生系别：");
    scanf("%s", L->data[i].faculty);
    printf("\n请输入学生英语成绩：");
    scanf("%d", &L->data[i].engMark);
    printf("\n请输入学生数学成绩：");
    scanf("%d", &L->data[i].matMark);
    printf("\n请输入学生计算机成绩：");
    scanf("%d", &L->data[i].comMark);
    L->data[i].total = L->data[i].engMark + L->data[i].matMark + L->data[i].comMark;
}

void MenuLayout() {
    printf("顺序表的各种操作\n");
    printf("||          1.读取学生信息顺序表                ||\n");
    printf("||          2.插入学生信息条目                  ||\n");
    printf("||          3.删除学生信息条目                  ||\n");
    printf("||          4.按位置查找学生信息                ||\n");
    printf("||          5.按学号查找学生信息                ||\n");
    printf("||          6.求顺序表的长度                   ||\n");
    printf("||          7.更新学生信息条目                  ||\n");
    printf("||          8.学生信息排序                     ||\n");
}

void Menu() {
    int flag, n, i, loc;
    BaseType x;
    DataType t;
    MenuLayout();
    printf("请输入选项: ");
    scanf("%d", &flag);
    switch (flag) {
        case 1:
            InitList(&L);
            CreateList(&L);
            printf("建立数据内容为: ");
            DispList(&L);
            break;
        case 2:
            printf("请输入要插入的位置: ");
            scanf("%d", &i);
            printf("请输入要插入的学生信息: \n");
            printf("\n请输入学生编号：");
            scanf("%d", &x.num);
            printf("\n请输入学生学号：");
            scanf("%d", &x.id);
            printf("\n请输入学生姓名：");
            scanf("%s", x.name);
            printf("\n请输入学生性别：");
            scanf("%s", x.sex);
            printf("\n请输入学生系别：");
            scanf("%s", x.faculty);
            printf("\n请输入学生英语成绩：");
            scanf("%d", &x.engMark);
            printf("\n请输入学生数学成绩：");
            scanf("%d", &x.matMark);
            printf("\n请输入学生计算机成绩：");
            scanf("%d", &x.comMark);
            x.total = x.engMark + x.matMark + x.comMark;
            if (InsElem(&L, i, &x)) {
                printf("已成功在第%d的位置上添加新条目, 添加后的数据为: \n", i);
                DispList(&L);
            }
            else
                printf("输入插入点参数错误!");
            break;
        case 3:
            printf("请输入要删除的元素位置: ");
            scanf("%d", &i);
            if (DelElem(&L, i, &x)) {
                printf("已成功在第%d条的位置上删除学生信息, 删除后的线性表为: \n", i);
                DispList(&L);
            }
            else
                printf("\n输入删除的参数错误");
            break;
        case 4:
            printf("请输入要查看表中元素位置(从1开始): ");
            scanf("%d", &i);
            if(GetElem(&L, i, &x)) {
                printf("当前线性表第%d个条目的值为:\n", i);
                printf("\n编号\t\t学号\t\t\t姓名\t\t性别\t\t系名\t\t\t英语\t\t数学\t\t计算机\t总分\n");
                printf("=============================================================================\n");
                printf("%d", x.num);
                printf("\t\t%d", x.id);
                printf("\t%-8s", x.name);
                printf("\t%s", x.sex);
                printf("\t\t%s", x.faculty);
                printf("\t\t\t%d", x.engMark);
                printf("\t\t%d", x.matMark);
                printf("\t\t%d", x.comMark);
                printf("\t\t%d\n", x.total);
                printf("=============================================================================\n");
            }
            else
                printf("输入的位置错误!");
            break;
        case 5:
            printf("请输入要查找的元素值为: ");
            scanf("%d", &t);
            loc = Locate(&L, t);
            if (loc) {
                printf("\n编号\t\t学号\t\t\t姓名\t\t性别\t\t系名\t\t\t英语\t\t数学\t\t计算机\t总分\n");
                printf("=============================================================================\n");
                printf("%d", L.data[loc].num);
                printf("\t\t%d", L.data[loc].id);
                printf("\t%-8s", L.data[loc].name);
                printf("\t%s", L.data[loc].sex);
                printf("\t\t%s", L.data[loc].faculty);
                printf("\t\t\t%d", L.data[loc].engMark);
                printf("\t\t%d", L.data[loc].matMark);
                printf("\t\t%d", L.data[loc].comMark);
                printf("\t\t%d\n", L.data[loc].total);
                printf("=============================================================================\n");
            }
            else
                printf("该表中无此元素!");
            break;
        case 6:
            printf("当前线性表的长度为: %d", L.Length);
            break;
        case 7:
            printf("请输入要更新的元素位置");
            scanf("%d", &t);
            UpdateInfo(&L, t - 1);
            DispList(&L);
            break;
        case 8:
            printf("开始排序了");
        default:
            printf("输入有误, 请重新输入!");
            Menu();
    }
}

void Stop() {
    int flag;
    printf("\n0.退出");
    printf("\n1.继续");
    printf("\n是否继续:");
    scanf("%d", &flag);
    if (flag) {
        Menu();
        Stop();
    }
}

int main() {
    Menu();
    Stop();
    return 0;
}
