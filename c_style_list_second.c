/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月10日18:33:06
    @brief:    单链表的相关操作(具体请查看主函数)
    @message:
   代码的上一行为所写注释,命名规范在2022年8月11日19:06:46完成统一.指针变量前缀加上p_
*/

#include <stdio.h>
#include <stdlib.h>

//结点类型
struct Node {
    int data;
    struct Node* p_next;
};

//创建表头
struct Node* CreateHeadNode() {
    struct Node* p_head_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == p_head_node) {
        return NULL;
    }
    //这里我写的是有头链表,表头不存储数据,所以不需要将data进行初始化
    p_head_node->p_next = NULL;
    return p_head_node;
}

//创建新结点,每次需要插入数据时就调用该函数,将int类型的数据初始化为结点类型
struct Node* CreateNewNode(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == new_node) {
        return NULL;
    }
    //初始化新结点
    new_node->data = new_data;
    new_node->p_next = NULL;
    return new_node;
}

//遍历链表
void PrintList(struct Node* p_head_node) {
    //定义移动指针,因为头结点不存储数据,所以直接指向头结点的下一个结点
    struct Node* p_move = p_head_node->p_next;
    while (NULL != p_move) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_next;
    }
    putchar('\n');
}

//表头法插入
void InsertNewNodeByHead(struct Node* p_head_node, int new_data) {
    //调用生成新结点函数
    struct Node* p_new_node = CreateNewNode(new_data);
    //表头法插入
    p_new_node->p_next = p_head_node->p_next;
    p_head_node->p_next = p_new_node;
}

//表尾法插入(push_back)
void InsertNewNodeByTail(struct Node* p_head_node, int new_data) {
    struct Node* p_new_node = CreateNewNode(new_data);
    struct Node* p_tail_node = p_head_node;
    //找到尾结点
    while (NULL != p_tail_node->p_next) {
        p_tail_node = p_tail_node->p_next;
    }
    //表尾法插入
    p_tail_node->p_next = p_new_node;
}

//指定位置插入(以data作为参照)
void InsertByDataValue(struct Node* p_head_node, int data_value, int new_data) {
    struct Node* p_pre_node = p_head_node;
    struct Node* p_cur_node = p_head_node->p_next;
    // 注意:条件不能交换(短路现象)
    // p_p_cur_node == NULL,NULL->data
    // 判断是否为所寻找的数据的前提是p_p_cur_node!=NULL
    while (p_cur_node != NULL && p_cur_node->data != data_value) {
        // p_p_pre_node = p_p_pre_node->p_next;
        // p_p_cur_node = p_p_cur_node->p_next;
        // 下面的写法更能够体现相邻的特色
        p_pre_node = p_cur_node;
        p_cur_node = p_pre_node->p_next;
    }
    //分析结果
    if (NULL == p_cur_node) {
        printf("没有找到指定结点,无法插入\n");
    } else {
        struct Node* new_node = CreateNewNode(new_data);
        p_pre_node->p_next = new_node;
        new_node->p_next = p_cur_node;
    }
}

//指定位置插入(以第几个结点作为参照)
void InsertByNodeIndex(struct Node* p_head_node, int node_index, int new_data) {
    if (node_index < 0) {
        printf("序号有问题,无法插入\n");
        return;
    }
    //加一个计数的
    //因为是不存在第0个元素的
    int count = 1;
    struct Node* p_pre_node = p_head_node;
    struct Node* p_cur_node = p_head_node->p_next;
    while (p_cur_node != NULL && count < node_index) {
        p_pre_node = p_cur_node;
        p_cur_node = p_cur_node->p_next;
        ++count;
    }
    if (NULL == p_cur_node) {
        printf("序号有问题,无法插入\n");
    } else {
        struct Node* new_node = CreateNewNode(new_data);
        p_pre_node->p_next = new_node;
        new_node->p_next = p_cur_node;
    }
}

//通过头结点删除(本质上是删除头结点的下一个结点)
void DeleteByHead(struct Node* p_head_node) {
    struct Node* p_next_node = p_head_node->p_next;
    //防御性编程
    if (NULL == p_head_node || NULL == p_next_node) {
        printf("链表为空,无法删除\n");
        return;
    } else {
        p_head_node->p_next = p_next_node->p_next;
        free(p_next_node);
        p_next_node = NULL;
    }
}

//通过尾结点删除
void DeleteByTail(struct Node* p_head_node) {
    struct Node* p_pre_node = p_head_node;
    struct Node* p_tail_node = p_head_node->p_next;
    if (NULL == p_head_node || p_tail_node == NULL) {
        printf("链表为空,无法删除\n");
        return;
    }
    while (NULL != p_tail_node->p_next) {
        p_pre_node = p_tail_node;
        p_tail_node = p_pre_node->p_next;
    }
    //将尾结点置为空
    p_pre_node->p_next = NULL;
    free(p_tail_node);
    p_tail_node = NULL;
}

//通过data删除指定位置结点
void DeleteByNodeIndex(struct Node* p_head_node, int data_value) {
    struct Node* p_pre_node = p_head_node;
    struct Node* p_cur_node = p_head_node->p_next;
    if (NULL == p_head_node || NULL == p_cur_node) {
        printf("链表为空,无法删除\n");
        return;
    }
    while (NULL != p_cur_node && p_cur_node->data != data_value) {
        p_pre_node = p_cur_node;
        p_cur_node = p_pre_node->p_next;
    }
    if (NULL == p_cur_node) {
        printf("未找到指定结点\n");
    } else {
        p_pre_node->p_next = p_cur_node->p_next;
        free(p_cur_node);
        p_cur_node = NULL;
    }
}

//寻找相同的结点
struct Node* SearchNode(struct Node* p_head_node, int data_value) {
    struct Node* p_move = p_head_node->p_next;
    while (NULL != p_move && p_move->data != data_value) {
        p_move = p_move->p_next;
    }
    return p_move;
}

//删除所有相同的结点
void DeleteAllSameNode(struct Node* p_head_node, int data_value) {
    while (NULL != SearchNode(p_head_node, data_value)) {
        DeleteByNodeIndex(p_head_node, data_value);
    }
}

//销毁链表
void DestoryList(struct Node** p_head_node) {
    while (NULL != (*p_head_node)->p_next) {
        DeleteByHead(*p_head_node);
    }
    free(*p_head_node);
    *p_head_node = NULL;
}

int main(int argc, char* argv[]) {
    //创建链表
    struct Node* p_list = CreateHeadNode();

    printf("测试表头法插入:");
    for (int i = 1; i <= 3; ++i) {
        InsertNewNodeByHead(p_list, i);
    }
    PrintList(p_list);

    printf("测试表尾法插入:");
    for (int i = 1; i <= 3; ++i) {
        InsertNewNodeByTail(p_list, i);
    }
    PrintList(p_list);

    printf("测试以数据作为参照插入新节点:");
    InsertByDataValue(p_list, 1, 666);
    PrintList(p_list);

    printf("测试以结点作为参照插入新节点:");
    InsertByNodeIndex(p_list, 1, 888);
    PrintList(p_list);

    printf("通过头结点删除:");
    DeleteByHead(p_list);
    PrintList(p_list);

    printf("通过尾结点删除:");
    DeleteByTail(p_list);
    PrintList(p_list);

    printf("通过数据删除指定结点:");
    DeleteByNodeIndex(p_list, 666);
    PrintList(p_list);

    printf("删除所有的'1':");
    DeleteAllSameNode(p_list, 1);
    PrintList(p_list);

    printf("销毁链表:");
    DestoryList(&p_list);
    printf("%p", p_list);

    return 0;
}