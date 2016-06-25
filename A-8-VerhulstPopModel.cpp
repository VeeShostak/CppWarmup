
#include <iostream>
#include <iomanip> // cout formatting

using namespace std;

int main()
{

	// === Task 0:
	
	// variables for the formula inputted by the user
	double g,  // population growth rate
	       h,  // minimum loss rate
		   M,  // carrying capacity
		   pN; // p(n). It needs a starting value for p(0) initial population

	// variable for the table
	int maxYear; // max number of years to calculate and to show in table

	// ===== User enters parameters (error check all parameters)

	do {
		cout << "Enter population growth rate percentage (%): ";
		cin >> g;
	} while (g < 0);
	g = g / 100; // convert g percent value to a decimal value for use in the formula

	do {
		cout << "Enter minimum loss rate percentage (%): ";
		cin >> h;
	} while (h < 0 || h > 100); // h must be less than 100%
	h = h / 100; // convert h percent value to a decimal value for use in the formula

	do {
		cout << "Enter carrying capacity: ";
		cin >> M;
	} while (M < 1); // there needs to be a carrying capacity of at least 1

	do {
		// enter p(0) for the initial population
		cout << "Enter the initial population: ";
		cin >> pN;
	} while (pN < 1); // there needs to be an initial population of at least 1

	do {
		// 1 to k years (ask for k years)
		cout << "Calculate from 1 to how many years? (max year): ";
		cin >> maxYear;
	} while (maxYear < 1); // we must show the table for at least 1 year


	// cout formatting, shows population ROUNDED to 2 decimal places
	cout << setprecision(2) << fixed << showpoint;

	// ===== print from year 0 to maxYear(user defined)
	// table uses setw (set width), so if Population is greater than the set setw display value
	// cout will override the setw value. (setw only specifies the minimum number of positions
	// in the print field)

	int n;  // counting variable for year

	cout << "\n\tTable \n\n";
	for (n = 0; n < maxYear; n++)
	{
		// pupulation for year n+1
		double population = ((1 + g - h) * pN) - (g*(pN * pN) / M);

		// format  table
		cout  << left << setw(10) << "Year" << "     "  << right <<  setw(12) << "Population" << endl;
		cout  << left << setw(10) << (n + 1) << "     " << right << setw(12) << population << endl << endl;

		// set p(n) to the new population so we can calculate p(n+1) the next year's
		// population. (this is needed for the formula)
		pN = population;
	}


	/*
	Task 1: Behavior of g:

	Note: Here we are speaking of g in terms of it being in decimal form (g/100).

	===== critical values of g leading to oscillating bahavior:

	*As the value of g remains between 2 and 2.6 (including) (2 <= g <= 2.6),
	we see oscillating behavior in the population*


	===== critical values of g leading to chaotic bahavior:

	*As the value of g remains greater than 2.6 (g > 2.6)
	we see chaotic behavior in the population*
	From that point, as the value of g increases the more chaotic the population becomes.
	*/

	return 0;
}
