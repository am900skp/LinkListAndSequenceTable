/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月10日18:15:04
    @brief:    初识链表
    @message:  代码的上一行为所写注释,命名规范在2022年8月11日19:07:23完成统一.指针变量前缀加上p_
*/

#include <stdio.h>

//结点类型
struct Node {
    int data;
    struct Node* p_next;
};

int main(int argc, char* argv[]) {
    //创建三个结点
    struct Node node1 = {1, NULL};
    struct Node node2 = {2, NULL};
    struct Node node3 = {3, NULL};
    //将结点连接在一起,形成链表
    node1.p_next = &node2;
    node2.p_next = &node3;
    //遍历链表
    struct Node* p_move = &node1;
    printf("第一个节点数据:%d\n", p_move->data);
    printf("第二个节点数据:%d\n", p_move->p_next->data);
    printf("第三个节点数据:%d\n", p_move->p_next->p_next->data);
    //上面不太方便，用循环来做
    while (p_move != NULL) {
        printf("%d  ", p_move->data);
        p_move = p_move->p_next;  
    }
    return 0;
}