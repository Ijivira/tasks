#include <iostream>
#include "BooleanVector.h"


// конструктор по умолчанию, 
BooleanVector::BooleanVector()
{
    
    numBits_ = 0;
    numBytes_ = 0;
    vectorData_ = nullptr;
}

// конструктор с параметрами (размер и значение - одно и то же для всех разрядов),
BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
{
    numBits_ = numBits;
    if (numBits == 0)
     {
        numBytes_ = 0;
        vectorData_ = nullptr;
        return;
     }

    numBytes_ = (numBits + 7) / 8;
    vectorData_ = new uint8_t[numBytes_];

    for (uint32_t byteIndex = 0; byteIndex < numBytes_; byteIndex++)
    {
        vectorData_[byteIndex] = initialValue ? 0xFF : 0;
    }
}
// конструктор из массива const char *, 
BooleanVector::BooleanVector(const char* str)
{
    numBits_ = strlen(str);
    numBytes_ = (numBits_ + 7) / 8;
    vectorData_ = new uint8_t[numBytes_];

    uint32_t byteIndex;
    uint32_t bitWithinByte;

    for (uint32_t bitIndex = 0; bitIndex < numBits_; bitIndex++)
    {
        byteIndex = bitIndex / 8;
        bitWithinByte = bitIndex % 8;
        if (str[bitIndex]=='1')
        {
            vectorData_[byteIndex] |= (1 << bitWithinByte);
        }
        else if (str[bitIndex] == '0')
        {
            vectorData_[byteIndex] &= ~(1 << bitIndex);
        }
    }
}

// конструктор копирования;
BooleanVector::BooleanVector(const BooleanVector& other)
{
    numBits_ = other.numBits_;
    numBytes_ = other.numBytes_;

    vectorData_ = new uint8_t[numBytes_];

    for (uint32_t byteIndex = 0; byteIndex < numBytes_; byteIndex++)
    {
        vectorData_[byteIndex] = other.vectorData_[byteIndex];
    }
}
// перемещающий конструктор
BooleanVector::BooleanVector(BooleanVector&& other)
{
    numBits_ = other.numBits_;
    numBytes_ = other.numBytes_;
    vectorData_ = other.vectorData_;
    other.vectorData_ = nullptr;
}

// деструктор
BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
}

// длина(количество бит) вектора;
uint32_t BooleanVector::getBitsCount() const
{
    return numBits_;
}

// обмен содержимого с другим вектором(swap);
void BooleanVector::swap(BooleanVector& other)
{
    uint8_t* vectorData_temp = vectorData_;
    uint32_t numBits_temp = numBits_;
    uint32_t numBytes_temp = numBytes_;

    vectorData_ = other.vectorData_;
    numBits_ = other.numBits_;
    numBytes_ = other.numBytes_;

    other.vectorData_= vectorData_temp;
    other.numBits_= numBits_temp;
    other.numBytes_= numBytes_temp;
}

// ввод / вывод в консоль(потоковый);
// потоковый вывод в консоль;
std::ostream& operator<<(std::ostream& outputStream, BooleanVector& booleanVector)
{
    uint32_t length = booleanVector.getBitsCount();

    for (uint32_t bitIndex = 0; bitIndex < length; bitIndex++)
    {
        outputStream << (booleanVector[bitIndex] ? "1" : "0");
    }

    return outputStream;
}
std::istream& operator>>(std::istream& inputStream, BooleanVector& booleanVector)
{
    std::cout << "vector size?" << std::endl;
    uint32_t numBits;
    std::cin >> numBits;

    booleanVector = BooleanVector(numBits, false);

    std::cout << "Enter the values." << std::endl;

    for (uint32_t bitIndex = 0; bitIndex < numBits; bitIndex++)
    {
        uint8_t bitValue;
        std::cin >> bitValue;
        if (bitValue == '0')
        {
            booleanVector.setValue(bitIndex, false);
        }
        else if (bitValue == '1')
        {
            booleanVector.setValue(bitIndex, true);
        }
        else{
            std::cout << "Values should be only 0 or 1. Try again." << std::endl;
            std::cin >> booleanVector;
            return inputStream;
        }
    }

    return inputStream;
}

// инверсия всех компонент вектора;
void BooleanVector::complete_inversion()
{
    BitReference Ref = begin();

    for (int i = 0; i < numBits_; ++Ref, ++i)
    {
        Ref = !(bool)Ref;
    }
}

// инверсия i - ой компоненты;
void BooleanVector::inversion(const uint32_t bitIndex)
{
    if (bitIndex < numBits_ && bitIndex >= 0)
    {
        BitReference Ref = begin() + bitIndex;
        Ref = !(bool)Ref;
    }
    else
    {
        std::cout << "Error. Vector length = " << bitIndex << std::endl;
    }
}

// установка в 0 / 1 i - ой компоненты;
void BooleanVector::setValue(const uint32_t bitIndex, const bool newValue)
{
    if (bitIndex < numBits_ && bitIndex >= 0)
    {
        uint32_t byteIndex = bitIndex / 8;
        uint32_t bitWithinByte = bitIndex % 8;

        if (newValue)
            vectorData_[byteIndex] |= (1 << bitWithinByte);
        else
            vectorData_[byteIndex] &= ~(1 << bitWithinByte);
    }
    else
    {
        std::cout << "Error. Vector length = " << bitIndex << std::endl;
    }
}

// установка в 0 / 1 k компонент, начиная с i - ой;
void BooleanVector::setValuePart(const uint32_t bitIndex, const uint32_t length, const bool newValue)
{
    if (bitIndex < numBits_ && bitIndex+length <= numBits_  && bitIndex >= 0 )
    {
        BitReference Ref = begin() + bitIndex;
        for (int i = 0; i < length; ++Ref, ++i)
        {
            Ref = newValue;
        }
    }
    else
    {
        std::cout << "Error. You have gone beyond the vector limits." << std::endl;
    }
}

// установка в 0 / 1 всех компонент вектора;
void BooleanVector::setValueAll(const bool newValue)
{
    BitReference Ref = begin();
    for (int i = 0; i < numBits_; ++Ref, ++i)
    {
        Ref = newValue;
    }
}

// вес вектора(количество единичных компонент)
uint32_t BooleanVector::weight()
{
    uint32_t Sum = 0;
    BitReference Ref = begin();
    for (int i = 0; i < numBits_; ++Ref, ++i)
    {
        Sum += Ref;
    }
    return Sum;
}


// получение компоненты [];
bool BooleanVector::operator[](const uint32_t bitIndex) const
{
    if (bitIndex < numBits_ && bitIndex >= 0)
    { 
        uint32_t byteIndex = bitIndex / 8;
        uint32_t bitWithinByte = bitIndex % 8;

        return vectorData_[byteIndex] & (1 << bitWithinByte);
    }
    else
    {
        std::cout << "Error. Vector length = " << bitIndex << std::endl;
        return false;
    }
}

BooleanVector::BitReference BooleanVector::operator[](const uint32_t bitIndex)
{
    if (bitIndex < numBits_ && bitIndex >= 0)
    {
        uint32_t byteIndex = bitIndex / 8;
        uint32_t bitWithinByte = bitIndex % 8;

        return BitReference(&vectorData_[byteIndex], bitWithinByte);
    }
    else
    {
        std::cout << "Error. Vector length = " << bitIndex << std::endl;
    }
}

// побитовое умножение(&, &=);
BooleanVector BooleanVector::operator &(const BooleanVector& other) const
{
    BooleanVector New(*this);
    New &= other;
    return New;
}
BooleanVector& BooleanVector::operator &=(const BooleanVector& other)
{
    if (numBits_ == other.numBits_)
    {
        BitReference Ref = begin();
        BitReference other_Ref = other.begin();

        for (int i = 0; i < numBits_; ++Ref, ++other_Ref, ++i)
        {
            Ref = (bool)Ref & (bool)other_Ref;
        }
    }
    else std::cout << "Error. Vectors of different lengths!" << std::endl;
    return *this;
}

// побитовое сложение(| , |=);
BooleanVector BooleanVector::operator |(const BooleanVector& other) const
{
    BooleanVector New(*this);
    New |= other;
    return New;
}
BooleanVector& BooleanVector::operator |=(const BooleanVector& other)
{
    if (numBits_ == other.numBits_)
    {
        BitReference Ref = begin();
        BitReference other_Ref = other.begin();

        for (int i = 0; i < numBits_; ++Ref, ++other_Ref, ++i)
        {
            Ref = (bool)Ref | (bool)other_Ref;
        }
    }
    else std::cout << "Error. Vectors of different lengths!" << std::endl;
    return *this;
}

// побитовое исключающее ИЛИ(^, ^=);
BooleanVector BooleanVector::operator ^(const BooleanVector& other) const
{
    BooleanVector New(*this);
    New ^= other;
    return New;
}
BooleanVector& BooleanVector::operator ^=(const BooleanVector& other)
{
    if (numBits_ == other.numBits_)
    {
        BitReference Ref = begin();
        BitReference other_Ref = other.begin();

        for (int i = 0; i < numBits_; ++Ref, ++other_Ref, ++i)
        {
            Ref = (bool)Ref ^ (bool)other_Ref;
        }
    }
    else std::cout << "Error. Vectors of different lengths!" << std::endl;
    return *this;
}

// побитовые сдвиги(<< , >> , <<=, >>=);
BooleanVector BooleanVector::operator << (const uint32_t bitIndex)
{
    BooleanVector New;
    New = *this;
    New <<= bitIndex;

    return New;
}

BooleanVector& BooleanVector::operator <<= (const uint32_t bitIndex)
{
    BitReference Ref = begin();

    int i = 0;
    for (; i < numBits_- bitIndex; ++i, ++Ref)
    {
        Ref = (bool) (Ref + bitIndex);
    }
    for (;i < numBits_; ++i, ++Ref)
    {
        Ref = false;
    }

    return *this;
}

BooleanVector BooleanVector::operator >> (const uint32_t bitIndex)
{
    BooleanVector New(*this);
    New >>= bitIndex;

    return New;
}

BooleanVector& BooleanVector::operator >>= (const uint32_t bitIndex)
{
    BitReference Ref = end();
    int i = numBits_-1;

    for (; i >= bitIndex;  --Ref, --i)
    {
        Ref = (bool)(Ref - bitIndex);
    }
    for (; i >= 0; --i, --Ref)
    {
        Ref = false;
    }

    return *this;
}

// побитовая инверсия(~);
BooleanVector BooleanVector::operator ~ ()
{
    BooleanVector New(*this);
    BitReference New_Ref = New.begin();

    for (int i = 0; i < New.numBits_; ++New_Ref, ++i) 
    {
        New_Ref = !(bool)New_Ref;
    }
    return New;
}

// присваивание(=).
BooleanVector& BooleanVector::operator = (const BooleanVector& other)
{
    if (this != &other)
    {
        delete[] vectorData_;
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;
        vectorData_ = new uint8_t[numBytes_];

        for (uint32_t byteIndex = 0; byteIndex < numBytes_; byteIndex++)
        {
            vectorData_[byteIndex] = other.vectorData_[byteIndex];
        }
    }
    return *this;
}
BooleanVector& BooleanVector::operator = (const char* str)
{
    numBits_ = strlen(str);
    numBytes_ = (numBits_ + 7) / 8;
    delete[] vectorData_;
    vectorData_ = new uint8_t[numBytes_];

    uint32_t byteIndex;
    uint32_t bitWithinByte;

    for (uint32_t bitIndex = 0; bitIndex < numBits_; bitIndex++)
    {
        byteIndex = bitIndex / 8;
        bitWithinByte = bitIndex % 8;
        if (str[bitIndex] == '1')
        {
            vectorData_[byteIndex] |= (1 << bitWithinByte);
        }
        else if (str[bitIndex] == '0')
        {
            vectorData_[byteIndex] &= ~(1 << bitIndex);
        }
    }
    return *this;
}

// присваивание перемещением
BooleanVector& BooleanVector::operator =(BooleanVector&& other)
{
    if (this != &other)
    {
        delete[] vectorData_;
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;
        vectorData_ = other.vectorData_;
        other.vectorData_ = nullptr;
    }
    return *this;
}