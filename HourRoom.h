//
// Created by tomer on 6/11/2019.
//

#ifndef WET2_HOURROOM_H
#define WET2_HOURROOM_H

#include <iostream>
#include "Lecture.h"


class HourRoom {
public:
    //c'tor & d'tor
    HourRoom(int hour, int roomID);
    ~HourRoom();

    //helper functions:
    Lecture* getLecture();
    void setLecture(Lecture* new_lecture);
    void deleteLecture();
    bool isHourRoomEmpty();

private:
    //properties:
    int hour;
    int room_id;
    Lecture* lecture;
};

HourRoom::HourRoom(int hour, int roomID) : hour(hour),
        room_id(roomID), lecture(nullptr)  {}

HourRoom::~HourRoom() {
    delete lecture;
    lecture= nullptr;
}

Lecture* HourRoom::getLecture(){
    return lecture;
}

void HourRoom::setLecture(Lecture *new_lecture) {
    lecture=new_lecture;
}

bool HourRoom::isHourRoomEmpty() {
    return lecture == nullptr;
}
void HourRoom::deleteLecture() {
    delete lecture;
    lecture=nullptr;
}
#endif //WET2_HOURROOM_H
