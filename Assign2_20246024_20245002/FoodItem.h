#pragma once
#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>

class FoodItem {
private:
	std::string itemName;
	double price;
	int quantity;

public:
	FoodItem() : itemName(""), price(0.0), quantity(0) {}
	FoodItem(const std::string& name, double p, int q);

	std::string getName() const { return itemName; }
	double getPrice() const { return price; }
	int getQuantity() const { return quantity; }

	// Declaration only here - definition lives in FoodItem.cpp
	double calculateItemTotal() const;
	void displayItem() const;
};

#endif