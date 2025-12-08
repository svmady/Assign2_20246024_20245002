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

    DeliveryDriver();
    DeliveryDriver(const std::string& id, const std::string& n, const std::string& phone,
        const std::string& vehicle);

    void displayInfo() const override;
    double calculateEarnings() const override;

    void completeDelivery(double orderValue);

    DeliveryDriver& operator++();
    DeliveryDriver operator++(int);

    std::string getVehicleType() const { return vehicleType; }
    int getCompletedDeliveries() const { return completedDeliveries; }
    double getTotalEarnings() const { return totalEarnings; }

    ~DeliveryDriver() override {}
};

#endif