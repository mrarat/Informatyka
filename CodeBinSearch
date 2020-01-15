#include <iostream>
#include <chrono>
#include <cstdlib> // srand() and rand() work fine even when not included ???

#include <fstream>

unsigned int erand()
{
    return (unsigned long long)(rand()*(RAND_MAX+1) + rand())%UINT_MAX;
}

template<class T>
T ReadFile(std::ifstream &instream, int pos)
{
    instream.seekg(pos*sizeof(T));

    T val;
    instream.read((char*)&val, sizeof(T));

    return val;
}

template<class T>
int BinarySearch(std::ifstream &instream, T val)
{
    int left = 0;

    instream.seekg(0,instream.end);
    int right = (instream.tellg()/sizeof(T))-1; //std::cout << "\nright = " << right << "\n";

    while(left <= right)
    {
        int mid = left + (right-left)/2; // prevents overflow

        T val_mid = ReadFile<T>(instream, mid);

        if(val_mid == val)
            return mid;
        else if(val_mid < val)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main()
{
    // proper way to set up srand()
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    int arr_size = 1000;
    int *arr = new int[arr_size];

    arr[0] = rand()%256;
    for(int i=1; i<arr_size; i++)
        arr[i] = arr[i-1] + 1 + rand()%256;

    // Print array
    std::cout << "arr:\n";
    for(int i=0; i<arr_size; i++)
        std::cout << i << ".\t" << arr[i] << "\n";
    std::cout << "\n";

    // Save array to file
    std::ofstream outstream("file.bin", std::ios::binary);

    if(!outstream.is_open())
        return -1;

    outstream.write((char*)arr, sizeof(int)*arr_size);

    outstream.close();

    delete [] arr;

    // Binary search
    std::ifstream instream("file.bin", std::ios::binary);

    if(!instream.is_open())
        return -1;

    while(true)
    {
        std::cout << "Enter value: "; int val; std::cin >> val;

        if(val == -1)
        {
            std::cout << "\n";
            break;
        }

        std::cout << "result: " << BinarySearch<int>(instream, val) << "\n\n";
    }

    instream.close();

    return 0;
}

