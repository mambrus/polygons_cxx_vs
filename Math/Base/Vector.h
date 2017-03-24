#ifndef Vector_h
#    define Vector_h
#    include <stdlib.h>
#    include <iostream>
#    include <sstream>

using namespace std;

// Number of elements in array
#    define NELEM( A ) \
	( sizeof(A) / sizeof(A[0]) )

namespace Math {
	namespace Base {
		template < class T > class Vector {

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
			Vector();
			Vector(size_t, T[]);
			Vector(size_t, T);
			Vector(size_t);

			//Copy constructor
			Vector(const Vector & v);

			inline size_t Length() {
				return m_n;
			}

			// Operators
			// Assignment
			virtual Vector & operator =(const T i);
			virtual Vector & operator =(const T a[]);
			virtual Vector & operator =(const Vector & v);

			// Index operator
			virtual T & operator[] (size_t i);

			//Linear algebra operators
			// ====================================================================
			template < class Y >
			const friend Vector < Y > operator +(const Vector < Y >
				lhs,
				const Vector < Y >
				&);
			template < class Y > const friend Vector < Y >
				operator -(const Vector < Y >, const Vector < Y > &);


#    ifdef NEVER
				const friend Vector operator *(const Vector lhs,
					const T & m);
				const friend Vector operator /(const Vector lhs,
					const T & d);
#    endif			//NEVER
				// ====================================================================

				friend ostream & operator<<(ostream & out, const Vector & v) {
					size_t i;
					out << "{";
					for (i = 0; i < v.m_n - 1; i++) {
						out << *(v.m_v[i]) << ",";
					};
					out << *(v.m_v[i]) << "}";
					return out;
				}

				static ostream & stats(ostream & out) {
					out << "{i=";
					out << instances;
					out << ",";
					out << "t=";
					out << ntotever;
					out << "}" << endl;
					return out;
				}

				~Vector();
		};

		// Helper functions
		template < class T >
		Vector < Vector < T > >MatrixInitialize(const Vector < Vector < T > >&,
			T baseval);

		// Include template implementation
#    include "Vector.tpp"
	}
}
#endif				//Vector_h
