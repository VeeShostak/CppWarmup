
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h> // for toupper tolower
using namespace std;

// function prototypes
void splitIntoWords(string sentence, vector<string> &words);
void sameBackwards(vector<string> &words, vector<string> &reverseWords);
void removeConsec(vector<string> &words);
void captheI(vector<string> &words);
void replaceInstr(vector<string> &words);

int main()
{

	// ===============================
	// task 1 (& task 5)
	// ===============================

	string sentence;  // stores sentence from user

	do {
		cout << "Enter a sentence:\n";
		getline(cin, sentence);
	} while (sentence.length() < 1 || sentence[0] == '.'); // error check for null string and first input cant be a period

	// Precondition: sentence.lenght() >= 1 (first input cant be a period). sentence has no punctuation.
	// everyword is separated with a single space. sentence does not start with spaces.
	// Task 5: (Removed precondition where sentence has to end with a period, now this is optional)


	vector<string> words;  // holds words from the sentence
	// split the sentence into words and store in wordsVector
	splitIntoWords(sentence, words);

	vector<string> reverseWords(words.size()); // holds the words reversed. initialized to the size of words vector
	// store the words reversed in reverseWords vector
	for (int i = words.size() - 1, count = 0; i >= 0; i--, count++)
	{
		reverseWords[count] = words[i];
	}

	// Check if the sentence reads the same farwards as backwards
	sameBackwards(words, reverseWords);


	// ===============================
	// task 2
	// ===============================

	// remove consecutive duplicate words
	removeConsec(words);


	// ===============================
	// task 3
	// ===============================

	// capitalize the word I
	captheI(words);


	// ===============================
	// task 4 (& task 5)
	// ===============================

	// replace every word "instructor" in the sentence with "Mr. John Doe"
	// task 5: removed precodition where first letter of "instructor" has to be lowercase, now it can also be uppercase
	replaceInstr(words);


	// ===============================

	// show the new sentence
	string modSent = "";
	for (int i = 0; i < words.size(); i++)
	{
		modSent += words[i];
		modSent += " ";
	}
	cout << "\nThe new sentence:\n\n" << modSent << endl;

	return 0;
}

// ====================================================
// Functon Definitons
// ====================================================


// splits the sentence into words
// Precondition: sentence.lenght() >= 1 (first input cant be a period). sentence has no punctuation.
// every word is separated with a single space. sentence does not start with spaces.

// Postcondtion: the vector of strings contains all the words from the sentence (w/o spaces or punctuation)
// in order from left to right
void splitIntoWords(string sentence, vector<string> &words)
{
	string oneWord = ""; // to store each word and then push it to the vector
	for (int i = 0; i < sentence.length(); i++)
	{
		// copy only the chars (letters a-z) of the word,
		if (sentence[i] != ' ' && sentence[i] != '.')
		{
			oneWord += sentence[i];
		}

		// if space OR on last word OR on period(end of sent), then split into a word and push back to vector
		if (sentence[i] == ' ' || sentence[i] == '.' )
		{
			words.push_back(oneWord);

			// reset the word
			oneWord = "";
		}
	}
}

// Check if the sentence reads the same farwards as backwards
// Precondition: vector words has only words from the sentence(w/o spaces or punctuation) in order
// from left to right. vector reverse words has the same words but from right to left(in opposite order)

// Postcondition: outputs if the sentence reads the same farwards as backwards
void sameBackwards(vector<string> &words, vector<string> &reverseWords)
{
	bool check = true; // true if sentence is read same backwards as farwards

	for (int i = 0; i < reverseWords.size() && check; i++)
	{
		if (reverseWords[i] != words[i])
		{
			check = false;
			break; // break if not equal, no more comparisons needed.
		}

	}
	if (check)
	{
		cout << "\nYES!\nThe sentence reads the same farwards as backwards!\n";
	}
	else if (!check)
	{
		cout << "\nNO!\nThe Sentence does NOT read the same farwards as backwards!\n";
	}
}

// remove consecutive duplicate words from the sentence
// Precondition: vector words has only words from the sentence(w/o spaces or punctuation) in order
// from left to right

// Postcondition: deletes the repeated words in words vector and updates the size of the vector accordingly
void removeConsec(vector<string> &words)
{
	// remove consecutive duplicate words from the sentence

	int pos; // stores index of the word to remove
	int updateSize = words.size() - 1; // holds the updated size of vector after an element is removed

	// use the split up words  and see if the i one matches the i + 1 one.
	for (int i = 0; i < updateSize; i++)
	{

		// if i word matches i+1 word then remove the repeated i+1 word and update the vector
		if (words[i] == words[i + 1])
		{
			pos = (i + 1); // store the index of the wrod to remove

			// move each element to the right of pos (i>pos), 1 to the left (down 1 index)
			// the element to remove gets overwritten in first iteration
			for (int z = pos; z < words.size() - 1; z++)
			{
				words[z] = words[z+1];
			}
			// the last element will be equal to the previose element (since the prev element got
			// assigned the last element), so we delete this last element
			words.pop_back();  // can also use words.resize(words.size() - 1);

			// start comparing from the same word, in case if more than two consecutive words
			i--;

			updateSize = words.size() - 1; // update the new size
		}
	}

}

// capitalize the word I
// Precondition: vector words has only words from the sentence(w/o spaces or punctuation) in order
// from left to right

// Postcondition: every lowercase "i" will be capitalized in the words vector
void captheI(vector<string> &words)
{
	for (int i = 0; i < words.size(); i++)
	{
		// if found lowercase i, make it uppercase
		if (words[i] == "i")
		{
			words[i] = toupper(words[i].at(0)); // at.(0) == str[0]  index access
		}
	}
}

// replace every word "instructor" in the sentence with "Mr. John Doe"
// Precondition: vector words has only words from the sentence(w/o spaces or punctuation) in order
// from left to right.
// (task 5 removed a precondition. "instructor" word can now start with a lowercase or uppercase letter (i I) )

// Postcondition: in the case of the word "instructor" being found in the words vector - it
// will be replaced with 3 words "Mr." "John" "Doe , and the size of the vector will
// be updated accordingly (size increased by 2).
void replaceInstr(vector<string> &words)
{
	// replace every word "instructor" in the sentence with my professor's name "Mr. Ali ElSayed"

	// if words[index] ==  the word instructor
	// replace it and add 3 more strings: one is "Mr." another is "John" and third is "Doe"
	string findWord = "instructor", varFindWord = "Instructor";
	string addWord1 = "Mr.",
		addWord2 = "John",
		addWord3 = "Doe";

	int pos; // holds index of where instructor was found

	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == findWord || words[i] == varFindWord)
		{
			// set pos to the index of where instructor was found
			pos = i;

			// overwrite instructor with addWord1
			words[pos] = addWord1;

			// increase the vector size by 2
			words.resize(words.size() + 2);

			// shift eveything after pos (index>pos), to the right by 2 (up 2 indexes). we need to
			// make space for our two new words at pos+1 and pos+2.
			for (int count = 0; count < (words.size() - 3 - pos); count++)
			{
				words[words.size() - 1 - count] = words[words.size() - 3 - count];
			}

			// assign our new 2 words to the 2 freed spaces after pos
			words[pos + 1] = addWord2;
			words[pos + 2] = addWord3;

		}
	}
}
