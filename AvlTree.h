//
// Created by eyal on 4/24/2019.
//

#ifndef HW1_AVLTREE_H
#define HW1_AVLTREE_H

#include "assert.h"
#include "AvlNode.h"
#define BF_RANGE_POS 2
#define BF_RANGE_NEG -2


enum AVL_STATUS{
    AVL_SUCCESS, AVL_FAILURE, AVL_MEMORY_ERROR, AVL_ALREADY_EXISTS
};

template<typename T>
class AvlTree {
public:
    //c'tor & d'tor
    AvlTree();
    AvlTree(AvlNode<T>** arr, int elements_count);
    ~AvlTree();

    //Dictionary functions
    AVL_STATUS InsertElement(int key1, int key2, int key3, T* element);
    AVL_STATUS RemoveElement(int key1, int key2, int key3);
    T* FindElement(int key1, int key2, int key3);

    //helper functions
    bool isTreeEmpty();
    AvlNode<T>* getRoot();
    void InorderPrint();
    AvlNode<T>** GetTreeNodesInorder();
    void updateParentsPreOrder(AvlNode<T>*);
    T** GetTreeElements();
    int getElementCount();
    int getRootSum();
    // return sum of highest count nodes in the tree
    int getSumofHighestNodes(int count);

private:

    //helper functions
    AvlNode<T>* FindNode(int key1, int key2, int key3);
    AvlNode<T>* CreateTreeFromArrayAux(AvlNode<T> **arr,
                                       int start, int arr_end);
    void GetTreeNodesAux(int *i, AvlNode<T>** array, AvlNode<T>*node);
    AvlNode<T>* SecondaryKeySort(int key2, int key3, AvlNode<T>* iterator);
    AvlNode<T>* ThirdKeySort(int key3, AvlNode<T>* iterator);

    //roll functions
    void ExecuteRoll(AvlNode<T>*);
    void RollRight(AvlNode<T>*);
    void RollLeft(AvlNode <T>*);

    //Insert element functions
    AvlNode<T>* FindNodeInternal(int key1, int key2, int key3);
    void HandleParentRoll(AvlNode<T>*, AvlNode<T>*);
    void ExecuteRouteBalance(AvlNode<T>*);
    void FixRouteRankAndSum(AvlNode<T> *newNode);
    void FindAndPlaceSon(int key1, int key2, int key3, AvlNode<T>* parent ,
            AvlNode<T>* son);


    //Remove element functions
    void RemoveNodeAux(AvlNode<T>*);
    bool IsBasicNodeRemovalCase(AvlNode<T> *);
    void UpdateRoute(AvlNode<T>*);
    AvlNode<T>* FindNextInorderNode(AvlNode<T>*);
    void ParentFindAndSetSon(AvlNode<T>* parent,AvlNode<T>* son,
            AvlNode<T>* updated_son);
    void RemoveNodeFromTree(AvlNode<T>*);

    //functions not in use
    void GetTreeElementsAux(int *i, T** array, AvlNode<T> *node);

//Properties:
    AvlNode<T>* root;
    int elements_count;
};

template<typename T>
AvlTree<T>::AvlTree() : root(NULL), elements_count(0) {}

template<typename T>
AvlTree<T>::AvlTree(AvlNode<T>** arr, int elements_count) : root
(NULL), elements_count(elements_count) {
        root = CreateTreeFromArrayAux(arr, 0, elements_count -1);
}

//Insert element
template<typename T>
AVL_STATUS AvlTree<T>::InsertElement(int key1, int key2, int key3, T* element){
    AvlNode<T>* isExists = FindNode(key1,key2,key3);
    if(isExists) {
        return AVL_FAILURE;
    }
    AvlNode<T>* newNode = new AvlNode<T>(key1,key2,key3, element);
    elements_count++;
    if(!root) {
        root = newNode;
        return AVL_SUCCESS;
    }
    AvlNode<T>* parent = FindNodeInternal(key1,key2,key3);
    newNode->SetParentNode(parent);
    //find where is the son and place him in place
    FindAndPlaceSon(key1,key2,key3,parent,newNode);
    //fix rank
    FixRouteRankAndSum(newNode);
    ExecuteRouteBalance(newNode);

    return AVL_SUCCESS;
}

template<typename T>
void AvlTree<T>::FindAndPlaceSon(int key1, int key2, int key3,
                                 AvlNode<T> *parent, AvlNode<T>* son) {
    if(key1> parent->GetKey1()) {
        parent->SetRightSon(son);
    }
    if (key1 < parent->GetKey1()) {
        parent->SetLeftSon(son);
    }
    if (key1==parent->GetKey1()){
        if(key2> parent->GetKey2()) {
            parent->SetRightSon(son);
        }
        if (key2 < parent->GetKey2()) {
            parent->SetLeftSon(son);
        }
        if (key2==parent->GetKey2()){
            if(key3> parent->GetKey3()) {
                parent->SetRightSon(son);
            }
            if (key3 < parent->GetKey3()) {
                parent->SetLeftSon(son);
            }
        }
    }
}

template<typename T>
void AvlTree<T>::FixRouteRankAndSum(AvlNode<T> *newNode) {
    AvlNode<T>* iterator = newNode;
    while(iterator) {
        iterator->UpdateRankAndSum();

        iterator = iterator->GetParentNode();
    }
}

template<typename T>
void AvlTree<T>::ExecuteRouteBalance(AvlNode<T> *newNode) {
    AvlNode<T>* iterator = newNode;
    while(iterator != root) {
        AvlNode<T>* parent = iterator->GetParentNode();
        if(parent->GetHeight() >= iterator->GetHeight() + 1) {
            return;
        }
        parent->IncrementHeight();
        if(parent->GetBalanceFactor() >1 || parent->GetBalanceFactor()  < -1) {
            ExecuteRoll(parent);
            return;
        }
        iterator=parent;
    }

}
template<typename T>
void AvlTree<T>::ExecuteRoll(AvlNode<T>* node) {
    //LL
    if(node->GetBalanceFactor() == BF_RANGE_POS &&
            node->GetLeftSon()->GetBalanceFactor () >= 0) {
        RollRight(node->GetLeftSon());
        node->UpdateRankAndSum();
        node->GetParentNode()->UpdateRankAndSum();
        return;
    }
    //RR
    if(node->GetBalanceFactor() == BF_RANGE_NEG &&
            node->GetRightSon()->GetBalanceFactor() <= 0) {
        RollLeft(node->GetRightSon());
        node->UpdateRankAndSum();
        node->GetParentNode()->UpdateRankAndSum();
        return;
    }

    //LR
    if(node->GetBalanceFactor() == BF_RANGE_POS &&
            node->GetLeftSon()->GetBalanceFactor() == -1) {
        RollLeft(node->GetLeftSon()->GetRightSon());
        RollRight(node->GetLeftSon());
        node->UpdateRankAndSum();
        node->GetParentNode()->GetLeftSon()->UpdateRankAndSum();
        node->GetParentNode()->UpdateRankAndSum();
        return;
    }

    //RL
    if(node->GetBalanceFactor() == BF_RANGE_NEG &&
            node->GetRightSon()->GetBalanceFactor() == 1) {
        RollRight(node->GetRightSon()->GetLeftSon());
        RollLeft(node->GetRightSon());
        node->UpdateRankAndSum();
        node->GetParentNode()->GetRightSon()->UpdateRankAndSum();
        node->GetParentNode()->UpdateRankAndSum();
        return;
    }
}


template<typename T>
AvlNode<T>* AvlTree<T>::FindNodeInternal(int key1, int key2, int key3) {
    AvlNode<T>* iterator = root;
    if(!iterator) {
        return NULL;
    }
    while(iterator->GetKey1() != key1 || iterator->GetKey2() != key2 ||
    iterator->GetKey3() != key3)  {
        int currentKey1 = iterator->GetKey1();
        if(key1 > currentKey1) {
            if(!iterator->GetRightSon()) {
                return iterator;
            }
            iterator = iterator->GetRightSon();
        } else if (key1 < currentKey1) {
            if(!iterator->GetLeftSon()) {
                return iterator;
            }
            iterator = iterator->GetLeftSon();
        }
        if (key1==currentKey1){
            AvlNode<T>* res=SecondaryKeySort(key2,key3,iterator);
            if (!res){
                return iterator;
            }
            iterator=res;
        }
    }
    return iterator;
}

template<typename T>
AvlNode<T>* AvlTree<T>::SecondaryKeySort(int key2, int key3, AvlNode<T>
        *iterator) {
    int currentKey2 = iterator->GetKey2();
    if(key2 > currentKey2) {
        if(!iterator->GetRightSon()) {
            return NULL;
        }
        iterator = iterator->GetRightSon();
    } else if (key2 < currentKey2) {
        if(!iterator->GetLeftSon()) {
            return NULL;
        }
        iterator = iterator->GetLeftSon();
    }
    if (key2==currentKey2){
        iterator= ThirdKeySort(key3,iterator);
    }
    return iterator;
}

template<typename T>
AvlNode<T>* AvlTree<T>::ThirdKeySort(int key3, AvlNode<T> *iterator) {
    int currentKey3 = iterator->GetKey3();
    if(key3 > currentKey3) {
        if(!iterator->GetRightSon()) {
            return NULL;
        }
        iterator = iterator->GetRightSon();
    } else if (key3 < currentKey3) {
        if(!iterator->GetLeftSon()) {
            return NULL;
        }
        iterator = iterator->GetLeftSon();
    }
    return iterator;
}


template<typename T>
AvlNode<T>* AvlTree<T>::FindNode(int key1, int key2, int key3) {
    if(!root) {
        return NULL;
    }
    AvlNode<T>* node = FindNodeInternal(key1,key2,key3);
    if(node->GetKey1() == key1 && node->GetKey2()== key2 && node->GetKey3()
    == key3) {
        return node;
    }
    return NULL;
}

template <typename T>
void AvlTree<T>::RollRight(AvlNode<T>* node) {
    AvlNode<T> *right = node->GetRightSon();
    AvlNode<T> *oldParent = node->GetParentNode();

    HandleParentRoll(oldParent, node);
    node->SetRightSon(oldParent);
    oldParent->SetLeftSon(right);
    if(right) {
       right->SetParentNode(oldParent);
    }

    oldParent->UpdateHeight();
    node->UpdateHeight();
}

template <typename T>
void AvlTree<T>::RollLeft(AvlNode<T>* node) {
    AvlNode<T>* left= node->GetLeftSon();
    AvlNode<T> *oldParent=node->GetParentNode();

    HandleParentRoll(oldParent,node);
    node->SetLeftSon(oldParent);
    oldParent->SetRightSon(left);
    if(left) {
        left->SetParentNode(oldParent);
    }

    oldParent->UpdateHeight();
    node->UpdateHeight();
}

template <typename T>
void AvlTree<T>::HandleParentRoll(AvlNode<T>* oldParent, AvlNode<T>* newParent) {
    AvlNode<T>* grandParent = oldParent->GetParentNode();
    newParent->SetParentNode(grandParent);
    oldParent->SetParentNode(newParent);

    if(!grandParent) {
        root = newParent;
        return;
    }

    if (grandParent->GetRightSon() == oldParent) {
        grandParent->SetRightSon(newParent);
    } else {
        grandParent->SetLeftSon(newParent);
    }
}

///remove element functions///
template <typename T>
AVL_STATUS AvlTree<T>::RemoveElement(int key1, int key2, int key3){
    AvlNode<T>* to_remove=FindNode(key1,key2,key3);
    if(!to_remove){
        return AVL_FAILURE;
    }
    RemoveNodeAux(to_remove);
    elements_count--;
    return AVL_SUCCESS;
}

template <typename T>
void AvlTree<T>::RemoveNodeAux(AvlNode<T>* to_remove){
    AvlNode<T>* parent=to_remove->GetParentNode();
    //node is leaf or had one son
    if (IsBasicNodeRemovalCase(to_remove)){
        RemoveNodeFromTree(to_remove);
        FixRouteRankAndSum(parent);
        UpdateRoute(parent);
        return;
    }
    //node has both sons
    AvlNode<T>* next_inorder_node=FindNextInorderNode(to_remove);
    parent=next_inorder_node->GetParentNode();
    next_inorder_node->SwapNodeInfo(to_remove);
    IsBasicNodeRemovalCase(next_inorder_node);//send next_inorder because
    // of swap
    RemoveNodeFromTree(next_inorder_node);
    FixRouteRankAndSum(parent);
    UpdateRoute(parent); //update regarding the new location
}

template <typename T>
bool AvlTree<T>::IsBasicNodeRemovalCase(AvlNode<T> *to_remove){
    AvlNode<T>* parent=to_remove->GetParentNode();
    bool made_remove=false;
    if (to_remove->IsLeaf()){ //remove leaf
        if(!parent) {
            root = NULL;
        }
        else{
            ParentFindAndSetSon(parent,to_remove,NULL);
        }
        made_remove=true;
    }
    if (to_remove->OnlyOneChild()){ //only one child
        if (to_remove->GetRightSon()){
            ParentFindAndSetSon(parent,to_remove,
                                to_remove->GetRightSon());
        }
        else {
            ParentFindAndSetSon(parent,to_remove,
                                to_remove->GetLeftSon());
        }
        made_remove= true;
    }
    return made_remove;
}

template <typename T>
void AvlTree<T>::UpdateRoute(AvlNode<T>* node){
    if(!node) return;
    AvlNode<T>* iterator=node;
    while (iterator){
        iterator->UpdateHeight();
        if(iterator->GetBalanceFactor()== BF_RANGE_POS || iterator->GetBalanceFactor()
                                                          == BF_RANGE_NEG){
            ExecuteRoll(iterator);
        }
        iterator=iterator->GetParentNode();
    }
}

template <typename T>
AvlNode<T>* AvlTree<T>::FindNextInorderNode(AvlNode<T>* node){
    if(!node) return NULL;
    AvlNode<T>* next_inorder_node= node->GetRightSon();
    AvlNode<T>* iterator= node->GetRightSon()->GetLeftSon();
    while(iterator){
        next_inorder_node=iterator;
        iterator= iterator->GetLeftSon();
    }
    return next_inorder_node;
}

template <typename T>
void AvlTree<T>::ParentFindAndSetSon(AvlNode<T>* parent,AvlNode<T>* son,AvlNode<T>*
        updated_son){
    if (!parent){
        root=updated_son;
        updated_son->SetParentNode(NULL);
        return;
    }
    if(parent->GetRightSon()==son){
        parent->SetRightSon(updated_son);
    }
    if (parent->GetLeftSon()==son){
        parent->SetLeftSon(updated_son);
    }
    if(updated_son) {
        updated_son->SetParentNode(parent);
    }
}

//Print Tree Key's with Inorder scan
template <typename T>
void AvlTree<T>::InorderPrint(){
    std::cout<<"Inorder print:"<<std::endl;
    root->InorderAux();
    std::cout<<"end"<<std::endl;

}


template <typename T>
void AvlTree<T>::RemoveNodeFromTree(AvlNode<T>* node){
    node->SetLeftSon(NULL);
    node->SetRightSon(NULL);
    delete node;
}


//Find element
template <typename T>
T* AvlTree<T>::FindElement(int key1,int key2, int key3){
    AvlNode<T>* node=FindNode(key1,key2,key3);
    if (!node) return NULL;
    return node->GetData();
}

template <typename T>
AvlTree<T>::~AvlTree(){
    if(!root) return;
    delete root;
}

template <typename T>
bool AvlTree<T>::isTreeEmpty() {
    if (!root){
        return true;
    }
    return false;
}

template <typename T>
int AvlTree<T>::getElementCount() {
    return elements_count;
}

template <typename T>
int AvlTree<T>::getRootSum() {
    return root->getSum();
}

template <typename T>
int AvlTree<T>::getSumofHighestNodes(int count) { // count > 0
    int result =0;
    AvlNode<T> *iterator = root;
    if(!root) {
        return 0;
    }
    if(root->getRank() <= count) {
        return iterator->getSum();
    }

    while(count > 0) {
        while (iterator->getRank() >= count) {
            if (iterator->getRank() == count) {
                result += iterator->getSum();
                return result;
            }
            if(!iterator->GetRightSon()) {
                break;
            }
            iterator = iterator->GetRightSon();
        }
        if(count == 1) {
            result += iterator->GetKey1();
            return result;
        }

        // rank < count
        result += iterator->getSum();
        count -= iterator->getRank();

        if(count == 0) {
            return result;
        }

        iterator = iterator->GetParentNode();
        result += iterator->GetKey1();
        count -= 1;
        // continue algorithm with left of iterator
        iterator = iterator->GetLeftSon();
    }
    return result;
}
template <typename T>
T** AvlTree<T>::GetTreeElements(){
    T** result = new T*[elements_count];
    int i=0;
    GetTreeElementsAux(&i, result, root);
    return result;
}

template <typename T>
void AvlTree<T>::GetTreeElementsAux(int *i, T** array, AvlNode<T> *node){
    if (!node) return;

    GetTreeElementsAux(i, array, node->GetLeftSon());
    array[*i] = node->GetData();
    *i += 1;
    GetTreeElementsAux(i, array, node->GetRightSon());
}


template <typename T>
AvlNode<T>** AvlTree<T>::GetTreeNodesInorder(){
    AvlNode<T>** result = new AvlNode<T>*[elements_count];
    int i=0;
    GetTreeNodesAux(&i, result, root);
    return result;
}


template <typename T>
void AvlTree<T>::GetTreeNodesAux(int *i, AvlNode<T>** array, AvlNode<T> *node){
    if (!node) return;

    GetTreeNodesAux(i, array, node->GetLeftSon());
    array[*i] = new AvlNode<T>(*node);
    *i += 1;
    GetTreeNodesAux(i, array, node->GetRightSon());
}

template <typename T>
AvlNode<T>* AvlTree<T>::CreateTreeFromArrayAux(AvlNode<T> **arr,
                                               int start, int arr_end)
{
    // Base Case
    if (start > arr_end)
        return NULL;

    // Get the middle element and make it root
    int mid = (start + arr_end)/2;
    AvlNode<T>* root = arr[mid];

    /* Recursively construct the left subtree
    and make it left child of root */
    root->SetLeftSon(CreateTreeFromArrayAux(arr, start, mid - 1));

    /* Recursively construct the right subtree
    and make it right child of root */
    root->SetRightSon(CreateTreeFromArrayAux(arr, mid + 1, arr_end));
    root->UpdateHeight();
    root->UpdateRankAndSum();
    return root;
}

template <typename T>
AvlNode<T>* AvlTree<T>::getRoot() {
    return root;
}

template <typename T>
void AvlTree<T>::updateParentsPreOrder(AvlNode<T>* node){
    if (!node){
        return;
    }
    //update parents of sons:
    if (node->GetRightSon()){
        node->GetRightSon()->SetParentNode(node);
    }
    if (node->GetLeftSon()){
        node->GetLeftSon()->SetParentNode(node);
    }

    //recur on left subtree
    updateParentsPreOrder(node->GetLeftSon());

    //recur on right subtree
    updateParentsPreOrder(node->GetRightSon());
}
#endif //HW1_AVLTREE_H
