#include "extra.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory.h>
#include <set>
#include <string>
#include <vector>
#include <wchar.h>

namespace extra {

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

template<typename T>
T*
input_array(size_t len)
{
  T* array = new T[len];
  for (size_t i = 0; i < len; i++) {
    std::wcout << L"Input array elem[" << (i + 1) << L"]:";
    array[i] = input_value<T>();
  }
  return array;
}

#pragma region First_Extra

void
first_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  int sum = 0;
  for (size_t i = 0; i < len; i++) {
    if ((i + 1) % 2 == 0) {
      sum += lp_array[i];
    }
  }

  std::wcout << L"Sum of even elements is " << sum << L"\n";
  delete[] lp_array;
  return;
}

#pragma endregion First_Extra
#pragma region Second_Extra

void
second_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  size_t pos = 0;
  for (size_t i = 0; i < len; i++) {
    if (lp_array[i] < 0) {
      pos = i + 1;
      break;
    }
  }

  if (pos != 0) {
    std::wcout << L"Position of first negative element is " << pos << L"\n";
  } else {
    std::wcout << L"There are no negative elements in the array!\n";
  }

  delete[] lp_array;
  return;
}

#pragma endregion Second_Extra
#pragma region Third_Extra

void
third_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  double* lp_array = input_array<double>(len);
  std::wcout << L"Input minimal value:";
  double min = input_value<double>();
  std::wcout << L"Input maximal value:";
  double max = input_value<double>();

  size_t counter = 0;
  for (size_t i = 0; i < len; i++) {
    if (lp_array[i] > min && lp_array[i] < max) {
      counter += 1;
    }
  }

  std::wcout << L"Number of elements between " << min << L" and " << max
             << L" is " << counter << L"\n";

  delete[] lp_array;
  return;
}

#pragma endregion Third_Extra
#pragma region Fourth_Extra

enum SIGN
{
  POSITIVE,
  NEGATIVE,
  ZERO,
  EMPTY
};

void
fourth_extra()
{
  SIGN prev = SIGN::EMPTY;
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  size_t swaps = 0;
  for (size_t i = 0; i < len; i++) {
    if (lp_array[i] != 0) {
      switch (prev) {
        case SIGN::EMPTY:
          prev = lp_array[i] > 0 ? SIGN::POSITIVE : SIGN::NEGATIVE;
          break;
        case SIGN::NEGATIVE:
          if (lp_array[i] > 0) {
            swaps += 1;
            prev = SIGN::POSITIVE;
          }
          break;
        case SIGN::POSITIVE:
          if (lp_array[i] < 0) {
            swaps += 1;
            prev = SIGN::NEGATIVE;
          }
          break;
        case SIGN::ZERO:
          break;
      }
    }
  }

  std::wcout << L"Number of swaps of sign of numbers in the array is " << swaps
             << L"\n";
  delete[] lp_array;
  return;
}

#pragma endregion Fourth_Extra
#pragma region Fifth_Extra

void
fifth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  char prev = '\0';
  bool is_saw = true;

  for (size_t i = 0; i < len - 1; i++) {
    char temp = '\0';
    if (lp_array[i] < lp_array[i + 1]) {
      temp = '<';
    } else if (lp_array[i] > lp_array[i + 1]) {
      temp = '>';
    } else {
      is_saw = false;
      break;
    }

    if (temp == prev) {
      is_saw = false;
      break;
    }

    prev = temp;
  }

  std::wcout << std::boolalpha << L"Is sequence sawtooth? Answer: " << is_saw
             << std::noboolalpha << L"\n";

  delete[] lp_array;
  return;
}

#pragma endregion Fifth_Extra
#pragma region Sixth_Extra

void
sixth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  int sum = 0, mul = 1;
  for (size_t i = 0; i < len; i++) {
    if (lp_array[i] > 0) {
      sum += lp_array[i];
    } else if (lp_array[i] < 0) {
      mul *= lp_array[i];
    }
  }

  std::wcout << L"Sum of positive elements is " << sum
             << L" and multiplication of negative elements is " << mul << L"\n";
  delete[] lp_array;
  return;
}

#pragma endregion Sixth_Extra
#pragma region Seventh_Extra

void
seventh_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  int max_pos = 0, max_neg = INT32_MIN;
  for (size_t i = 0; i < len; i++) {
    if (lp_array[i] > 0 && lp_array[i] > max_pos) {
      max_pos = lp_array[i];
    }
    if (lp_array[i] < 0 && lp_array[i] > max_neg) {
      max_neg = lp_array[i];
    }
  }

  std::wcout << L"Maximal positive element is " << max_pos
             << L" and Maximal negative element is " << max_neg << L"\n";
  delete[] lp_array;
  return;
}

#pragma endregion Seventh_Extra
#pragma region Eighth_Extra

void
eighth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int* lp_array = input_array<int>(len);

  int sum = 0;
  size_t count = 0;
  for (size_t i = 0; i < len; i++) {
    if ((i + 1) % 2 != 0) {
      sum += lp_array[i];
      count += 1;
    }
  }

  std::wcout << L"Arithmetic mean of negative elements is "
             << (static_cast<double>(sum) / static_cast<double>(count))
             << L"\n";
  delete[] lp_array;
  return;
}

#pragma endregion Eighth_Extra
}