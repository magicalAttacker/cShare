//
//  main.c
//  linnerStronge
//
//  Created by 邢泽林 on 2020/11/17.
//

#include <stdio.h>
#define MAXLEN 100
typedef int DataType;
typedef struct {
    DataType data[MAXLEN];
    int Length;
}SeqList;
SeqList L;

void InitList(SeqList *L) {
    L->Length = 0;
}

void CreateList(SeqList *L, int n) {
    int i;
    printf("请输入%d个整数: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &L->data[i]);
    L->Length = i;
}

int GetElem(SeqList *L, int i, DataType *x) {
    if (i < 1 || i > L->Length)
        return 0;
    else {
        *x = L->data[i - 1];
        return 1;
    }
}

int Locate(SeqList *L, DataType x) {
    int i = 0;
    while(i < L->Length && L->data[i] != x)
        i++;
    if (i >= L->Length)
        return 0;
    else
        return i + 1;
}

int InsElem(SeqList *L, int i, DataType x) {
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
        L->data[i - 1] = x;
        L->Length++;
        return 1;
    }
    for (j = L->Length - 1; j >= i - 1; j--)
        L->data[j + 1] = L->data[j];
    L->data[i - 1] = x;
    L->Length++;
    return 1;
}

int DelElem(SeqList *L, int i, DataType *x) {
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
    for (i = 0; i < L->Length; i++)
        printf("%5d", L->data[i]);
}

void MenuLayout() {
    printf("顺序表的各种操作\n");
    printf("1.建立顺序表\n");
    printf("2.插入元素\n");
    printf("3.删除元素\n");
    printf("4.按位置查找元素\n");
    printf("5.按元素值查找元素\n");
    printf("6.求顺序表的长度\n");
    printf("请输入选项: ");
}

void Menu() {
    int flag, n, i, loc;
    DataType x;
    MenuLayout();
    printf("请输入选项: ");
    scanf("%d", &flag);
    switch (flag) {
        case 1:
            InitList(&L);
            printf("请输入建立线性表的个数: ");
            scanf("%d", &n);
            CreateList(&L, n);
            printf("建立的线性表为: ");
            DispList(&L);
            break;
        case 2:
            printf("请输入要插入的位置: ");
            scanf("%d", &i);
            printf("请输入要插入的元素值: ");
            scanf("%d", &x);
            if (InsElem(&L, i, x)) {
                printf("已成功在第%d的位置上输入%d, 插入后的线性表为: \n", i, x);
                DispList(&L);
            }
            else
                printf("输入插入点参数错误!");
            break;
        case 3:
            printf("请输入要删除的元素位置: ");
            scanf("%d", &i);
            if (DelElem(&L, i, &x)) {
                printf("已成功在第%d的位置上删除%d, 删除后的线性表为: \n", i, x);
                DispList(&L);
            }
            else
                printf("\n输入删除的参数错误");
            break;
        case 4:
            printf("请输入要查看表中元素位置(从1开始): ");
            scanf("%d", &i);
            if(GetElem(&L, i, &x))
                printf("当前线性表第%d个元素的值为: %d", i, x);
            else
                printf("输入的位置错误!");
            break;
        case 5:
            printf("请输入要插入的元素值为: ");
            scanf("%d", &x);
            loc = Locate(&L, x);
            if (loc)
                printf("查找元素值为%d的位置为: %d", x, loc);
            else
                printf("该表中无此元素!");
            break;
        case 6:
            printf("当前线性表的长度为: %d", L.Length);
            break;
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

int main(int argc, const char * argv[]) {
    Menu();
    Stop();
    return 0;
}
