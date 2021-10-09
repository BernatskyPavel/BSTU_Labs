#include "lab_06.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <wchar.h>

namespace lab_06 {
#pragma region Helpers
template<typename T>
T
input_value()
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
    }
    break;
  }
  return temp;
}

uint
sum_of_digits(uint number)
{
  std::wstring s_number = std::to_wstring(number);
  int result = 0;
  for (auto iterator = s_number.cbegin(); iterator != s_number.cend();
       iterator++) {
    wchar_t temp = *iterator;
    result += (int)(temp - L'0');
  }
  return result;
}

int
gcd(int a, int b)
{
  while (a != 0) {
    int old_a = a;
    a = b % a;
    b = old_a;
  }
  return abs(b);
}
#pragma endregion Helpers
#pragma region First_Variant
void
first_variant()
{
  std::wcout << L"First part:\n";
  double a = 1.774, m = 5.;
  for (double x = 3.; x <= 5.; x += 0.2) {
    double y = sqrtf64(a + m * m * x * x) / (a + x) * m;
    double z = (fabsf64(y) < 1.) ? (y + 1.) : (powf64(sinf64(y), 2.));
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  for (int i = 1; i <= 9; i += 1) {
    for (int j = 0; j <= 9; j += 1) {
      for (int k = 0; k <= 9; k += 1) {
        if (i != j && i != k && j != k) {
          std::wcout << i << j << k << L" ";
        }
      }
    }
    std::wcout << L"\n";
  }
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  std::wcout << L"First part:\n";
  double b = -0.05, a = 1.72;
  for (double i = -5.; i <= 5.; i += 2.) {
    double d = (i > 3. * b) ? (a + b * i) : (tanf64(b) - a * i);
    double z = (d * a / 4.) / (3. * a * b - expf64(1. + d) / 100.);
    std::wcout << L"d = " << d << L", z = " << z << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  int sum = 0;

  for (int i = 1; i < 200; i += 1) {
    if (i % 3 == 0) {
      sum += i;
    }
  }

  std::wcout << L"Sum of numbers dividable by 3 and lower than 200 is " << sum
             << L"\n";
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  std::wcout << L"First part:\n";
  double a = 105e-4, m = 4., i = 7.;
  double x[] = { 8., 1.9, -4., 1. };
  for (size_t j = 0; j < sizeof(x) / sizeof(x[0]); j++) {
    double s = expf64(-a * x[j]) - logf64(i / x[j] * m) / powf64(logf64(m), 2.);
    double p = (s > 2. * x[j]) ? (powf64(-i * s, 2.)) : (sinf64(-6. * s));
    std::wcout << L"s = " << s << L", p = " << p << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input N:";
  int n = input_value<int>();
  int count = 0;

  for (int i = 100; i <= 999; i += 1) {
    if (sum_of_digits(i) == n) {
      count += 1;
    }
  }

  std::wcout << L"Number of numbers with sum of digits equal to " << n
             << L" is " << count << L"\n";
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  std::wcout << L"First part:\n";
  double a = -5.5e-4, y = 2.7;
  double j[] = { 6., -8.2, 15.4, 2. };
  for (size_t i = 0; i < sizeof(j) / sizeof(j[0]); i++) {
    double x = powf64(cosf64(y), 2.) / (j[i] + 2. * a * y);
    double z =
      (x < sqrtf64(y)) ? (powf64(0.5 * y / j[i], 2.)) : (expf64(-j[i]));
    std::wcout << L"x = " << x << L", z = " << z << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input a:";
  int gcd_a = input_value<int>();
  std::wcout << L"Input b:";
  int gcd_b = input_value<int>();
  std::wcout << L"Greatest common diviser of a = " << gcd_a << L" and b = "
             << gcd_b << L" is " << gcd(gcd_a, gcd_b) << L"\n";
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  std::wcout << L"First part:\n";
  double y = 1.4e-3, x = 0.2, m = 4.;
  for (double j = 5.; j <= 11.; j += 2.) {
    double p = expf64(sinf64(j / x)) * logf64(x / y) * x;
    double q = (p > y * y) ? (sqrtf64(2. * x) / (j + p)) : (sqrtf64(p / m));
    std::wcout << L"p = " << p << L", q = " << q << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input N:";
  uint n = input_value<uint>();

  int factors[] = { 2, 3, 5 };
  int* ugly = new int[n + 1];
  ugly[0] = 1;
  int i2 = 0, i3 = 0, i5 = 0;
  int next_i2 = ugly[i2] * 2, next_i3 = ugly[i3] * 3, next_i5 = ugly[i5] * 5;

  for (int i = 1; i <= n; i++) {
    int next_ugly = std::min(next_i2, std::min(next_i3, next_i5));
    ugly[i] = next_ugly;
    std::wcout << next_ugly << L" ";
    if (next_ugly == next_i2) {
      i2 = i2 + 1;
      next_i2 = ugly[i2] * 2;
    }
    if (next_ugly == next_i3) {
      i3 = i3 + 1;
      next_i3 = ugly[i3] * 3;
    }
    if (next_ugly == next_i5) {
      i5 = i5 + 1;
      next_i5 = ugly[i5] * 5;
    }
  }
  std::wcout << L"\n";
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  std::wcout << L"First part:\n";
  double a = -4.2, i = 4.;
  double t[] = { 5., 1., -3., 9., -1. };
  for (size_t j = 0; j < sizeof(t) / sizeof(t[0]); j++) {
    double d = i + 2. * t[j] * (1. + sqrtf64(3. * a * a));
    double f = (d < t[j] * (t[j] + i)) ? (expf64(t[j] - d)) : (t[j] * i);
    std::wcout << L"d = " << d << L", f = " << f << L"\n";
  }
  std::wcout << L"\nSecond part:\n";
  for (int i = 9; i >= 1; i--) {
    for (int j = 9; j >= 0; j--) {
      if (i != j) {
        std::wcout << i << j << L" ";
      }
    }
    std::wcout << L"\n";
  }
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  std::wcout << L"First part:\n";
  double d = 51.9e-2, k = 1., a = 4.;
  for (double c = 3.7; c <= 5.; c += 0.1) {
    double x = tanf64(a * a - 1.) / (d + 1.0);
    double y =
      (3. * x < a * c) ? (a * k + d) : (cosf64(a * k) * expf64(a + 1.));

    std::wcout << L"x = " << x << L", y = " << y << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input M:";
  uint m = input_value<uint>();
  std::wcout << L"Input N:";
  uint n = input_value<uint>();

  for (uint i = 0; i < n; i++) {
    uint temp = sum_of_digits(i);
    if (temp * temp == m)
      std::wcout << i << L" ";
  }
  std::wcout << L"\n";
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  std::wcout << L"First part:\n";
  double c = 6e-4, b = 3., a = 6.;
  for (double i = 8; i <= 24.; i += 4) {
    double t = a * i / (a * a - b) * expf64(-a);
    double x = (t > 5. * c) ? (4.8e-3 + i * a) : (a + i * i * t);
    std::wcout << L"t = " << t << L", x = " << x << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input N:";
  uint n = input_value<uint>();

  std::wcout << L"Natural dividers of " << n << L" is:\n";
  for (uint i = 1; i <= n / 2; i++) {
    if (n % i == 0)
      std::wcout << i << L" ";
  }
  std::wcout << L"\n";
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  std::wcout << L"First part:\n";
  double j = -7e-3, f = 1.2;
  for (double w = 2.; w <= 5.; w += 0.5) {
    double s = w / (w * w - j) * logf64(fabsf64(w));
    double y = (s < 3. * sqrt(f)) ? (s * s / w) : (s - expf64(f / j));
    std::wcout << L"s = " << s << L", y = " << y << L"\n";
  }
  std::wcout << L"\nSecond part:\n";
  for (int i = 1; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int m = 0; m <= 9; m++) {
        for (int n = 0; n <= 9; n++) {
          if (i != j && i != m && i != n && j != m && j != n && m != n) {
            std::wcout << i << j << m << n << L" ";
          }
        }
      }
    }
    std::wcout << L"\n";
  }
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  std::wcout << L"First part:\n";
  double x = 2.5, k = 3., a = 1.2;
  for (double m = 4.; m <= 6.; m += 0.2) {
    double w = (x < m / 2.) ? (sqrt(0.2 * x) * k) : (expf64(2. * x * k));
    double v = sqrtf64(powf64(w, 3.) + fabsf64(x - a)) / logf64(1. + a);
    std::wcout << L"w = " << w << L", v = " << v << L"\n";
  }
  std::wcout << L"Sum of positive integers divisible by 5 and less than 150"
             << L" is:\n";
  int sum = 0;
  for (uint i = 5; i < 150; i++) {
    if (i % 5 == 0)
      sum += i;
  }
  std::wcout << sum << L"\n";
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  std::wcout << L"First part:\n";
  double a = 1.33e-3, k = 6.;
  double x[] = { 0.2, 1., -3., -6.1 };
  for (size_t j = 0; j < sizeof(x) / sizeof(x[0]); j++) {
    double d = expf64(-x[j]) + (x[j] - a) / logf64(x[j]);
    double b = (d < k * sqrtf64(a)) ? (sinf64(a / x[j])) : (6. * d * x[j]);
    std::wcout << L"d = " << d << L", b = " << b << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input F:";
  uint f = input_value<uint>();

  uint counter = 0;
  for (uint i = 10; i < 100; i++) {
    if (sum_of_digits(i) == f)
      counter += 1;
  }
  std::wcout << L"Number of two-digit natural numbers, the sum of the digits "
                L"of which is equal to "
             << f << L" is " << counter << L"\n";
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  std::wcout << L"First part:\n";
  double f = -125e-6, y = 1.7;
  for (double t = 1.; t <= 2.; t += 0.1) {
    double c = 2. * sinf64(f / 2.) + logf64(t);
    double d = (c < 3.) ? (y * (1. - y * y)) : (y * expf64(-2. * t) + f);
    std::wcout << L"c = " << c << L", d = " << d << L"\n";
  }
  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input x:";
  int gcd_x = input_value<int>();
  std::wcout << L"Input y:";
  int gcd_y = input_value<int>();
  std::wcout << L"Input z:";
  int gcd_z = input_value<int>();

  std::wcout << L"Greatest common diviser of x = " << gcd_x << L", y = "
             << gcd_y << L" and z = " << gcd_z << L" is "
             << gcd(gcd(gcd_x, gcd_y), gcd_z) << L"\n";
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  std::wcout << L"First part:\n";
  double a = 1.055, x = 0.6;
  for (double n = 6.; n <= 14.; n += 2.) {
    double y = powf64(cosf64(x * x), 2.) / fabsf64(x);
    double z = (y < a * x * n) ? (fabsf64(y)) : (sqrtf64(1. + expf64(-y)));
    std::wcout << L"y = " << y << L", z = " << z << L"\n";
  }

  std::wcout << L"\nSecond part:\n";
  int factors[] = { 3, 5 };
  int* ugly = new int[7];
  ugly[0] = 1;
  int i3 = 0, i5 = 0;
  int next_i3 = ugly[i3] * 3, next_i5 = ugly[i5] * 5;

  for (int i = 1; i <= 7; i++) {
    int next_ugly = std::min(next_i3, next_i5);
    ugly[i] = next_ugly;
    std::wcout << next_ugly << L" ";
    if (next_ugly == next_i3) {
      i3 = i3 + 1;
      next_i3 = ugly[i3] * 3;
    }
    if (next_ugly == next_i5) {
      i5 = i5 + 1;
      next_i5 = ugly[i5] * 5;
    }
  }
  std::wcout << L"\n";
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  std::wcout << L"First part:\n";
  double j = 10.4e+4, s = 5.2;
  double x[] = { 5., 0.4, -2.1, 6. };
  for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
    double v = 0.;
    if (2. * s > x[i] * j) {
      v = powf64(cosf64(j * x[i]), 2.);
    } else if (2. * s < x[i] * j) {
      v = 2. * tanf64(j * x[i]);
    } else {
      v = 5. - expf64(x[i] / 2.);
    }
    std::wcout << L"v = " << v << L"\n";
  }
  std::wcout << L"\nSecond part:\n";
  for (int i = 1; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int m = 0; m <= 9; m++) {
        if (i != j && i != m && j != m) {
          std::wcout << i << j << m << L" ";
        }
      }
    }
    std::wcout << L"\n";
  }
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  std::wcout << L"First part:\n";
  double x = -4e-3, s = 1.1;
  for (double j = 4.; j <= 7.; j += 0.5) {
    double b = 12. * s - expf64(-s / 2.) * (s - j);
    double z =
      (b < 1.5) ? (sqrtf64(-2. * x * j) + b) : (fabsf64(13. * x * j) + b);
    std::wcout << L"b = " << b << L", z = " << z << L"\n";
  }
  std::wcout << L"\nSecond part:\n";

  std::wcout << L"Input Q:";
  uint q = input_value<uint>();
  std::wcout << L"Input B:";
  uint b = input_value<uint>();

  for (uint i = 0; i < q; i++) {
    uint temp = sum_of_digits(i);
    if (temp * temp == b)
      std::wcout << i << L" ";
  }
  std::wcout << L"\n";
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  std::wcout << L"First part:\n";
  double x = 1.9;
  for (double t = 6.; t <= 14.; t += 2.) {
    double z = 0.;
    if (t > x) {
      z = powf64(sinf64(t), 2.);
    } else if (t < x) {
      z = 4. * (t + x);
    } else {
      z = 1. - expf64(x - 2.);
    }
    std::wcout << L"v = " << z << L"\n";
  }
  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input size:";
  int size = input_value<int>();
  int max_neg = INT32_MIN;
  int n = 0;
  for (size_t i = 0; i < size; i++) {
    std::wcout << L"Input N:";
    n = input_value<int>();
    if (n < 0 && n > max_neg) {
      max_neg = n;
    }
  }
  if (max_neg != INT32_MIN) {
    std::wcout << L"The largest negative number is " << max_neg << L"\n";
  } else {
    std::wcout << L"No negatives in the sequence!\n";
  }
}
#pragma endregion Sixteenth_Variant
}