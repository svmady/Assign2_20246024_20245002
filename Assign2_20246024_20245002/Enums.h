#pragma once
#ifndef ENUMS_H
#define ENUMS_H

enum class OrderStatus {
    PENDING,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

enum class UserType {
    CUSTOMER,
    DRIVER
};

#endif