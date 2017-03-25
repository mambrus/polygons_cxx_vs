#pragma once

#include "../Math/Base/Vector.h"

namespace Math {
	namespace LinearAlgebra {
		template < class T > class Vector : public Base::Vector<T>
		{
		public:
			Vector() : Base::Vector <T> () {};
			Vector(size_t s, T d[]) : Base::Vector <T> (s, d) {};
			Vector(size_t s, T d) : Base::Vector <T> (s, d) {};
			Vector(size_t s) : Base::Vector <T> (s) {};
			Vector(const Vector & v) : Base::Vector <T> (v) {};

			//~Vector() { Base::~Vector(); };

			template < class Y >
			const friend Vector < Y >
				operator +(const Vector < Y >, const Vector < Y > &);

			template < class Y >
			const friend Vector < Y >
				operator -(const Vector < Y >, const Vector < Y > &);


			/*
			template < class Y >
			const friend Vector < Y >
				operator *(const Vector < Y >, const < Y > & m);

			template < class Y >
			const friend Vector < Y >
				operator /(const Vector < Y >, const < Y > & d);
			*/

		};
		// Helper functions
		template < class T >
		Vector < Vector < T > > MatrixInitialize(const Vector < Vector < T > >&,
			T baseval);

		// Include template implementation
#include "Vector.tpp"

	}
}

