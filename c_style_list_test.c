/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月10日20:32:06
    @brief:    这个写的比较乱,但是代码是没问题的
    @message:  代码的上一行为所写注释
*/

#include <stdio.h>
#include <stdlib.h>

#define IS_LIST 0

struct Node {
    int data;
    struct Node* p_next;
};

#if IS_LIST
struct List {
    struct Node* p_root;
};
#endif

#if IS_LIST
void InitList(struct List* p_list);
#endif

struct Node* CreateNode(int new_data);

#if IS_LIST
void AppendNode(struct List* p_list, int new_data);
#else
void AppendNode(struct Node** p_head_node, int new_data);
#endif

#if IS_LIST
void PrintList(struct List* p_list);
#else
void PrintList(struct Node* p_head);
#endif

#if IS_LIST
#else
void InsertNewNodeByHead(struct Node** p_head, int new_data);
#endif

#if IS_LIST
//中间插入
void InsertPosNode(struct List* p_list, int pos, int new_data);
#else
void InsertPosNode(struct Node** head, int pos, int new_data);
#endif
void DeletePosNode(struct Node** p_head, int pos);
void DeleteHeadNode(struct Node** p_head);
int main(int argc, char** argv) {
#if IS_LIST
    struct List list;
    InitList(&list);
    for (int i = 0; i < 10; ++i) {
        AppendNode(&list, i);
    }
    PrintList(&list);
#else
    struct Node* p_head = NULL;
    for (int i = 0; i < 10; ++i) {
        InsertNewNodeByHead(&p_head, i);
        PrintList(p_head);
    }

    InsertPosNode(&p_head, 2, 666);
    PrintList(p_head);
#endif
    return 0;
}
#if IS_LIST
void InitList(struct List* p_list) {
    p_list->p_root = NULL;
}
#endif
struct Node* CreateNode(int new_data) {
    struct Node* p_new_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == p_new_node) {
        return NULL;
    }
    p_new_node->data = new_data;
    p_new_node->p_next = NULL;
    return p_new_node;
}
#if IS_LIST
void AppendNode(struct List* p_list, int new_data) {
    if (NULL == p_list) {
        return;
    }
    struct Node* p_new_node = CreateNode(new_data);
    if (NULL == p_new_node) {
        return;
    }
    if (p_list->p_root) {
        struct Node* p_tmp = p_list->p_root;
        while (NULL != p_tmp->p_next) {
            p_tmp = p_tmp->p_next;
        }
        p_tmp->p_next = p_new_node;
    } else {
        p_list->p_root = p_new_node;
    }
}
#else
void AppendNode(struct Node** p_head_node, int new_data) {
    struct Node* p_new_node = CreateNode(new_data);
    if (NULL == p_new_node) {
        return;
    }
    if (*p_head_node) {
        struct Node* p_tmp = *p_head_node;
        while (NULL != p_tmp->p_next) {
            p_tmp = p_tmp->p_next;
        }
        p_tmp->p_next = p_new_node;
    } else {
        *p_head_node = p_new_node;
    }
}
#endif

#if IS_LIST
void PrintList(struct List* p_list) {
    struct Node* p_tmp = p_list->p_root;
    printf("list: ");
    while (p_tmp) {
        printf("%d  ", p_tmp->data);
        p_tmp = p_tmp->p_next;
    }
    putchar('\n');
}
#else
void PrintList(struct Node* p_head) {
    struct Node* p_tmp = p_head;
    printf("list: ");
    while (p_tmp) {
        printf("%d  ", p_tmp->data);
        p_tmp = p_tmp->p_next;
    }
    putchar('\n');
}
#endif

#if IS_LIST
#else
void InsertNewNodeByHead(struct Node** p_head, int new_data) {
    struct Node* p_new_node = CreateNode(new_data);
    p_new_node->p_next = *p_head;
    *p_head = p_new_node;
}
#endif

//从head链表中找到pos结点并返回,找不到返回NULL
struct Node* FindPos(struct Node* p_head_node, int pos) {
    if (NULL == p_head_node) {
        return NULL;
    }
    struct Node* p_tmp = p_head_node;
    for (int i = 0; i < pos; ++i) {
        if (NULL == p_tmp) {
            return NULL;
        }
        p_tmp = p_tmp->p_next;
    }
    return p_tmp;
}

#if IS_LIST
//中间插入
void InsertPosNode(struct List* p_list, int pos, int new_data) {}
#else
void InsertPosNode(struct Node** head, int pos, int new_data) {
    if (NULL == *head) {
        return;
    }
    if (NULL == *head || 0 == pos) {
        AppendNode(head, new_data);
    }
    //这里我写的是以数组下标为基准插入,所以pos - 1
    struct Node* p_tmp = FindPos(*head, pos - 1);
    struct Node* p_new_node = CreateNode(new_data);
    p_new_node->p_next = p_tmp->p_next;
    p_tmp->p_next = p_new_node;
}
#endif

//删除链表中第一个节点
void DeleteHeadNode(struct Node** p_head) {
    if (NULL == p_head) {
        return;
    }
    //临时存储要删的节点
    struct Node* p_del = *p_head;
    //*head 的下一个节点要成为新的头节点
    *p_head = (*p_head)->p_next;
    //释放内存
    free(p_del);
}
//删除链表中第pos个节点
void DeletePosNode(struct Node** p_head, int pos) {
    if (NULL == p_head || pos < 0) {
        return;
    }
    if (0 == pos) {
        DeleteHeadNode(p_head);
        return;
    }
    //临时存储pos节点地址
    struct Node* p_del = FindPos(*p_head, pos);
    if (NULL == p_del) {
        return;
    }
    //先找到pos-1节点
    struct Node* p_del_prev = FindPos(*p_head, pos - 1);
    if (NULL == p_del_prev) {
        return;
    }
    // pos-1节点的next指针指向pos的下一个节点
    p_del_prev->p_next = p_del->p_next;
    //释放pos节点内存
    free(p_del);
}

