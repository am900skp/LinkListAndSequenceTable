//找两个链表中的相同元素组成第三个链表
//C风格单链表的动作,反转,合并
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* p_next;
};
//创建有头链表
struct Node* CreateList() {
    struct Node* p_list = (struct Node*)malloc(sizeof(struct Node));
    if (p_list == NULL) {
        return NULL;
    }
    p_list->p_next = NULL;
    return p_list;
}
struct Node* CreateNewNode(int new_data) {
    struct Node* p_new_node = (struct Node*)malloc(sizeof(struct Node));
    if (p_new_node == NULL) {
        return NULL;
    }
    p_new_node->data = new_data;
    p_new_node->p_next = NULL;
    return p_new_node;
}
//头结点后面插入
void InsertNode(struct Node* p_list, int new_data) {
    struct Node* p_new_node = CreateNewNode(new_data);
    p_new_node->p_next = p_list->p_next;  //新结点的下一个指向头结点的下一个
    p_list->p_next = p_new_node;  //头结点的下一个指向新结点
}
void PrintList(struct Node* p_list) {
    struct Node* p_move = p_list->p_next;
    while (p_move != NULL) {
        printf("%d\t", p_move->data);
        p_move = p_move->p_next;
    }
    printf("\n");
}
//交集
void Intersection(struct Node* p_list_one,
                  struct Node* p_list_two,
                  struct Node* p_list_three) {
    for (struct Node* p_first = p_list_one->p_next; NULL != p_first;
         p_first = p_first->p_next) {
        for (struct Node* p_second = p_list_two->p_next; NULL != p_second;
             p_second = p_second->p_next) {
            if (p_first->data == p_second->data) {
                InsertNode(p_list_three, p_second->data);
            }
        }
    }
}

//释放链表
void FreeList(struct Node** p_list) {
    if (NULL == p_list) {
        return;
    }
    struct Node* p_next_node = NULL;
    while (NULL != *p_list) {
        p_next_node = (*p_list)->p_next;
        free(*p_list);
        *p_list = p_next_node;
    }
}

//反转链表
// 1>>遍历逆序插入
void ReverseFirstWay(struct Node** p_list) {
    struct Node* p_tmp_list = CreateList();
    struct Node* p_move = (*p_list)->p_next;
    while (NULL != p_move) {
        InsertNode(p_tmp_list, p_move->data);
        p_move = p_move->p_next;
    }
    //释放原有的内存
    FreeList(p_list);
    *p_list = p_tmp_list;  //指向新的链表
}

//把每一个指向结点的指针掉转,再将头指针指向尾结点
void ReverseSecondWay(struct Node** p_list) {
    struct Node* p_pre_node = NULL;               //前驱结点
    struct Node* p_cur_node = (*p_list)->p_next;  //当前结点
    struct Node* p_next_node = (*p_list)->p_next;  //当前结点的下一个结点
    while (NULL != p_cur_node) {
        p_next_node = p_cur_node->p_next;  //保存下一个结点
        p_cur_node->p_next = p_pre_node;  //当前结点的p_next指针指向前驱结点
        p_pre_node = p_cur_node;   //前驱结点变成当前结点
        p_cur_node = p_next_node;  //当前结点变成下一个结点
    }
    (*p_list)->p_next = p_pre_node;  //表头指向最后一个结点       
}

int main(int argc, char* argv[]) {
    struct Node* list1 = CreateList();
    struct Node* list2 = CreateList();
    struct Node* list3 = CreateList();
    for (int i = 0; i < 3; ++i) {
        InsertNode(list1, i);
        InsertNode(list2, i);
    }
    InsertNode(list2, 100);
    Intersection(list1, list2, list3);
    PrintList(list3);

    struct Node* reverse_list = CreateList();
    for (int i = 1; i <= 3; ++i) {
        InsertNode(reverse_list, i);
    }
    printf("reverse_list反转前:");
    PrintList(reverse_list);
    printf("\n");
    printf("reverse_list反转后:");
    ReverseFirstWay(&reverse_list);
    PrintList(reverse_list);

    printf("reverse_list反转前:");
    PrintList(reverse_list);
    ReverseSecondWay(&reverse_list);
    printf("reverse_list反转后:");
    PrintList(reverse_list);

    return 0;
}
