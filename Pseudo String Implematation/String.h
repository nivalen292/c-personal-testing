#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>

// TODO: overload funcs for const char* and char*

class StringArray;

class String {
private:
	char* arr; 
	int length;
	int capacity;
	void copy(const String& other);
	void del();
	bool lookFor(int start, int end, const char* target) const;
	void changeCapacity(int newCap);
public:
	String();
	String(const char* arr);
	String(const String& other);
	~String();
	int getLength() const;
	void concat(const String& other);
	void concat(const char c);
	String& operator=(const String& other);
	String& operator+=(const String& other);
	String& operator+=(const char c);
	String operator+(const String& other) const;
	char& operator[](int index); // overload for const char& and change argument in operator<<
	bool find(const String& target) const;
	int findIndex(const String& target, int start = 0) const;
	void replace(const String& target, const String& source, bool global = false);
	const char* c_str() const;
	String slice(int start = 0, int end = -1) const;
	StringArray split(const String& separator) const;

	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);
	friend void getline(std::istream& is, String& str, char endChar);
};


class StringArray {
private:
	int length;
	String* arr;

	void del();
	void copy(const StringArray& other);
	void changeLength(int length);
public:
	StringArray();
	StringArray(const StringArray& other);
	StringArray& operator=(const StringArray& other);
	~StringArray();

	void add(const String& str);
	String join(const char* unionStr);
};


std::ostream& operator<<(std::ostream& os,const String& str);
std::istream& operator>>(std::istream& is, String& str); // fix not flushing properly
void getline(std::istream& is, String& str, char endChar = '\n');

#endif