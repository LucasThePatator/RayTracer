#pragma once

#define USE_BA

#include <stdint.h>
#define LARGE_DOUBLE std::numeric_limits<double>::max()
#define EPSILON 1e-10

#ifdef USE_UBLAS

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric::ublas;

class unit_Vector3d : public unit_vector<double> {

public: 

	unit_Vector3d() : unit_vector() {
	}

	unit_Vector3d(size_type index) : unit_vector(3, index) {
	}
};

typedef unit_Vector3d directionVector3d;

class Vector3d : public vector<double> {
public: 
	Vector3d() : vector() {
	}

	Vector3d(size_type index) : vector(3, index) {
	}
};

typedef Vector3d Point3d;
typedef Vector3d Color3d;

#endif
#ifdef USE_MTL

#include <mtl.hpp>
using namespace mtl;

typedef dense_vector<double> Vector3d;
typedef Vector3d Color3d;
typedef Vector3d Point3d;

#endif
#ifdef USE_BA

#include "BasicAlgebra.h"

typedef Vector<double, 3> Vector3d;
typedef Vector3d Color3d;
typedef Vector3d Point3d;

#endif


