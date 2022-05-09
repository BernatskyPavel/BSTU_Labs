#include "lab_10.hpp"
#include "array.hpp"
#include <iostream>
#include <vector>
#include <wchar.h>

using namespace lab_10::array;

namespace lab_10 {
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
#pragma region First_Variant
void
first_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true, 0, 10);
    std::wcout << L"Input value to remove from array:";
    size_t elem = input_value<int>();

    std::wcout << L"Array before updating:\n";
    array.print(true);
    array.remove_all(elem, true);
    array.insert_after_every(Array<int>::EVEN, 1);
    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<char> array = Array<char>(k, true, 20);
    Array<char> digits = Array<char>(0), symbols = Array<char>(0);

    for (size_t i = 0; i < array.size(); i++) {
      if (isdigit(array[i])) {
        digits.push(array[i]);
      } else {
        symbols.push(array[i]);
      }
    }

    std::wcout << L"Initial array:\n";
    array.print(true);
    std::wcout << L"Array of digits:\n";
    digits.print(true);
    std::wcout << L"Array of rest symbols:\n";
    symbols.print(true);
  }
  return;
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array_k = Array<int>(len, true), array_l = Array<int>(0),
               array_m = Array<int>(0);

    std::wcout << L"Array K:\n";
    array_k.print(true);

    for (size_t i = 0; i < array_k.size(); i++) {
      if (array_k[i] % 2 == 0) {
        array_l.push(array_k[i], Array<int>::Push::BACK);
      } else {
        array_m.push(array_k[i], Array<int>::Push::BACK);
      }
    }

    std::wcout << L"Array L with size " << array_l.size() << L":\n";
    array_l.print(true);
    std::wcout << L"Array M with size " << array_m.size() << L":\n";
    array_m.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    std::wcout << L"Input n:";
    size_t n = input_value<size_t>();
    Array<int> array = Array<int>(k, true, 0, 100);
    std::wcout << L"Initial array:\n";
    array.print(true);
    array.shiftc(n, Array<int>::Shift::RIGHT);
    std::wcout << L"Array after shifting:\n";
    array.print(true);
  }
  return;
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);
    size_t* indexes = new size_t[array.size() / 7 + 1];
    int deleted = 0;
    for (size_t i = 0; i < array.size(); i++) {
      if (i % 7 == 0) {
        indexes[deleted++] = i;
      }
    }
    while (deleted >= 0) {
      array.remove_at(indexes[--deleted], true);
    }
    array.insert_after_every(Array<int>::ODD, 4);
    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<int> array = Array<int>(k, true, -100, 100);
    std::wcout << L"Initial array:\n";
    array.print(true);
    array.sort(Array<int>::Order::ASC);
    std::wcout << L"Array after sorting:\n";
    array.print(true);
  }
  return;
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);
    std::wcout << L"Input index of element to remove:";
    size_t k;
    while (true) {
      k = input_value<size_t>();
      if (k >= array.size()) {
        std::wcout << L"Index out of range! Try again: \n";
      } else {
        break;
      }
    }
    std::wcout << L"Array before updating:\n";
    array.print(true);

    int deleted = array.remove_at(k, true);
    array.insert_after_every(Array<int>::EVEN, 0);

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length n:";
  {
    size_t n = input_value<size_t>();
    Array<char> array = Array<char>(n, true, 20);
    Array<char> digits = Array<char>(0), symbols = Array<char>(0);

    for (size_t i = 0; i < array.size(); i++) {
      if (isdigit(array[i])) {
        digits.push(array[i]);
      } else {
        symbols.push(array[i]);
      }
    }

    std::wcout << L"Initial array:\n";
    array.print(true);
    std::wcout << L"Array of digits:\n";
    digits.print(true);
    std::wcout << L"Array of rest symbols:\n";
    symbols.print(true);
  }
  return;
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    int sum = 0;

    for (size_t i = 0; i < array.size(); i++) {
      if ((i + 1) % 3 == 0) {
        array[i] = sum / 2;
        sum = 0;
      } else {
        sum += array[i];
      }
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length n:";
  {
    size_t n = input_value<size_t>();
    Array<wchar_t> array = Array<wchar_t>(0);
    for (size_t i = 0; i < n; i++) {
      std::wcout << L"Input " << i + 1 << L" symbol:";
      wchar_t ch = input_value<wchar_t>();
      array.push(ch);
    }

    bool is_symmetric = true;
    for (size_t i = 0; i < n / 2; i++) {
      if (array[i] != array[n - i - 1]) {
        is_symmetric = false;
        break;
      }
    }

    std::wcout << L"Initial array:\n";
    array.print(true);
    std::wcout << L"Is array symmetric: " << is_symmetric << L'\n';
  }
  return;
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    size_t i_max = 0, i_min = 0;
    int max = INT32_MIN, min = INT32_MAX;

    for (size_t i = 0; i < array.size(); i++) {
      if (max < array[i]) {
        max = array[i];
        i_max = i;
      }
      if (min > array[i]) {
        min = array[i];
        i_min = i;
      }
    }

    array[i_min] = max;
    array[i_max] = min;

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length n:";
  {
    size_t n = input_value<size_t>();
    std::wcout << L"Input array length m:";
    size_t m = input_value<size_t>();

    Array<int32_t> array_one = Array<int32_t>(n, true, 0, n),
                   array_two = Array<int32_t>(m, true, 0, m),
                   array_exclusive = Array<int32_t>(0);

    for (size_t i = 0; i < n; i++) {
      if (array_two.find_first(array_one[i]) == (size_t)(-1)) {
        array_exclusive.push(array_one[i], Array<int32_t>::Push::BACK);
      }
    }

    std::wcout << L"First array:\n";
    array_one.print(true);
    std::wcout << L"Second array:\n";
    array_two.print(true);
    if (array_exclusive.size() == 0) {
      std::wcout << L"First array have no exclusive elements!\n";
    } else {
      std::wcout << L"Minimal exclusive element: " << array_exclusive.min()
                 << L'\n';
    }
  }
  return;
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    int min = array.min();
    array.remove_all(min, true);

    int avg = static_cast<int>(array.avg());
    for (size_t i = 0; i < 3; i++) {
      array.push(avg, Array<int>::Push::FRONT);
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t n = input_value<size_t>();
    Array<wchar_t> array = Array<wchar_t>(0);
    for (size_t i = 0; i < n; i++) {
      std::wcout << L"Input " << i + 1 << L" symbol:";
      wchar_t ch = input_value<wchar_t>();
      array.push(ch);
    }

    std::wcout << L"Initial array:\n";
    array.print(true);
    array.sort(Array<wchar_t>::Order::DESC);
    std::wcout << L"Sorted array:\n";
    array.print(true);
  }
  return;
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    int max = array.max();

    for (size_t i = 0; i < array.size(); i++) {
      if (i % 2 != 0) {
        array[i] = max;
      }
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<int32_t> array = Array<int32_t>(k, true, -20, 20);

    size_t inversion_counter = 0;

    for (size_t i = 0; i < k - 1; i++) {
      if (array[i] > array[i + 1]) {
        inversion_counter += 1;
      }
    }

    std::wcout << L"Initial array:\n";
    array.print(true);
    std::wcout << L"Number of inversions is " << inversion_counter << L'\n';
  }
  return;
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array:\n";
    array.print(true);

    int avg = static_cast<int>(array.avg()), diff = array.max() - avg,
        closest = array.max();
    size_t pos = 0;
    for (size_t i = 0; i < array.size(); i++) {
      if (abs(array[i] - avg) < diff) {
        diff = abs(array[i] - avg);
        closest = array[i];
        pos = i;
      }
    }
    std::wcout << L"Closest element to the mean(" << avg
               << L") of array's values is " << closest << L" at position "
               << pos << L"\n";
  }
  std::wcout << L"Part two:\nInput array length n:";
  {
    size_t n = input_value<size_t>();
    std::wcout << L"Input array length m:";
    size_t m = input_value<size_t>();

    Array<int32_t> array_one = Array<int32_t>(n, true, 0, n),
                   array_two = Array<int32_t>(m, true, 0, m),
                   array_exclusive = Array<int32_t>(0);

    for (size_t i = 0; i < n; i++) {
      if (array_two.find_first(array_one[i]) == (size_t)(-1)) {
        array_exclusive.push(array_one[i], Array<int32_t>::Push::BACK);
      }
    }

    std::wcout << L"First array:\n";
    array_one.print(true);
    std::wcout << L"Second array:\n";
    array_two.print(true);
    if (array_exclusive.size() == 0) {
      std::wcout << L"First array have no exclusive elements!\n";
    } else {
      std::wcout << L"Maximal exclusive element: " << array_exclusive.max()
                 << L'\n';
    }
  }
  return;
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array:\n";
    array.print(true);

    if (len < 3) {
      std::wcout << L"Array is too short!\n";
      return;
    }
    int avg = 0;
    for (size_t i = array.size() - 1; i > array.size() - 4; i--) {
      avg += array[i];
    }
    avg /= 3;

    size_t index = array.find_first(avg);
    if (index == (size_t)-1) {
      std::wcout << L"No such element in the array!\n";
    } else {
      std::wcout
        << L"Element equal to mean of the last three elements is " << avg
        << L" and first occurance of the element is happend at position "
        << index << L"\n";
    }
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<int32_t> array = Array<int32_t>(k, true, 0, 15),
                   uniques = Array<int32_t>(0);

    for (size_t i = 0; i < k; i++) {
      if (array.find_first(array[i]) == array.find_last(array[i])) {
        uniques.push(array[i], Array<int32_t>::Push::BACK);
      }
    }

    std::wcout << L"Array:\n";
    array.print(true);
    if (uniques.size() == 0) {
      std::wcout << L"No unique values!\n";
    } else {
      std::wcout << L"Unique values:\n";
      uniques.print(true);
    }
  }
  return;
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    size_t counter = 0;

    for (size_t i = 0; i < array.size(); i++) {
      if (array[i] % 2 != 0 && counter != 5) {
        counter += 1;
        array.remove_at(i);
        i--;
      }
    }

    for (size_t i = 0; i < 3; i++) {
      array.push(array[0], Array<int>::Push::BACK);
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t n = input_value<size_t>();
    Array<wchar_t> array = Array<wchar_t>(0);
    for (size_t i = 0; i < n; i++) {
      std::wcout << L"Input " << i + 1 << L" symbol:";
      wchar_t ch = input_value<wchar_t>();
      array.push(ch);
    }

    std::wcout << L"Initial array:\n";
    array.print(true);

    size_t i = 0;
    do {
      if (array.find_first(array[i]) != i) {
        array.remove_at(i);
      } else {
        i += 1;
      }
    } while (i != array.size());

    std::wcout << L"Updated array:\n";
    array.print(true);
  }
  return;
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    int min = array.min();

    for (size_t i = 0; i < array.size(); i++) {
      if (i % 2 == 0) {
        array[i] = min;
      }
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<wchar_t> array = Array<wchar_t>(0);
    for (size_t i = 0; i < k; i++) {
      std::wcout << L"Input " << i + 1 << L" symbol:";
      wchar_t ch = input_value<wchar_t>();
      array.push(ch);
    }

    size_t unique_counter = 0;

    for (size_t i = 0; i < k; i++) {
      if (array.find_first(array[i]) == i) {
        unique_counter += 1;
      }
    }

    std::wcout << L"Array:\n";
    array.print(true);
    if (unique_counter == 0) {
      std::wcout << L"No unique values!\n";
    } else {
      std::wcout << L"Number of unique values is " << unique_counter << L'\n';
    }
  }
  return;
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    int sum = 0;
    for (size_t i = 0; i < array.size(); i++) {
      sum += array[i];
    }
    for (size_t i = array.size() - 1; i > 0; i--) {
      sum -= array[i];
      array[i] = sum;
    }

    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<wchar_t> array = Array<wchar_t>(0), uniques = Array<wchar_t>(0);

    for (size_t i = 0; i < k; i++) {
      std::wcout << L"Input " << i + 1 << L" symbol:";
      wchar_t ch = input_value<wchar_t>();
      array.push(ch);
    }

    for (size_t i = 0; i < k; i++) {
      if (array.find_first(array[i]) == array.find_last(array[i])) {
        uniques.push(array[i], Array<wchar_t>::Push::BACK);
      }
    }

    std::wcout << L"Array:\n";
    array.print(true);
    if (uniques.size() == 0) {
      std::wcout << L"No unique values!\n";
    } else {
      std::wcout << L"Unique values:\n";
      uniques.print(true);
    }
  }
  return;
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true, 0, 10);

    std::wcout << L"Array:\n";
    array.print(true);

    size_t index = array.find_first(0);
    if (index == (size_t)-1) {
      std::wcout << L"No zeroes in the array!\n";
    } else {
      std::wcout << L"First occurance of zero is happend at position " << index
                 << L"\n";
      index = array.find_last(0);
      std::wcout << L"Last occurance of zero is happend at position " << index
                 << L"\n";
    }
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<int32_t> array = Array<int32_t>(k, true, 0, 100),
                   frequents = Array<int32_t>(0);
    size_t max_frequency = 1;

    std::wcout << L"Array:\n";
    array.print(true);

    array.sort(Array<int32_t>::Order::ASC);

    do {
      int32_t temp = array[0];
      size_t prev_size = array.size();
      array.remove_all(array[0]);
      size_t diff = prev_size - array.size();
      if (diff > max_frequency) {
        max_frequency = diff;
        frequents.clear();
        frequents.push(temp, Array<int32_t>::Push::BACK);
      } else if (diff == max_frequency) {
        frequents.push(temp, Array<int32_t>::Push::BACK);
      }
    } while (array.size() != 0);

    if (frequents.size() == 1) {
      std::wcout << L"The most common number is " << frequents[0] << L'\n';
    } else {
      std::wcout << L"The most common numbers:\n";
      frequents.print(true);
    }
  }
  return;
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    Array<int> array = Array<int>(len, true, -99, 99);

    std::wcout << L"Array before updating:\n";
    array.print(true);

    size_t* indexes = new size_t[array.size() / 3 + 1];
    int deleted = 0;
    for (size_t i = 0; i < array.size(); i++) {
      if (i % 3 == 0) {
        indexes[deleted++] = i;
      }
    }
    while (deleted >= 0) {
      array.remove_at(indexes[--deleted], true);
    }

    array.insert_after_neg(10);
    std::wcout << L"Array after updating:\n";
    array.print(true);
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    std::wcout << L"Input n:";
    size_t n = input_value<size_t>();
    Array<int32_t> array = Array<int32_t>(k, true, 0, 100);
    std::wcout << L"Initial array:\n";
    array.print(true);
    array.shiftc(n, Array<int32_t>::Shift::LEFT);
    std::wcout << L"Array after shifting:\n";
    array.print(true);
  }
  return;
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  std::wcout << L"Part one:\nInput array length:";
  {
    size_t len = input_value<size_t>();
    int MIN = 0, MAX = 25;
    Array<int> array = Array<int>(len, true, MIN, MAX);

    std::wcout << L"Array:\n";
    array.print(true);

    size_t index = array.find_first(array.min());
    if (index == (size_t)-1) {
      std::wcout << L"No minimal values in the array!\n";
    } else {
      std::wcout << L"First occurance of minimal is happend at position "
                 << index << L"\n";
    }
    index = array.find_first(array.max());
    if (index == (size_t)-1) {
      std::wcout << L"No maximal values in the array!\n";
    } else {
      std::wcout << L"First occurance of maximal is happend at position "
                 << index << L"\n";
    }
  }
  std::wcout << L"Part two:\nInput array length k:";
  {
    size_t k = input_value<size_t>();
    Array<int32_t> array = Array<int32_t>(k, true, 0, 10),
                   frequents = Array<int32_t>(0);

    std::wcout << L"Array:\n";
    array.print(true);

    array.sort(Array<int32_t>::Order::ASC);

    do {
      int32_t temp = array[0];
      size_t prev_size = array.size();
      array.remove_all(array[0]);
      size_t diff = prev_size - array.size();
      if (diff == 2) {
        frequents.push(temp, Array<int32_t>::Push::BACK);
      }
    } while (array.size() != 0);

    if (frequents.size() == 0) {
      std::wcout << L"No numbers found exactly twice!\n";
    } else {
      std::wcout << L"Numbers found exactly twice:\n";
      frequents.print(true);
    }
  }
  return;
}
#pragma endregion Sixteenth_Variant
}