#include "Book.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Book::Book()
{
	title = nullptr;
	author = nullptr;
	this->ratings = new Rating[maxRatings];
	pages = new Page[maxPagesBook];
	this->pagesCount = 0;
	this->comments = new Comment[maxComments];
	this->countComments = 0;
	this->countRatings = 0;
}

Book::Book(const char* title, const char* author)
{
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);

	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
	this->pages = new Page[maxPagesBook];
	this->pagesCount = 0;
	char buffer[MAX_SIZE];
	char fileName[MAX_SIZE] = "";
	int i = 0;
	while (title[i] != '\0') {
		fileName[i] = title[i];
		i++;
	}
	fileName[i] = '.';
	fileName[i + 1] = 't';
	fileName[i + 2] = 'x';
	fileName[i + 3] = 't';
	std::ifstream bookFile(fileName, std::ifstream::in | std::ifstream::out | std::ifstream::app);

	if (!bookFile.is_open()) {
		std::cout << "Error! Can not open the file!";
		return;
	}
	int pageNumber = 0;
	Page page;
	bool currentPage = false;
	while (bookFile) {
		bookFile.getline(buffer, MAX_SIZE);
		if (buffer[0] == '\0') {
			if (pageNumber == 0)break;
			else
			{
				this->pages[this->pagesCount] = page;
				this->pagesCount++;
				break;
			}

		}
		if (buffer[0] == 'P' && buffer[1] == 'a' && buffer[2] == 'g' && buffer[3] == 'e' && buffer[4] == ' ') {
			if (currentPage) {
				pageNumber--;
				this->pages[pagesCount] = page;
				this->pagesCount++;
				page.clearPage();
			}

			pageNumber = buffer[5] - '0';
			Line newLine(buffer);
			page.addLine(newLine);
			currentPage = true;
		}
		else
		{
			Line newLine(buffer);
			page.addLine(newLine);
		}
	}
	char newFile[MAX_SIZE] = "";
	int t = 2;
	newFile[0] = 'R';
	newFile[1] = '-';
	while (title[t - 2] != '\0') {
		newFile[t] = title[t - 2];
		t++;
	}
	newFile[t] = '.';
	newFile[t + 1] = 't';
	newFile[t + 2] = 'x';
	newFile[t + 3] = 't';
	std::ifstream ratFile(newFile, std::ifstream::in | std::ifstream::out | std::ifstream::app);
	this->comments = new Comment[maxComments];
	this->ratings = new Rating[maxRatings];
	this->countRatings = 0;
	this->countComments = 0;

	while (!ratFile.eof()) {
		int counter = 0;
		int counterRating = 0;
		char buff[MAX_SIZE] = "";
		char username[MAX_SIZE] = "";
		char rating[MAX_SIZE] = "";
		int realRating = 0;
		ratFile.getline(buff, MAX_SIZE);
		if (buff[0] == ' ' || buff[0] == '\0')break;
		while (buff[counter] != ':')
		{
			username[counter] = buff[counter];
			counter++;
		}
		counter++;
		while (buff[counter] != '\0') {
			rating[counterRating] = buff[counter];
			counter++;
			counterRating++;
		}
		realRating = atoi(rating);
		Rating rate(realRating, username);
		this->ratings[this->countRatings] = rate;
		this->countRatings++;
	}
	newFile[0] = 'C';
	std::ifstream comFile(newFile, std::ifstream::in | std::ifstream::out | std::ifstream::app);
	while (!comFile.eof()) {
		char buff[MAX_SIZE] = "";
		char username[MAX_SIZE] = "";
		char com[MAX_SIZE] = "";
		comFile.getline(buff, MAX_SIZE);
		int cnt = 0;
		int commentCnt = 0;
		if (buff[0] == ' ' || buff[0] == '\0')break;
		while (buff[cnt] != ':')
		{
			username[cnt] = buff[cnt];
			cnt++;
		}
		cnt++;
		while (buff[cnt] != '\0') {
			com[commentCnt] = buff[cnt];
			cnt++;
			commentCnt++;
		}
		Comment comm(com, username);
		this->comments[this->countComments] = comm;
		this->countComments++;
	}
}

Book::Book(const Book& other)
{
	copy(other);
}

void Book::setPagesCount(const int& pages) {
	this->pagesCount = pages;
}
Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
Book::~Book()
{
	free();
}

void Book::copy(const Book& other)
{
	title = new char[strlen(other.title) + 1];
	strcpy(title, other.title);

	author = new char[strlen(other.author) + 1];
	strcpy(author, other.author);
	this->pages = new Page[maxPagesBook];

	for (size_t i = 0; i < other.pagesCount; i++)
	{
		pages[i] = other.pages[i];
	}
	pagesCount = other.pagesCount;

	this->ratings = new Rating[maxRatings];
	for (int i = 0; i < other.countRatings; i++)
	{
		this->ratings[i] = other.ratings[i];
	}
	this->countRatings = other.countRatings;

	this->comments = new Comment[maxComments];
	for (size_t i = 0; i < other.countComments; i++)
	{
		comments[i] = other.comments[i];
	}
	countComments = other.countComments;
}

void Book::free()
{
	delete[] title;
	delete[] author;
	delete[] pages;
	delete[] comments;
	delete[] ratings;
}

void Book::changeTitle(const char* title) {
	delete[] this->title;
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}
void Book::setTitle(const char* title)
{
	free();
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}

void Book::setAuthor(const char* author)
{
	free();
	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
}


const char* Book::getTitle() const
{
	return title;
}

const char* Book::getAuthor() const
{
	return author;
}

const Page* Book::getPages() const
{
	return pages;
}

int Book::getPagesCount() const
{
	return pagesCount;
}


void Book::addRating(const Rating& from) {
	this->ratings[countRatings] = from;
	this->countRatings++;
}

void Book::addComment(const Comment& from) {
	this->comments[countComments] = from;
	this->countComments++;
}

void Book::addPage(const char* bookName) {
	char input[MAX_SIZE];
	char fileName[MAX_SIZE] = "";
	int i = 0;
	while (bookName[i] != '\0') {
		fileName[i] = bookName[i];
		i++;
	}
	fileName[i] = '.';
	fileName[i + 1] = 't';
	fileName[i + 2] = 'x';
	fileName[i + 3] = 't';
	std::ofstream bookFile(fileName, std::ofstream::in | std::ofstream::out | std::ofstream::app);
	if (!bookFile.is_open()) {
		std::cout << "Error! Can not open the file!";
		return;
	}
	Page page;
	bool newPage = true;
	while (true) {
		std::cin.getline(input, MAX_SIZE);
		if (strcmp(input, ":quit") == 0)
		{
			this->pages[pagesCount] = page;
			this->pagesCount++;
			newPage = true;
			break;
		}
		else
		{
			int counter = 0;
			char toAdd[MAX_SIZE] = "";
			toAdd[0] = 'P';
			toAdd[1] = 'a';
			toAdd[2] = 'g';
			toAdd[3] = 'e';
			toAdd[4] = ' ';
			toAdd[5] = (this->pagesCount + 1) + '0';
			toAdd[6] = ':';
			while (input[counter] != '\0') {
				toAdd[counter + 7] = input[counter];
				counter++;
			}
			Line newLine(toAdd);
			page.addLine(newLine);
			if (newPage) {
				bookFile << "Page " << this->pagesCount + 1 << ":" << input << std::endl;
				newPage = false;
			}
			else
				bookFile << input << std::endl;
		}
	}
}

void Book::printBook(const int& pageNumber) {
	this->pages[pageNumber].printPage();
}

void Book::printRatings() const {
	for (int i = 0; i < this->countRatings; i++)
	{
		std::cout << this->ratings[i].getUsername() << " rated " << this->ratings[i].getRating() << " stars!" << std::endl;
	}
}

void Book::printComments() const {
	for (int i = 0; i < this->countComments; i++)
	{
		std::cout << this->comments[i].getUser() << " wrote: " << this->comments[i].getText() << std::endl;
	}
}

void Book::deletePage(const int& page) {
	this->pages[page].clearPage();
}

void Book::getRatingsFromFile(const char* filename) {
	delete[] comments;
	this->comments = new Comment[maxComments];
	this->countComments = 0;
	std::ifstream comFile(filename, std::ifstream::in | std::ifstream::out | std::ifstream::app);
	while (!comFile.eof()) {
		char buff[MAX_SIZE] = "";
		char username[MAX_SIZE] = "";
		char com[MAX_SIZE] = "";
		comFile.getline(buff, MAX_SIZE);
		int cnt = 0;
		int commentCnt = 0;
		if (buff[0] == ' ' || buff[0] == '\0')break;
		while (buff[cnt] != ':')
		{
			username[cnt] = buff[cnt];
			cnt++;
		}
		cnt++;
		while (buff[cnt] != '\0') {
			com[commentCnt] = buff[cnt];
			cnt++;
			commentCnt++;
		}
		Comment comm(com, username);
		this->comments[this->countComments] = comm;
		this->countComments++;
	}
}