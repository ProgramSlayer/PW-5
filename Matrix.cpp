#include "Matrix.h"
#include <cassert>
#include <algorithm>

#pragma region ��������� �������

/// <summary>
/// ���������� �������� � �������� ������� �� �������� �������.
/// </summary>
/// <param name="Any"> - ������� ��� ������.</param>
/// <param name="row"> - ������ ��������.</param>
/// <param name="col"> - ������� ��������.</param>
/// <param name="added_value"> - �������� ��� �����������.</param>
void add(Matrix& Any, size_t row, size_t col, const double added_value)
{
	Any.set_elem(row, col, Any.get_elem(row, col) + added_value);
}

/// <summary>
/// ������ � ������� 2 ������ �������.
/// </summary>
/// <param name="any"> - ������� ��� ������������ �����.</param>
/// <param name="first"> - ������ ������ ������ ��� ������������.</param>
/// <param name="second"> - ������ ������ ������ ��� ������������.</param>
/// <returns>
/// true - ������������ �����������; false - ������������ �� �����������.
/// </returns>
bool rowSwap(Matrix& any, const size_t first, const size_t second) 
{
	// �������� �� ������� �������.
	if (any.get_rSize() == 0 || any.get_cSize() == 0) return 0;
	// �������� �� ��, ��������� �� ������� ����� � �������� �������.
	if (first >= any.get_rSize() || second >= any.get_rSize()) return 0;
	// �������� �� ��, ��� ������� ����� �� ���������.
	if (first == second) return 0;
	
	// ����� �������� ��������� ������������.
	for (size_t column{}; column != any.get_cSize(); ++column)
		std::swap(any(first, column), any(second, column));
	// ������������ ���������.
	return 1;
}

#pragma endregion

#pragma region ������ Matrix
	
	// ���������� �������� ������ �������� ������� �� �������� �������.
	size_t Matrix::get_index(size_t row, size_t col) const
	{
		//assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE"); // assert(bool = true)
		//assert((row < this->rown) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");
		return row + col * m_rown;
	}

	// ����������� �� ���������.
	Matrix::Matrix() : m_values{0}, m_rown(1), m_coln(1) {}

	// �����������, ����������� ������� ������� � ���������������� � �������� ������� ���������.
	Matrix::Matrix(size_t rown, size_t coln) : m_coln(coln), m_rown(rown), m_values(coln * rown) {}

	// ���������� �����������.
	Matrix::Matrix(const Matrix& m) : m_coln{ m.m_coln }, m_rown{ m.m_rown }, m_values{ m.m_values } {}

	// ����������.
	Matrix::~Matrix()
	{
		m_values.clear();
		m_values.shrink_to_fit();
	}

	// ���������� ����� �������.
	const size_t Matrix::get_rSize() const { return m_rown; }
	// ���������� �������� �������.
	const size_t Matrix::get_cSize() const { return m_coln; }

	// ��������� �������� ������� �� �������� �������.
	const double Matrix::get_elem(size_t row, size_t col) const
	{
		if (row >= m_rown || col >= m_coln)
			throw "Error: matrix index out of bounds";
		return m_values.at(get_index(row, col));
	}

	// ��������� �������� �������� ������� �� �������� �������.
	void Matrix::set_elem(size_t row, size_t col, const double value)
	{
		if (row >= m_rown || col >= m_coln)
			throw "Error: matrix index out of bounds";

		//this->values.erase(this->values.begin() + this->get_index(row, col));
		//this->values.insert(this->values.begin() + this->get_index(row, col), value);
		m_values.at(get_index(row, col)) = value;
	}

	/// <summary>
	/// �������� �������� ������� ������� ������� �� �������� ����������� �������-�������.
	/// </summary>
	/// <param name="col"> - ����� ������� ������� �������, �������� �������� ���� ��������.</param>
	/// <param name="column"> - ������-�������, �������� �������� ������� �������� ������� ������� �������.</param>
	void Matrix::set_column(size_t col, const Matrix& column)
	{
		if (col >= m_coln)
			throw "Error: matrix index out of bounds";
		if (column.m_rown != m_rown)
			throw "Error: matrixes have different amounts of rows";
		if (column.m_coln != 1)
			throw "Error: matrix must be a column matrix";

		// ������� ����������� ������� �� ����� ������� �������� �������.
		m_values.erase(m_values.begin() + col * m_rown, m_values.begin() + (col + 1) * m_rown);
		m_values.insert(m_values.begin() + col * m_rown, column.m_values.begin(), column.m_values.end());
	}

	// ����� ������������ ������� ������� ������.
	const double Matrix::det() const {
		// ��������:
		if (get_cSize() != get_rSize()) throw "Error: matrix is not square";
		if (get_cSize() == 0) throw "Error: matrix must be no zero";

		// ���� ������� ������� �� 1 �����, ������ ������� ��� �����.
		if ((get_cSize() == 1) && (get_rSize() == 1))
			return this->get_elem(0, 0);

		// ����� ���������� ����� ������, ������� ��� ���� ������: https://codereview.stackexchange.com/questions/204135/determinant-using-gauss-elimination
		Matrix workCopy{ *this };
		size_t num = m_coln;
		double det = 1;

		for (size_t i = 0; i < num; ++i) {
			
			// ���������� �������, ���������� �����: https://wikiboard.ru/wiki/Pivot_element
			double pivotElement = workCopy.get_elem(i,i); 
			
			size_t pivotRow = i;
			for (size_t row = i + 1; row < num; ++row) {
				if (std::abs(workCopy/*.get_elem*/(row, i)) > std::abs(pivotElement)) {
					pivotElement = workCopy/*.get_elem*/(row, i);
					pivotRow = row;
				}
			}
			if (pivotElement == 0.0) return 0.0; 
			if (pivotRow != i) {
				// ������������ ����� ��� ���������� ����������.
				rowSwap(workCopy, i, pivotRow);
				det *= -1.0;
			}
			det *= pivotElement;
			for (size_t row = i + 1; row < num; ++row) {
				for (size_t col = i + 1; col < num; ++col) {
					// ����������.
					workCopy(row, col) -= workCopy/*.get_elem*/(row, i) * workCopy/*.get_elem*/(i, col) / pivotElement;
				}
			}	
		}
		return det;
	}


	// ���������� ����������� ����� �������.
	const double Matrix::norm() const
	{
		if (m_rown * m_coln == 0)
			throw "Error: matrix is zero";
		// ������ ������� ��������� ������� �������.
		std::vector<double> absoluteValues(m_rown * m_coln);
		// ��������� ������ �������.
		for (size_t i{}; i != absoluteValues.size(); ++i)
			absoluteValues[i] = std::abs(m_values[i]);
		// ����� ���������� �������� � ������� �������.
		const auto& maxValue{ std::max_element(absoluteValues.begin(), absoluteValues.end()) };
		// ������� ���������� ��������.
		return *maxValue;
	}

	/// <summary>
	/// ����������� ����� ������� ����� ����������� ������ �������.
	/// </summary>
	/// <param name="Any"> - ������ �������.</param>
	/// <returns>������ �� ������� ������.</returns>
	Matrix& Matrix::operator=(const Matrix& Any)
	{
		// ���� ��������� �� ������� ������ this ��������� ���� ��, ���� � ���������� ������ �� �������,
		// ������� ������ �� ������� ������.
		if (this == &Any)
		{
			return *this;
		}

		// ����������� ����������� ������ �������.
		m_coln = Any.m_coln;
		m_rown = Any.m_rown;
		m_values = Any.m_values;

		// ������� ������ �� ������� ������.
		return *this;
	}

	// ���������� ��� ����������� �������� Matrix.
	const double Matrix::operator()(size_t row, size_t col) const
	{
		if (row >= m_rown || col >= m_coln) throw "Error: index out of bounds";
		return m_values.at(get_index(row, col));
	}

	// ���������� ��� ������� �������� Matrix.
	double& Matrix::operator()(size_t row, size_t col)
	{
		if (row >= m_rown || col >= m_coln) throw "Error: index out of bounds";
		return m_values.at(get_index(row, col));
	}

#pragma endregion


#pragma region �������������� ���������
	Matrix operator+(const Matrix& left, const Matrix& right)
	{
		// 0. Checking of the sizes:
		if (left.get_cSize() != right.get_cSize()) throw "Matrixes don't have the same amount of columns";
		if (left.get_rSize() != right.get_rSize()) throw "Matrixes don't have the same amount of rows";
		if (left.get_cSize() == 0 || left.get_rSize() == 0) throw "Error: matrixes must be no zero";

		Matrix result(left.get_rSize(), left.get_cSize());

		for (size_t j = 0; j < right.get_cSize(); j++)
		{
			for (size_t i = 0; i < right.get_rSize(); i++)
			{
				result.set_elem(i, j, left.get_elem(i, j) + right.get_elem(i, j));
			}
		}

		return result;
	}

	Matrix operator-(const Matrix& left, const Matrix& right)
	{
		if (left.get_cSize() != right.get_cSize()) throw "Matrixes don't have the same amount of columns";
		if (left.get_rSize() != right.get_rSize()) throw "Matrixes don't have the same amount of rows";
		if (left.get_cSize() == 0 || left.get_rSize() == 0) throw "Error: matrixes must be no zero";

		Matrix result(left.get_rSize(), left.get_cSize());

		for (size_t j = 0; j < right.get_cSize(); j++)
		{
			for (size_t i = 0; i < right.get_rSize(); i++)
			{
				result.set_elem(i, j, left.get_elem(i, j) - right.get_elem(i, j));
			}
		}

		return result;
	}

	Matrix operator*(const Matrix& left, const Matrix& right)
	{
		// ���������� �������� ����� ������� ������ ��������������� ���������� ����� ������ �������.
		if (left.get_cSize() != right.get_rSize()) throw "Error: columns count of left matrix isn't equal to rows count of right matrix";
		if (left.get_cSize() == 0 || left.get_rSize() == 0) throw "Error: matrixes must be no zero";

		// �������������� �������: l ����� �� ����� �������, n �������� �� ������ �������.
		Matrix result(left.get_rSize(), right.get_cSize());

		// ���������� ������������ �� ������� � ���������.
		for (size_t i{}; i != result.get_rSize(); ++i)
		{
			for (size_t j{}; j != result.get_cSize(); ++j)
			{
				for (size_t r{}; r != left.get_cSize(); ++r)
				{
					add(result, i, j, left.get_elem(i, r) * right.get_elem(r, j));
				}
			}
		}

		return result;
	}
#pragma endregion