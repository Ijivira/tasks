#include <iostream>
#include <fstream>
#include <chrono>
#include <math.h>
void output_pyramid(int* array, const int N)
{
    int row = 0, j = 0, max_element = 0;
    while (row <= log2(N))
    {
        
        for(; j <= max_element && j < N; j++)
        { 
            std::cout << array[j]<< " ";
        }
        std::cout << std::endl;
        row++;
        max_element += pow(2, row);
    }
    std::cout << std::endl;
}
void output_array(int* array, const int N)
{
    for (int i=0; i < N; i++)
    {
        std::cout << array[i] << " ";
    }
}


bool check_order(int* array, const int N)
{
    int i = 1;
    for (; i < N && array[i - 1] <= array[i]; i++);
    if (i == N) return true;
    else return false;
}

void swap(int& A, int& B)
{
    int temp = A;
    A = B;
    B = temp;
}

void sifting(int* array, int N_elements, int i)
{
    int temp = array[i];
    int flag = 1;
    int j = 2 * i + 1;
    while (j < N_elements && flag)
    {
        if (j + 1 < N_elements && array[j + 1] > array[j])
            j = j + 1;


        if (array[j]> temp)
        {
            array[i] = array[j];
            i = j;
            j = 2 * i + 1;
        }
        else
            flag = 0;
    }

    array[i] = temp;
}

int* pyramid_sorting(int *array, int N_elements)
{
    int* new_array = new int[N_elements];


    for (int i = 0; i < N_elements; i++) {
        new_array[i] = array[i];
    }
// Построение пирамиды
    for (int i = N_elements / 2 - 1; i >= 0; i--)
        sifting(new_array, N_elements, i);

// Проcеивание всех элементов
    for (int i = N_elements-1; i > 0; i--)
    {
        swap(new_array[0], new_array[i]);
        sifting(new_array, i, 0);
    }


    return new_array;
}


void main()
{
    int N[3] = { 1000, 10000, 100000},
        a[3] = { -10, -1000, -100000},
        b[3] = { 10, 1000, 100000},
        time[3][3][3];

    // прогонка по трем разным массивам
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // ЧТЕНИЕ ФАЙЛА
             std::string file_name = "array_N_" + std::to_string(N[i]) +
                 "_range_" + std::to_string(a[j]) + "_" + std::to_string(b[j]) + ".txt";

            std::ifstream file(file_name);

            if (file.is_open()) {
                std::cout << file_name << std::endl;
            }

            int N_elements = 0;
            int temp;

            while (file >> temp)
            {
                N_elements++;
            }

            int* array = new int[N_elements];

            file.clear();
            file.seekg(0, std::ios::beg);

            for (int index = 0; index < N_elements; file >> array[index], index++);

            file.close();


            // СОРТИРОВКА
            // три раза
            int* new_array = new int[N_elements];

            for (int k = 0; k < 3; k++)
            {
                const auto timeBegin = std::chrono::high_resolution_clock::now();

                new_array = pyramid_sorting(array, N_elements);

                const auto timeEnd = std::chrono::high_resolution_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin).count();

                check_order(new_array, N_elements) ?
                    std::cout << "array is sorted" << std::endl :
                    std::cout << "array is NOT sorted" << std::endl;

                delete[] new_array;

                time[i][j][k] = duration;
            }
        }

    }
    
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                std::cout << time[i][j][k] << " ";
                sum += time[i][j][k];
            }
        }
        std::cout << " average: " << sum / 9 << " microseconds." << std::endl;
    }
}