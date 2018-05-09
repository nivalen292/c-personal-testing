#include "stdafx.h"
#include "String.h"

void String::copy(const String & other) {
	capacity = other.capacity;
	length = other.length;
	arr = new char[capacity];
	strcpy_s(arr, capacity, other.arr);
}

void String::del() {
	delete[] arr;
}

bool String::lookFor(int start, int targetLen, const char * target) const {
	int index = 0;
	for (int i = start; i < start + targetLen; i++) {
		if (arr[i] != target[index++]) {
			return false;
		}
	}
	return true;
}

void String::changeCapacity(int newCap) {
	char* temp = arr;
	arr = new char[newCap];
	for (int i = 0; i < capacity && i < newCap; i++) {
		arr[i] = temp[i];
	}
	delete[] temp;
	if (capacity > newCap) {
		
		arr[capacity - 1] = '\0';
		length = strlen(arr);
	}
	capacity = newCap;
}

String::String() : arr(NULL), length(0), capacity(0) {
}

String::String(const char* arr) {
	capacity = strlen(arr) + 1;
	length = strlen(arr);
	this->arr = new char[capacity];
	strcpy_s(this->arr, capacity, arr);
}

String::String(const String & other) {
	copy(other);
}

String::~String() {
	del();
}

String & String::operator=(const String & other) {
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
}

int String::getLength() const {
	return length;
}

void String::concat(const String & other) {
	char* temp = arr;
	capacity = length + other.length + 1;
	length = length + other.length;
	arr = new char[capacity]();
	if (temp != NULL) {
		strcpy_s(arr, strlen(temp) + 1, temp);
	}
	strcat_s(arr, capacity, other.arr);
	delete[] temp;
}

void String::concat(const char c) {
	char str[2] = "";
	str[0] = c;
	operator+=(String(str));
}

String& String::operator+=(const String & other) {
	concat(other);
	return *this;
}

String & String::operator+=(const char c) {
	char str[2] = "";
	str[0] = c;
	operator+=(String(str));
	return *this;
}

String String::operator+(const String & other) const {
	String s(arr);
	s.concat(other);
	return s;
}

char& String::operator[](int index) {
	if (length > 0) {
		if (index >= 0 && index < length) {
			return arr[index];
		}
		else if (index < 0) {
			index = -index;
			index %= length;
			return arr[length - index];
		}
		else if (index > length) { 
			index %= length;
			return arr[index];
		}
	}
}

bool String::find(const String & target) const {
	return findIndex(target) != -1;
}

int String::findIndex(const String & target, int start) const {
	for (int i = start; i < length; i++) {
		if (lookFor(i, target.length, target.arr)) {
			return i;
		}
	}
	return -1;
}

void String::replace(const String & target, const String & source, bool global) {
	String result;
	if (global) {
		for (int i = 0; i < length; i++) {
			if (lookFor(i, target.length, target.arr)) {
				result += source;
				i += (source.length - 1);
			}
			else {
				result += arr[i];
			}
		}
	}
	else {
		bool replaced = false;;
		for (int i = 0; i < length; i++) {
			if (lookFor(i, target.length, target.arr) && !replaced) {
				replaced = true;
				result += source;
				i += (source.length - 1);
			}
			else {
				result += arr[i];
			}
		}
	}
	*this = result;
}

const char * String::c_str() const {
	return arr;
}

String String::slice(int start, int end) const {
	end = (end == -1) ? length : end;
	if (end >= length || end < 0) {
		return String();
	}
	String result;
	for (int i = start; i < end; i++) {
		result += arr[i];
	}
	return result;
}

StringArray String::split(const String& separator) const {
	StringArray result;
	int lastMatch = 0;

	for (int i = 0; i < length; i++) {
		if (lookFor(i, separator.length, separator.arr)) {
			result.add(slice(lastMatch, i));
			lastMatch = i + separator.length - 1;
		}
	}

	return result;
}

std::ostream & operator<<(std::ostream & os, const String & str) {
	for (int i = 0; i < str.length; i++) {
		os << str.arr[i];
	}
	return os;
}

std::istream & operator>>(std::istream & is, String & str) {
	char c;
	is.get(c);
	while (c != ' ' && c != '\n' && !is.eof()) {
		str += c;
		is.get(c);
	}
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // for filestreams is.ignore(std::numeric_limits<std::streamsize>::max());
	return is;
}

void getline(std::istream & is, String & str, char endChar) {
	char c;
	is.get(c);
	while (c != '\n' && c != endChar && !is.eof()) {
		str += c;
		is.get(c);
	}
}

void StringArray::del() {
	delete[] arr;
}

void StringArray::copy(const StringArray & other) {
	arr = new String[other.length];
	for (int i = 0; i < other.length; i++) {
		arr[i] = other.arr[i];
	}
	length = other.length;
}

void StringArray::changeLength(int length) {
	String* temp = arr;
	arr = new String[length];
	for (int i = 0; i < length && i < this->length; i++) {
		arr[i] = temp[i];
	}
	delete[] temp;
	this->length = length;
}

StringArray::StringArray() : arr(NULL), length(0) {
}

StringArray::StringArray(const StringArray & other) {
	copy(other);
}

StringArray & StringArray::operator=(const StringArray & other) {
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
}

StringArray::~StringArray() {
	del();
}

void StringArray::add(const String & str) {
	changeLength(length + 1);
	arr[length - 1] = str;
}

String StringArray::join(const char * unionStr) {
	String result;
	for (int i = 0; i < length; i++) {
		result += arr[i];
		if (i != length - 1) {
			result += String(unionStr);
		}
	}
	return result;
}
