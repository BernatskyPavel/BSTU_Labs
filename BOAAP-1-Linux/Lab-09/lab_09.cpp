#include "lab_09.hpp"
#include "array.hpp"
#include <iostream>
#include <vector>
#include <wchar.h>

namespace lab_09 {

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

#pragma region First_Variant

void
first_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);
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
  array.insert_after_every(Array::EVEN, 0);

  std::wcout << L"Array after updating:\n";
  array.print(true);
  return;
}

#pragma endregion First_Variant
#pragma region Second_Variant

void
second_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array_k = Array(len, true), array_l = Array(0), array_m = Array(0);

  std::wcout << L"Array K:\n";
  array_k.print(true);

  for (size_t i = 0; i < array_k.size(); i++) {
    if (array_k[i] % 2 == 0) {
      array_l.push(array_k[i], Array::Push::BACK);
    } else {
      array_m.push(array_k[i], Array::Push::BACK);
    }
  }

  std::wcout << L"Array L with size " << array_l.size() << L":\n";
  array_l.print(true);
  std::wcout << L"Array M with size " << array_m.size() << L":\n";
  array_m.print(true);
  return;
}

#pragma endregion Second_Variant
#pragma region Third_Variant

void
third_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  array.insert_after_every(Array::ODD, 4);
  std::wcout << L"Array after updating:\n";
  array.print(true);
  return;
}

#pragma endregion Third_Variant
#pragma region Fourth_Variant

void
fourth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  return;
}

#pragma endregion Fourth_Variant
#pragma region Fifth_Variant

void
fifth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  return;
}

#pragma endregion Fifth_Variant
#pragma region Sixth_Variant

void
sixth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 10);
  std::wcout << L"Input value to remove from array:";
  size_t elem = input_value<int>();

  std::wcout << L"Array before updating:\n";
  array.print(true);
  array.remove_all(elem, true);
  array.insert_after_every(Array::EVEN, 1);
  std::wcout << L"Array after updating:\n";
  array.print(true);
  return;
}

#pragma endregion Sixth_Variant
#pragma region Seventh_Variant

void
seventh_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

  std::wcout << L"Array before updating:\n";
  array.print(true);

  int min = array.min();
  array.remove_all(min, true);

  int avg = static_cast<int>(array.avg());
  for (size_t i = 0; i < 3; i++) {
    array.push(avg, Array::Push::FRONT);
  }

  std::wcout << L"Array after updating:\n";
  array.print(true);
  return;
}

#pragma endregion Seventh_Variant
#pragma region Eighth_Variant

void
eighth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  return;
}

#pragma endregion Eighth_Variant
#pragma region Ninth_Variant

void
ninth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
             << L") of array's values is " << closest << L" at position " << pos
             << L"\n";
  return;
}

#pragma endregion Ninth_Variant
#pragma region Tenth_Variant

void
tenth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
    std::wcout << L"Element equal to mean of the last three elements is " << avg
               << L" and first occurance of the element is happend at position "
               << index << L"\n";
  }

  return;
}

#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant

void
eleventh_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
    array.push(array[0], Array::Push::BACK);
  }

  std::wcout << L"Array after updating:\n";
  array.print(true);
  return;
}

#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant

void
twelfth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  return;
}

#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant

void
thirteenth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true);

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
  return;
}

#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant

void
fourteenth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, 0, 10);

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

  return;
}

#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant

void
fifteenth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  Array array = Array(len, true, -99, 99);

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
  return;
}

#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant

void
sixteenth_variant()
{
  std::wcout << L"Input array length:";
  size_t len = input_value<size_t>();
  int MIN = 0, MAX = 25;
  Array array = Array(len, true, MIN, MAX);

  std::wcout << L"Array:\n";
  array.print(true);

  size_t index = array.find_first(0);
  if (index == (size_t)-1) {
    std::wcout << L"No minimal values in the array!\n";
  } else {
    std::wcout << L"First occurance of minimal is happend at position " << index
               << L"\n";
  }
  index = array.find_first(25);
  if (index == (size_t)-1) {
    std::wcout << L"No maximal values in the array!\n";
  } else {
    std::wcout << L"First occurance of maximal is happend at position " << index
               << L"\n";
  }
  return;
}

#pragma endregion Sixteenth_Variant
}