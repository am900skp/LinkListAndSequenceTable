#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2

struct MM {
    char name[20];
    int age;
};

struct Data {
    int index;  //序号
    struct MM mm_data;
};

//顺序表的结构体
typedef struct SqList {
    int sqlist_size;  //顺序表中元素个数
    struct Data* p_memory;
} SQLIST, *LPSQLIST;

//创建顺序表
LPSQLIST CreateSqList() {
    LPSQLIST p_sqlist = (LPSQLIST)malloc(sizeof(SQLIST));
    if (NULL == p_sqlist) {
        return NULL;
    }
    p_sqlist->sqlist_size = 0;
    p_sqlist->p_memory = (struct Data*)malloc(sizeof(struct Data) * MAX);
    return p_sqlist;
}

//开辟更多内存
void ReallocMemory(LPSQLIST p_sqlist, int cur_size, int new_size) {
    printf("开辟更多内存\n");
    int max_size = cur_size > new_size ? cur_size : new_size;
    p_sqlist->p_memory = (struct Data*)realloc(p_sqlist->p_memory,
                                               sizeof(struct Data) * max_size);
}

//插入顺序表
void InsertData(LPSQLIST p_sqlist, struct Data new_data) {
    //元素个数已满,内存重新申请为当前大小的两倍
    if (MAX == p_sqlist->sqlist_size) {
        ReallocMemory(p_sqlist, MAX, 2 * MAX);
    }
    //直接插在表尾
    p_sqlist->p_memory[p_sqlist->sqlist_size] = new_data;
    //调整位置
    //后面的和前面的相比
    for (int i = p_sqlist->sqlist_size; i >= 0; --i) {
        if (p_sqlist->p_memory[i - 1].index > p_sqlist->p_memory[i].index) {
            struct Data tmp = p_sqlist->p_memory[i - 1];
            p_sqlist->p_memory[i - 1] = p_sqlist->p_memory[i];
            p_sqlist->p_memory[i] = tmp;
        } else {
            break;
        }
    }
    //元素个数+1
    p_sqlist->sqlist_size++;
}
//删除顺序表
//因为顺序表本身就有顺序,所以只需挪位置即可,移动元素
void DeleteData(LPSQLIST p_sqlist, int del_index) {
    //找到删除元素的下标
    int del_pos = -1;
    for (int i = 0; i < p_sqlist->sqlist_size; ++i) {
        if (p_sqlist->p_memory[i].index == del_index) {
            del_pos = i;
            break;
        }
    }
    //调整数组
    if (del_pos == -1) {
        printf("未找到指定元素");
        return;
    } else {
        //数组后面的元素往前移动
        for (int i = del_pos; i < p_sqlist->sqlist_size; ++i) {
            p_sqlist->p_memory[i] = p_sqlist->p_memory[i + 1];
        }
        //元素个数-1
        p_sqlist->sqlist_size--;
    }
}
//遍历顺序表
void PrintSqList(LPSQLIST p_sqlist) {
    for (int i = 0; i < p_sqlist->sqlist_size; ++i) {
        printf("序号:%d\t名字:%s\t年龄:%d\n", p_sqlist->p_memory[i].index,
               p_sqlist->p_memory[i].mm_data.name,
               p_sqlist->p_memory[i].mm_data.age);
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    LPSQLIST p_sqlist = CreateSqList();
    struct Data array[4] = {3, "小红", 18, 1, "小明",  14,
                            0, "雨墨", 18, 2, "小asd", 4};
    for (int i = 0; i < 4; ++i) {
        InsertData(p_sqlist, array[i]);
    }
    PrintSqList(p_sqlist);
    printf("测试删除序号1:\n");
    DeleteData(p_sqlist, 1);
    PrintSqList(p_sqlist);
    //删除顺序表
    free(p_sqlist);
    return 0;
}