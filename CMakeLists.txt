cmake_minimum_required(VERSION 3.20)
project(SPL_HW1)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPL_HW1 src/main.cpp include/Action.h include/Customer.h include/Studio.h include/Trainer.h include/Workout.h src/Action.cpp src/Workout.cpp src/Trainer.cpp src/Studio.cpp src/Customer.cpp)
