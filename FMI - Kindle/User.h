#pragma once
#include "Book.h"
const int maxBooks = 20;
const int maxWritenBooks = 20;
class User
{
private:
	char* username;
	char* password;
	Book* readBooks;
	Book* writenBooks;
	int readBooksCount;
	int writenBooksCount;
	void copy(const User& other);
	void free();

public:
	User();
	User(const char* username, const char* password);
	User(const char* username, const char* password, std::ifstream& books);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	void setUsername(const char* username);
	void setPassword(const char* password);

	const char* getUserName() const;
	const char* getPassword() const;

	void addWritenBook(const Book& book);
	bool operator==(const User& other);
	void addPage(const char* bookName);
	void readBook(const Book& book);
	void viewRatings(const char* bookName);
	void rateBook(const char* bookName, const Rating& rating);
	void commentBook(const char* bookName, const Comment& comment);
	void viewComments(const char* bookName);
	void writeBook(const Book& book);
	bool changeTitle(const char* bookName, const char* newTitle);
	void changeRating(const char* bookName, const char* fileName, const char* username, const int& newRating);
};

