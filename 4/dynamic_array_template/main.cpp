#include <iostream>
#include "DynamicArray.h"

int main()
{
	double A[] = {12, 2, 3, 4, 8, 10, 20 };
	double B[] = {9, 8, 7, 6, 8, 8, 6, 3, 1};
	DynamicArray<double> Dynamic_A (A, sizeof(A)/ sizeof(A[0]));
	DynamicArray<double> Dynamic_B (B, sizeof(B) / sizeof(B[0]));
	DynamicArray<double> Dynamic_С;

	int a;
	
	//получение размера(количества хранимых элементов в настоящий момент)
	std::cout << std::endl << "getting the size:" << std::endl;
	Dynamic_A.output();
	std::cout << Dynamic_A.get_length() << std::endl;

	//обмен содержимого с другим массивом (swap);
	std::cout << std::endl << "Swapping content with another array:" << std::endl;
	std::cout << "it was" << std::endl;
	Dynamic_A.output();
	Dynamic_B.output();
	Dynamic_A.swap(Dynamic_B);
	std::cout << "has become" << std::endl;
	Dynamic_A.output();
	Dynamic_B.output();

	// поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, 
	// если совпадений нет);
	std::cout << std::endl << "element search:" << std::endl;
	Dynamic_A.output();
	std::cout << "What are we looking for?" << std::endl;
	std::cin >> a;
	std::cout << Dynamic_A.search(a) << std::endl;

	//ввод/вывод в консоль (потоковый);
	std::cout << std::endl << "entering an array from the console:" << std::endl;
	Dynamic_С.input();
	Dynamic_С.output();

	//сортировка элементов(любым алгоритмом);
	std::cout << std::endl << "sorting the elements:" << std::endl;
	Dynamic_A.output();
	Dynamic_A.sort();
	Dynamic_A.output();

	//вставка элемента по индексу.Если индекс некорректный, вернуть false;
	std::cout << std::endl << "inserting an element by index:" << std::endl;
	Dynamic_A.output();
	Dynamic_A.insert(66, 4);
	Dynamic_A.output();

	// Удаление элемента по индексу
	std::cout << std::endl << "deleting an item by index:" << std::endl;
	Dynamic_A.output();
	std::cout << "Where do we delete it?" << std::endl;
	std::cin >> a;
	Dynamic_A.delete_position(a);
	Dynamic_A.output();

	// удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
	std::cout << std::endl << "deleting an element by value:" << std::endl;
	Dynamic_A.output();
	std::cout << "What are we deleting?" << std::endl;
	std::cin >> a;
	Dynamic_A.delete_element(a);
	Dynamic_A.output();
	std::cout << std::endl;

	// удаление элементов с заданным значением;
	std::cout << std::endl << "deleting all elements with the specified value:" << std::endl;
	Dynamic_A.output();
	std::cout << "What are we deleting?" << std::endl;
	std::cin >> a;
	Dynamic_A.delete_all_element(a);
	Dynamic_A.output();

	// поиск максимального / минимального элемента;
	std::cout << std::endl << "searching for the maximum/minimum element:" << std::endl;
	Dynamic_B.output();
	std::cout << Dynamic_B.min() << std::endl;
	std::cout << Dynamic_B.max() << std::endl;

	//присваивание копированием (=);
	std::cout << std::endl << "assignment by copying:" << std::endl;
	std::cout << "it was" << std::endl;
	Dynamic_A.output();
	Dynamic_С.output();
	Dynamic_С = Dynamic_A;
	std::cout << "has become" << std::endl;
	Dynamic_A.output();
	Dynamic_С.output();

	//добавление элемента в конец массива(+и += );
	std::cout << std::endl << "adding an element to the end of the array(+ and += ):" << std::endl;
	Dynamic_A.output();
	Dynamic_A = Dynamic_A + 9 + 5 + 6;
	Dynamic_A.output();
	std::cout << std::endl;

	Dynamic_A += 12;
	Dynamic_A.output();
	std::cout << std::endl;
	
	//сложение (конкатенация) с другим массивом(+ и +=);
	std::cout << std::endl << "addition (concatenation) with another array (+ and +=):" << std::endl;
	Dynamic_A.output();
	Dynamic_B.output();
	Dynamic_С = Dynamic_A + Dynamic_B;
	Dynamic_С.output();
	std::cout << std::endl;

	Dynamic_С += Dynamic_B;
	Dynamic_С.output();

	// сравнение(== и != ).
	std::cout << std::endl << "comparison(== and != ):" << std::endl;
	Dynamic_A.output();
	Dynamic_B.output();
	(Dynamic_A == Dynamic_B) ? std::cout << "equals" : std::cout << "different";
	std::cout << std::endl;
	(Dynamic_A != Dynamic_B) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;

	Dynamic_A = Dynamic_B;
	Dynamic_A.output();
	Dynamic_B.output();
	(Dynamic_A == Dynamic_B) ? std::cout << "equals" : std::cout << "different";
	std::cout << std::endl;
	(Dynamic_A != Dynamic_B) ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;
	
	// работа итераторов
	// получение итераторов на начало / конец массива
	std::cout << std::endl << "getting iterators at the beginning / end of an array:" << std::endl;
	Dynamic_A.output();
	std::cout << *(Dynamic_A.begin()) << std::endl;
	std::cout << *(Dynamic_A.end()-1) << std::endl;

	// вставка по итератору
	std::cout << std::endl << "iterator insertion:" << std::endl;
	Dynamic_A.output();
	Dynamic_A.insert(5, Dynamic_A.begin()+2);
	Dynamic_A.output();
	std::cout << std::endl;
	
	// удаление по итератору
	std::cout << std::endl << "deleting by iterator:" << std::endl;
	Dynamic_A.output();
	Dynamic_A.delete_element(Dynamic_A.begin());
	Dynamic_A.output();
	std::cout << std::endl;

	// удаление по итераторам
	Dynamic_A.output();
	Dynamic_A.delete_element(Dynamic_A.begin() + 2, Dynamic_A.begin() + 3);
	Dynamic_A.output();

	// потоковый ввод и вывод
	Dynamic_A.output();
	std::cin >> Dynamic_A;
	std::cout << Dynamic_A;
	return 0;
}