/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月10日19:46:06
    @brief:    基础链式结构写管理系统(简单应用)
    @message:  代码的上一行为所写注释,命名规范在2022年8月11日19:12:17完成统一.指针变量前缀加上p_
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//美女类型
struct MM {
    char name[20];
    int age;
    int num;
};

//结点类型
struct Node {
    // int data;
    struct MM data;
    struct Node* p_next;
};

//创建表头
struct Node* CreateHeadNode();
//创建新结点,每次需要插入数据时就调用该函数,将int类型的数据初始化为结点类型
struct Node* CreateNewNode(struct MM data);
//遍历链表
void PrintList(struct Node* p_head_node);
//表头法插入
void InsertNewNodeByHead(struct Node* p_head_node, struct MM data);
//通过data删除指定位置结点
void DeleteByName(struct Node* p_head_node, const char* p_mm_name);
//寻找相同的结点
struct Node* SearchNode(struct Node* p_head_node, const char* p_mm_name);
//菜单
void Menu();
//录入信息
void InsertMMData(struct Node* p_head_node);
//查找信息
void SearchMMData(struct Node* p_head_node);
//修改信息
void ModifyMMData(struct Node* p_head_node);
//删除信息
void DeleteMMData(struct Node* p_head_node);
//冒泡排序
void BubbleSort(struct Node* p_head_node);
//选项
void KeyDown(struct Node* p_list);

int main(int argc, char* argv[]) {
    struct Node* p_list = CreateHeadNode();
    while (1) {
        Menu();
        KeyDown(p_list);
        system("pause");
        system("cls");
    }
    return 0;
}

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
struct Node* CreateNewNode(struct MM data) {
    struct Node* p_new_node = (struct Node*)malloc(sizeof(struct Node));
    if (NULL == p_new_node) {
        return NULL;
    }
    //初始化新结点
    p_new_node->data = data;
    p_new_node->p_next = NULL;
    return p_new_node;
}

//遍历链表
void PrintList(struct Node* p_head_node) {
    //定义移动指针,因为头结点不存储数据,所以直接指向头结点的下一个结点
    struct Node* p_move = p_head_node->p_next;
    printf("姓名\t年龄\t编号\n");
    while (NULL != p_move) {
        printf("%s\t%d\t%d\n", p_move->data.name, p_move->data.age,
               p_move->data.num);
        p_move = p_move->p_next;
    }
    putchar('\n');
}

//表头法插入
void InsertNewNodeByHead(struct Node* p_head_node, struct MM data) {
    //调用生成新结点函数
    struct Node* p_new_node = CreateNewNode(data);
    //表头法插入
    p_new_node->p_next = p_head_node->p_next;
    p_head_node->p_next = p_new_node;
}

//通过data删除指定位置结点
void DeleteByName(struct Node* p_head_node, const char* p_mm_name) {
    struct Node* p_pre_node = p_head_node;
    struct Node* p_cur_node = p_head_node->p_next;
    if (NULL == p_head_node || NULL == p_cur_node) {
        printf("链表为空,无法删除\n");
        return;
    }
    // while (NULL != p_cur_node && p_cur_node->data != data_value) {
    //     p_pre_node = p_cur_node;
    //     p_cur_node = p_pre_node->p_next;
    // }
    //相同返回0,
    while (NULL != p_cur_node && strcmp(p_cur_node->data.name, p_mm_name)) {
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
struct Node* SearchNode(struct Node* p_head_node, const char* p_mm_name) {
    struct Node* p_move = p_head_node->p_next;
    // while (NULL != p_move && p_move->data != data_value) {
    //     p_move = p_move->p_next;
    // }
    while (NULL != p_move && strcmp(p_move->data.name, p_mm_name)) {
        p_move = p_move->p_next;
    }
    return p_move;
}

void Menu() {
    printf("-----------【MM管理系统】-------------\n");
    printf("\t\t0.退出功能\n");
    printf("\t\t1.录入信息\n");
    printf("\t\t2.浏览信息\n");
    printf("\t\t3.查找信息\n");
    printf("\t\t4.修改信息\n");
    printf("\t\t5.删除信息\n");
    printf("\t\t6.排序显示\n");
    printf("-------------------------------------\n");
    printf("请输入(0-6):");
}

//录入美女信息
void InsertMMData(struct Node* p_head_node) {
    struct MM mm;
    printf("输入美女信息:");
    scanf("%s%d%d", mm.name, &mm.age, &mm.num);
    InsertNewNodeByHead(p_head_node, mm);
}

void SearchMMData(struct Node* p_head_node) {
    char mm_name[20];
    printf("请输入查找美女的姓名:");
    scanf("%s", mm_name);
    struct Node* p_result = SearchNode(p_head_node, mm_name);
    if (NULL == p_result) {
        printf("未找到指定位置\n");
    } else {
        printf("姓名\t年龄\t编号\n");
        printf("%s\t%d\t%d\n", p_result->data.name, p_result->data.age,
               p_result->data.num);
    }
}

void ModifyMMData(struct Node* p_head_node) {
    char mm_name[20];
    printf("请输入修改美女的姓名:");
    scanf("%s", mm_name);
    struct Node* p_result = SearchNode(p_head_node, mm_name);
    if (NULL == p_result) {
        printf("未找到指定位置\n");
    } else {
        printf("重新输入美女的信息:");
        scanf("%s%d%d", p_result->data.name, &p_result->data.age,
              &p_result->data.num);
        printf("修改成功\n");
    }
}

void DeleteMMData(struct Node* p_head_node) {
    char mm_name[20];
    printf("请输入删除美女的姓名:");
    scanf("%s", mm_name);
    DeleteByName(p_head_node, mm_name);
}

void BubbleSort(struct Node* p_head_node) {
    for (struct Node* p = p_head_node->p_next; p != NULL; p = p->p_next) {
        for (struct Node* q = p_head_node->p_next; q != NULL; q = q->p_next) {
            //按照年龄方式升序
            if (q->p_next != NULL && q->data.age > q->p_next->data.age) {
                struct MM tmp = q->data;
                q->data = q->p_next->data;
                q->p_next->data = tmp;
            }
        }
    }
    PrintList(p_head_node);
}

void KeyDown(struct Node* p_list) {
    struct MM mm;
    int options = 0;
    scanf("%d", &options);
    switch (options) {
        case 0:
            printf("----退出----\n");
            exit(0);
            break;
        case 1:
            printf("----录入----\n");
            InsertMMData(p_list);
            break;
        case 2:
            printf("----浏览----\n");
            PrintList(p_list);
            break;
        case 3:
            printf("----查找----\n");
            SearchMMData(p_list);
            break;
        case 4:
            printf("----修改----\n");
            ModifyMMData(p_list);
            break;
        case 5:
            printf("----删除----\n");
            DeleteMMData(p_list);
            break;
        case 6:
            printf("-----排序----\n");
            BubbleSort(p_list);
            break;
        default:
            printf("----error----\n");
            break;
    }
}