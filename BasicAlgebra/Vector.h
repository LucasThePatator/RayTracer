#pragma once

#include <cmath>

template<typename T, size_t size>
class Vector
{
public:

	Vector(void)
	{
		for(int i = 0; i < size; i++)
			this->vector[i] = 0;
	}

	Vector(const Vector<T, size> &vec)
	{
		for(int i = 0; i < size; i++)
			this->vector[i] = vec.vector[i];
	}

	Vector(T value) 
	{
		for (int i = 0; i < size; i ++) {
			this->vector[i] = value;
		}
	}

	~Vector(void)
	{
	}

	//Operators

	//Multiplication by a scalar
	template<typename T, size_t size>
	friend Vector<T, size> operator* (T scalar, const Vector<T, size> &op) {

		Vector<T, size> result(op);
		for(int i = 0; i < size; i++) {
			result.vector[i] *= scalar;
		}

		return result;
	}

	//Multiplication by a scalar
	Vector<T, size> operator*= (T scalar) {
		Vector<T, size> result;
		for(int i = 0; i < size; i++) {
			this->vector[i] *= scalar;
		}

		return result;
	}


	//division by a scalar
	template<typename T, size_t size>
	friend Vector<T, size> operator/ (const Vector<T, size> &op, T scalar) {

		Vector<T, size> result(op);
		for(int i = 0; i < size; i++) {
			result.vector[i] /= scalar;
		}

		return result;
	}

	//Scalar product between two vectors
	template<typename T, size_t size>
	friend T operator* (const Vector<T, size> &op1, const Vector<T, size> &op2) {

		T result = 0;
		for(int i = 0; i < size; i++) {
			result += op1.vector[i] * op2.vector[i];
		}

		return result;
	}

	Vector<T, size> operator += (const Vector<T, size> &op1) {

		Vector<T, size> result(0);
		for(int i = 0; i < size; i++) {
			this->vector[i] = this->vector[i] * op1.vector[i];
		}

		return result;
	}

	//Addition of two vectors
	template<typename T, size_t size>
	friend Vector<T, size> operator+ (const Vector<T, size> &op1, const Vector<T, size> &op2) {

		Vector<T, size>  result;
		for (int i = 0; i < size; i ++) {
			result.vector[i] = op1.vector[i] + op2.vector[i];
		}

		return result;
	}

	//Unary minus for a vector
	template<typename T, size_t size>
	friend Vector<T, size> operator- (const Vector<T, size> &op2) {

		Vector<T, size>  result;
		for (int i = 0; i < size; i ++) {
			result.vector[i] = - op2.vector[i];
		}

		return result;
	}

	//Substraction of two vectors
	template<typename T, size_t size>
	friend Vector<T, size> operator- (const Vector<T, size> &op1, const Vector<T, size> &op2) {

		Vector<T, size>  result;
		for (int i = 0; i < size; i ++) {
			result.vector[i] = op1.vector[i] - op2.vector[i];
		}

		return result;
	}

	//Square norm2 of a vector
	template<typename T, size_t size>
	friend T norm2_2 (const Vector<T, size> &op) {

		T result = 0;
		for(int i = 0; i < size; i++) {
			result += op.vector[i] * op.vector[i];
		}

		return result;
	}

	//norm2 of a vector
	template<typename T, size_t size>
	friend T norm2(const Vector<T, size> &op) {

		T result = 0;
		for(int i = 0; i < size; i++) {
			result += op.vector[i] * op.vector[i];
		}

		return sqrt(result);
	}

	//Access to the elements
	T &operator[] (int i) {
		return vector[i];
	}

	bool operator== (const Vector<T, size> &op) {
		for(int i = 0; i < size; i++) {
			if (this->vector[i] != op.vector[i])
				return false;
		}
		return true;
	}

	bool operator!= (const Vector<T, size> &op) {
		for(int i = 0; i < size; i++) {
			if (this->vector[i] != op.vector[i])
				return true;
		}
		return false;
	}


	//dot product
	template<typename T, size_t size>
	friend Vector<T, size> dot(const Vector<T, size> &op1, const Vector<T, size> &op2) {

		Vector<T, size> result(0);
		for(int i = 0; i < size; i++) {
			result.vector[i] = op1.vector[i] * op2.vector[i];
		}

		return result;
	}

private :
	T vector[size];
};




