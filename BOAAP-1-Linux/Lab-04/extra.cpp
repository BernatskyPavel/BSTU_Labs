#include "extra.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>

namespace extra {

struct InputRules
{
public:
  template<typename T>
  static bool empty(T arg)
  {
    return true;
  }
  static bool chess_row(int row) { return (row >= 1 && row <= 8); }
  static bool chess_col(wchar_t col) { return (col >= L'a' && col <= L'h'); }
};

class Calculator
{
public:
  double Calculate(double x, wchar_t oper, double y)
  {
    switch (oper) {
      case L'+':
        return x + y;
        break;
      case L'-':
        return x - y;
        break;
      case L'*':
        return x * y;
        break;
      case L'/':
        return x / y;
        break;
      case L'%':
        return fmodf64(x, y);
        break;
      default:
        return 0.0;
        break;
    }
  }
};

enum ShapeType
{
  IRREGULAR,
  PARALLELOGRAM,
  TRAPEZOID,
  RECTANGLE,
  SQUARE,
  RHOMBUS,
};

template<typename T>
T
input_value(bool func(T) = InputRules::empty)
{
  T temp;
  for (;;) {
    std::wcin >> temp;

    if (std::wcin.fail()) {
      std::wcin.clear();
      wchar_t x;
      std::wcin >> x;
      std::wcout << L"Invalid input! Try again: ";
      continue;
    } else if (!func(temp)) {
      std::wcout << L"Invalid input! Try again: ";
      continue;
    }
    break;
  }
  return temp;
}

void
first_extra()
{
  std::wcout << L"Calculator Console Application" << std::endl << std::endl;
  std::wcout << "Please enter the operation to perform. Format: a+b | a-b | "
                "a*b | a/b | a%b | a!b to stop"
             << std::endl;

  double x = 0.0, y = 0.0, result = 0.0;
  wchar_t oper = L'+';

  Calculator calc;

  while (true) {
    std::wcin >> x >> oper >> y;
    if (oper == L'!') {
      break;
    }
    result = calc.Calculate(x, oper, y);
    std::wcout << L"Result is: " << result << L"\n";
  }

  return;
}

void
second_extra()
{
  std::wcout << L"Input k:";
  wchar_t k = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input m:";
  wchar_t m = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input n:";
  int n = input_value<int>(InputRules::chess_row);

  if (abs((int)(k - m)) == abs(n - 1)) {
    std::wcout << L"Figure at " << m << n << " is under threat!\n";
  } else {
    std::wcout << L"Figure at " << m << n << " is safe!\n";
  }
}

void
third_extra()
{
  std::wcout << L"Input k:";
  wchar_t k = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input m:";
  wchar_t m = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input n:";
  int n = input_value<int>(InputRules::chess_row);

  int col_diff = abs((int)(k - m)), row_diff = abs(n - 1);

  if (col_diff == row_diff || col_diff * row_diff == 0) {
    std::wcout << L"Place at " << m << n << " is reachable in one turn!\n";
  } else {
    std::wcout << L"Place at " << m << n << " is unreachable in one turn!\n"
               << L"Two steps needed: " << k << L"1 -> " << m << "1, " << m
               << L"1 -> " << m << n << std::endl;
  }
}

void
fourth_extra()
{
  std::wcout << L"Input a:";
  double a = input_value<double>();
  std::wcout << L"Input b:";
  double b = input_value<double>();
  double houses[2][2];
  std::wcout << L"Input p:";
  houses[0][0] = input_value<double>();
  std::wcout << L"Input q:";
  houses[0][1] = input_value<double>();
  std::wcout << L"Input r:";
  houses[1][0] = input_value<double>();
  std::wcout << L"Input s:";
  houses[1][1] = input_value<double>();

  size_t combinations[][2] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

  double houses_area_sum = 0.0;
  for (size_t i = 0; i < 2; i++) {
    houses_area_sum += houses[i][0] * houses[0][1];
  }

  if (a * b < houses_area_sum) {
    std::wcout << L"Buildings doesn't fit!\n";
  } else {
    bool result = false;
    double area_max_side = std::max(a, b);
    double area_min_side = std::min(a, b);

    for (size_t i = 0; i < 4; i++) {
      double sum =
               houses[0][combinations[i][0]] + houses[1][combinations[i][1]],
             max = std::max(houses[0][1 - combinations[i][0]],
                            houses[1][1 - combinations[i][1]]);
      result = result || (area_max_side >= std::max(sum, max) &&
                          area_min_side >= std::min(sum, max));
    }

    if (result) {
      std::wcout << L"Buildings does fit!\n";
    } else {
      std::wcout << L"Buildings doesn't fit!\n";
    }
  }
}

void
fifth_extra()
{
  std::wcout << L"Input r:";
  double r = input_value<double>();
  std::wcout << L"Input p:";
  double p = input_value<double>();
  std::wcout << L"Input q:";
  double q = input_value<double>();

  double inner_radius = (p * q) / (2 * hypot(p, q));
  if (r <= inner_radius) {
    std::wcout << L"Sphere does fit!\n";
  } else {
    std::wcout << L"Sphere doesn't fit!\n";
  }
}

void
sixth_extra()
{
  std::wcout << L"Input a:";
  double a = input_value<double>();
  std::wcout << L"Input b:";
  double b = input_value<double>();
  std::wcout << L"Input c:";
  double c = input_value<double>();
  std::wcout << L"Input r:";
  double r = input_value<double>();
  std::wcout << L"Input s:";
  double s = input_value<double>();
  std::wcout << L"Input t:";
  double t = input_value<double>();

  if (a * b * c > r * s * t) {
    std::wcout << L"Package doesn't fit!\n";
    return;
  }

  std::vector<double> box = { a, b, c };
  std::sort(box.begin(), box.end(), std::greater<double>());
  std::vector<double> pkg = { r, s, t };
  std::sort(pkg.begin(), pkg.end(), std::greater<double>());
  if (box[0] <= pkg[0] && box[1] <= pkg[1] && box[2] <= pkg[2]) {
    std::wcout << L"Package does fit!\n";
  } else {
    std::wcout << L"Package doesn't fit!\n";
  }
}

void
seventh_extra()
{
  int xs[4] = { 0, 0, 0, 0 };
  int ys[4] = { 0, 0, 0, 0 };

  for (size_t i = 0; i < 4; i++) {
    std::wcout << L"Input x" << i + 1 << L":";
    xs[i] = input_value<int>();
    std::wcout << L"Input y" << i + 1 << L":";
    ys[i] = input_value<int>();
  }

  int vecs[][2] = {
    { xs[1] - xs[0], ys[1] - ys[0] },
    { xs[2] - xs[1], ys[2] - ys[1] },
    { xs[3] - xs[2], ys[3] - ys[2] },
    { xs[0] - xs[3], ys[0] - ys[3] },
  };

  double vecs_r[] = {
    std::hypot(vecs[0][0], vecs[0][1]),
    std::hypot(vecs[1][0], vecs[1][1]),
    std::hypot(vecs[2][0], vecs[2][1]),
    std::hypot(vecs[3][0], vecs[3][1]),
  };
}

void
eighth_extra()
{}

void
ninth_extra()
{}

void
tenth_extra()
{}
}