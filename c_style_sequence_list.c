#include <stdio.h>
#include <stdlib.h>
struct MM {
    char name[20];
    int age;
};

struct Data {
    int index;
    struct MM mm_data;
};

typedef struct Node {
    struct Data data;
    struct Node* p_next;
} NODE, *LPNODE;

typedef struct SqList {
    int sql_size;
    LPNODE p_head_node;
} SQLIST, *LPSQLIST;

LPNODE CreateList() {
    LPNODE p_head_node = (LPNODE)malloc(sizeof(NODE));
    if (NULL == p_head_node) {
        return NULL;
    }
    p_head_node->p_next = NULL;
    return p_head_node;
}

LPNODE CreateNode(struct Data new_data) {
    LPNODE p_new_node = (LPNODE)malloc(sizeof(NODE));
    if (NULL == p_new_node) {
        return NULL;
    }
    p_new_node->data = new_data;
    p_new_node->p_next = NULL;
    return p_new_node;
}

//创建顺序表
LPSQLIST CreateSqList() {
    LPSQLIST p_sqlist = (LPSQLIST)malloc(sizeof(SQLIST));
    if (NULL == p_sqlist) {
        return NULL;
    }
    p_sqlist->sql_size = 0;
    p_sqlist->p_head_node = CreateList();
    return p_sqlist;
}

void PrintSqList(LPSQLIST p_sqlist) {
    LPNODE p_move = p_sqlist->p_head_node->p_next;
    while (NULL != p_move) {
        printf("序号:%d\t姓名:%s\t年龄:%d\n", p_move->data.index,
               p_move->data.mm_data.name, p_move->data.mm_data.age);
        p_move = p_move->p_next;
    }
    putchar('\n');
}

void InsertData(LPSQLIST p_sqlist, struct Data new_data) {
    LPNODE p_new_node = CreateNode(new_data);
    //找到指定位置
    LPNODE p_pre_node = p_sqlist->p_head_node;
    LPNODE p_pos_node = p_sqlist->p_head_node->p_next;
    while (NULL != p_pos_node && p_pos_node->data.index < new_data.index) {
        p_pre_node = p_pos_node;
        p_pos_node = p_pre_node->p_next;
    }
    // if (NULL == p_pos_node) {
    //     p_pre_node->p_next = p_new_node;
    // } else {
    //     p_pre_node->p_next = p_new_node;
    //     p_new_node->p_next = p_pos_node;
    // }
    p_pre_node->p_next = p_new_node;
    p_new_node->p_next = p_pos_node;
    p_sqlist->sql_size++;
}

void DeleteNode(LPSQLIST p_sqlist, int index) {
    LPNODE p_pre_node = p_sqlist->p_head_node;
    LPNODE p_pos_node = p_sqlist->p_head_node->p_next;
    while (NULL != p_pos_node && p_pos_node->data.index != index) {
        p_pre_node = p_pos_node;
        p_pos_node = p_pos_node->p_next;
    }
    if (NULL == p_pos_node) {
        printf("未找到数据");
        return;
    } else {
        p_pre_node->p_next = p_pos_node->p_next;
        free(p_pos_node);
        p_pos_node = NULL;
        p_sqlist->sql_size--;
    }
}

int main(int argc, char* argv[]) {
    LPSQLIST p_sqlist = CreateSqList();
    struct Data array[4] = {3, "小红", 18, 1, "小明",  14,
                            0, "雨墨", 18, 2, "小asd", 4};
    for (int i = 0; i < 4; ++i) {
        InsertData(p_sqlist, array[i]);
    }
    PrintSqList(p_sqlist);
    printf("删除序号为3的结点:\n");
    DeleteNode(p_sqlist, 3);
    PrintSqList(p_sqlist);
    return 0;
}