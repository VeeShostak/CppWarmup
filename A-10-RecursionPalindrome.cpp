
#include <string>
#include <iostream>
#include <ctype.h> // for toupper tolower
using namespace std;

// function prototypes
void removePunct(string &str);
bool checkPalindrome(string str);


int main()
{

	// ==========================
	// Task 0
	// ==========================

	cout << "\n\tTask 2\n";
	string str2nd;
	// input string from user
	cout << "Enter a string: ";
	cin >> str2nd;
	removePunct(str2nd); // remove punctuation from the string

	// call the recursive function to check if the string is a palindrome
	if (checkPalindrome(str2nd) )
	{
		cout << "The string is a palindrome.\n";
	}
	else
	{
		cout << "The string is NOT a palindrome.\n";
	}



// ==========================
// ==========================
// Function definitions
// ==========================

// remove all punctuation and make all chars in string lowercase
void removePunct(string &str)
{
	string cleanStr = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (tolower(str[i]) >= 'a' && tolower(str[i]) <= 'z')
		{
			cleanStr += tolower(str[i]);
		}
	}

	str = cleanStr;
	return;
}


// checks palindromes for even and odd string lengths. returns true if string is a palindrome
// for x being the original string,
// palindrom(x) = x[0]==x[n-1] AND palindrome(x[1], x[n-2]) ... palindrome(x[middle], x[middle] )
bool checkPalindrome(string str)
{
	int len = str.length();
	string right = str.substr((len - 1), 1);// right character
	string left = str.substr(0, 1); // left character

	// if at least one char not equal, return false
	if (left != right)
	{

		return false;
	}
	// compared everything, did not return false, so its a palindrome.
	// for str odd length, len will be 1, and for str even length,  len will be 2
	if (len <= 2)
	{
		return true;
	}
	str = str.substr((0 + 1), (len - 2)); // update: AND palindrome(x[1], x[n-2]) ...
	return checkPalindrome(str); // keep comparing
}
