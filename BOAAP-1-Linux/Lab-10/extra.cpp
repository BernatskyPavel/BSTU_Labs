#include "extra.hpp"
#include "array.hpp"
#include <iomanip>
#include <iostream>
#include <wchar.h>

using namespace lab_10::array;

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
  Array<int32_t> array = Array<int32_t>(len, true, 0, 20);

  std::wcout << L"Array:\n";
  array.print(true);

  int32_t max = 0;
  size_t last_day = 7;

  if (array.size() <= 7) {
    max = array.sum();
  } else {
    for (size_t i = 0; i < 7; i++)
      max += array[i];
    int32_t next = max;
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
  Array<int32_t> array = Array<int32_t>(len, true, 0, 20);

  std::wcout << L"Array:\n";
  array.print(true);

  int32_t pairs = 0;

  for (size_t i = 0; i < array.size() - 1; i++)
    if (array[i] == array[i + 1])
      pairs += 1;

  std::wcout << L"Number of pairs of equal elements is " << pairs << L"\n";

  return;
}

#pragma endregion Second_Extra
#pragma region Third_Extra
void
third_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array<int32_t> array = Array<int32_t>(len, true, 0, 5);

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
#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array<int32_t> array = Array<int32_t>(len, true, 0, 10);

  std::wcout << L"Array:\n";
  array.print(true);
  int32_t dict_size = abs(array.max()) + abs(array.min());
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
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra
void
fifth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array<int32_t> array = Array<int32_t>(2 * len + 1, true, 1, 25);

  std::wcout << L"Array:\n";
  array.print(true);

  int32_t median = 0;
  size_t index = 0;

  for (size_t i = 0; i < array.size(); i++) {
    int32_t temp = 0;
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
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  if (len > 100) {
    std::wcout << L"Array length can not be bigger than 100!\n";
    return;
  }
  Array<int32_t> array = Array<int32_t>(len, true, -100, 100),
                 seq = Array<int32_t>(0);

  int64_t max_sum = 0, cur_sum = 0;
  size_t start_index = 0, end_index = 0, cur_start_index = 0;
  bool is_prev_negative = true;

  for (size_t i = 0; i < len; i++) {
    if (is_prev_negative && array[i] > 0) {
      cur_start_index = i;
    }
    if (array[i] < 0) {
      if (!is_prev_negative && cur_sum > max_sum) {
        end_index = i - 1;
        start_index = cur_start_index;
        max_sum = cur_sum;
      }

      is_prev_negative = true;
      cur_sum = 0;
      continue;
    }
    is_prev_negative = false;
    cur_sum += static_cast<int64_t>(array[i]);
  }

  if (cur_sum > max_sum) {
    start_index = cur_start_index;
    end_index = len - 1;
  }

  for (size_t i = start_index; i <= end_index; i++) {
    seq.push(array[i], Array<int32_t>::Push::BACK);
  }

  std::wcout << L"Array:\n";
  array.print(true);

  std::wcout << L"Sequence with maximal sum:\n";
  seq.print(true);

  return;
}
#pragma endregion Sixth_Extra
}