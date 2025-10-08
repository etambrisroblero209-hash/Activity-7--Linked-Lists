#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class item{
private:
    string name;
    double cost;
public:
    item() : name(""), cost(0.0) {}
    item(string itemName, double itemCost) {
        name = itemName;
        cost = itemCost;
    }
    string get_name() const { return name; }
    double get_cost() const { return cost; }
    void print_item() const { 
        cout << fixed << setprecision(2);
        cout << "Item: " << name << ", Cost ($" << cost << ")" << endl;
    }
};

struct Node {
    item* data;
    Node* next;
    Node(item* item) {
        data = item;
        next = nullptr;
    }
};

class shopping_Cart{
private:
    Node* head;
public:
    shopping_Cart() { head = nullptr; }

    void add_item_at_start(item* item) {
        Node* newNode = new Node(item);
        newNode->next = head; 
        head = newNode;       
        cout << "Added '" << item->get_name() << "' to the START of the cart." << endl;
    }

    void delete_item_at_start() {
        if (!head) {
            cout << "Cart is empty, nothing to delete." << endl;
            return;
        }
        
        Node* temp = head;          
        item* deletedData = temp->data;
        head = head->next;          
        
        cout << "Deleting '" << deletedData->get_name() << "' from the START of the cart." << endl;
        delete deletedData;
        delete temp;
    }

    void view_cart() const {
        Node* current = head;
        if (!current) {
            cout << "Shopping Cart: EMPTY" << endl;
            return;
        }
        cout << "--- Shopping Cart (Start to End) ---" << endl;
        while (current) {
            current->data->print_item();
            current = current->next;
        }
        cout << "--------------------------------------" << endl;
    }

    double checkout() const {
        double total = 0;
        Node* current = head;
        while (current) {
            total += current->data->get_cost();
            current = current->next;
        }
        return total;
    }

    ~shopping_Cart() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current->data; 
            delete current;       
            current = nextNode;
        }
    }
};

int main() {
    shopping_Cart cart;

    
    cart.add_item_at_start(new item("Tea", 2.25));  
    cart.add_item_at_start(new item("Milk", 3.50)); 
    cart.add_item_at_start(new item("Car", 999.09)); 

    cart.view_cart();

    
    cart.delete_item_at_start(); 
    cart.view_cart();

    cart.delete_item_at_start(); 
    cart.view_cart();

    cout << "Final Total: $" << cart.checkout() << endl;

    return 0;
}