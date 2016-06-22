
#include <iostream>
#include <iomanip> // cout formatting
using namespace std;

// functions prototypes
int reversePos(int num); // reverse positive integer
int getDigit(int num, int index); // return the index'th digit of num
int numDigits(int num);  // return the number of digits in num
void reverseInPlace(int &n); // reverse by passing by reference

int main()
{
	// =======================================
	// === Task 0 & 1 ===
	// ========================================

	int num; // user inputs num
	int newNum = 0; // holds num reversed

	do {
		cout << "\tTask 0 & 1\ninput a value for num: ";
		cin >> num;
	} while (num > 1023 || num < 1);


	// display a table of integes and their reverses for all
	// multiples of n from 1 to 1023 inclusive

	for (int count = num; count <= 1023; count *= 2)
	{
		newNum = reversePos(count); // reverse num and store in newNum

		cout << "  " << left << setw(10) << count << right << setw(10) << newNum << endl;
	}


	// ========================================
	// === Task 2 ===
	// ========================================

	int num2; // user inputs num3
	newNum = 0; // reset. holds num reversed

	do {
		cout << "\n\tTask 2\ninput a value for num2: ";
		cin >> num2;
	} while (num2 > 1023 || num2 < -1023);

	// display a table of integes and their reverses for all
	// multiples of n from -1023 to 1023 inclusive

	for (int count = num2; count <= 1023 && count >= -1023; count *= 2)
	{
		num2 = count;
		reverseInPlace(num2); // reverse num3 by referece

		cout << "  " << left << setw(10) << count << right << setw(10) << num2 << endl;
	}

	return 0;
}

// ====================================
// function definitions *****
// ====================================

// pass by reference reversal
// precondition: num is between 1023 and -1023
// postcondition: no return value, n is modified by reference
void reverseInPlace(int &n)
{
	n = reversePos(n);
}


// reverse positive integer
// precondition: num > 0
// postcondition: the return value is num read backwords (in decimal)
int reversePos(int num)
{

	int newNum = 0; // holds num reversed

	int totalDig; // holds total digits
	int theDigit; // holds the index'th digit

				  // get the num of digits in num
	totalDig = numDigits(num);

	// reverse the digits
	for (int count = 0; count < (totalDig); count++)
	{
		// get the count'th digit from num
		theDigit = getDigit(num, count);

		// place num's count'th digit in correct position to obtain the reverse of num

		int place = 1; // multiply the digit by this to set correct decimal value of rev num digits

					   // how many zeroes to add to int place
		for (int i = (totalDig - 1); i > count; i--)
		{
			place *= 10;
		}
		// set the reverse decimal value for the digit
		theDigit *= place;

		// accumulate all the digits(in their right decimal places) to create the new num in reverse
		newNum += theDigit;
	}

	return newNum;
}

// return the index'th digit of num
// precondition: num > 0 index >= 0
// postcondition: the return value is the index'th digit of num
int getDigit(int num, int index)
{
	int digit; // holds the index'th digit of num

	int place = 1; // divide num by this before performing % 10. (holds the correct decimal place before %10)
				   // how many zeroes to add to int place
	for (int count = 0; count < index; count++)
	{
		place *= 10;
	}

	// get index'th digit
	digit = (num / place) % 10;

	return digit;

}

// return the number of digits in num
// precondition: num > 0
// postcondition: the return value is the number of digits in num
int numDigits(int num)
{
	int digits; // counts number of digits

	for (digits = 0; num != 0; digits++)
	{
		num /= 10;
	}

	return digits;
}




// ========== other/notes =======

/*  (Sample for algorithm construction) To reverse a 3 digit num:

// first digit
tempNum = ((num / 1) % 10) * 100;

// after first num, get second number
tempNum += ((num / 10) % 10) * 10;

// third num.
tempNum += ((num / 100) % 10) * 1;

cout << tempNum << endl;
*/
