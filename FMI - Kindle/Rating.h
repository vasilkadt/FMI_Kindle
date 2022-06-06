#pragma once
class Rating
{
private:
	int rating;
	char* username;
	void copy(const Rating& other);
	void free();

public:
	Rating();
	Rating(const int rating, const char* username);
	Rating(const Rating& other);
	Rating& operator=(const Rating& other);
	~Rating();

	void setRating(const int rating);
	void setUsername(const char* username);

	const int getRating() const;
	const char* getUsername() const;
};