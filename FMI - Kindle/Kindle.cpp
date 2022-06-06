#include "Kindle.h"
#include <iostream>

#pragma warning(disable : 4996)
Kindle::Kindle() {
	this->users = new User[maxUsers];
	this->readBooks = new Book[maxReadBooks];
	this->currentBookPosition = 0;
	this->currentUserPosition = 0;
}

Kindle::Kindle(std::ifstream& usersFile, std::ifstream& booksFile)
{
	this->users = new User[maxUsers];
	this->readBooks = new Book[maxReadBooks];
	this->currentBookPosition = 0;
	this->currentUserPosition = 0;
	char buffer[BUFFER_LINE_SIZE];
	int countUserLines = 1;
	char username[BUFFER_LINE_SIZE] = "";
	char password[BUFFER_LINE_SIZE] = "";
	while (!usersFile.eof())
	{
		usersFile.getline(buffer, BUFFER_LINE_SIZE);
		if (buffer[0] == '\0')break;
		if (countUserLines % 2 != 0) {
			int i = 0;
			while (buffer[i] != '\0') {
				username[i] = buffer[i];
				i++;
			}
		}
		else
		{
			int i = 0;
			while (buffer[i] != '\0') {
				password[i] = buffer[i];
				i++;
			}
			User user(username, password);
			this->users[currentUserPosition] = user;
			this->currentUserPosition++;
			i = 0;
			while (username[i] != '\0' && password[i] != '\0')
			{
				username[i] = '\0';
				password[i] = '\0';
				i++;
			}
		}
		countUserLines++;
	}

	while (!booksFile.eof())
	{
		booksFile.getline(buffer, BUFFER_LINE_SIZE);
		int i = 3;
		char title[BUFFER_LINE_SIZE] = "";
		char author[BUFFER_LINE_SIZE] = "";
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
		Book book(title, author);
		for (int i = 0; i < this->currentUserPosition; i++)
		{
			if (strcmp(this->users[i].getUserName(), author) == 0) {
				this->users[i].addWritenBook(book);
			}
		}
		this->readBooks[currentBookPosition] = book;
		this->currentBookPosition++;
	}
	usersFile.close();
	booksFile.close();
}

User Kindle::login(const char* username, const char* password)
{
	int userCounter = 0;

	while (userCounter != this->currentUserPosition)
	{
		if (strcmp(this->users[userCounter].getUserName(), username) == 0 && strcmp(this->users[userCounter].getPassword(), password) == 0) {
			std::cout << "Welcome, " << username;
			return this->users[userCounter];
		}
		userCounter++;
	}
	User user;
	return user;
}

void Kindle::signup(std::ofstream& myFile)
{
	std::cout << ">Enter username: ";
	char username[MAX_SIZE];
	std::cin >> username;
	std::cout << ">Enter password: ";
	char password[MAX_SIZE];
	std::cin >> password;
	myFile << username << std::endl << password << std::endl;
	User user(username, password);
	this->users[currentUserPosition] = user;
	this->currentUserPosition++;
	std::cout << "User registered!";
}

void Kindle::view(std::ifstream& myFile)
{
	int booksCounter = 0;
	while (booksCounter != this->currentBookPosition) {
		std::cout << booksCounter + 1 << ". " << this->readBooks[booksCounter].getTitle();
		std::cout << " by " << this->readBooks[booksCounter].getAuthor();
		std::cout << std::endl;
		booksCounter++;
	}
}

void Kindle::logout() {
	std::cout << "User succefully logged out!";
}

Book* Kindle::getBooks() const {
	return this->readBooks;
}

void Kindle::printBook(User& user, const char* bookName) {
	int bookCounter = 0;
	char input[BUFFER_LINE_SIZE] = "";
	while (bookCounter != this->currentBookPosition) {
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			user.readBook(this->readBooks[bookCounter]);
			int counter = 0;
			if (this->readBooks[bookCounter].getPagesCount() == 0) {
				std::cout << "Book is empty!";
				break;
			}
			this->readBooks[bookCounter].printBook(counter);
			while (true) {
				std::cin.getline(input, BUFFER_LINE_SIZE);
				if (strcmp(input, "q") == 0) {
					break;
				}
				else if (strcmp(input, "n") == 0) {
					counter++;
					if (this->readBooks[bookCounter].getPagesCount() == counter) {
						std::cout << "No more pages" << std::endl;
						counter--;
					}
					else
						this->readBooks[bookCounter].printBook(counter);
				}
				else if (strcmp(input, "p") == 0)
				{
					counter--;
					if (counter < 0) {
						std::cout << "This was the first page!" << std::endl;
						counter++;
					}
					else
						this->readBooks[bookCounter].printBook(counter);
				}
			}
			break;
		}
		bookCounter++;
	}
}

void Kindle::addNewBook(const Book& book, std::ofstream& booksFile) {
	this->readBooks[this->currentBookPosition] = book;
	booksFile << std::endl;
	booksFile << this->currentBookPosition + 1 << ". " << book.getTitle() << " by " << book.getAuthor();
	booksFile.close();
	this->currentBookPosition++;
}

void Kindle::getPage(const char* bookname, const int& page) {
	int bookCounter = 0;

	while (bookCounter != this->currentBookPosition)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookname) == 0) {
			if (page >= this->readBooks[bookCounter].getPagesCount() || page <= 0)
				std::cout << "Invalid page number";
			else
				this->readBooks[bookCounter].printBook(page - 1);
		}
		bookCounter++;
	}
	std::cout << "Invalid Book Title!";
}

void Kindle::changeTitle(const char* bookName, const char* newTitle, std::ofstream& books) {
	int bookCounter = 0;
	std::ofstream ofs;
	ofs.open("Books.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofs.open("Books.txt", std::ofstream::app);
	while (bookCounter != this->currentBookPosition)
	{
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].changeTitle(newTitle);
			ofs << bookCounter + 1 << newTitle << " by " << this->readBooks[bookCounter].getAuthor() << std::endl;
		}
		else
		{
			ofs << bookCounter + 1 << this->readBooks[bookCounter].getTitle() << " by " << this->readBooks[bookCounter].getAuthor() << std::endl;
		}
		bookCounter++;
	}
}

void Kindle::addPage(const char* bookName) {
	int bookCounter = 0;
	while (bookCounter != this->currentBookPosition) {
		if (strcmp(this->readBooks[bookCounter].getTitle(), bookName) == 0) {
			this->readBooks[bookCounter].addPage(bookName);
			break;
		}
		bookCounter++;
	}
}