// C风格双向链表
#include <stdio.h>
#include <stdlib.h>

//结点类型,单一个体
typedef struct Node {
    int data;
    struct Node* p_left;   //指向左面的结点
    struct Node* p_right;  //指向右面的结点
} NODE, *LPNODE;

//链表类型
typedef struct List {
    LPNODE p_head_node;  //头结点
    LPNODE p_tail_node;  //尾结点
    int size;            //当前链表中结点个数
} LIST, *LPLIST;

//创建结点
LPNODE CreateNode(int new_data) {
    LPNODE p_new_node = (LPNODE)malloc(sizeof(NODE));
    if (NULL == p_new_node) {
        return NULL;
    }
    p_new_node->data = new_data;
    p_new_node->p_left = NULL;
    p_new_node->p_right = NULL;
    return p_new_node;
}

//创建链表
LPLIST CreateList() {
    LPLIST p_new_list = (LPLIST)malloc(sizeof(LIST));
    if (NULL == p_new_list) {
        return NULL;
    }
    p_new_list->size = 0;
    p_new_list->p_head_node = NULL;
    p_new_list->p_tail_node = NULL;
    return p_new_list;
}

//头插法,在有头结点前插入新节点
void InsertNewNodeByHead(int new_data, LPLIST p_list) {
    LPNODE p_new_node = CreateNode(new_data);
    if (p_list->size == 0) {  //链表为空
        p_list->p_tail_node = p_new_node;
        // p_list->p_head_node = p_new_node;
    } else {
        p_new_node->p_right = p_list->p_head_node;  //新结点的右指针指向头结点
        p_list->p_head_node->p_left = p_new_node;  //头结点左指针指向新结点
        // p_list->p_head_node = p_new_node;
    }
    p_list->p_head_node = p_new_node;  //头结点变成新结点
    p_list->size++;
}

//尾插法,在尾结点后插入新结点
void InsertNewNodeByTail(int new_data, LPLIST p_list) {
    LPNODE p_new_node = CreateNode(new_data);
    if (p_list->size == 0) {
        p_list->p_head_node = p_new_node;
        // p_list->p_tail_node = p_new_node;
    } else {
        p_new_node->p_left = p_list->p_tail_node;
        p_list->p_tail_node->p_right = p_new_node;
        // p_list->p_tail_node = p_new_node;
    }
    p_list->p_tail_node = p_new_node;
    p_list->size++;
}

//顺序遍历链表
void OrderPrintList(LPLIST p_list) {
    LPNODE p_move = p_list->p_head_node;
    while (NULL != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_right;
    }
    putchar('\n');
}

//逆序遍历链表
void ReverseOrderPrintList(LPLIST p_list) {
    LPNODE p_move = p_list->p_tail_node;
    while (NULL != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_left;
    }
    putchar('\n');
}

//指定位置插入
void InsertByPosData(LPLIST p_list, int new_data, int pos_data) {
    LPNODE pos_front = NULL;
    LPNODE pos_node = p_list->p_head_node;
    //遍历寻找指定结点
    while (NULL != pos_node && pos_node->data != pos_data) {
        pos_front = pos_node;
        pos_node = pos_front->p_right;
    }
    if (NULL == pos_node) {
        printf("未找到指定结点");
        return;
    } else {
        //表头法插入
        if (NULL == pos_front) {
            InsertNewNodeByHead(new_data, p_list);
        } else {  //指定结点插入
            LPNODE p_new_node = CreateNode(new_data);
            pos_front->p_right = p_new_node;
            p_new_node->p_left = pos_front;
            p_new_node->p_right = pos_node;
            pos_node->p_left = p_new_node;
            p_list->size++;
        }
    }
}

int main(int argc, char* argv[]) {
    LPLIST p_list = CreateList();
    for (int i = 0; i < 3; ++i) {
        InsertNewNodeByHead(i, p_list);
    }
    printf("头插法顺序遍历链表:");
    OrderPrintList(p_list);
    printf("头插法逆序遍历链表:");
    ReverseOrderPrintList(p_list);
    printf("在表尾插入100并顺序遍历链表:");
    InsertNewNodeByTail(100, p_list);
    OrderPrintList(p_list);
    printf("在0前面插入666并顺序遍历:");
    InsertByPosData(p_list, 666, 0);
    OrderPrintList(p_list);
    printf("在100前面插入999并逆序遍历:");
    InsertByPosData(p_list, 999, 100);
    ReverseOrderPrintList(p_list);
    return 0;
}
