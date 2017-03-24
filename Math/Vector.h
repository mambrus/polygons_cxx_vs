#ifndef Vector_h
#    define Vector_h
#    include <MathExports.h>
#    include <stdlib.h>
#    include <iostream>
#    include <sstream>

using namespace std;

// Number of elements in array
#    define NELEM( A ) \
	( sizeof(A) / sizeof(A[0]) )

MATH_EXPORT template < class T > class Vector {

 protected:
	//Sub-optimal ways of keeping track of statistics
	static int instances;
	static int ntotever;
	const inline void statmng() {
		instances++;
		m_uid = ntotever;
		ntotever++;
	};

 private:
	T ** m_v;
	size_t m_n;
	int m_uid;		/* Unique id. Used for debugging DTOR/CTOR order of
				   tmp/stack instances. */
	virtual bool is_zero(const T &);

	void free_array();

 public:
	MATH_EXPORT Vector();
	MATH_EXPORT Vector(size_t, T[]);
	MATH_EXPORT Vector(size_t, T);
	MATH_EXPORT Vector(size_t);

	//Copy constructor
	MATH_EXPORT Vector(const Vector & v);

	MATH_EXPORT inline int Length() {
		return m_n;
	}

	// Operators
	// Assignment
	MATH_EXPORT virtual Vector & operator =(const T i);
	MATH_EXPORT virtual Vector & operator =(const T a[]);
	MATH_EXPORT virtual Vector & operator =(const Vector & v);

	// Index operator
	MATH_EXPORT virtual T & operator[] (size_t i);

	//Linear algebra operators
	// ====================================================================
	template < class Y >
	    MATH_EXPORT const friend Vector < Y > operator +(const Vector < Y >
							     lhs,
							     const Vector < Y >
							     &);
	template < class Y > MATH_EXPORT const friend Vector < Y >
	    operator -(const Vector < Y >, const Vector < Y > &);


#    ifdef NEVER
	MATH_EXPORT const friend Vector operator *(const Vector lhs,
						   const T & m);
	MATH_EXPORT const friend Vector operator /(const Vector lhs,
						   const T & d);
#    endif			//NEVER
	// ====================================================================

	MATH_EXPORT friend ostream & operator<<(ostream & out, const Vector & v) {
		size_t i;
		out << "{";
		for (i = 0; i < v.m_n - 1; i++) {
			out << *(v.m_v[i]) << ",";
		};
		out << *(v.m_v[i]) << "}";
		return out;
	}

	MATH_EXPORT static ostream & stats(ostream & out) {
		out << "{i=";
		out << instances;
		out << ",";
		out << "t=";
		out << ntotever;
		out << "}" << endl;
		return out;
	}

	MATH_EXPORT ~ Vector();
};

#    include "Vector.tpp"

#endif				//Vector_h
