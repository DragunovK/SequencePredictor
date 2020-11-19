/**
* Created by Kirill Dragunov on 30 oct. 2020 10:56:00
*/

#pragma once
#include <string>
#include <functional>

class SimpleMatrix
{
private:
	double** matrix;
	size_t rows;
	size_t cols;

public:
	~SimpleMatrix();
	SimpleMatrix();
	SimpleMatrix(const SimpleMatrix& other);
	SimpleMatrix(const size_t& rows, const size_t& cols, double** values);
	SimpleMatrix(const size_t& rows, const size_t& cols, const double& value = 0);
	SimpleMatrix(const size_t& rows, const size_t& cols, const double& lowerBound, const double& upperBound);

	SimpleMatrix operator*(const SimpleMatrix& other);
	SimpleMatrix operator*(const double& other);
	void operator*=(const SimpleMatrix& other);
	void operator*=(const double& other);

	SimpleMatrix operator+(const SimpleMatrix& other);
	SimpleMatrix operator+(const double& other);
	void operator+=(const SimpleMatrix& other);
	void operator+=(const double& other);

	SimpleMatrix operator-(const SimpleMatrix& other);
	SimpleMatrix operator-(const double& other);
	void operator-=(const SimpleMatrix& other);
	void operator-=(const double& other);

	SimpleMatrix& operator=(const SimpleMatrix& other);

	void pushBackColumn(const SimpleMatrix& other);
	void pushBackRow(const SimpleMatrix& other);
	void pushBack(const double& val, const bool& asRow);

	SimpleMatrix getColumn(const size_t& index);
	SimpleMatrix getRow(const size_t& index);

	SimpleMatrix getSubColumn(const size_t& index, const size_t& x1, const size_t& x2) const;
	SimpleMatrix getSubRow(const size_t& index, const size_t& y1, const size_t& y2) const;

	SimpleMatrix transpose();
	void transpose_();

	SimpleMatrix elementwiseMult(const SimpleMatrix& other);
	void elementwiseMult_(const SimpleMatrix& other);

	SimpleMatrix function(std::function<double(double)> f);
	void function_(std::function<double(double)> f);

	double** data() const;

	double elementSum() const;

	double at(const size_t& row, const size_t& col);
	void setElement(const size_t& row, const size_t& col, const double& val);

	size_t rowsNumber() const;
	size_t colsNumber() const;

	std::string toString() const;

	friend SimpleMatrix operator+(const double& left, const SimpleMatrix& right);
	friend SimpleMatrix operator+(const int& left, const SimpleMatrix& right);

	friend SimpleMatrix operator-(const double& left, const SimpleMatrix& right);
	friend SimpleMatrix operator-(const int& left, const SimpleMatrix& right);

	friend SimpleMatrix operator*(const double& left, const SimpleMatrix& right);
	friend SimpleMatrix operator*(const int& left, const SimpleMatrix& right);
};

