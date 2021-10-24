#include "Solver.h"

Matrix Solver::solveSoLAE(const Matrix& coefMatrix, const Matrix& vectorColumn, const SolutionMethod sm)
{
	switch (sm)
	{
	case SolutionMethod::CRAMER:
		return Matrix(cramer(coefMatrix, vectorColumn));
	case SolutionMethod::LU_DECOMPOSITION:
		return Matrix(lu_decomposition(coefMatrix, vectorColumn));
	default:
		return Matrix(0, 0);
	}
}

Matrix Solver::cramer(const Matrix& coefMatrix, const Matrix& vectorColumn)
{
	double determinator = coefMatrix.det();

	// ��� ������, ���� ������������ = 0?

	Matrix resultX(vectorColumn.get_rSize(), 1);

	for (size_t i{}; i != vectorColumn.get_rSize(); ++i)
	{
		Matrix cramersMatrix{ coefMatrix };
		cramersMatrix.set_column(i, vectorColumn);
		double detI = cramersMatrix.det();
		resultX(i, 0) = detI / determinator;
	}
	return resultX;
}

Matrix Solver::lu_decomposition(const Matrix& coefMatrix, const Matrix& vectorColumn)
{
	// ���������� ������� ����� ���������� � ���������.

	// LU-���������� ���������� �������.
	Decomposition lu{ coefMatrix };

	// ������ ���������: Ly = vectorColumn.

	Matrix yVector{ lu.getSideSize(), 1 };
	for (size_t i{ 0 }; i < yVector.get_rSize(); ++i)
	{
		// ����� ������������ L(i, k) * y(k, 0).
		double sumOfProducts{};
		for (size_t k{}; k < i; ++k)
			sumOfProducts += lu.getElemFromL(i, k) * yVector(k, 0);
		yVector(i, 0) = vectorColumn(i, 0) - sumOfProducts;
	}

	// ������ ��������� Ux = y.

	auto lastElementIndex{ yVector.get_rSize() - 1 };
	Matrix xVector{ yVector.get_rSize(), 1 };

	// � ����������� ����� ���� �������� � ����������.
	// ��� ������: https://www.boost.org/doc/libs/develop/libs/safe_numerics/doc/html/tutorial/3.html

	for (size_t i{ lastElementIndex }; i >= 0 && i < xVector.get_rSize(); --i)
	{
		double sumOfProducts{};
		for (size_t k{ i }; k != lastElementIndex; ++k)
			sumOfProducts += lu.getElemFromU(i, k) * xVector(k, 0);
		xVector(i, 0) = (yVector(i, 0) - sumOfProducts) / lu.getElemFromU(i, i);
	}

	return xVector;
}