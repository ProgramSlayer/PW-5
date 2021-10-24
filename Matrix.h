#pragma once
//Пользовательский тип(класс);
//Определены методы :
//	уметь извлекать элементы матрицы;
//	уметь определять размер матицы
//	операция вычисления определителя det();
//	метод замены столбца;
//	вычислять норму;
//	вычислять разность;
//	вычислять произведение;
//	копировать матрицы.

#include <iostream>
#include <vector>
//#include <utility>

class Matrix
{
private:
	/// <summary>
	/// Возвращает линейный индекс элемента матрицы на заданной позиции.
	/// </summary>
	/// <param name="row"> - строка элемента.</param>
	/// <param name="col"> - столбец элемента.</param>
	size_t get_index(size_t row, size_t col) const;	// Почему разумно сделать этот гетер приватным?

	std::vector <double> m_values;	// Вектор значений (матрица хранится как последовательность столбцов).
	size_t m_rown;					// Количество строк.
	size_t m_coln;					// Количество столбцов.

public:

	Matrix();
	Matrix(size_t rown, size_t coln); // Инициализирует матрицу заданных размеров (заполнена нулями).
	Matrix(const Matrix& m);
	//Matrix(Matrix&& m) noexcept : m_coln{ m.m_coln }, m_rown{ m.m_rown }, m_values{ std::move_if_noexcept(m.m_values) }{}

	~Matrix();

	// Возвращает количество строк матрицы.
	const size_t get_rSize() const;
	// Возвращает количество столбцов матрицы.
	const size_t get_cSize() const;
	// Возвращает значение элемента матрицы на заданной позиции.
	const double get_elem(size_t row, size_t col) const;
	// Устанавливает значение элемента матрицы на заданной позиции.
	void set_elem(size_t row, size_t col, const double value);

	/// <summary>
	/// Заменяет элементы столбца текущей матрицы на элементы переданного вектора-столбца.
	/// </summary>
	/// <param name="col"> - номер столбца текущей матрицы, элементы которого надо изменить.</param>
	/// <param name="column"> - вектор-столбец, элементы которого заменят элементы столбца текущей матрицы.</param>
	void set_column(size_t col, const Matrix& column); // должен изменять текущий объект

	const double det() const;	// Поиск определителя.
	const double norm() const;	// Поиск бесконечной нормы матрицы.

	Matrix& operator=(const Matrix& Any);	// Оператор присваивания копированием.

	// Индексатор для константных объектов Matrix (только получение значения элемента).
	const double operator()(size_t row, size_t col) const;
	// Индексатор для обычных объектов Matrix (получение/установка значения).
	double& operator()(size_t row, size_t col);
};

Matrix operator+(const Matrix& left, const Matrix& right);	// Исключение из тела класса, защищает данные от изменения.
Matrix operator-(const Matrix& left, const Matrix& right);	// Для операторов +,-,/, если есть возможность, лучше использовать
Matrix operator*(const Matrix& left, const Matrix& right);	// перегрузку через функции, как в данном примере.