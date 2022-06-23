#include <iostream>
#include <cmath>
#include <cwchar>

struct Result {
    double first = 0.0;
    double second = 0.0;
    double third = 0.0;

    void println()
    {
        if (this->third == 0.0) {
            this->println_two();
        } else {
            this->println_three();
        }
    }

    void println_two()
    {
        std::wcout << L"first: " << this->first << L", second: " << this->second << L".\n";
    }

    void println_three()
    {
        std::wcout << L"first: " << this->first << L", second: " << this->second << L", third: " << this->third << L".\n";
    }
};

Result first_variant(int, double, double);
Result second_variant(int, double, double);
Result third_variant(int, double, double);
Result fourth_variant(int, double, double);
Result fifth_variant(int, double, double);
Result sixth_variant(double, double, int);
Result seventh_variant(double, int, double);
Result eighth_variant(double, int, double);
Result ninth_variant(double, double, double);
Result tenth_variant(double, double, int, int);
Result eleventh_variant(double, double, double);
Result twelfth_variant(int, double, double);
Result thirteenth_varian(double, int, int, double);
Result fourteenth_variant(double, double, int, double);
Result fifteenth_variant(double, double);
Result sixteenth_variant(int, double);

int main()
{
    std::wcout << L"Variant  1: "; first_variant(4, 2e-4, 8.1).println();
    std::wcout << L"Variant  2: "; second_variant(2, -0.12, 1.3e-4).println();
    std::wcout << L"Variant  3: "; third_variant(-6, 4.5, 1.5e-6).println();
    std::wcout << L"Variant  4: "; fourth_variant(6, -1.2, 0.4e+6).println();
    std::wcout << L"Variant  5: "; fifth_variant(40, 1.1, 5e-6).println();
    std::wcout << L"Variant  6: "; sixth_variant(0.956, 5e-6, 4).println();
    std::wcout << L"Variant  7: "; seventh_variant(1.4, 6, 0.05e-5).println();
    std::wcout << L"Variant  8: "; eighth_variant(0.1, 12, 5e-6).println();
    std::wcout << L"Variant  9: "; ninth_variant(0.5, 1.4, 2e-4).println();
    std::wcout << L"Variant 10: "; tenth_variant(1.7, 4e-8, 3, 3).println();
    std::wcout << L"Variant 11: "; eleventh_variant(1.5, -1.8, 15e-9).println();
    std::wcout << L"Variant 12: "; twelfth_variant(6, 5e-7, 0.095).println();
    std::wcout << L"Variant 13: "; thirteenth_varian(0.5e-8, -9, -4, 1.5).println();
    std::wcout << L"Variant 14: "; fourteenth_variant(1.5, -8.1, 4, 4e-8).println();
    std::wcout << L"Variant 15: "; fifteenth_variant(1.75, 4.5e-4).println();
    std::wcout << L"Variant 16: "; sixteenth_variant(6, 0.05e-5).println();
    return 0;
}

Result first_variant(int k, double x, double a)
{
    double d_k = (double)k;
    Result result;

    result.first = 2.0 * d_k / a + log(2.0 + x);
    result.second = sqrt(d_k - 1.0) / (result.first + 1.0);

    return result;
}

Result second_variant(int n, double b, double x)
{
    double d_n = (double)n;
    Result result;

    result.first = 1.0 / (x - 1.0) + sin(x) - sqrt(d_n);
    result.second = (exp(-b) + 1.0) / (2 * result.first);

    return result;
}

Result third_variant(int i, double x, double z)
{
    double d_i = (double)i;
    Result result;

    result.first = tan(-x * d_i) / sqrt(x - z);
    result.second = sin(2.0 * result.first) / result.first;

    return result;
}

Result fourth_variant(int t, double y, double x)
{
    double d_t = (double)t;
    Result result;

    result.first  = 2.6 * d_t + cos(y / (3.0 * x + y));
    result.second = sin(result.first) / cos(result.first);

    return result;
}

Result fifth_variant(int b, double x, double a)
{
    double d_b = (double)b;
    Result result;

    result.first  = (a + d_b) * tan(x) / (x + 1.0);
    result.second = 0.5 * d_b - sqrt(result.first - a * d_b);

    return result;
}

Result sixth_variant(double y, double a, int n)
{
    double d_n = (double)n;
    Result result;

    result.first  = 1.0 / sqrt(y) + 14.0 * a;
    result.second = (result.first + 1.0) / (a + 2.0);
    result.third = log((2.0 * d_n / 3.0) + exp(-n) / result.second);

    return result;
}

Result seventh_variant(double x, int m, double z)
{
    double d_m = (double)m;
    Result result;

    result.first  = sqrt(1.0 + x) - cos(2.0 / d_m);
    result.second = 0.6 * z - 2.0 * exp(-2.0 * result.first * d_m);

    return result;
}

Result eighth_variant(double x, int j, double y)
{
    double d_j = (double)j;
    Result result;

    result.first  = 0.4 * x - 1.0 / d_j * tan(y);
    result.second = result.first - sin(result.first);

    return result;
}

Result ninth_variant(double y, double c, double x)
{
    Result result;

    result.first  = exp(c * x) / y + 3.0;
    result.second = sqrt(powf(result.first, 3.0) - 0.1 * result.first);

    return result;
}

Result tenth_variant(double z, double a, int m, int n)
{
    double d_m = (double)m, d_n = (double)n;
    Result result;

    result.first = (z + log(z)) / (exp(-3.0) + sqrt(a));
    result.second = (1.0 + d_m * d_n) / log(1 + z);

    return result;
}

Result eleventh_variant(double a, double x, double z)
{
    Result result;

    result.first  = tan(1.0) * (1.0 + x) + z - exp(a);
    result.second = 9.0 * sqrt(2.0 - 3.0 * x) + fabs(a + 1.0);

    return result;
}

Result twelfth_variant(int k, double r, double x)
{
    double d_k = (double)k;
    Result result;

    result.first  = tan(x) + r * (1.0 - log(x));
    result.second = result.first / (powf(x, 3.0) + 1.0) / (1 - exp(d_k - 4.0));

    return result;
}

Result thirteenth_varian(double d, int c, int j, double a)
{
    double d_c = (double)c, d_j = (double)j;
    Result result;

    result.first = d * d_c + a * sqrt(d_c - 1.0);
    result.second = 0.5 * result.first / d + exp(a);

    return result;
}

Result fourteenth_variant(double a, double b, int j, double t)
{
    double d_j = (double)j;
    Result result;

    result.first = sqrt(t * a / t + 1.0) + 4.0 * exp(2.0 * b);
    result.second = result.first * a / (1.0 + 0.1 * a);
    result.third = result.first + d_j * sqrt(powf(a, 2.0) + powf(b, 2.0));

    return result;
}

Result fifteenth_variant(double a, double b)
{
    Result result;

    result.first = a * exp(-2.0 * b) - sqrt(1.0 + a);
    result.second = log(1.0 + 20.0 * b) / (1.0 + a);

    return result;
}

Result sixteenth_variant(int m, double z)
{
    double d_m = (double)m;
    Result result;

    result.first = cos(5.0 * d_m) / powf(sin(0.4 * d_m), 2.0);
    result.second = 4.0 * z * result.first - 7.0 * exp(-2.0 * result.first);

    return result;
}
