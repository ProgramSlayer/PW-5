#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>
#include <locale>
#include <cstdlib>
#include "Matrix.h"
#include "FileReader.h"
#include "Decomposition.h"
#include "Solver.h"
#include "Timer.h"

// ����������� ����� ��������� ������� �� �������.
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
/// ���������� (������)��������� ����� � �������� ���������.
/// </summary>
/// <param name="min"> - ������ ������� ���������.</param>
/// <param name="max"> - ������� ������� ���������.</param>
/// <returns>(������)��������� ����� � �������� ���������.</returns>
double getRandomRealNumber(const double min = -100, const double max = 100)
{
	// ���������, ������� ���������������� �� ������� ������ ������� time().
	static std::mt19937 generator{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	// ����������, ������� ��� ��� � ����� ���������� ��������� �����.
	std::uniform_real_distribution<> d{ min, max };
	return d(generator);
}

/// <summary>
/// ��������� ���������� ������� (������)���������� ������� � �������� ���������.
/// </summary>
/// <param name="m"> - ������� ��� ����������.</param>
/// <param name="min"> - ������ ������� ���������.</param>
/// <param name="max"> - ������� ������� ���������.</param>
void fillMatrixWithRandomNumbers(Matrix& m, const double min = -100, const double max = 100)
{
	for (size_t i{}; i != m.get_rSize(); ++i)
		for (size_t j{}; j != m.get_cSize(); ++j)
			m(i, j) = getRandomRealNumber(min, max);
}

// ���������������� ���� ������������ �����
std::string userFileInput(const std::string& filePath)
{
	std::string input{};
	std::ifstream tryToOpenFile;
	while (true)
	{
		std::cout << "������� ��� � ���������� �����.\n";
		std::cout << "��� ���� >> ";
		std::getline(std::cin, input);
		if (!input.find(".txt"))
		{
			std::cout << "���, ���� ��� ����������!\n\n";
			continue;
		}
		else
		{
			tryToOpenFile.open(std::string(filePath + input));
			if (!tryToOpenFile.is_open())
			{
				std::cout << "���, ���� �� ������!\n\n";
				continue;
			}
		}
		return input;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp1251");
	system("cls");
	while (true) {

		std::string path{ ".\\Matrixes\\" };

		// ������ ���� � �����
		std::string fullPathAndName{ path + userFileInput(path) }; 

		try{ 
			Matrix a{ read(fullPathAndName) }; 

			// �������� ������������ ������� ����� ���������� �� �����
			if (a.det() == 0.0) {
				throw "Error: determinant = 0\n" ;
			}

			// ������ ������� ����.
			Matrix x_exist{ a.get_rSize(), 1 };
			fillMatrixWithRandomNumbers(x_exist);

			// ������ ������ �����.
			Matrix b{ a * x_exist };

			Timer t;

			// ������� ���� ������� �������.
			Matrix x_Cramer{ Solver::solveSoLAE(a, b) };
			auto cramerMethodTimeElapsed{ t.elapsed() };

			t.reset();

			// ������� ���� ����� LU-����������.
			Matrix x_LU{ Solver::solveSoLAE(a, b, Solver::SolutionMethod::LU_DECOMPOSITION) };

			auto luMethodTimeElapsed{ t.elapsed() };

			std::cout << "Cramer method time elapsed: " << std::setprecision(15) << std::scientific << cramerMethodTimeElapsed << '\n';
			std::cout << "LU method time elapsed: " << std::setprecision(15) << std::scientific << luMethodTimeElapsed << "\n\n";

			std::cout << "|| x_exist - x_Cramer || = " << std::setprecision(15) << std::scientific << (x_exist - x_Cramer).norm() << '\n';
			std::cout << "|| x_exist - x_LU ||     = " << std::setprecision(15) << std::scientific << (x_exist - x_LU).norm() << '\n';
			std::cout << "|| x_Cramer - x_LU ||    = " << std::setprecision(15) << std::scientific << (x_Cramer - x_LU).norm() << '\n';
			break;
		}
		catch(const char* e) {
			std::cout<< e << '\n';
		}
		catch (...) {
			std::cout << "���-�� �� ���!"<< '\n';
		}
	}
			
	return 0;
}