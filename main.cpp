#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product {
protected:
    string name;
    double price;
    int quantity;

public:
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}

    virtual double getTotalPrice() const {
        return price * quantity;
    }

    virtual void display() const {
        cout << "Product: " << name << ", Price: $" << price << ", Quantity: " << quantity << endl;
    }
};

class Client {
private:
    string name;
    string address;

public:
    Client(string n, string addr) : name(n), address(addr) {}

    void display() const {
        cout << "Client: " << name << ", Address: " << address << endl;
    }
};

class Order {
private:
    int orderNumber;
    Client client;
    vector<Product*> products;

public:
    Order(int num, const Client& c, const vector<Product*>& p) : orderNumber(num), client(c), products(p) {}

    double getTotalPrice() const {
        double total = 0.0;
        for (const auto& product : products) {
            total += product->getTotalPrice();
        }
        return total;
    }

    void display() const {
        cout << "Order Number: " << orderNumber << endl;
        client.display();
        cout << "Products:" << endl;
        for (const auto& product : products) {
            product->display();
        }
        cout << "Total Price: $" << getTotalPrice() << endl;
    }
};

class DiscountedOrder : public Order {
private:
    double discountPercentage;

public:
    DiscountedOrder(int num, const Client& c, const vector<Product*>& p, double discount)
            : Order(num, c, p), discountPercentage(discount) {}

    double getTotalPrice() const override {
        double total = Order::getTotalPrice();
        return total - (total * (discountPercentage / 100.0));
    }
};

int main() {
    // Create products
    Product p1("Laptop", 999.99, 3);
    Product p2("Phone", 599.99, 2);
    Product p3("Tablet", 399.99, 5);

    // Create a client
    Client client("John Doe", "123 Main St, City");

    // Create orders
    vector<Product*> products1 = {&p1, &p2};
    Order order1(1, client, products1);

    vector<Product*> products2 = {&p2, &p3};
    DiscountedOrder order2(2, client, products2, 10.0); // 10% discount

    // Display orders
    cout << "Order 1:" << endl;
    order1.display();

    cout << endl;

    cout << "Order 2:" << endl;
    order2.display();

    return 0;
}