#pragma once
//���������������� ���(�����);
//���������� ������ :
//	����� ��������� �������� �������;
//	����� ���������� ������ ������
//	�������� ���������� ������������ det();
//	����� ������ �������;
//	��������� �����;
//	��������� ��������;
//	��������� ������������;
//	���������� �������.

#include <iostream>
#include <vector>
//#include <utility>

class Matrix
{
private:
	/// <summary>
	/// ���������� �������� ������ �������� ������� �� �������� �������.
	/// </summary>
	/// <param name="row"> - ������ ��������.</param>
	/// <param name="col"> - ������� ��������.</param>
	size_t get_index(size_t row, size_t col) const;	// ������ ������� ������� ���� ����� ���������?

	std::vector <double> m_values;	// ������ �������� (������� �������� ��� ������������������ ��������).
	size_t m_rown;					// ���������� �����.
	size_t m_coln;					// ���������� ��������.

public:

	Matrix();
	Matrix(size_t rown, size_t coln); // �������������� ������� �������� �������� (��������� ������).
	Matrix(const Matrix& m);
	//Matrix(Matrix&& m) noexcept : m_coln{ m.m_coln }, m_rown{ m.m_rown }, m_values{ std::move_if_noexcept(m.m_values) }{}

	~Matrix();

	// ���������� ���������� ����� �������.
	const size_t get_rSize() const;
	// ���������� ���������� �������� �������.
	const size_t get_cSize() const;
	// ���������� �������� �������� ������� �� �������� �������.
	const double get_elem(size_t row, size_t col) const;
	// ������������� �������� �������� ������� �� �������� �������.
	void set_elem(size_t row, size_t col, const double value);

	/// <summary>
	/// �������� �������� ������� ������� ������� �� �������� ����������� �������-�������.
	/// </summary>
	/// <param name="col"> - ����� ������� ������� �������, �������� �������� ���� ��������.</param>
	/// <param name="column"> - ������-�������, �������� �������� ������� �������� ������� ������� �������.</param>
	void set_column(size_t col, const Matrix& column); // ������ �������� ������� ������

	const double det() const;	// ����� ������������.
	const double norm() const;	// ����� ����������� ����� �������.

	Matrix& operator=(const Matrix& Any);	// �������� ������������ ������������.

	// ���������� ��� ����������� �������� Matrix (������ ��������� �������� ��������).
	const double operator()(size_t row, size_t col) const;
	// ���������� ��� ������� �������� Matrix (���������/��������� ��������).
	double& operator()(size_t row, size_t col);
};

Matrix operator+(const Matrix& left, const Matrix& right);	// ���������� �� ���� ������, �������� ������ �� ���������.
Matrix operator-(const Matrix& left, const Matrix& right);	// ��� ���������� +,-,/, ���� ���� �����������, ����� ������������
Matrix operator*(const Matrix& left, const Matrix& right);	// ���������� ����� �������, ��� � ������ �������.