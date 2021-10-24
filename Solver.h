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