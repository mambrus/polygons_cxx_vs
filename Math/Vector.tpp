#include "Vector.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
// Default constructor
template < class T > Vector < T >::Vector()
{
	statmng();
	m_n = 0;
}

// Copy constructor. Run-time invokes when ever an intermediate object is
// needed. Typically part of an expression, i.e. temporary value of
// sub-expression is created using this constructor.
template < class T > Vector < T >::Vector(const Vector & v)
{
	statmng();
	m_n = v.m_n;
	m_v = (T **) calloc(v.m_n, sizeof(T *));

	for (size_t j = 0; j < m_n; j++) {
		m_v[j] = new T();
		*(m_v[j]) = *v.m_v[j];	//De-refer, force deep copy
	}
}

// Assignment constructor
template < class T > Vector < T >::Vector(size_t i, T a[])
{
	statmng();
	m_n = i;
	m_v = (T **) calloc(i, sizeof(T *));

	for (size_t j = 0; j < i; j++) {
		m_v[j] = new T();
		*(m_v[j]) = a[j];
	}
}

// Allocation constructor
// Just allocates the memory and sets sizes.
template < class T > Vector < T >::Vector(size_t i)
{
	statmng();
	T t;

	m_n = i;
	m_v = (T **) calloc(i, sizeof(T *));

	for (size_t j = 0; j < i; j++) {
		m_v[j] = new T();
	}
}

// Allocation constructor
// Just allocates the memory and initializes with type-data.
template < class T > Vector < T >::Vector(size_t i, T a)
{
	statmng();
	T t;

	m_n = i;
	m_v = (T **) calloc(i, sizeof(T *));

	for (size_t j = 0; j < i; j++) {
		m_v[j] = new T();
		*(m_v[j]) = a;
	}
}

// Assignment operator  - Own element type
template < class T > Vector < T > &Vector < T >::operator =(const T i)
{
	if (m_n > 1) {
		free_array();
		m_v = (T **) calloc(1, sizeof(T *));
		m_v[0] = new T();
	} else if (m_n == 0) {
		m_v = (T **) calloc(1, sizeof(T *));
		m_v[0] = new T();
	}
	m_n = 1;
	*(m_v[0]) = i;
	return *this;
}

// Assignment operator  - Array of own element type
// Size is *this, *this must have been instantiated with a size.
template < class T > Vector < T > &Vector < T >::operator =(const T a[])
{
	if (m_n == 0) {
		std::ostringstream s;
		s << "Vector::Length() must not be zero";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
	for (size_t i = 0; i < m_n; i++) {
		*(m_v[i]) = a[i];
	}
	return *this;
}

// Copy operator (see also copy constructor)
template < class T >
    Vector < T > &Vector < T >::operator =(const Vector < T > &v)
{
	if (m_n > 0 && (v.m_n != m_n)) {
		free_array();

		m_n = v.m_n;
		m_v = (T **) calloc(v.m_n, sizeof(T *));

		for (size_t i = 0; i < m_n; i++) {
			m_v[i] = new T();
			*(m_v[i]) = *v.m_v[i];
		}
	} else if (m_n == 0) {
		m_n = v.m_n;
		m_v = (T **) calloc(v.m_n, sizeof(T *));
		for (size_t i = 0; i < m_n; i++) {
			m_v[i] = new T();
			*(m_v[i]) = *v.m_v[i];
		}
	} else {
		for (size_t i = 0; i < m_n; i++) {
			*(m_v[i]) = *v.m_v[i];
		}
	}

	return *this;

}

// Index operator
template < class T > T & Vector < T >::operator [](size_t i) {
	if (i > (m_n - 1)) {
		std::ostringstream s;
		s << "Index [" << i <<
		    "] is out of range for Vector[" << (m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
	return *(m_v[i]);
}

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

template < class T > void Vector < T >::free_array()
{
	if (m_n > 0 && m_v) {
		for (size_t i = 0; i < m_n; i++) {
			free(m_v[i]);
		}
		free(m_v);
	}
}

// Destructor.
template < class T > Vector < T >::~Vector()
{
	--instances;
	free_array();
}

/* Class stats variables */
// Below is probably not such a good idea...
template < class T > int Vector < T >::instances = 0;
template < class T > int Vector < T >::ntotever = 0;

/* NOTE Stubbed TBD !!!*/
template < class T > bool Vector < T >::is_zero(const T & d)
{
	return false;
}
