#pragma once
#include <fstream>
#include "Line.h"

const int MAX_SIZE = 1024;
const int maxLinesInPage = 15;
class Page
{
private:
	Line* lines;
	int countLines;

public:

	Page();
	Page(const Page& other);
	Page& operator=(const Page& other);
	~Page();

	void printPage() const;
	void addLine(const Line& newLine);
	void clearPage();

private:
	void copy(const Page& other);
	void free();
};