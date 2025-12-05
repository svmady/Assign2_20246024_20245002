#pragma once
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "Order.h"
#include "DeliveryDriver.h"

void saveCompletedOrders(Order** orders, int numOrders);
void saveDriverStatistics(DeliveryDriver** drivers, int numDrivers);

#endif