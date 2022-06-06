#pragma once
#include "Page.h"
#include "Rating.h"
#include "Comment.h"
const int maxPagesBook = 1500;
const int maxRatings = 50;
const int maxComments = 50;
class Book
{
private:
	char* title;
	char* author;
	Page* pages;
	int pagesCount;
	Rating* ratings;
	int countRatings;
	Comment* comments;
	int countComments;

public:
	Book();
	Book(const char* title, const char* author);
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book();

	void addPage(const char* bookName);
	void deletePage(const int& page);
	void getRatingsFromFile(const char* filename);

	void setTitle(const char* title);
	void setAuthor(const char* author);
	void setPagesCount(const int& pages);
	void addRating(const Rating& from);
	void addComment(const Comment& from);

	void changeTitle(const char* title);
	const char* getTitle() const;
	const char* getAuthor() const;
	const Page* getPages() const;
	int getPagesCount() const;
	void printRatings() const;
	void printComments() const;

	void printBook(const int&);
private:
	void copy(const Book& other);
	void free();
};