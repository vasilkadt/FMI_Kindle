#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h> 
#include "User.h"
#include"Interface.h"
#include "Kindle.h"
#pragma warning(disable : 4996)

int toSeparator(const char* command)
{
	int counter = 0;
	while (*command != ' ' && *command != '\n' && *command != '\0')
	{
		counter++;
		command++;
	}

	return counter;
}

void myInterface()
{
	std::ofstream outputFile("Users.txt", std::ios::app);
	std::ifstream inputFile("Users.txt");
	std::ifstream books("Books.txt");
	std::ofstream outputBooks("Books.txt", std::ios::app);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "Error! Can not open the file!";
		return;
	}
	Kindle kindle(inputFile, books);
	bool userLogged = false;
	std::cout << ">";
	User user;
	User newUser;
	while (true)
	{
		char commandLine[BUFFER_LINE_SIZE];
		std::cin.getline(commandLine, BUFFER_LINE_SIZE);
		if (commandLine[0] == ' '||commandLine[0]=='\0') continue;
		int size = strlen(commandLine);
		int firstArgSize = toSeparator(commandLine);
		char* firstArg = new char[firstArgSize + 1];
		for (int i = 0; i < firstArgSize; i++) {
			firstArg[i] = commandLine[i];
		}
		firstArg[firstArgSize] = '\0';
		if (strcmp(commandLine, "login") == 0)
		{
			std::cout << ">Enter username: ";
			char username[MAX_SIZE];
			std::cin >> username;
			std::cout << ">Enter password: ";
			char password[MAX_SIZE];
			std::cin >> password;
			newUser = kindle.login(username, password);
			if (newUser == user) {
				std::cout << "This user does not exist!";
			}
			else
			{
				userLogged = true;
			}
		}
		else if (strcmp(commandLine, "signup") == 0)
		{
			kindle.signup(outputFile);
			
		}
		else if (strcmp(commandLine, "view") == 0)
		{
			if (userLogged) {
				kindle.view(books);
				std::cout << ">";
			}
			else {
				std::cout << "First you have to login!";
				std::cout << std::endl << ">";
			}
			continue;
		}
		else if (strcmp(firstArg, "read") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				kindle.printBook(newUser, bookName);

				std::cout << ">";
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "rate") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				char rating[2] = "";
				int realRating = 0;
				int counter = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						if (commandLine[i] == ' ' && commandLine[i + 1] >= 48 && commandLine[i + 1] <= 57) {
							rating[0] = commandLine[i + 1];
							if (commandLine[i + 2] != '\0') rating[1] = commandLine[i + 2];
							break;
						}
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				if (rating[1] == '\0') realRating = rating[0] - '0';
				else realRating = 10;
				Rating rate(realRating, newUser.getUserName());
				char fileName[MAX_SIZE] = "";
				int t = 2;
				fileName[0] = 'R';
				fileName[1] = '-';
				while (bookName[t - 2] != '\0') {
					fileName[t] = bookName[t - 2];
					t++;
				}
				fileName[t] = '.';
				fileName[t + 1] = 't';
				fileName[t + 2] = 'x';
				fileName[t + 3] = 't';
				std::ofstream comFile(fileName, std::ofstream::in | std::ofstream::out | std::ofstream::app);
				comFile << newUser.getUserName() << ':' << realRating << std::endl;
				newUser.rateBook(bookName, rate);
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "comment") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char comment[BUFFER_LINE_SIZE] = "";
				bool isComment = false;
				int counter = 0;
				int i = 0;
				while (commandLine[i] != '\0')
				{
					if (i >= firstArgSize + 1) {
						if (commandLine[i] == ' ' && commandLine[i + 1] == '"') {
							i += 2;
							isComment = true;
						}
						if (isComment) {
							if (commandLine[i] == '"')break;
							comment[counter] = commandLine[i];
							counter++;
						}
						else bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				Comment com(comment, newUser.getUserName());
				char fileName[MAX_SIZE] = "";
				int t = 2;
				fileName[0] = 'C';
				fileName[1] = '-';
				while (bookName[t - 2] != '\0') {
					fileName[t] = bookName[t - 2];
					t++;
				}
				fileName[t] = '.';
				fileName[t + 1] = 't';
				fileName[t + 2] = 'x';
				fileName[t + 3] = 't';
				std::ofstream comFile(fileName, std::ofstream::in | std::ofstream::out | std::ofstream::app);
				comFile << newUser.getUserName() << ':' << comment << std::endl;
				newUser.commentBook(bookName, com);
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "comments") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				newUser.viewComments(bookName);
				std::cout << '>';
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "rates") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				int i = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				newUser.viewRatings(bookName);
				std::cout << '>';
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "write") == 0)
		{
			if (userLogged) {
				char input[BUFFER_LINE_SIZE] = "";
				char title[BUFFER_LINE_SIZE] = "";
				std::cout << ">>Enter title: ";
				std::cin.getline(input, BUFFER_LINE_SIZE);
				if (input[0] == ' ')continue;
				int i = 0;
				while (input[i] != '\0') {
					title[i] = input[i];
					i++;
				}
				std::cout << ">>Enter pages count: ";
				std::cin.getline(input, BUFFER_LINE_SIZE);
				int pagesCount = 0;
				pagesCount = atoi(input);
				Book newBook(title, newUser.getUserName());
				kindle.addNewBook(newBook, outputBooks);
				newUser.writeBook(newBook);
				for (int i = 0; i < pagesCount; i++)
				{
					kindle.addPage(title);
				}
				std::cout << '>';
				continue;
			}
			else
			{
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "addPage") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				newUser.addPage(bookName);
				std::cout << '>';
				continue;
			}
			else
			{
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "getPage") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				char pagePosition[4] = "";
				int realPosition = 0;
				int counter = 1;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						if (commandLine[i] == ' ' && commandLine[i + 1] >= 48 && commandLine[i + 1] <= 57) {
							pagePosition[0] = commandLine[i + 1];
							while (commandLine[i + 2] != '\0') {
								pagePosition[counter] = commandLine[i + 2];
								i++;
								counter++;
							}
							break;
						}
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				realPosition = atoi(pagePosition);
				kindle.getPage(bookName, realPosition);
				std::cout << '>';
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "changeTitle") == 0)
		{
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				char newTitle[BUFFER_LINE_SIZE] = "";
				std::cout << ">>Enter new title:";
				std::cin.getline(newTitle, BUFFER_LINE_SIZE);
				if (newUser.changeTitle(bookName, newTitle)) {
					kindle.changeTitle(bookName, newTitle, outputBooks);
				}

				std::cout << ">";
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "deletePage") == 0) {
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				char pagePosition[4] = "";
				int realPosition = 0;
				int counter = 1;
				while (commandLine[i] != '\0')
				{
					if (i >= firstArgSize + 1) {
						if (commandLine[i] == ' ' && commandLine[i + 1] >= 48 && commandLine[i + 1] <= 57) {
							pagePosition[0] = commandLine[i + 1];
							while (commandLine[i + 2] != '\0') {
								pagePosition[counter] = commandLine[i + 2];
								i++;
								counter++;
							}
							break;
						}
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				realPosition = atoi(pagePosition);
				kindle.getPage(bookName, realPosition);
				std::cout << '>';
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(firstArg, "changeRate") == 0) {
			if (userLogged) {
				char bookName[BUFFER_LINE_SIZE] = "";
				char line[BUFFER_LINE_SIZE] = "";
				int i = 0;
				char newRate[4] = "";
				int realNewRate = 0;
				int counter = 1;
				while (commandLine[i] != '\0') {
					if (i >= firstArgSize + 1) {
						if (commandLine[i] == ' ' && commandLine[i + 1] >= 48 && commandLine[i + 1] <= 57) {
							newRate[0] = commandLine[i + 1];
							while (commandLine[i + 2] != '\0') {
								newRate[counter] = commandLine[i + 2];
								i++;
								counter++;
							}
							break;
						}
						bookName[i - firstArgSize - 1] = commandLine[i];
					}
					i++;
				}
				realNewRate = atoi(newRate);
				Rating newRating(realNewRate, newUser.getUserName());
				char fileName[MAX_SIZE] = "";
				int t = 2;
				fileName[0] = 'R';
				fileName[1] = '-';
				while (bookName[t - 2] != '\0') {
					fileName[t] = bookName[t - 2];
					t++;
				}
				fileName[t] = '.';
				fileName[t + 1] = 't';
				fileName[t + 2] = 'x';
				fileName[t + 3] = 't';
				newUser.changeRating(bookName, fileName, newUser.getUserName(), realNewRate);
				std::cout << '>';
				continue;
			}
			else {
				std::cout << "First you have to login!";
			}
		}
		else if (strcmp(commandLine, "logout") == 0)
		{
			kindle.logout();
			userLogged = false;
		}
		else
		{
		std::cout << "Invalid command! Valid commands are: login, signup, logout.";
		}
		std::cout << std::endl << '>';
	}
}