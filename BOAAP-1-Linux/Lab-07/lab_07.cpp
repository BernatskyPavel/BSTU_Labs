#include "lab_07.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>

namespace lab_07 {
#pragma region First_Variant
void
first_variant()
{
  double h = 0., d = 12.5e-4;
  double a[] = { 0.8, 4., -7., 2., 0.91 };
  size_t n = 5;

  h += d;
  for (size_t i = 0; i < n; i++) {
    h += (a[i] * a[i]);
  }

  std::wcout << L"Value of h is " << h << L"\n";
  return;
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  double g = 1., c = -0.045;
  double b[] = { 0.9, 0.5, -2., -0.1 };
  size_t m = 4;

  for (size_t j = 0; j < m; j++) {
    g *= powf64(b[j] + 1., 2.);
  }
  g *= c;
  std::wcout << L"Value of g is " << g << L"\n";
  return;
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  double z = 0.;
  double x[] = { -2., 6., 1.1, 2.7, 4. };
  size_t m = 5;

  z += 8. * x[2];

  for (size_t i = 0; i < m; i++) {
    z += powf64(x[i] - 2., 2.);
  }

  std::wcout << L"Value of z is " << z << L"\n";
  return;
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  double g = 0., k = 6., sum = 0.;
  double a[] = { 2.3, 7., -2., -4., 9. };

  for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
    sum += (a[i] / static_cast<double>(i + 1));
  }
  while (k <= 7.) {
    std::wcout << L"Value of k is " << k << L" and value of g is " << (k / sum)
               << L"\n";
    k += 0.2;
  }
  return;
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  double a = 1.5, b = -4.15;
  double v[] = { 1., 1.5, -4., -1.9, 3. };

  for (size_t i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
    std::wcout << L"Value of w[" << i + 1 << L"] is "
               << (v[i] > 0 ? (a + v[i]) : (b / v[i])) << L"\n";
  }

  return;
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  double a = 0., b = 1.;
  double x[] = { 2.7, -5., 4., 3.5, -7. };
  size_t m = 5;

  for (size_t i = 0; i < m; i++) {
    if (x[i] > 0.) {
      a += x[i];
    } else {
      b *= x[i];
    }
  }

  std::wcout << L"Value of a is " << a << L" and value of b is " << b << L"\n";
  return;
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  double d = 0.;
  double a[] = { 0.5, 2., 2.5, 1., 0., 8. }, b[] = { 2.3, 4., 0.5, 2., 3., 9. };
  size_t n = 6;

  for (size_t i = 0; i < n; i++) {
    d += (sqrtf64(a[i] + b[i]) / (i + 1));
  }

  std::wcout << L"Value of d is " << d << L"\n";
  return;
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  double d = 0., c = 0.7;
  double a[] = { 3., 12., -4., 6.2, 3., 0.4 }, b[] = { 19., 1., -24., 4.2, 8. };
  size_t n1 = 6, n2 = 5;

  for (size_t i = 0; i < n1; i++) {
    d += a[i];
  }
  for (size_t i = 0; i < n2; i++) {
    d -= c * powf64(b[i] - 1., 2.);
  }

  std::wcout << L"Value of d is " << d << L"\n";
  return;
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  double d = 5.5e-4;
  double x[] = { 0.7, 6., -7., 9., -4., 1. };

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    std::wcout << L"Value of a[" << i + 1 << L"] is "
               << ((expf64(-x[i]) * sinf64(x[i])) / (sqrtf64(d + cosf64(x[i]))))
               << L"\n";
  }

  return;
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  double q = 0.;
  double x[] = { 3., -2., 0.7, -1., -2., 7. },
         y[] = { 1., 5., -1.2, 6., 9., -4. };
  size_t n = 6;

  for (size_t i = 0; i < n; i++) {
    q += (x[i] * y[i]);
  }

  std::wcout << L"Value of q is " << q << L"\n";
  return;
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  double a = 5.45, mul = 1.;
  double y[] = { 2.1, 7.7, -4., 5., 9. };
  size_t n = 5;

  for (size_t i = 0; i < n; i++) {
    mul *= y[i] / (powf64(i + 1., 2.) + 1.);
  }

  std::wcout << L"Value of q is " << (4. * mul) << L" and value of s is "
             << (2. * a + (4. * mul) * sinf64(a)) << L"\n";
  return;
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  double z = 0, sum = 0.;
  double x[] = { 1., 2.7, 4.7, 6., 10. };

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    if (z < x[i]) {
      z = x[i];
    }
    sum += (x[i] * x[i]);
  }

  std::wcout << L"Value of z is " << z << L" and value of y is " << (z * sum)
             << L"\n";
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  double p = 0, mul = 1.;
  double y[] = { 3., -2., 0.9, 0.5, 1. };

  for (size_t i = 0; i < sizeof(y) / sizeof(y[0]); i++) {
    if (p > y[i]) {
      p = y[i];
    }
    mul *= (y[i] - 5.);
  }

  std::wcout << L"Value of p is " << p << L" and value of q is " << (mul + p)
             << L"\n";
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  double c = 10.1, sum = 0.;
  double y[] = { 4., -6., 3., -3., 9., 5. };

  for (size_t i = 0; i < sizeof(y) / sizeof(y[0]); i++) {
    sum += y[i];
  }

  std::wcout << L"Value of z is "
             << (sum > c ? (powf64(sinf64(c), 2.)) : (powf64(cosf64(c), 2.)))
             << L"\n";
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  double t = 0.45, q = 0.;
  double x[] = { 1.1, 6.2, 3., -4., 6., 1. };

  q += t;

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    q += (x[i] + 1.) / x[i];
  }

  std::wcout << L"Value of q is " << q << L"\n";
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  double t = 0.5, sum = 0.;
  double x[] = { 8., -2.3, -8.4, 5.1, 9. };

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    sum += (x[i] * x[i]);
  }
  while (t <= 3.) {
    std::wcout << L"Value of t is " << t << L" and value of y is "
               << (t > 2 ? (sum + t) : (cosf64(t * t))) << L"\n";
    t += 0.5;
  }

  return;
}
#pragma endregion Sixteenth_Variant
}