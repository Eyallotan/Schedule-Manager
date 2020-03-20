//
// Created by tomer on 6/11/2019.
//

#ifndef WET2_SCHEDULE_H
#define WET2_SCHEDULE_H

#include "UnionFind.h"
#include "HashTable.h"
#include "Course.h"
#include "HourRoom.h"
#include "library2.h"

#define M 10

class Schedule {
public:
    //c'tor & d'tor
    Schedule(int n);
    ~Schedule();

    //interface functions:
    StatusType addRoom(int roomID);
    StatusType deleteRoom(int roomID);
    StatusType addLecture(int courseID, int groupID, int roomID,
            int hour, int numOfStudents);
    StatusType deleteLecture(int hour, int roomID);
    StatusType mergeCourses(int courseID1, int courseID2);
    StatusType competition(int courseID1, int courseID2, int numGroups, int
    *winner);
    StatusType getAverageStudentsInCourse(int hour, int roomID,
                    float * average);

private:
    //properties:
    int courses_count;
    UnionFind<Course> *courses;
    HashTable<HourRoom> *rooms;

    //helper functions:
    StatusType validateRoomAvailability(int roomID);
    AvlNode<Lecture>** UnionLecturesArray(AvlNode<Lecture>** arr1,
    AvlNode<Lecture>** arr2, int arr1_len, int arr2_len, StatusType* result);
    StatusType mergeCoursesAux1(Course* course1, Course* course2);
    void mergeCoursesAux2(Course* course1, Course* course2, Course*
    merged_course);
    void deleteArrays(AvlNode<Lecture>** arr1, int arr1_len,
            AvlNode<Lecture>** arr2, int arr2_len);
};

Schedule::Schedule(int n) : courses_count(n){
    courses = new UnionFind<Course>(courses_count);
    for (int i = 1; i <= n; ++i) {
        ReverseTreeNode<Course> *set = courses->Makeset(i);
        Course *course = new Course(i);
        set->setData(course);
    }
    rooms = new HashTable<HourRoom>[M+1];
}

StatusType Schedule::addRoom(int roomID) {
    if(roomID <= 0) {
        return INVALID_INPUT;
    }
    for (int i = 1; i <= M; ++i) {
        //check if room exists
        if (rooms[i].Find(roomID)) {
            return FAILURE;
        }
    }
    for (int i = 1; i <= M; ++i) {
        HourRoom *hourRoom = new HourRoom(i, roomID);
        rooms[i].Insert(roomID, hourRoom);
    }
    return SUCCESS;
}
StatusType Schedule::deleteRoom(int roomID) {
    if(roomID <= 0) {
        return INVALID_INPUT;
    }
    StatusType validation_result = validateRoomAvailability(roomID);
    if(validation_result != SUCCESS) {
        return validation_result;
    }

    for (int i = 1; i <= M; ++i) {
        rooms[i].Delete(roomID);
    }
    return SUCCESS;
}

StatusType Schedule::validateRoomAvailability(int roomID) {

    for (int i = 1; i <= M; ++i) {
        HourRoom *hourRoom = rooms[i].Find(roomID);
        //check if room exists
        if(!hourRoom) {
            return FAILURE;
        }
        //check if room available
        if(!hourRoom->isHourRoomEmpty()) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

StatusType Schedule::addLecture(int courseID, int groupID, int roomID,
               int hour, int numOfStudents) {
    if (courseID>courses_count || groupID < 0 || courseID < 1 ||
    numOfStudents < 0 || roomID <= 0 || hour > M || hour < 1 ){
        return INVALID_INPUT;
    }
    HourRoom *hourRoom = rooms[hour].Find(roomID);
    if(!hourRoom) {
        return FAILURE;
    }
    if(!hourRoom->isHourRoomEmpty()) {
        return FAILURE;
    }

    Course* course=courses->Find(courseID);
    if (course->lectureGroupInHourExists(groupID,hour)){
        return FAILURE;
    }
    Lecture* lecture=new Lecture(courseID,groupID,roomID,hour,numOfStudents);
    //add lecture to course trees
    course->addLectureToCourse(lecture,numOfStudents,groupID,hour);
    //add lecture to hash table
    Lecture* copy=new Lecture(*lecture);
    rooms[hour].Find(roomID)->setLecture(copy);
    return SUCCESS;

}
StatusType Schedule::deleteLecture(int hour, int roomID) {
    if (roomID <= 0 || hour > M || hour < 1 ){
        return INVALID_INPUT;
    }
    if (!(rooms[hour].Find(roomID)) ||
            rooms[hour].Find(roomID)->isHourRoomEmpty()){
        return FAILURE;
    }
    Lecture* to_delete=rooms[hour].Find(roomID)->getLecture();
    int course_id = to_delete->getCourseID();
    Course* course=courses->Find(course_id);
    //delete lecture from course trees
    course->deleteLectureFromCourse(to_delete->getNumStudents(),
            to_delete->getGroupID(),to_delete->getHour());
    //delete lecture from hash table
    rooms[hour].Find(roomID)->deleteLecture();
    return SUCCESS;

}
StatusType Schedule::mergeCourses(int courseID1, int courseID2) {
    if (courseID1>courses_count || courseID1 < 1 || courseID2>courses_count
    || courseID2 < 1 ){
        return INVALID_INPUT;
    }
    Course* course1=courses->Find(courseID1);
    Course* course2=courses->Find(courseID2);
    if (course1==course2){
        return FAILURE;
    }
    if(mergeCoursesAux1(course1,course2)==FAILURE){
        return FAILURE;
    }
    return SUCCESS;
}


StatusType Schedule::mergeCoursesAux1(Course* course1, Course* course2){
    AvlNode<Lecture>** course1_group_hour_nodes =
            course1->getElementsInArray(GROUP_HOUR_TREE);
    AvlNode<Lecture>** course2_group_hour_nodes =
            course2->getElementsInArray(GROUP_HOUR_TREE);

    StatusType result=SUCCESS;
    AvlNode<Lecture>** union_lectures_array=UnionLecturesArray
            (course1_group_hour_nodes, course2_group_hour_nodes
                    ,course1->getLectureCount(),
                    course2->getLectureCount(),&result);
    /*failure means there are two groups that have a
     lecture in the same hour*/
    if (result==FAILURE){
        deleteArrays(course1_group_hour_nodes,course1->getLectureCount(),
                course2_group_hour_nodes, course2->getLectureCount());
        return FAILURE;
    }

    Course* merged_course=courses->Union(course1->getCourseID()
            ,course2->getCourseID());
    merged_course->replaceLectures(union_lectures_array,
                                   course1->getLectureCount()+
                                   course2->getLectureCount(),
                                   GROUP_HOUR_TREE);
    mergeCoursesAux2(course1,course2,merged_course);
    delete [] course1_group_hour_nodes;
    delete [] course2_group_hour_nodes;
    delete [] union_lectures_array;
    return SUCCESS;
}

void Schedule::deleteArrays(AvlNode<Lecture> **arr1, int arr1_len,
                            AvlNode<Lecture> **arr2, int arr2_len) {
    for (int i = 0; i < arr1_len; ++i) {
        delete arr1[i];
    }
    for (int j = 0; j < arr2_len; ++j) {
        delete arr2[j];
    }
    delete [] arr1;
    delete [] arr2;
}

void Schedule::mergeCoursesAux2(Course* course1, Course* course2, Course*
merged_course){
    AvlNode<Lecture>** course1_lecture_nodes =
            course1->getElementsInArray(LECTURES_TREE);
    AvlNode<Lecture>** course2_lecture_nodes =
            course2->getElementsInArray(LECTURES_TREE);

    StatusType result=SUCCESS;
    AvlNode<Lecture>** union_lectures_array=UnionLecturesArray
            (course1_lecture_nodes, course2_lecture_nodes
                    ,course1->getLectureCount(),
             course2->getLectureCount(),&result);
    //this function won't fail with lecture trees (no double entries)

    merged_course->replaceLectures(union_lectures_array,
                                   course1->getLectureCount()+
                                   course2->getLectureCount(),
                                   LECTURES_TREE);
    delete [] course1_lecture_nodes;
    delete [] course2_lecture_nodes;
    delete [] union_lectures_array;
}


AvlNode<Lecture>** Schedule::UnionLecturesArray(AvlNode<Lecture>** arr1,
                                                AvlNode<Lecture>** arr2, int
                                                arr1_len, int arr2_len,
                                                StatusType* result) {
    AvlNode<Lecture>** array = new AvlNode<Lecture>*[arr1_len + arr2_len];
    int i = 0, j = 0;
    while (i < arr1_len && j < arr2_len) {
        if (arr1[i]->GetKey1() == arr2[j]->GetKey1() && arr1[i]->GetKey2() ==
                arr2[j]->GetKey2() && arr1[i]->GetKey3() == arr2[j]->GetKey3()){
            delete [] array;
            *result=FAILURE; //found two identical groups in the same hour
            return NULL;
        }
        if(arr1[i]->GetKey1() < arr2[j]->GetKey1()) {
            array[i+j] = arr1[i];
            i++;
            continue;
        }
        if (arr1[i]->GetKey1() > arr2[j]->GetKey1()) {
            array[i+j] = arr2[j];
            j++;
            continue;
        }
        if (arr1[i]->GetKey1() == arr2[j]->GetKey1()){
            if(arr1[i]->GetKey2() < arr2[j]->GetKey2()) {
                array[i+j] = arr1[i];
                i++;
                continue;
            }
            if (arr1[i]->GetKey2() > arr2[j]->GetKey2()) {
                array[i+j] = arr2[j];
                j++;
                continue;
            }
            if (arr1[i]->GetKey2() == arr2[j]->GetKey2()){
                if(arr1[i]->GetKey3() < arr2[j]->GetKey3()) {
                    array[i+j] = arr1[i];
                    i++;
                    continue;
                }
                if (arr1[i]->GetKey3() > arr2[j]->GetKey3()) {
                    array[i+j] = arr2[j];
                    j++;
                    continue;
                }
            }
        }

    } // sorry..

    while(i < arr1_len){
        array[i+j] = arr1[i];
        i++;
    }

    while(j < arr2_len){
        array[i+j] = arr2[j];
        j++;
    }
    return array;
}




StatusType Schedule::competition(int courseID1, int courseID2, int numGroups,
        int *winner) {
    if (courseID1>courses_count || courseID2>courses_count || courseID1 < 1 ||
            courseID2 < 1 || numGroups <= 0 || !winner ){
        return INVALID_INPUT;
    }

    Course *course1 = courses->Find(courseID1);
    Course *course2 = courses->Find(courseID2);
    if(course1 == course2) {
        return FAILURE;
    }

    int courseOneSum = course1->getHighestGroupStudents(numGroups);
    int courseTwoSum = course2->getHighestGroupStudents(numGroups);
    if(courseOneSum == courseTwoSum) {
        *winner = courseID1 > courseID2 ? courseID1 : courseID2;
        return SUCCESS;
    }

    *winner = courseOneSum > courseTwoSum ? courseID1 : courseID2;
    return SUCCESS;
}
StatusType Schedule::getAverageStudentsInCourse(int hour, int roomID,
                               float * average) {
    if (roomID <= 0 || hour > M || hour < 1 || !average){
        return INVALID_INPUT;
    }
    HourRoom *hourRoom = rooms[hour].Find(roomID);
    if(!hourRoom) {
        return FAILURE;
    }
    Lecture *lecture = hourRoom->getLecture();
    if(!lecture) {
        return FAILURE;
    }

    Course *course = courses->Find(lecture->getCourseID());
    int total_students_count = course->getTotalStudentsCount();
    int lectures_count = course->getLectureCount();
    *average = (float) total_students_count / lectures_count;

    return SUCCESS;
}

Schedule::~Schedule() {
    delete courses;
    delete[] rooms;
}

#endif //WET2_SCHEDULE_H
