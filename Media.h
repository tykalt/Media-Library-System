#pragma once
#include <string>
#include <iostream>
using namespace std;

class Media {
protected:
  char type;
  string title;
  string name;
  int rating;
  string genre;
  int length;
  int yearReleased;

public:
  Media();

  Media(char c, string t, string n, int r, string g, int l, int yr) {
    type = c;
    title = t;
    name = n;
    rating = r;
    genre = g;
    length = l;
    yearReleased = yr;
  }

  // getters
  char getType() { return type; }
  string getTitle() { return title; }
  string getName() { return name; }
  int getRating() { return rating; }
  string getGenre() { return genre; }
  int getLength() { return length; }
  int getYearReleased() { return yearReleased; }

  // setters
  void setType(char c) { type = c; }
  void setTitle(string t) { title = t; }
  void setName(string n) { name = n; }
  void setRating(int r) { rating = r; }
  void setGenre(string g) { genre = g; }
  void setLength(int l) { length = l; }
  void setYearReleased(int yr) { yearReleased = yr; }

  // virtual destructor
  virtual ~Media() {}

  // pure virtual function for polymorphic printing
  virtual void print(ostream& out, const vector<Media*>& mediaLib) = 0;
};
