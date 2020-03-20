cmake_minimum_required(VERSION 3.12)
project(Wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet2 main.cpp AvlNode.h AvlTree.h List.h ListNode.h
        HashTable.h KeyValuePair.h ReverseTreeNode.h UnionFind.h
        HourRoom.h Course.h Lecture.h Schedule.h library2.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -o main")