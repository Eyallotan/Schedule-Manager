
#include <iostream>
#include "AvlTree.h"
#include "List.h"
#include "HashTable.h"
#include "UnionFind.h"
#include <assert.h>
#include "Schedule.h"
class avlObj{
public:
    avlObj(int i=0) :key(i){}
    ~avlObj() {
        //std::cout<< "obj deleted!" << std::endl;
    };
    int key;
};

void testRightRoll() {
    AvlTree<avlObj> avlTree;
    avlObj* l1 = new avlObj();
    avlObj* l2 = new avlObj();
    avlObj* l3 = new avlObj();
    avlTree.InsertElement(4,1,1, l1);
    avlTree.InsertElement(3,1,1, l2);
    avlTree.InsertElement(2,1,1, l3);
}

void testHorizontalTree() {
    AvlTree<avlObj> avlTree;
    avlTree.InsertElement(24,1,1, new avlObj());
    avlTree.InsertElement(12,1,1, new avlObj());
    avlTree.InsertElement(6,1,1, new avlObj());
    avlTree.InsertElement(50,1,1, new avlObj());
}

void testRightLineTree() {
    AvlTree<avlObj> rightTree;
    rightTree.InsertElement(1,1,1, new avlObj());
    rightTree.InsertElement(2,1,1, new avlObj());
    rightTree.InsertElement(6,1,1, new avlObj());
    rightTree.InsertElement(50,1,1, new avlObj());
}

void testLeftLineTree() {
    AvlTree<avlObj> leftTree;
    leftTree.InsertElement(24,1,1, new avlObj());
    leftTree.InsertElement(12,1,1, new avlObj());
    leftTree.InsertElement(6,1,1, new avlObj());
    leftTree.InsertElement(3,1,1, new avlObj());
}

void testPage26Tree() {
    AvlTree<avlObj> leftTree;
    leftTree.InsertElement(15,1,1, new avlObj());
    leftTree.InsertElement(10,1,1, new avlObj());
    leftTree.InsertElement(20,1,1, new avlObj());
    leftTree.InsertElement(6,1,1, new avlObj());
    leftTree.InsertElement(13,1,1, new avlObj());
    leftTree.InsertElement(17,1,1, new avlObj());
    leftTree.InsertElement(24,1,1, new avlObj());
    leftTree.InsertElement(4,1,1, new avlObj());
    leftTree.InsertElement(7,1,1, new avlObj());
    leftTree.InsertElement(12,1,1, new avlObj());
    leftTree.InsertElement(14,1,1, new avlObj());

    // Cause LR Roll
    leftTree.InsertElement(11,1,1, new avlObj());
    leftTree.InorderPrint();

}

void testRL() {
    AvlTree<avlObj> leftTree;
    leftTree.InsertElement(11,1,1, new avlObj());
    leftTree.InsertElement(8,1,1, new avlObj());
    leftTree.InsertElement(19,1,1, new avlObj());
    leftTree.InsertElement(6,1,1, new avlObj());
    leftTree.InsertElement(10,1,1, new avlObj());
    leftTree.InsertElement(13,1,1, new avlObj());
    leftTree.InsertElement(25,1,1, new avlObj());
    leftTree.InsertElement(12,1,1, new avlObj());
    leftTree.InsertElement(17,1,1, new avlObj());
    leftTree.InsertElement(23,1,1, new avlObj());
    leftTree.InsertElement(29,1,1, new avlObj());
    //leftTree.InorderPrint();

    // Cause RL Roll
    leftTree.InsertElement(15,1,1, new avlObj());
}

void testRemove(){
    AvlTree<avlObj> DonaTree;

    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.RemoveElement(11,1,1); //leaf is root

    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.InsertElement(6,1,1, new avlObj());
    DonaTree.RemoveElement(6,1,1); //leaf is left son
    DonaTree.RemoveElement(11,1,1); //leaf is root


    DonaTree.InsertElement(6,1,1, new avlObj());
    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.RemoveElement(11,1,1); //leaf is right son
    DonaTree.RemoveElement(6,1,1); //leaf is root

    DonaTree.InsertElement(6,1,1, new avlObj());
    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.RemoveElement(6,1,1); //remove vertex with right son
    DonaTree.RemoveElement(11,1,1);

    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.InsertElement(6,1,1, new avlObj());
    DonaTree.RemoveElement(11,1,1); //remove vertex with left son
    DonaTree.RemoveElement(6,1,1);

    //delete 5 example
    DonaTree.InsertElement(5,1,1, new avlObj());
    DonaTree.InsertElement(2,1,1, new avlObj());
    DonaTree.InsertElement(9,1,1, new avlObj());
    DonaTree.InsertElement(3,1,1, new avlObj());
    DonaTree.InsertElement(7,1,1, new avlObj());
    DonaTree.InsertElement(10,1,1, new avlObj());
    DonaTree.InsertElement(8,1,1, new avlObj()); //the next inorder has right son
    DonaTree.InorderPrint();
    DonaTree.RemoveElement(5,1,1);
    DonaTree.InorderPrint();
    DonaTree.RemoveElement(2,1,1);
    DonaTree.RemoveElement(9,1,1);
    DonaTree.RemoveElement(3,1,1);
    DonaTree.RemoveElement(7,1,1);
    DonaTree.RemoveElement(10,1,1);
    DonaTree.RemoveElement(8,1,1);
    DonaTree.InorderPrint();


    //delete with 2 rolls
    DonaTree.InsertElement(5,1,1, new avlObj());
    DonaTree.InsertElement(2,1,1, new avlObj());
    DonaTree.InsertElement(8,1,1, new avlObj());
    DonaTree.InsertElement(1,1,1, new avlObj());
    DonaTree.InsertElement(4,1,1, new avlObj());
    DonaTree.InsertElement(6,1,1, new avlObj());
    DonaTree.InsertElement(10,1,1, new avlObj());
    DonaTree.InsertElement(3,1,1, new avlObj());
    DonaTree.InsertElement(7,1,1, new avlObj());
    DonaTree.InsertElement(9,1,1, new avlObj());
    DonaTree.InsertElement(12,1,1, new avlObj());
    DonaTree.InsertElement(11,1,1, new avlObj());
    DonaTree.InorderPrint();
    DonaTree.RemoveElement(1,1,1); //RL and RR roll
    DonaTree.InorderPrint();

}

void KeyTest(){
    //insert
    AvlTree<int>* keytree=new AvlTree<int>();
    keytree->InsertElement(1,1,1, new int);
    keytree->InsertElement(1,1,2, new int);
    keytree->InsertElement(1,2,1, new int);
    keytree->InsertElement(1,2,2, new int);
    keytree->InsertElement(2,2,2, new int);
    keytree->InsertElement(3,1,1, new int);
    keytree->InsertElement(3,1,5, new int);
    keytree->InsertElement(3,3,3, new int);
    keytree->InorderPrint();

    keytree->RemoveElement(1,1,2);
    keytree->RemoveElement(2,2,2);
    keytree->RemoveElement(3,1,5);
    keytree->InorderPrint();
    keytree->RemoveElement(1,1,1);
    keytree->RemoveElement(1,2,1);
    keytree->RemoveElement(1,2,2);
    keytree->RemoveElement(3,1,1);
    keytree->RemoveElement(3,3,3);
    keytree->InorderPrint();

    keytree->InsertElement(1,2,2, new int);
    keytree->InsertElement(1,1,3, new int);
    keytree->InsertElement(1,2,1, new int);
    keytree->InsertElement(1,1,1, new int);
    keytree->InsertElement(1,1,4, new int);
    keytree->InsertElement(1,2,3, new int);
    int* i=new int;
    keytree->InsertElement(1,2,3, i);
    delete i;
    keytree->InsertElement(1,4,5, new int);
    keytree->InorderPrint();

    delete keytree;


}

void getSumofHighestNodesTests() {
    std::cout<<"getSumofHighestNodes Tests"<<std::endl;

    AvlTree<avlObj> avlTree;
    avlTree.InsertElement(24,1,1, new avlObj());
    avlTree.InsertElement(12,1,1, new avlObj());
    avlTree.InsertElement(6,1,1, new avlObj());
    avlTree.InsertElement(50,1,1, new avlObj());

    int result = avlTree.getSumofHighestNodes(10);
    assert(result == 92);

    result = avlTree.getSumofHighestNodes(4);
    assert(result == 92);

    result = avlTree.getSumofHighestNodes(2);
    assert(result == 74);

    result = avlTree.getSumofHighestNodes(1);
    assert(result == 50);

    result = avlTree.getSumofHighestNodes(3);
    assert(result == 86);
    std::cout<<"getSumofHighestNodes Tests Completed"<<std::endl;
}
void AVLTests() {
    std::cout<<"~~~~~~~~~~~~~~~ AVL tests ~~~~~~~~~~~~~~~"<<std::endl;
    testRightRoll();
    testHorizontalTree();
    testLeftLineTree();
    testRightLineTree();
    testPage26Tree();
    testRL();
    testRemove();
    getSumofHighestNodesTests();
    std::cout<<"~~~~~~~~~~~~~~~ AVL tests Completed ~~~~~~~~~~~~~~~"<<std::endl;
}

void RehashTests() {

/*
        define DEFAULT_SIZE 10
        define ENLARGEMENT_RATIO 3
        define ENLARGEMENT_FACTOR 2
        define REDUCTION_RATIO 0.25
        define REDUCTION_FACTOR 0.5
     */

    HashTable<avlObj> *myHash = new HashTable<avlObj>();

    for(int i=0 ; i< 1000; i++) {
        myHash->Insert(i, new avlObj(i));
    }
    for(int i=0 ; i< 999; i++) {
        myHash->Delete(i);
    }
    assert(myHash->Find(999)->key==999);

    delete myHash;


}
void HashTableTests() {
    HashTable<avlObj> *myHash = new HashTable<avlObj>();

    myHash->Insert(4, new avlObj(3));
    assert(myHash->Find(4)->key == 3);
    myHash->Insert(13, new avlObj());
    myHash->Insert(17, new avlObj());
    myHash->Insert(16, new avlObj());
    myHash->Insert(11, new avlObj());
    myHash->Insert(1, new avlObj());
    myHash->Insert(12, new avlObj());
    myHash->Insert(60, new avlObj());
    //myHash->printHashTable();
    myHash->Insert(70, new avlObj());
    myHash->Insert(80, new avlObj(12));
    assert(myHash->Find(80)->key == 12);
    assert(myHash->Find(81) == NULL);

    //myHash->printHashTable();

    avlObj *test = myHash->Find(1);
    delete myHash;

    RehashTests();
}

void UnionFindTests(){
    UnionFind<int>* donaSet= new UnionFind<int>(10);
    for (int i=1;i<=10;i++) {
        ReverseTreeNode<int>* node=donaSet->Makeset(i);
        int* val=new int;
        *val=i;
        node->setData(val);
        assert(*donaSet->Find(i)==i);
    }
    assert(*donaSet->Union(1,2)==1);
    assert(*donaSet->Union(3,4)==3);
    assert(*donaSet->Union(2,4)==1);
    assert(*donaSet->Find(4)==1); //shrink routes
    assert(*donaSet->Union(5,6)==5);
    assert(*donaSet->Union(6,5)==5);
    assert(*donaSet->Union(7,8)==7);
    assert(*donaSet->Union(9,8)==7);
    assert(*donaSet->Union(5,9)==7);
    assert(*donaSet->Union(2,8)==7);

    delete donaSet;

}

void getAverageStudentsInCourseTests() {
    std::cout<<"get Average Students In Course Tests"<<std::endl;
    StatusType result;

    Schedule *dona = new Schedule(12);
    dona->addRoom(5);
    dona->addRoom(6);
    result=dona->addLecture(1,1,5,1,20);
    assert(result==SUCCESS);
    result=dona->addLecture(1,2,5,2,30);
    assert(result==SUCCESS);
    result=dona->addLecture(1,3,5,3,40);
    assert(result==SUCCESS);
    result=dona->addLecture(1,4,5,4,50);
    assert(result==SUCCESS);

    float averege;
    result = dona->getAverageStudentsInCourse(1,5, &averege);
    assert(result==SUCCESS);
    assert(averege==35);
    averege =0;
    result = dona->getAverageStudentsInCourse(2,5, &averege);
    assert(result==SUCCESS);
    assert(averege==35);
    averege =0;
    result = dona->getAverageStudentsInCourse(3,5, &averege);
    assert(result==SUCCESS);
    assert(averege==35);
    averege =0;
    result = dona->getAverageStudentsInCourse(4,5, &averege);
    assert(result==SUCCESS);
    assert(averege==35);
    averege =0;
    result = dona->getAverageStudentsInCourse(5,5, &averege);
    assert(result==FAILURE);
    result = dona->getAverageStudentsInCourse(5,8, &averege);
    assert(result==FAILURE);
    result = dona->getAverageStudentsInCourse(5,8, NULL);
    assert(result==INVALID_INPUT);
    delete dona;
    std::cout<<"~~ get Average Students In Course Completed ~~"<<std::endl;
}

void competitionTests() {
    std::cout<<"~~ competition Tests ~~"<<std::endl;
    StatusType result;

    Schedule *dona = new Schedule(12);
    dona->addRoom(5);
    dona->addRoom(6);
    result=dona->addLecture(1,1,5,1,20);
    result=dona->addLecture(1,2,5,2,30);
    result=dona->addLecture(1,3,5,3,40);
    result=dona->addLecture(1,4,5,4,50);

    result=dona->addLecture(2,1,6,6,20);
    result=dona->addLecture(2,2,6,7,30);
    result=dona->addLecture(2,3,6,8,40);
    result=dona->addLecture(2,4,6,9,50);

    result=dona->addLecture(3,4,5,5,2000);
    result=dona->addLecture(4,4,6,5,1200);

    int winner =0;

    result = dona->competition(1, 2, 5, NULL);
    assert(result == INVALID_INPUT);
    result = dona->competition(1, 2, 0, &winner);
    assert(result == INVALID_INPUT);
    result = dona->competition(0, 2, 2, &winner);
    assert(result == INVALID_INPUT);
    result = dona->competition(1, 13, 3, &winner);
    assert(result == INVALID_INPUT);

    result = dona->competition(3, 4, 5, &winner);
    assert(result == SUCCESS);
    assert(winner == 3);

    result = dona->competition(1, 2, 5, &winner);
    assert(result == SUCCESS);
    assert(winner == 2);

    dona->mergeCourses(1, 2);
    result = dona->competition(1, 2, 5, &winner);
    assert(result == FAILURE);

    delete dona;
    std::cout<<"~~ competition Tests Completed ~~"<<std::endl;
}

void ScheduleTest() {
    std::cout<<"create schedule test"<<std::endl;
    Schedule *dona = new Schedule(12);
    std::cout<<"create schedule success"<<std::endl;
    std::cout<<"add room test"<<std::endl;
    StatusType result = dona->addRoom(5);
    assert(result==SUCCESS);
    result=dona->addRoom(6);
    assert(result==SUCCESS);
    result=dona->addRoom(7);
    assert(result==SUCCESS);
    result=dona->addRoom(8);
    assert(result==SUCCESS);
    result=dona->addRoom(1000);
    assert(result==SUCCESS);
    result=dona->addRoom(1000);
    assert(result==FAILURE);
    result=dona->addRoom(0);
    assert(result==INVALID_INPUT);
    std::cout<<"add room test success"<<std::endl;
    std::cout<<"add lecture test"<<std::endl;
    //basic add lecture
    result=dona->addLecture(1,10,5,5,50);
    assert(result==SUCCESS);
    //basic delete lecture
    result=dona->deleteLecture(5,5);
    assert(result==SUCCESS);
    //add lecture INVALID_INPUT:
    result=dona->addLecture(13,10,5,5,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(0,10,5,5,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(1,-9,5,5,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(1,10,0,5,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(1,10,5,11,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(1,10,5,0,50);
    assert(result==INVALID_INPUT);
    result=dona->addLecture(1,10,5,5,-70);
    assert(result==INVALID_INPUT);
    //add lecture FAILURE:
    result=dona->addLecture(1,10,5,5,50);
    assert(result==SUCCESS);
    result=dona->addLecture(1,10,6,5,30); //this group already has a lecture
    // in this hour
    assert(result==FAILURE);
    result=dona->addLecture(2,10,5,5,50); //room already in use
    assert(result==FAILURE);
    result=dona->addLecture(1,20,19,5,50); //room doesn't exist
    assert(result==FAILURE);
    std::cout<<"add lecture test success"<<std::endl;
    std::cout<<"delete room test"<<std::endl;
    result=dona->deleteRoom(5);
    assert(result==FAILURE);
    result=dona->deleteRoom(34);
    assert(result==FAILURE);
    result=dona->deleteRoom(-7);
    assert(result==INVALID_INPUT);
    result=dona->deleteRoom(8);
    assert(result==SUCCESS);
    std::cout<<"delete room test success"<<std::endl;
    std::cout<<"delete lecture test"<<std::endl;
    result=dona->deleteLecture(0,5);
    assert(result==INVALID_INPUT);
    result=dona->deleteLecture(13,5);
    assert(result==INVALID_INPUT);
    result=dona->deleteLecture(5,0);
    assert(result==INVALID_INPUT);
    result=dona->deleteLecture(5,99);
    assert(result==FAILURE);
    result=dona->deleteLecture(5,6);
    assert(result==FAILURE);
    result=dona->deleteLecture(5,5);
    assert(result==SUCCESS);
    std::cout<<"delete lecture success"<<std::endl;
    std::cout<<"merge courses test"<<std::endl;
    result=dona->mergeCourses(6,7);
    assert(result==SUCCESS);
    result=dona->mergeCourses(6,7);
    assert(result==FAILURE);
    result=dona->addRoom(20);
    assert(result==SUCCESS);
    result=dona->addRoom(21);
    assert(result==SUCCESS);
    result=dona->addRoom(22);
    assert(result==SUCCESS);
    result=dona->addRoom(23);
    assert(result==SUCCESS);
    result=dona->addLecture(4,10,20,6,50);
    assert(result==SUCCESS);
    result=dona->addLecture(5,10,21,6,50);
    assert(result==SUCCESS);
    result=dona->mergeCourses(4,5);
    assert(result==FAILURE);
    result=dona->addLecture(3,20,22,3,50);
    assert(result==SUCCESS);
    result=dona->addLecture(3,20,23,2,50);
    assert(result==SUCCESS);
    result=dona->mergeCourses(3,4);
    assert(result==SUCCESS);
    result=dona->mergeCourses(3,5);
    assert(result==FAILURE);
    std::cout<<"merge courses success"<<std::endl;
    getAverageStudentsInCourseTests();
    competitionTests();
     std::cout<<"delete schedule test"<<std::endl;
    delete dona;
    std::cout<<"delete schedule success"<<std::endl;
    std::cout<<"Congratulations!"<<std::endl;
}



int main() {
    AVLTests();
    HashTableTests();
    KeyTest();
    UnionFindTests();
    ScheduleTest();


    return 0;
}
