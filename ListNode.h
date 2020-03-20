//
// Created by eyall on 5/5/2019.
//

#ifndef HW1_NODE_H
#define HW1_NODE_H

#include <iostream>

template<typename T>
class ListNode{
public:
    //c'tor & d'tor
    explicit ListNode(T*);
    ~ListNode();

    //helper functions:
    void setPrevious(ListNode<T>*);
    void setNext(ListNode<T>*);
    ListNode<T>* getNext();
    ListNode* getPrevious();
    T* getVal();
    void setValue(T *new_val);

private:
    //properties:
    T* val;
    ListNode<T>* next;
    ListNode<T>* previous;
};

template<typename T>
ListNode<T>::ListNode(T* val) : val(val), next(NULL), previous(NULL){}

template<typename T>
void ListNode<T>::setNext(ListNode<T> *next_node)  {
    if (!next_node) {
        next=NULL;
        return;
    }
    next=next_node;
}

template<typename T>
void ListNode<T>::setPrevious(ListNode<T> *previous_node) {
    if (!previous_node){
        previous=NULL;
        return;
    }
    previous=previous_node;
}

template<typename T>
ListNode<T>* ListNode<T>::getNext() {
    return next;
}

template<typename T>
ListNode<T>* ListNode<T>::getPrevious() {
    return previous;
}

template<typename T>
T* ListNode<T>::getVal() {
    return val;
}

template<typename T>
void ListNode<T>::setValue(T *new_val) {
    val = new_val;
}

template<typename T>
ListNode<T>::~ListNode() {
    delete val;
}

#endif //HW1_NODE_H
