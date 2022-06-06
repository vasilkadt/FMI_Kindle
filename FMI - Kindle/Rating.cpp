#include "Rating.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

void Rating::copy(const Rating& other)
{
	this->rating = other.rating;
	this->username = new char[strlen(other.username) + 1];
	strcpy(this->username, other.username);
}

void Rating::free()
{
	delete[] username;
}

Rating::Rating()
{
	rating = 0;
	this->username = nullptr;
}

Rating::Rating(const Rating& other) {
	copy(other);
}
Rating& Rating::operator=(const Rating& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
Rating::~Rating() {
	free();
}
Rating::Rating(const int rating, const char* username)
{
	this->rating = rating;

	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

void Rating::setRating(const int rating)
{
	this->rating = rating;
}

void Rating::setUsername(const char* username)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

const int Rating::getRating() const
{
	return rating;
}

const char* Rating::getUsername() const
{
	return this->username;
}