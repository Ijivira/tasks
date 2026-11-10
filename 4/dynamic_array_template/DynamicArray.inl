/******************************************/
/*				ТЕЛО ШАБЛОНА			  */
/******************************************/

#include <iostream>
#include <limits>
#include <cstdlib>
#include "DynamicArray.h"


// конструкторы
// по умолчанию
template <typename T>
DynamicArray<T>::DynamicArray()
{
	data = nullptr;
	length = 0;
}

// конструктор из обычного массива
template <typename T>
DynamicArray<T>::DynamicArray(const T* const Array, const int ArrayLength)
{
	length = ArrayLength;
	data = new T[length];
	for (int index = 0; index < length; index++)
	{
		data[index] = Array[index];
	}
}
// конструктор копирования
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	length = other.length;
	data = new T[length];
	for (int index = 0; index < length; index++)
	{
		data[index] = other.data[index];
	}
}

// перемещающий конструктор
template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other)
{
	length = other.length;
	data = other.data;
	other.data = nullptr;
}


// деструктор
template <typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] data;
}

// получение размера (количества хранимых элементов в настоящий момент);
template <typename T>
int DynamicArray<T>::get_length() const
{
	return length;
}

// обмен содержимого с другим массивом
template <typename T>
void DynamicArray<T>::swap(DynamicArray& other)
{
	std::swap(length, other.length);

	T* time = data;
	data = other.data;
	other.data = time;
}

// поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
template <typename T>
int DynamicArray<T>::search(const T element) const
{
	int index = 0;
	for (; index < length && data[index] != element; index++);
	if (index == length) {
		return -1;
	}
	else return index;
}

// Вывод на консоль
template <typename T>
void DynamicArray<T>::output() const
{
	if (length == 0)
	{
		std::cout << "empty array" << std::endl;
	}
	else {
		for (int index = 0; index < length; index++)
		{
			std::cout << data[index] << " ";
		}
		std::cout << std::endl;
	}
}

// Ввод с консоли
template <typename T>
DynamicArray<T>& DynamicArray<T>::input()
{
	delete[] data;

	std::cout << "Enter the number of array elements" << std::endl;
	std::cin >> length;
	std::cout << "Enter the array elements" << std::endl;
	data = new T[length];

	for (int index = 0; index < length; index++)
	{
		std::cin >> data[index];
	}

	return *this;
}

// сортировка элементов
template <typename T>
void DynamicArray<T>::sort()
{
	for (int k = length; k > 1; k--) {
		for (int index = 0; index < k - 1; index++)
			if (data[index] > data[index + 1]) std::swap(data[index], data[index + 1]);
	}
}

// вставка элемента по индексу. Если индекс некорректный, вернуть false;
template <typename T>
bool DynamicArray<T>::insert(const T element, const int position)
{
	if (position > length) {
		std::cout << "Erorr. Index outside the array." << std::endl;
		return false;
	}
	else {
		length = length + 1;
		T* New_data = new T[length];
		int index = 0;
		for (; index < position; index++)
		{
			New_data[index] = data[index];
		}

		New_data[index] = element;
		index++;

		for (; index < length; index++)
		{
			New_data[index] = data[index - 1];
		}

		delete[] data;
		data = New_data;
		return true;
	}
}

// Удаление элемента по индексу
template <typename T>
bool DynamicArray<T>::delete_position(const int position)
{
	if (position > length) {
		std::cout << "Erorr. Index outside the array." << std::endl;
		return false;
	}
	else {
		length = length - 1;
		T* New_data = new T[length];
		int index = 0;
		for (; index < position; index++)
		{
			New_data[index] = data[index];
		}

		for (; index < length; index++)
		{
			New_data[index] = data[index + 1];
		}

		delete[] data;
		data = New_data;
		return true;
	}
}

// удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
template <typename T>
bool DynamicArray<T>::delete_element(const T element)
{
	int position = search(element);
	if (position == -1) {
		std::cout << "There is no such element." << std::endl;
		return false;
	}
	else {
		delete_position(position);
		return true;
	}
}

// удаление всех элементов с заданным значением;
template <typename T>
bool DynamicArray<T>::delete_all_element(const T element)
{
	while (length > 0) {
		int position = search(element);
		if (position == -1) {
			return false;
		}
		else {
			delete_position(position);
		}
	}
	return true;
}

// поиск максимального / минимального элемента;
template <typename T>
T DynamicArray<T>::min() const
{
	if (length == 0) return INT_MAX;
	else {
		T min = data[0];

		for (int index = 0; index < length; index++)
			if (data[index] < min) {
				min = data[index];
			};

		return min;
	}
}

template <typename T>
T DynamicArray<T>::max() const
{
	if (length == 0) return INT_MIN;
	else {
		T max = data[0];

		for (int index = 0; index < length; index++)
			if (data[index] > max) {
				max = data[index];
			}

		return max;
	}
}

// Перегрузки операторов
//получение ссылки на элемент по индексу ([ ]);
template <typename T>
T& DynamicArray<T>::operator [](int index) const
{
	try {
		if (length < index)
			throw std::out_of_range("the index exceeded the length of the array");
	}
	catch (std::out_of_range s) {
		std::cout << s.what() << std::endl;
		std::exit(-1);
	}
	return data[index];
}

#if 0
//присваивание копированием (=);
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator =(const DynamicArray& other)
{
	if (this != &other)
	{
		delete[] data;
		length = other.length;
		data = new T[length];
		for (int index = 0; index < length; index++)
		{
			data[index] = other.data[index];
		}
	}
	return *this;
}
#endif

//присваивание копированием (=);
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator =(const DynamicArray& other)
{
	if (this != &other)
	{
		DynamicArray copy(other);
		swap(copy);
	}
	return *this;
}

// присваивание перемещением(= (DynamicArray && other))
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator =(DynamicArray&& other)
{
	if (this != &other)
	{
		delete[] data;
		length = other.length;
		data = other.data;
		other.data = nullptr;
	}
	return *this;
}

//добавление элемента в конец массива (+ и +=);
template <typename T>
DynamicArray<T> DynamicArray<T>::operator +(const T element) const
{
	DynamicArray NewArray;

	NewArray.length = length + 1;

	NewArray.data = new T[NewArray.length];

	int index = 0;
	for (; index < NewArray.length - 1; index++)
	{
		NewArray.data[index] = data[index];
	}
	NewArray.data[index] = element;
	return NewArray;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator +=(const T element)
{
	T* New_data = new T[length + 1];

	int index = 0;
	for (; index < length; index++)
	{
		New_data[index] = data[index];
	}
	New_data[index] = element;

	length = length + 1;
	delete[] data;

	data = New_data;

	return *this;
}

// сложение(конкатенация) с другим массивом (+ и += );
template <typename T>
DynamicArray<T> DynamicArray<T>::operator +(const DynamicArray& other) const
{
	DynamicArray NewArray;

	NewArray.length = length + other.length;

	NewArray.data = new T[NewArray.length];

	int index = 0;
	for (; index < length; index++)
	{
		NewArray.data[index] = data[index];
	}

	for (; index < NewArray.length; index++)
	{
		NewArray.data[index] = other.data[index - length];
	}

	return NewArray;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator +=(const DynamicArray& other)
{
	T* New_data = new T[length + other.length];

	int index = 0;
	for (; index < length; index++)
	{
		New_data[index] = data[index];
	}

	for (; index < length + other.length; index++)
	{
		New_data[index] = other.data[index - length];
	}

	length += other.length;
	delete[] data;

	data = New_data;

	return *this;
}

// сравнение(== и != )
template <typename T>
bool DynamicArray<T>::operator ==(const DynamicArray<T>& other) const
{
	if (this == &other)
	{
		return true;
	}
	else if (length != other.length)
	{
		return false;
	}
	else {
		int index = 0;
		for (; (index < length) && (data[index] == other.data[index]); index++);
		if (index == length)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

template <typename T>
bool DynamicArray<T>::operator !=(const DynamicArray& other) const
{
	return !(*this == other);
}

// ИТЕРАТОРЫ
template <typename T>
DynamicArray<T>::iterator::iterator()
{
	data = nullptr;
	index = 0;
}
template <typename T>
DynamicArray<T>::iterator::iterator(T* data, int index) : data(data), index(index) {}

template <typename T>
bool DynamicArray<T>::iterator::operator == (const DynamicArray::iterator otherIterator)
{
	if (data == otherIterator.data && index == otherIterator.index)
		return 1;
	else
		return 0;
}

template <typename T>
bool DynamicArray<T>::iterator::operator != (const DynamicArray::iterator otherIterator)
{
	return !(*this == otherIterator);
}

template <typename T>
bool DynamicArray<T>::iterator::operator > (const DynamicArray::iterator otherIterator)
{
	if (data == otherIterator.data && index > otherIterator.index)
		return 1;
	else
		return 0;
}

template <typename T>
bool DynamicArray<T>::iterator::operator < (const DynamicArray::iterator otherIterator)
{
	if (data == otherIterator.data && index < otherIterator.index)
		return 1;
	else
		return 0;
}

template <typename T>
int DynamicArray<T>::iterator::operator - (const DynamicArray::iterator otherIterator)
{
	return index - otherIterator.index;
}

template <typename T>
DynamicArray<T>::iterator& DynamicArray<T>::iterator::operator + (const int n)
{
	index = index + n;
	return *this;
}

template <typename T>
DynamicArray<T>::iterator& DynamicArray<T>::iterator::operator - (const int n)
{
	index = index - n;
	return *this;
}

template <typename T>
DynamicArray<T>::iterator& DynamicArray<T>::iterator::operator ++ ()
{
	++index;
	return *this;
}

template <typename T>
DynamicArray<T>::iterator DynamicArray<T>::iterator::operator ++ (int)
{
	DynamicArray::iterator copy(*this);
	++index;
	return copy;
}

template <typename T>
T& DynamicArray<T>::iterator::operator *() const
{
	return *(data + index);
}

// получение итераторов на начало / конец массива
template <typename T>
DynamicArray<T>::iterator DynamicArray<T>::begin() const
{
	return iterator(data, 0);
}

template <typename T>
DynamicArray<T>::iterator DynamicArray<T>::end() const
{
	return iterator(data, length);
}

// вставка элемента перед итератором
template <typename T>
bool DynamicArray<T>::insert(const T element, DynamicArray<T>::iterator it)
{
	if (it < begin() || it > end())
		return false;
	else {
		length = length + 1;
		T* New_data = new T[length];

		DynamicArray::iterator indx;

		for (indx = begin(); indx != it; ++indx)
		{
			New_data[indx - begin()] = *indx;
		}

		New_data[indx - begin()] = element;

		for (; indx != end(); ++indx)
		{
			New_data[indx - begin() + 1] = *indx;
		}

		data = New_data;

		return true;
	}
}

//удаление элемента или диапазона элементов с помощью итераторов
template <typename T>
bool DynamicArray<T>::delete_element(DynamicArray::iterator it)
{
	if (it < begin() || it > end())
		return false;
	else {
		T* New_data = new T[length - 1];

		DynamicArray::iterator indx = begin();

		for (; indx != it; ++indx)
		{
			New_data[indx - begin()] = *indx;
		}

		for (indx = it; indx != end(); ++indx)
		{
			New_data[indx - begin() - 1] = *indx;
		}

		data = New_data;
		length = length - 1;

		return true;
	}
}

template <typename T>
bool DynamicArray<T>::delete_element(DynamicArray::iterator it_begin, DynamicArray::iterator it_end)
{
	if (it_begin < begin() || it_end > end())
		return false;
	else {
		T* New_data = new T[length - (it_end - it_begin) - 1];

		DynamicArray::iterator indx;

		for (indx = begin(); indx != it_begin; ++indx)
		{
			New_data[indx - begin()] = *indx;
		}

		indx = indx + (it_end - it_begin) + 1;

		for (; indx != end(); ++indx)
		{
			New_data[indx - begin() - (it_end - it_begin) - 1] = *indx;
		}

		data = New_data;
		length = length - (it_end - it_begin) - 1;

		return true;
	}
}

template <typename T>
std::ostream& operator << (std::ostream& outputStream, const DynamicArray<T>& Array)
{
	int array_length = Array.get_length();

	outputStream << "[";

	for (int index = 0; index < array_length; index++)
	{
		outputStream << Array[index];

		if (index < array_length - 1) outputStream << ", ";
	}

	outputStream << "]";

	return outputStream;
}

template <typename T>
std::istream& operator >> (std::istream& inputStream, DynamicArray<T>& Array)
{
	int element;
	inputStream >> element;

	Array += element;

	return inputStream;
}