#include "extra.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>

namespace extra {
#pragma region Helpers
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

double
scalar_multiple(int a[2], int b[2])
{
  return fabs(static_cast<double>(a[0]) * static_cast<double>(b[0]) +
              static_cast<double>(a[1]) * static_cast<double>(b[1]));
}

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
#pragma endregion Helpers
#pragma region First_Extra
void
first_extra()
{
  std::wcout << L"Input a:";
  int a = input_value<int>();
  std::wcout << L"Input b:";
  int b = input_value<int>();
  std::wcout << L"Input c:";
  int c = input_value<int>();

  int sum = 0;

  sum += a % 5 == 0 ? a : 0;
  sum += b % 5 == 0 ? b : 0;
  sum += c % 5 == 0 ? c : 0;

  if (sum == 0) {
    std::wcout << L"Sum: Error\n";
  } else {
    std::wcout << L"Sum: " << sum << L'\n';
  }
  return;
}
#pragma endregion First_Extra
#pragma region Second_Extra
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
#pragma endregion Second_Extra
#pragma region Third_Extra
void
third_extra()
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
#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
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
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra
void
fifth_extra()
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
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
{
  std::wcout << L"Input Rook column:";
  wchar_t r_col = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input Rook row:";
  int r_row = input_value<int>(InputRules::chess_row);
  std::wcout << L"Input Bishop column:";
  wchar_t b_col = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input Bishop row:";
  int b_row = input_value<int>(InputRules::chess_row);
  std::wcout << L"Input King column:";
  wchar_t k_col = input_value<wchar_t>(InputRules::chess_col);
  std::wcout << L"Input King row:";
  int k_row = input_value<int>(InputRules::chess_row);

  if ((r_col == k_col && r_row == k_row) ||
      (b_col == k_col && b_row == k_row) ||
      (r_col == b_col && r_row == b_row)) {
    std::wcout << L"Invalid input: Overlapped figures!\n";
    return;
  }

  bool is_danger_from_rook = false, is_danger_from_bishop = false;

  is_danger_from_rook = (r_col == k_col) || (r_row == k_row);
  is_danger_from_bishop =
    (abs(static_cast<short>(b_col) - static_cast<short>(k_col)) ==
     abs(b_row - k_row));
  if (is_danger_from_bishop && is_danger_from_rook) {
    std::wcout << L"Danger for king from both figures!\n";
  } else if (is_danger_from_bishop) {
    std::wcout << L"Danger for king from Bishop!\n";
  } else if (is_danger_from_rook) {
    std::wcout << L"Danger for king from Rook!\n";
  } else {
    std::wcout << L"No danger for king!\n";
  }
}
#pragma endregion Sixth_Extra
#pragma region Seventh_Extra
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

  if ((xs[0] == xs[2] && ys[0] == ys[2]) ||
      (xs[1] == xs[2] && ys[1] == ys[2]) ||
      (xs[0] == xs[3] && ys[0] == ys[3]) ||
      (xs[1] == xs[3] && ys[1] == ys[3])) {
    std::wcout << L"Two vectors are criss crossing each other!\n";
    return;
  }

  int xa1_min = std::min(xs[0], xs[1]), xa1_max = std::max(xs[0], xs[1]),
      xa2_min = std::min(xs[2], xs[3]), xa2_max = std::max(xs[2], xs[3]);

  int xa_min = std::max(xa1_min, xa2_min), xa_max = std::min(xa1_max, xa2_max);

  if (xa1_max < xa2_min) {
    std::wcout << L"Two vectors aren't criss crossing each other!\n";
    return;
  }

  double a1 = static_cast<double>(ys[0] - ys[1]) /
              static_cast<double>(xs[0] - xs[1]),
         a2 = static_cast<double>(ys[2] - ys[3]) /
              static_cast<double>(xs[2] - xs[3]);
  double b1 = ys[0] - a1 * xs[0], b2 = ys[2] - a2 * xs[2];

  double xa = (b2 - b1) / (a1 - a2);
  if (xa < xa_min || xa > xa_max) {
    std::wcout << L"Two vectors aren't criss crossing each other!\n";
  } else {
    std::wcout << L"Two vectors are criss crossing each other!\n";
  }
}
#pragma endregion Seventh_Extra
#pragma region Old_Seventh_Extra
void
old_seventh_extra()
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

  bool collinearity[] = {
    fabs(scalar_multiple(vecs[0], vecs[2]) - fabs(vecs_r[0] * vecs_r[2])) <
      1e-14,
    fabs(scalar_multiple(vecs[1], vecs[3]) - fabs(vecs_r[1] * vecs_r[3])) <
      1e-14,
  };

  if (collinearity[0] && collinearity[1]) {
    if (scalar_multiple(vecs[0], vecs[1]) == 0) {
      if (vecs_r[0] == vecs_r[1]) {
        if (vecs_r[0] != vecs_r[3]) {
          std::wcout << L"Shape: RHOMBUS!\n";
        } else {
          std::wcout << L"Shape: SQUARE!\n";
        }
        return;
      } else if (vecs_r[0] == vecs_r[2] && vecs_r[1] == vecs_r[3]) {
        std::wcout << L"Shape: RECTANGLE!\n";
        return;
      }
      std::wcout << L"Shape: ?!\n";
    } else {
      if (vecs_r[0] == vecs_r[1]) {
        std::wcout << L"Shape: RHOMBUS!\n";
      } else {
        std::wcout << L"Shape: PARALLELOGRAM!\n";
      }
      return;
    }
  } else if (collinearity[0] || collinearity[1]) {
    std::wcout << L"Shape: TRAPEZOID!\n";
    return;
  } else {
    std::wcout << L"Shape: IRREGULAR!\n";
    return;
  }
}
#pragma endregion Old_Seventh_Extra
}