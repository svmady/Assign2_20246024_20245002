#include "FoodItem.h"
#include <iostream>
#include <iomanip>

using namespace std;

FoodItem::FoodItem(const string& name, double p, int q)
    : itemName(name), price(p), quantity(q) {
}

double FoodItem::calculateItemTotal() const {
    return price * quantity;
}

void FoodItem::displayItem() const {
    cout << itemName
        << " x" << quantity
        << " @ " << fixed << setprecision(2) << price
        << " EGP = " << fixed << setprecision(2) << calculateItemTotal() << " EGP";
}