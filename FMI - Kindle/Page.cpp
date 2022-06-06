#include "Page.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Page::Page()
{
	this->lines = new Line[maxLinesInPage];
	this->countLines = 0;
}

Page::Page(const Page& other)
{
	copy(other);
}

Page& Page::operator=(const Page& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Page::~Page()
{
	free();
}

void Page::copy(const Page& other)
{
	this->lines = new Line[maxLinesInPage];
	for (size_t i = 0; i < other.countLines; i++)
	{
		this->lines[i] = other.lines[i];
	}
	countLines = other.countLines;
}

void Page::free()
{
	delete[] lines;
}

void Page::printPage() const
{

	for (size_t i = 0; i < countLines; i++)
	{
		std::cout << this->lines[i].getText() << std::endl;
	}
}

void Page::addLine(const Line& newLine)
{
	lines[countLines] = newLine;
	countLines++;
}

void Page::clearPage() {
	this->lines = new Line[maxLinesInPage];
	this->countLines = 0;
}