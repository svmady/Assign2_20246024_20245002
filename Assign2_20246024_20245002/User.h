#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include "Enums.h"

class User {
protected:
        std::string userId;
        std::string name;
        std::string phoneNumber;
        static int totalUsers;
public:
    User();
    User(const std::string& id, const std::string& n, const std::string& phone);

    virtual void displayInfo() const = 0;
    virtual double calculateEarnings() const = 0;

    static int getTotalUsers();

    std::string getUserId() const { return userId; }
    std::string getName() const { return name; }

    virtual ~User();
};


#endif