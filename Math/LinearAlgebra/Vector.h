#pragma once

#include "../Math/Base/Vector.h"

namespace Math {
	namespace LinearAlgebra {
		template < class T > class Vector : Base::Vector<T>
		{
		public:
			Vector() : Base::Vector() {};
			Vector(size_t s, T d[]) : Base::Vector(s, d) {};
			Vector(size_t s, T d) : Base::Vector(s, d) {};
			Vector(size_t s) : Base::Vector(s) {};
			Vector(const Vector & v) : Base::Vector(v) {};

			~Vector() { Base::~Vector(); };
		};
	};
};
