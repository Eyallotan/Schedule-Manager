//
// Created by tomer on 6/11/2019.
//

#ifndef WET2_LECTURE_H
#define WET2_LECTURE_H


class Lecture {
public:
    //c'tors & d'tor
    Lecture(int CourseID, int groupID, int roomID, int hour, int numStudents);
    Lecture(const Lecture& copy);
    ~Lecture() = default;

    //helper functions:
    int getCourseID();
    int getGroupID();
    int getRoomID();
    int getHour();
    int getNumStudents();

private:
    //properties:
    int course_id;
    int group_id;
    int room;
    int hour;
    int num_students;

};

Lecture::Lecture(int CourseID, int groupID, int roomID, int hour,
        int numStudents) : course_id(CourseID), group_id(groupID),
        room(roomID), hour(hour), num_students(numStudents){}

Lecture::Lecture(const Lecture &copy) : course_id(copy.course_id), group_id
(copy.group_id), room(copy.room), hour(copy.hour),
num_students(copy.num_students) {}


int Lecture::getCourseID() {
    return course_id;
}

int Lecture::getGroupID() {
    return group_id;
}

int Lecture::getRoomID() {
    return room;
}

int Lecture::getHour() {
    return hour;
}

int Lecture::getNumStudents() {
    return num_students;
}


#endif //WET2_LECTURE_H
