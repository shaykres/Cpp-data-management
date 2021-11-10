cmake_minimum_required(VERSION 3.20)
project(SPL_HW1)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPL_HW1 main.cpp Action.h Customer.h Studio.h Trainer.h Workout.h Action.cpp Workout.cpp Trainer.cpp Studio.cpp Customer.cpp)
