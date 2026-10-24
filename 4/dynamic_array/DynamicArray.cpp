#include <iostream>
#include "DynamicArray.h"

// конструкторы
// по умолчанию
DynamicArray::DynamicArray()
{
	data = nullptr;
	length = 0;
}
// конструктор из обычного массива
DynamicArray::DynamicArray(const int* const Array, const int ArrayLength)
{
	length = ArrayLength;
	data = new int[length];
	for (int index = 0; index < length; index++)
	{
		data[index] = Array[index];
	}
}
// конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& other)
{
	length = other.length;
	data = new int[length];
	for (int index = 0; index < length; index++)
	{
		data[index] = other.data[index];
	}
}

// перемещающий конструктор
DynamicArray::DynamicArray(DynamicArray&& other)
{
	length = other.length;
	data = other.data;
	other.data = nullptr;
}

 
// деструктор
DynamicArray::~DynamicArray()
{
	delete[] data;
}

// получение размера (количества хранимых элементов в настоящий момент);
int DynamicArray::get_length() const
{
	return length;
}

// обмен содержимого с другим массивом
void DynamicArray::swap(DynamicArray& other)
{
	std::swap(length, other.length);

	int* time = data;
	data = other.data;
	other.data = time;
}

// поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
int DynamicArray::search(const int element) const
{
	int index = 0;
	for (; index < length && data[index] != element; index++);
	if (index == length) {
		return -1;
	}
	else return index;
}

// Вывод на консоль
void DynamicArray::output() const
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
DynamicArray& DynamicArray::input()
{
	delete[] data;

	std::cout << "Enter the number of array elements" << std::endl;
	std::cin >> length;
	std::cout << "Enter the array elements" << std::endl;
	data = new int[length];

	for (int index = 0; index < length; index++)
	{
		std::cin >> data[index];
	}

	return *this;
}

// сортировка элементов
DynamicArray& DynamicArray::sort()
{
	
	for (int k = length; k > 1; k--) {
		for (int index = 0; index < k - 1; index++)
			if (data[index] > data[index + 1]) std::swap(data[index], data[index + 1]);
	}

	return *this;
}

// вставка элемента по индексу. Если индекс некорректный, вернуть false;
DynamicArray& DynamicArray::insert(const int element, const int position)
{
	if (position > length) {
		std::cout << "Erorr. Index outside the array." << std::endl;
	}
	else {
		length = length + 1;
		int* New_data = new int[length];
		int index = 0;
		for (; index < position; index++)
		{
			New_data[index] = data[index];
		}

		New_data[index] = element;
		index++;

		for (; index < length; index++)
		{
			New_data[index] = data[index-1];
		}

		delete[] data;
		data = New_data;
	}
	return *this;
}

// Удаление элемента по индексу
DynamicArray& DynamicArray::delete_position(const int position)
{
	if (position > length) {
		std::cout << "Erorr. Index outside the array." << std::endl;
	}
	else {
		length = length - 1;
		int* New_data = new int[length];
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
	}
	return *this;
}

// удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
DynamicArray& DynamicArray::delete_element(const int element)
{
	int position = search(element);
	if (position == -1) {
		std::cout << "There is no such element." << std::endl;
	}
	else {
		delete_position(position);
	}
	return *this;
}

// удаление всех элементов с заданным значением;
DynamicArray& DynamicArray::delete_all_element(const int element)
{
	while (length > 0){
		int position = search(element);
		if (position == -1) {
			return *this;
		}
		else {
			delete_position(position);
		}
	}
	return *this;
}

// поиск максимального / минимального элемента;
int DynamicArray::min() const
{
	int min = data[0];

	for (int index = 0; index < length; index++)
		if (data[index] < min) {
			min = data[index];
		};

	return min;
}

int DynamicArray::max() const
{
	int max = data[0];

	for (int index = 0; index < length; index++)
		if (data[index] > max) {
			max = data[index];
		}

	return max;
}

// Перегрузки операторов
//получение ссылки на элемент по индексу ([ ]);
int& DynamicArray::operator [](int index) const
{
	return data[index];
}

#if 0
//присваивание копированием (=);
DynamicArray& DynamicArray::operator =(const DynamicArray& other)
{
	if (this != &other)
	{
		delete[] data;
		length = other.length;
		data = new int[length];
		for (int index = 0; index < length; index++)
		{
			data[index] = other.data[index];
		}
	}
	return *this;
}
#endif

//присваивание копированием (=);
DynamicArray& DynamicArray::operator =(const DynamicArray& other)
{
	if (this != &other)
	{
		DynamicArray copy(other);
		swap(copy);
	}
	return *this;
}

// присваивание перемещением(= (DynamicArray && other))
DynamicArray& DynamicArray::operator =(DynamicArray&& other)
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
DynamicArray DynamicArray::operator +(const int element) const
{
	DynamicArray NewArray;
	
	NewArray.length = length + 1;

	NewArray.data = new int[NewArray.length];

	int index = 0;
		for (; index < NewArray.length-1; index++)
		{
			NewArray.data[index] = data[index];
		}
	NewArray.data[index] = element;
	return NewArray;
}

DynamicArray& DynamicArray::operator +=(const int element)
{
	int *New_data = new int[length+1];
	
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
DynamicArray DynamicArray::operator +(const DynamicArray& other) const
{
	DynamicArray NewArray;

	NewArray.length = length + other.length;

	NewArray.data = new int[NewArray.length];

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

DynamicArray& DynamicArray::operator +=(const DynamicArray& other)
{
	int* New_data = new int[length + other.length];

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
bool DynamicArray::operator ==(const DynamicArray& other) const
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

bool DynamicArray::operator !=(const DynamicArray& other) const
{
	return !(*this == other);
}

// ИТЕРАТОРЫ

DynamicArray::iterator::iterator() 
{
	data = nullptr;
	index = 0;
}
DynamicArray::iterator::iterator(int* data, int index): data(data), index(index){}

bool DynamicArray::iterator::operator == (const DynamicArray::iterator otherIterator)
{
	if (data == otherIterator.data && index == otherIterator.index)
		return 1;
	else 
		return 0;
}

bool DynamicArray::iterator::operator != (const DynamicArray::iterator otherIterator)
{
	return !(*this == otherIterator);
}

int DynamicArray::iterator::operator - (const DynamicArray::iterator otherIterator)
{
	return index - otherIterator.index;
}

DynamicArray::iterator& DynamicArray::iterator::operator + (const int n)
{
	index = index + n;
	return *this;
}

DynamicArray::iterator& DynamicArray::iterator::operator - (const int n)
{
	index = index - n;
	return *this;
}

DynamicArray::iterator& DynamicArray::iterator::operator ++ ()
{
	++index;
	return *this;
}

DynamicArray::iterator DynamicArray::iterator::operator ++ (int)
{
	DynamicArray::iterator copy(*this);
	++index;
	return copy;
}

int& DynamicArray::iterator::operator *() const
{
	return *(data + index);
}

// получение итераторов на начало / конец массива
DynamicArray::iterator DynamicArray::begin() const
{
	return iterator(data, 0);
}

DynamicArray::iterator DynamicArray::end() const
{
	return iterator(data, length);
}

// вставка элемента перед итератором
DynamicArray& DynamicArray::insert(const int element, DynamicArray::iterator it)
{
	length = length + 1;
	int* New_data = new int[length];

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

	return *this;
}

//удаление элемента или диапазона элементов с помощью итераторов
DynamicArray& DynamicArray::delete_element (DynamicArray::iterator it)
{
	
	int* New_data = new int[length-1];

	DynamicArray::iterator indx= begin();

	for (; indx != it; ++indx)
	{
		New_data[indx - begin()] = *indx;
	}

	for (indx = it; indx != end(); ++indx)
	{
		New_data[indx  - begin() - 1] = *indx;
	}

	data = New_data;
	length = length - 1;

	return *this;
}

DynamicArray& DynamicArray::delete_element(DynamicArray::iterator it_begin, DynamicArray::iterator it_end)
{
	int* New_data = new int[length - (it_end - it_begin) - 1];

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

	return *this;
}