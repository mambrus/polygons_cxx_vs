#include "Vector.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Add operator
template < class T >
const Vector < T > operator +(const Vector < T > lhs,
	const Vector < T > &rhs)
{
	if (lhs.m_n != rhs.m_n) {
		std::ostringstream s;
		s << "Vectors must have the same dimension to be added. [" <<
			(lhs.m_n - 1) << "] != [" << (rhs.m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}

	for (size_t i = 0; i < lhs.m_n; i++) {
		*(lhs.m_v[i]) = *(lhs.m_v[i]) + *(rhs.m_v[i]);
	}
	return lhs;
}

// Subtract operator
template < class T >
const Vector < T > operator -(const Vector < T > lhs,
	const Vector < T > &rhs)
{
	if (lhs.m_n != rhs.m_n) {
		std::ostringstream s;
		s << "Vectors must have the same dimension to be subtracted. ["
			<< (lhs.m_n - 1) << "] != [" << (rhs.m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}

	for (size_t i = 0; i < lhs.m_n; i++) {
		*(lhs.m_v[i]) = *(lhs.m_v[i]) - *(rhs.m_v[i]);
	}
	return lhs;
}

#ifdef NEVER
// Multiply operator
const Vector operator *(const Vector lhs, const T & m)
{
	for (size_t i = 0; i < lhs.m_n; i++) {
		*(lhs.m_v[i]) *= m;
	}
	return lhs;
}

// Division operator
const Vector operator /(const Vector lhs, const T & d)
{
	if (lhs.is_zero(d)) {
		std::ostringstream s;
		s << "Vector division would be by zero! (avoided)";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}

	for (size_t i = 0; i < lhs.m_n; i++) {
		*(lhs.m_v[i]) /= d;
	}
	return lhs;
}
#endif				//NEVER

// Helper functions
//==============================================================================
// Helper function until better constructors / static casting methods exists
template < class T >
Vector < Vector < T > > MatrixInitialize(const Vector < Vector < T > >&me,
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

		//(Math::Base::Vector < Vector < T > >)R[j] = I;
	}

	free(I);
	return R;
}

