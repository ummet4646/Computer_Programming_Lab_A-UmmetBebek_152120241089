#include <iostream>
#include <string>
using namespace std;

// -------------------- MONEY BUNDLE --------------------
struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3]; // [0]=100, [1]=50, [2]=20
};

// -------------------- STACK NODE (LinkedList) --------------------
struct MoneyNode {
    MoneyBundle data;
    MoneyNode* next;
};

// -------------------- MONEY STACK --------------------
class MoneyStack {
private:
    MoneyNode* top;

public:
    MoneyStack() {
        top = NULL;
    }

    // Receive Money (Push)
    void pushBundle(MoneyBundle bundle) {
        MoneyNode* newNode = new MoneyNode;
        newNode->data = bundle;
        newNode->next = top;
        top = newNode;
        cout << "Money bundle pushed to stack.\n";
    }

    // Pop Money
    MoneyBundle popBundle() {
        MoneyBundle bundle;

        if (top == NULL) {
            cout << "Safe is empty!\n";
            return bundle;
        }

        MoneyNode* temp = top;
        bundle = temp->data;
        top = top->next;
        delete temp;

        return bundle;
    }

    bool isEmpty() {
        return top == NULL;
    }

    // Display Money Stack
    void displayStack() {
        MoneyNode* temp = top;

        cout << "\n--- Money Bundles in Safe (Stack) ---\n";

        if (temp == NULL) {
            cout << "No money bundles in safe.\n";
            return;
        }

        while (temp != NULL) {
            cout << "Serial: " << temp->data.serialNumber
                << " | Currency: " << temp->data.currencyType
                << " | 100s: " << temp->data.billCounts[0]
                << " | 50s: " << temp->data.billCounts[1]
                << " | 20s: " << temp->data.billCounts[2]
                << endl;

            temp = temp->next;
        }
    }
};

// -------------------- CUSTOMER STRUCT --------------------
struct Customer {
    string customerName;
    string transactionType;
};

// -------------------- CIRCULAR QUEUE --------------------
class CustomerQueue {
private:
    Customer queue[5];
    int front;
    int rear;
    int count;

public:
    CustomerQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // New Customer (Enqueue)
    void enqueue(Customer c) {
        if (count == 5) {
            cout << "Queue is full!\n";
            return;
        }

        rear = (rear + 1) % 5;
        queue[rear] = c;
        count++;

        cout << "Customer added to queue.\n";
    }

    // Dequeue Customer
    Customer dequeue() {
        Customer c;

        if (count == 0) {
            cout << "Queue is empty!\n";
            return c;
        }

        c = queue[front];
        front = (front + 1) % 5;
        count--;

        return c;
    }

    bool isEmpty() {
        return count == 0;
    }

    // Display Queue
    void displayQueue() {
        cout << "\n--- Customers Waiting (Circular Queue) ---\n";

        if (count == 0) {
            cout << "No customers in queue.\n";
            return;
        }

        int i = front;
        for (int j = 0; j < count; j++) {
            cout << "Name: " << queue[i].customerName
                << " | Transaction: " << queue[i].transactionType
                << endl;

            i = (i + 1) % 5;
        }
    }
};

// -------------------- MAIN PROGRAM --------------------
int main() {
    MoneyStack moneyStack;
    CustomerQueue customerQueue;

    int choice;

    do {
        cout << "\n===== BANK BRANCH MANAGEMENT SYSTEM =====\n";
        cout << "1. Receive Money (Push Stack)\n";
        cout << "2. New Customer (Enqueue Queue)\n";
        cout << "3. Process Transaction (Pop & Dequeue)\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            MoneyBundle bundle;
            cout << "Serial Number: ";
            cin >> bundle.serialNumber;
            cout << "Currency Type: ";
            cin >> bundle.currencyType;
            cout << "Number of 100 bills: ";
            cin >> bundle.billCounts[0];
            cout << "Number of 50 bills: ";
            cin >> bundle.billCounts[1];
            cout << "Number of 20 bills: ";
            cin >> bundle.billCounts[2];

            moneyStack.pushBundle(bundle);
        }

        else if (choice == 2) {
            Customer c;
            cout << "Customer Name: ";
            cin >> c.customerName;
            cout << "Transaction Type: ";
            cin >> c.transactionType;

            customerQueue.enqueue(c);
        }

        else if (choice == 3) {
            if (!moneyStack.isEmpty() && !customerQueue.isEmpty()) {
                Customer c = customerQueue.dequeue();
                MoneyBundle b = moneyStack.popBundle();

                cout << "\nTransaction Processed!\n";
                cout << "Customer: " << c.customerName << endl;
                cout << "Money Bundle Serial Used: " << b.serialNumber << endl;
            }
            else {
                cout << "Queue empty or Safe empty!\n";
            }
        }

        else if (choice == 4) {
            moneyStack.displayStack();
            customerQueue.displayQueue();
        }

    } while (choice != 5);

    return 0;
}