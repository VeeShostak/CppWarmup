# C++ Warmup Programs

This is a repository containing my solutions to short C++ programs designed to give a starting foundation in software development. We will be analyzing the problem at hand and designing a solution using the C++ programming language.

##### Programs:

[1) A-1-LinkedListData](#A-1)

[2) A-2-ArrayData](#A-2)

[3) A-3-ImageManipulation](#A-3)

[4) A-4-SentenceStrVec](#A-4)

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


---


<a name="A-3"></a>
### A-3-ImageManipulation.cpp

You will do basic manipulations of gray-scale images. The data structure for an image is a 2-D array, so you will be writing functions that manipulate 2-D arrays.

*TASKS*

For all tasks:

You are provided a sample gray-scale image to work on, *A-3-inImage.pgm*

There are many image formats (jpg, png, etc.), and we will use PGM (Portable GrayMap) since it is a simple grayscale format.

You may need to use the following linux programs while developing your programs.

1. Viewing a PGM image: eom and gimp are standard Linux program for viewing images in various formats (eog is another, but its not installed in Lab G).
2. Converting between image formats: The Linux utility convert will convert between all standard formats, where its 2 arguments are the input and output files, with format determined by filename suffix. You won't need this unless you want to play with other image formats.

We need a way to convert gray-scale images to arrays, and output arrays into image files. You are provided with two functions as follows:
1. writeImage: writes the argument image (a 2-D array) to outImage.pgm in PGM grayscale format.

2. readImage: reads a PGM grayscale format from inImage.pgm into an array, and updates the height/width arguments appropriately (since they are passed by reference).

Place them in your code and use these functions as is.

Task 0:

You are provided a sample gray-scale image to work on. Save the image supplied with the assignment to $PWD (your projects working directory). This file format has 8-bit images - i.e., each pixel is a gray scale value between 0 and 255 inclusive.

Write a small program that uses the given readimage/writeimage functions to input the PPM file into an array, copies the image to a 2nd array, and writes the 2nd array back. View the resulting image to make sure its the same as the original image.

Task 1:

One way to highlight objects in an image is to make all pixels below a threshold (T1) 0, and all pixels above a threshold (T2) 255. Write a function to highlight the image, using the following prototype:

````void highlight(int image[][MAXHEIGHT],int width, int height, int t1, int t2)````

Write a main program that inputs t1 and t2 from the user, highlights the image, and then writes the image.

This highlighting is called segmentation, though most segmentation algorithms are much more complicated.

Task 2:

Write a function that quantizes the image to q grayscale shades. For example, if q=8, replace each pixel between 0-31 by  0, 32-63 by 32, ..., and 224-255 by 224. Use the same order of arguments as in task 1 (using q instead of t1/t2), and name your function quantize. As before, write a main driver program, except inputting q this time.

Caution: You will need to handle the special case where q is not a factor of 256. You can do any reasonable set of intervals for this case (though all intervals won't have the same size, obviously).

For this task use the following prototype:
````void quantize(int image[][MAXHEIGHT],int width, int height, int q)````

Task 3:

One way to pixelate an image is to effectively make every nXn non-overlapping window contain the same value (the obvious value is the average of the window). For example, if n=2, the following image:

    10 20 30 40
    11 21 31 41
    12 22 32 42
    13 23 33 43

may be transformed to:

    16 16 36 36
    16 16 36 36
    18 18 37 37
    18 18 37 37

where the 16 was computed by averaging 10, 20, 11, and 21 (after rounding), and so on.

Repeat the earlier tasks, except with a function named pixelate which is defined as follows:

````void pixelate(int image[][MAXHEIGHT], int width, int height, int n)````

Task 4:

A sliding window operator replaces each pixel with some function of its 8 neighbors (and itself). Consider the following 3X3 window:

    a b c
    d e f
    g h i

Then, pixel e would be replaced by some function f(a,b,c,d,e,f,g,h,i). One way to detect edges is to use the function 5e-(b+d+f+h). Note that this is a sliding window operator unlike the non-overlapping windows in the previous task - that is, the window is always a window around the pixel whose value is being computed.

Write an edge detector function, named edgeDet. For pixels at the left/right/top/bottom edges of the image, consider their neighbors to be 'wrapped around' to the other end. For example row 0 would be considered to be the row after the last row of the image. Use the following prototype:

````void edgeDet(int image[][MAXHEIGHT], int width, int height)````

Task 5:

Write a main program that plays with the parameters to the above functions to produce an image that seems to look interesting (yes, this is very subjective). For example,  main might first quantize the image, then highlight it, and then do edge detection.


---


<a name="A-4"></a>
### A-4-SentenceStrVec.cpp


You will write a program that implements all the fundamental constructs you should know; strings, vectors, functions, and the basics. You are required to use vectors for any indeterminate-sized data other than strings.

*TASKS*

You will do various analysis tasks on a sentence input by keyboard. Your final program should be one cpp file with each task operating on the result of the previous task, suitably modular with functions to handle individual concerns.

Task 0:

After reading all the tasks, identify suitable preconditions on the input sentence for which your code will work. Write these preconditions as comments. An example precondition might be that the sentence does not start with spaces, but you will need more.

Don't forget that the preconditions (and postconditions) form a contract with your customer, and the program is considered wrong (and you don't get paid) if you dont handle a sentence that isn't explicitly barred by a precondition.
You may make any reasonable preconditions, but make sure you allow arbitrarily long sentences.

Task 1:

Check if the sentence reads the same forwards as backwards by word, and output a message indicating whether it does or not. For example, "I am what am I." qualifies, but "I am what I am." does not. For the purposes of this lab, words are delimited by one or more spaces (except at the beginning and end of the sentence), and there is exactly one period at the end of every sentence.

Hint: Since all tasks rely on the identification of words, you might first want to split the sentence into words (in a separate function). Think about the best type for a variable that stores a sequence of words - that will be the type of the functions return value.

Task 2:

A common writing error is to duplicate words (e.g., "I ate the the pizza."). Go through the sentence and remove any consecutive duplicated words.
Note that although duplicate words might sometimes be intended, we are not worried about that case for the purposes of this lab.

Task 3:

Another  writing error is to not capitalize the word "I". Handle this.

Task 4:

Replace every word "instructor" in the sentence, with "Mr. John Doe"

Task 5:

Looking at your preconditions, modify your code to relax as many of them as you can.