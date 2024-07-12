#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_BOOKS = 100;  // Maximum number of books allowed
const int MAX_PATRONS = 50; // Maximum number of patrons allowed

class Book {
public:
    Book(string title, string author, string isbn, bool checked_out = false) 
        : title(title), author(author), isbn(isbn), checked_out(checked_out) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool isCheckedOut() const { return checked_out; }

    void checkOut() { checked_out = true; }
    void returnBook() { checked_out = false; }

    void display() const {
        cout << "Title: " << title 
             << ", Author: " << author 
             << ", ISBN: " << isbn 
             << ", Status: " << (checked_out ? "Checked out" : "Available") << endl;
    }

    string toString() const {
        return title + "," + author + "," + isbn + "," + (checked_out ? "1" : "0");
    }

private:
    string title;
    string author;
    string isbn;
    bool checked_out;
};

class Patron {
public:
    Patron(string name, int patron_id) 
        : name(name), patron_id(patron_id) {}

    string getName() const { return name; }
    int getPatronID() const { return patron_id; }

    void display() const {
        cout << "Name: " << name << ", Patron ID: " << patron_id << endl;
    }

    string toString() const {
        return name + "," + to_string(patron_id);
    }

private:
    string name;
    int patron_id;
};

class Library {
public:
    Library() {
        loadBooks();
        loadPatrons();
    }

    ~Library() {
        saveBooks();
        savePatrons();
    }

    void addBook(const Book& book) {
        if (books.size() < MAX_BOOKS) {
            books.push_back(book);
            saveBooks();
            cout << "Book added successfully." << endl;
        } else {
            cout << "Cannot add more books. Maximum limit reached." << endl;
        }
    }

    void addPatron(const Patron& patron) {
        if (patrons.size() < MAX_PATRONS) {
            patrons.push_back(patron);
            savePatrons();
            cout << "Patron added successfully." << endl;
        } else {
            cout << "Cannot add more patrons. Maximum limit reached." << endl;
        }
    }

    void displayBooks() const {
        for (const auto& book : books) {
            book.display();
        }
    }

    void displayPatrons() const {
        for (const auto& patron : patrons) {
            patron.display();
        }
    }

    void checkOutBook(const string& isbn, int patron_id) {
        for (auto& book : books) {
            if (book.getISBN() == isbn && !book.isCheckedOut()) {
                book.checkOut();
                saveBooks();
                cout << "Book checked out successfully." << endl;
                return;
            }
        }
        cout << "Book not available for check out." << endl;
    }

    void returnBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn && book.isCheckedOut()) {
                book.returnBook();
                saveBooks();
                cout << "Book returned successfully." << endl;
                return;
            }
        }
        cout << "Book not found or not checked out." << endl;
    }

private:
    vector<Book> books;
    vector<Patron> patrons;

    void loadBooks() {
        ifstream file("C:\\Users\\VANSHIKA\\project_c++\\Library_management_system\\Book.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, isbn, checked_out_str;
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, isbn, ',');
            getline(ss, checked_out_str, ',');
            bool checked_out = (checked_out_str == "1");
            books.emplace_back(title, author, isbn, checked_out);
        }
    }

    void saveBooks() const {
        ofstream file("C:\\Users\\VANSHIKA\\project_c++\\Library_management_system\\Book.txt");
        for (const auto& book : books) {
            file << book.toString() << endl;
        }
    }

    void loadPatrons() {
        ifstream file("C:\\Users\\VANSHIKA\\project_c++\\Library_management_system\\Patron.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, patron_id_str;
            getline(ss, name, ',');
            getline(ss, patron_id_str, ',');
            int patron_id = stoi(patron_id_str);
            patrons.emplace_back(name, patron_id);
        }
    }

    void savePatrons() const {
        ofstream file("C:\\Users\\VANSHIKA\\project_c++\\Library_management_system\\Patron.txt");
        for (const auto& patron : patrons) {
            file << patron.toString() << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "Library Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Patron\n";
        cout << "3. Display Books\n";
        cout << "4. Display Patrons\n";
        cout << "5. Check Out Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, author, isbn;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            library.addBook(Book(title, author, isbn));
        } else if (choice == 2) {
            string name;
            int patron_id;
            cout << "Enter patron name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter patron ID: ";
            cin >> patron_id;
            library.addPatron(Patron(name, patron_id));
        } else if (choice == 3) {
            library.displayBooks();
        } else if (choice == 4) {
            library.displayPatrons();
        } else if (choice == 5) {
            string isbn;
            int patron_id;
            cout << "Enter book ISBN: ";
            cin.ignore();
            getline(cin, isbn);
            cout << "Enter patron ID: ";
            cin >> patron_id;
            library.checkOutBook(isbn, patron_id);
        } else if (choice == 6) {
            string isbn;
            cout << "Enter book ISBN: ";
            cin.ignore();
            getline(cin, isbn);
            library.returnBook(isbn);
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;
    }

    return 0;
}
