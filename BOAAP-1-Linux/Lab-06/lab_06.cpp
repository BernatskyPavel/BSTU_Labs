#include "lab_06.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>

namespace lab_06 {

#pragma region First_Variant

#define C 2.1
#define R 4e-4
#define M 7.

double
first_variant_first_formula(double r, double j, double c, double m)
{
  return (10. * r - j) / (powf64(c, 2.) + expf64(-m));
}

double
first_variant_second_formula(double h, double j, double c, double m)
{
  return (h * m - powf64(j, 2.)) + powf64(0.1 * c, 2.);
}

void
first_variant()
{
  double js[] = { 4.2, 0.3, 1.7 };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double h = first_variant_first_formula(R, js[i], C, M);
    double y = first_variant_second_formula(h, js[i], C, M);
    std::wcout << L"h = " << h << L", y = " << y << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 0.;
  while (j <= 1.7) {
    double h = first_variant_first_formula(R, j, C, M);
    double y = first_variant_second_formula(h, j, C, M);
    std::wcout << L"h = " << h << L", y = " << y << L"\n";
    j += 0.1;
  }

  std::wcout << L"Cycle Double For results:\n";
  double js_two[] = { 9., 1.8, 15., -3. };
  for (size_t i = 0; i < sizeof(js_two) / sizeof(double); i++) {
    for (double m = 1.0; m <= 2.; m += 0.5) {
      double h = first_variant_first_formula(R, js_two[i], C, m);
      double y = first_variant_second_formula(h, js_two[i], C, m);
      std::wcout << L"h = " << h << L", y = " << y << L"\n";
    }
  }
}

#undef C
#undef R
#undef M

#pragma endregion First_Variant
#pragma region Second_Variant

#define A 2e-3
#define B 8.5
#define N 2.

double
second_variant_first_formula(double i, double b, double a)
{
  return sqrtf64(i * b - b * b * a);
}

double
second_variant_second_formula(double y, double n, double b)
{
  return y * tanf64(n / 4.) - expf64(1. + b);
}

void
second_variant()
{
  double is[] = { 2., 1., 8.3 };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(is) / sizeof(double); i++) {
    double y = second_variant_first_formula(is[i], B, A);
    double z = second_variant_second_formula(y, N, B);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double i = 1.;
  while (i <= 3.) {
    double y = second_variant_first_formula(i, B, A);
    double z = second_variant_second_formula(y, N, B);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
    i += 0.5;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ns[] = { 3., -6., 0.2, 2.8 };
  for (size_t n = 0; n < sizeof(ns) / sizeof(double); n++) {
    for (double b = 2.; b <= 3.; b += 0.5) {
      double y = second_variant_first_formula(i, b, A);
      double z = second_variant_second_formula(y, n, b);
      std::wcout << L"y = " << y << L", z = " << z << L"\n";
    }
  }
}

#undef A
#undef B
#undef N

#pragma endregion Second_Variant
#pragma region Third_Variant

#define Y -1.55
#define A 6.

double
third_variant_first_formula(double a, double j, double y)
{
  return sqrtf64(a + 1.) - tanf64(j + y);
}

double
third_variant_second_formula(double j, double y, double z)
{
  return expf64(-j * 0.1 * y) + powf64(3. * z, 2.);
}

void
third_variant()
{
  double js[] = { 8., -0.6, 1., 6.4 };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double z = third_variant_first_formula(A, js[i], Y);
    double q = third_variant_second_formula(js[i], Y, z);
    std::wcout << L"z = " << z << L", q = " << q << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = -1.;
  while (j <= 1.) {
    double z = third_variant_first_formula(A, j, Y);
    double q = third_variant_second_formula(j, Y, z);
    std::wcout << L"z = " << z << L", q = " << q << L"\n";
    j += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ys[] = { 3.3, -4., 0.9 };
  for (size_t n = 0; n < sizeof(ys) / sizeof(double); n++) {
    for (double a = 1.; a <= 2.; a += 0.2) {
      double z = third_variant_first_formula(a, j, ys[n]);
      double q = third_variant_second_formula(j, ys[n], z);
      std::wcout << L"z = " << z << L", q = " << q << L"\n";
    }
  }
}

#undef Y
#undef A

#pragma endregion Third_Variant
#pragma region Fourth_Variant

#define B 2.5
#define M 3.
#define A 1.4e-3

double
fourth_variant_first_formula(double m, double j, double a)
{
  return (m * j) / tanf64(a) - expf64(10. * m);
}

double
fourth_variant_second_formula(double y, double b, double a)
{
  return 2. * y * b + sqrtf64(a + b);
}

void
fourth_variant()
{
  double js[] = { 0.7, -2., 2.9 };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double y = fourth_variant_first_formula(M, js[i], A);
    double z = fourth_variant_second_formula(y, B, A);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = B;
  while (j <= 3.) {
    double y = fourth_variant_first_formula(M, j, A);
    double z = fourth_variant_second_formula(y, B, A);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
    j += 0.1;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ys[] = { 0.3, 1., 0.7, 4. };
  double ms[] = { 7.3, -2., 0.8 };
  for (size_t n = 0; n < sizeof(ys) / sizeof(double); n++) {
    for (size_t k = 0; k < sizeof(ms) / sizeof(double); k++) {
      double y = fourth_variant_first_formula(ms[k], j, A);
      double z = fourth_variant_second_formula(ys[n], B, A);
      std::wcout << L"y = " << y << L", z = " << z << L"\n";
    }
  }
}

#undef B
#undef M
#undef A

#pragma endregion Fourth_Variant
#pragma region Fifth_Variant

#define Y 1.6e-4
#define X -1.
#define K 6.

double
fifth_variant_first_formula(double i, double k, double y)
{
  return i / k - sqrtf64(y) / 0.4;
}

double
fifth_variant_second_formula(double c, double x)
{
  return expf64(1. - c) + 4.9 * (x * x + 1.);
}

void
fifth_variant()
{
  double is[] = { 0.9, 8.4, 2. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(is) / sizeof(double); i++) {
    double c = fifth_variant_first_formula(is[i], K, Y);
    double d = fifth_variant_second_formula(c, X);
    std::wcout << L"c = " << c << L", d = " << d << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double i = 0.;
  while (i <= 3.) {
    double c = fifth_variant_first_formula(i, K, Y);
    double d = fifth_variant_second_formula(c, X);
    std::wcout << L"c = " << c << L", d = " << d << L"\n";
    i += 0.5;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ys[] = { 1.3, -8., 0.2 };
  for (size_t n = 0; n < sizeof(ys) / sizeof(double); n++) {
    for (double x = 1.; x <= 2.; x += 0.1) {
      double c = fifth_variant_first_formula(i, K, ys[n]);
      double d = fifth_variant_second_formula(c, x);
      std::wcout << L"c = " << c << L", d = " << d << L"\n";
    }
  }
}

#undef Y
#undef X
#undef K

#pragma endregion Fifth_Variant
#pragma region Sixth_Variant

#define B -5.4
#define M 4.
#define U 0.05e-4

double
sixth_variant_first_formula(double u, double b, double k, double m)
{
  return u + b - 2. * sqrtf64(0.7 * k + m);
}

double
sixth_variant_second_formula(double u)
{
  return 100. * expf64(-0.2 * u) - logf64(8.1 * u);
}

void
sixth_variant()
{
  double ks[] = { 0.9, 8.4, 2. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(ks) / sizeof(double); i++) {
    double v = sixth_variant_first_formula(U, B, ks[i], M);
    double w = sixth_variant_second_formula(U);
    std::wcout << L"v = " << v << L", w = " << w << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double k = 3.;
  while (k <= 4.) {
    double v = sixth_variant_first_formula(U, B, k, M);
    double w = sixth_variant_second_formula(U);
    std::wcout << L"v = " << v << L", w = " << w << L"\n";
    k += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ms[] = { -1.3, -2., 4.9 };
  for (size_t n = 0; n < sizeof(ms) / sizeof(double); n++) {
    for (double b = 7.; b <= 8.; b += 0.2) {
      double v = sixth_variant_first_formula(U, b, k, ms[n]);
      double w = sixth_variant_second_formula(U);
      std::wcout << L"v = " << v << L", w = " << w << L"\n";
    }
  }
}

#undef B
#undef M
#undef U

#pragma endregion Sixth_Variant
#pragma region Seventh_Variant

#define X 0.9
#define Y 2.
#define T 6.96e-5

double
seventh_variant_first_formula(double t, double y, double i, double x)
{
  return t * y * y - sqrtf64(i + x) * tanf64(y);
}

double
seventh_variant_second_formula(double z, double y)
{
  return sqrtf64(z * (z + 5.)) * logf64(y);
}

void
seventh_variant()
{
  double is[] = { 9., -1.4, 5. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(is) / sizeof(double); i++) {
    double z = seventh_variant_first_formula(T, Y, is[i], X);
    double q = seventh_variant_second_formula(z, Y);
    std::wcout << L"z = " << z << L", q = " << q << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double i = 1.;
  while (i <= 2.) {
    double z = seventh_variant_first_formula(T, Y, i, X);
    double q = seventh_variant_second_formula(z, Y);
    std::wcout << L"z = " << z << L", q = " << q << L"\n";
    i += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double xs[] = { -1.3, -2., 4.9 };
  for (size_t n = 0; n < sizeof(xs) / sizeof(double); n++) {
    for (double t = 7.; t <= 8.; t += 0.2) {
      double z = seventh_variant_first_formula(t, Y, i, xs[n]);
      double q = seventh_variant_second_formula(z, Y);
      std::wcout << L"z = " << z << L", q = " << q << L"\n";
    }
  }
}

#undef X
#undef Y
#undef T

#pragma endregion Seventh_Variant
#pragma region Eighth_Variant

#define Y 5.
#define T -7.4
#define N 9.

double
eighth_variant_first_formula(double j, double t, double y, double n)
{
  return 0.6 * j + expf64(t * j) * powf64(4.0 * y / n, 2.0);
}

double
eighth_variant_second_formula(double w, double t, double n)
{
  return sqrtf64(w - 0.1 * t) / (2.0 + n * n);
}

void
eighth_variant()
{
  double js[] = { 0.5, 8.4, 0.3 };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double w = eighth_variant_first_formula(js[i], T, Y, N);
    double s = eighth_variant_second_formula(w, T, N);
    std::wcout << L"w = " << w << L", s = " << s << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 1.;
  while (j <= 2.) {
    double w = eighth_variant_first_formula(j, T, Y, N);
    double s = eighth_variant_second_formula(w, T, N);
    std::wcout << L"w = " << w << L", s = " << s << L"\n";
    j += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ys[] = { 0.1, -3., 0.5 };
  for (size_t n = 0; n < sizeof(ys) / sizeof(double); n++) {
    for (double j = 0.1; j <= 0.4; j += 0.1) {
      double w = eighth_variant_first_formula(j, T, ys[n], N);
      double s = eighth_variant_second_formula(w, T, N);
      std::wcout << L"w = " << w << L", s = " << s << L"\n";
    }
  }
}

#undef Y
#undef T
#undef N

#pragma endregion Eighth_Variant
#pragma region Ninth_Variant

#define S 5.9
#define M 6.
#define F 1.2e-3

double
ninth_variant_first_formula(double s, double c, double f)
{
  return (s + c) / logf64(f) / expf64(-s);
}

double
ninth_variant_second_formula(double y, double m)
{
  return (y - m) / logf64(y);
}

void
ninth_variant()
{
  double cs[] = { 2., 0.5, -4. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(cs) / sizeof(double); i++) {
    double y = ninth_variant_first_formula(S, cs[i], F);
    double h = ninth_variant_second_formula(y, M);
    std::wcout << L"y = " << y << L", h = " << h << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double c = 0.;
  while (c <= 0.9) {
    double y = ninth_variant_first_formula(S, c, F);
    double h = ninth_variant_second_formula(y, M);
    std::wcout << L"y = " << y << L", h = " << h << L"\n";
    c += 0.1;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ss[] = { 0.1, -3., 0.5 };
  for (size_t n = 0; n < sizeof(ss) / sizeof(double); n++) {
    for (double j = 0.2; j <= 0.5; j += 0.1) {
      double y = ninth_variant_first_formula(ss[n], c, F);
      double h = ninth_variant_second_formula(y, M);
      std::wcout << L"y = " << y << L", h = " << h << L"\n";
    }
  }
}

#undef S
#undef M
#undef F

#pragma endregion Ninth_Variant
#pragma region Tenth_Variant

#define S 7.4
#define M 10.
#define F 3.2e-4

double
tenth_variant_first_formula(double s, double f)
{
  return s / logf64(5.2 * f) / (expf64(-s) + 2.);
}

double
tenth_variant_second_formula(double m, double y, double k)
{
  return (1. + m * (y - k)) / logf64(y);
}

void
tenth_variant()
{
  double ks[] = { 4., 0.5, 8. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(ks) / sizeof(double); i++) {
    double y = tenth_variant_first_formula(S, F);
    double v = tenth_variant_second_formula(M, y, ks[i]);
    std::wcout << L"y = " << y << L", v = " << v << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double k = 0.;
  while (k <= 0.4) {
    double y = tenth_variant_first_formula(S, F);
    double v = tenth_variant_second_formula(M, y, k);
    std::wcout << L"y = " << y << L", v = " << v << L"\n";
    k += 0.5;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ks2[] = { 0.1, -3., 0.5 };
  for (size_t n = 0; n < sizeof(ks2) / sizeof(double); n++) {
    for (double m = 0.3; m <= 0.7; m += 0.1) {
      double y = tenth_variant_first_formula(S, F);
      double v = tenth_variant_second_formula(m, y, ks2[n]);
      std::wcout << L"y = " << y << L", v = " << v << L"\n";
    }
  }
}

#undef S
#undef M
#undef F

#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant

#define A -1.4
#define M 16.

double
eleventh_variant_first_formula(double a, double m)
{
  return tanf64(a / 3.) + expf64(a / m);
}

double
eleventh_variant_second_formula(double w, double j, double a)
{
  return 0.9 * sqrtf64(w + j) + fabsf64(a * a - 1.);
}

void
eleventh_variant()
{
  double js[] = { 0.5, 9.1, 5. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double w = eleventh_variant_first_formula(A, M);
    double r = eleventh_variant_second_formula(w, js[i], A);
    std::wcout << L"w = " << w << L", r = " << r << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 1.8;
  while (j <= 3.) {
    double w = eleventh_variant_first_formula(A, M);
    double r = eleventh_variant_second_formula(w, j, A);
    std::wcout << L"w = " << w << L", r = " << r << L"\n";
    j += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double as[] = { 0.2, -4., 0.6 };
  for (size_t n = 0; n < sizeof(js) / sizeof(double); n++) {
    for (double j = 0.1; j <= 0.4; j += 0.1) {
      double w = eleventh_variant_first_formula(as[n], M);
      double r = eleventh_variant_second_formula(w, j, as[n]);
      std::wcout << L"w = " << w << L", r = " << r << L"\n";
    }
  }
}

#undef A
#undef M

#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant

#define B 0.5
#define M 8.
#define A 2.4e-4

double
twelfth_variant_first_formula(double m, double b, double a)
{
  return (m - b) / (sinf64(a) - expf64(a));
}

double
twelfth_variant_second_formula(double y, double a, double j, double b)
{
  return 3. * y + sqrtf64(a - 4. * j * b);
}

void
twelfth_variant()
{
  double js[] = { 1.7, 2.9, -8. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double y = twelfth_variant_first_formula(M, B, A);
    double z = twelfth_variant_second_formula(y, A, js[i], B);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 2.;
  while (j <= 3.) {
    double y = twelfth_variant_first_formula(M, B, A);
    double z = twelfth_variant_second_formula(y, A, j, B);
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
    j += 0.5;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ms[] = { 0.4, -1., 1.9 };
  for (size_t n = 0; n < sizeof(js) / sizeof(double); n++) {
    for (double b = 2.; b <= 3.; b += 0.5) {
      double y = twelfth_variant_first_formula(ms[n], b, A);
      double z = twelfth_variant_second_formula(y, A, j, b);
      std::wcout << L"y = " << y << L", z = " << z << L"\n";
    }
  }
}

#undef B
#undef M
#undef A

#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant

#define A 8.
#define M 6.
#define B 5e-3

double
thirteenth_variant_first_formula(double k, double a, double m, double b)
{
  return sinf64(k / a) / cosf64(m * b);
}

double
thirteenth_variant_second_formula(double d, double k)
{
  return d / (d * d + 1) / (1. - expf64(k));
}

void
thirteenth_variant()
{
  double ks[] = { 1.6, 9.1, -8. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(ks) / sizeof(double); i++) {
    double d = thirteenth_variant_first_formula(ks[i], A, M, B);
    double c = thirteenth_variant_second_formula(d, ks[i]);
    std::wcout << L"d = " << d << L", c = " << c << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double k = A;
  while (k <= 3.) {
    double d = thirteenth_variant_first_formula(k, A, M, B);
    double c = thirteenth_variant_second_formula(d, k);
    std::wcout << L"d = " << d << L", c = " << c << L"\n";
    k -= 0.5;
  }

  std::wcout << L"Cycle Double For results:\n";
  double ks2[] = { 1.7, 5., -2. };
  for (size_t n = 0; n < sizeof(ks2) / sizeof(double); n++) {
    for (double a = 2.; a <= 2.8; a += 0.2) {
      double d = thirteenth_variant_first_formula(ks2[n], a, M, B);
      double c = thirteenth_variant_second_formula(d, ks[n]);
      std::wcout << L"d = " << d << L", c = " << c << L"\n";
    }
  }
}

#undef A
#undef M
#undef B

#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant

#define B 2.
#define J 6.
#define A 1.5e-8

double
fourteenth_variant_first_formula(double a, double b, double j, double i)
{
  return a / (b + expf64(b)) / (1. + j * i);
}

double
fourteenth_variant_second_formula(double y, double j)
{
  return cosf64(y + 1.) / sqrtf64(fabsf64(-2. * j));
}

void
fourteenth_variant()
{
  double is[] = { 7., 4., 2., 6. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(is) / sizeof(double); i++) {
    double y = fourteenth_variant_first_formula(A, B, J, is[i]);
    double t = fourteenth_variant_second_formula(y, J);
    std::wcout << L"y = " << y << L", t = " << t << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double i = 3.;
  while (i <= 2.) {
    double y = fourteenth_variant_first_formula(A, B, J, i);
    double t = fourteenth_variant_second_formula(y, J);
    std::wcout << L"y = " << y << L", t = " << t << L"\n";
    i -= 0.1;
  }

  std::wcout << L"Cycle Double For results:\n";
  double as[] = { 0.1, -1., 3. };
  for (size_t n = 0; n < sizeof(is) / sizeof(double); n++) {
    for (double b = 2.4; b <= 3.; b += 0.2) {
      double y = fourteenth_variant_first_formula(as[n], b, J, i);
      double t = fourteenth_variant_second_formula(y, J);
      std::wcout << L"y = " << y << L", t = " << t << L"\n";
    }
  }
}

#undef B
#undef J
#undef A

#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant

#define A -1.
#define Y 0.4
#define T 5e-5

double
fifteenth_variant_first_formula(double t, double a, double y, double j)
{
  return sqrtf64(t * a + y) + 4 * expf64(-2.0 * j);
}

double
fifteenth_variant_second_formula(double y, double a, double z)
{
  return logf64(0.4 * y) / (7.0 * a - z);
}

void
fifteenth_variant()
{
  double js[] = { 5., 3., 1., 7., 3. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double z = fifteenth_variant_first_formula(T, A, Y, js[i]);
    double w = fifteenth_variant_second_formula(Y, A, z);
    std::wcout << L"z = " << z << L", w = " << w << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 1.;
  while (j <= 2.) {
    double z = fifteenth_variant_first_formula(T, A, Y, j);
    double w = fifteenth_variant_second_formula(Y, A, z);
    std::wcout << L"z = " << z << L", w = " << w << L"\n";
    j += 0.2;
  }

  std::wcout << L"Cycle Double For results:\n";
  double as[] = { 0.2, -1.6, 9.4 };
  for (size_t n = 0; n < sizeof(js) / sizeof(double); n++) {
    for (double t = 2.4; t <= 3.; t += 0.2) {
      double z = fifteenth_variant_first_formula(t, as[n], Y, j);
      double w = fifteenth_variant_second_formula(Y, as[n], z);
      std::wcout << L"z = " << z << L", w = " << w << L"\n";
    }
  }
}

#undef A
#undef Y
#undef T

#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant

#define A -1.4
#define M 6.
#define T 15e-5

double
sixteenth_variant_first_formula(double a, double t, double m)
{
  return cosf64(a / 3.) + t + expf64(a / m);
}

double
sixteenth_variant_second_formula(double w, double j, double a)
{
  return 0.7 * sqrtf64(3. * w + j) + fabsf64(a * a - 1.);
}

void
sixteenth_variant()
{
  double js[] = { 0.5, 9.1, 5. };
  std::wcout << L"Cycle For results:\n";
  for (size_t i = 0; i < sizeof(js) / sizeof(double); i++) {
    double w = sixteenth_variant_first_formula(A, T, M);
    double r = sixteenth_variant_second_formula(w, js[i], A);
    std::wcout << L"w = " << w << L", r = " << r << L"\n";
  }

  std::wcout << L"Cycle While results:\n";
  double j = 1.;
  while (j <= 2.) {
    double w = sixteenth_variant_first_formula(A, T, M);
    double r = sixteenth_variant_second_formula(w, j, A);
    std::wcout << L"w = " << w << L", r = " << r << L"\n";
    j += 0.1;
  }

  std::wcout << L"Cycle Double For results:\n";
  double as[] = { 0.2, -1.6, 9.4 };
  for (size_t n = 0; n < sizeof(js) / sizeof(double); n++) {
    for (double m = 2.4; m <= 3.; m += 0.2) {
      double w = sixteenth_variant_first_formula(as[n], T, m);
      double r = sixteenth_variant_second_formula(w, j, as[n]);
      std::wcout << L"w = " << w << L", r = " << r << L"\n";
    }
  }
}

#undef A
#undef M
#undef T

#pragma endregion Sixteenth_Variant
}