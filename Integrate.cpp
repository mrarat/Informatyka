#include <iostream>

double Abs(double val)
{
    if(val < 0)
        return -val;
    return val;
}

double IntegrateFragm(double (*func)(double), double start, double end, unsigned long long int fragments)
{
    double fragm_length = (end - start)/double(fragments); //std::cout << "fragm_length = " << fragm_length << "\n";
    double result = 0.0;
    double prev = func(start); //std::cout << "0.\t" << func(start) << "\n";

    for(unsigned long long int i=0; i<fragments; i++)
    {
        double val = func(start + double(i+1)*fragm_length);
        result += val + prev;
        prev = val;
    }

    return result*fragm_length/2;
}

double Integrate(double (*func)(double), double start, double end, double precision)
{
    unsigned long long int fragments = 2;

    double result_prev = IntegrateFragm(func, start, end, 1);
    double result = IntegrateFragm(func, start, end, 2);

    while(Abs(result_prev - result) > precision)
    {
        fragments <<= 1;
        result_prev = result;
        result = IntegrateFragm(func, start, end, fragments);
    }

    std::cout << "fragments = " << fragments << "\n";

    return result;
}

double Func1(double x)
{
    return x+1;
}

double Func2(double x)
{
    return x*x/2-x+1;
}

int main()
{
    std::cout << "result = " << Integrate(Func2, 0.0, 11.0, 0.000001) << "\n";

    return 0;
}
