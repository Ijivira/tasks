#pragma once
#include <stdint.h>
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
    
    // деструктор;
    ~BooleanVector();

    // длина(количество бит) вектора;
    uint32_t get_length() const;

    // получение компоненты[]
    bool operator[](const uint32_t bitIndex);

private:
    uint8_t* data;
    uint32_t length; //bits
    uint32_t size; // bytes
};


class BooleanVector::BitReference
{
public:

    BitReference(uint8_t* Byte_Pointer, uint32_t Bit_Index);

    operator bool();
    void operator = (const bool newValue);

private:

    uint8_t* bytePtr;
    uint32_t bitIndex;
};