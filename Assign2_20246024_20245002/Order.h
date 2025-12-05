#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "enums.h"
#include "FoodItem.h"
#include "Customer.h"
#include "DeliveryDriver.h"

class Order;
std::ostream& operator<<(std::ostream& os, const Order& order);
bool operator>(const Order& lhs, const Order& rhs);

class Order {
private:
    std::string orderId;
    Customer* customer;
    DeliveryDriver* driver;
    FoodItem* items;
    int itemCount;
    int capacity;
    OrderStatus status;
    static int totalOrders;

    void resizeItemsArray();

public:

    static int initializeStatic() { totalOrders = 0; return 0; }
    static int staticInit;

    Order();
    Order(const std::string& id, Customer* cust);
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();

    void addItem(const FoodItem& item);
    void assignDriver(DeliveryDriver* drv);
    double calculateTotal() const;
    void updateStatus(OrderStatus newStatus);
    void displayOrder() const;

    static int getTotalOrders();
    static std::string statusToString(OrderStatus s);

    std::string getOrderId() const { return orderId; }
    Customer* getCustomer() const { return customer; }
    DeliveryDriver* getDriver() const { return driver; }
    OrderStatus getStatus() const { return status; }
    int getItemCount() const { return itemCount; }

    Order& operator+=(const FoodItem& item);
    Order operator+(const Order& other) const;
    FoodItem& operator[](int index);
    const FoodItem& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
    friend bool operator>(const Order& lhs, const Order& rhs);
};

#endif