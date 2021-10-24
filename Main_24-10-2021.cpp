#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>
#include "Matrix.h"
#include "FileReader.h"
#include "Decomposition.h"
#include "Solver.h"
#include "Timer.h"

// Примитивный вывод элементов матрицы на консоль.
void printMatrix(const Matrix& m, const unsigned int precision = 6)
{
	if (m.get_cSize() == 0 || m.get_rSize() == 0)
	{
		std::cout << "Matrix is zero!\n\n";
		return;
	}

	for (size_t i{ 0 }; i != m.get_rSize(); ++i)
	{
		for (size_t j{ 0 }; j != m.get_cSize(); ++j)
		{
			//std::cout.width(20);
			std::cout << std::setprecision(precision) << std::scientific << m(i, j) << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

/// <summary>
/// Возвращает (псевдо)случайное число в заданном диапазоне.
/// </summary>
/// <param name="min"> - нижняя граница диапазона.</param>
/// <param name="max"> - верхняя граница диапазона.</param>
/// <returns>(Псевдо)случайное число в заданном диапазоне.</returns>
double getRandomRealNumber(const double min = -100, const double max = 100)
{
	// Генератор, который инициализируется от времени вызова функции time().
	static std::mt19937 generator{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	// Размещение, которое как раз и будет возвращать случайное число.
	std::uniform_real_distribution<> d{ min, max };
	return d(generator);
}

/// <summary>
/// Заполняет переданную матрицу (псевдо)случайными числами в заданном диапазоне.
/// </summary>
/// <param name="m"> - матрица для заполнения.</param>
/// <param name="min"> - нижняя граница диапазона.</param>
/// <param name="max"> - верхняя граница диапазона.</param>
void fillMatrixWithRandomNumbers(Matrix& m, const double min = -100, const double max = 100)
{
	for (size_t i{}; i != m.get_rSize(); ++i)
		for (size_t j{}; j != m.get_cSize(); ++j)
			m(i, j) = getRandomRealNumber(min, max);
}

// Пользовательский ввод наименования файла
std::string userFileInput(const std::string& filePath)
{
	std::string input{};
	std::ifstream tryToOpenFile;
	while (true)
	{
		std::cout << "Input name and extension of file.\n";
		std::cout << "Your input >> ";
		std::getline(std::cin, input);
		if (!input.find(".txt"))
		{
			std::cout << "Your input file doesn't have an extension!\n\n";
			continue;
		}
		else
		{
			tryToOpenFile.open(std::string(filePath + input));
			if (!tryToOpenFile.is_open())
			{
				std::cout << "File not found!\n\n";
				continue;
			}
		}
		return input;
	}
}

int main()
{
	while (true) {

		std::string path{ ".\\Matrixes\\" };

		// Полный путь к файлу
		std::string fullPathAndName{ path + userFileInput(path) };

		try {
			Matrix a{ read(fullPathAndName) };

			// Проверка определителя матрицы после считывания из файла
			if (a.det() == 0.0) {
				throw "Error: determinant = 0\n";
			}

			// Точное решение СЛАУ.
			Matrix x_exist{ a.get_rSize(), 1 };
			fillMatrixWithRandomNumbers(x_exist);

			// Вектор правой части.
			Matrix b{ a * x_exist };

			Timer t;

			// Решение СЛАУ методом Крамера.
			Matrix x_Cramer{ Solver::solveSoLAE(a, b) };
			auto cramerMethodTimeElapsed{ t.elapsed() };

			t.reset();

			// Решение СЛАУ через LU-разложение.
			Matrix x_LU{ Solver::solveSoLAE(a, b, Solver::SolutionMethod::LU_DECOMPOSITION) };

			auto luMethodTimeElapsed{ t.elapsed() };

			std::cout << "Cramer method time elapsed: " << std::setprecision(15) << std::scientific << cramerMethodTimeElapsed << '\n';
			std::cout << "LU method time elapsed: " << std::setprecision(15) << std::scientific << luMethodTimeElapsed << "\n\n";

			std::cout << "|| x_exist - x_Cramer || = " << std::setprecision(15) << std::scientific << (x_exist - x_Cramer).norm() << '\n';
			std::cout << "|| x_exist - x_LU ||     = " << std::setprecision(15) << std::scientific << (x_exist - x_LU).norm() << '\n';
			std::cout << "|| x_Cramer - x_LU ||    = " << std::setprecision(15) << std::scientific << (x_Cramer - x_LU).norm() << '\n';
			break;
		}
		catch (const char* e) {
			std::cout << e << '\n';
		}
		catch (...) {
			std::cout << "Something's wrong, I can feel it" << '\n';
		}
	}

	return 0;
}