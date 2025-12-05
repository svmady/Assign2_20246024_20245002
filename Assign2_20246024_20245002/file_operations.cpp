#include "file_operations.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void saveCompletedOrders(Order** orders, int numOrders) {
    const string filename = "completed_orders.txt";
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    cout << "\n--- Saving Completed Orders to " << filename << " and Screen ---\n";
    file << "--- Completed Orders Report ---\n\n";

    for (int i = 0; i < numOrders; ++i) {
        Order* order = orders[i];
        if (order->getStatus() == OrderStatus::DELIVERED) {
            order->displayOrder();

            file << "Order ID: " << order->getOrderId() << "\n";
            file << "Customer: " << (order->getCustomer() ? order->getCustomer()->getName() : "N/A") << "\n";
            file << "Driver: " << (order->getDriver() ? order->getDriver()->getName() : "N/A") << "\n";
            file << "Total: " << fixed << setprecision(2) << order->calculateTotal() << " EGP\n";
            file << "--------------------------------\n";
        }
    }

    cout << "\nCompleted orders successfully saved.\n";
    file.close();
}

void saveDriverStatistics(DeliveryDriver** drivers, int numDrivers) {
    const string filename = "driver_stats.txt";
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    cout << "\n--- Saving Driver Statistics to " << filename << " and Screen ---\n";
    file << "--- Driver Statistics Report ---\n\n";

    for (int i = 0; i < numDrivers; ++i) {
        DeliveryDriver* driver = drivers[i];

        driver->displayInfo();

        file << "Driver ID: " << driver->getUserId() << "\n";
        file << "Name: " << driver->getName() << "\n";
        file << "Completed Deliveries: " << driver->getCompletedDeliveries() << "\n";
        file << "Total Earnings: " << fixed << setprecision(2) << driver->getTotalEarnings() << " EGP\n";
        file << "--------------------------------\n";
    }

    cout << "\nDriver statistics successfully saved.\n";
    file.close();
}