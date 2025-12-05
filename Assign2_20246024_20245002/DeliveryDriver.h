#pragma once
#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H

#include "User.h"

class DeliveryDriver : public User {
private:
    std::string vehicleType;
    int completedDeliveries;
    double totalEarnings;

public:
    // Constructors
    DeliveryDriver();
    DeliveryDriver(const std::string& id, const std::string& n, const std::string& phone,
        const std::string& vehicle);

    // Overridden Functions
    void displayInfo() const override;
    double calculateEarnings() const override;

    // Core Methods
    void completeDelivery(double orderValue);

    // Operator Overloading
    DeliveryDriver& operator++();    // Prefix
    DeliveryDriver operator++(int);  // Postfix

    // Getters
    std::string getVehicleType() const { return vehicleType; }
    int getCompletedDeliveries() const { return completedDeliveries; }
    double getTotalEarnings() const { return totalEarnings; }

    ~DeliveryDriver() override {}
};

#endif