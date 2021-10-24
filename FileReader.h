#ifndef FILEREADER_H
#define FILEREADER_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iomanip>

/// <summary>
/// Записывает содержимое файла с матрицей в объект класса Matrix.
/// </summary>
/// <param name="fullway2data"> - полный путь и имя файла с матрицей.</param>
/// <returns>Объект класса Matrix.</returns>
Matrix read(std::string fullway2data)
{
	// Объект для чтения файла.
	std::ifstream inputfile;
	// Открыть файл.
	inputfile.open(fullway2data);
	// Матрица, в которую (не) будет записано содержимое файла.
	Matrix Res;

	// Проверить, что файл удалось открыть.
	if (inputfile.is_open())
	{
		/*
		Алгоритм работы:
		1. В buff_s по одной записываются строки текстового файла.
		2. Содержимое строки файла из buff_s копируется(?) в buff_ss.
		3. buff_ss извлекает из своего содержимого числа и записывает их по одному в buff_d.
		4. Значение buff_d помещается в buff_data_row, имитацию одной строки файла.
		5. Содержимое buff_data_row копируется(?) в buff_data, имитацию всей матрицы из файла.
		6. Когда файл полностью прочитан, Res получает новые размеры: количество строк от buff_data и количество столбцов от первого (нулевого) вектора внутри buff_data.
		7. Далее Res просто заполняется значениями из содержимого buff_data.
		*/

		std::string buff_s;
		double buff_d;
		std::vector <double> buff_data_row;
		std::vector <std::vector<double>> buff_data;

		while (getline(inputfile, buff_s))
		{
			std::istringstream buff_ss(buff_s);

			while (buff_ss >> buff_d)
			{
				buff_data_row.push_back(buff_d);
			}

			buff_data.push_back(buff_data_row);
			buff_data_row.clear();
		}

		Res = Matrix(buff_data.size(), buff_data.at(0).size());

		for (size_t row = 0; row < Res.get_rSize(); row++)
		{
			//if (buff_data.at(row).size() != Res.get_cSize()) throw "Error: copied matrix must be square";

			if (buff_data.at(row).size() != Res.get_cSize())
			{
				std::cout << "ERROR: copying matrix is failed! Process was stopped!" << std::endl;

				return Res;
			}

			for (size_t col = 0; col < Res.get_cSize(); col++)
			{
				Res.set_elem(row, col, buff_data.at(row).at(col));
			}
		}
	}
	// Файл не удалось открыть.
	else
	{
		std::cout << "ERROR: copying matrix is failed! File isn't opened!" << std::endl;
	}
	// Вернуть результирующую матрицу.
	return Res;
}
void print(const Matrix& Any, unsigned int precicion)
{
	if ((Any.get_rSize() == 0) || (Any.get_cSize() == 0))
	{
		std::cout << "WARNING: printed matrix is empty!" << std::endl;
	}

	for (size_t i = 0; i < Any.get_rSize(); i++)
	{
		for (size_t j = 0; j < Any.get_cSize(); j++)
		{
			std::cout << std::setprecision(precicion) << std::scientific << Any.get_elem(i, j) << "		";
		}
		std::cout << std::endl;
	}
}

#endif // !FILEREADER_H