#include <iostream>
#include <fstream>
#include <chrono>

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

int* copy(int* array, int N_elements)
{
    int* new_array = new int[N_elements];
    for (int i = 0; i < N_elements; i++)
        new_array[i] = array[i];
    return new_array;
}

void print(int* array, int left, int right)
{
    for (int i = left; i <= right; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

// Сортировка
void Sort(int* array, int left, int right) {
    if (left < right) {
        int i = left;
        int j = right;
        int x = array[(left + right) / 2];

        while (i <= j)
        {
            while (array[i] < x) i++;
            while (array[j] > x) j--;

            if (i <= j)
            {
                swap(array[i], array[j]);
                i++;
                j--;
            }
        }
        Sort(array, left, j);
        Sort(array, i, right);
    }
}


int main() 
{
    int N[3] = { 1000, 10000, 100000 },
        a[3] = { -10, -1000, -100000 },
        b[3] = { 10, 1000, 100000 },
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
                new_array = copy(array, N_elements);

                const auto timeBegin = std::chrono::high_resolution_clock::now();

                Sort(new_array, 0, N_elements-1);

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

    return 0;
}