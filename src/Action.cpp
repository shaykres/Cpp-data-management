
// Created by Shay on 10/11/2021.
//
#include "../include/Action.h"

extern Studio* backup;

BaseAction::BaseAction():errorMsg(""), status(ActionStatus::ERROR)
{

}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

BaseAction::BaseAction(const BaseAction& other):errorMsg(other.errorMsg), status(other.status)
{
}

void BaseAction::complete()
{
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg)
{
    this->errorMsg = errorMsg;
    status = ERROR;
    std::cout << getErrorMsg() << std::endl;
}

std::string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

BaseAction::~BaseAction() {
    std::cout << "base action distructor" << std::endl;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer*>& customersList):trainerId(id), customers(customersList)
{

}

void OpenTrainer::act(Studio& studio)
{
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr|| t->isOpen()){
        error( "Workout session does not exist or is already open");
    }
    else {
        t->openTrainer();
        ;for (int i = 0; i < customers.size(); i++) {
            t->addCustomer(customers[i]);
        }
        complete();
    }
}

std::string OpenTrainer::toString() const
{
    std::string str = "open ";
    str=str+std::to_string(trainerId);
    for (int i = 0;i < customers.size();i++) {
        str=str+" "+customers[i]->getName()+","+ customers[i]->toString();
    }
    if (getStatus() == COMPLETED)
        str = str + " Completed";
    else
        str = str + " Error:" + getErrorMsg();
    return str;
}

BaseAction* OpenTrainer::clone()
{
    OpenTrainer* op = new OpenTrainer(*this);
    return op;
}

OpenTrainer::OpenTrainer(const OpenTrainer& other):BaseAction(other),trainerId(other.trainerId)
{
    for (int i = 0; i < other.customers.size(); i++) {
        customers.push_back(other.customers[i]->clone());
    }
}

OpenTrainer::~OpenTrainer()
{
    customers.clear();
}

Order::Order(int id):trainerId(id)
{

}

void Order::act(Studio& studio)
{
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !t->isOpen()) {
        error("Trainer does not exist or is not open");
    }
    else {
        if (t->getOrders().empty()) {
            std::vector<Customer *> trainerCustomerl = t->getCustomers();
            std::vector<Workout> workout_options = studio.getWorkoutOptions();
            for (int i = 0; i < trainerCustomerl.size(); i++)
                t->order(trainerCustomerl[i]->getId(), trainerCustomerl[i]->order(workout_options), workout_options);
            t->updateSalary();
        }
        t->printorderList();
        complete();
    }
}

std::string Order::toString() const
{
    std::string str = "order ";
    str=str+std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        str = str + " Completed";
    else
        str = str + " Error:" + getErrorMsg();
    return str;
}

BaseAction* Order::clone()
{
    Order* o = new Order(*this);
    return o;
}

Order::Order(const Order& other) :BaseAction(other), trainerId(other.trainerId)
{
}

//Order::~Order() {
//    std::cout << "order distructor" << std::endl;
//}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src), dstTrainer(dst), id(customerId)
{
}

void MoveCustomer::act(Studio& studio)
{
    Trainer* tsrc = studio.getTrainer(srcTrainer);
    Trainer* tdst = studio.getTrainer(dstTrainer);
    if (tsrc == nullptr || !tsrc->isOpen()|| tdst == nullptr || !tdst->isOpen()|| tsrc->getCustomer(id)==nullptr|| tdst->getCapacity() == tdst->getCustomers().size())
        error("Cannot move customer");
    else {
        Customer* c = tsrc->getCustomer(id);
        std::vector<OrderPair> orderList=tsrc->getCustomerOrder(id);
        tsrc->removeCustomer(id);
        if (tsrc->getCustomers().size() == 0)
            tsrc->closeTrainer();
        tdst->addCustomer(c);
        tdst->addCustomerOrders(orderList);
        complete();
    }
}

std::string MoveCustomer::toString() const
{
    std::string str = "move ";
    str=str+std::to_string(srcTrainer)+" "+std::to_string(dstTrainer)+" "+std::to_string(id);
    if (getStatus() == COMPLETED)
        str = str + " Completed";
    else
        str = str + " Error:" + getErrorMsg();
    return str;
}

BaseAction* MoveCustomer::clone()
{
    MoveCustomer* mc = new MoveCustomer(*this);
    return mc;
}

MoveCustomer::MoveCustomer(const MoveCustomer& other) :BaseAction(other), srcTrainer(other.srcTrainer),
                                                       dstTrainer(other.dstTrainer), id(other.id)
{
}

Close::Close(int id):trainerId(id)
{
}

void Close::act(Studio& studio)
{
    Trainer* t = studio.getTrainer(trainerId);
    if (t == nullptr || !t->isOpen())
        error("Trainer does not exist or is not open");
    else {
        t->closeTrainer();
        complete();
    }
}

std::string Close::toString() const
{
    std::string str = "close ";
    str=str+std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        str = str + " Completed";
    else
        str = str + " Error:" + getErrorMsg();
    return str;
}

BaseAction* Close::clone()
{
    Close* c = new Close(*this);
    return c;
}

Close::Close(const Close& other):BaseAction(other), trainerId(other.trainerId)
{
}

CloseAll::CloseAll()
{

}

void CloseAll::act(Studio& studio)
{
    std::cout << "S" << std::endl;
    for (int i = 0; i < studio.getNumOfTrainers(); i++) {
        if (studio.getTrainer(i)->isOpen()) {
            BaseAction* close=new Close(i);
            close->act(studio);
        }
    }
    studio.closeStudio();
    std::cout << "Studio is now closed!" << std::endl;
    //complete();
}

std::string CloseAll::toString() const
{
    std::string str = "closeall Completed";
    return str;
}

BaseAction* CloseAll::clone()
{
    CloseAll* cl = new CloseAll(*this);
    return cl;
}

CloseAll::CloseAll(const CloseAll& other) :BaseAction(other)
{
}

PrintWorkoutOptions::PrintWorkoutOptions()
{
}

void PrintWorkoutOptions::act(Studio& studio)
{
    for (int i = 0; i < studio.getWorkoutOptions().size(); i++) {
        std::cout << studio.getWorkoutOptions()[i].toString() << std::endl;
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const
{
    std::string str = "workout_options Completed";
    return str;
}

BaseAction* PrintWorkoutOptions::clone()
{
    PrintWorkoutOptions* pwo = new PrintWorkoutOptions(*this);
    return pwo;
}

PrintWorkoutOptions::PrintWorkoutOptions(const PrintWorkoutOptions& other):BaseAction(other)
{
}

PrintTrainerStatus::PrintTrainerStatus(int id):trainerId(id)
{
}

void PrintTrainerStatus::act(Studio& studio)
{
    Trainer* t = studio.getTrainer(trainerId);
    if(t!=nullptr){
        if (!t->isOpen())
            std::cout << "Trainer " << trainerId << " status: closed" << std::endl;
        else {
            std::cout << "Trainer " << trainerId << " status: open" << std::endl;
            std::cout << "Customers:" << std::endl;
            for (int i = 0;i < t->getCustomers().size();i++) {
                std::cout << t->getCustomers()[i]->getId() <<" "<< t->getCustomers()[i]->getName() << std::endl;
            }
            std::cout << "Orders:" << std::endl;
            for (int i = 0;i < t->getOrders().size();i++) {
                std::cout << t->getOrders()[i].second.getName()<<" "<< t->getOrders()[i].second.getPrice() << "NIS " << t->getOrders()[i].first << std::endl;
            }
            std::cout << "Current Trainer's Salary: " <<t->getSalary()<<"NIS"<< std::endl;
        }
    }
    complete();
}

std::string PrintTrainerStatus::toString() const
{
    std::string str = "status ";
    str=str+std::to_string(trainerId)+ " Completed";
    return str;
}

BaseAction* PrintTrainerStatus::clone()
{
    PrintTrainerStatus* pts = new PrintTrainerStatus(*this);
    return pts;
}

PrintTrainerStatus::PrintTrainerStatus(const PrintTrainerStatus& other) :BaseAction(other), trainerId(other.trainerId)
{
}

PrintActionsLog::PrintActionsLog()
{
}

void PrintActionsLog::act(Studio& studio)
{
    for (int i = 0; i < studio.getActionsLog().size(); i++) {
        std::cout<<studio.getActionsLog()[i]->toString()<<std::endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const
{
    std::string str = "log Completed";
    return str;
}

BaseAction* PrintActionsLog::clone()
{
    PrintActionsLog* pal = new PrintActionsLog(*this);
    return pal;
}

PrintActionsLog::PrintActionsLog(const PrintActionsLog& other):BaseAction(other)
{
}

//PrintActionsLog::~PrintActionsLog() {
//    std::cout << "log distructor" << std::endl;
//}

BackupStudio::BackupStudio()
{
}

void BackupStudio::act(Studio& studio)
{
    backup=new Studio(studio);
    complete();
}

std::string BackupStudio::toString() const
{
    return "backup "+getStatus();
}

BaseAction* BackupStudio::clone()
{
    BackupStudio* bs = new BackupStudio(*this);
    return bs;
}

BackupStudio::BackupStudio(const BackupStudio& other):BaseAction(other)
{
}

RestoreStudio::RestoreStudio()
{
}

void RestoreStudio::act(Studio& studio)
{
    if (backup == nullptr)
        error("No backup available");
    else {
        studio = *backup;
        backup = nullptr;
        complete();
    }
}

std::string RestoreStudio::toString() const
{
    return "restore " + getStatus();
}

BaseAction* RestoreStudio::clone()
{
    RestoreStudio* rs = new RestoreStudio(*this);
    return rs;
}

RestoreStudio::RestoreStudio(const RestoreStudio& other):BaseAction(other)
{
}

