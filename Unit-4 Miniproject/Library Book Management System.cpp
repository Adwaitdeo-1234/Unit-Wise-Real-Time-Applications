#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Book
{
private:
    string isbn;
    string title;
    string author;
    string category;
    string availability;

public:
    // Constructor
    Book()
    {
        availability = "Available";
    }

    Book(string i, string t, string a, string c, string av = "Available")
    {
        isbn = i;
        title = t;
        author = a;
        category = c;
        availability = av;
    }

    // Getters
    string getISBN()
    {
        return isbn;
    }

    string getAvailability()
    {
        return availability;
    }

    // Display book
    void display()
    {
        cout << "\nISBN         : " << isbn;
        cout << "\nTitle        : " << title;
        cout << "\nAuthor       : " << author;
        cout << "\nCategory     : " << category;
        cout << "\nAvailability : " << availability << "\n";
    }

    // Convert object to file format
    string toFileFormat()
    {
        return isbn + "|" + title + "|" + author + "|" +
               category + "|" + availability;
    }

    // Create Book object from file line
    static Book fromFileFormat(string line)
    {
        stringstream ss(line);

        string i, t, a, c, av;

        getline(ss, i, '|');
        getline(ss, t, '|');
        getline(ss, a, '|');
        getline(ss, c, '|');
        getline(ss, av, '|');

        return Book(i, t, a, c, av);
    }

    // Setters for updating
    void setTitle(string t)
    {
        title = t;
    }

    void setAuthor(string a)
    {
        author = a;
    }

    void setCategory(string c)
    {
        category = c;
    }

    void setAvailability(string av)
    {
        availability = av;
    }
};


// ================= LIBRARY CLASS =================

class Library
{
private:
    string fileName = "library.txt";

public:

    // Add a new book
    void addBook()
    {
        string isbn, title, author, category;

        cout << "\nEnter ISBN: ";
        cin >> isbn;

        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Category: ";
        getline(cin, category);

        // Check duplicate ISBN
        if (findBook(isbn, false))
        {
            cout << "\nBook with this ISBN already exists!\n";
            return;
        }

        Book book(isbn, title, author, category);

        ofstream file(fileName, ios::app);

        if (file.is_open())
        {
            file << book.toFileFormat() << endl;
            file.close();

            cout << "\nBook added successfully!\n";
        }
        else
        {
            cout << "\nError opening file!\n";
        }
    }


    // Search book
    bool findBook(string isbn, bool displayResult = true)
    {
        ifstream file(fileName);

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            Book book = Book::fromFileFormat(line);

            if (book.getISBN() == isbn)
            {
                if (displayResult)
                {
                    cout << "\nBook Found!";
                    book.display();
                }

                file.close();
                return true;
            }
        }

        file.close();

        if (displayResult)
            cout << "\nBook not found!\n";

        return false;
    }


    // Issue a book
    void issueBook()
    {
        string isbn;

        cout << "\nEnter ISBN of book to issue: ";
        cin >> isbn;

        fstream file(fileName, ios::in);
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            Book book = Book::fromFileFormat(line);

            if (book.getISBN() == isbn)
            {
                found = true;

                if (book.getAvailability() == "Available")
                {
                    book.setAvailability("Issued");
                    cout << "\nBook issued successfully!\n";
                }
                else
                {
                    cout << "\nBook is already issued!\n";
                }
            }

            temp << book.toFileFormat() << endl;
        }

        file.close();
        temp.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        if (!found)
            cout << "\nBook not found!\n";
    }


    // Return a book
    void returnBook()
    {
        string isbn;

        cout << "\nEnter ISBN of book to return: ";
        cin >> isbn;

        ifstream file(fileName);
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            Book book = Book::fromFileFormat(line);

            if (book.getISBN() == isbn)
            {
                found = true;

                if (book.getAvailability() == "Issued")
                {
                    book.setAvailability("Available");
                    cout << "\nBook returned successfully!\n";
                }
                else
                {
                    cout << "\nBook is already available!\n";
                }
            }

            temp << book.toFileFormat() << endl;
        }

        file.close();
        temp.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        if (!found)
            cout << "\nBook not found!\n";
    }


    // Update book details
    void updateBook()
    {
        string isbn;

        cout << "\nEnter ISBN of book to update: ";
        cin >> isbn;

        ifstream file(fileName);
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            Book book = Book::fromFileFormat(line);

            if (book.getISBN() == isbn)
            {
                found = true;

                string title, author, category;

                cin.ignore();

                cout << "Enter new title: ";
                getline(cin, title);

                cout << "Enter new author: ";
                getline(cin, author);

                cout << "Enter new category: ";
                getline(cin, category);

                book.setTitle(title);
                book.setAuthor(author);
                book.setCategory(category);

                cout << "\nBook updated successfully!\n";
            }

            temp << book.toFileFormat() << endl;
        }

        file.close();
        temp.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        if (!found)
            cout << "\nBook not found!\n";
    }


    // Generate availability report
    void availabilityReport()
    {
        ifstream file(fileName);

        string line;
        int total = 0;
        int available = 0;
        int issued = 0;

        cout << "\n========================================";
        cout << "\n       LIBRARY AVAILABILITY REPORT";
        cout << "\n========================================";

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            Book book = Book::fromFileFormat(line);

            total++;

            if (book.getAvailability() == "Available")
            {
                available++;
            }
            else
            {
                issued++;
            }

            book.display();
        }

        file.close();

        cout << "\n========================================";
        cout << "\nTotal Books     : " << total;
        cout << "\nAvailable Books : " << available;
        cout << "\nIssued Books    : " << issued;
        cout << "\n========================================\n";
    }
};


// ================= MAIN FUNCTION =================

int main()
{
    Library library;

    int choice;

    do
    {
        cout << "\n\n======================================";
        cout << "\n       LIBRARY MANAGEMENT SYSTEM";
        cout << "\n======================================";

        cout << "\n1. Add Book";
        cout << "\n2. Search Book";
        cout << "\n3. Issue Book";
        cout << "\n4. Return Book";
        cout << "\n5. Update Book";
        cout << "\n6. Availability Report";
        cout << "\n7. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;

        case 2:
        {
            string isbn;

            cout << "\nEnter ISBN to search: ";
            cin >> isbn;

            library.findBook(isbn);
            break;
        }

        case 3:
            library.issueBook();
            break;

        case 4:
            library.returnBook();
            break;

        case 5:
            library.updateBook();
            break;

        case 6:
            library.availabilityReport();
            break;

        case 7:
            cout << "\nThank you for using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}