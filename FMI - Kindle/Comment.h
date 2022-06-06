#pragma once

class Comment
{
private:
	char* text;
	char* username;

public:
	Comment();
	Comment(const char* text, const char* username);
	Comment(const Comment& other);
	Comment& operator=(const Comment& other);
	~Comment();

	void setText(const char* text);
	void setUsername(const char* username);

	const char* getText() const;
	const char* getUser() const;

private:
	void copy(const Comment& other);
	void free();
};