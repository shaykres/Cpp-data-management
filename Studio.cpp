//
// Created by Shay on 10/11/2021.
//
#include "Studio.h"

Studio::Studio() {
    open = true;
    /*trainers = std::vector<Trainer*>();
    workout_options=std::vector<Workout>() ;
    actionsLog=std::vector<BaseAction*>() ;*/

}

Studio::Studio(const std::string &configFilePath) {
    open = true;
    std::ifstream myfile(configFilePath);
    std::string line;
    std::vector<std::string> myInputs;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line[0] != '#' && !line.empty()) {
                myInputs.push_back(line);
            }
        }
        myfile.close();
        int numOfTrainers = std::stoi(myInputs[0]);
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
    } else std::cout << "Unable to open file";
}

void Studio::start() {
    std::cout << "Studio is now open!" << std::endl;
    while (this->open) {
        char command[500];
        std::cin.getline(command, 500);
        BaseAction *act = buildAction(command);
        act->act(*this);
        actionsLog.push_back(act);
    }
}

BaseAction *Studio::buildAction(char *command) {
    std::string action;
    int j = 0;
    while (j < strlen(command) && command[j] != ' ') {
        action = action + command[j];
        j++;
    }
    j++;
    for (int i = 0; i < strlen(command) - j; ++i)
        command[i] = command[j + i];

    std::cout << command << std::endl;

    BaseAction *a;
    switch (hashit(action)) {
        case string_code::open: {
            int commandlenth=strlen(command) - j;

            command[commandlenth] = '\0';

            //std::cout << command << std::endl;

            std::string idt;
            std::vector<Customer *> customers;
            int idlen = 0;
            while (command[idlen] != ' ') {
                idt = idt + command[idlen];
                idlen++;
            }
            idlen++;
            commandlenth=commandlenth-idlen;
            for (int i = 0; i < commandlenth; ++i)
                command[i] = command[idlen + i];
            command[commandlenth] = '\0';
            int trainerid = std::stoi(idt);

            int indexCommand = 0;
            int capacity= getTrainer(trainerid)->getCapacity();
            while (indexCommand < commandlenth&&capacity>0) {
                std::string myCoustomer;
                while (command[indexCommand] != ' ' && indexCommand < commandlenth) {
                    myCoustomer = myCoustomer + command[indexCommand];
                    indexCommand++;
                }
                indexCommand++;
               // std::cout << command << std::endl;
                //std::cout << myCoustomer << std::endl;
                commandlenth = commandlenth - indexCommand;
                for (int i = 0; i < commandlenth; ++i)
                    command[i] = command[indexCommand + i];
                command[commandlenth ] = '\0';
                indexCommand = 0;
                customers.push_back(buildCustomer(myCoustomer));
                capacity--;
            }
//            for(int i=0; i<customers.size(); i++){
//                std::cout << customers[i]->getId()<<","<<customers[i]->getName() << customers[i]->toString()<<std::endl;
//            }
            a = new OpenTrainer(trainerid, customers);
            break;
        }


        case string_code::order: {
            int id = std::stoi(command);
            //std::cout << id << std::endl;
            a = new Order(id);
            break;
        }


        case string_code::move: {
            int idsrc = std::stoi(command);
            for (int i = 0; i < 3; ++i)
                command[i] = command[i + 2];
            int iddst = std::stoi(command);
            for (int i = 0; i < 3; ++i)
                command[i] = command[i + 2];
            int cid = std::stoi(command);
            a = new MoveCustomer(idsrc, iddst, cid);
            break;
        }


        case string_code::close: {
            int id = std::stoi(command);
            a = new Close(id);
            break;
        }

        case string_code::closeall: {
            std::cout << "Studio is now closed!" << std::endl;
            a = new CloseAll();
            break;
        }

        case string_code::workout_options:
            a = new PrintWorkoutOptions();
            break;
        case string_code::status: {
            int id = std::stoi(command);
            a = new PrintTrainerStatus(id);
            break;
        }
        case string_code::mylog:
            a = new PrintActionsLog();
            break;
        case string_code::mybackup:
            a = new BackupStudio();
            break;
        case string_code::restore:
            a = new RestoreStudio();
            break;
        default:;

    }

    return a;
}

Customer *Studio::buildCustomer(std::string myCoustomer) {
    std::string type;
    std::string CustomerName;
    int comma = myCoustomer.find(",");
    CustomerName = myCoustomer.substr(0, comma);
    type = myCoustomer.substr(comma + 1, myCoustomer.size());

    Customer *c;
    if (std::equal(type.begin(), type.end(), "swt")) {
        c = new SweatyCustomer(CustomerName, create_id());
    } else if (std::equal(type.begin(), type.end(), "chp")) {
        c = new CheapCustomer(CustomerName, create_id());
    } else if (std::equal(type.begin(), type.end(), "mcl")) {
        c = new HeavyMuscleCustomer(CustomerName, create_id());
    } else
        c = new FullBodyCustomer(CustomerName, create_id());
    return c;
}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    for (int i = 0; i < trainers.size(); i++) {
        if (trainers[i]->getId() == tid)
            return trainers[i];
    }
    return nullptr;
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

void Studio::closeStudio() {
    open = false;
    clear();
}

Studio::~Studio() {
    clear();
}

Studio::Studio(const Studio &other) : open(other.open) {
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

void Studio::operator=(const Studio &other) {
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

string_code Studio::hashit(const std::string &inString) {
    if (inString == "open") return string_code::open;
    if (inString == "order") return string_code::order;
    if (inString == "move") return string_code::move;
    if (inString == "close") return string_code::close;
    if (inString == "closeall") return string_code::closeall;
    if (inString == "workout_options") return string_code::workout_options;
    if (inString == "status") return string_code::status;
    if (inString == "log") return string_code::mylog;
    if (inString == "backup") return string_code::mybackup;
    if (inString == "restore") return string_code::restore;
}

int Studio::create_id() {
    static std::atomic<int> id{-1};
    return id.fetch_add(1, std::memory_order_relaxed) + 1;

}

void Studio::clear() {
    for (int i = 0; i < trainers.size(); i++)
        delete trainers[i];

    for (int i = 0; i < actionsLog.size(); i++)
        delete actionsLog[i];
}

