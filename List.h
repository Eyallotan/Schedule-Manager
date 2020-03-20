//
// Created by eyall on 5/4/2019.
//

#ifndef HW1_LIST_H
#define HW1_LIST_H

#include <iostream>
#include "ListNode.h"


template<typename T>
class List{
public:
    //c'tor & d'tor
    List();
    ~List();

    //create and insert ListNode at start of list
    ListNode<T>* insertNode(T* val);
    //delete ListNode pointed to by to_delete
    void deleteNode(ListNode<T>* to_delete);
    int getLength();
    ListNode<T>* getHead();

private:
    //properties:
    ListNode<T> *head, *tail;
};

template<typename T>
List<T>::List(): head(NULL), tail(NULL) {}


template<typename T>
ListNode<T>* List<T>::insertNode(T* val) {
    ListNode<T>* node_new= new ListNode<T>(val);
    if (!head){
        head=node_new;
        tail=node_new;
    }
    else{
        tail->setNext(node_new);
        node_new->setPrevious(tail);
        tail=node_new;
    }
    return node_new;
}

template<typename T>
List<T>::~List() {
    ListNode<T>* iterator = head;
    if (!head){
        return;
    }
    while (iterator){
        ListNode<T>* temp = iterator;
        iterator=iterator->getNext();
        deleteNode(temp);
    }
    head=NULL;
    tail=NULL;
}

template<typename T>
void List<T>::deleteNode(ListNode<T>* to_delete) {
    if(to_delete==head){
        head=to_delete->getNext();
        if (!head) {
            tail = NULL;
            delete to_delete;
            return;
        }
        head->setPrevious(NULL);
    }
    else if (to_delete==tail){
        tail=to_delete->getPrevious();
        tail->setNext(NULL);
    }
    else {
        to_delete->getPrevious()->setNext(to_delete->getNext());
        to_delete->getNext()->setPrevious(to_delete->getPrevious());
    }
    delete to_delete;
}

template<typename T>
int List<T>::getLength() {
    if (!head){
        return 0;
    }
    int length=0;
    ListNode<T>* iterator=head;
    while (iterator){
        length++;
        iterator=iterator->getNext();
    }
    return length;
}

template<typename T>
ListNode<T>* List<T>::getHead() {
    return head;
}
#endif //HW1_LIST_H
