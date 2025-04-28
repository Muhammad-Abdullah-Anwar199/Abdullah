cmake_minimum_required(VERSION 3.30)
project(spring2025_se102_oop_project_s)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(spring2025_se102_oop_project_s
    admin.cpp
    admin.h
    main.cpp
    membership.cpp
    membership.h
    notification.cpp
    notification.h
    review.cpp
    review.h
    ticket.cpp
    ticket.h
    user.cpp
    user.h
    museum.cpp
    museum.h
        exhibit.cpp
        exhibit.h
        schedule.cpp
        schedule.h
        guide.cpp
        guide.h)
