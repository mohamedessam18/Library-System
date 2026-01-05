#include <iostream>
#include <string>
using namespace std;

int* ids = nullptr;
string* titles = nullptr;
string* authors = nullptr;
bool* available = nullptr;
int bookCount = 0;

int searchBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (ids[i] == id )
            return i;
        
    }
    return -1;
}

void addBook() {
    int id;
    string title, author;

    cout << "Enter book ID: ";
    cin >> id;

    if (searchBookById(id) != -1) {
        cout << "Book ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter author: ";
    getline(cin, author);

    int* newIds = new int[bookCount + 1];
    string* newTitles = new string[bookCount + 1];
    string* newAuthors = new string[bookCount + 1];
    bool* newAvailable = new bool[bookCount + 1];

    for (int i = 0; i < bookCount; i++) {
        newIds[i] = ids[i];
        newTitles[i] = titles[i];
        newAuthors[i] = authors[i];
        newAvailable[i] = available[i];
    }

    newIds[bookCount] = id;
    newTitles[bookCount] = title;
    newAuthors[bookCount] = author;
    newAvailable[bookCount] = true;

    delete[] ids;
    delete[] titles;
    delete[] authors;
    delete[] available;

    ids = newIds;
    titles = newTitles;
    authors = newAuthors;
    available = newAvailable;

    bookCount++;
    cout << "Book added successfully!\n";
}

void updateBook() {
    int id;
    cout << "Enter book ID to update: ";
    cin >> id;

    int index = searchBookById(id);
    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    cin.ignore();
    cout << "Enter new title: ";
    getline(cin, titles[index]);
    cout << "Enter new author: ";
    getline(cin, authors[index]);

    cout << "Book updated successfully!\n";
}

void removeBook() {
    int id;
    cout << "Enter book ID to remove: ";
    cin >> id;

    int index = searchBookById(id);
    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    int* newIds = new int[bookCount - 1];
    string* newTitles = new string[bookCount - 1];
    string* newAuthors = new string[bookCount - 1];
    bool* newAvailable = new bool[bookCount - 1];

    for (int i = 0, j = 0; i < bookCount; i++) {
        if (i == index) continue;
        newIds[j] = ids[i];
        newTitles[j] = titles[i];
        newAuthors[j] = authors[i];
        newAvailable[j] = available[i];
        j++;
    }

    delete[] ids;
    delete[] titles;
    delete[] authors;
    delete[] available;

    ids = newIds;
    titles = newTitles;
    authors = newAuthors;
    available = newAvailable;

    bookCount--;
    cout << "Book removed successfully!\n";
}

void borrowBook() {
    int id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    int index = searchBookById(id);
    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }
    if (!available[index]) {
        cout << "Book is already borrowed!\n";
        return;
    }
    available[index] = false;
    cout << "Book borrowed successfully!\n";
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;

    int index = searchBookById(id);
    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }
    if (available[index]) {
        cout << "Book is already available!\n";
        return;
    }
    available[index] = true;
    cout << "Book returned successfully!\n";
}

void displayBooks() {
    if (bookCount == 0) {
        cout << "No books in the library!\n";
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        cout << "ID: " << ids[i] << endl;
        cout << "Title: " << titles[i] << endl;
        cout << "Author: " << authors[i] << endl;
        cout << "Status: " << (available[i] ? "Available" : "Borrowed") << endl;
        cout << "-------------------------\n";
    }
}

void showMenu() {
    cout << "\n--- Alex Library System ---\n";
    cout << "1. Add Book\n";
    cout << "2. Update Book\n";
    cout << "3. Remove Book\n";
    cout << "4. Borrow Book\n";
    cout << "5. Return Book\n";
    cout << "6. Display Books\n";
    cout << "0. Exit\n";
}

int main() {
    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: updateBook(); break;
        case 3: removeBook(); break;
        case 4: borrowBook(); break;
        case 5: returnBook(); break;
        case 6: displayBooks(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    delete[] ids;
    delete[] titles;
    delete[] authors;
    delete[] available;

    return 0;
}
