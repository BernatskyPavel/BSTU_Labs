#include "extra.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory.h>
#include <string>
#include <tuple>
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

#pragma region First_Extra
int
sum_of_digits(int number)
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

void
first_extra()
{
  size_t min = 100000, max = 999999;
  std::vector<std::tuple<size_t, size_t>> lucky_pairs =
    std::vector<std::tuple<size_t, size_t>>();
  for (size_t i = min; i < max; i++) {
    if (sum_of_digits(i) % 7 == 0 && sum_of_digits(i + 1) % 7 == 0) {
      lucky_pairs.push_back(std::make_tuple(i, i + 1));
    }
  }
  if (lucky_pairs.size() != 0) {
    std::wcout << L"There is at least one pair of consecutive lucky tickets!\n";
    for (auto iterator = lucky_pairs.cbegin(); iterator != lucky_pairs.cend();
         iterator++) {
      std::wcout << L"Pair: " << std::get<0>(*iterator) << L", "
                 << std::get<1>(*iterator) << "\n";
    }
  } else {
    std::wcout << L"There are no pairs of consecutive lucky tickets!\n";
  }
}
#pragma endregion Firest_Extra
#pragma region Second_Extra
void
second_extra()
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
#pragma endregion Second_Extra
#pragma region Third_Extra

enum Gender
{
  Male,
  Female,
};

struct Student
{
  Gender gender;
  unsigned short b_year;
  unsigned short height;
  unsigned short weight;
};

void
third_extra()
{
  Student students[] = {
    { Gender::Male, 1998, 181, 72 }, { Gender::Female, 1999, 172, 48 },
    { Gender::Male, 1997, 179, 69 }, { Gender::Female, 1989, 168, 51 },
    { Gender::Male, 1996, 185, 78 }, { Gender::Female, 2000, 165, 52 },
    { Gender::Male, 1999, 185, 80 }, { Gender::Female, 1997, 175, 56 },
    { Gender::Male, 2000, 168, 61 }, { Gender::Female, 1996, 180, 49 },
    { Gender::Male, 1998, 190, 79 }, { Gender::Female, 2000, 163, 54 },
    { Gender::Male, 1996, 175, 68 }, { Gender::Female, 2000, 170, 52 }
  };

  time_t current = time(NULL);
  tm* local_current = localtime(&current);
  int current_year = local_current->tm_year + 1900;

  size_t male_highest_index = 0, male_fattest_index = 0,
         female_youngest_index = 0, female_lowest_index = 0;

  size_t male_counter = 0, female_counter = 0;

  typeof(Student::height) male_max_height = 0, female_min_height = 999;
  typeof(Student::weight) max_weight = 0;
  typeof(Student::b_year) max_b_year = 0, male_sum_age = 0, female_sum_age = 0;

  for (size_t i = 0; i < sizeof(students) / sizeof(Student); i++) {
    switch (students[i].gender) {
      case Gender::Female:
        female_counter += 1;
        female_sum_age += current_year - students[i].b_year;
        if (students[i].height <= female_min_height) {
          female_lowest_index = i;
          female_min_height = students[i].height;
        }
        if (students[i].b_year > max_b_year) {
          female_youngest_index = i;
          max_b_year = students[i].b_year;
        } else if (students[i].b_year == max_b_year) {
          if (students[i].height <= female_min_height) {
            female_youngest_index = i;
            max_b_year = students[i].b_year;
            female_lowest_index = i;
            female_min_height = students[i].height;
          }
        }
        break;

      case Gender::Male:
        male_counter += 1;
        male_sum_age += current_year - students[i].b_year;
        if (students[i].weight >= max_weight) {
          male_fattest_index = i;
          max_weight = students[i].weight;
        }
        if (students[i].height > male_max_height) {
          male_highest_index = i;
          male_max_height = students[i].height;
        } else if (students[i].height == male_max_height) {
          if (students[i].weight >= max_weight) {
            male_highest_index = i;
            male_max_height = students[i].height;
            male_fattest_index = i;
            max_weight = students[i].weight;
          }
        }
        break;
    }
  }

  std::wcout << L"Statistic: \n - Number of boys: " << male_counter
             << L"\n - Number of girls: " << female_counter
             << "\n - Average age of boys: "
             << (double)male_sum_age / (double)male_counter
             << "\n - Average age of girls: "
             << (double)female_sum_age / (double)female_counter << L'\n'
             << "Answer on the first question: "
             << (male_highest_index == male_fattest_index ? L"Yes\n" : L"No\n")
             << "Answer on the second question: "
             << (female_lowest_index == female_youngest_index ? L"Yes\n"
                                                              : L"No\n");
}
#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
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
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra

enum SIGN
{
  POSITIVE,
  NEGATIVE,
  ZERO,
  EMPTY
};

void
fifth_extra()
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
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
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
#pragma endregion Sixth_Extra
#pragma region Seventh_Extra
// Task was changed from KOT+KOT=TOK to KOT+KTO=TOK, because original task has
// no solution
void
seventh_extra()
{
  for (int k = 1; k <= 9; k++) {
    for (int o = 0; o <= 9; o++) {
      for (int t = 0; t <= 9; t++) {
        if (k == o || k == t || o == t) {
          continue;
        } else {
          if ((199 * k + o - 89 * t) == 0) {
            std::wcout << (100 * k + 10 * o + t) << L" + "
                       << (100 * k + 10 * t + o) << " = "
                       << (100 * t + 10 * o + k) << L"\n";
          }
        }
      }
    }
  }
}
#pragma endregion Seventh_Extra
void
eighth_extra()
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

}