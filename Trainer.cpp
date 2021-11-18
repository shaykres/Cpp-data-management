//
// Created by Shay on 10/11/2021.
//
#include "Trainer.h"

Trainer::Trainer(int t_capacity) : capacity(t_capacity)
{
    open = false;
    salary=0;

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
            copyOrder.push_back(orderList[i]);
        else
            salary=salary-orderList[i].second.getPrice();
        //orderList.pop_back();
    }
    orderList.clear();
    for (int i = 0; i < copyOrder.size(); i++) {
        orderList.push_back(copyOrder[i]);
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
    return salary;
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
    clear();

}

Trainer::Trainer(const Trainer& other):id(other.id), capacity(other.capacity), open(other.open),salary(other.salary) ,orderList(other.orderList)
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
        salary=other.salary;
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

Trainer::Trainer(Trainer &&other):id(other.id), capacity(other.capacity), open(other.open),salary(other.salary),customersList(other.customersList),
    orderList(other.orderList){
    other.customersList.clear();
    other.orderList.clear();

}

Trainer &Trainer::operator=(Trainer &&other) {
    if(this!=&other){
        clear();
        id=other.id;
        capacity=other.capacity;
        salary=other.salary;
        open=other.open;
        customersList=other.customersList;
        orderList=other.orderList;
    }
    return *this;
}

void Trainer::clear() {
    for (int i = 0; i < customersList.size(); i++)
        delete customersList[i];
    orderList.clear();
}

std::vector<OrderPair> Trainer::getCustomerOrder(int Customerid) {
    std::vector<OrderPair> customerOrders;
    for(int i=0; i<orderList.size(); i++){
        if(orderList[i].first==Customerid)
            customerOrders.push_back(orderList[i]);
    }
    return customerOrders;
}

void Trainer::addCustomerOrders(std::vector<OrderPair> CustomerOrders) {

    for(int i=0; i<CustomerOrders.size(); i++){
        orderList.push_back(CustomerOrders[i]);
        updateSalary(CustomerOrders[i]);
    }

}

void Trainer::updateSalary(OrderPair pair) {
    salary=salary+pair.second.getPrice();
}

void Trainer::updateSalary() {
    for(int i=0;i<orderList.size();i++){
        salary = salary + orderList[i].second.getPrice();
    }
}

void Trainer::printorderList() {
    for(int i=0;i<orderList.size();i++)
        std::cout<< getCustomer(orderList[i].first)->getName()<<" Is Doing "<< orderList[i].second.getName() << std::endl;
}


