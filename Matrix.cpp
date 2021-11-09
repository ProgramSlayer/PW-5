#include "Matrix.h"
#include <cassert>
#include <algorithm>


/// <summary>
/// Прибавляет значение к элементу матрицы на заданной позиции.
/// </summary>
/// <param name="Any"> - матрица для работы.</param>
/// <param name="row"> - строка элемента.</param>
/// <param name="col"> - столбец элемента.</param>
/// <param name="added_value"> - значение для прибавления.</param>
void add(Matrix& Any, size_t row, size_t col, const double added_value)
{
	Any.set_elem(row, col, Any.get_elem(row, col) + added_value);
}

/// <summary>
/// Меняет в матрице 2 строки местами.
/// </summary>
/// <param name="any"> - матрица для перестановки строк.</param>
/// <param name="first"> - индекс первой строки для перестановки.</param>
/// <param name="second"> - индекс второй строки для перестановки.</param>
/// <returns>
/// true - перестановка произведена; false - перестановка не произведена.
/// </returns>
bool rowSwap(Matrix& any, const size_t first, const size_t second)
{
	// Проверка на нулевую матрицу.
	if (any.get_rSize() == 0 || any.get_cSize() == 0) return 0;
	// Проверка на то, находятся ли индексы строк в пределах матрицы.
	if (first >= any.get_rSize() || second >= any.get_rSize()) return 0;
	// Проверка на то, что индексы строк не совпадают.
	if (first == second) return 0;

	// После проверок выполнить перестановку.
	for (size_t column{}; column != any.get_cSize(); ++column)
		std::swap(any(first, column), any(second, column));
	// Перестановка выполнена.
	return 1;
}



// Возвращает линейный индекс элемента матрицы на заданной позиции.
size_t Matrix::get_index(size_t row, size_t col) const
{
	//assert((col < this->coln) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE"); // assert(bool = true)
	//assert((row < this->rown) && "ERROR_MATRIX_INDEX_IS_OUT_SIZE");
	return row + col * m_rown;
}

// Конструктор по умолчанию.
Matrix::Matrix() : m_values{ 0 }, m_rown(1), m_coln(1) {}

// Конструктор, принимающий размеры матрицы и инициализирующий её элементы нулевым значением.
Matrix::Matrix(size_t rown, size_t coln) : m_coln(coln), m_rown(rown), m_values(coln* rown) {}

// Копирующий конструктор.
Matrix::Matrix(const Matrix& m) : m_coln{ m.m_coln }, m_rown{ m.m_rown }, m_values{ m.m_values } {}

// Деструктор.
Matrix::~Matrix()
{
	m_values.clear();
	m_values.shrink_to_fit();
}

// Количество строк матрицы.
const size_t Matrix::get_rSize() const { return m_rown; }
// Количество столбцов матрицы.
const size_t Matrix::get_cSize() const { return m_coln; }

// Получение элемента матрицы на заданной позиции.
const double Matrix::get_elem(size_t row, size_t col) const
{
	if (row >= m_rown || col >= m_coln)
		throw "Error: matrix index out of bounds";
	return m_values.at(get_index(row, col));
}

// Установка значения элемента матрицы на заданной позиции.
void Matrix::set_elem(size_t row, size_t col, const double value)
{
	if (row >= m_rown || col >= m_coln)
		throw "Error: matrix index out of bounds";

	//this->values.erase(this->values.begin() + this->get_index(row, col));
	//this->values.insert(this->values.begin() + this->get_index(row, col), value);
	m_values.at(get_index(row, col)) = value;
}

/// <summary>
/// Заменяет элементы столбца текущей матрицы на элементы переданного вектора-столбца.
/// </summary>
/// <param name="col"> - номер столбца текущей матрицы, элементы которого надо изменить.</param>
/// <param name="column"> - вектор-столбец, элементы которого заменят элементы столбца текущей матрицы.</param>
void Matrix::set_column(size_t col, const Matrix& column)
{
	if (col >= m_coln)
		throw "Error: matrix index out of bounds";
	if (column.m_rown != m_rown)
		throw "Error: matrixes have different amounts of rows";
	if (column.m_coln != 1)
		throw "Error: matrix must be a column matrix";

	// Вставка переданного столбца на место столбца исходной матрицы.
	m_values.erase(m_values.begin() + col * m_rown, m_values.begin() + (col + 1) * m_rown);
	m_values.insert(m_values.begin() + col * m_rown, column.m_values.begin(), column.m_values.end());
}

// Поиск определителя матрицы методом Гаусса (Gaussian Elimination With Partial Pivoting).
const double Matrix::det() const {
	// Проверки:
	if (get_cSize() != get_rSize()) throw "Error: matrix is not square";
	if (get_cSize() == 0) throw "Error: matrix must be no zero";

	// Если матрица состоит из 1 числа, просто вернуть это число.
	if ((get_cSize() == 1) && (get_rSize() == 1))
		return this->get_elem(0, 0);

	// Иначе используем метод Гаусса, который был взят отсюда: https://codereview.stackexchange.com/questions/204135/determinant-using-gauss-elimination
	Matrix workCopy{ *this };
	size_t num = m_coln;
	double det = 1;

	for (size_t i = 0; i < num; ++i) {

		// Поворотный элемент, информация здесь: https://wikiboard.ru/wiki/Pivot_element
		double pivotElement = workCopy.get_elem(i, i);

		size_t pivotRow = i;
		for (size_t row = i + 1; row < num; ++row) {
			if (std::abs(workCopy/*.get_elem*/(row, i)) > std::abs(pivotElement)) {
				pivotElement = workCopy/*.get_elem*/(row, i);
				pivotRow = row;
			}
		}
		if (pivotElement == 0.0) return 0.0;
		if (pivotRow != i) {
			// Перестановка строк для выполнения исключения.
			rowSwap(workCopy, i, pivotRow);
			det *= -1.0;
		}
		det *= pivotElement;
		for (size_t row = i + 1; row < num; ++row) {
			for (size_t col = i + 1; col < num; ++col) {
				// Исключение.
				workCopy(row, col) -= workCopy/*.get_elem*/(row, i) * workCopy/*.get_elem*/(i, col) / pivotElement;
			}
		}
	}
	return det;
}


// Возвращает бесконечную норму матрицы.
const double Matrix::norm() const
{
	if (m_rown * m_coln == 0)
		throw "Error: matrix is zero";
	// Вектор модулей элементов текущей матрицы.
	std::vector<double> absoluteValues(m_rown * m_coln);
	// Заполнить вектор модулей.
	for (size_t i{}; i != absoluteValues.size(); ++i)
		absoluteValues[i] = std::abs(m_values[i]);
	// Найти наибольшее значение в векторе модулей.
	const auto& maxValue{ std::max_element(absoluteValues.begin(), absoluteValues.end()) };
	// Вернуть наибольшее значение.
	return *maxValue;
}

/// <summary>
/// Присваивает левой матрице копию содержимого правой матрицы.
/// </summary>
/// <param name="Any"> - Правая матрица.</param>
/// <returns>Ссылка на текущий объект.</returns>
Matrix& Matrix::operator=(const Matrix& Any)
{
	// Если указатель на текущий объект this указывает туда же, куда и переданная ссылка на матрицу,
	// вернуть ссылку на текущий объект.
	if (this == &Any)
	{
		return *this;
	}

	// Копирование содержимого правой матрицы.
	m_coln = Any.m_coln;
	m_rown = Any.m_rown;
	m_values = Any.m_values;

	// Вернуть ссылку на текущий объект.
	return *this;
}

// Индексатор для константных объектов Matrix.
const double Matrix::operator()(size_t row, size_t col) const
{
	if (row >= m_rown || col >= m_coln) throw "Error: index out of bounds";
	return m_values.at(get_index(row, col));
}

// Индексатор для обычных объектов Matrix.
double& Matrix::operator()(size_t row, size_t col)
{
	if (row >= m_rown || col >= m_coln) throw "Error: index out of bounds";
	return m_values.at(get_index(row, col));
}



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
	// Количество столбцов левой матрицы должно соответствовать количеству строк правой матрицы.
	if (left.get_cSize() != right.get_rSize()) throw "Error: columns count of left matrix isn't equal to rows count of right matrix";
	if (left.get_cSize() == 0 || left.get_rSize() == 0) throw "Error: matrixes must be no zero";

	// Результирующая матрица: l строк от левой матрицы, n столбцов от правой матрицы.
	Matrix result(left.get_rSize(), right.get_cSize());

	// Вычисление произведения по формуле с википедии.
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
