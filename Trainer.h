//
// Created by Shay on 10/11/2021.
//

#ifndef SPL_HW1_TRAINER_H
#define SPL_HW1_TRAINER_H
#include <vector>
#include "Customer.h"
#include "Workout.h"
#include <iostream>

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();
    int getId();
    void setId(int Id);
    ~Trainer();
    void clear();
    Trainer(const Trainer& other);
    void operator=(const Trainer& other);
    Trainer* clone();
    Trainer(Trainer&& other);
    Trainer& operator=(Trainer &&other);
    std::vector<OrderPair> getCustomerOrder(int Customerid);
    void addCustomerOrders(std::vector<OrderPair> CustomerOrders);
    void updateSalary();
    void printorderList();
private:
    int id;
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    int salary;
};

#endif //SPL_HW1_TRAINER_H
