#include "extra.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <wchar.h>

namespace extra {
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
#pragma endregion Helpers
#pragma region First_Extra
void
first_extra()
{
  std::wcout << L"Input P:";
  double p = input_value<double>();
  std::wcout << L"Input Q:";
  double q = input_value<double>();

  p *= 1000.0;

  size_t days = 0;
  while (p <= q) {
    p *= 1.03;
    days += 1;
  }
  std::wcout << L"The revenue value exceeded the target value and is equal to "
             << p << ". It took " << days << " day(s) for this!\n";
}
#pragma endregion Firest_Extra
#pragma region Second_Extra
void
second_extra()
{
  std::wcout << L"Input N:";
  int n = input_value<int>();

  double* expenses = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++) {
    std::wcout << L"Input S" << i + 1 << L":";
    expenses[i] = input_value<double>();
  }

  std::wcout << L"Input P:";
  double p = input_value<double>();

  double sum = 0;

  for (size_t i = 0; i < n; i++) {
    sum += expenses[i];
    sum *= (1.0 - p / 100.0);
  }
  free(expenses);
  std::wcout << L"The cost of accumulated equipment is " << sum << L"\n";
}
#pragma endregion Second_Extra
#pragma region Third_Extra
enum SIGN
{
  POSITIVE,
  NEGATIVE,
  ZERO,
  EMPTY
};

void
third_extra()
{
  SIGN prev = SIGN::EMPTY;
  size_t swaps = 0;
  int n = 0;
  do {
    std::wcout << L"Input N:";
    n = input_value<int>();
    if (prev == SIGN::EMPTY) {
      prev = n > 0 ? SIGN::POSITIVE : (n < 0 ? SIGN::NEGATIVE : SIGN::ZERO);
    } else {
      SIGN temp =
        n > 0 ? SIGN::POSITIVE : (n < 0 ? SIGN::NEGATIVE : SIGN::ZERO);
      if (temp != prev) {
        swaps += 1;
      }
      prev = temp;
    }
  } while (n != 0);

  std::wcout << L"Number of swaps of sign of numbers is " << swaps - 1 << L"\n";
}
#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
{
  std::wcout << L"Input K:";
  uint k = input_value<uint>();

  if (k == 0) {
    std::wcout << L"K must be positive number bigger than 0!\n";
    return;
  }

  uint last_power = 1;
  size_t digit_counter = 1;
  while (digit_counter < k) {
    last_power *= 2;
    std::wstring temp = std::to_wstring(last_power);
    digit_counter += temp.length();
  }

  std::wstring str = std::to_wstring(last_power);
  std::reverse(str.begin(), str.end());

  std::wcout << L"Digit at position K is " << str[digit_counter - k] << L"\n";
}
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra
void
fifth_extra()
{
  u_long absolute_primes[] = { 2,
                               3,
                               5,
                               7,
                               11,
                               13,
                               17,
                               31,
                               37,
                               71,
                               73,
                               79,
                               97,
                               113,
                               131,
                               199,
                               311,
                               337,
                               373,
                               733,
                               919,
                               991,
                               1111111111111111111 };
  std::wcout << L"Input N:";
  u_long n = input_value<u_long>();

  std::wcout << L"Absolute primes before N: \n";
  for (size_t i = 0; i < sizeof(absolute_primes) / sizeof(u_long); i++) {
    if (absolute_primes[i] < n) {
      std::wcout << absolute_primes[i] << L"\n";
    } else {
      if (i == 0) {
        std::wcout << L"None\n";
      }
    }
  }
}
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
{
  std::wcout << L"Input K:";
  uint k = input_value<uint>();

  std::wstring str_k = std::to_wstring(k);
  std::vector<size_t> indices = std::vector<size_t>();
  for (size_t i = 0; i < str_k.length(); i++) {
    if (str_k[i] == L'3' || str_k[i] == L'6') {
      indices.push_back(i);
    }
  }

  for (int i = indices.size() - 1; i >= 0; i--) {
    str_k.erase(indices[i], 1);
  }

  std::wcout << L"Number after removing digits: " << str_k << L"\n";
}
#pragma endregion Sixth_Extra
}