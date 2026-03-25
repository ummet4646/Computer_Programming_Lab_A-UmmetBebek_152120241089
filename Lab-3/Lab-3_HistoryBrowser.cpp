#include <iostream>
#include <string>
using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3]; // Hour, Minute, Second
    Page* next;
    Page* prev;
};

Page* head = NULL;
Page* tail = NULL;
Page* current = NULL;

// Visit Page (Append)
void visitPage(string url, string title, int h, int m, int s) {
    Page* newPage = new Page;

    newPage->url = url;
    newPage->title = title;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;

    newPage->next = NULL;
    newPage->prev = tail;

    if (head == NULL) {
        head = newPage;
        tail = newPage;
    }
    else {
        tail->next = newPage;
        tail = newPage;
    }

    current = newPage;
}

// Back
void goBack() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        cout << "Moved Back\n";
    }
    else {
        cout << "No previous page\n";
    }
}

// Forward
void goForward() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        cout << "Moved Forward\n";
    }
    else {
        cout << "No next page\n";
    }
}

// Delete Current Page
void deleteCurrent() {
    if (current == NULL) return;

    Page* temp = current;

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;
    else
        tail = current->prev;

    if (current->next != NULL)
        current = current->next;
    else
        current = current->prev;

    delete temp;
    cout << "Current page deleted\n";
}

// Display History
void displayHistory() {
    Page* temp = head;

    if (temp == NULL) {
        cout << "History is empty\n";
        return;
    }

    while (temp != NULL) {
        cout << temp->title << " - " << temp->url << " Time: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i];
            if (i < 2) cout << ":";
        }

        if (temp == current)
            cout << "  <--- Current Page";

        cout << endl;
        temp = temp->next;
    }
}

// Clear Memory
void clearHistory() {
    Page* temp = head;
    while (temp != NULL) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

// Main Menu
int main() {
    int choice;

    while (true) {
        cout << "\n===== Browser History Manager =====\n";
        cout << "1. Visit Page\n";
        cout << "2. Back\n";
        cout << "3. Forward\n";
        cout << "4. Delete Current Page\n";
        cout << "5. Display History\n";
        cout << "6. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        // Input hatası kontrol
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!\n";
            continue;
        }

        if (choice == 1) {
            string url, title;
            int h, m, s;

            cout << "Enter URL: ";
            cin >> url;
            cout << "Enter Title: ";
            cin >> title;
            cout << "Enter Time (Hour Minute Second): ";
            cin >> h >> m >> s;

            visitPage(url, title, h, m, s);
        }
        else if (choice == 2) {
            goBack();
        }
        else if (choice == 3) {
            goForward();
        }
        else if (choice == 4) {
            deleteCurrent();
        }
        else if (choice == 5) {
            displayHistory();
        }
        else if (choice == 6) {
            clearHistory();
            cout << "Program exited and memory cleared.\n";
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}