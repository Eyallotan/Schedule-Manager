//
// Created by eyall on 6/12/2019.
//

#include "library2.h"
#include "Schedule.h"
#include <exception>
using namespace std;

void* Init(int n){
    if (n<1) {
        return nullptr;
    }
    Schedule *DS= nullptr;
    try {
        DS = new Schedule(n);
        return (void *) DS;
    }
    catch (std::bad_alloc& e){
        return nullptr;
    }
}

StatusType addRoom(void *DS, int roomID){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->addRoom(roomID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}


StatusType deleteRoom(void *DS, int roomID){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->deleteRoom(roomID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType addLecture(void *DS, int courseID, int groupID, int roomID, int
hour, int numStudents){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->addLecture(courseID,groupID,roomID,hour
                ,numStudents);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType deleteLecture(void *DS, int hour, int roomID){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->deleteLecture(hour,roomID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType mergeCourses(void *DS, int courseID1, int courseID2){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->mergeCourses(courseID1,courseID2);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType competition(void *DS, int courseID1, int courseID2, int numGroups,
        int * winner){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->competition(courseID1, courseID2, numGroups,
                winner);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

StatusType getAverageStudentsInCourse(void *DS, int hour, int roomID,
        float *average){
    if (!DS){
        return INVALID_INPUT;
    }
    try{
        return ((Schedule *)DS)->getAverageStudentsInCourse(hour, roomID,
                                   average);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}

void Quit(void **DS){
    Schedule* to_delete=((Schedule *)(*DS));
    delete to_delete;
    *DS= nullptr;
}

