//
// Created by eyal on 4/24/2019.
//
#ifndef HW1_AVLNODE_H
#define HW1_AVLNODE_H
#include <iostream>
#include "assert.h"
#define VOID_HEIGHT -1

template<typename T>
class AvlNode {
public:
    //c'tors & d'tor
    AvlNode() = default;
    AvlNode(int key1,int key2, int key3, T* data);
    ~AvlNode();
    AvlNode(const AvlNode<T>& copy);

    //helper functions:
    AvlNode<T>* GetLeftSon();
    AvlNode<T>* GetRightSon();
    AvlNode<T>* GetParentNode();
    int GetHeight();
    int GetBalanceFactor();
    int GetKey1();
    int GetKey2();
    int GetKey3();
    int getRank();
    int getSum();
    T* GetData();
    void SetData(T *new_data);
    void SetLeftSon(AvlNode<T>*);
    void SetRightSon(AvlNode<T> *);
    void SetParentNode(AvlNode<T>*);
    void UpdateHeight();
    void UpdateRankAndSum();
    void IncrementHeight();
    bool IsLeaf();
    bool OnlyOneChild();
    void SwapNodeInfo(AvlNode<T>*);
    void InorderAux();

private:
    //properties:
    int key1;
    int key2;
    int key3;
    int height;
    int rank;
    int sum;
    AvlNode<T>* leftNode;
    AvlNode<T>* rightNode;
    AvlNode<T>* parent;
    T* data;
};

template <typename T>
AvlNode<T>::AvlNode(int key1,int key2, int key3, T* data) : key1(key1), key2
(key2), key3(key3), height(0), rank(0), sum(key1), leftNode(NULL),
rightNode(NULL), parent(NULL),data(data) {}

template <typename T>
AvlNode<T>::AvlNode(const AvlNode<T>& copy): key1(copy.key1), key2(copy.key2)
, key3(copy.key3), height(0), rank(0), sum(copy.sum), leftNode(NULL), rightNode
(NULL), parent(NULL), data(NULL){ data = new T(*copy.data);
}

template <typename T>
int AvlNode<T>::GetKey1(){
    return key1;
}

template <typename T>
int AvlNode<T>::GetKey2(){
    return key2;
}

template <typename T>
int AvlNode<T>::GetKey3(){
    return key3;
}

template <typename T>
int AvlNode<T>::GetHeight(){
    return height;
}

template <typename T>
int AvlNode<T>::GetBalanceFactor(){
    int left = GetLeftSon() ? GetLeftSon()->GetHeight() : VOID_HEIGHT;
    int right = GetRightSon() ? GetRightSon()->GetHeight() : VOID_HEIGHT;

    return left - right;
}

template <typename T>
AvlNode<T>*  AvlNode<T>::GetLeftSon() {
    return leftNode;
}

template <typename T>
AvlNode<T>*  AvlNode<T>::GetRightSon() {
    return rightNode;
}

template <typename T>
AvlNode<T>*  AvlNode<T>::GetParentNode() {
    return parent;
}

template <typename T>
void AvlNode<T>::SetLeftSon(AvlNode<T> *node) {
    leftNode = node;
}

template <typename T>
void AvlNode<T>::SetRightSon(AvlNode<T> *node) {
    rightNode = node;
}

template <typename T>
void AvlNode<T>::SetParentNode(AvlNode<T>* node) {
    parent = node;
}

template <typename T>
void AvlNode<T>::IncrementHeight() {
    height++;
}

static int MaxHeight(int h_left,int h_right){
    if (h_left>h_right) return h_left;
    return h_right;
}

template <typename T>
void AvlNode<T>::UpdateHeight(){
    int leftChild = GetLeftSon() ? GetLeftSon()->GetHeight() : VOID_HEIGHT;
    int rightChild = GetRightSon() ? GetRightSon()->GetHeight() : VOID_HEIGHT;

    height = 1 + MaxHeight(leftChild, rightChild);
}

template <typename T>
bool AvlNode<T>::IsLeaf(){
    return (!leftNode && !rightNode);
}

template <typename T>
bool AvlNode<T>::OnlyOneChild(){
    return (leftNode&&!rightNode)||(!leftNode&&rightNode);
}

template <typename T>
void AvlNode<T>::SwapNodeInfo(AvlNode<T>* node){
    T* temp=node->data;
    node->data=data;
    data=temp;
    int temp_height=node->height;
    node->height=height;
    height=temp_height;
    //swap keys
    int temp_key1=node->key1;
    node->key1=key1;
    key1=temp_key1;
    int temp_key2=node->key2;
    node->key2=key2;
    key2=temp_key2;
    int temp_key3=node->key3;
    node->key3=key3;
    key3=temp_key3;
}

template <typename T>
void AvlNode<T>::InorderAux(){
    if (!this) return;

    this->GetLeftSon()->InorderAux();
    std::cout<<"key1: " << key1 << " ,key2: "<< key2 << " ,key3: "<< key3
    <<" ,height: "<< height <<", rank:" << rank
    << ", sum:" << sum << std::endl;
    this->GetRightSon()->InorderAux();
}

template <typename T>
T* AvlNode<T>::GetData(){
    return data;
}

template <typename T>
void AvlNode<T>::SetData(T *new_data) {
    data = new_data;
}

template <typename T>
AvlNode<T>::~AvlNode(){

    if(leftNode) {
        delete leftNode;
    }
    if(rightNode) {
        delete rightNode;
    }
    delete data;
}

template <typename T>
int AvlNode<T>::getRank() {
    return rank;
}

template <typename T>
int AvlNode<T>::getSum() {
    return sum;
}

template <typename T>
void AvlNode<T>::UpdateRankAndSum(){
    int rightRank = rightNode ? rightNode->rank : 0;
    int leftRank  = leftNode ? leftNode->rank : 0;
    rank = rightRank + leftRank + 1;

    int rightSum = rightNode ? rightNode->sum : 0;
    int leftSum  = leftNode ? leftNode->sum : 0;
    sum = key1 + rightSum + leftSum;

}

#endif //HW1_AVLNODE_H
