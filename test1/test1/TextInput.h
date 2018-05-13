#pragma once
#include <string>
#include <ctype.h>
class TextInput
{
protected:
	std::string val;
public:
	TextInput();
	~TextInput();

	virtual void add(char c) {
		val.push_back(c);
	}
	std::string getValue() {
		return val;
	}


	virtual std::string run() {
		return "TextInput";
	}
};

class NumericInput : public TextInput 
{ 

public:
	void add(char c) {
//		if (isdigit(c)) {
		if ('0' <= c && c <= '9') {
				val.push_back(c);
		}
	}

	virtual std::string run() {
		return "NumericInput";
	}

};



void runTextInput();