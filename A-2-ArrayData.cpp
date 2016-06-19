
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // cout formatting
#include <cmath> // abs value for growth rate ifnegative growth
#include <vector>

using namespace std;

const int MAX_COUNTRIES = 500;

// structure and class definitions
struct Country {
	string name; // name of country
	// popululation of country for each specific year
	long double pop1950;
	long double pop1970;
	long double pop1990;
	long double pop2010;
	long double pop2015;

	// store growth rates for each country
	long double growth1950to1970;
	long double growth1970to1990;
	long double growth1990to2010;
	long double growth2010to2015;

};

struct World {
	int numCountries;
	Country countries[MAX_COUNTRIES];
	// indices of 3 largest countries
	int first, second, third;
} myWorld; // myWorld is an instance of World

// function definitions
void initializeWorldObject(World& myWorld, ifstream& popFile);



int main()
{

	// =======================================
	// Task 0
	// =======================================

	// open file to input data from it to another variable
	ifstream  popFile; // open for input
	popFile.open("population.csv");
	if (popFile.fail())
	{
		cout << "Error opening file\n";
	}

	// inititialize myWorld(instance of World) to the data read from datafile in popFile
	// note: original population has been multiplied by 1000
	initializeWorldObject(myWorld, popFile);


	// =======================================
	// Task 1
	// =======================================

	// Precondition: there are at least three countries
	// for 2015 poplulation, print the 3 largest countries in order
	// -Modified the data structure to store the indices of the 3 countries (for quick access)

	// local vars to hold indices of 3 largest countries
	int localFirst = 0, localSecond = 0, localThird = 0;


	for (int i = 0; i < myWorld.numCountries; i++)
	{
		if (myWorld.countries[i].pop2015 > myWorld.countries[localFirst].pop2015)
		{
			localFirst = i;
		}

		// 	i is less than the localfirst and i is greater than local second
		if ((myWorld.countries[localFirst].pop2015 > myWorld.countries[i].pop2015) && (myWorld.countries[localSecond].pop2015 < myWorld.countries[i].pop2015))
		{
			localSecond = i;

		}

		//  i is less than the localsecond and i is greater than localthird.
		if ((myWorld.countries[localSecond].pop2015 > myWorld.countries[i].pop2015) && (myWorld.countries[localThird].pop2015 < myWorld.countries[i].pop2015))
		{
			localThird = i;
		}

	}

	// pass the indices
	myWorld.first = localFirst;
	myWorld.second = localSecond;
	myWorld.third = localThird;

	// display the 3 largest countries in order with their populations from 2015
	cout << fixed << setprecision(0); // cout formatting to display floating point not scientific notation

	cout  << "The largest country is"<< myWorld.countries[localFirst].name << ", which had "
		  << myWorld.countries[localFirst].pop2015 << " people in 2015" << endl;

	cout << "\nThe second largest country is" << myWorld.countries[localSecond].name << ", which had "
		<< myWorld.countries[localSecond].pop2015 << " people in 2015" << endl;

	cout << "\nThe third largest country is" << myWorld.countries[localThird].name << ", which had "
		<< myWorld.countries[localThird].pop2015 << " people in 2015" << endl;


	// =======================================
	// Task 2
	// =======================================


	//calculate  growth rate: (new pop - prev pop/  prev pop ) * 100  or  (difference/initialPopulation * 100)
	for (int i = 0; i < myWorld.numCountries; i++)
	{
		// calculate growth rate for all intervals and store it in the data structure
		myWorld.countries[i].growth1950to1970 = abs( ((myWorld.countries[i].pop1970 - myWorld.countries[i].pop1950) / myWorld.countries[i].pop1950) * 100 );
		myWorld.countries[i].growth1970to1990 = abs( ((myWorld.countries[i].pop1990 - myWorld.countries[i].pop1970) / myWorld.countries[i].pop1970) * 100 );
		myWorld.countries[i].growth1990to2010 = abs( ((myWorld.countries[i].pop2010 - myWorld.countries[i].pop1990) / myWorld.countries[i].pop1990) * 100 );
		myWorld.countries[i].growth2010to2015 = abs( ((myWorld.countries[i].pop2015 - myWorld.countries[i].pop2010) / myWorld.countries[i].pop2010) * 100 );
	}

	// output the fastest growing country for each interval

	// 4 variables to hold index for fastest growing country for each of 4 intervals
	int fast1950 = 0;
	int fast1970 = 0;
	int fast1990 = 0;
	int fast2010 = 0;


	for (int i = 0; i < myWorld.numCountries; i++)
	{
		if (myWorld.countries[i].growth1950to1970 > myWorld.countries[fast1950].growth1950to1970)
		{
			fast1950 = i;
		}

		if (myWorld.countries[i].growth1970to1990 > myWorld.countries[fast1970].growth1970to1990)
		{
			fast1970 = i;
		}

		if (myWorld.countries[i].growth1990to2010 > myWorld.countries[fast1990].growth1990to2010)
		{
			fast1990 = i;
		}

		if (myWorld.countries[i].growth2010to2015 > myWorld.countries[fast2010].growth2010to2015)
		{
			fast2010 = i;
		}
	}

	// output the fastest growing country for four intervals
	cout << "\n\nThe fastest growing country between 1950 and 1970 is" << myWorld.countries[fast1950].name << endl;
	cout << "\nThe fastest growing country between 1970 and 1990 is" << myWorld.countries[fast1970].name << endl;
	cout << "\nThe fastest growing country between 1990 and 2010 is" << myWorld.countries[fast1990].name << endl;
	cout << "\nThe fastest growing country between 2010 and 2015 is" << myWorld.countries[fast2010].name << endl;


	// =======================================
	// Task 3
	// =======================================

	vector<int> meetCond; // indices of countries that meet both conditions

	// at least 20% of 3rd largest country's population in 2015
	long double conditionOne = 0.20 * myWorld.countries[myWorld.third].pop2015;


	// larger growth rate in 2015 than the 3rd largest country.
	long double conditionTwo = myWorld.countries[myWorld.third].growth2010to2015;

	// get the indices of all such countries that meet both conditions
	for (int i = 0; i < myWorld.numCountries; i++)
	{
		if ((myWorld.countries[i].pop2015 >= conditionOne) && myWorld.countries[i].growth2010to2015 > conditionTwo)
		{
			// pushback these countries(represented as indices) to the vector
			meetCond.push_back(i);
		}
	}
	cout << "\n\nList of countries that meet both conditions:\n";
	// display the countries
	for (int i = 0; i < meetCond.size(); i++)
	{
		cout << myWorld.countries[meetCond[i]].name << endl;
	}


	return 0;
} // <-end main

// ====================================================
// Functon Definitons
// ====================================================

void initializeWorldObject(World& myWorld, ifstream& popFile)
{
	// inititialize myWorld(instance of World) to the data read from datafile in popFile

	// local population variables
	long double locpop1950;
	long double locpop1970;
	long double locpop1990;
	long double locpop2010;
	long double locpop2015;

	string localname; // local var for country name
	int locnumCountry = 0; // local # of countries

	// while not at the end of the file
	while (popFile >> locpop1950 >> locpop1970 >> locpop1990 >> locpop2010 >> locpop2015)
	{
		// getline for country name (b/c it has spaces)
		// make sure not at the end of the file
		if (!popFile.eof()) // we will not be at end of file-this is not needed
		{
			getline(popFile, localname);
		}

		// initialize myWorld accordingly
		myWorld.countries[locnumCountry].pop1950 = locpop1950 * 1000;
		myWorld.countries[locnumCountry].pop1970 = locpop1970 * 1000;
		myWorld.countries[locnumCountry].pop1990 = locpop1990 * 1000;
		myWorld.countries[locnumCountry].pop2010 = locpop2010 * 1000;
		myWorld.countries[locnumCountry].pop2015 = locpop2015 * 1000;
		myWorld.countries[locnumCountry].name = localname;

		// keep count of the number of countries - must increment after initialization of myWorld
		locnumCountry++;
	}

	// we're done calculating total number of countries, assign the value
	myWorld.numCountries = locnumCountry;

	// NOTE: USE DEBUGGER TO SEE IF IT WAS INITIALIZED WITH CORRECT VALUES
}
