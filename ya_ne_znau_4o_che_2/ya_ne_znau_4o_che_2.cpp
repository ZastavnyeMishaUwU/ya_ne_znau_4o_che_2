#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_BOOKS = 100;

class EBook {
public:
    string title;
    string author;

    EBook() : title(""), author("") {}
    EBook(const string& t, const string& a) : title(t), author(a) {}

    void writeToFile(ofstream& file) const {
        file << title << endl;
        file << author << endl;
    }

    static EBook readFromFile(ifstream& file) {
        string t, a;
        getline(file, t);
        getline(file, a);
        return EBook(t, a);
    }
};

void saveToFile(EBook books[], int size, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            books[i].writeToFile(file);
        }
        file.close();
        cout << "Books saved to file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

int readFromFile(EBook books[], const string& filename) {
    ifstream file(filename);
    int count = 0;
    if (file.is_open()) {
        while (count < MAX_BOOKS && !file.eof()) {
            books[count] = EBook::readFromFile(file);
            if (!books[count].title.empty() && !books[count].author.empty()) {
                count++;
            }
        }
        file.close();
        cout << "Books read from file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
    return count; 
}

int main() {
    EBook books[MAX_BOOKS] = {
        EBook("C++ Programming", "Bjarne Stroustrup"),
        EBook("Clean Code", "Robert C. Martin")
    };

    string filename = "ebooks.txt";


    saveToFile(books, 2, filename);

    EBook loadedBooks[MAX_BOOKS];


    int loadedCount = readFromFile(loadedBooks, filename);


    for (int i = 0; i < loadedCount; i++) {
        cout << "Title: " << loadedBooks[i].title << ", Author: " << loadedBooks[i].author << endl;
    }

    return 0;
}
