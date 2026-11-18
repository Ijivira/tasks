#include "BooleanVector.h"

BooleanVector::BitReference::BitReference()
{
    bytePtr = nullptr;
    bitIndex = 0;
}
BooleanVector::BitReference::BitReference(uint8_t* Byte_Pointer, uint32_t Bit_Index)
    : bytePtr(Byte_Pointer), bitIndex(Bit_Index) {
}

BooleanVector::BitReference::operator bool()
{
    return *bytePtr & (1 << bitIndex);
}

void BooleanVector::BitReference::operator = (const bool newValue)
{
    if (newValue)
        *bytePtr |= (1 << bitIndex);
    else
        *bytePtr &= ~(1 << bitIndex);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator = (const BitReference& other)
{
    bytePtr = other.bytePtr;
    bitIndex = other.bitIndex;
    return *this;
}

BooleanVector::BitReference BooleanVector::BitReference::operator + (const uint32_t Bits)
{
    BitReference New;
    New.bytePtr = bytePtr + (bitIndex + Bits) / 8;
    New.bitIndex = (bitIndex + Bits) % 8;

    return New;
}

BooleanVector::BitReference BooleanVector::BitReference::operator - (const uint32_t Bits)
{
    BitReference New;
    New.bytePtr = bytePtr + (int)(bitIndex - Bits - 7) / 8;
    New.bitIndex = (8 + (int)(bitIndex - Bits) % 8) % 8;

    return New;
}


BooleanVector::BitReference& BooleanVector::BitReference::operator ++ ()
{
    bytePtr = bytePtr + (bitIndex + 1) / 8;
    bitIndex = (bitIndex + 1) % 8;
    return *this;
}

BooleanVector::BitReference& BooleanVector::BitReference::operator -- ()
{
    bytePtr = bytePtr + (int)(bitIndex - 8) / 8;
    bitIndex = (8 + (int)(bitIndex - 1) % 8) % 8;
    return *this;
}

BooleanVector::BitReference BooleanVector::begin() const
{
    BitReference Ref(vectorData_, 0);
    return Ref;
}

BooleanVector::BitReference BooleanVector::end() const
{
    BitReference Ref(vectorData_ + numBytes_-1, numBits_ % 8);
    return Ref;
}