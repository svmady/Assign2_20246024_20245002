#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "Enums.h"
#include "FoodItem.h"
#include "User.h"
#include "Customer.h"
#include "DeliveryDriver.h"
#include "Order.h"
#include "DynamicArray.h" 
#include "file_operations.h"
#include "binary_operations.h"

using namespace std;



int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void displayMenu() {
    cout << "\n=================================================\n";
    cout << "  ELMENUS MANAGEMENT SYSTEM v1.0 (Dynamic Array)\n";
    cout << "=================================================\n";
    cout << "## USER MANAGEMENT\n";
    cout << " 1. Register New Customer\n";
    cout << " 2. Register New Delivery Driver\n";
    cout << "-------------------------------------------------\n";
    cout << "## ORDER MANAGEMENT\n";
    cout << " 3. Create New Order\n";
    cout << " 4. Add Items to Order\n";
    cout << " 5. Assign Driver to Order\n";
    cout << " 6. Update Order Status\n";
    cout << " 7. Display Order Details\n";
    cout << "-------------------------------------------------\n";
    cout << "## INFORMATION & REPORTS\n";
    cout << " 8. Display Customer Information\n";
    cout << " 9. Display Driver Information\n";
    cout << " 10. Compare Two Orders by Total\n";
    cout << " 11. Display System Statistics\n";
    cout << "-------------------------------------------------\n";
    cout << "## FILE OPERATIONS\n";
    cout << " 12. Save Completed Orders (Text File)\n";
    cout << " 13. Save Driver Statistics (Text File)\n";
    cout << "-------------------------------------------------\n";
    cout << "## BONUS: BINARY FILE OPERATIONS (O(1) Access)\n";
    cout << " 14. Save All Orders to Binary File (orders.dat)\n";
    cout << " 15. Load Order by Position (O(1) Retrieval)\n";
    cout << "-------------------------------------------------\n";
    cout << " 17. Exit System\n";
    cout << "=================================================\n";
}

int main() {

    DynamicArray<Customer*> customers;
    DynamicArray<DeliveryDriver*> drivers;
    DynamicArray<Order*> orders;

    int choice;
    do {
        displayMenu();
        choice = getIntInput("Enter your choice (1-17): ");

        try {
            switch (choice) {
            case 1: {
                string id = getStringInput("Enter Customer ID: ");
                string name = getStringInput("Enter Name: ");
                string phone = getStringInput("Enter Phone Number: ");
                string address = getStringInput("Enter Delivery Address: ");

                Customer* newCustomer = new Customer(id, name, phone, address);
                customers.add(newCustomer);
                newCustomer->displayInfo();
                break;
            }
            case 2: {
                string id = getStringInput("Enter Driver ID: ");
                string name = getStringInput("Enter Name: ");
                string phone = getStringInput("Enter Phone Number: ");
                string vehicle = getStringInput("Enter Vehicle Type: ");

                DeliveryDriver* newDriver = new DeliveryDriver(id, name, phone, vehicle);
                drivers.add(newDriver);
                newDriver->displayInfo();
                break;
            }
            case 3: {
                if (customers.getSize() == 0) { cout << "Error: No customers registered.\n"; break; }
                string orderId = getStringInput("Enter Order ID: ");
                string custId = getStringInput("Enter Customer ID for this order: ");

                Customer* selectedCustomer = nullptr;
                for (int i = 0; i < customers.getSize(); ++i) {
                    if (customers[i]->getUserId() == custId) {
                        selectedCustomer = customers[i];
                        break;
                    }
                }

                if (selectedCustomer) {
                    Order* newOrder = new Order(orderId, selectedCustomer);
                    orders.add(newOrder);
                    cout << "Order " << orderId << " created successfully.\n";
                }
                else {
                    cout << "Error: Customer ID not found.\n";
                }
                break;
            }
            case 4: {
                string orderId = getStringInput("Enter Order ID to modify: ");
                Order* currentOrder = nullptr;
                for (int i = 0; i < orders.getSize(); ++i) {
                    if (orders[i]->getOrderId() == orderId) {
                        currentOrder = orders[i];
                        break;
                    }
                }
                if (currentOrder) {
                    string name = getStringInput("Enter Item Name: ");
                    double price = getDoubleInput("Enter Price (EGP): ");
                    int quantity = getIntInput("Enter Quantity: ");
                    FoodItem newItem(name, price, quantity);
                    (*currentOrder) += newItem;
                    cout << "Item added. Current total: " << currentOrder->calculateTotal() << " EGP\n";
                }
                else {
                    cout << "Error: Order ID not found.\n";
                }
                break;
            }
            case 5: {
                string orderId = getStringInput("Enter Order ID: ");
                string driverId = getStringInput("Enter Driver ID to assign: ");
                Order* currentOrder = nullptr;
                DeliveryDriver* selectedDriver = nullptr;
                for (int i = 0; i < orders.getSize(); ++i) { if (orders[i]->getOrderId() == orderId) { currentOrder = orders[i]; break; } }
                for (int i = 0; i < drivers.getSize(); ++i) { if (drivers[i]->getUserId() == driverId) { selectedDriver = drivers[i]; break; } }

                if (currentOrder && selectedDriver) {
                    currentOrder->assignDriver(selectedDriver);
                    if (currentOrder->getStatus() < OrderStatus::OUT_FOR_DELIVERY) {
                        currentOrder->updateStatus(OrderStatus::OUT_FOR_DELIVERY);
                    }
                }
                else { cout << "Error: Order ID or Driver ID not found.\n"; }
                break;
            }
            case 6: {
                string orderId = getStringInput("Enter Order ID: ");
                Order* currentOrder = nullptr;
                for (int i = 0; i < orders.getSize(); ++i) { if (orders[i]->getOrderId() == orderId) { currentOrder = orders[i]; break; } }

                if (currentOrder) {
                    cout << "Available Statuses (0:PENDING, 1:PREPARING, 2:OUT_FOR_DELIVERY, 3:DELIVERED, 4:CANCELLED):\n";
                    int statusChoice = getIntInput("Enter new status number: ");

                    if (statusChoice >= 0 && statusChoice <= 4) {
                        currentOrder->updateStatus(static_cast<OrderStatus>(statusChoice));
                    }
                    else { cout << "Invalid status choice.\n"; }
                }
                else { cout << "Error: Order ID not found.\n"; }
                break;
            }
            case 7: {
                string orderId = getStringInput("Enter Order ID: ");
                bool found = false;
                for (int i = 0; i < orders.getSize(); ++i) {
                    if (orders[i]->getOrderId() == orderId) {
                        cout << (*orders[i]);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Error: Order ID not found.\n";
                break;
            }
            case 8: {
                string custId = getStringInput("Enter Customer ID: ");
                bool found = false;
                for (int i = 0; i < customers.getSize(); ++i) {
                    if (customers[i]->getUserId() == custId) {
                        customers[i]->displayInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Error: Customer ID not found.\n";
                break;
            }
            case 9: {
                string driverId = getStringInput("Enter Driver ID: ");
                bool found = false;
                for (int i = 0; i < drivers.getSize(); ++i) {
                    if (drivers[i]->getUserId() == driverId) {
                        drivers[i]->displayInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Error: Driver ID not found.\n";
                break;
            }
            case 10: {
                if (orders.getSize() < 2) { cout << "Error: Need at least two orders to compare.\n"; break; }
                string id1 = getStringInput("Enter ID of Order 1: ");
                string id2 = getStringInput("Enter ID of Order 2: ");
                Order* o1 = nullptr, * o2 = nullptr;
                for (int i = 0; i < orders.getSize(); ++i) {
                    if (orders[i]->getOrderId() == id1) o1 = orders[i];
                    if (orders[i]->getOrderId() == id2) o2 = orders[i];
                }
                if (o1 && o2) {
                    if (*o1 > *o2) { cout << "Result: Order " << id1 << " is more expensive than Order " << id2 << ".\n"; }
                    else if (*o2 > *o1) { cout << "Result: Order " << id2 << " is more expensive than Order " << id1 << ".\n"; }
                    else { cout << "Result: Same total price.\n"; }
                }
                else { cout << "Error: One or both Order IDs not found.\n"; }
                break;
            }
            case 11: {
                cout << "\n--- System Statistics ---\n";
                cout << "Total Registered Users: " << User::getTotalUsers() << "\n";
                cout << "Total Orders Created: " << Order::getTotalOrders() << "\n";
                cout << "Total Customers: " << customers.getSize() << "\n";
                cout << "Total Drivers: " << drivers.getSize() << "\n";
                double totalLoyaltyValue = 0.0;
                for (int i = 0; i < customers.getSize(); ++i) { totalLoyaltyValue += customers[i]->calculateEarnings(); }
                cout << "Total Loyalty Points Value: " << fixed << setprecision(2) << totalLoyaltyValue << " EGP\n";
                double totalDriverEarnings = 0.0;
                for (int i = 0; i < drivers.getSize(); ++i) { totalDriverEarnings += drivers[i]->calculateEarnings(); }
                cout << "Total Driver Earnings: " << fixed << setprecision(2) << totalDriverEarnings << " EGP\n";
                break;
            }

            case 12: {
                saveCompletedOrders(orders.getData(), orders.getSize());
                break;
            }
            case 13: {
                saveDriverStatistics(drivers.getData(), drivers.getSize());
                break;
            }

            case 14: {
                if (orders.getSize() == 0) { cout << "Error: No orders to save.\n"; break; }
                saveOrdersToBinary(orders.getData(), orders.getSize());
                break;
            }
            case 15: {
                if (orders.getSize() == 0) { cout << "Error: No orders to load. Save orders first (Option 14).\n"; break; }
                cout << "Total orders saved (0-indexed): " << orders.getSize() - 1 << endl;
                int position = getIntInput("Enter 0-indexed position of the order to retrieve: ");
                loadOrderByPosition(position, orders.getSize());
                break;
            }

            case 17: {
                cout << "Exiting system. Goodbye!\n";
                break;
            }

            default:
                cout << "Invalid choice.\n";
                break;
            }
        }
        catch (const exception& e) {
            cerr << "An error occurred: " << e.what() << "\n";
        }
        catch (...) {
            cerr << "An unknown error occurred.\n";
        }

    } while (choice != 17);

    cout << "\n--- Freeing Dynamic Memory ---\n";
    for (int i = 0; i < orders.getSize(); ++i) {
        delete orders[i];
    }
    for (int i = 0; i < customers.getSize(); ++i) {
        delete customers[i];
    }
    for (int i = 0; i < drivers.getSize(); ++i) {
        delete drivers[i];
    }
    cout << "All dynamic memory freed. System closed.\n";

    return 0;
}