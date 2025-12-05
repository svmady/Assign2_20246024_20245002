#pragma once
#ifndef BINARY_OPERATIONS_H
#define BINARY_OPERATIONS_H

#include "Order.h"
#include <string>

struct OrderRecord {
    char orderId[30];
    char customerName[50];
    char driverName[50];
    double total;
    int status;
};

void saveOrdersToBinary(Order** orders, int numOrders);

void loadOrderByPosition(int position, int numOrders);

#endif