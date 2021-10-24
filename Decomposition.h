#pragma once

#include <iostream>
#include <vector>
#include "Matrix.h"

/// <summary>
/// Проверяет, является ли переданная матрица ненулевой и квадратной.
/// </summary>
/// <param name="matrix"> - матрица для проверки.</param>
/// <returns>
/// true - матрица ненулевая и квадратная; false - в противном случае.
/// </returns>
static bool originalMatrixGood(const Matrix& matrix);

class Decomposition
{
private:
	// Поле для хранения компактной квадратной (L/U) матрицы.
	std::vector<double> m_LUValues;
	// Размер стороны (L/U) матрицы.
	size_t m_sideSize{};
	// Возвращает линейный индекс для доступа к элементу (L/U) матрицы.
	size_t getLinearIndex(const size_t row, const size_t col) const;
	// Метод декомпозиции.
	void decompose(const Matrix& a);
	// Возвращает элемент (L/U) матрицы.
	const double getElemFromLU(size_t row, size_t col) const;

public:
	// Конструкторы и деструкторы.
	Decomposition(const Matrix& baseMatrix);
	~Decomposition();

	//const std::vector<double>& getLU() const;
	
	// Возвращает размер стороны квадратной (L/U) матрицы.
	const size_t getSideSize() const;

	// Получение матриц (L/U), L, U.
	const Matrix getMatrixLU() const;
	const Matrix getMatrixL() const;
	const Matrix getMatrixU() const;

	// Получение элементов из матриц L, U.
	const double getElemFromL(size_t row, size_t col) const;
	const double getElemFromU(size_t row, size_t col) const;
};

