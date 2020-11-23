//
//  main.c
//  cLearning
//
//  Created by 邢泽林 on 2020/11/16.
//

#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef struct linknode {
    DataType data;
    struct linknode *next;
} LinkList;
LinkList L;
LinkList Deleted;
int delNum = 1;

LinkList *InitList(LinkList *head) {
    head = (LinkList *)malloc(sizeof(LinkList));
    head->next = NULL;
    return head;
}

void CreateListH(LinkList *head, int n) {
    LinkList *s;
    int i;
    printf("请输入%d个整数: \n", n);
    for (i = 0; i < n; i++) {
        s = (LinkList *)malloc(sizeof(LinkList));
        scanf("%d", &s->data);
        s->next = head->next;
        head->next = s;
    }
    printf("建立链表操作成功!\n");
}

void CreateListL(LinkList *head, int n) {
    LinkList *s, *last;
    int i;
    last = head;
    printf("请输入%d个整数: \n",n);
    for (i = 0; i< n; i++) {
        s = (LinkList *)malloc(sizeof(LinkList));
        scanf("%d", &s->data);
        s->next = NULL;
        last->next = s;
        last = s;
    }
    printf("建立链表操作成功\n");
}

int LengthList(LinkList *head) {
    LinkList *p = head->next;
    int j = 0;
    while (p != NULL) {
        p = p->next;
        j++;
    }
    return j;
}

void Locate(LinkList *head, DataType x) {
    int j = 1;
    LinkList *p;
    p = head->next;
    while (p != NULL && p->data != x) {
        p = p->next;
        j++;
    }
    if (p != NULL)
        printf("在表的第%d位找到值为%d的节点!\n", j, x);
    else
        printf("未找到值为%d的节点!\n", x);
}

void SearchList (LinkList *head, int i) {
    LinkList *p;
    int j = 0;
    p = head;
    if (i > LengthList(head))
        printf("位置错误,链表中没有该位置!\n");
    else {
        while (p->next != NULL && j < i) {
                p = p->next;
                j++;
            }
        if (j==i)
            printf("在第%d位上的元素值为%d!\n", i, p->data);
    }
}

void InsList(LinkList *head, int i, DataType x) {
    int j = 0;
    LinkList *p, *s;
    p = head;
    while (p->next != NULL && j < i-1) {
        p = p->next;
        j++;
    }
    if (p != NULL) {
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = x;
        s->next = p->next;
        p->next = s;
        printf("插入元素成功!\n");
    }
    else
        printf("插入元素失败!\n");
}

void DelList(LinkList *head, int i) {
    int j = 0;
    DataType x;
    InitList(&Deleted);
    LinkList *p = head, * s;
    while (p->next != NULL && j < i-1) {
        p = p->next;
        j++;
    }
    if (p->next != NULL && j == i-1) {
        s = p->next;
        x = s->data;
        InsList(&Deleted, delNum, x);
        delNum++;
        p->next = s->next;
        free(s);
        printf("删除第%d位上的元素%d成功!\n", i, x);
    }
    else
        printf("删除节点位置错误,删除失败!\n");
}

void DispList(LinkList *head) {
    LinkList *p;
    p = head->next;
    while (p != NULL) {
        printf("%5d", p->data);
        p = p->next;
    }
}

void MenuLayout() {
    printf("链表的各种操作\n");
    printf("1.头插法建立链表\n");
    printf("2.尾插法建立链表\n");
    printf("3.求链表长度函数\n");
    printf("4.按值查找\n");
    printf("5.按序号查找\n");
    printf("6.插入操作\n");
    printf("7.删除操作\n");
    printf("8.输出全部\n");
    printf("9.输出历史上被删除的元素\n");
    printf("请输入选项: ");
}

void Menu() {
    MenuLayout();
    int select, flag, temp, locate;
    scanf("%d", &select);
    switch (select) {
        case 1:
            InitList(&L);
            printf("请输入要创建元素的个数: ");
            scanf("%d", &temp);
            CreateListH(&L, temp);
            printf("现在的链表元素:\n");
            DispList(&L);
            break;
        case 2:
            InitList(&L);
            printf("请输入要创建元素的个数: ");
            scanf("%d", &temp);
            CreateListL(&L, temp);
            printf("现在的链表元素:\n");
            DispList(&L);
            break;
        case 3:
            printf("链表长度为: %d\n", LengthList(&L));
            break;
        case 4:
            printf("请输入要查找的序号: ");
            scanf("%d", &temp);
            Locate(&L, temp);
            break;
        case 5:
            printf("请输入要查找的位置: ");
            scanf("%d", &locate);
            SearchList(&L, locate);
            break;
        case 6:
            printf("请输入要插入的位置: ");
            scanf("%d", &locate);
            printf("请输入要插入的元素: ");
            scanf("%d", &temp);
            InsList(&L, locate, temp);
            printf("现在的链表元素:\n");
            DispList(&L);
            break;
        case 7:
            printf("请输入要删除的位置: ");
            scanf("%d", &locate);
            DelList(&L, locate);
            printf("现在的链表元素:\n");
            DispList(&L);
            break;
        case 8:
            DispList(&L);
            break;
        case 9:
            printf("历史上被删除的节点: ");
            DispList(&Deleted);
            break;
        default:
            printf("输入错误!");
            break;
    }
    printf("\n0.退出\n");
    printf("1.继续\n");
    printf("是否继续: ");
    scanf("%d", &flag);
    if (flag == 1) {
        Menu();
    }
    else if (flag == 0) {
        exit(0);
    }
    else {
        printf("\n输入错误, 请重新输入\n");
        Menu();
    }
}

int main(int argc, const char * argv[]) {
    Menu();
    return 0;
}
