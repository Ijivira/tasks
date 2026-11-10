#include <iostream>
#include "BooleanVector.h"


// конструктор по умолчанию, 
BooleanVector::BooleanVector()
{
	length = 0;
    size = 0;
    data = nullptr;
}

// конструктор с параметрами (размер и значение - одно и то же для всех разрядов),
BooleanVector::BooleanVector(const uint32_t vectorLength, const bool initialValue)
{
	 length = vectorLength;
     if (length == 0)
     {
         size = 0;
         data = nullptr;
         return;
     }

     size = (length + 7) / 8;

     data = new uint8_t[size];

     for (uint32_t byteIndex = 0; byteIndex < size; byteIndex++)
     {
         data[byteIndex] = initialValue ? 0xFF : 0;
     }
}
/*// конструктор из массива const char *, 
BooleanVector::BooleanVector(const char* str)
{

}

// конструктор копирования;
BooleanVector(const BooleanVector& other);
*/

// деструктор
BooleanVector::~BooleanVector()
{
    delete[] data;
}

// длина(количество бит) вектора;
uint32_t BooleanVector::get_length() const
{
    return length;
}

// обмен содержимого с другим вектором(swap);
// ввод / вывод в консоль(потоковый);
// потоковый вывод в консоль;
std::ostream& operator<<(std::ostream& outputStream, const BooleanVector& booleanVector)
{
    uint32_t length = booleanVector.get_length();

    for (uint32_t bitIndex = 0; bitIndex < length; bitIndex++)
    {
        outputStream << (booleanVector[bitIndex] ? "1" : "0");
    }

    return outputStream;
}
// инверсия всех компонент вектора;
// инверсия i - ой компоненты;
// установка в 0 / 1 i - ой компоненты;
// установка в 0 / 1 k компонент, начиная с i - ой;
// установка в 0 / 1 всех компонент вектора;
// вес вектора(количество единичных компонент).

// получение компоненты [];
bool BooleanVector::operator [](const uint32_t bitIndex) const
{
    // TODO: Сделать проверку на выход за границы вектора
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return data[byteIndex] & (1 << bitWithinByte);
}

BooleanVector::BitReference BooleanVector::operator [](const uint32_t bitIndex)
{
    // TODO: Сделать проверку на выход за границы вектора
    uint32_t byteIndex = bitIndex / 8;
    uint32_t bitWithinByte = bitIndex % 8;

    return BitReference(&data[byteIndex], bitWithinByte);
}
// побитовое умножение(&, &=);
// побитовое сложение(| , |=);
// побитовое исключающее ИЛИ(^, ^=);
// побитовые сдвиги(<< , >> , <<=, >>=);
// побитовая инверсия(~);
// присваивание(= ).


BooleanVector::BitReference::BitReference(uint8_t* Byte_Pointer, uint32_t Bit_Index) 
    : bytePtr(Byte_Pointer), bitIndex(Bit_Index) {}

BooleanVector::BitReference::operator bool()
{
    return *bytePtr & (1 << bitIndex);
}

void BooleanVector::BitReference::operator=(const bool newValue)
{
    if (newValue)
        *bytePtr |= (1 << bitIndex);
    else
        *bytePtr &= ~(1 << bitIndex);
}