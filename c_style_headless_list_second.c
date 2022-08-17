//C风格无头链表(2)
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* p_next;
};

struct Node* CreateNewNode(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == new_node) {
        return NULL;
    }
    new_node->data = new_data;
    new_node->p_next = NULL;
    return new_node;
}

void InsertNewNodeByHead(struct Node** list, int new_data) {
    struct Node* new_node = CreateNewNode(new_data);
    new_node->p_next = *list;  //新节点的下一个指向头结点
    *list = new_node;          //头结点变为新节点
}

void InsertNewNodeByPos(struct Node** list, int new_data, int pos_data) {
    struct Node* pos_node = *list;
    struct Node* pre_node = NULL;
    while (NULL != pos_node && pos_node->data != pos_data) {
        pre_node = pos_node;
        pos_node = pos_node->p_next;
    }
    if (NULL == pos_node) {
        printf("error\n");
    } else if (NULL == pre_node) {
        InsertNewNodeByHead(list, new_data);
    } else {
        struct Node* new_node = CreateNewNode(new_data);
        pre_node->p_next = new_node;
        new_node->p_next = pos_node;
    }
}

void PrintList(struct Node* p_list) {
    struct Node* p_move = p_list;
    while (NULL != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_next;
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    struct Node* list = CreateNewNode(1);
    PrintList(list);
    for (int i = 0; i < 3; ++i) {
        InsertNewNodeByHead(&list, i);
        PrintList(list);
    }
    InsertNewNodeByPos(&list, -100, 2);
    InsertNewNodeByPos(&list, 10010, 1);
    PrintList(list);
    return 0;
}