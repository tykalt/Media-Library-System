#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Media.h"
#include "Movie.h"
#include "Book.h"
#include "Song.h"
using namespace std;

// PRE: accepts a string
// POST: returns true if the string is a number, false otherwise
bool isDigits(string str1);

// PRE: accepts input and output streams, and a vector of Media pointers
// POST: reads media data from the input stream and populates the vector
void readMediaList(istream &i, ostream &o, vector<Media*> &m);

// PRE: accepts a command string, output streams, and a vector of Media pointers
// POST: processes the command and performs the corresponding action
void handleCommand(const string& commandRecord, ostream& out, ostream& err, vector<Media*>& mediaLib);

// PRE: accepts a vector of tokens, output streams, and a vector of Media pointers
// POST: adds a new Media object to the vector if the tokens are valid
void addMedia(const vector<string>& tokens, ostream& out, ostream& err, vector<Media*>& mediaLib);

// PRE: accepts a type character, an output stream, and a vector of Media pointers
// POST: prints all Media objects of the specified type to the output stream
void printByType(char type, ostream& out, const vector<Media*>& mediaLib);

// PRE: accepts a type character, a minimum rating, an output stream, and a vector of Media pointers
// POST: prints all Media objects of the specified type with a rating >= minRating
void printByRating(char type, int minRating, ostream& out, const vector<Media*>& mediaLib);

// PRE: accepts a type character, a genre string, an output stream, and a vector of Media pointers
// POST: prints all Media objects of the specified type with the specified genre
void printByGenre(char type, const string& genre, ostream& out, const vector<Media*>& mediaLib);

// PRE: accepts an output stream and a vector of Media pointers
// POST: prints all Media objects in the vector to the output stream
void printAll(ostream& out, const vector<Media*>& mediaLib);

// PRE: accepts an output stream and a vector of Media pointers
// POST: prints the total count of each type of Media object in the vector
void printTotals(ostream& out, const vector<Media*>& mediaLib);


