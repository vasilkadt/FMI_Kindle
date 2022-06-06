#include "Comment.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Comment::Comment()
{
	text = nullptr;
	this->username = nullptr;
}

Comment::Comment(const char* text, const char* username)
{
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);

	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

Comment::Comment(const Comment& other)
{
	copy(other);
}

Comment& Comment::operator=(const Comment& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Comment::~Comment()
{
	free();
}

void Comment::setText(const char* text)
{
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);
}

void Comment::setUsername(const char* username)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

const char* Comment::getText() const
{
	return text;
}

const char* Comment::getUser() const
{
	return this->username;
}

void Comment::copy(const Comment& other)
{
	this->text = new char[strlen(other.text) + 1];
	strcpy(this->text, other.text);

	this->username = new char[strlen(other.username) + 1];
	strcpy(this->username, other.username);
}

void Comment::free()
{
	delete[] text;
	delete[] username;
}