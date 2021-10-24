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
/// ���������� ���������� ����� � �������� � ������ ������ Matrix.
/// </summary>
/// <param name="fullway2data"> - ������ ���� � ��� ����� � ��������.</param>
/// <returns>������ ������ Matrix.</returns>
Matrix read(std::string fullway2data)
{
	// ������ ��� ������ �����.
	std::ifstream inputfile;
	// ������� ����.
	inputfile.open(fullway2data);
	// �������, � ������� (��) ����� �������� ���������� �����.
	Matrix Res;

	// ���������, ��� ���� ������� �������.
	if (inputfile.is_open())
	{
		/*
		�������� ������:
		1. � buff_s �� ����� ������������ ������ ���������� �����.
		2. ���������� ������ ����� �� buff_s ����������(?) � buff_ss.
		3. buff_ss ��������� �� ������ ����������� ����� � ���������� �� �� ������ � buff_d.
		4. �������� buff_d ���������� � buff_data_row, �������� ����� ������ �����.
		5. ���������� buff_data_row ����������(?) � buff_data, �������� ���� ������� �� �����.
		6. ����� ���� ��������� ��������, Res �������� ����� �������: ���������� ����� �� buff_data � ���������� �������� �� ������� (��������) ������� ������ buff_data.
		7. ����� Res ������ ����������� ���������� �� ����������� buff_data.
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
			if (buff_data.at(row).size() != Res.get_cSize()) throw "Error: copied matrix must be square";

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
	// ���� �� ������� �������.
	else
	{
		std::cout << "ERROR: copying matrix is failed! File isn't opened!" << std::endl;
	}
	// ������� �������������� �������.
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