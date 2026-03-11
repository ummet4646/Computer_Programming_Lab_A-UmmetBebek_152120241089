#include <iostream>
#include <string>
using namespace std;

// Node struct
struct Node {
    string songTitle;
    Node* next;
};

// Fonksiyonlar
void addSong(Node*& head, const string& title) {
    Node* newNode = new Node;
    newNode->songTitle = title;
    newNode->next = head;
    head = newNode;
}

void listSongs(Node* head) {
    Node* current = head;
    int number = 1;
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }
    while (current) {
        cout << number << ". " << current->songTitle << endl;
        current = current->next;
        number++;
    }
}

bool searchSong(Node* head, const string& title) {
    Node* current = head;
    while (current) {
        if (current->songTitle == title)
            return true;
        current = current->next;
    }
    return false;
}

// Main Menu
int main() {
    Node* playlist = nullptr;
    int choice;
    string title;

    do {
        cout << "\n--- Music Playlist ---\n";
        cout << "1. Add Song\n";
        cout << "2. Search Song\n";
        cout << "3. List Songs\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // newline temizleme

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);
            addSong(playlist, title);
            cout << "Song added!\n";
            break;
        case 2:
            cout << "Enter song title to search: ";
            getline(cin, title);
            if (searchSong(playlist, title))
                cout << "Song found!\n";
            else
                cout << "Song not found.\n";
            break;
        case 3:
            listSongs(playlist);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    // Belleği temizleme
    while (playlist) {
        Node* temp = playlist;
        playlist = playlist->next;
        delete temp;
    }

    return 0;
}