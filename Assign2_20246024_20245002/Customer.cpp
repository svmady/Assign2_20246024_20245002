#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer() : User(), deliveryAddress(""), loyaltyPoints(0) {}

Customer::Customer(const string& id, const string& n, const string& phone,
    const string& address, int points)
    : User(id, n, phone), deliveryAddress(address), loyaltyPoints(points) {
}

void Customer::displayInfo() const {
    cout << "\n--- Customer Details ---\n";
    cout << "ID: " << userId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Phone: " << phoneNumber << "\n";
    cout << "Address: " << deliveryAddress << "\n";
    cout << "Loyalty Points: " << loyaltyPoints << "\n";
    cout << "Estimated Earnings (Points Value): " << calculateEarnings() << " EGP\n";
}

double Customer::calculateEarnings() const {
    return loyaltyPoints * 0.5;
}

Customer& Customer::operator+=(int points) {
    loyaltyPoints += points;
    return *this;
}