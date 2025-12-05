#include "binary_operations.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <iomanip>

using namespace std;

void saveOrdersToBinary(Order** orders, int numOrders) {
    const string filename = "orders.dat";
    ofstream file(filename, ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Error: Could not open binary file " << filename << " for writing.\n";
        return;
    }

    for (int i = 0; i < numOrders; ++i) {
        Order* order = orders[i];
        OrderRecord record;

        strncpy_s(record.orderId, order->getOrderId().c_str(), 29);
        record.orderId[29] = '\0';

        string custName = order->getCustomer() ? order->getCustomer()->getName() : "N/A";
        strncpy_s(record.customerName, custName.c_str(), 49);
        record.customerName[49] = '\0';

        string drvName = order->getDriver() ? order->getDriver()->getName() : "Unassigned";
        strncpy_s(record.driverName, drvName.c_str(), 49);
        record.driverName[49] = '\0';

        record.total = order->calculateTotal();
        record.status = static_cast<int>(order->getStatus());

        file.write(reinterpret_cast<const char*>(&record), sizeof(OrderRecord));
    }

    file.close();
    cout << "Successfully saved " << numOrders << " orders to binary file " << filename << ".\n";
}

void loadOrderByPosition(int position, int numOrders) {
    const string filename = "orders.dat";
    ifstream file(filename, ios::in | ios::binary);

    if (!file.is_open()) {
        cerr << "Error: Could not open binary file " << filename << " for reading.\n";
        return;
    }
    if (position < 0 || position >= numOrders) {
        cerr << "Error: Invalid position. Position must be between 0 and " << numOrders - 1 << ".\n";
        file.close();
        return;
    }

    // Start time measurement
    auto start = chrono::high_resolution_clock::now();

    // Calculate the byte offset: O(1) calculation
    long offset = static_cast<long>(position) * sizeof(OrderRecord);

    // Use seekg() to jump directly to the record: O(1) disk access
    file.seekg(offset, ios::beg);

    OrderRecord record;
    file.read(reinterpret_cast<char*>(&record), sizeof(OrderRecord));

    // Stop time measurement
    auto end = chrono::high_resolution_clock::now();

    file.close();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    // Display results
    cout << "\n--- Binary Order Retrieval (O(1) Access) ---\n";
    cout << "Retrieving Order at Position (0-indexed): " << position << "\n";
    cout << "Order ID: " << record.orderId << "\n";
    cout << "Customer: " << record.customerName << "\n";
    cout << "Driver: " << record.driverName << "\n";
    cout << "Total: " << fixed << setprecision(2) << record.total << " EGP\n";
    cout << "Status: " << Order::statusToString(static_cast<OrderStatus>(record.status)) << "\n";

    // Display time taken
    cout << "\n*** Time Taken (Proving O(1) Access): " << duration.count() << " nanoseconds ***\n";
    cout << "------------------------------------------------\n";
}