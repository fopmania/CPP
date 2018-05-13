#include "stdafx.h"
#include "Palindrome.h"
#include <ctype.h>

Palindrome::Palindrome()
{
}


Palindrome::~Palindrome()
{
}
bool Palindrome::isPalindrome(const std::string& word)
{
	for (int i = 0; i < word.length() / 2; i++) {
		if (tolower(word.at(i)) != tolower(word.at(word.length() - i - 1))) {
			return false;
		}
	}
	return true;
}
