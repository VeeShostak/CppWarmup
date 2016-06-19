# C++ Warmup Programs

This is a repository containing my solutions to short C++ programs designed to give a starting foundation in software development. We will be analyzing the problem at hand and designing a solution using the C++ programming language.

##### Programs:

[1) A-1-LinkedListData](#A-1)


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
