#include "Order.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

int Order::totalOrders = 0;
int Order::staticInit = Order::initializeStatic();

void Order::resizeItemsArray() {
    capacity = std::max(1, capacity * 2);
    FoodItem* newItems = new FoodItem[capacity];

    for (int i = 0; i < itemCount; ++i) {
        newItems[i] = items[i];
    }

    delete[] items;
    items = newItems;
}

Order::Order()
    : orderId(""), customer(nullptr), driver(nullptr), itemCount(0), capacity(10), status(OrderStatus::PENDING) {
    items = new FoodItem[capacity];
    totalOrders++;
}

Order::Order(const string& id, Customer* cust)
    : orderId(id), customer(cust), driver(nullptr), itemCount(0), capacity(10), status(OrderStatus::PENDING) {
    items = new FoodItem[capacity];
    totalOrders++;
}

Order::Order(const Order& other)
    : orderId(other.orderId), customer(other.customer), driver(other.driver),
    itemCount(other.itemCount), capacity(other.capacity), status(other.status) {

    items = new FoodItem[capacity];
    for (int i = 0; i < itemCount; ++i) {
        items[i] = other.items[i];
    }
    totalOrders++;
}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        delete[] items;

        orderId = other.orderId;
        customer = other.customer;
        driver = other.driver;
        itemCount = other.itemCount;
        capacity = other.capacity;
        status = other.status;

        items = new FoodItem[capacity];
        for (int i = 0; i < itemCount; ++i) {
            items[i] = other.items[i];
        }
    }
    return *this;
}

Order::~Order() {
    delete[] items;
}

void Order::addItem(const FoodItem& item) {
    if (itemCount >= capacity) {
        resizeItemsArray();
    }
    items[itemCount++] = item;
}

void Order::assignDriver(DeliveryDriver* drv) {
    driver = drv;
    cout << "Order " << orderId << " assigned to Driver: " << drv->getName() << "\n";
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemCount; ++i) {
        total += items[i].calculateItemTotal();
    }
    return total;
}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
    cout << "Order " << orderId << " status updated to " << statusToString(newStatus) << "\n";

    if (newStatus == OrderStatus::DELIVERED) {
        double total = calculateTotal();

        if (driver) {
            driver->completeDelivery(total);
            cout << "Driver " << driver->getName() << " completed delivery and earned: " << total * 0.15 << " EGP\n";
        }

        if (customer) {
            int pointsToAdd = static_cast<int>(round(total / 2.0));
            (*customer) += pointsToAdd;
            cout << "Customer " << customer->getName() << " gained " << pointsToAdd << " loyalty points.\n";
        }
    }
}

void Order::displayOrder() const {
    cout << "\n======================================================\n";
    cout << "                   ORDER ID: " << orderId << "\n";
    cout << "======================================================\n";

    cout << "Status: " << statusToString(status) << "\n";
    cout << "Customer: " << (customer ? customer->getName() : "[N/A]") << "\n";
    cout << "Driver: " << (driver ? driver->getName() : "[Unassigned]") << "\n";

    cout << "\n--- Items (" << itemCount << ") ---\n";
    for (int i = 0; i < itemCount; ++i) {
        cout << "  - ";
        items[i].displayItem();
        cout << "\n";
    }

    cout << "\nTOTAL PRICE: " << fixed << setprecision(2) << calculateTotal() << " EGP\n";
    cout << "======================================================\n";
}

int Order::getTotalOrders() { return totalOrders; }

string Order::statusToString(OrderStatus s) {
    switch (s) {
    case OrderStatus::PENDING: return "PENDING";
    case OrderStatus::PREPARING: return "PREPARING";
    case OrderStatus::OUT_FOR_DELIVERY: return "OUT_FOR_DELIVERY";
    case OrderStatus::DELIVERED: return "DELIVERED";
    case OrderStatus::CANCELLED: return "CANCELLED";
    default: return "UNKNOWN";
    }
}

Order& Order::operator+=(const FoodItem& item) {
    addItem(item);
    return *this;
}

Order Order::operator+(const Order& other) const {
    Order combinedOrder("Combined_" + this->orderId + "_" + other.orderId, this->customer);

    for (int i = 0; i < this->itemCount; ++i) {
        combinedOrder.addItem(this->items[i]);
    }
    for (int i = 0; i < other.itemCount; ++i) {
        combinedOrder.addItem(other.items[i]);
    }
    return combinedOrder;
}

FoodItem& Order::operator[](int index) {
    if (index < 0 || index >= itemCount) {
        throw out_of_range("Order item index out of bounds (non-const).");
    }
    return items[index];
}

const FoodItem& Order::operator[](int index) const {
    if (index < 0 || index >= itemCount) {
        throw out_of_range("Order item index out of bounds (const).");
    }
    return items[index];
}

ostream& operator<<(ostream& os, const Order& order) {
    order.displayOrder();
    return os;
}

bool operator>(const Order& lhs, const Order& rhs) {
    return lhs.calculateTotal() > rhs.calculateTotal();
}