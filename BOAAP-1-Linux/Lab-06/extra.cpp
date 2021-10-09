#include "extra.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <vector>

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
#pragma endregion Helpers
#pragma region First_Extra
bool
is_prime(unsigned int n)
{
  if (n <= 1)
    return false;
  if (n == 2)
    return true;
  for (unsigned int i = 2; i <= sqrt(n); ++i)
    if (n % i == 0)
      return false;
  return true;
}

void
first_extra()
{
  std::wcout << L"Full square numbers:\n";
  for (int i = 1; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k <= 9; k++) {
        if (i < j && j < k) {
          int num = i * 100 + j * 10 + k;
          double root = sqrt(num);
          if (root == (double)(int)root && is_prime((uint)root)) {
            std::wcout << num << L" ";
          }
        }
      }
    }
  }
  std::wcout << L"\n";
}
#pragma endregion Firest_Extra
#pragma region Second_Extra

using ll = long long;

ll dp[1000001];
const int MOD = (int)1e9 + 7;

void
second_extra()
{
  std::vector<int> coins = { 2, 5, 20, 50 };
  int goal = 100;
  dp[0] = 1;
  for (int i = 1; i <= 4; i++) {
    for (int weight = 0; weight <= goal; weight++) {
      if (weight - coins[i - 1] >= 0) {
        dp[weight] += dp[weight - coins[i - 1]];
        dp[weight] %= MOD;
      }
    }
  }

  std::wcout << dp[goal] << '\n';
}
#pragma endregion Second_Extra
#pragma region Third_Extra

void
third_extra()
{
  std::wcout << L"Input C1:";
  double c1 = input_value<double>();
  std::wcout << L"Input C2:";
  double c2 = input_value<double>();

  size_t counter = 0;

  do {
    if (counter % 2 == 0) {
      c2 += c1 / 2.0;
      c1 /= 2.0;
    } else {
      c1 += c2 / 2.0;
      c2 /= 2.0;
    }
    counter += 1;
  } while (counter < 12);

  std::wcout << L"After 12 transfusions values of C1 and C2 are " << c1
             << L" and " << c2 << L"\n";
}
#pragma endregion Third_Extra
#pragma region Fourth_Extra
void
fourth_extra()
{
  int mask = 1111;
  int variants[] = { 1001, 0101, 1100, 1000, 0100, 0010, 0001,
                     0110, 1010, 0011, 0111, 1011, 1101, 1110 };
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      if (i != j) {
        for (int v = 0; v < sizeof(variants) / sizeof(variants[0]); v++) {
          int variant = variants[v] * i + (mask - variants[v]) * j;
          if (sum_of_digits(variant) == 30 && variant % (2 * 7 * 11) == 0) {
            std::wcout << L"Car plate is " << variant << L"\n";
            return;
          }
        }
      }
    }
  }
  std::wcout << L"Can't find such car plate!\n";
}
#pragma endregion Fourth_Extra
#pragma region Fifth_Extra

double
formula(double n)
{
  return n * sinf64(n);
}

void
fifth_extra()
{
  double first_sum = 0.0;
  for (int i = 10; i <= 99; i++) {
    first_sum += formula(static_cast<double>(i));
  }
  double second_sum = 0.0;
  for (int i = 1; i <= 100; i++) {
    double temp = formula(static_cast<double>(i));
    if (temp > 0)
      second_sum += temp;
  }
  double third_sum = 0.0;
  for (int i = 1; i <= 100; i++) {
    double temp = formula(static_cast<double>(i));
    if (fabsf64(temp) < 0.5)
      third_sum += temp;
  }

  std::wcout
    << L"Sum of sequence term with double digit positions is " << first_sum
    << L"\n"
    << L"Sum of sequence positive terms within first hundred is " << second_sum
    << L"\n"
    << L"Sum of sequence terms with absolute value less than 0.5 within "
       L"first hundred is "
    << third_sum << L"\n";
}
#pragma endregion Fifth_Extra
#pragma region Sixth_Extra
void
sixth_extra()
{
  std::wcout << L"Input N:";
  size_t n = input_value<size_t>();
  size_t old_n = n;
  if (n == 0 || n == 1) {
    std::wcout << L"0 or 1 don't have canonical representation!\n";
    return;
  }

  if (is_prime(n)) {
    std::wcout << L"Canonical representation of " << n << L" is 1 *" << n
               << L"!\n";
    return;
  }

  std::map<size_t, int> powers = std::map<size_t, int>();
  size_t i = 2;
  std::pair<std::map<size_t, int>::iterator, bool> result;
  while (n != 1) {
    if (is_prime(i) && n % i == 0) {
      result = powers.try_emplace(i, 1);
      if (result.second == false) {
        result.first->second += 1;
      }
      n /= i;
      i = 1;
    }
    i += 1;
  }
  std::wstring str;
  for (std::map<size_t, int>::iterator iter = powers.begin();
       iter != powers.end();
       ++iter) {
    str +=
      (std::to_wstring(iter->first) + L"^" + std::to_wstring(iter->second));
    if (iter != --powers.end()) {
      str += L" * ";
    }
  }
  std::wcout << L"Canonical representation of " << old_n << L" is "
             << str.c_str() << L"!\n";
}
#pragma endregion Sixth_Extra
#pragma region Seventh_Extra

tm
make_date(int d, int m, int y)
{
  return std::tm{
    /* .tm_sec  = */ 0,
    /* .tm_min  = */ 0,
    /* .tm_hour = */ 0,
    /* .tm_mday = */ d,
    /* .tm_mon  = */ m - 1,
    /* .tm_year = */ y - 1900,
  };
}

void
print_mdy(std::tm const* date)
{
  std::wcout << std::setw(2) << std::setfill(L'0') << date->tm_mday << L'.'
             << std::setw(2) << (date->tm_mon + 1) << L'.' << std::setw(4)
             << (date->tm_year + 1900);
}

void
seventh_extra()
{

  std::wcout << L"All 'Black' Tuesdays and Fridays:\n";

  int d = 13, m = 1, y = 2016;
  std::tm date;
  while (y != 2018) {
    date = make_date(d, m, y);
    std::time_t time_temp = std::mktime(&date);
    std::tm const* time_out = std::localtime(&time_temp);

    switch (time_out->tm_wday) {
      case 2: {
        std::wcout << L"'Black' Tuesday: ";
        print_mdy(time_out);
        std::wcout << L"\n";
      } break;
      case 5: {
        std::wcout << L"'Black' Friday: ";
        print_mdy(time_out);
        std::wcout << L"\n";
      } break;
      default:
        break;
    }

    m += 1;
    if (m == 13) {
      y += 1;
      m = 1;
    }
  }
}
#pragma endregion Seventh_Extra
#pragma region Eighth_Extra

uint
count_vector_sum(const std::vector<size_t>& v, const std::vector<uint>& s)
{
  uint sum = 0;
  for (size_t i = 0; i < 4; ++i)
    sum += (s[v[i]] * s[v[i]]);
  return sum;
}

bool
is_several_variants(uint number, bool is_zero_included = false)
{
  uint sums = 0;

  std::vector<uint> v_numbers;
  for (size_t i = (is_zero_included ? 0 : 1); i <= (size_t)sqrt(number); i++) {
    v_numbers.push_back(i);
  };
  size_t v_length = v_numbers.size() - 1;
  std::vector<size_t> v(5, 0);
  while (true) {
    for (size_t i = 0; i < 4; ++i) { // vai um
      if (v[i] > v_length) {
        v[i + 1] += 1;
        for (int k = i; k >= 0; --k) {
          v[k] = v[i + 1];
        }
      }
    }

    if (v[4] > 0)
      break;

    if (count_vector_sum(v, v_numbers) == number) {
      sums += 1;
    }

    v[0] += 1;
  }

  return sums > 1 ? true : false;
}

void
eighth_extra()
{
  uint non_zero_result = 0;
  size_t i = 0;
  while (!is_several_variants(++i)) {
  }
  non_zero_result = i;
  i = 0;
  while (!is_several_variants(++i, true)) {
  }
  std::wcout << L"Minimal zero-include four-square number is " << i << L"\n"
             << L"Minimal zero-exclude four-square number is "
             << non_zero_result << L"\n";
}
#pragma endregion Eighth_Extra
}