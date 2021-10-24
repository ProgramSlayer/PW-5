#pragma once

#include <iostream>
#include <vector>
#include "Matrix.h"

/// <summary>
/// ���������, �������� �� ���������� ������� ��������� � ����������.
/// </summary>
/// <param name="matrix"> - ������� ��� ��������.</param>
/// <returns>
/// true - ������� ��������� � ����������; false - � ��������� ������.
/// </returns>
static bool originalMatrixGood(const Matrix& matrix);

class Decomposition
{
private:
	// ���� ��� �������� ���������� ���������� (L/U) �������.
	std::vector<double> m_LUValues;
	// ������ ������� (L/U) �������.
	size_t m_sideSize{};
	// ���������� �������� ������ ��� ������� � �������� (L/U) �������.
	size_t getLinearIndex(const size_t row, const size_t col) const;
	// ����� ������������.
	void decompose(const Matrix& a);
	// ���������� ������� (L/U) �������.
	const double getElemFromLU(size_t row, size_t col) const;

public:
	// ������������ � �����������.
	Decomposition(const Matrix& baseMatrix);
	~Decomposition();

	//const std::vector<double>& getLU() const;
	
	// ���������� ������ ������� ���������� (L/U) �������.
	const size_t getSideSize() const;

	// ��������� ������ (L/U), L, U.
	const Matrix getMatrixLU() const;
	const Matrix getMatrixL() const;
	const Matrix getMatrixU() const;

	// ��������� ��������� �� ������ L, U.
	const double getElemFromL(size_t row, size_t col) const;
	const double getElemFromU(size_t row, size_t col) const;
};

