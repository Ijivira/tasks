#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>



void write_file(int* array, const int N, std::string file_name)
{
    std::ofstream file(file_name);

    for (int* p = array; p < array + N; p++)
    {
        file << *p << " ";
    }
    std::cout << std::endl;

    file.close();
}


void random_array(int* array, const int N, int a, int b)
{
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    std::uniform_int_distribution<int> Data(a, b);

    for (int* p = array; p < array + N; p++)
    {
        *p = Data(generator);
    }
}

void creating_array_files(int N[3], int a[3], int b[3])
{
    for (int i = 0; i < 3; i++)
    {
        int* array = new int[N[i]];

        std::string file_name = "array_N_" + std::to_string(N[i]) +
            "_range_" + std::to_string(a[i]) + "_" + std::to_string(b[i]) + ".txt";

        random_array(array, N[i], a[i], b[i]);
        write_file(array, N[i], file_name);

        delete[] array;

    }
}

void output(int* array, const int N)
{
    for (int i = 0; i < N; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}


void Sorting_by_insertion(int* array, const int N)
{
    for (int i = 1; i < N; i ++)
    {
        int temporary = array[i];

        int j = i - 1;
        while (temporary < array[j])
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temporary;
    }
}

int* Shell_Sorting(const int* array, const int N)
{
    int* new_array = new int[N];
    for (int i = 0; i < N; i++) {
        new_array[i] = array[i];
    }

    // 1 Вариант
    for (int step = N / 2; step > 0; step /= 2)

    // 2 Вариант
    /*int size_h = std::log2(N);
    int* h = new int[size_h];
    for (int i = 0; i < size_h; i++)
    {
        h[i] = pow(2, i+1) - 1;
    }

    int step = h[0];
    for (int i = 0; i < size_h; i++, step = h[i])*/

    // 3 Вариант
    /*int size_h = std::log2(N) - 1;
    int* h = new int[size_h];
    h[0] = 1;
    for (int i = 1; i < size_h; i++)
    {
        h[i] = 3*h[i] + 1;
    }

    int step = h[0];
    for (int i = 0; i < size_h; i++, step = h[i])*/
    {
        
        for (int i = step; i < N; i += step)
        {
            int temporary = new_array[i];
            int j = i - step;
            
            while (j >= 0 && temporary < new_array[j] )
            {
                new_array[j + step] = new_array[j];
                j -= step;
            }
            new_array[j + step] = temporary;
        }
        
    }
    return new_array;
}

bool check_order(int* array, const int N)
{
    int i = 1;
    for (; i < N && array[i-1] <= array[i]; i++);
    if (i == N) return true;
    else return false;
}

void main()
{
    int N[3] = { 1000, 10000, 100000},
        a[3] = { -10, -1000, -100000},
        b[3] = { 10, 1000, 100000},
        time[3][3];

    // СОЗДАНИЕ ФАЙЛОВ
    creating_array_files (N, a, b);

    // прогонка по трем разным массивам
    for (int i = 0; i < 3; i++)
    {
        // ЧТЕНИЕ ФАЙЛА
        std::string file_name = "array_N_" + std::to_string(N[i]) +
        "_range_" + std::to_string(a[i]) + "_" + std::to_string(b[i]) + ".txt";

        std::ifstream file(file_name);

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

        for (int j = 0; j < 3; j++)
        {
            check_order(array, N_elements) ?
                std::cout << "array is sorted" << std::endl :
                std::cout << "array is NOT sorted" << std::endl;

            const auto timeBegin = std::chrono::high_resolution_clock::now();

            new_array = Shell_Sorting(array, N_elements);

            const auto timeEnd = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin).count();


            check_order(new_array, N_elements) ?
                std::cout << "array is sorted" << std::endl :
                std::cout << "array is NOT sorted" << std::endl;
            
            time[i][j] = duration;
        }
       
    }
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            std::cout << time[i][j] << " ";
            sum += time[i][j];
        }
        std::cout << " average: " << sum / 3 << " milliseconds." << std::endl;
    }
}