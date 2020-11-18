/**
* Created by Kirill Dragunov on 11 nov. 2020 20:58:17
*/

#include "SimpleMatrix.h"
#include <chrono>
#include <random>

std::default_random_engine randomEngine(std::chrono::steady_clock::now().time_since_epoch().count());

SimpleMatrix::~SimpleMatrix()
{
	for (size_t i = 0; i < rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;
}

SimpleMatrix::SimpleMatrix()
{
	matrix = new double* [1];
	matrix[0] = new double[1];
	matrix[0][0] = 0.0;

	rows = cols = 0;
}

SimpleMatrix::SimpleMatrix(const SimpleMatrix& other)
{
	this->rows = other.rows;
	this->cols = other.cols;

	this->matrix = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->matrix[i] = new double[cols];

		for (size_t j = 0; j < cols; j++)
			this->matrix[i][j] = other.matrix[i][j];
	}
}

SimpleMatrix::SimpleMatrix(const size_t& rows, const size_t& cols, const double& value)
{
	this->rows = rows;
	this->cols = cols;

	this->matrix = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->matrix[i] = new double[cols];

		for (size_t j = 0; j < cols; j++)
			this->matrix[i][j] = value;
	}
}

SimpleMatrix::SimpleMatrix(const size_t& rows, const size_t& cols, const double& lowerBound, const double& upperBound)
{
	std::uniform_real_distribution<double> realDistribution(lowerBound, upperBound);

	this->rows = rows;
	this->cols = cols;

	this->matrix = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->matrix[i] = new double[cols];

		for (size_t j = 0; j < cols; j++)
			this->matrix[i][j] = realDistribution(randomEngine);
	}
}

SimpleMatrix::SimpleMatrix(const size_t& rows, const size_t& cols, double** values)
{
	this->rows = rows;
	this->cols = cols;

	this->matrix = new double* [rows];
	for (size_t i = 0; i < this->rows; i++)
	{
		this->matrix[i] = new double[this->cols];
		for (size_t j = 0; j < this->cols; j++)
		{
			this->matrix[i][j] = values[i][j];
		}
	}
}

SimpleMatrix SimpleMatrix::operator*(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = 0.0;
			for (size_t k = 0; k < this->cols; k++)
			{
				resultData[i][j] += this->matrix[i][k] * other.matrix[k][j];
			}
		}
	}

	SimpleMatrix result(this->rows, other.cols, resultData);

	for (size_t i = 0; i < this->rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::operator*(const double& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[this->cols];
		for (size_t j = 0; j < this->cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] * other;
		}
	}

	SimpleMatrix result(this->rows, this->cols, resultData);

	for (size_t i = 0; i < rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

void SimpleMatrix::operator*=(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = 0.0;
			for (size_t k = 0; k < this->cols; k++)
			{
				resultData[i][j] += this->matrix[i][k] * other.matrix[k][j];
			}
		}
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;

	this->matrix = resultData;
}

void SimpleMatrix::operator*=(const double& other)
{
	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			this->matrix[i][j] *= other;
}

SimpleMatrix SimpleMatrix::operator+(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] + other.matrix[i][j];
		}
	}

	SimpleMatrix result(this->rows, other.cols, resultData);

	for (size_t i = 0; i < rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::operator+(const double& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[this->cols];
		for (size_t j = 0; j < this->cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] + other;
		}
	}

	SimpleMatrix result(this->rows, this->cols, resultData);

	for (size_t i = 0; i < rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

void SimpleMatrix::operator+=(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] + other.matrix[i][j];
		}
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;

	this->matrix = resultData;
}

void SimpleMatrix::operator+=(const double& other)
{
	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			this->matrix[i][j] += other;
}

SimpleMatrix SimpleMatrix::operator-(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] - other.matrix[i][j];
		}
	}

	SimpleMatrix result(this->rows, other.cols, resultData);

	for (size_t i = 0; i < rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::operator-(const double& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[this->cols];
		for (size_t j = 0; j < this->cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] - other;
		}
	}

	SimpleMatrix result(this->rows, this->cols, resultData);

	for (size_t i = 0; i < rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

void SimpleMatrix::operator-=(const SimpleMatrix& other)
{
	double** resultData = new double* [this->rows];

	for (size_t i = 0; i < this->rows; i++)
	{
		resultData[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			resultData[i][j] = this->matrix[i][j] - other.matrix[i][j];
		}
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;

	this->matrix = resultData;
}

void SimpleMatrix::operator-=(const double& other)
{
	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			this->matrix[i][j] -= other;
}

SimpleMatrix& SimpleMatrix::operator=(const SimpleMatrix& other)
{
	if (this == &other) {
		return *this;
	}

	this->rows = other.rows;
	this->cols = other.cols;

	this->matrix = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->matrix[i] = new double[cols];

		for (size_t j = 0; j < cols; j++)
			this->matrix[i][j] = other.matrix[i][j];
	}

	return *this;
}

void SimpleMatrix::pushBackColumn(const SimpleMatrix& other)
{
	if (this->rows != other.rows && this->rows == 0)
		this->rows += other.rows;
	for (size_t i = 0; i < this->rows; i++)
	{
		this->matrix[i] = (double*)realloc(this->matrix[i], (this->cols + other.cols) * sizeof(double));
		for (size_t j = 0; j < other.cols; j++)
			this->matrix[i][this->cols + j] = other.matrix[i][j];
	}

	this->cols += other.cols;
}

void SimpleMatrix::pushBackRow(const SimpleMatrix& other)
{
	if (this->cols != other.cols && this->cols == 0)
		this->cols += other.cols;
	this->matrix = (double**)realloc(matrix, (rows + other.rows) * sizeof(*matrix));

	for (size_t i = 0; i < other.rows; i++)
	{
		this->matrix[this->rows + i] = new double[this->cols];
		for (size_t j = 0; j < other.cols; j++)
			this->matrix[this->rows + i][j] = other.matrix[i][j];
	}

	this->rows += other.rows;
}

void SimpleMatrix::pushBack(const double& val, const bool& asRow)
{
	if (asRow)
	{
		if (cols > 1) 
			throw std::exception("pushBack works for column or row vector only. To push back into matrix[2+][2+] use pushBackRow() or pushBackColumn()");

		this->matrix = (double**)realloc(matrix, (++rows) * sizeof(*matrix));
		this->matrix[rows - 1] = new double[this->cols];

		this->matrix[rows - 1][0] = val;
	}
	else
	{
		if (rows > 1)
			throw std::exception("pushBack works for column or row vector only. To push back into matrix[2+][2+] use pushBackRow() or pushBackColumn()");

		this->matrix[0] = (double*)realloc(this->matrix[0], (++cols) * sizeof(double));
		
		this->matrix[0][cols - 1] = val;
	}
}

SimpleMatrix SimpleMatrix::getColumn(const size_t& index)
{
	double** resultData = new double* [this->cols];

	for (size_t i = 0; i < this->cols; i++)
	{
		resultData[i] = new double[1];
		resultData[i][0] = this->matrix[i][index];
	}
	
	SimpleMatrix result(this->cols, 1, resultData);

	for (size_t i = 0; i < cols; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::getRow(const size_t& index)
{
	double** resultData = new double* [1];
	resultData[0] = new double[this->cols];

	for (size_t i = 0; i < this->cols; i++)
		resultData[0][i] = this->matrix[index][i];

	SimpleMatrix result(1, this->cols, resultData);

	for (size_t i = 0; i < 1; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::getSubColumn(const size_t& index, const size_t& x1, const size_t& x2) const
{
	double** resultData = new double* [x2 - x1];

	for (size_t i = 0; i < x2 - x1; i++)
	{
		resultData[i] = new double[1];
		resultData[i][0] = this->matrix[x1 + i][index];
	}

	SimpleMatrix result(x2 - x1, 1, resultData);

	for (size_t i = 0; i < x2 - x1; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::getSubRow(const size_t& index, const size_t& y1, const size_t& y2) const
{
	double** resultData = new double* [1];
	resultData[0] = new double[y2 - y1];

	for (size_t i = 0; i < y2 - y1; i++)
		resultData[0][i] = matrix[index][y1 + i];

	SimpleMatrix result(1, y2 - y1, resultData);

	for (size_t i = 0; i < 1; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix SimpleMatrix::transpose()
{
	SimpleMatrix result(*this);

	result.transpose_();

	return result;
}

void SimpleMatrix::transpose_()
{
	double** resultData = new double* [this->cols];

	for (size_t i = 0; i < this->cols; i++)
	{
		resultData[i] = new double[this->rows];
		for (size_t j = 0; j < this->rows; j++)
		{
			resultData[i][j] = this->matrix[j][i];
		}
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;

	std::swap(this->rows, this->cols);

	this->matrix = resultData;
}

SimpleMatrix SimpleMatrix::elementwiseMult(const SimpleMatrix& other)
{
	SimpleMatrix result(*this);
	
	result.elementwiseMult_(other);
	
	return result;
}

void SimpleMatrix::elementwiseMult_(const SimpleMatrix& other)
{
	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			this->matrix[i][j] *= other.matrix[i][j];
}

SimpleMatrix SimpleMatrix::function(std::function<double(double)> f)
{
	SimpleMatrix result(*this);

	result.function_(f);

	return result;
}

void SimpleMatrix::function_(std::function<double(double)> f)
{
	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			matrix[i][j] = f(matrix[i][j]);
}

double** SimpleMatrix::data() const
{
	return this->matrix;
}

double SimpleMatrix::elementSum() const
{
	double result = 0.0;

	for (size_t i = 0; i < this->rows; i++)
		for (size_t j = 0; j < this->cols; j++)
			result += matrix[i][j];

	return result;
}

double SimpleMatrix::at(const size_t& row, const size_t& col)
{
	return this->matrix[row][col];
}

void SimpleMatrix::setElement(const size_t& row, const size_t& col, const double& val)
{
	this->matrix[row][col] = val;
}

size_t SimpleMatrix::rowsNumber() const
{
	return this->rows;
}

size_t SimpleMatrix::colsNumber() const
{
	return this->cols;
}

std::string SimpleMatrix::toString() const
{
	std::string resultString = "[\n";

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			resultString += (std::to_string(this->matrix[i][j]) + "\t\t");

		resultString.pop_back();
		resultString += '\n';
	}
	resultString += "]";

	return resultString;
}

SimpleMatrix operator+(const double& left, const SimpleMatrix& right)
{
	SimpleMatrix result(right);
	
	result += left;
	
	return result;
}

SimpleMatrix operator+(const int& left, const SimpleMatrix& right)
{
	SimpleMatrix result(right);
	
	result += left;
	
	return result;
}

SimpleMatrix operator-(const double& left, const SimpleMatrix& right)
{
	double** resultData = new double* [right.rows];
	for (size_t i = 0; i < right.rows; i++)
	{
		resultData[i] = new double[right.cols];
		for (size_t j = 0; j < right.cols; j++)
			resultData[i][j] = left - right.matrix[i][j];
	}

	SimpleMatrix result(right.rows, right.cols, resultData);
	
	for (size_t i = 0; i < right.rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix operator-(const int& left, const SimpleMatrix& right)
{
	double** resultData = new double* [right.rows];
	for (size_t i = 0; i < right.rows; i++)
	{
		resultData[i] = new double[right.cols];
		for (size_t j = 0; j < right.cols; j++)
			resultData[i][j] = left - right.matrix[i][j];
	}

	SimpleMatrix result(right.rows, right.cols, resultData);
	
	for (size_t i = 0; i < right.rows; i++)
		delete[] resultData[i];
	delete[] resultData;

	return result;
}

SimpleMatrix operator*(const double& left, const SimpleMatrix& right)
{
	SimpleMatrix result(right);

	result *= left;

	return result;
}

SimpleMatrix operator*(const int& left, const SimpleMatrix& right)
{
	SimpleMatrix result(right);

	result *= left;

	return result;
}

