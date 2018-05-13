#include "stdafx.h"
#include "TextInput.h"
#include <iostream>

TextInput::TextInput()
{
}


TextInput::~TextInput()
{
}



void runTextInput() {
	TextInput* input = new NumericInput();
	input->add('1');
	input->add('a');
	input->add('0');
	std::cout << input->getValue();

	std::cout << ((TextInput*)input)->run();
}