//
// Created by tomer on 6/11/2019.
//

#ifndef WET2_COURSE_H
#define WET2_COURSE_H

#include "AvlTree.h"
#include "Lecture.h"
#include <stdbool.h>
#define KEY1 1
#define LECTURES_TREE 1
#define GROUP_HOUR_TREE 2


class Course {
public:
    //c'tor & d'tor
    Course(int i);
    ~Course();

    //helper functions:
    int getCourseID();
    bool lectureGroupInHourExists(int group_id, int hour);
    void addLectureToCourse(Lecture* to_add, int num_students, int group_id,
            int hour);
    void deleteLectureFromCourse(int num_students, int group_id, int hour);
    AvlNode<Lecture>** getElementsInArray(int indicator);
    int getLectureCount();
    int getTotalStudentsCount();
    void replaceLectures(AvlNode<Lecture>** new_lectures, int
    new_lectures_count, int indicator);
    int getHighestGroupStudents(int lectures_count);

private:
    //properties:
    int course_id;
    AvlTree<Lecture> *lectures;
    AvlTree<Lecture> *group_hour_sort;
};

Course::Course(int i) :course_id(i) {
    lectures = new AvlTree<Lecture>();
    group_hour_sort = new AvlTree<Lecture>();

}

Course::~Course() {
    delete lectures;
    delete group_hour_sort;
}

int Course::getCourseID() {
    return course_id;
}

bool Course::lectureGroupInHourExists(int group_id, int hour) {
     return group_hour_sort->FindElement(KEY1,group_id,hour);
}

void Course::addLectureToCourse(Lecture *to_add, int num_students, int group_id,
                                int hour) {
    Lecture* copy= new Lecture(*to_add);
    lectures->InsertElement(num_students,group_id,hour,to_add);
    group_hour_sort->InsertElement(KEY1,group_id,hour,copy);
}

void Course::deleteLectureFromCourse(int num_students, int group_id, int hour) {
    lectures->RemoveElement(num_students,group_id,hour);
    group_hour_sort->RemoveElement(KEY1,group_id,hour);
}

AvlNode<Lecture>** Course::getElementsInArray(int indicator) {
    if (indicator==GROUP_HOUR_TREE) {
        return group_hour_sort->GetTreeNodesInorder();
    }
    else {
        return lectures->GetTreeNodesInorder();
    }
}

int Course::getLectureCount() {
    return lectures->getElementCount();
}

int Course::getTotalStudentsCount() {
    return lectures->getRootSum();
}

int Course::getHighestGroupStudents(int lectures_count) {
    return lectures->getSumofHighestNodes(lectures_count);
}

void Course::replaceLectures(AvlNode<Lecture>** new_lectures,
                             int new_lectures_count, int indicator) {
    if (indicator==LECTURES_TREE) {
        delete lectures;
        lectures = new AvlTree<Lecture>(new_lectures, new_lectures_count);
        lectures->updateParentsPreOrder(lectures->getRoot());
        if(lectures->getRoot()){
            lectures->getRoot()->SetParentNode(nullptr);
        }
    }
    else {
        delete group_hour_sort;
        group_hour_sort = new AvlTree<Lecture>(new_lectures, new_lectures_count);
        group_hour_sort->updateParentsPreOrder(group_hour_sort->getRoot());
        if(group_hour_sort->getRoot()){
            group_hour_sort->getRoot()->SetParentNode(nullptr);
        }
    }
}

#endif //WET2_COURSE_H
