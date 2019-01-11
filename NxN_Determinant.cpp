// This program calculates the value of an N x N determinant, based on an input matrix of
// integers loaded from a text file (file name determined by the user and entered by the user
// at the beginning of the program), and displays the result to the user.
//
// The functions det_1x1, det_2x2, and det_nxn return the solutions to 1 x 1, 2 x 2, and N x N
// determinants, respectively.
//
// det_nxn uses RECURSION by breaking an N x N determinant into 3 (N-1) x (N-1) determinants, which
// are calculated using the det_nxn function, which themselves are broken down each into 3 (N-2) x (N-2)
// determinants, and so on, until the determinants have been broken down to 2 x 2 determinants, which
// are calculated using the det_2x2 function.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// function prototypes
vector<vector<double>> getFileInput(string filename);
double det_1x1(double x);
double det_2x2(vector<vector<double>> matrix);
double det_nxn(vector<vector<double>> matrix);

int main()
{

	vector<vector<double>> inputMatrix;
	string filename;

	// get the file name that contains the input
	cout << "\n\n  Enter the file name containing the N x N matrix (please include the .txt extension): ";
	cin >> filename;
	inputMatrix = getFileInput(filename);
	cout << "\n\n  ";

	// display the matrix of numbers to the user for confirmation purposes
	for (int i = 0; i < inputMatrix.size(); i++)
	{
		for (int j = 0; j < inputMatrix[i].size(); j++)
		{
			cout << inputMatrix[i][j] << " ";
		}
		cout << "\n  ";
	}

	// display the result to the user
	cout << "\n\n     RESULT: " << det_nxn(inputMatrix) << "\n\n";

	cin.ignore(); cin.ignore();

	return 0;
}


vector<vector<double>> getFileInput(string filename)
/* This function reads the file 'filename' (a *.txt file) and assigns the numbers to
   matrix. The numbers in the input file MUST in a comma-separated format.
   For example, the following 3x3 determinant:

			1  2  3
			4  5  6
			7  8  9

   must be represented in the input text file as follows:

1,2,3
4,5,6
7,8,9

  There also must be as many rows as there are columns. So, 3x3, 4x4, 5x5,...,NxN matrices
  are all acceptable. However, a 3x4 matrix would notbe.
*/
{
	vector<vector<double>> inputMatrix;
	ifstream myFile;
	string stringInput;
	myFile.open(filename);

	// for every row of text in the file myFile...
	while (getline(myFile, stringInput))
	{
		stringstream linestream(stringInput);
		string individualNumber;

		// increase the number of rows in inputMatrix by 1
		inputMatrix.resize(inputMatrix.size() + 1);

		while (getline(linestream, individualNumber, ','))
		{
			// increase the number of columns in inputMatrix by 1
			inputMatrix[inputMatrix.size() - 1].resize(inputMatrix[inputMatrix.size() - 1].size() + 1);

			// convert individualNumber from a string to a double, and input
			// the double value into the currentinputMatrix element
			stringstream cast(individualNumber);
			cast >> inputMatrix[inputMatrix.size() - 1][inputMatrix[inputMatrix.size() - 1].size() - 1];
		}
	}

	return inputMatrix;
}


double det_1x1(double x)
// the determinant of a single number is equal to the number itself
{
	return x;
}


double det_2x2(vector<vector<double>> matrix)
/*
	The determinant of a 2x2 matrix, with the following structure:

			a   b

			c   d

	equals (a x d) - (b x c)
*/
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
}


double det_nxn(vector<vector<double>> matrix)
// this function returns the determinant of any N x N matrix
{
	vector<vector<double>> submatrix;
	double result = 0;

	// there shouldn't be any 0-element matrix passed to this function,
	// but in case that happens, return 0 for the result
	if (matrix.size() == 0) { return 0; }

	// if the matrix 1x1, just return the number itself
	else if (matrix.size() == 1) { return matrix[0][0]; }

	// if the matrix is 2x2, return the value returned by det_2x2
	else if (matrix.size() == 2) { return det_2x2(matrix); }

	// otherwise, n > 2, and we will employ recursion to express
	// the value of the N x N determinant in terms of (N-1) x (N-1)
	// determinants, then express those determinants in terms of
	// (N-2) x (N-2) determinants, and so on, until the entire expression
	// is in terms of 2x2 determinants that can be calculated using det_2x2.
	// (This is called 'cofactor expansion' or 'expansion of minors' in
	// linear algebra texts.)
	else
	{
		// create an (n-1) x (n-1) matrix to hold the (n-1) x (n-1) determinants
		submatrix.resize(matrix.size() - 1);
		for (int i = 0; i < submatrix.size(); i++) { submatrix[i].resize(submatrix.size()); }

		// i goes through row 0 of the input matrix, from left to right
		for (int i = 0; i < matrix.size(); i++)
		{
			// j goes through rows 1 through n (downward of the input matrix)
			for (int j = 1; j < matrix.size(); j++)
			{
				// k goes through columns 0 through n, within row j of the input matrix
				for (int k = 0; k < matrix.size(); k++)
				{
					if (k < i)
					{
						submatrix[j - 1][k] = matrix[j][k];
					}
					else if (k > i)
					{
						submatrix[j - 1][k - 1] = matrix[j][k];
					}
					// (if j = i, then do nothing -- skip that column)
				}
			}

			result = result + (matrix[0][i] * det_nxn(submatrix) * pow(-1.0,i));
		}
		
		return result;
	}
}