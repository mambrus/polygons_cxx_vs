#include "Vector.h"


// Helper function until better constructors / static casting methods exists
template < class T >
Vector < Vector < T > >MatrixInitialize(const Vector < Vector < T > >&me,
	T baseval)
{
	Vector < Vector < T > >R = me;
	size_t dim1 = R.Length();
	size_t dim2 = R[0].Length();
	T *I = new T[dim2]; for (int i = 0; i < dim2; i++) { I[i] = 0; }

	int i, j;

	for (j = 0; j < dim1; j++) {
		for (i = 0; i < dim2; i++) {
			I[i] = baseval + (100 * j + i);
		}
		R[j] = I;
	}

	free(I);
	return R;
}