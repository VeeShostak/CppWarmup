# C++ Warmup Programs

This is a repository containing my solutions to short C++ programs designed to give a starting foundation in software development. We will be analyzing the problem at hand and designing a solution using the C++ programming language.

##### Programs:

[1) A-1-LinkedListData](#A-1)

[2) A-2-ArrayData](#A-2)

## Program Descriptions:

*A-(assignment#)-(fileName)*


---


<a name="A-1"></a>
### A-1-LinkedListData.cpp

You will use pointers for dynamic data structures. Specifically you will be using linked lists to perform basic manipulations of data.

You will use the provided *A-1-Population.csv* file, which is a simplified version of data sourced from the UN (a few countries with non-ASCII characters in their name were left out just in case your program has problems with those).

*TASKS:*

For all tasks, you should use the following data structure for storing a country and its current population:

    struct Country {
        string  name;
        double  population;
      };
      struct Node {
        Country ctry;
        Node *  next;
      };
      Node * world;

You will store the world as a linked list of countries.

Task 0:

Input the name and current population of each country into a linked list, where each node is of the type Country. The format of the provided population file is as follows:

-Columns 1-5: populations (in 1000s) of country in 1950, 1970, 1990, 2010, 2015, respectively. Since the population is in 1000s, the number is a real number.

-Column 6: Name of country.

Your code should ignore irrelevant fields (i.e., input them but don't store them).
You can implement this function by doing a push for each line of data read from the file.

Task 1:

Write a function, ````void printCountry (Node * world, string name)````, which finds the country with that name in world and prints its population. Use the following output format:
````<country> has <num> people.````

You can write a main driver program that calls printCountry to test your program (or use ddd (debugging)).

Task 2:

Write a function, ````update(Node * world, Country c)````. If a country with the same name as c is already in the list pointed to by world, this function updates its population (with c's population). Otherwise, c is pushed onto the list.

Suggestion: you may wish to make a precondition that the list does not contain 2 countries with the same name.

To test your function, you will need to write a main driver program to call update. This program should:
1.	Input a country name and population from the user
2.	Store that input into a struct. A statically allocated struct suffices.
3.	Call update
4.	Call printCountry to check that you did it correctly.

Task 3:

Write a function, merge, that takes three country names as arguments (ctry1, ctry2, newctry), and merges ctry1 and ctry2 into a country named newctry.

One way to do this is to rename one of the old countries (call it A), add the population of the other country (B) to A's population, and delete B. You will need to make your own prototype as the above is not complete.

Also write an appropriate driver program to test your program.

You can make preconditions that cover some special cases, but your code should properly handle the cases where a deleted node is at the beginning or end of the list, and also avoid memory leaks.


---


<a name="A-2"></a>
### A-2-ArrayData.cpp

You will do some basic manipulations of data. For this, you will need to do some File I/O and use structs (along with other data structures).

You will use the provided *A-2-Population.csv* file, which is a simplified version of data sourced from the UN (a few countries with non-ASCII characters in their name were left out just in case your program has problems with those).

The goal here is to keep track of population information about the countries of the world.

*TASKS*

Task 0:

The format of the provided population file is as follows:

-Columns 1-5: populations (in 1000s) of country in 1950, 1970, 1990, 2010, 2015, respectively. Since the population is in 1000s, the number is a real number.

-Column 6: Name of country.

Thus, a suitable data structure might be:

      struct Country {
        string name;
        double pop1950;
        double pop1970;
        double pop1990;
        double pop2010;
        double pop2015
      };
      struct World {
        int     numCountries;
        Country countries[MAXCOUNTRIES];
      } myWorld;

You will change this data structure later.

Write a function to initialize myWorld to data read from the supplied data file. There are a few complications to deal with:

1. Reading the populations is straightforward, and can be done using the standard file IO functions (i.e., ">>" using an input stream). However, since the names of some countries contain spaces, we need to use getline instead of >> for the name field. Fortunately, the country is the final field so we can use ">>" to read the populations and then a getline to finish the line.

2. You will need to input data until the end of file is reached. Recall that getline's return value is false if at end of file, so its easy to check for this.
To check that you did this correctly, you may wish to use ddd (debugging) to check the value of myWorld.

Task 1:

Write a program that prints the 3 largest countries (by 2015 population). Also modify the data structure to store the indices of these 3 countries so that the searching can be avoided in the future.

One algorithm to do this is a 3 pass algorithm; a better algorithm might be to keep track of the 'top 3' and adjust these as you iterate through the data structure. Print out the results in the following format:

    The largest country is XXXXX, which had XXXXXX people in 2015.
    The second largest country is XXXXX, which had XXXXXX people in 2015.
    The third largest country is XXXXX, which had XXXXXX people in 2015.

Make sure you print the actual populations (not in 1000s) - e.g., the US would have approximately 300000000 people.

You may assume the precondition that there are at least 3 countries.

Task 2:

Now you have to determine the country with fastest growth rate in the 1950-1970, 1970-1990, and 1990-2010, and 2010-2015 intervals. There are several ways to do this, but you will use the following approach:

1.	Compute and store the growth rates for each country in these 4 intervals. You will need to modify the data structure to also store the rates. For simplicity, we will compute the 20 year growth (or 5 years for the final interval) instead of an actual annual growth rate (so, a population of 100 in 1950 and 150 in 1970 would have a growth of 50% or 0.5 in that interval).

2.	Scan through the results to output the fastest growing country for each interval. The output format is:

 ````The fastest growing country between 1950 and 1970 is XXXXX````
... (for other intervals, in order)

Task 3:

Now you have to look at countries that are candidates to become one of the 3 biggest countries in the future. To do this, you want to pick countries that are currently at least 20% as large as the 3rd largest country, and have a larger growth rate than the 3rd largest country (obviously, this criteria uses a very long term definition of "future").

Print a list of all such countries, one per line, in order of occurrence in the file.