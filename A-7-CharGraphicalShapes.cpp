
#include <iostream>
#include <iomanip> // cout formatting

using namespace std;

int main()
{

	char astr = '*'; // use an asterisk character to print shapes

	// ==========================================
	// ==========================================
	//  Part 1)

	int h,  // height of ractangle
		w;  // width of rectangle

	cout << "1) Rectangle:\n";

	// ask user for length and width
	// Error check w and l to be mininum of 3 and no negatives
	do {
		cout << "Enter width of rectangle: ";
		cin >> w;
	} while (w < 3);

	do {
		cout << "Enter height of rectangle: ";
		cin >> h;
	} while (h < 3);

	cout << endl;

	// Print the Rectangle:

	// === top of rectangle
	for (int count = 0; count < w; count++)
	{
		cout << astr;
	}
	cout << endl; // go to next line (to proceed to draw middle part of rectangle)


	// === middle of rectangle
	for (int count = 0; count < h-2; count++) // counts through rows
	{
		// first asterisk
		cout << astr;

		// spaces between asterisks
		for (int i = 0; i < w - 2; i++)
		{
			cout << " ";
		}

		// last asterisk and go to next row
		cout << astr << endl;
	}


	// === bottom of rectangle
	for (int count = 0; count < w; count++)
	{
		cout << astr;
	}

	// ==========================================
	// ==========================================
	// Part 2)

	int len;  // length of each stroke

	cout << "\n\n2) X:\n";

	// ask user for length of the stroke
	// input needs to be a minimum of 3, and take only odd values
	do {
		cout << "Enter length of leg (3 minimum & odd): ";
		cin >> len;
	} while (len < 3 || (len % 2) == 0);

	cout << endl;


	// === top part of x
	for (int count = 1; count < ((len / 2) + 1); count++) // counts through rows
	{
		// spaces for left side
		for (int z = 1; z < count; z++)
		{
			cout << " ";
		}

		cout << astr;  // left asterisk

		// space between asterisks
		for (int i = 0; i < (len - (2 * count)); i++)
		{
			cout << " ";
		}

		cout << astr << endl; // right asterisk

	}


	// === middle part of x ( 1 asterisk)
	for (int count = 0; count < (len / 2); count++)
	{
		cout << " ";
	}
	cout << astr << endl; // place the middle astr and move to next row to proceed to bottom part of x


	// === bottom part of x
	for (int count = 1; count < ((len / 2) + 1) ; count++) // counts through rows
	{

		// spaces for left side
		for (int z = 0; z < ((len / 2) - count); z++)
		{
			cout << " ";
		}

		cout << astr;  // left asterisk

		// space between 2 asterisks
		for (int i = 1; i < (2 * count); i++)
		{
			cout << " ";

		}

		cout << astr << endl; // right asterisk

	}

	// ==========================================
	// ==========================================
	// Part 3)

	int sideLower;  // length of the side

	cout << "\n3) Lower triangular part of a square:\n";

	// ask user for length of the side
	// input must be at least 2
	do {
		cout << "Enter the side length: ";
		cin >> sideLower;
	} while (sideLower < 2);

	cout << endl;

	// print lower triang part of square
	for (int count = 0; count < sideLower; count++)  // counts through rows
	{
		for (int i = 0; i < (count + 1); i++)
		{
			cout << astr;
		}
		cout << endl;
	}


	// ==========================================
	// ==========================================
	// Part 4)

	int sideUpper;  // length of the side

	cout << "\n4) Upper triangular part of a square:\n";

	// ask user for length of the side
	// input must be at least 2
	do {
		cout << "Enter the side length: ";
		cin >> sideUpper;
	} while (sideUpper < 2);

	cout << endl;

	// print upper triangle part of a square
	for (int count = 0; count < sideUpper; count++)  // counts through rows
	{
		// spaces from left
		for (int i = 0; i < count; i++)
		{
			cout << " ";
		}

		// asterisks on right
		for (int z = 0; z < (sideUpper - count); z++)
		{
			cout << astr;
		}

		cout << endl; // move to next row
	}



	// ==========================================
	// ==========================================
	// Part 5)

	int radius;  // length of the radius

	cout << "\n5) Circle:\n";

	// ask user for the radius
	// input must be at least 5 and be a multiple of 5
	do {
		cout << "Enter the radius (multiple of 5): ";
		cin >> radius;
	} while (radius < 5 || !(radius % 5 == 0));

	cout << endl;

	// print circle: inner loop takes care of x axis. if x^2 +y^2 = r^2
	// it is part of the crcrcle, if not it is outside(one space).
	// diameter is 2*r

	for (int count = 0; count <= (2 * radius); count++) // counts through rows(y-axis)
	{
		for (int i = 0; i <= (2* radius); i++) // counts through each column(x-axis)
		{
			// all of the asterisks must always be the radius apart from the the center so,
			// x^2 + y^2  needs to equal r^2  . if it does then the point is part of the circle

			int location = (count - radius)*(count - radius) + (i - radius)*(i - radius);

			// location needs to equal to r^2 for the point to be part of the circle
			if (location == (radius * radius))
			{
				cout << astr;
			}
			// if not then the point is outside so place a space
			else
			{
				cout << " ";
			}
		}

		cout << endl; // go to next row
	}


	return 0;
}
