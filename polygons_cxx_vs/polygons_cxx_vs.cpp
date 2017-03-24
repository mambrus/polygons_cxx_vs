#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#include <simple/SimpleFunctions.h>
#include <advanced/AdvancedFunctions.h>
#include <Vector.h>

#include<iostream>
#include<map>

#define PVECTOR_STATS { \
	cout << "Vector < int >:"; \
	cout << Vector < int >::stats(cout) << endl; \
	cout << endl; \
	cout << "Vector < float >:"; \
	cout << Vector < float >::stats(cout) << endl; \
	cout << endl; \
	cout << "Vector < double >:"; \
	cout << Vector < double >::stats(cout) << endl; \
	cout << endl; \
	cout << "Vector < Vector <int > >:"; \
	cout << Vector < Vector < int > >::stats(cout) << endl; \
	cout << endl; \
	cout << "Vector < Vector <float > >:"; \
	cout << Vector < Vector < float > >::stats(cout) << endl; \
	cout << endl; \
	cout << "Vector < Vector <double > >:"; \
	cout << Vector < Vector < double > >::stats(cout) << endl; \
	cout << endl; \
}

int glob_gdb_1 = 0;

// Helper function until better constructors / static casting methods exists
template < class T >
    Vector < Vector < T > >MatrixInitialize(const Vector < Vector < T > >&me,
					    T baseval)
{
	Vector < Vector < T > >R = me;
	int dim1 = R.Length();
	int dim2 = R[0].Length();
	T I[dim1] = { 0 };

	int i, j;

	for (j = 0; j < dim1; j++) {
		for (i = 0; i < dim2; i++) {
			I[i] = baseval + (100 * j + i);
		}
		R[j] = I;
	}

	return R;
}

int main(int argc, char *argv[])
{
	struct mallinfo before, after;
	int mused;

	before = mallinfo();

	after = mallinfo();
	mused =
	    (after.uordblks - before.uordblks) + (after.hblkhd - before.hblkhd);
	printf("Allocated memory: %d \n", mused);

	{
		// Define a 2-dimensional integer vector (matrix) and test index operators
		// on it.
		cout << endl;
		{
			int i, j;
			int dim1 = 3, dim2 = 4;

			// Create the matrix
			printf("Instantiating matrix\n");
			Vector < Vector < int > >matrix(dim1,
						       Vector < int >(dim2));
			printf("Initializing matrix\n");
			matrix = MatrixInitialize < int >(matrix, 11);

			// Print matrix out in various forms and using various methods
			for (i = 0; i < dim1; i++) {
				for (j = 0; j < dim2; j++) {
					cout << "[" << i << "." << j << "] : ";
					cout << matrix[i][j] << endl;
				}
				cout << "[" << i << "]: " << matrix[i] << endl;
				cout << endl;
			}
			cout << matrix << endl;
			cout << endl;
		}

		// Define a 2-dimensional double vector (matrix) and test index operators
		// on it.
		cout << endl;
		{
			int i, j;
			int dim1 = 3, dim2 = 4;

			// Create the matrix
			printf("Instantiating matrix\n");
			Vector < Vector < double > >matrix(dim1,
							  Vector < double >(dim2));
			printf("Initializing matrix\n");
			matrix = MatrixInitialize < double >(matrix, 1.1);

			// Print matrix out in various forms and using various methods
			for (i = 0; i < dim1; i++) {
				for (j = 0; j < dim2; j++) {
					cout << "[" << i << "." << j << "] : ";
					cout << matrix[i][j] << endl;
				}
				cout << "[" << i << "]: " << matrix[i] << endl;
				cout << endl;
			}
			cout << matrix << endl;
			cout << endl;
		}

#ifdef NEVER
		cout << endl;
		{
			int a[] = {
				11, 12, 13, 14
			};
			// ===========================================
			cout << "Constructor and assignments <int>:" << endl;
			// ===========================================
			Vector < int >A(NELEM(a), a);
			cout << "1:st assignment constructor (array):" << endl;
			cout << A << endl << endl;
			Vector < int >B;
			B = A;

			Vector < int >C(4, 21, 22, 23, 24);
			cout << "2:nd assignment constructor (va_arg):" << endl;
			cout << C << endl << endl;
			Vector < int >D = C;

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;

			// ===========================================
			cout << "Index operator <int>:" << endl;
			// ===========================================
			for (int i = 0; i < 4; i++) {
				A[i] = 30 + i;
			}

			// Use debugger in this loop as CTOR/DTOR (tmp) operations may occur.
			for (int i = 0; i < 4; i++) {
				B[i] = A[3 - i];
				C[i] = B[3 - i];
				D[i] = C[i] + 1;
			}

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;

			// ===========================================
			cout << "Test exception<int>s:" << endl;
			// ===========================================
			//
			// Index operator: Exceed boundaries deliberately
			for (int i = 0; i < (4 + 1); i++) {
				try {
					D[i] = B[i];
				}
				catch(const std::invalid_argument & e) {
					cout <<
					    "Dang! Exception \"invalid_argument\" at index="
					    << i <<
					    " and caught. Further info: " <<
					    e.what() << endl;
				}
			}

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;
		}

		cout << endl;
		{
			double a[] = {
				11.0, 12.0, 13.0, 14.0
			};
			// ===========================================
			cout << "Constructor and assignments <double>:" << endl;
			// ===========================================
			Vector < double >A(NELEM(a), a);
			Vector < double >B;
			B = A;

			Vector < double >C(4, 21.0, 22.0, 23.0, 24.0);
			Vector < double >D = C;

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;

			// ===========================================
			cout << "Index operator <double>:" << endl;
			// ===========================================
			for (int i = 0; i < 4; i++) {
				A[i] = 30.3 + i;
			}

			// Use debugger in this loop as CTOR/DTOR (tmp) operations may occur.
			for (int i = 0; i < 4; i++) {
				B[i] = A[3 - i];
				C[i] = B[3 - i];
				D[i] = C[i] + 1;
			}

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;

			// ===========================================
			cout << "Test exceptions <double>:" << endl;
			// ===========================================
			//
			// Index operator: Exceed boundaries deliberately
			for (int i = 0; i < (4 + 1); i++) {
				try {
					D[i] = B[i];
				}
				catch(const std::invalid_argument & e) {
					cout <<
					    "Dang! Exception \"invalid_argument\" at index="
					    << i <<
					    " and caught. Further info: " <<
					    e.what() << endl;
				}
			}

			cout << "A:" << A << endl
			    << "B:" << B << endl << "C:" << C << endl << "D:" <<
			    D << endl;
		}
#endif				//NEVER

		// ===========================================
		cout << "Linear algebra operators (+/-):" << endl;
		// ===========================================
		{
			glob_gdb_1 = 1;
			Vector < int >A(4);
			int a[] = { 11, 12, 13, 14 };
			A = a;
			Vector < int >B(4);
			int b[] = { 21, 22, 23, 24 };
			B = b;
			cout << "A:" << A << endl;
			cout << "B:" << B << endl;
			Vector < int >C = A + B;
			Vector < int >D = B - (A + B);
			cout << "C:" << C << endl;
			cout << "D:" << D << endl;
			cout << "Source variables are now NOT tainted" << endl;
			cout << "A:" << A << endl;
			cout << "B:" << B << endl;
		}
		// Define a 2-dimensional ditto
		cout << endl;
		{
			int i, j;
			int dim1 = 3, dim2 = 4;

			// Create the matrix
			printf("Instantiating matrixs\n");
			Vector < Vector < int > >mx1(dim1,
						       Vector < int >(dim2));
			Vector < Vector < int > >mx2(dim1,
						       Vector < int >(dim2));
			printf("Initializing matrixs\n");
			mx1 = MatrixInitialize < int >(mx1, 11);
			mx2 = MatrixInitialize < int >(mx2, 57);
			Vector < Vector < int > >mx3 = mx1 + mx2;
			Vector < Vector < int > >mx4 = mx2 - mx1;

			// Print matrix out in various forms and using various methods
			for (i = 0; i < dim1; i++) {
				for (j = 0; j < dim2; j++) {
					cout << "[" << i << "." << j << "] : ";
					cout << mx3[i][j] << endl;
				}
				cout << "[" << i << "]: " << mx3[i] << endl;
				cout << endl;
			}
			cout << endl;
			// Print matrix out in various forms and using various methods
			for (i = 0; i < dim1; i++) {
				for (j = 0; j < dim2; j++) {
					cout << "[" << i << "." << j << "] : ";
					cout << mx4[i][j] << endl;
				}
				cout << "[" << i << "]: " << mx4[i] << endl;
				cout << endl;
			}
			cout << endl;
			cout << "mx1: " << mx1 << endl;
			cout << "mx2: " << mx2 << endl;
			cout << "mx3: " << mx3 << endl;
			cout << "mx4: " << mx4 << endl;
			cout << endl;
		}

#ifdef NO_LINALGEBRA
		// ===========================================
		cout << "Linear algebra operators (mul/div):" << endl;
		// ===========================================
		{
			Vector < int >A(4, 11, 12, 13, 14);
			Vector < int >B(4, 33, 44, 55, 66);
			cout << "A:" << A << endl;
			cout << "B:" << B << endl;
			Vector < int >C = A * 2;
			Vector < int >D = B / 3;
			cout << "C:" << C << endl;
			cout << "D:" << D << endl;
			cout << "Source variables are now NOT tainted" << endl;
			cout << "A:" << A << endl;
			cout << "B:" << B << endl;
		}

#endif				//NO_LINALGEBRA

		printf("=================================================\n");
		printf("Printout of static Vector-stats before last scope\n");
		printf("=================================================\n");
		PVECTOR_STATS;

	}
	printf("=================================================\n");
	printf("Printout of static Vector-stats after last scope\n");
	printf("=================================================\n");
	PVECTOR_STATS;

	after = mallinfo();
	mused =
	    (after.uordblks - before.uordblks) + (after.hblkhd - before.hblkhd);
	printf("Allocated memory: %d \n", mused);

	return 0;
}
