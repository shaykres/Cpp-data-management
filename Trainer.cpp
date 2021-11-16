//
// Created by Shay on 10/11/2021.
//
#include "Trainer.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity)
{
    open = false;

}

int Trainer::getCapacity() const
{
    return capacity;
}

void Trainer::addCustomer(Customer* customer)
{
    customersList.push_back(customer);
}

void Trainer::removeCustomer(int id)
{
    std::vector<Customer*> copy;
    while (!customersList.empty() && customersList.back()->getId() != id) {
        copy.push_back(customersList.back());
        customersList.pop_back();
    }

    if (!customersList.empty()) {
        customersList.pop_back();
    }

    while (!copy.empty()) {
        customersList.push_back(copy.back());
        copy.pop_back();
    }

    std::vector<OrderPair> copyOrder;
    for (int i = 0; i < orderList.size(); i++) {
        if(orderList[i].first!=id)
            copyOrder.push_back(orderList.back());
        orderList.pop_back();
    }
    for (int i = 0; i < copyOrder.size(); ++i) {
        orderList.push_back(copyOrder.back());
    }
    copy.clear();
    copyOrder.clear();
}

Customer* Trainer::getCustomer(int id)
{
    for (int i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id)
            return customersList[i];
    }
    return nullptr;

}

std::vector<Customer*>& Trainer::getCustomers()
{
    return customersList;
}

std::vector<OrderPair>& Trainer::getOrders()
{
    return orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options)
{
    for (int i = 0; i < workout_ids.size(); i++) {
        int j = 0;
        while (workout_options[j].getId() != workout_ids[i])
            j++;
        orderList.push_back(OrderPair(customer_id, workout_options[j]));
        std::cout << getCustomer(customer_id)<<" Is Doing "<< workout_options[j].getName() << std::endl;
    }
}

void Trainer::openTrainer()
{
    open = true;
}

void Trainer::closeTrainer()
{
    open = false;
    std::cout << "Trainer "<<getId() <<" closed. Salary "<< getSalary()<<"NIS" << std::endl;
    for (int i = 0; i < customersList.size(); i++) {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary()
{
    int sum = 0;
    for (int i = 0;i < orderList.size();i++) {
        sum = sum + orderList[i].second.getPrice();
    }
    return sum;
}

bool Trainer::isOpen()
{
    return open;
}

int Trainer::getId()
{
    return id;
}

Trainer::~Trainer()
{
    for (int i = 0; i < customersList.size(); i++)
        delete customersList[i];
    orderList.clear();
}

Trainer::Trainer(const Trainer& other):id(other.id), capacity(other.capacity), open(other.open) //orderList(other.orderList)
{
    for (int i = 0; i < other.customersList.size(); i++) {
        customersList.push_back(other.customersList[i]->clone());
    }
}

void Trainer::operator=(const Trainer& other)
{
    if (&other != this) {
        id = other.id;
        capacity = other.capacity;
        for (int i = 0; i < customersList.size(); i++)
            delete customersList[i];
        customersList.clear();
        for (int i = 0; i < other.customersList.size(); i++)
            customersList.push_back(other.customersList[i]->clone());
        orderList.clear();
        for (int i = 0; i < other.orderList.size(); i++) {
            orderList.push_back(OrderPair(other.orderList[i].first,other.orderList[i].second));
        }

    }
}

Trainer* Trainer::clone()
{
    Trainer* t = new Trainer(*this);
    return t;
}

void Trainer::setId(int Id) {
    id=Id;

}

