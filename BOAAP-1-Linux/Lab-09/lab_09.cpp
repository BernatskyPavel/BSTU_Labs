#include "lab_09.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <wchar.h>

namespace lab_09 {

typedef double (*formula)(double);
typedef double (*derivative_formula)(double, bool);

#pragma region Part_One
double
trapezoidal_rule(formula func, double a, double b, double n = 200.)
{
  double h = (b - a) / n;
  double I = 0., x = a + h;

  for (size_t k = 1; k < n; k++) {
    I += func(x);
    x += h;
  }

  I += (func(a) + func(b)) / 2.;
  I *= h;

  return I;
}

double
simpson_rule(formula func, double a, double b, double n = 200.)
{
  double h = (b - a) / n;
  double I = 0., x = a + h;
  double odd_sum = 0., even_sum = 0.;

  for (size_t j = 1; j <= (n / 2 - 1); j++) {
    even_sum += func(a + 2. * j * h);
  }
  for (size_t j = 1; j <= (n / 2); j++) {
    odd_sum += func(a + (2. * j - 1.) * h);
  }

  I = func(a) + 2. * even_sum + 4. * odd_sum + func(b);

  double intpart = 0.;
  modff64(I, &intpart);

  return intpart * h / 3.;
}

const formula _formulas[] = {
  [](double _x) { return powf64(_x, 3.) - 3.; },
  [](double _x) { return powf64(cosf64(_x), 3.); },
  [](double _x) { return powf64(_x, 3.) + 1.; },
  [](double _x) { return expf64(_x) - 1. / _x; },
  [](double _x) { return 5. - powf64(_x, 2.); },
  [](double _x) { return powf64(_x, 3.) + 1.; },
  [](double _x) { return expf64(_x) + 2.; },
  [](double _x) { return powf64(_x, 3.) - 1.; },
  [](double _x) { return powf64(_x, 3.) + 3.; },
  [](double _x) { return powf64(_x, 2.) - 4.; },
  [](double _x) { return sinf64(_x) + 1.; },
  [](double _x) { return expf64(_x) + 2.; },
  [](double _x) { return powf64(_x, 3.) + 2.; },
  [](double _x) { return powf64(_x, 4.) + 4.; },
  [](double _x) { return powf64(sinf64(_x), 2.) + 1; },
  [](double _x) { return powf64(_x, 2.) + (1. / _x); },
};

const double limits[][2] = {
  { 1., 3. },  { 4., 7. }, { 1., 6. }, { 2., 3. }, { 8., 12. }, { 1., 5. },
  { 5., 11. }, { 0., 3. }, { 3., 6. }, { 4., 8. }, { 1., 3. },  { 5., 11. },
  { 8., 14. }, { 1., 4. }, { 2., 7. }, { 0., 4. },
};

void
part_one(size_t index)
{

  if (index > sizeof(_formulas) / sizeof(_formulas[0])) {
    std::wcout << L"Part one: No such index error!\n";
    return;
  }

  std::wcout << L"Part one:\n";
  double tr_I = trapezoidal_rule(
           _formulas[index - 1], limits[index - 1][0], limits[index - 1][1]),
         sm_I = simpson_rule(
           _formulas[index - 1], limits[index - 1][0], limits[index - 1][1]);
  std::wcout << L"The integral value calculated by the trapezoidal rule is "
             << tr_I
             << L"\nThe integral value calculated by the Simpson's rule is "
             << sm_I << L"\n";
}
#pragma endregion Part_One

#pragma region Part_Two
double
newton_raphson_method(derivative_formula func, double a, double eps = 1e-4)
{
  double xprev, x = a;
  do {
    xprev = x;
    x = xprev - func(xprev, false) / func(xprev, true);
  } while (fabsf64(x - xprev) >= eps);

  return x;
}

double
dichotomy_method(derivative_formula func, double a, double b, double eps = 1e-4)
{
  if (fabsf64(func(a, false)) == 0.) {
    return a;
  }
  if (fabsf64(func(b, false)) == 0.) {
    return b;
  }
  double left = std::min(a, b), right = std::max(a, b);
  if (!std::isfinite(func(left, false))) {
    left += (eps * (left < 0 ? -1. : 1.));
  }
  if (!std::isfinite(func(right, false))) {
    right += (eps * (right <= 0 ? -1. : 1.));
  }
  bool left_sign = std::signbit(func(left, false)),
       right_sign = std::signbit(func(right, false));
  double c = 0;
  while (true) {
    c = (left + right) / 2.;
    double temp = func(c, false);
    if (fabsf64(temp) <= eps) {
      break;
    }
    bool temp_sign = std::signbit(temp);
    if (temp_sign == left_sign) {
      left_sign = temp_sign;
      left = c;
    }
    if (temp_sign == right_sign) {
      right_sign = temp_sign;
      right = c;
    }
  }

  return c;
}

const derivative_formula _formulas_and_derivatives[] = {
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 1.;
    else
      return powf64(_x, 3.) + _x - 3.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return -sinf64(_x) + 1.;
    else
      return cosf64(_x) + _x - 7.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 2.;
    else
      return powf64(_x, 3.) + 2. * _x - 1.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return expf64(_x) + 1. / powf64(_x, 2.);
    else
      return expf64(_x) - 3. - 1. / _x;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return -2. * _x + 1.;
    else
      return 2. - powf64(_x, 2.) + _x;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 5. + 3. * powf64(_x, 2.);
    else
      return 5. * _x - 1. + powf64(_x, 3.);
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return expf64(_x) + 1.;
    else
      return expf64(_x) + _x - 4.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 1.;
    else
      return powf64(_x, 3.) + _x - 2.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 3.;
    else
      return powf64(_x, 3.) + 3. * _x - 1.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 1.;
    else
      return powf64(_x, 3.) + _x - 4.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return cosf64(_x) + 3. * powf64(_x, 2.);
    else
      return sinf64(_x) + powf64(_x, 3.);
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return expf64(_x) + 4. * _x;
    else
      return expf64(_x) + 2. * powf64(_x, 2.) - 3.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 2. + 3. * powf64(_x, 2.);
    else
      return 2. * _x + powf64(_x, 3.) - 7.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 3. * powf64(_x, 2.) + 2.;
    else
      return powf64(_x, 3.) + 2. * _x - 4.;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return cosf64(_x) + 1.;
    else
      return sinf64(_x) + 2. + _x;
  },
  [](double _x, bool is_derivative) {
    if (is_derivative)
      return 2. * _x + 4.;
    else
      return powf64(_x, 2.) + 4. * _x - 2.;
  }
};

const double xs[] = { 1., 6., 0., -1., -1., 0., 1.,  1.,
                      0., 1., 0., -2., 1.,  1., -2., -5. };

void
part_two(size_t index)
{
  if (index > sizeof(_formulas_and_derivatives) /
                sizeof(_formulas_and_derivatives[0])) {
    std::wcout << L"Part two: No such index error!\n";
    return;
  }
  std::wcout << L"Part two:\n";
  double nt_I = newton_raphson_method(_formulas_and_derivatives[index - 1],
                                      xs[index - 1]),
         dh_I = dichotomy_method(_formulas_and_derivatives[index - 1],
                                 xs[index - 1],
                                 xs[index - 1] + 1.);
  std::wcout << L"The root of continious function calculated by the "
                L"Newton-Raphson method is "
             << nt_I
             << L"\nThe root of continious function calculated by the "
                L"dichotomy method is "
             << dh_I << L"\n";
  return;
}
#pragma endregion Part_Two
void
general_call(size_t index)
{
  part_one(index);
  part_two(index);
}
#pragma region First_Variant
void
first_variant()
{
  part_one(1);
  part_two(1);
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  part_one(2);
  part_two(2);
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  part_one(3);
  part_two(3);
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  part_one(4);
  part_two(4);
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  part_one(5);
  part_two(5);
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  part_one(6);
  part_two(6);
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  part_one(7);
  part_two(7);
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  part_one(8);
  part_two(8);
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  part_one(9);
  part_two(9);
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  part_one(10);
  part_two(10);
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  part_one(11);
  part_two(11);
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  part_one(12);
  part_two(12);
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  part_one(13);
  part_two(13);
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  part_one(14);
  part_two(14);
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  part_one(15);
  part_two(15);
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  part_one(16);
  part_two(16);
}
#pragma endregion Sixteenth_Variant
}