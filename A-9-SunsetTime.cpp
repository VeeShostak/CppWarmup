
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int main()
{
	// ==== Task 0: =====

	string instr = "John Doe";	// name of to use
	int sunTimeH,	// stores sunset time in hours
		sunTimeM;	// stores sunset time in minutes

	// ask user for today's sunset time
	// use do while loop for error-checking
	do {
		cout << "Enter the hours part of today's sunset time (1-12): ";
		cin >> sunTimeH;
	} while (sunTimeH < 1 || sunTimeH > 12);

	do {
		cout << "Enter the minutes part of today's sunset time (0-59): ";
		cin >> sunTimeM;
	} while (sunTimeM < 0 || sunTimeM > 59);

	// convert the user's sunset time to a 24 hour format for easier calculation
	sunTimeH += 12;

	// retrieve the current time (24 hour format)
	time_t t;
	struct tm *now;
	t = time(0);			// get current time
	now = localtime(&t);	// adjust for local timezone
	int hour = now->tm_hour;	// retrieve current hour
	int min = now->tm_min;	// retrieve current min

	// ==============================================================================
	// Determine if it is morning, afternoon, or evening.
	// ==============================================================================

	// Determine if Before or After sunset: ( needed b/c if hours equal, we decide by min)
	// if hourLessSunH is true, then it is before sunset
	bool hourLessSunH = true;

	if (hour == sunTimeH) // when hours are equal determine by minutes
	{
		// it is before sunset
		if (min < sunTimeM)
		{
			hourLessSunH = true;
		}
		// it is after sunset
		else if (min >= sunTimeM)
		{
			hourLessSunH = false;
		}
	}

	// it is after sunset
	else if (hour > sunTimeH)
	{
		hourLessSunH = false;
	}

	// it is before sunset
	else if (hour < sunTimeH)
	{
		hourLessSunH = true;
	}


	// *===== CASES =====*

	// morning is before sunset and before 12
	if (hour < 12 && hourLessSunH)
	{
		cout << "Good morning " << instr << endl;
	}

	// afternoon is before sunset and after 12
	else if (hour > 12 && hourLessSunH)
	{
		cout << "Good afternoon " << instr << endl;
	}

	// evening is after sunset
	else if (!(hourLessSunH))
	{
		cout << "Good evening " << instr << endl;
	}

	// =============================================
	// ==== Task 1: =====
	// =============================================

	// ==== determine when it will be dark ====

	int darkHours,		// in how many hours it will be dark
		darkMinutes;	// in how many minutes it will be dark

	// if it is after sunset, get the time until the following sunset
	if (!(hourLessSunH))
	{
		// find how much time passed after sunset
		darkHours = hour - sunTimeH;	// temporarily store value


		// Algorithm for Minutes (adjusts hour if necessary (if too many minutes))
		// if the current min is higher than sunset Min, get difference -no need for other algorithm
		if (min >= sunTimeM)
		{
			darkMinutes = min - sunTimeM;
		}
		// if current min is less than sunset min, adjust the hour and min accordingly
		else if (min < sunTimeM)
		{
			darkMinutes = min - sunTimeM;
			// minus 1 from the hour and find the right number of minutes before its dark
			--darkHours;
			darkMinutes = 60 + darkMinutes; // adds a negative value to 60 to find min
		}

	}

	// if it is before sunset, find in how long(hours & min) the sun will set
	if (hourLessSunH)
	{
		darkHours = sunTimeH - hour;

		// Algorithm for Minutes (adjusts hour if necessary (if too many minutes)
		// if the current min is higher than sunset Min, adjust the hour and min accordingly
		if (min > sunTimeM)
		{
			darkMinutes = sunTimeM - min;	// darkMinutes will be a negative value
			// minus 1 from the hour and find the right number of minutes before its dark
			--darkHours;
			darkMinutes = 60 + darkMinutes; // adds a negative value to 60 to find min
		}
		// if the current minute is less than or equal to the sun set time min then the number of hours and
		// minutes will be correct if we find difference -no need for a different algorithm
		else if (min <= sunTimeM)
		{
			darkMinutes = sunTimeM - min;
		}
	}

	// display in how long it will be dark
	cout << "It will be dark in " << darkHours << " hours"
		 << " and " << darkMinutes << " minutes. \n";


	// ==================================================
	// *** Ask user in how many minutes he will be home
	// *** after user gets home decide whether it will be dark or light
	// assume the following sunrise has not yet happened

	int minToHome;	// stores in how many min the user will be home

	cout << "How many minutes from now do you expect to be home? ";
	cin >> minToHome;

	// time it will be when user gets home
	min = min + minToHome;

	// adjust time if min over 60 for proper format
	if (min > 60)
	{
		// find how many hours in those minutes and append them to current hour
		hour = hour + (min / 60);
		min = (min % 60); // remainder is the minutes
	}

	// decide if it will be dark or light

	string getHome = "light";	// once user gets home it will be light or dark

	// decide if it is passed sunset. ( needed b/c if hours equal, we decide by min)
	bool passedSunset = true;

	// passed sunset
	if (hour > sunTimeH)
	{
		passedSunset = true;
	}
	// before sunset
	else if (hour < sunTimeH)
	{
		passedSunset = false;
	}

	else if (hour == sunTimeH) // if hours equal determine by minutes
	{
		// passed sunset
		if (min >= sunTimeM)
		{
			passedSunset = true;
		}
		// before sunset
		else if (min < sunTimeM)
		{
			passedSunset = false;
		}
	}

	// CASES for light or dark after user gets home

	// it is passed sunset, dark
	if (passedSunset)
	{
		getHome = "Dark";
	}

	// it is before sunset, light
	else if (!(passedSunset))
	{
		getHome = "Light";
	}

	// display
	cout << "When you get home it will be " << getHome << endl;



	return 0;
}
