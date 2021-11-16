//
// Created by Shay on 10/11/2021.
//
#include "Studio.h"
#include <fstream>
#include <sstream>

Studio::Studio()
{
    open = true;
    id=0;
    /*trainers = std::vector<Trainer*>();
    workout_options=std::vector<Workout>() ;
    actionsLog=std::vector<BaseAction*>() ;*/
}

Studio::Studio(const std::string& configFilePath)
{
    Studio();
    std::ifstream myfile(configFilePath);
    std::string line;
    std::vector<std::string> myInputs;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] != '#' & line[0] != ' ') {
                myInputs.push_back(line);
            }
        }
        myfile.close();
    }

//        int numOfTrainers = std::stoi(myInputs[0]);
//        int j = 0;
//        for (int i = 0; i < myInputs[1].length() && j < numOfTrainers; i = i + 2) {
//            Trainer *t = new Trainer(myInputs[1][i]);
//            t->setId(j);
//            j++;
//            trainers.push_back(t);
//        }
//
//        std::string delimiter = ",";
//        for(int i=3; i<myInputs.size(); i++){
//            int firstcome=myInputs[i].find(delimiter);
//            std::string workoutName = myInputs[i].substr(0, firstcome);
//            std::string workouttype = myInputs[i].substr(firstcome+1, myInputs[i].find(delimiter));
//            std::string workoutprice = myInputs[i].substr(workoutName.length()+workouttype.length()+2, myInputs[i].find(delimiter));
//        }
//    }
    else std::cout << "Unable to open file";
}

void Studio::start()
{
    std::cout << "Studio is now open!" << std::endl;
    while(this->open){
        char command[500];
        std::cin.getline(command,500);
        BaseAction* act=buildAction(command);
        act->act(*this);
    }
}
BaseAction* Studio::buildAction(char* command){
    std::string action;
    int j=0;
    while(command[j] != ' '){
        action=action+command[j];
        j++;
    }
    j++;
    for (int i=0; i<j ; ++i)
        command[i] = command[j+i];
    BaseAction* a;
    if(action=="open"){
       char id =command[0];
    }
    a=new Order(2);
    return a;
}
Customer* Studio:: buildCustomer(char* command){
    char *type;
    type = strtok (command,",");
    Customer *c;
    if(type=="swt"){
        c=new SweatyCustomer(command,id);
    }
    else if(type=="chp"){
        c=new CheapCustomer(command,id);
    }
    else if(type=="mcl"){
        c=new HeavyMuscleCustomer(command,id);
    }
    else
        c=new FullBodyCustomer(command,id);
    id=id+1;
    return c;
}

int Studio::getNumOfTrainers() const
{
    return trainers.size();
}

Trainer* Studio::getTrainer(int tid)
{
    for (int i = 0; i < trainers.size(); i++) {
        if (trainers[i]->getId() == tid)
            return trainers[i];
    }
    return nullptr;
}

const std::vector<BaseAction*>& Studio::getActionsLog() const
{
    return actionsLog;
}

std::vector<Workout>& Studio::getWorkoutOptions()
{
    return workout_options;
}

void Studio::closeStudio()
{
    open = false;
    delete this;
}

Studio::~Studio()
{
    for (int i = 0; i < trainers.size(); i++)
        delete trainers[i];

    for (int i = 0; i < actionsLog.size(); i++)
        delete actionsLog[i];
}

Studio::Studio(const Studio& other):open(other.open)
{
    for (int i = 0; i < other.trainers.size(); i++) {
        trainers.push_back(other.trainers[i]->clone());
    }

    for (int i = 0; i < other.actionsLog.size(); i++) {
        actionsLog.push_back(other.actionsLog[i]->clone());
    }
    for (int i = 0; i < other.workout_options.size(); i++) {
        workout_options.push_back(other.workout_options[i]);
    }


}

void Studio::operator=(const Studio& other)
{
    if (&other != this) {
        open = other.open;
        workout_options.clear();
        for (int i = 0; i < other.workout_options.size(); i++) {
            workout_options.push_back(other.workout_options[i]);
        }

        for (int i = 0; i < trainers.size(); i++)
            delete trainers[i];
        trainers.clear();
        for (int i = 0; i < other.trainers.size(); i++)
            trainers.push_back(other.trainers[i]->clone());

        for (int i = 0; i < actionsLog.size(); i++)
            delete actionsLog[i];
        actionsLog.clear();
        for (int i = 0; i < other.actionsLog.size(); i++)
            actionsLog.push_back(other.actionsLog[i]->clone());

    }
}

