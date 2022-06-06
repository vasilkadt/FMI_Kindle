#pragma once
#include "User.h"
#include "Book.h"
#include <fstream>

const int BUFFER_LINE_SIZE = 1024;
const int maxUsers = 30;
const int maxReadBooks = 30;

class Kindle
{
private:
	User* users;
	Book* readBooks;
	int currentUserPosition;
	int currentBookPosition;

public:
	Kindle();
	Kindle(std::ifstream& usersFile, std::ifstream& booksFile);

	User login(const char* username, const char* password);
	void signup(std::ofstream& myFile);
	void logout();
	void view(std::ifstream& myFile);
	Book* getBooks() const;
	void getPage(const char* bookname, const int& page);
	void changeTitle(const char* bookName, const char* newTitle, std::ofstream& books);
	void addPage(const char* bookName);
	void addNewBook(const Book& book, std::ofstream& booksFile);
	void printBook(User& user, const char* bookName);
};
