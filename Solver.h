//#pragma once
//
//
//
//#include "Matrix.h"
//#include "Decomposition.h"
//
//
//Matrix cramersRule(Matrix& matrix, Matrix& vectorCol);
//
//class Task {
//private:
//	Matrix m_a;
//	Matrix m_vectorColumn;
//
//public:
//	Task(const Matrix& aMatrix, const Matrix& vectorColumn) : m_a{ aMatrix }, m_vectorColumn{ vectorColumn }{}
//};
//
//class Solver
//{
//private:
//	// 0) Values:
//	// ������� ������� (������� � [��. ��������])   || ��� ��� ��������� ����� ���������� � ������ Task 
//	// ������ ����� (������ b [��. ��������])		|| � ������������ ����� Task c ������� Solver.
//	//
//	// ����� ������ �������� �������� ��� �� ������������� ������� ������������ ��� ������� � �������.
//	// ����� ����� �������� ����, �������� ������ ������� ������� ������� ��� ����������� ������������� �������� ����������.
//	// � ����� ������ ������������ ������ ���������� ������ � ������ ������ ������� LU �����������.
//
//
//public:
//	enum class SolverMethod { CRAMER, LU_DECOMPOSITON };
//	
//};


#ifndef SOLVER_H
#define SOLVER_H

#include "Matrix.h"
#include "Decomposition.h"
//#include <utility>

class Solver
{
private:
	// cramer()
	static Matrix cramer(const Matrix& coefMatrix, const Matrix& vectorColumn);
	
	/* lu_decomposition()
	static Matrix lu_decomposition(const Matrix& coefMatrix, const Matrix& vectorColumn);*/

	static Matrix lu_decomposition(const Matrix& coefMatrix, const Matrix& vectorColumn);

public:
	enum class SolutionMethod { CRAMER, LU_DECOMPOSITION };
	static Matrix solveSoLAE(const Matrix& coefMatrix, const Matrix& vectorColumn, const SolutionMethod sm = SolutionMethod::CRAMER);
};


#endif // !SOLVER_H