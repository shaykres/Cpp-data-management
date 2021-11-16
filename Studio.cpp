//
// Created by Shay on 10/11/2021.
//
#include "Studio.h"

Studio::Studio()
{
    open = true;
    /*trainers = std::vector<Trainer*>();
    workout_options=std::vector<Workout>() ;
    actionsLog=std::vector<BaseAction*>() ;*/

}

Studio::Studio(const std::string& configFilePath) {
    open = true;
    std::ifstream myfile(configFilePath);
    std::string line;
    std::vector<std::string> myInputs;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] != '#' && !line.empty()) {
                myInputs.push_back(line);
            }
//            std::cout << line << std::endl;
        }
        myfile.close();

        //printing
//        for (int i = 0; i < myInputs.size(); i++) {
//            std::cout << myInputs[i] << std::endl;
//        }

        int numOfTrainers = std::stoi(myInputs[0]);
        //printing
//        std::cout << numOfTrainers << std::endl;

        std::string s = myInputs[1];
        std::string delimiter = ",";
        std::vector<int> trainersC;
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            trainersC.push_back(std::stoi(token));
            s.erase(0, pos + delimiter.length());
        }
        trainersC.push_back(std::stoi(s));

        for (int i = 0; i < trainersC.size(); i++) {
            Trainer *t = new Trainer(trainersC[i]);
            t->setId(i);
            trainers.push_back(t);
        }

        //printing
//        for (int i = 0; i < trainers.size(); i++) {
//            std::cout << trainers[i]->getId() << "," << trainers[i]->getCapacity() << std::endl;
//        }

        int indexWorkout = 0;
        for (int i = 2; i < myInputs.size(); i++) {

            int loc = myInputs[i].find(delimiter);
            std::string workoutName = myInputs[i].substr(0, loc);
            while (!workoutName.empty() && std::isspace(*workoutName.begin()))
                workoutName.erase(workoutName.begin());
            while (!workoutName.empty() && std::isspace(*workoutName.rbegin()))
                workoutName.erase(workoutName.length() - 1);
            myInputs[i].erase(0, loc + 1);

            loc = myInputs[i].find(delimiter);
            std::string workouttype = myInputs[i].substr(0, loc);
            while (!workouttype.empty() && std::isspace(*workouttype.begin()))
                workouttype.erase(workouttype.begin());
            while (!workouttype.empty() && std::isspace(*workouttype.rbegin()))
                workouttype.erase(workouttype.length() - 1);
            myInputs[i].erase(0, loc + 1);

            loc = myInputs[i].find(delimiter);
            std::string workoutprice = myInputs[i].substr(0, loc);
            while (!workoutprice.empty() && std::isspace(*workoutprice.begin()))
                workoutprice.erase(workoutprice.begin());
            while (!workoutprice.empty() && std::isspace(*workoutprice.rbegin()))
                workoutprice.erase(workoutprice.length() - 1);

            if (std::equal(workouttype.begin(), workouttype.end(), "Anaerobic")) {
                Workout w(indexWorkout, workoutName, std::stoi(workoutprice), WorkoutType::ANAEROBIC);
                workout_options.push_back(w);
            } else if (std::equal(workouttype.begin(), workouttype.end(), "Mixed")) {
                Workout w(indexWorkout, workoutName, std::stoi(workoutprice), WorkoutType::MIXED);
                workout_options.push_back(w);
            } else {
                Workout w(indexWorkout, workoutName, std::stoi(workoutprice), WorkoutType::CARDIO);
                workout_options.push_back(w);
            }
            indexWorkout++;

        }
//        //printing
//        for (int i = 0; i < workout_options.size(); i++) {
//            std::cout << workout_options[i].getId() << "," << workout_options[i].getName()<<","<<workout_options[i].getType()<<","<< workout_options[i].getPrice()<< std::endl;
//        }
    }
    else std::cout << "Unable to open file";
}

void Studio::start()
{
    std::cout << "Studio is now open!" << std::endl;
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
    clear();

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

Studio::Studio(Studio &&other):open(other.open), trainers(other.trainers), workout_options(other.workout_options),
                               actionsLog(other.actionsLog) {
    other.trainers.clear();
    other.workout_options.clear();
    other.actionsLog.clear();

}

Studio &Studio::operator=(Studio &&other) {

    if(this!=&other){
        clear();
        open=other.open;
        workout_options=other.workout_options;
        trainers=other.trainers;
        actionsLog=other.actionsLog;
    }
    return *this;
}

void Studio::clear() {
    for (int i = 0; i < trainers.size(); i++)
        delete trainers[i];

    for (int i = 0; i < actionsLog.size(); i++)
        delete actionsLog[i];
}



