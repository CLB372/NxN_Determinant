# NxN_Determinant
This program calculates the value of an N x N determinant, based on an input matrix of
integers loaded from a text file (file name determined by the user and entered by the user
at the beginning of the program), and displays the result to the user.

The functions det_1x1, det_2x2, and det_nxn return the solutions to 1 x 1, 2 x 2, and N x N
determinants, respectively.

det_nxn uses RECURSION by breaking an N x N determinant into 3 (N-1) x (N-1) determinants, which
are calculated using the det_nxn function, which themselves are broken down each into 3 (N-2) x (N-2)
determinants, and so on, until the determinants have been broken down to 2 x 2 determinants, which
are calculated using the det_2x2 function.

The input file should be in the same directory as the executable file, and it must ONLY contain 
a matrix of integers where the number of rows = the number of columns.

Within the same row, the numbers should be separated by commas. So, a 3x3 input matrix should look like:

1,2,3
4,5,6
7,8,9

The file NxN_Determinant.exe is the executable file for this program.

The file NxN_Determinant.cpp contains the relevant C++ code.
