/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月11日21:40:13
    @brief:    类模板封装单链表,C++风格
    @message:  代码的上一行为所写注释
*/

#include <iostream>
#include <string>
using namespace std;

template <class T>
class MyList {
   private:
    struct Node {
        T data;
        Node* p_next;  //指向下一个结点
        Node* p_prev;  //指向前一个结点
        Node() {}
        Node(const T& data) {
            this->data = data;
            p_prev = p_next = nullptr;
        }
    };
    Node* p_head;
    Node* p_tail;

   public:
    MyList() { p_tail = p_head = NULL; }
    void AppendNode(const T& new_data);
    void Traver();

   private:
    Node* _FindPos(int pos);
};

template <class T>
void MyList<T>::AppendNode(const T& new_data) {
    // 1 创建新结点
    Node* p_new = new Node(new_data);
    if (p_tail) {  //不是空链表
        //新结点连接到尾结点后
        p_tail->p_next = p_new;
        p_new->p_prev = p_tail;
        //更新p_tail
        p_tail = p_new;
        //维持循环双链表结构
        p_tail->p_next = p_head;
        p_head->p_prev = p_tail;
    } else {  //空链表
        p_head = p_tail = p_new;
    }
}

template <class T>
void MyList<T>::Traver() {
    Node* p_tmp = p_head;
    cout << "list:";
    if (p_head == NULL) {
        cout << "链表为空" << endl;
        return;
    }
    if (p_head == p_tail) {
        cout << p_head->data << endl;
        return;
    }
    while (p_tmp != p_tail) {
        cout << p_tmp->data << " ";
        p_tmp = p_tmp->p_next;
    }

    cout << p_tail->data << endl;
}

int main(int argc, char** argv) {
    MyList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.AppendNode(i);
        list.Traver();
    }
    return 0;
}

