#include "Line.h"
#include <cstring>
#include <iostream>
#pragma warning (disable: 4996)
void Line::copy(const Line& other) {
	this->text = new char[strlen(other.text) + 1];
	strcpy(this->text, other.text);
}

void Line::free() {
	delete[] text;
}

Line::Line() {
	this->text = nullptr;
}

Line::Line(const char* text) {
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);
}

Line::Line(const Line& other) {
	copy(other);
}

Line& Line::operator=(const Line& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Line::~Line() {
	free();
}

void Line::setText(const char* text) {
	free();
	this->text = new char[strlen(text) + 1];
	strcpy(this->text, text);
}

const char* Line::getText() const {
	return this->text;
}