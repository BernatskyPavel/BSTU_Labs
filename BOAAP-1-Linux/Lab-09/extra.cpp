#include "extra.hpp"
#include "array.hpp"
#include <iomanip>
#include <iostream>
#include <wchar.h>

using namespace lab_09::array;

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
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 20);

  std::wcout << L"Array:\n";
  array.print(true);

  int max = 0;
  size_t last_day = 7;

  if (array.size() <= 7) {
    max = array.sum();
  } else {
    for (size_t i = 0; i < 7; i++)
      max += array[i];
    int next = max;
    for (size_t i = 7; i < array.size(); i++) {
      next = next - array[i - 7] + array[i];
      if (next > max) {
        max = next;
        last_day = i + 1;
      }
    }
  }

  std::wcout << L"Maximum rainfall was " << max << " mm betwween "
             << last_day - 7 << L" and " << last_day << L" days!\n";

  return;
}
#pragma endregion First_Extra
#pragma region Second_Extra
void
second_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 100);

  std::wcout << L"Array before swaps:\n";
  array.print(true);

  int max = array.max(), min = array.min();

  size_t index_max = array.find_first(max), index_min = array.find_first(min);

  size_t from = std::min(index_max, index_min),
         to = (index_max + index_min) - from;

  size_t steps = (to - from - 1) / 2;

  for (size_t i = 1; i <= steps; i++)
    array.swap(from + i, to - i);

  std::wcout << L"Array after swaps:\n";
  array.print(true);
  return;
}
#pragma endregion Second_Extra
#pragma region Third_Extra
void
third_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 20);

  std::wcout << L"Array:\n";
  array.print(true);

  int pairs = 0;

  for (size_t i = 0; i < array.size() - 1; i++)
    if (array[i] == array[i + 1])
      pairs += 1;

  std::wcout << L"Number of pairs of equal elements is " << pairs << L"\n";

  return;
}

#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 5);

  std::wcout << L"Array:\n";
  array.print(true);

  size_t index = 0, max = 0, temp = 0, index_temp = 0;
  bool is_seq = false;

  for (size_t i = 0; i < array.size() - 1; i++)
    if (array[i] == array[i + 1]) {
      if (!is_seq) {
        index_temp = i;
        is_seq = true;
      }
      temp += 1;
    } else {
      if (is_seq) {
        is_seq = false;
        if (temp > max) {
          max = temp;
          index = index_temp;
        }
        temp = 0;
      }
    }

  std::wcout << L"The longest sequence of the elements with same values is "
             << max + 1 << L" elements long (array[" << index << L"..."
             << index + max << L"]\n";

  return;
}
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra
void
fifth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 10);

  std::wcout << L"Array:\n";
  array.print(true);
  int dict_size = abs(array.max()) + abs(array.min());
  size_t* dict = new size_t[dict_size];

  for (size_t i = 0; i < dict_size; i++)
    dict[i] = 0;

  for (size_t i = 0; i < array.size(); i++)
    if (array[i] < 0) {
      dict[array.max() + array[i]] += 1;
    } else {
      dict[array[i]] += 1;
    }

  size_t counter = 0;
  for (size_t i = 0; i < dict_size; i++)
    if (dict[i] != 0)
      counter++;

  std::wcout << L"The number of different elements in the array is " << counter
             << L"\n";

  return;
}
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 1, 100);

  std::wcout << L"Array:\n";
  array.print(true);

  bool is_fib = false;
  int max = array.max(), fib_0 = 0, fib_1 = 1;

  do {
    fib_0 = fib_1;
    fib_1 += fib_0;

    if (array.find_first(fib_1) != (size_t)-1) {
      is_fib = true;
      break;
    }

  } while (fib_1 < max);

  std::wcout << std::boolalpha
             << L"Is there any Fibonacci number in the array? Answer is "
             << is_fib << std::noboolalpha << L"\n";

  return;
}
#pragma endregion Sixth_Extra
#pragma region Seventh_Extra
void
seventh_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array_k = Array(len, true), array_l = Array(0), array_m = Array(0);

  std::wcout << L"Array K:\n";
  array_k.print(true);

  int avg = array_k.avg();

  for (size_t i = 0; i < array_k.size(); i++) {
    if (array_k[i] < avg) {
      array_l.push(array_k[i], Array::Push::BACK);
    } else if (array_k[i] > avg) {
      array_m.push(array_k[i], Array::Push::BACK);
    }
  }

  std::wcout << L"Array L (size: " << array_l.size()
             << L") with elements lower than average:\n";
  array_l.print(true);
  std::wcout << L"Array M (size: " << array_m.size()
             << L") with elements lower than average:\n";
  array_m.print(true);
  return;
}
#pragma endregion Seventh_Extra
#pragma region Eighth_Extra
void
eighth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(2 * len + 1, true, 1, 25);

  std::wcout << L"Array:\n";
  array.print(true);

  int median = 0;
  size_t index = 0;

  for (size_t i = 0; i < array.size(); i++) {
    int temp = 0;
    for (size_t j = 0; j < array.size(); j++) {
      if (array[i] < array[j])
        temp += 1;
    }
    if (temp == len) {
      median = array[i];
      index = i;
      break;
    }
  }

  std::wcout << std::boolalpha << L"Median of the array is is " << median
             << L" at position " << index << L"\n";

  return;
}
#pragma endregion Eighth_Extra
}