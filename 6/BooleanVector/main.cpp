#include "BooleanVector.h"
#include <iostream>

int main()
{
    // конструктор по умолчанию, 
    BooleanVector testVector1;

    // конструктор с параметрами (размер и значение - одно и то же для всех разрядов),
    BooleanVector testVector2(8, true);

    // конструктор из массива const char *, 
    char str[] = "0000000011111111";
    BooleanVector testVector3(str);
    std::cout << str << std::endl;
    std::cout << testVector3 << std::endl << std::endl;

    // конструктор копирования;
    BooleanVector testVector4(testVector3);
    std::cout << testVector4 << std::endl<< std::endl;

    // длина(количество бит) вектора;
    std::cout << "length(number of bits) of a vector" << std::endl;
    std::cout << testVector4.getBitsCount() << std::endl << std::endl;

    // обмен содержимого с другим вектором(swap);
    std::cout << "swap" << std::endl;
    std::cout << testVector2 << std::endl;
    std::cout << testVector4 << std::endl;
    testVector2.swap(testVector4);
    std::cout << testVector2 << std::endl;
    std::cout << testVector4 << std::endl << std::endl;

    /*// потоковый ввод с консоли;
    std::cout << "vector from the console" << std::endl;
    BooleanVector testVector5;
    std::cin >> testVector5;
    std::cout << testVector5 << std::endl << std::endl;
    */
    // инверсия всех компонент вектора;
    std::cout << "complete inversion" << std::endl;
    std::cout << testVector4 << std::endl;
    testVector4.complete_inversion();
    std::cout << testVector4 << std::endl << std::endl;

    // инверсия i - ой компоненты;
    std::cout << "inversion (i=2)" << std::endl;
    std::cout << testVector4 << std::endl;
    testVector4.inversion(2);
    std::cout << testVector4 << std::endl << std::endl;

    // установка в 0 / 1 i - ой компоненты;
    std::cout << "new bit value (i=0)" << std::endl;
    std::cout << testVector4 << std::endl;
    testVector4.setValue(0, 1);
    std::cout << testVector4 << std::endl << std::endl;

    // установка в 0 / 1 k компонент, начиная с i - ой;
    std::cout << "new bits value (i..i+k)" << std::endl;
    std::cout << testVector4 << std::endl;
    testVector4.setValuePart(testVector4.getBitsCount() - 3, 3, 1);
    std::cout << testVector4 << std::endl << std::endl;

    // установка в 0 / 1 всех компонент вектора;
    std::cout << "new value" << std::endl;
    std::cout << testVector4 << std::endl;
    testVector4.setValueAll(1);
    std::cout << testVector4 << std::endl << std::endl;

    // вес вектора(количество единичных компонент)
    std::cout << "weight" << std::endl;
    std::cout << testVector3 << std::endl;
    std::cout << testVector3.weight() << std::endl << std::endl;

    // побитовое умножение(&, &=);
    std::cout << "bitwise multiplication(&, &=)" << std::endl;
    testVector2 = "0011";
    testVector3 = "0101";
    std::cout << testVector2 << std::endl;
    std::cout << testVector3 << std::endl;
    testVector4 = testVector2 & testVector3;
    std::cout << testVector4 << std::endl << std::endl;

    // побитовое сложение(|, |=);
    std::cout << "bitwise addition(|, |=)" << std::endl;
    std::cout << testVector2 << std::endl;
    std::cout << testVector3 << std::endl;
    testVector4 = testVector2 | testVector3;
    std::cout << testVector4 << std::endl << std::endl;

    // побитовое исключающее ИЛИ(^, ^=);
    std::cout << "bitwise exclusive OR(^, ^=)" << std::endl;
    std::cout << testVector2 << std::endl;
    std::cout << testVector3 << std::endl;
    testVector4 = testVector2 ^ testVector3;
    std::cout << testVector4 << std::endl << std::endl;

    // побитовые сдвиги(<< , >> , <<=, >>=);
    std::cout << "bitwise shifts(<< , >> , <<=, >>=)" << std::endl;
    std::cout << testVector3 << std::endl;
    testVector4 = testVector3 << 2;
    std::cout << testVector4 << std::endl;
    testVector4 = testVector3 >> 2;
    std::cout << testVector4 << std::endl;


    // побитовая инверсия(~);
    std::cout << "bitwise inversion(~)" << std::endl;
    std::cout << testVector3 << std::endl;
    testVector4 = ~testVector3;
    std::cout << testVector4 << std::endl;


    return 0;
}