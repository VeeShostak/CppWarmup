

#include <iostream>

using namespace std;

// function prototypes
int nChooseKAlgo1(int n, int k);
int nChooseKAlgo2(int n, int k);
int nChooseKAlgo3(int n, int k);
double nChooseKAlgo4(int n, int k);

int main()
{


	int n,
		k;

	double	result; // for task 4 result must be a double otherwise it will output incorrect results (try n=8, k=4)

	cout << "\t C(n,k) calculations\n\n";

	// ask user for n and k. -error check for n and k
	do {
		cout << "enter value for n: ";
		cin >> n;
	} while (n < 0); // accept only values of n where n >= 0

	do {
		cout << "enter value for k: ";
		cin >> k;
	} while (k < 0 || k > n); // accept only values of k where 0 <= k <= n

	// ==================================
	// TASK 1

  	// send n,k to algo 1
	result = nChooseKAlgo1(n, k);

	cout << "Task 1: ";
	cout << result << endl;

	/*
	(on my machine:)
	1) The largest value of n for which C(n,n-1) returns a correct result
	is 12. The results are incorrect because the computation of the
	numerator (12!) , and denomenator, results in a very large number that is beyond
	the size that the int can handle. This results in an overflow.

	The largest value for which it does not result in an overflow exception
	(when an exception condition is not triggered on overflow) is 34 (C(34,33))
	*/


	// ==================================
	// TASK 2

	// send n,k to algo 2
	result = nChooseKAlgo2(n, k);

	cout << "\nTask 2: ";
	cout << result << endl;

	/*
	Efficiency-wise, it is more efficient and does slightly less multiplies than the previous calculation.
	*/

	// ==================================
	// TASK 3

	// send n,k to algo 3
	result = nChooseKAlgo3(n, k);

	cout << "\nTask 3: ";
	cout << result << endl;



	// ==================================
	// TASK 4
	result = nChooseKAlgo4(n, k);

	cout << "\nTask 4: ";
	cout << result << endl;

	/*
	This calculation takes in much larger values for C(n,n-1)
	*/


	return 0;
} // <- end of main()


  // ===============================================
  // function definitions
  // ===============================================

  // TASK 1 algorithm
int nChooseKAlgo1(int n, int k)
{
	int answer;
	int tempN = n; // holds the value of n since the actual parameter value of n will be updated (n!)
	int tempK = k; // holds the value of k since the actual parameter value of k will be updated (k!)

	int differenceFact = (n - k); // will store  (n-k)! (the factorial of the difference)
	int diffFactTemp = (n - k); // stores the initial n-k value, since thedifferenceFact variable will be updated

								// calculate n!
	for (int count = 1; count < tempN; count++)
	{
		n *= (tempN - count);
	}

	// calculate k!
	for (int count = 1; count < tempK; count++)
	{
		k *= (tempK - count);
	}

	// calculate (n-k)!
	for (int count = 1; count < diffFactTemp; count++)
	{
		differenceFact *= (diffFactTemp - count);
	}

	// calculate arithmetic of  n! /  k! * (n - k)!
	answer = (n / (k * differenceFact));

	return answer;
}


// TASK 2 algorithm
int nChooseKAlgo2(int n, int k)
{
	int answer;
	int tempN = n; // holds the value of n since the actual parameter value of n will be updated (n!)
	int tempK = k; // holds the value of k since the actual parameter value of k will be updated (k!)

	int differenceFact = (n - k + 1); // will store  (n-k+1)!
	int diffFactTemp = (n - k + 1); // stores the initial n-k+1 value, since thedifferenceFact variable will be updated

	// calculate n(n-1)(n-2)...(n-k+1)
	for (int count = 1; count <= (tempN - diffFactTemp); count++)
	{
		n *= (tempN - count);
	}


	// calculate k!
	for (int count = 1; count < tempK; count++)
	{
		k *= (tempK - count);
	}

	// claculate arithmetic of n(n-1)(n-2)...(n-k+1)/k!
	answer = (n / k);


	return answer;
}

// TASK 3 algorithm
int nChooseKAlgo3(int n, int k)
{
	int answer;
	int tempN = n; // holds the value of n since the actual parameter value of n will be updated (n!)
	int tempK = k; // holds the value of k since the actual parameter value of k will be updated (k!)

	int differenceFact = (n - k + 1); // will store  (n-k+1)!
	int diffFactTemp = (n - k + 1); // stores the initial n-k+1 value, since thedifferenceFact variable will be updated

									// apply property C(n,k) = C(n,n-k)
									// calculate the one that does less calculations (Which is the one that has a lower k value)
	if ((n - k) < k)
	{
		k = (n - k);
	}


	// calculate n(n-1)(n-2)...(n-k+1)
	for (int count = 1; count <= (tempN - diffFactTemp); count++)
	{
		n *= (tempN - count);
	}



	// calculate k!
	for (int count = 1; count < tempK; count++)
	{
		k *= (tempK - count);
	}

	// claculate arithmetic of n(n-1)(n-2)...(n-k+1)/k!
	answer = (n / k);


	return answer;
}

// TASK 4 algorithm
double nChooseKAlgo4(int n, int k)
{
	double tempAnsw = 1;
	int answer;
	double nkDiff = (n - k);

	for (int count = 1; count <= k; count++)
	{
		// answer acuumulates product of 1+(n-k)/1 * 1+(n-k)/1 ... * 1+(n-k)/k
		tempAnsw *= (1 + (nkDiff / count));
	}


	return tempAnsw;
}
