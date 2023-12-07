#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Define a class for library members
class Member {
public:
    int memberID;
    std::string memberName;

    Member(int id, const std::string& name) : memberID(id), memberName(name) {}
};

// Define a class for books
class Book {
public:
    int bookID;
    std::string bookName;
    int pageCount;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;

    Book(int id, const std::string& name, int pageCount, const std::string& firstName, const std::string& lastName, const std::string& type)
        : bookID(id), bookName(name), pageCount(pageCount), authorFirstName(firstName), authorLastName(lastName), bookType(type) {}
};

// Define a class for the library
class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    // Add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Add a member to the library
    void addMember(const Member& member) {
        members.push_back(member);
    }

    // Display all books in the library
    void displayBooks() const {
        for (const auto& book : books) {
            std::cout << "ID: " << book.bookID << ", Name: " << book.bookName << ", Author: " << book.authorFirstName + " " + book.authorLastName << ", Type: " << book.bookType << std::endl;
        }
    }

    // Display all members in the library
    void displayMembers() const {
        for (const auto& member : members) {
            std::cout << "ID: " << member.memberID << ", Name: " << member.memberName << std::endl;
        }
    }
};

// Main program
int main(int argc, char* argv[]) {
    // Check for the correct command line arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Get the filename from the command line arguments
    const std::string filename(argv[1]);

    // Create a Library instance
    Library library;

    // Read data from CSV file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    std::cout << "File opened successfully." << std::endl;

    std::string line;
    // Read and ignore the header line
    std::getline(inputFile, line);
    std::cout << "Skipping header line: " << line << std::endl;

    // Process each line in the file
    while (std::getline(inputFile, line)) {
        std::cout << "Processing line: " << line << std::endl;

        // Tokenize the line using a comma as the delimiter
        std::istringstream ss(line);
        std::string token;

        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            std::cout << "Token: " << token << std::endl;
            tokens.push_back(token);
        }

        // Check the number of tokens to determine if it represents a member or a book
        if (tokens.size() == 6) {  
            int memberID = std::stoi(tokens[0]);
            std::string memberName = tokens[1];
            Member member(memberID, memberName);
            library.addMember(member);
        } else if (tokens.size() == 5) {  
            int bookID = std::stoi(tokens[0]);
            std::string bookName = tokens[1];
            int pageCount = std::stoi(tokens[2]);
            std::string authorFirstName = tokens[3];
            std::string authorLastName = tokens[4];
            std::string bookType = tokens[5];

            Book book(bookID, bookName, pageCount, authorFirstName, authorLastName, bookType);
            library.addBook(book);
        } else {
            std::cerr << "Error: Unexpected number of fields in line." << std::endl;
        }
    }

    // Display all books and members in the library
    std::cout << "\nBooks in the Library:\n";
    library.displayBooks();

    std::cout << "\nMembers in the Library:\n";
    library.displayMembers();

    return 0;
}
