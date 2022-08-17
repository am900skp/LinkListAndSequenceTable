//C风格有序链表
#include <stdio.h>
#include <stdlib.h>

struct data {
    int index;  //构建序号
    int data;   //数据
};

struct Node {
    struct data my_data;
    struct Node* p_next;
};

//创建有头链表
struct Node* CreateList() {
    struct Node* p_list = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == p_list) {
        return NULL;
    }
    //初始化头结点
    p_list->p_next = NULL;
    return p_list;
}

//创建结点
struct Node* CreateNewNode(struct data my_data) {
    struct Node* p_new_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == p_new_node) {
        return NULL;
    }
    //初始化结点数据
    p_new_node->my_data = my_data;
    p_new_node->p_next = NULL;
    return p_new_node;
}

void InsertOrderList(struct Node* p_list, struct data my_data) {
    struct Node* p_new_node = CreateNewNode(my_data);
    struct Node* pre_node = p_list;          //前驱结点
    struct Node* cur_node = p_list->p_next;  //当前结点
    //升序
    while (NULL != cur_node && cur_node->my_data.index < my_data.index) {
        pre_node = cur_node;
        cur_node = pre_node->p_next;
    }
    if (NULL == cur_node) {
        pre_node->p_next = p_new_node;
    } else {
        pre_node->p_next = p_new_node;
        p_new_node->p_next = cur_node;
    }
}

void PrintList(struct Node* p_list) {
    struct Node* p_move = p_list->p_next;
    while (NULL != p_move) {
        printf("序号:%d,数据:%d\n", p_move->my_data.index, p_move->my_data.data);
        p_move = p_move->p_next;
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    //五对数据,两个两个是一对
    struct data array[5] = {2, 1, 5, 3, 6, 8, 7, 10, 11, 0};
    struct Node* p_list = CreateList();
    for (int i = 0; i < 5; ++i) {
        InsertOrderList(p_list, array[i]);
    }
    PrintList(p_list);
    return 0;
}