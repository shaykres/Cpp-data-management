//
// Created by Shay on 10/11/2021.
//
#include "../include/Customer.h"
#include <algorithm>
#include <string>
#include <iostream>


Customer::Customer(std::string c_name, int c_id) : id(c_id), name(c_name)
{
}

std::string Customer::getName() const
{
    return name;
}

int Customer::getId() const
{
    return id;
}



Customer::Customer(const Customer& other):id(other.id), name(other.name)
{
    //there is no need for the copy constructor
}

Customer::~Customer() {

}


//void Customer::operator=(const Customer& other)
//{
//	if (&other != this) {
//		id = other.id;
//		name = other.name;
//	}
//}

SweatyCustomer::SweatyCustomer(std::string name, int id) :Customer(name, id)
{

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout>& workout_options)
{
    std::vector<int> myWorkout;
    for (int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == WorkoutType::CARDIO)
            myWorkout.push_back(workout_options[i].getId());
    }

    return myWorkout;
}

std::string SweatyCustomer::toString() const
{
    return "swt";
}

Customer* SweatyCustomer::clone()
{
    SweatyCustomer* c = new SweatyCustomer(*this);
    return c;
}

//SweatyCustomer::~SweatyCustomer() {
//
//}


CheapCustomer::CheapCustomer(std::string name, int id) :Customer(name, id)
{
}

std::vector<int> CheapCustomer::order(const std::vector<Workout>& workout_options)
{
    std::vector<int> myWorkout;
    if (workout_options.size() > 0) {

        int minprice = workout_options[0].getPrice();
        int idmin = workout_options[0].getId();
        for (int i = 1; i < workout_options.size(); i++) {
            if ((minprice > workout_options[i].getPrice())||((minprice == workout_options[i].getPrice())&& (idmin> workout_options[i].getId()))) {
                minprice = workout_options[i].getPrice();
                idmin = workout_options[i].getId();
            }
        }
        myWorkout.push_back(idmin);
    }
    return myWorkout;
}

std::string CheapCustomer::toString() const
{
    return "chp";
}

Customer* CheapCustomer::clone()
{
    CheapCustomer* c = new CheapCustomer(*this);
    return c;
}

//CheapCustomer::~CheapCustomer() {
//
//}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) :Customer(name, id)
{
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout>& workout_options)
{
    std::vector<int> myWorkout;
    std::vector<Workout> workout;
    for (int i = 0; i < workout_options.size(); i++) {
        if (workout_options[i].getType() == WorkoutType::ANAEROBIC)
            workout.push_back(workout_options[i]);
    }
    std::sort(workout.begin(), workout.end());
    for(int i=0; i<workout.size(); i++){
        myWorkout.push_back(workout[i].getId());
    }
    workout.clear();
    return myWorkout;
}

std::string HeavyMuscleCustomer::toString() const
{
    return "mcl";
}

Customer* HeavyMuscleCustomer::clone()
{
    HeavyMuscleCustomer* c = new HeavyMuscleCustomer(*this);
    return c;
}

//HeavyMuscleCustomer::~HeavyMuscleCustomer() {
//
//}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) :Customer(name, id)
{
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout>& workout_options)
{
    std::vector<Workout> CardioWorkout;
    std::vector<Workout> MixWorkout;
    std::vector<Workout> AnaerobicWorkout;
    for (int i = 0;i < workout_options.size();i++) {
        if (workout_options[i].getType() == WorkoutType::ANAEROBIC)
            AnaerobicWorkout.push_back(workout_options[i]);
        else if (workout_options[i].getType() == WorkoutType::CARDIO)
            CardioWorkout.push_back(workout_options[i]);
        else
            MixWorkout.push_back(workout_options[i]);
    }
    std::vector<int> myWorkout;
    if (CardioWorkout.size() > 0) {
        int minpriceC = CardioWorkout[0].getPrice();
        int idminC = CardioWorkout[0].getId();
        for (int i = 1; i < CardioWorkout.size(); i++) {
            if ((minpriceC > CardioWorkout[i].getPrice()) || ((minpriceC == CardioWorkout[i].getPrice()) && (idminC > CardioWorkout[i].getId()))) {
                minpriceC = CardioWorkout[i].getPrice();
                idminC = CardioWorkout[i].getId();
            }
        }
        myWorkout.push_back(idminC);
    }
    if (MixWorkout.size() > 0) {
        int maxprice = MixWorkout[0].getPrice();
        int idmax = MixWorkout[0].getId();
        for (int i = 1; i < MixWorkout.size(); i++) {
            if ((maxprice < MixWorkout[i].getPrice()) || ((maxprice == MixWorkout[i].getPrice()) && (idmax > MixWorkout[i].getId()))) {
                maxprice = MixWorkout[i].getPrice();
                idmax = MixWorkout[i].getId();
            }
        }
        myWorkout.push_back(idmax);
    }
    if (AnaerobicWorkout.size() > 0) {
        int minpriceA = AnaerobicWorkout[0].getPrice();
        int idminA = AnaerobicWorkout[0].getId();
        for (int i = 1; i < AnaerobicWorkout.size(); i++) {
            if ((minpriceA > AnaerobicWorkout[i].getPrice()) || ((minpriceA == AnaerobicWorkout[i].getPrice()) && (idminA > AnaerobicWorkout[i].getId()))) {
                minpriceA = AnaerobicWorkout[i].getPrice();
                idminA = AnaerobicWorkout[i].getId();
            }
        }
        myWorkout.push_back(idminA);
    }
    return myWorkout;

}

std::string FullBodyCustomer::toString() const
{
    return "fbd";
}

Customer* FullBodyCustomer::clone()
{
    FullBodyCustomer* c = new FullBodyCustomer(*this);
    return c;
}

//FullBodyCustomer::~FullBodyCustomer() {
//
//}

