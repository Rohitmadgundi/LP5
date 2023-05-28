#include<iostream>
#include<omp.h>

int main(int argc, char const *argv[])
{
    #pragma omp parallel num_threads(7)
    {
        std::cout << "hello world \n";
    }
    return 0;
}
