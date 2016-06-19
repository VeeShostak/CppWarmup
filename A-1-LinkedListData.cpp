
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // cout formatting
using namespace std;

// structs and classes
struct Country
{
	string name;
	double population;
};

struct Node {
	Country ctry;
	Node* next; // points to next node, or points to NULL if on last node of the list
};

// function prototypes
void printCountry(Node* &world, string name);
void update(Node* &world, Country c);
void merge(Node* &world, string ctry1, string ctry2, string newctry);

int main()
{
	// !!!
	// NOTE in task 0: I have code that gets rid of first whitespace character in country name in the file
	// and stores the name w/o 1st whitespace char in the list. -We get rid of an extra whitespace, since
	// the original file provided in the problem has this formatting
	// !!!

	// =======================================
	// Task 0
	// =======================================
	// Preconditions: -csv file with proper order of data (5 columns have 5 populations and 6th column is name of country).
	// -6th column, name of country, contains a space in front of the country name (this precond is needed b/c we
	// have code that gets rid of this extra whitespace, since the original file provided in the problem has this formatting).

	// input the name and current population of each country into a linked list, where
	// each node is of the type country

	// open for input
	ifstream popFile;
	popFile.open("population.csv");
	if (popFile.fail())
	{
		cout << "Error opening file\n";
	}

	// local variables to read from file and store the ones we need
	long double locpop1950;
	long double locpop1970;
	long double locpop1990;
	long double locpop2010;
	long double locpop2015;
	string localname;

	// for linked list
	Node* world = NULL; // head of the list
	Node* newNode; // for dynamically allocating new nodes

	// input appropriate parameters of each country into a linked list
	while (popFile >> locpop1950 >> locpop1970 >> locpop1990 >> locpop2010 >> locpop2015)
	{
		if (!popFile.eof()) // we will not be at end of file-this is not needed
		{
			getline(popFile, localname);
		}

		// get rid of first whitespace character in country name in the file and store w/o whitespace in the list
		string tempStr = "";
		for (int i = 1; i < localname.length(); i++) // i = 0  is a whitespace
		{
			tempStr += localname[i];
		}
		localname = tempStr;

		if (world == NULL) // when list is empty
		{
			newNode = new Node; // create new node
			// store country name and population
			newNode->ctry.name = localname;
			newNode->ctry.population = locpop2015;

			newNode->next = NULL; // this is the last node ( and the first). last node's next points to NULL
			world = newNode; // head points to first node
		}
		else
		{
			newNode = new Node; // create new node

			// store country name and population
			newNode->ctry.name = localname;
			newNode->ctry.population = (locpop2015 * 1000);

			newNode->next = world; // this is now the first node so point to next(2nd) node
			world = newNode; // head points to new first node
		}

	}

	// =======================================
	// Task 1
	// =======================================
	// Preconditions: -the input string findName is in same format as names of countries in liked list(no extra space in front or end of string)

	cout << fixed << setprecision(0); // cout formatting to display in floating point, not scientific notation

	cout << "\tTask 1\n";
	string findName = "Madagascar"; // test value
	printCountry(world, findName);

	// =======================================
	// Task 2
	// =======================================
	// Precondition: -the list has no countries with the same name

	cout << "\n\tTask 2\n";
	Country newCountry;

	// ask user for country name and population
	cout << "Enter country name: ";
	cin >> newCountry.name;
	cout << "Enter country population: ";
	cin >> newCountry.population;

	// update population or add country if not in list
	update(world, newCountry);

	// check by calling printCountry
	printCountry(world, newCountry.name);

	// =======================================
	// Task 3
	// =======================================
	// Preconditions: -the list has no countries with the same name
	// -ctry1 and ctry2 must be different names. (-check to make sure addition of populations does not cause overflow)

	string ctry1 = "Egypt", ctry2 = "Wallis and Futuna Islands", newctry = "NEWCOUNTRYa"; // test values

	// merge populations of ctry1 and ctry2, name new country newctry by overwriting ctry 1. and deleting ctry2
	merge(world, ctry1, ctry2, newctry);

	// diplay the list to check
	Node* current = world;
	while (current != NULL)
	{
		cout << "Name: " << current->ctry.name << "  Pop: " << current->ctry.population << endl;
		current = current->next;
	}

	return 0;
} // <-end main


// ====================================================
// Functon Definitons
// ====================================================


// for Task 1: find the country by name and print its population
void printCountry(Node* &world, string name)
{
	// find the country by name and print its name and population
	Node* curr = world;
	while (curr != NULL)
	{
		if (name == curr->ctry.name)
		{
			// output
			cout << curr->ctry.name << " has " << curr->ctry.population << " people." << endl;
			break;
		}
		curr = curr->next;
	}
}


// for Task 2: if country with same name as c is already in the list pointed to by world, update its population
// otherwise c is pushed onto the list
void update(Node* &world, Country c)
{
	bool found = false;
	Node* curr = world;
	while (curr != NULL)
	{
		if (c.name == curr->ctry.name)
		{
			// change population
			curr->ctry.population = c.population;
			found = true;
			break;
		}
		curr = curr->next;
	}

	// push into the list if not found
	if (!found)
	{
		Node* newNode = new Node;
		newNode->ctry.name = c.name;
		newNode->ctry.population = c.population;

		newNode->next = world; // newNode is now the first node, so it points to next (2nd) node
		world = newNode; // head points to the new first node
	}

}


// For Task 3: 3 country names as args, merge ctry1 and ctry2 into country named newctry
void merge(Node* &world, string ctry1, string ctry2, string newctry)
{

	// search for cntry1, if match, nest loop to search for cntry 2, if found then merge
	// we will overwrite curr with appropriate parameters, and delete curr2nd

	Node* curr = world;
	bool foundBoth = false;  // breaks out of both loops if true
	while (curr != NULL && !(foundBoth))
	{
		if (curr->ctry.name == ctry1) // found first name in list
		{
			Node* curr2ndPrev = world; // previous node of curr2nd

			// curr2nd starts at second node, skips the first node(head) comparison. = preondition: list has n>=2 elements
			Node* curr2nd = curr2ndPrev->next;

			while (curr2nd != NULL && !(foundBoth)) // traverse until 2nd name is found in list
			{
				if (curr2nd->ctry.name == ctry2)
				{
					foundBoth = true; // break out of both loops since merge will be complete after this if block

					// ovewrite node with ctry1 match
					curr->ctry.name = newctry; // change the name
					curr->ctry.population += curr2nd->ctry.population; // add their populations

					// delete curr2nd
					// prev node points to node after curr2nd, since curr2nd will be deleted
					curr2ndPrev->next = curr2nd->next;

					delete curr2nd;
					curr2nd = NULL;
				}
				// if 2nd match at head, delete the first node, make head point to node after first
				else if (world->ctry.name == ctry2)
				{
					foundBoth = true; // break out of both loops since merge will be complete after this if block
					// ovewrite node with ctry1 match
					curr->ctry.name = newctry; // change the name
					curr->ctry.population += curr2nd->ctry.population; // add their populations

					// pop head(first node)
					Node* temp = world;
					world = world->next; // make head point to node after first, since we delete first node
					delete temp;
					temp = NULL;
				}
				// if 2nd match at last node, delete the last node, prev node becomes last
				else if ( (curr2nd->next == NULL) && (curr2nd->ctry.name == ctry2) )
				{
					foundBoth = true; // break out of both loops since merge will be complete after this if block
					// ovewrite node with ctry1 match
					curr->ctry.name = newctry; // change the name
					curr->ctry.population += curr2nd->ctry.population; // add their populations

					curr2ndPrev->next = NULL;
					delete curr2nd;
					curr2nd = NULL;
				}

				// traverse if merge not complete
				if ((!foundBoth))
				{
					// update both to travesrse the list
					curr2nd = curr2nd->next;
					curr2ndPrev = curr2ndPrev->next;
				}
			}
		}

		if (!(foundBoth))
		{
			curr = curr->next;
		}
	}

}
