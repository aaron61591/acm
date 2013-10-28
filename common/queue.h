/*************************************************************************
    > File Name: queue.h
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年10月19日 星期六 15时23分41秒
 ************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct Node {
    Node<T>* next;
    T data;
};

template <typename T>
class Queue {

    public:
        Queue();
        void push(T);
        T remove();
        size_t size();
        bool empty();
    private:
        Node<T>* head;
        Node<T>* tail;
};


template <typename T>
Queue<T>::Queue() {

    Node<T>* p = new Node<T>;
    p->next = NULL;
    this->head = p;
    this->tail = p;
}

template <typename T>
void Queue<T>::push(T node) {

    Node<T>* p = new Node<T>;
    p->data = node;
    p->next = NULL;
    this->tail->next = p;
    this->tail = p;
}

template <typename T>
T Queue<T>::remove() {

    if (this->head == this->tail) {
        throw runtime_error("This is a empty queue!");
    } else {
        Node<T>* p = this->head->next;
        this->head->next = p->next;
        T e = p->data;
        if (this->tail == p)
            this->tail = this->head;
        delete p;
        return e;
    }
}

template <typename T>
size_t Queue<T>::size() {

    int count(0);
    Node<T>* p = this->head;
    while (p != this->tail) {
        p = p->next;
        ++count;
    }
    return count;
}

#endif /* QUEUE_H */
