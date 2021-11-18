//
// Created by Shay on 10/11/2021.
//

#ifndef SPL_HW1_ACTION_H
#define SPL_HW1_ACTION_H
#include <string>
#include <iostream>
#include "Customer.h"
#include "Trainer.h"


enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
    virtual BaseAction* clone() = 0;
    BaseAction(const BaseAction& other);
    virtual ~BaseAction();
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;

};
#include "Studio.h"

class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    OpenTrainer(const OpenTrainer& other);
    ~OpenTrainer();
private:
    const int trainerId;
    std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    Order(const Order& other);
    //~Order();
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    MoveCustomer(const MoveCustomer& other);
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    Close(const Close& other);
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    CloseAll(const CloseAll& other);
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    PrintWorkoutOptions(const PrintWorkoutOptions& other);
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    PrintTrainerStatus(const PrintTrainerStatus& other);
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    PrintActionsLog(const PrintActionsLog& other);
    //~PrintActionsLog();
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    BackupStudio(const BackupStudio& other);
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;
    BaseAction* clone();
    RestoreStudio(const RestoreStudio& other);

};
#endif //SPL_HW1_ACTION_H
