/*
    @author:   KaiPeng_Sun
    @Time:     2022年7月12日21:40:13
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
        Node* p_next;
        Node() {}
        Node(const T& data) {
            this->data = data;
            p_next = nullptr;
        }
    };
    Node* p_head;

   public:
    MyList() { p_head = NULL; }
    void AppendNode(const T& new_data);      //尾插
    void AddNode(const T& new_data);         //头插
    void InsertNode(int pos, int new_data);  //中间插
    void Traver();                           //遍历
    void DeletePosNode(int pos);             //删除特定结点
    void DeleteHeadNode();                   //删除头结点

   private:
    Node* _FindPos(int pos);
};

template <class T>
void MyList<T>::AppendNode(const T& new_data) {
    Node* p_new = new Node(new_data);
    Node* p_tmp = p_head;
    if (p_tmp) {
        while (p_tmp->p_next) {
            p_tmp = p_tmp->p_next;
        }
        p_tmp->p_next = p_new;
    } else {
        p_head = p_new;
    }
}

template <class T>
void MyList<T>::AddNode(const T& new_data) {
    Node* p_new = new Node(new_data);
    p_new->p_next = p_head;
    p_head = p_new;
}

template <class T>
void MyList<T>::InsertNode(int pos, int new_data) {
    if (pos < 0) {
        return;
    }
    if (nullptr == p_head || 0 == pos) {
        AddNode(new_data);
    }
    Node* p_new = new Node(new_data);
    Node* p_prev = _FindPos(pos);
    p_new->p_next = p_prev->p_next;
    p_prev->p_next = p_new;
}

template <class T>
void MyList<T>::Traver() {
    Node* p_tmp = p_head;
    cout << "list: ";
    while (p_tmp) {
        cout << p_tmp->data << "  ";
        p_tmp = p_tmp->p_next;
    }
    cout << '\n';
}

template <class T>
void MyList<T>::DeletePosNode(int pos) {
    if (nullptr == p_head || pos < 0) {
        return;
    }
    if (0 == pos) {
        DeleteHeadNode();
        return;
    }
    Node* p_del_prev = _FindPos(pos - 1);
    if (nullptr == p_del_prev) {
        return;
    }
    Node* p_del = _FindPos(pos);
    if (nullptr == p_del) {
        return;
    }
    p_del_prev->p_next = p_del->p_next;
    delete p_del;
}

template <class T>
void MyList<T>::DeleteHeadNode() {
    if (nullptr == p_head) {
        return;
    }
    Node* p_del = p_head;
    p_head = p_del->p_next;
    delete p_del;
}

template <class T>
typename MyList<T>::Node* MyList<T>::_FindPos(int pos) {
    Node* p_pos = p_head;
    for (int i = 0; i < pos; ++i) {
        if (nullptr == p_pos) {
            return nullptr;
        } else {
            p_pos = p_pos->p_next;
        }
    }
    return p_pos;
}

int main(int argc, char** argv) {
    MyList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.AppendNode(i);
        list.Traver();
    }
    list.InsertNode(5, 666);
    list.Traver();

    list.DeleteHeadNode();
    list.Traver();

    list.DeletePosNode(5);
    list.Traver();
    
    return 0;
}