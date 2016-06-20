
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>

#include <stdlib.h> // rand
#include <time.h> // time
using namespace std;


const int MAXWIDTH = 512;
const int MAXHEIGHT = 512;

// overflowing the stack, array is too large, so use static storage class (globally defined vars use static)
// NOTE: The stack is being overflown because the Visual Studio IDE reserves 1gb for it,
// you can fix this in configuration properties of the IDE and reserve more.

int image[MAXWIDTH][MAXHEIGHT]; // first image array
int imageSec[MAXWIDTH][MAXHEIGHT]; // second image array

// function prototypes
void readImage(int image[][MAXHEIGHT], int &width, int &height);
void writeImage(int image[][MAXHEIGHT], int width, int height);
void highlight(int image[][MAXHEIGHT], int width, int height, int t1, int t2);
void quantize(int image[][MAXHEIGHT], int width, int height, int q);
void pixelate(int image[][MAXHEIGHT], int width, int height, int n);
void niceImage(int image[][MAXHEIGHT], int question, int width, int height);
void edgeDet(int image[][MAXHEIGHT], int width, int height);

int main()
{
	// dimensions of image
	int width = MAXWIDTH;
	int height = MAXHEIGHT;


	// =======================================
	// Task 0
	// =======================================

	// read a PGM image format from inImage.pgm,and place it into first array
	readImage(image, width, height);

	// copy the image in first array to a second aray
	for (int w = 0; w < MAXWIDTH; w++)
	{
		for (int h = 0; h < MAXHEIGHT; h++)
		{
			imageSec[w][h] = image[w][h];
		}
	}

	// write the image from the second array, to outputImage.pgm.
	writeImage(imageSec, width, height);


	// =======================================
	// Task 1
	// =======================================

	// ask user for T1 , T2 thresholds
	int t1, t2;
	cout << "\tTask 1\nEnter t1 threshold: ";
	cin >> t1;
	cout << "Enter t2 theshold: ";
	cin >> t2;

	// highlight the image in the array
	highlight(image, width, height, t1, t2);

	// write the image from array to outputImage.pgm
	writeImage(image, width, height);


	// =======================================
	// Task 2
	// =======================================

	// ask user for q
	int q; // how many shades of colors we will have when quantizing
	cout << "\n\n\tTask 2\nEnter value for q: ";
	cin >> q;

	// quantize the image in array
	quantize(image, width, height, q);

	// write the image from the array to outputImage.pgm
	writeImage(image, width, height);


	// =======================================
	// Task 3
	// =======================================

	// ask user for n
	int n;
	cout << "\n\n\tTask 3\nEnter a value for n: ";
	cin >> n;

	// pixelate the image in array
	pixelate(image, width, height, n);

	// write the image from the array to outputImage.pgm
	writeImage(image, width, height);


	// =======================================
	// Task 4
	// =======================================
	int cont; // to pause before continuing processing image with new function
	cout << "\n\n\tTask 4\nEnter any integer value to continue: ";
	cin >> cont;

	edgeDet(image, width, height);

	// write the image from array to outputImage.pgm
	writeImage(image, width, height);


	// =======================================
	// Task 5
	// =======================================

	// produce interesting image from previous tasks.
	int question = 1;
	cout << "\n\n\tTask 5\nProduce interesting image? (0 = yes)\n";
	cin >> question;

	niceImage(image, question, width, height);
	// write the image from array to outputImage.pgm
	writeImage(image, width, height);


	return 0;
} // <-end main

// ====================================================
// Functon Definitons
// ====================================================

// reads a PGM file.
// Notice that: width and height are passed by reference!
void readImage(int image[][MAXHEIGHT], int &width, int &height) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	// read the header P2
	instr >> c;  assert(c == 'P');
	instr >> c;  assert(c == '2');

	// skip the comments (if any)
	while ((instr >> ws).peek() == '#') { instr.ignore(4096, '\n'); }

	instr >> width;
	instr >> height;

	assert(width <= MAXWIDTH);
	assert(height <= MAXHEIGHT);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[col][row];
	instr.close();
	return;
}

// Writes a PGM file
void writeImage(int image[][MAXHEIGHT], int width, int height) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[col][row] < 256);
			assert(image[col][row] >= 0);
			ostr << image[col][row] << ' ';
			// lines should be no longer than 70 characters
			if ((col + 1) % 16 == 0) ostr << endl;
		}
		ostr << endl;
	}
	ostr.close();
	return;
}

// highlight for task 1
void highlight(int image[][MAXHEIGHT], int width, int height, int t1, int t2)
{
	// make all pixels below t1: 0   and make all pixels above t2: 255
	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			if (image[w][h] < t1)
			{
				image[w][h] = 0;
			}
			else if (image[w][h] > t2)
			{
				image[w][h] = 255;
			}
		}
	}

	return;
}

// quantize for task 2
void quantize(int image[][MAXHEIGHT], int width, int height, int q)
{
	int totalShades = 256; // original image has 0 - 255 gray scale values

	// START Algo- split into ranges

	vector<int> rangesMax(q);
	vector<int> rangesMin(q);
	int section = 256 / q;

	rangesMax[0] = section - 1;
	rangesMin[0] = 0;
	for (int i = 1; i < q; i++)
	{

		// if q was odd, and on last range, then last range will be uneven
		if ((q % 2 != 0) && (i = q - 1))
		{
			rangesMax[i] = rangesMax[i - 1] + (totalShades - 1 - rangesMax[i - 1]); //prev max + 255-prevmax
			rangesMin[i] = rangesMin[i - 1] + section; // pre min + section
		}
		else {
			rangesMax[i] = rangesMax[i - 1] + section; // prev max + section
			rangesMin[i] = rangesMin[i - 1] + section; // pre min + section
		}
	}
	// END Algo- split into ranges

	// overwrite each pixel betwenn range min[i] and max[i] with min[i]
	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			// check each pixel for q number of ranges
			for (int i = 0; i < q; i++)
			{
				if (image[w][h] <= rangesMax[i] && image[w][h] >= rangesMin[i])
				{
					image[w][h] = rangesMin[i];
				}
			}
		}
	}
	return;
}

// pixelate for task 3
void pixelate(int image[][MAXHEIGHT], int width, int height, int n)
{
	//n on the x axis, n on the y axis
	// compute their average color, and set them all to be that average

	int updateW = 0;
	int updateH = 0;
	int nWidth = n;
	int nHeight = n;
	// bool flag, while not done, keep going
	bool done = false;

	while (!done)
	{
		int blockVal = 0; // will hold average value of block
		// get total color from block
		for (int w = updateW; w < nWidth; w++)
		{
			for (int h = updateH; h < nHeight; h++)
			{
				blockVal += image[w][h];
			}
		}

		// get average (rounded)
		blockVal /= (n*n);
		blockVal = round(blockVal);

		// update that block with the average value
		for (int w = updateW; w < nWidth; w++)
		{
			for (int h = updateH; h < nHeight; h++)
			{
				image[w][h] = blockVal;
			}
		}

		// update the sizes accordingly for next iteration

		// not at horiz or verti edge, so continue to go through horizantally
		if (updateW + n < 256 && updateH + n < 256)
		{
			updateH += n;
			nHeight += n;
		}

		// at horiz edge, start vertically
		else if (updateW + n < 256 && updateH + n >= 256)
		{
			// reset horiz
			updateH = 0;
			nHeight = n;

			updateW += n;
			nWidth += n;
		}
		// at verti edge only, continue horizantally
		else if (updateW + n >= 256 && updateH + n < 256)
		{
			updateH += n;
			nHeight += n;
		}

		// falls to last conditional, both at edge, pixelation complete
		else if (updateW + n + n >= 256 && updateH + n + n >= 256)
		{
			done = true;
		}

	}

	return;
}

// edge detector function
void edgeDet(int image[][MAXHEIGHT], int width, int height)
{

	int ePixel; // holds the e pixel

	// vars repsonsible for updating for next ith iteration
	int updWidth = 1;
	int updHeight = 1;

	int e, b, d, f, h; // vars for function

	for (int w = 1; w < width - 2; w++) // exclude right edge
	{

		for (int col = 1; col < height - 2; col++)
		{

			e = image[w][col];
			b = image[w][col - 1];
			d = image[w - 1][col];
			f = image[w + 1][col];
			h = image[w][col + 1];

			ePixel = 5 * e - (b + d + f + h); // function

			// error check values 0-255 only: if below 0 set to 0, if above 255 set to 255
			if (ePixel > 255)
			{
				ePixel = 255;
			}
			else if (ePixel < 0)
			{
				ePixel = 0;
			}

			image[w][col] = ePixel;


		}
	}
}


// interesting image
void niceImage(int image[][MAXHEIGHT], int question, int width, int height)
{
	if (question == 0)
	{
		int value, value2;
		srand(time(0)); // random seed initialization

		// get random value in range 1- 100
		value = rand() % 100 + 1;

		// pixelate first
		int task5Pix = 8;
		pixelate(image, width, height, task5Pix);

		// get second random value 1 - 200
		value2 = rand() % 200 + 1;

		highlight(image, width, height, value, value2);

		// quantize
		int quantT5 = 16;
		quantize(image, width, height, quantT5);

		// edges function
		edgeDet(image, width, height);

	}
}
