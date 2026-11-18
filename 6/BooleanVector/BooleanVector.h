#pragma once
#include <stdint.h>
#include <iostream>

class BooleanVector
{
public:

    class BitReference;

    // конструктор по умолчанию, 
    BooleanVector();
    // конструктор с параметрами (размер и значение - одно и то же для всех разрядов),
    BooleanVector(const uint32_t vectorLength, const bool initialValue);
    // конструктор из массива const char *, 
    BooleanVector(const char* str);
    // конструктор копирования;
    BooleanVector(const BooleanVector& other);
    // перемещающий конструктор
    BooleanVector(BooleanVector&& other);
    
    // деструктор;
    ~BooleanVector();

    // длина(количество бит) вектора;
    uint32_t getBitsCount() const;

    // обмен содержимого с другим вектором(swap);
    void swap(BooleanVector& other);

    // инверсия всех компонент вектора;
    void complete_inversion();
    // инверсия i - ой компоненты;
    void inversion(const uint32_t bitIndex);

    // установка в 0 / 1 i - ой компоненты;
    void setValue(const uint32_t bitIndex, const bool newValue);
    // установка в 0 / 1 k компонент, начиная с i - ой;
    void setValuePart(const uint32_t bitIndex, const uint32_t length, const bool newValue);
    // установка в 0 / 1 всех компонент вектора;
    void setValueAll(const bool newValue);

    // вес вектора(количество единичных компонент)
    uint32_t weight();

    // получение компоненты[]
    bool operator[](const uint32_t bitIndex) const;
    BitReference operator[](const uint32_t bitIndex);

    // перегрузка +
    BooleanVector operator + (const int Bit);

    // побитовое умножение(&, &=);
    BooleanVector& operator &=(const BooleanVector& other);
    BooleanVector operator &(const BooleanVector& other) const;
    // побитовое сложение(| , |=);
    BooleanVector& operator |=(const BooleanVector& other);
    BooleanVector operator |(const BooleanVector& other) const;
    // побитовое исключающее ИЛИ(^, ^=);
    BooleanVector& operator ^=(const BooleanVector& other);
    BooleanVector operator ^(const BooleanVector& other) const;
    // побитовые сдвиги(<< , >> , <<=, >>=);*/
    BooleanVector operator << (const uint32_t bitIndex);
    BooleanVector& operator <<= (const uint32_t bitIndex);
    BooleanVector operator >> (const uint32_t bitIndex);
    BooleanVector& operator >>= (const uint32_t bitIndex);
    // побитовая инверсия(~);
    BooleanVector operator ~ ();

    // присваивание(= ).
    BooleanVector& operator =(const BooleanVector& other);
    BooleanVector& operator = (const char* str);
    // присваивание перемещением(= (DynamicArray && other))
    BooleanVector& operator =(BooleanVector&& other);

    BitReference begin() const;
    BitReference end() const;

private:
    uint8_t* vectorData_;
    uint32_t numBits_;
    uint32_t numBytes_;
};


class BooleanVector::BitReference
{
public:
    BitReference();
    BitReference(uint8_t* Byte_Pointer, uint32_t Bit_Index);

    operator bool();
    void operator = (const bool newValue);
    BitReference& operator = (const BitReference& other);
    BitReference operator + (const uint32_t Bits);
    BitReference operator - (const uint32_t Bits);
    BitReference& operator ++ ();
    BitReference& operator -- ();
    

private:
    uint8_t* bytePtr;
    uint32_t bitIndex;
};

std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector);
std::ostream& operator<<(std::ostream& outputStream, BooleanVector& booleanVector);