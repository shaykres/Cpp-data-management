//
// Created by Shay on 10/11/2021.
//

#ifndef SPL_HW1_WORKOUT_H
#define SPL_HW1_WORKOUT_H
#include <string>

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};

class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
    std::string toString();
    ~Workout();
    Workout(const Workout& other);
    bool operator < (const Workout& str) const;
   // void operator = (const Workout& str) ;


private:
    const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};

#endif //SPL_HW1_WORKOUT_H
