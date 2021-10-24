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
//	// Матрица системы (матрица А [см. конспект])   || Эти два параметра можно определить в классе Task 
//	// Правая часть (вектор b [см. конспект])		|| И Асоциировать класс Task c классом Solver.
//	//
//	// Такой подход позволит избавить нас от необходимости хранить декомпозицию или систему в солвере.
//	// Можно также добавить флаг, хранящий способ задания матрицы системы или возможность инициализации объектом разложения.
//	// А можно просто использовать объект разложения только в случае вызова солвера LU разложением.
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