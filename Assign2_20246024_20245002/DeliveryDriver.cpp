#include "DeliveryDriver.h"
#include <iostream>
#include <iomanip>

using namespace std;

DeliveryDriver::DeliveryDriver()
    : User(), vehicleType(""), completedDeliveries(0), totalEarnings(0.0) {
}

DeliveryDriver::DeliveryDriver(const string& id, const string& n, const string& phone,
    const string& vehicle)
    : User(id, n, phone), vehicleType(vehicle), completedDeliveries(0), totalEarnings(0.0) {
}

void DeliveryDriver::displayInfo() const {
    double avgEarnings = (completedDeliveries > 0)
        ? totalEarnings / completedDeliveries
        : 0.0;

    cout << "\n--- Delivery Driver Details ---\n";
    cout << "ID: " << userId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Phone: " << phoneNumber << "\n";
    cout << "Vehicle Type: " << vehicleType << "\n";
    cout << "Completed Deliveries: " << completedDeliveries << "\n";
    cout << "Total Earnings: " << fixed << setprecision(2) << totalEarnings << " EGP\n";
    cout << "Avg. Earnings per Delivery: " << fixed << setprecision(2) << avgEarnings << " EGP\n";
}

double DeliveryDriver::calculateEarnings() const {
    return totalEarnings;
}

void DeliveryDriver::completeDelivery(double orderValue) {
    totalEarnings += orderValue * 0.15;
    completedDeliveries++;
}

DeliveryDriver& DeliveryDriver::operator++() {
    completedDeliveries++;
    return *this;
}

DeliveryDriver DeliveryDriver::operator++(int) {
    DeliveryDriver temp = *this;
    completedDeliveries++;
    return temp;
}