#include "User.h"
#include <cstring>
#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)

User::User()
{
	username = nullptr;
	password = nullptr;
	this->readBooks = new Book[maxBooks];
	this->writenBooks = new Book[maxWritenBooks];
	this->readBooksCount = 0;
	this->writenBooksCount = 0;
}

User::User(const char* username, const char* password)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);

	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
	this->readBooks = new Book[maxBooks];
	this->writenBooks = new Book[maxWritenBooks];
	this->readBooksCount = 0;
	this->writenBooksCount = 0;
}

User::User(const char* username, const char* password, std::ifstream& books) {
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);

	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
	char buffer[MAX_SIZE] = "";
	while (!books.eof()) {
		books.getline(buffer, MAX_SIZE);
		int i = 3;
		char title[MAX_SIZE] = "";
		char author[MAX_SIZE] = "";
		bool isAuthor = false;
		int authorCounter = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == ' ' && buffer[i + 1] == 'b' && buffer[i + 2] == 'y' && buffer[i + 3] == ' ') {
				i += 3;
				isAuthor = true;
			}
			else
			{
				if (isAuthor) {
					author[authorCounter] = buffer[i];
					authorCounter++;
				}
				else title[i - 3] = buffer[i];
			}
			i++;
		}
		this->readBooks = new Book[maxBooks];
		this->writenBooks = new Book[maxWritenBooks];
		this->readBooksCount = 0;
		this->writenBooksCount = 0;
		if (strcmp(author, username) == 0) {
			Book book(title, author);
			this->writenBooks[writenBooksCount] = book;
		}
	}
	books.close();
}
User::User(const User& other)
{
	copy(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

User::~User()
{
	free();
}

void User::copy(const User& other)
{
	if (other.username == nullptr || other.password == nullptr) {
		username = nullptr;
		password = nullptr;
	}
	else {
		username = new char[strlen(other.username) + 1];
		strcpy(username, other.username);

		password = new char[strlen(other.password) + 1];
		strcpy(password, other.password);
	}
	this->readBooks = new Book[maxBooks];
	for (int i = 0; i < other.readBooksCount; i++)
	{
		this->readBooks[i] = other.readBooks[i];
	}
	this->readBooksCount = other.readBooksCount;
	this->writenBooks = new Book[maxWritenBooks];
	for (int i = 0; i < other.writenBooksCount; i++)
	{
		this->writenBooks[i] = other.writenBooks[i];
	}
	this->writenBooksCount = other.writenBooksCount;
}

void User::free()
{
	delete[] username;
	delete[] password;
	delete[] readBooks;
	delete[] writenBooks;
}

void User::setUsername(const char* username)
{
	free();
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

void User::setPassword(const char* password)
{
	free();
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
}

const char* User::getUserName() const {
	return this->username;
}
const char* User::getPassword() const {
	return this->password;
}


void User::readBook(const Book& book) {
	this->readBooks[this->readBooksCount] = book;
	this->readBooksCount++;
}

void User::rateBook(const char* bookName, const Rating& rating) {
	int bookCounter = 0;
	bool found = false;
	while (bookCounter != this->readBooksCount)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].addRating(rating);
			std::cout << "Book rated successfully!";
			found = true;
			break;
		}
	}
	if (!found)
		std::cout << "This Book has not been read!";
}

void User::changeRating(const char* bookName, const char* fileName, const char* username, const int& newRating) {
	int bookCounter = 0;
	bool found = false;
	while (bookCounter != this->readBooksCount)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			found = true;
			break;
		}
	}
	if (!found)
		std::cout << "This Book has not been read!";
	else {
		std::ifstream comFile(fileName);
		std::ofstream ofs;
		ofs.open("temp.txt", std::ofstream::out);
		char buff[MAX_SIZE] = "";

		bool hasUser = false;
		while (!comFile.eof()) {
			comFile.getline(buff, MAX_SIZE);
			char user[MAX_SIZE] = "";
			int i = 0;
			if (buff[0] == ' ' || buff[0] == '\0')break;
			while (buff[i] != ':') {
				user[i] = buff[i];
				i++;
			}
			if (strcmp(user, username) == 0) {
				ofs << username << ':' << newRating << std::endl;
				hasUser = true;
			}
			else
			{
				ofs << buff << std::endl;
			}
		}
		ofs.close();
		comFile.close();
		remove(fileName);
		rename("temp.txt", fileName);
		if (!hasUser) {
			std::cout << "User not found!";
		}
		else
		{
			std::cout << "Rating changed successfully!" << std::endl;
			this->readBooks[bookCounter].getRatingsFromFile(fileName);
		}
	}
}

bool User::operator==(const User& other) {
	if (username == nullptr && password == nullptr) return true;
	return false;
}
void User::viewRatings(const char* bookName) {
	int bookCounter = 0;
	while (bookCounter != this->readBooksCount)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].printRatings();
			break;
		}
	}
}

void User::commentBook(const char* bookName, const Comment& comment) {
	int bookCounter = 0;
	bool found = false;
	while (bookCounter != this->readBooksCount)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].addComment(comment);
			std::cout << "Book commented successfully!";
			found = true;
			break;
		}
	}
	if (!found)
		std::cout << "This Book has not been read!";
}

void User::viewComments(const char* bookName) {
	int bookCounter = 0;
	while (bookCounter != this->readBooksCount)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].printComments();
			break;
		}
	}
}

void User::writeBook(const Book& book) {
	this->writenBooks[this->writenBooksCount] = book;
	this->writenBooksCount++;
}

void User::addWritenBook(const Book& book) {
	this->writenBooks[this->writenBooksCount] = book;
	this->writenBooksCount++;
}
void User::addPage(const char* bookName) {
	int bookCounter = 0;
	bool found = false;
	while (bookCounter != this->writenBooksCount) {
		if (strcmp(this->writenBooks[bookCounter].getTitle(), bookName) == 0) {
			this->writenBooks[bookCounter].addPage(bookName);
			found = true;
			break;
		}
		bookCounter++;
	}
	if(!found)
	std::cout << "This book can not be edited!";
}

bool User::changeTitle(const char* bookName, const char* newTitle) {
	int bookCounter = 0;
	while (bookCounter != this->writenBooksCount) {
		if (strcmp(this->writenBooks[bookCounter].getTitle(), bookName) == 0) {
			this->writenBooks[bookCounter].changeTitle(newTitle);
			return true;
		}
		bookCounter++;
	}
	std::cout << "This book can not be edited!" << std::endl;
	return false;
}