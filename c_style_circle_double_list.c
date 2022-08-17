// C风格双向循环链表
#include <stdio.h>
#include <stdlib.h>

//结点类型
typedef struct Node {
    int data;
    struct Node* p_left;
    struct Node* p_right;
} NODE, *LPNODE;

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
LPNODE CreateList() {
    LPNODE p_head_node = (LPNODE)malloc(sizeof(NODE));
    if (NULL == p_head_node) {
        return NULL;
    }
    p_head_node->p_left = p_head_node->p_right = p_head_node;  //都指向自身
    return p_head_node;
}

//尾插
//不需要找表尾,表尾就是默认头结点的lef t指针所指向的位置
//注意:用头结点描述尾结点
void InsertNewNodeByTail(LPNODE p_head_node, int new_data) {
    LPNODE p_new_node = CreateNode(new_data);
    //换了一种方式表示表尾,用表头的左指针表示表尾
    // p_head_node->p_left->p_right = p_new_node
    //也就是说表尾->p_right = p_new_node;
    p_head_node->p_left->p_right = p_new_node;
    p_new_node->p_left = p_head_node->p_left;
    // p_new_node->p_left = p_head_node->p_left
    // p_new_node->p_left等价于表尾
    p_new_node->p_right = p_head_node;
    p_head_node->p_left = p_new_node;
}

//顺序遍历链表
void OrderPrintList(LPNODE p_head_node) {
    //因为是环形的,所以不能用老规矩(NULL结束遍历)
    //只需要遍历一圈,再走到头结点结束遍历即可
    LPNODE p_move = p_head_node->p_right;
    while (p_head_node != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_right;
    }
    putchar('\n');
}

//逆序遍历链表
void ReverseOrderPrintList(LPNODE p_head_node) {
    LPNODE p_move = p_head_node->p_left;
    while (p_head_node != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_left;
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    LPNODE p_list = CreateList();
    for (int i = 0; i < 3; ++i) {
        InsertNewNodeByTail(p_list, i);
    }
    printf("顺序遍历链表:");
    OrderPrintList(p_list);
    printf("逆序遍历链表:");
    ReverseOrderPrintList(p_list);
    return 0;
}
