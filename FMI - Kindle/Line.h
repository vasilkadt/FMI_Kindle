#pragma once

class Line
{
private:
	char* text;
	void copy(const Line& other);
	void free();

public:
	Line();
	Line(const char* text);
	Line(const Line& other);
	Line& operator=(const Line& other);
	~Line();

	void setText(const char* text);

	const char* getText() const;
};