#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
private:
	std::string deliveryAddress;
	int loyaltyPoints;

public:
	Customer();
	Customer(const std::string& id, const std::string& n, const std::string& phone,
		const std::string& address, int points = 0);

    void displayInfo() const override;
    double calculateEarnings() const override;

    Customer& operator+=(int points);

    std::string getDeliveryAddress() const { return deliveryAddress; }
    int getLoyaltyPoints() const { return loyaltyPoints; }

    ~Customer() override {}
};

#endif