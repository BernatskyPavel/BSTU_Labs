#include "lab_03.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <wchar.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cmath>

typedef std::vector<std::vector<uint>> figure;
extern struct winsize win_size;

void print_figure(figure fig, wchar_t ch, Position pos) {

    int max = 0;

    for(int i = 0; i < fig.size(); i++) {
        int temp = 0;
        for(int j = 1; j < fig[i].size(); j++) {
            temp += fig[i][j];
        }
        if(max<temp) max = temp;
    }

    int diff = 0;

    switch(pos) {
        case CENTER: diff = (win_size.ws_col - max) / 2; break;
        case LEFT: diff = 1; break;
        case RIGHT: diff = (win_size.ws_col - max); break;
    };

    for(int i = 0; i < fig.size(); i++) {
        for(int j = 0; j < fig[i][0]; j++) {
            std::wcout << std::setw(fig[i][2*j+1]+(j==0?diff:0)) << std::setfill(SPACE) << SPACE <<  std::setw(fig[i][2*j+2])<< std::setfill(ch) << ch;
        }
        std::wcout << L"\n";
    }
}

double input_number() {
    double temp;
    for(;;){
        std::wcin >> temp;

        if(std::wcin.fail()) {
            std::wcin.clear();
            wchar_t x;
            std::wcin >> x;
            std::wcout << L"Invalid input! Try again: ";
            continue;
        }
        break;
    }
    return temp;
}

void first_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure semi_sphere = {{1, 0, 40}, {1,0,40}, {1, 0, 40}, {1, 1, 38}, {1, 2, 36}, {1, 3, 34}, {1, 4, 32}, {1, 6, 28}, {1, 8, 24}, {1, 11, 18}, {1,15,10}};

    print_figure(semi_sphere, ch, Position::LEFT);

    double a, b;
    std::wcout << L"\n----- Part 2 -----\nType number a:";
    a = input_number();

    std::wcout << L"Type number b:";
    b = input_number();

    std::wcout << L"Before swap: a = " << a << L", b = " << b << L"\n";

    double temp = b;
    b = a;
    a = temp;

    std::wcout << L"After swap with temp variable: a = " << a << L", b = " << b << L"\n";

    a = a + b;
    b = a - b;
    a = a - b;

    std::wcout << L"After swap without variable: a = " << a << L", b = " << b << L"\n";
}

void second_variant()
{
    //ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);

    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure hexagon = {{1, 6, 11}, {1,4,15}, {1, 2, 19}, {1, 0, 23}, {1, 0, 23}, {1, 0, 23}, {1, 0, 23}, {1, 0, 23}, {1, 0, 23}, {1, 2, 19}, {1,4,15}, {1, 6, 11}};

    print_figure(hexagon, ch, Position::CENTER);

    double m;
    std::wcout << L"\nType number m:";
    m = input_number();
    std::wcout << L"m = " << m << L"\n";

    double a = (m-5.0)/2.0, b = m - a;

    std::wcout << L"After: a = " << a << L", b = " << b << L"\n";
}

void third_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

     figure xmas_tree = {{1, 13, 1}, {1,12,3}, {1, 10, 7}, {1, 8, 11}, {1, 6, 15}, {1, 4, 19}, {1, 2, 23}, {1, 10, 7}, {1, 8, 11}, {1, 6, 15}, {1, 4, 19}, {1, 2, 23}, {1, 0, 27}, {1, 10, 7}, {1, 10, 7}, {1, 10, 7}, {1, 10, 7}};

    print_figure(xmas_tree, ch, Position::LEFT);

    double n;
    std::wcout << L"\nType number n:";
    n = input_number();
    std::wcout << L"n = " << n << L", S = " << pow(2.0*n+2.0, 2.0) / n << L"\n";
}

void fourth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure sphere = {{1,15,10}, {1, 11, 18}, {1, 8, 24}, {1, 6, 28}, {1, 4, 32}, {1, 3, 34}, {1, 2, 36}, {1, 1, 38}, {1, 0, 40}, {1,0,40}, {1, 0, 40}, {1, 0, 40}, {1,0,40}, {1, 0, 40}, {1, 1, 38}, {1, 2, 36}, {1, 3, 34}, {1, 4, 32}, {1, 6, 28}, {1, 8, 24}, {1, 11, 18}, {1,15,10}};

    print_figure(sphere, ch, Position::CENTER);

    double x, y, z;
    std::wcout << L"\nType number x:";
    x = input_number();
    std::wcout << L"Type number y:";
    y = input_number();
    std::wcout << L"Type number z:";
    z = input_number();

    double mean = (fabs(x) + fabs(y) + fabs(z)) / 3.0;
    double geom_mean = powf64(fabs(x) * fabs(y) * fabs(z), (1.0/3.0));

    std::wcout << L"x = " << x << L", y = " << y << L", z = " << z << L", Mean = " << mean << L", GMean =  " << geom_mean << L"\n";

}

void fifth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure triangle = {{1, 12, 1}, {1, 11, 3}, {1, 10, 5}, {1, 9, 7}, {1, 8, 9}, {1, 7, 11}, {1, 6, 13}, {1, 5, 15}, {1, 4, 17}, {1, 3, 19}, {1, 2, 21}, {1, 1, 23}, {1, 0, 25}};

    print_figure(triangle, ch, Position::CENTER);

    double p;
    int n;
    std::wcout << L"\nType number n:";
    n = (int)input_number();
    std::wcout << L"Type number p:";
    p = input_number();

    double start = 100.0, current = start;

    for(size_t i = 0; i < n; i++) {
        current = (current * (100.0 + p) / 100.0) * (100.0 - p) / 100.0;
    }

    double size = fabs(1.0 - current / start) * 100.0;

    const wchar_t* dyn = size >= 1.0? L"Positive" : L"Negtive";

    std::wcout << L"n = " << n << L", p = " << p << L", Dyn = " << dyn << L", Size = " << size << L"%\n";
}

void sixth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure star = {{1, 7, 1}, {1, 6, 3}, {1, 5, 5}, {1, 0, 15}, {1, 2, 11}, {1, 4, 7}, {2, 3, 3, 3, 3}, {2, 2, 2, 7, 2}};

    print_figure(star, ch, Position::LEFT);

    double x1,y1,x2,y2;
    std::wcout << L"\nType number x1:";
    x1 = (int)input_number();
    std::wcout << L"Type number y1:";
    y1 = input_number();
    std::wcout << L"Type number x2:";
    x2 = (int)input_number();
    std::wcout << L"Type number y2:";
    y2 = input_number();

    double dist = sqrtf(powf(fabs(x1 - x2), 2.0) + powf(fabs(y1 - y2), 2.0));

    std::wcout << L"M1 = (" << x1 << L", " << y1 << L"), M2 = (" << x2 << L", " << y2 << L"), Dist = " << dist << L"\n";
}

void seventh_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure trapezoid = {{1, 7, 23}, {1, 6, 26}, {1, 5, 29}, {1, 4, 32}, {1, 3, 35}, {1, 2, 38}, {1, 1, 41}, {1, 0, 44}};

    print_figure(trapezoid, ch, Position::CENTER);

    double r;
    std::wcout << L"\nType number r:";
    r = (int)input_number();

    double s = acos(-1) * powf(r, 2.0);

    std::wcout << L"R = " << r << L", S = " << s << L"\n";
}

void eighth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure person = {{1, 3, 6}, {1, 2, 8}, {1, 2, 8}, {1, 3, 6}, {1, 5, 2}, {1, 3, 6}, {3, 2, 2, 1, 2, 1, 2}, {3, 1, 2, 2, 2, 2, 2}, {3, 0, 2, 3, 2, 3, 2}, {1, 5, 2}, {1, 4, 4}, {2, 3, 2, 2, 2}, {2, 2, 2, 4, 2}, {2, 1, 2, 6, 2}};

    print_figure(person, ch, Position::LEFT);

    double x, y, z;
    std::wcout << L"\nType number x:";
    x = input_number();
    std::wcout << L"Type number y:";
    y = input_number();
    std::wcout << L"Type number z:";
    z = input_number();

    double semi_perimeter = (x + y + z) / 2.0;
    double area = sqrt(semi_perimeter * (semi_perimeter - x) * (semi_perimeter - y) * (semi_perimeter - z));

    std::wcout << L"x = " << x << L", y = " << y << L", z = " << z << L", S = " << area << L"\n";
}

void ninth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure arrows = {{2, 24, 3, 9, 5}, {2, 23, 5, 8, 5}, {2, 22, 7, 7, 5}, {2, 21, 9, 6, 5}, {4, 11, 2, 7, 11, 5, 5, 10, 2}, {4, 11, 4, 8, 5, 8, 5, 8, 4}, {4, 0, 17, 6, 5, 8, 5, 6, 17}, {4, 0, 18, 5, 5, 8, 5, 5, 18}, {4, 0, 17, 6, 5, 8, 5, 6, 17}, {4, 11, 4, 8, 5, 8, 5, 8, 4}, {4, 11, 2, 10, 5, 5, 11, 7, 2}, {2, 23, 5, 6, 9}, {2, 23, 5, 7, 7}, {2, 23, 5, 8, 5}, {2, 23, 5, 9, 3}};

    print_figure(arrows, ch, Position::LEFT);

    double a;
    std::wcout << L"\nType number a:";
    a = (int)input_number();

    double quadro = a * a;
    quadro = quadro * quadro;

    std::wcout << L"a = " << a << L", a^4 = " << quadro << L"\n";

}

void tenth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure elipse = {{1, 15, 16}, {1, 10, 26}, {1, 4, 38}, {1, 0, 46}, {1, 0, 46}, {1, 0, 46}, {1, 4, 38}, {1, 10, 26}, {1, 15, 16}};

    print_figure(elipse, ch, Position::LEFT);

    double n, k;
    std::wcout << L"\nType number N:";
    n = input_number();
    std::wcout << L"Type number K:";
    k = input_number();

    std::wcout << L"N = " << n << L", K = " << k << L", Apples each = " << (int)(k/n) << L"\n";
}

void eleventh_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure square = {{1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}, {1, 0, 20}};

    print_figure(square, ch, Position::LEFT);

    double d;
    std::wcout << L"\nType number d:";
    d = input_number();

    std::wcout << L"d = " << d << L", S = " << powf(d, 2.0) / 2.0 << L"\n";
}

void twelfth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure plus = {{1, 10, 4}, {1, 10, 4}, {1, 10, 4}, {1, 10, 4}, {1, 10, 4}, {1, 0, 24}, {1, 0, 24}, {1, 10, 4}, {1, 10, 4}, {1, 10, 4}, {1, 10, 4}, {1, 10, 4}};

    print_figure(plus, ch, Position::LEFT);

    double d;
    std::wcout << L"\nType number d:";
    d = input_number();

    double d_signinficand = (double)((int)d);
    double d_float = d - d_signinficand;

    std::wstring s_d_signinficand = std::to_wstring((int)d_signinficand);
    std::wstring s_d_float = std::to_wstring(d_float);

    std::wstring s_rd = std::wstring();

    if(d_float != 0.0) {

        for(std::wstring::reverse_iterator iter = s_d_float.rbegin(); *iter != L','; ++iter) {
            s_rd += *iter;
        }

        s_rd += L",";
    }

    for(std::wstring::reverse_iterator iter = s_d_signinficand.rbegin(); iter != s_d_signinficand.rend(); ++iter) {
        s_rd += *iter;
    }

    std::wcout << s_rd << L"\n";

    double rd = std::stod(s_rd);

    std::wcout << L"d = " << d << L", reversed d = " << rd << L"\n";
}

void thirteenth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure heart = {{2, 3, 2, 5, 2}, {2, 1, 5, 3, 5}, {2, 0, 7, 1, 7}, {1, 0, 15}, {1, 0, 15}, {1, 1, 13}, {1, 2, 11}, {1, 3, 9}, {1, 4, 7}, {1, 5, 5}, {1, 6, 3}, {1, 7, 1}};

    print_figure(heart, ch, Position::LEFT);

    int n, m;
    std::wcout << L"\nType number n:";
    n = (int)input_number();
    std::wcout << L"Type number m:";
    m = (int)input_number();

    int temp = (n-1)*10;
    std::wcout << L"N = " << n << L", M = " << m << L", time = " << m + (temp / 60) << L":" << (int)temp % 60<< L"\n";
}

void fourteenth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure rhombus = {{1, 11, 1}, {1, 10, 3}, {1, 8, 7}, {1, 6, 11}, {1, 4, 15}, {1, 2, 19}, {1, 0, 23}, {1, 2, 19}, {1, 4, 15}, {1, 6, 11}, {1, 8, 7}, {1, 10, 3}, {1, 11, 1}};

    print_figure(rhombus, ch, Position::LEFT);

    std::wcout << L"\n";
    double v[5];
    for (size_t i = 0; i < 5; i++){
        std::wcout << L"\nType number v"<<i+1<<L":";
        v[i] = input_number();
    }

    double avg = 0.0;

    for (size_t i = 0; i < 5; i++){
        avg += powf(v[i], -1.0);
        std::wcout << L"Type number v"<<i+1<<L" = " << v[i] << L"\n";
    }

    avg /= 5.0;
    avg = powf(avg, -1.0);

    std::wcout << L"Avg = " << avg << L"\n";
}

void fifteenth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure rhombus = {{2, 11, 1, 3, 3}, {2, 10, 3, 2, 3}, {1, 8, 10}, {1, 6, 12}, {1, 4, 15}, {1, 2, 19}, {1, 0, 23}, {1, 3, 17}, {1, 3, 17}, {3, 3, 5, 3, 1, 3, 5}, {3, 3, 5, 3, 1, 3, 5}, {1, 3, 17}, {1, 3, 17}, {1, 3, 17}, {1, 3, 17}};

    print_figure(rhombus, ch, Position::LEFT);

    int app;
    std::wcout << L"\nType number app:";
    app = (int)input_number();

    int floor = 0, hall = 0;

    hall = ceil((double)app/36);
    floor = ceil(fmod(((double)app/4.0), 9.0));

    std::wcout << L"app = " << app << L", hall = " << hall << L", floor = " << floor << L"\n";
}

void sixteenth_variant()
{
    wchar_t ch;
    std::wcout << L"\nType symbol to fill:";
    std::wcin >> ch;
    std::wcout << L"\n";

    figure mushroom = {{1, 31, 16}, {1, 26, 26}, {1, 25, 27}, {1, 23, 31}, {1, 21, 33}, {1, 20, 36}, {1, 19, 38}, {1, 18, 40}, {1, 18, 41}, {1, 17, 42}, {1, 18, 42}, {1, 17, 42}, {1, 18, 41}, {1, 19, 39}, {3, 19, 5, 8, 14, 8, 4}, {1, 32, 14}, {1, 31, 16}, {1, 31, 17}, {1, 31, 16}, {1, 33, 12}, {1, 33, 12}, {1, 32, 14}, {1, 26, 26}, {1, 0, 80}};

    print_figure(mushroom, ch, Position::LEFT);

    int a, b, c;
    std::wcout << L"\nType number a:";
    a = (int)input_number();
    std::wcout << L"Type number b:";
    b = (int)input_number();
    std::wcout << L"Type number c:";
    c = (int)input_number();

    std::wcout << L"a = " << a << L", b = " << b << L", c = " << c << L", Score = " << a*50+b*100+c*200<< L"\n";
}

