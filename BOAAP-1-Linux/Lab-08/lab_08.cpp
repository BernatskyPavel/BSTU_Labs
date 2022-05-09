#include "lab_08.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>

namespace lab_08 {
#pragma region Helpers
#pragma endregion Helpers

#pragma region First_Variant
void
first_variant()
{
  std::wcout << L"First part:\n";
  double h = 0., d = 12.5e-4;
  double a[] = { 0.8, 4., -7., 2., 0.91 };

  h += d;
  for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
    h += (a[i] * a[i]);
  }

  std::wcout << L"Value of h is " << h << L"\nSecond part:\n";

  double x[] = { 1., 2.7, 4.7, 6., 10. };
  size_t x_size = sizeof(x) / sizeof(x[0]);
  double* z = std::max_element(x, x + x_size);
  double y = 0.0;

  for (size_t i = 0; i < 5; i++) {
    y += (x[i] * x[i]);
  }

  std::wcout << L"Value of y is " << y * *z << L" and value of z is " << *z
             << L"\n";
  return;
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  std::wcout << L"First part:\n";
  double g = 1., c = -0.045;
  double b[] = { 0.9, 0.5, -2., -0.1 };
  size_t m = sizeof(b) / sizeof(b[0]);

  for (size_t j = 0; j < m; j++) {
    g *= powf64(b[j] + 1., 2.);
  }
  g *= c;
  std::wcout << L"Value of g is " << g << L"\nSecond part:\n";

  double y[] = { 6., 2., 0.9, 0.1, 5. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* t = std::min_element(y, y + y_size);
  double q = 1.;

  for (size_t i = 0; i < y_size; i++) {
    q *= (y[i] + *t);
  }

  std::wcout << L"Value of q is " << q << L" and value of t is " << *t << L"\n";
  return;
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  std::wcout << L"First part:\n";
  double z = 0.;
  double x[] = { -2., 6., 1.1, 2.7, 4. };
  size_t m = sizeof(x) / sizeof(x[0]);

  z += 8. * x[2];

  for (size_t i = 0; i < m; i++) {
    z += powf64(x[i] - 2., 2.);
  }

  std::wcout << L"Value of z is " << z << L"\nSecond part:\n";

  double x2[] = { 9., 2.7, 4.1, 6., 12. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]);
  double* p = std::max_element(x2, x2 + x_size);
  double y = 0.;

  for (size_t i = 0; i < 5; i++) {
    y += (x2[i] * x2[i] + 1.);
  }

  std::wcout << L"Value of p is " << *p + y << L" and value of y is " << y
             << L"\n";
  return;
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  std::wcout << L"First part:\n";
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
  std::wcout << L"Second part:\n";
  double y[] = { 6., 8., 0.9, 0.2, 4. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* p = std::max_element(y, y + y_size);
  double q = 1.;

  for (size_t i = 0; i < 4; i++) {
    q *= (y[i] + 2 * *p);
  }

  std::wcout << L"Value of q is " << q << L"\n";
  return;
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  std::wcout << L"First part:\n";
  double a = 1.5, b = -4.15;
  double v[] = { 1., 1.5, -4., -1.9, 3. };
  size_t v_size = sizeof(v) / sizeof(v[0]);
  double* w = new double[v_size];
  for (size_t i = 0; i < v_size; i++) {
    *(w + i) = v[i] > 0 ? (a + v[i]) : (b / v[i]);
  }

  double* c = std::max_element(w, w + v_size);
  delete[] w;

  std::wcout << L"Value of c is " << *c << L"\nSecond part:\n";
  double y[] = { 3., -2., 0.9, 0.5, 1. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* p = std::min_element(y, y + y_size);
  double q = 1.;

  for (size_t i = 0; i < y_size; i++) {
    q += (y[i] - 5.);
  }

  std::wcout << L"Value of p is " << *p << L" and value of q is " << q + *p
             << L"\n";
  return;
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  std::wcout << L"First part:\n";
  double a = 0., b = 1.;
  double x[] = { 2.7, -5., 4., 3.5, -7. };
  size_t n = sizeof(x) / sizeof(x[0]);

  for (size_t i = 0; i < n; i++) {
    if (x[i] > 0.) {
      a += x[i];
    } else {
      b *= x[i];
    }
  }

  std::wcout << L"Value of a is " << a << L" and value of b is " << b
             << L"\nSecond part:\n";

  double x2[] = { 5.1, 6.4, 3., 2., 6. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]);
  double* a2 = std::min_element(x2, x2 + x_size);
  double c = *a2;

  for (size_t i = 0; i < x_size; i++) {
    c += x2[i] / (1 + x2[i]);
  }

  std::wcout << L"Value of a is " << *a2 << L" and value of c is " << c
             << L"\n";
  return;
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  std::wcout << L"First part:\n";
  double d = 0.;
  double a[] = { 0.5, 2., 2.5, 1., 0., 8. }, b[] = { 2.3, 4., 0.5, 2., 3., 9. };
  size_t n = sizeof(a) / sizeof(a[0]);

  for (size_t i = 0; i < n; i++) {
    d += (sqrtf64(a[i] + b[i]) / (i + 1));
  }

  std::wcout << L"Value of d is " << d << L"\nSecond part:\n";
  double x[] = { 2., 1.3, 0.4, 5.1, 7. };
  size_t x_size = sizeof(x) / sizeof(x[0]);
  double* a2 = std::min_element(x, x + x_size);

  for (double t = 0.5; t <= 3; t += 0.5) {
    std::wcout << L"Value of t is " << t << L" and value of y is "
               << (t > 2 ? *a2 : cosf64(t * t)) << L"\n";
  }
  return;
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  std::wcout << L"First part:\n";
  double d = 0., c = 0.7;
  double a[] = { 3., 12., -4., 6.2, 3., 0.4 }, b[] = { 19., 1., -24., 4.2, 8. };
  size_t n1 = sizeof(a) / sizeof(a[0]), n2 = sizeof(b) / sizeof(b[0]);

  for (size_t i = 0; i < n1; i++) {
    d += a[i];
  }
  for (size_t i = 0; i < n2; i++) {
    d -= c * powf64(b[i] - 1., 2.);
  }

  std::wcout << L"Value of d is " << d << L"\nSecond part:\n";
  double x[] = { 1., 6.7, 4., 6., 17. };
  size_t x_size = sizeof(x) / sizeof(x[0]);
  double* z = std::min_element(x, x + x_size);
  double y = 0.;

  for (size_t i = 0; i < x_size; i++) {
    y += x[i] * x[i];
  }

  std::wcout << L"Value of z is " << *z + 2 << L" and value of y is "
             << y + *z + 2 << L"\n";
  return;
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  std::wcout << L"First part:\n";
  double d = 5.5e-4;
  double x[] = { 0.7, 6., -7., 9., -4., 1. };

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    std::wcout << L"Value of a[" << i + 1 << L"] is "
               << ((expf64(-x[i]) * sinf64(x[i])) / (sqrtf64(d + cosf64(x[i]))))
               << L"\n";
  }
  std::wcout << L"Second part:\n";
  double y[] = { 3., -2., 0.9, 0.5, 1. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* p = std::min_element(y, y + y_size);
  double q = 1.;

  for (size_t i = 0; i < y_size; i++) {
    q *= (y[i] - 5);
  }

  std::wcout << L"Value of p is " << *p << L" and value of q is " << q + *p
             << L"\n";
  return;
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  std::wcout << L"First part:\n";
  double q = 0.;
  double x[] = { 3., -2., 0.7, -1., -2., 7. },
         y[] = { 1., 5., -1.2, 6., 9., -4. };
  size_t n = sizeof(x) / sizeof(x[0]);

  for (size_t i = 0; i < n; i++) {
    q += (x[i] * y[i]);
  }

  std::wcout << L"Value of q is " << q << L"\nSecond part:\n";

  double x2[] = { 1., 6.7, 4., 6., 17. }, a[] = { 0.4, 8., 15. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]), a_size = sizeof(a) / sizeof(a[0]);
  double* y2 = new double[a_size];
  double sum = 0.;

  for (size_t i = 0; i < x_size; i++) {
    sum += x[i];
  }

  for (size_t i = 0; i < a_size; i++) {
    *(y2 + i) = a[i] + sum;
  }

  std::wcout << L"Value of k is " << *std::max_element(y2, y2 + a_size)
             << L"\n";
  delete[] y2;
  return;
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  std::wcout << L"First part:\n";
  double a = 5.45, mul = 1.;
  double y[] = { 2.1, 7.7, -4., 5., 9. };
  size_t n = sizeof(y) / sizeof(y[0]);

  for (size_t i = 0; i < n; i++) {
    mul *= y[i] / (powf64(i + 1., 2.) + 1.);
  }

  std::wcout << L"Value of q is " << (4. * mul) << L" and value of s is "
             << (2. * a + (4. * mul) * sinf64(a)) << L"\nSecond part:\n";

  double y2[] = { 1.3, 1., 0.9, 0.5, 8. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* p = std::min_element(y2, y2 + y_size);
  double k = 1.;

  for (size_t i = 0; i < 5; i++) {
    k *= (y[i] + *p);
  }

  std::wcout << L"Value of k is " << k << L"\n";
  return;
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  std::wcout << L"First part:\n";
  double z = 0, sum = 0.;
  double x[] = { 1., 2.7, 4.7, 6., 10. };

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    if (z < x[i]) {
      z = x[i];
    }
    sum += (x[i] * x[i]);
  }

  std::wcout << L"Value of z is " << z << L" and value of y is " << (z * sum)
             << L"\nSecond part:\n";

  double x2[] = { 1.1, 6.2, 3., -4., 6., 1. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]);
  double q = 0.45;

  for (size_t i = 0; i < x_size; i++) {
    q += (x2[i] + 1.) / x2[i];
  }

  std::wcout << L"Value of q is " << q << L"\n";
  return;
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  std::wcout << L"First part:\n";
  double q = 0.;
  double y[] = { 5., 7., 0.9, 0.5, 2. };
  size_t y_size = sizeof(y) / sizeof(y[0]);
  double* d = std::min_element(y, y + y_size);

  for (size_t i = 0; i < y_size; i++) {
    q += (4. * y[i] + *d);
  }

  std::wcout << L"Value of d is " << *d << L" and value of q is " << q
             << L"\nSecond part:\n";

  double x[] = { 8., -2.3, -8.4, 5.1, 9. };
  size_t x_size = sizeof(x) / sizeof(x[0]);
  double sum = 0.;
  for (size_t i = 0; i < 5; i++) {
    sum += x[i] * x[i];
  }

  for (double t = 0.5; t <= 3; t += 0.5) {
    std::wcout << L"Value of t is " << t << L" and value of y is "
               << (t > 2 ? sum + t : cosf64(t * t)) << L"\n";
  }
  return;
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  std::wcout << L"First part:\n";
  double c = 10.1, sum = 0.;
  double y[] = { 4., -6., 3., -3., 9., 5. };

  for (size_t i = 0; i < sizeof(y) / sizeof(y[0]); i++) {
    sum += y[i];
  }

  std::wcout << L"Value of z is "
             << (sum > c ? (powf64(sinf64(c), 2.)) : (powf64(cosf64(c), 2.)))
             << L"\nSecond part:\n";

  double x[] = { 9., 1.7, 4., 6., 3. };
  size_t x_size = sizeof(x) / sizeof(x[0]);
  double m = 1. + *std::max_element(x, x + x_size);
  double y2 = 0.;

  for (size_t i = 0; i < 5; i++) {
    y2 += (x[i] * x[i] + m);
  }

  std::wcout << L"Value of m is " << m << L" and value of y is " << y2 << L"\n";

  return;
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  std::wcout << L"First part:\n";
  double t = 0.45, q = 0.;
  double x[] = { 1.1, 6.2, 3., -4., 6., 1. };

  q += t;

  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    q += (x[i] + 1.) / x[i];
  }

  std::wcout << L"Value of q is " << q << L"\nSecond part:\n";

  double x2[] = { 5., 4., 3., 2., 6., 1. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]);
  double* a = std::max_element(x, x + x_size);
  double c = 0.;

  for (size_t i = 0; i < 5; i++) {
    c += *a / (x2[i] + 1.);
  }

  std::wcout << L"Value of a is " << *a << L" and value of c is " << c << L"\n";
  return;
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  std::wcout << L"First part:\n";
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
  std::wcout << L"Second part:\n";

  double x2[] = { 4., 0.3, 4., 1., 7. };
  size_t x_size = sizeof(x2) / sizeof(x2[0]);
  double* max = std::max_element(x2, x2 + x_size);

  for (double t = 0.6; t <= 2; t += 0.2) {
    std::wcout << L"Value of t is " << t << L" and value of z is "
               << (t > 1 ? *max : cosf64(t * t)) << L"\n";
  }
  return;
}
#pragma endregion Sixteenth_Variant
}