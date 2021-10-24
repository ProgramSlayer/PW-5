#include "Decomposition.h"
#include <cassert>

bool originalMatrixGood(const Matrix& matrix) {
	return  matrix.get_rSize() == matrix.get_cSize() && matrix.get_rSize() != 0;
}

// �����������.
Decomposition::Decomposition(const Matrix& baseMatrix) : m_sideSize{ baseMatrix.get_rSize() }, m_LUValues(baseMatrix.get_rSize()* baseMatrix.get_rSize())
{
	decompose(baseMatrix);
}

// ��������� ��������� ������� �������� �� ������ ���������� �������.
size_t Decomposition::getLinearIndex(const size_t row, const size_t col) const {
	if (row >= m_sideSize || col >= m_sideSize) throw "Error: index out of bounds";
	return row + col * m_sideSize;
}

// ����������.
Decomposition::~Decomposition()
{
    m_LUValues.clear();
    m_LUValues.shrink_to_fit();
}

//const std::vector<double>& Decomposition::getLU() const { return m_LUValues; }

const size_t Decomposition::getSideSize() const { return m_sideSize; }

const double Decomposition::getElemFromLU(size_t row, size_t col) const {
	if (row >= m_sideSize || col >= m_sideSize) throw "Error: index out of bounds";
	return m_LUValues.at(getLinearIndex(row, col));
}

// ���������� �������� �������� L-������� �� �������� �������.
const double Decomposition::getElemFromL(size_t row, size_t col) const {
	if (row >= m_sideSize || col >= m_sideSize) throw "Error: index out of bounds";
	if (col < row) return m_LUValues.at(getLinearIndex(row, col));
	if (row == col) return 1;
	return 0;
}
// ���������� �������� �������� U-������� �� �������� �������.
const double Decomposition::getElemFromU(size_t row, size_t col) const {
	if (row >= m_sideSize || col >= m_sideSize) throw "Error: index out of bounds"; 
	if (col > row) return m_LUValues.at(getLinearIndex(row, col));
	if (row == col) return m_LUValues.at(getLinearIndex(row, col));
	return 0;
}


// ��������� ������� L.
const Matrix Decomposition::getMatrixL() const
{
	Matrix lower(m_sideSize, m_sideSize);
	for (size_t j = 0; j < m_sideSize; j++)
		for (size_t i = j + 1; i < m_sideSize; i++)
			lower.set_elem(i, j, getElemFromLU(i, j));
	for (size_t i = 0; i < m_sideSize; i++)
		lower.set_elem(i, i, 1);
	return lower;
}

// ��������� ������� U.
const Matrix Decomposition::getMatrixU() const
{
	Matrix upper(m_sideSize, m_sideSize);
	for (size_t i = 0; i < m_sideSize; i++)
		for (size_t j = i; j < m_sideSize; j++)
			upper.set_elem(i, j, getElemFromLU(i, j));
	return upper;
}

// ��������� ������� (L/U).
const Matrix Decomposition::getMatrixLU() const {
	Matrix LUmatrix(m_sideSize, m_sideSize);
	for (size_t i = 0; i < m_sideSize; i++)
		for (size_t j = 0; j < m_sideSize; j++)
			LUmatrix.set_elem(i, j, getElemFromLU(i, j));
	return LUmatrix;
}

// ���������� �������.
void Decomposition::decompose(const Matrix& a) 
{
	// �������� �������� �������� L-�������, ����������� ���� ������� ���������, ��� ������� ��������� (L/U) �������,
	// � �������� U-�������, ����������� ���� ������� ���������, ��� ������� ���������� (L/U) �������.
	
	for (size_t i{}; i != m_sideSize; ++i)
		m_LUValues.at(getLinearIndex(i, i)) = 1;

	for (size_t i{}; i != m_sideSize; ++i) 
	{
		for (size_t j{}; j != m_sideSize; ++j) 
		{
			double sumProd{};
			// ������� � (L/U)-������� ������� �� U-�������.
			if (i <= j) 
			{
				for (size_t k{}; k != i; ++k)
					sumProd += m_LUValues.at(getLinearIndex(i, k)) * m_LUValues.at(getLinearIndex(k, j));
				m_LUValues.at(getLinearIndex(i, j)) = a(i, j) - sumProd;
			}
			// ������� � (L/U)-������� ������� �� L-�������.
			else 
			{
				for (size_t k{}; k != j; ++k)
					sumProd += m_LUValues.at(getLinearIndex(i, k)) * m_LUValues.at(getLinearIndex(k, j));
				m_LUValues.at(getLinearIndex(i, j)) = (a(i, j) - sumProd) / m_LUValues.at(getLinearIndex(j, j));
			}
		}
	}
}

