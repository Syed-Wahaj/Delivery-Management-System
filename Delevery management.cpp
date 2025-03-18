#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Order {
    int orderID;
    string customerName;
    string address;
    double packageWeight;
    string status;
    string assignedDriver;
    double deliveryCharge;
};

vector<Order> orders;

double calculateDeliveryCharge(double weight) {
    return weight * 5.0; // Example: $5 per kg
}

void addOrder() {
    Order newOrder;
    cout << "Enter Order ID: ";
    cin >> newOrder.orderID;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, newOrder.customerName);
    cout << "Enter Address: ";
    getline(cin, newOrder.address);
    cout << "Enter Package Weight (kg): ";
    cin >> newOrder.packageWeight;
    newOrder.status = "Pending";
    newOrder.assignedDriver = "None";
    newOrder.deliveryCharge = calculateDeliveryCharge(newOrder.packageWeight);
    orders.push_back(newOrder);
    cout << "Order added successfully!\n";
}

void viewOrders() {
    cout << "\nPending Deliveries:\n";
    for (const auto& order : orders) {
        cout << "Order ID: " << order.orderID << " | Customer: " << order.customerName << " | Status: " << order.status << "\n";
    }
}

void updateOrderStatus() {
    int id, choice;
    cout << "Enter Order ID to update status: ";
    cin >> id;
    for (auto& order : orders) {
        if (order.orderID == id) {
            cout << "Select new status:\n";
            cout << "1. Pending\n2. Out for Delivery\n3. Delivered\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Ignore any newline character
            
            if (choice == 1) order.status = "Pending";
            else if (choice == 2) order.status = "Out for Delivery";
            else if (choice == 3) order.status = "Delivered";
            else {
                cout << "Invalid choice! Status not updated.\n";
                return;
            }
            cout << "Status updated successfully!\n";
            return;
        }
    }
    cout << "Order not found!\n";
}

void assignDriver() {
    int id;
    cout << "Enter Order ID to assign driver: ";
    cin >> id;
    cin.ignore();
    for (auto& order : orders) {
        if (order.orderID == id) {
            cout << "Enter Driver's Name: ";
            getline(cin, order.assignedDriver);
            cout << "Driver assigned successfully!\n";
            return;
        }
    }
    cout << "Order not found!\n";
}

void removeDeliveredOrders() {
    orders.erase(remove_if(orders.begin(), orders.end(), [](const Order& o) { return o.status == "Delivered"; }), orders.end());
    cout << "Delivered orders removed!\n";
}

void generateReport() {
    double totalRevenue = 0;
    int totalDeliveries = 0;
    cout << "\nDelivery Report:\n";
    for (const auto& order : orders) {
        if (order.status == "Delivered") {
            totalRevenue += order.deliveryCharge;
            totalDeliveries++;
        }
    }
    cout << "Total Deliveries: " << totalDeliveries << "\n";
    cout << "Total Revenue: $" << totalRevenue << "\n";
}

int main() {
    int choice;
    do {
        cout << "\nDelivery Management System";
        cout << "\n1. Add Order\n2. View Orders\n3. Update Order Status\n4. Assign Driver\n5. Remove Delivered Orders\n6. Generate Report\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addOrder(); break;
            case 2: viewOrders(); break;
            case 3: updateOrderStatus(); break;
            case 4: assignDriver(); break;
            case 5: removeDeliveredOrders(); break;
            case 6: generateReport(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again!\n";
        }
    } while (choice != 7);
    return 0;
}