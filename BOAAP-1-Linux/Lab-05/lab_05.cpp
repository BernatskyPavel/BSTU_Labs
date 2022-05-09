#include "lab_05.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <wchar.h>

namespace lab_05 {
#pragma region Helpers
double
input_number()
{
  double temp;
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

Order
partial_cmp(int a, int b)
{
  Order result;

  if (a == b) {
    result = Order::EQUAL;
  } else if (a > b) {
    result = Order::GREATER;
  } else {
    result = Order::LESS;
  }

  return result;
}
#pragma endregion Helpers
#pragma region First_Variant
void
first_variant()
{
  std::wcout << L"\nInput m:";
  double m = input_number();
  std::wcout << L"Input n:";
  double n = input_number();
  std::wcout << L"Input p:";
  double p = input_number();

  int i = 0;
  if (m < 0.0) {
    i += 1;
  }
  if (n < 0.0) {
    i += 1;
  }
  if (p < 0.0) {
    i += 1;
  }

  std::wcout << L"m = " << m << L", n = " << n << L", p = " << p
             << L", negatives = " << i << L"\n";
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  std::wcout << L"\nInput a:";
  double a = input_number();
  std::wcout << L"Input b:";
  double b = input_number();
  std::wcout << L"Input c:";
  double c = input_number();

  bool is_paired = false;
  if (a == b || a == c || b == c) {
    is_paired = true;
  }

  std::wcout << L"a = " << a << L", b = " << b << L", c = " << c
             << L", is any paired? = " << is_paired << L"\n";
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  std::wcout << L"\nInput a:";
  double a = input_number();
  std::wcout << L"Input b:";
  double b = input_number();
  std::wcout << L"Input c:";
  double c = input_number();

  double mean = 0.0;
  if (a * b * c == 0) {
    mean = (a + b + c) / 3.0;
  } else {
    mean = powf(a * b * c, (1.0 / 3.0));
  }

  std::wcout << L"a = " << a << L", b = " << b << L", c = " << c << L", mean = "
             << mean << L"\n";
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  std::wcout << L"\nInput month:";
  int month = static_cast<int>(input_number());

  switch (month) {
    case 12:
    case 1 ... 2:
      std::wcout << L"Season: Winter!\n";
      break;
    case 3 ... 5:
      std::wcout << L"Season: Spring!\n";
      break;
    case 6 ... 8:
      std::wcout << L"Season: Summer!\n";
      break;
    case 9 ... 11:
      std::wcout << L"Season: Autumn!\n";
      break;
    default:
      std::wcout << L"Invalid month!\n";
      break;
  }
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  std::wcout << L"\nInput a:";
  int a = static_cast<int>(input_number());
  std::wcout << L"Input b:";
  int b = static_cast<int>(input_number());
  std::wcout << L"Input c:";
  int c = static_cast<int>(input_number());
  std::wcout << L"Input d:";
  int d = static_cast<int>(input_number());

  bool is_odd = false;

  if (a % 2 != 0) {
    is_odd = true;
  } else if (b % 2 != 0) {
    is_odd = true;
  } else if (c % 2 != 0) {
    is_odd = true;
  } else if (d % 2 != 0) {
    is_odd = true;
  }
  std::wcout.setf(std::ios::boolalpha);
  std::wcout << L"a = " << a << L", b = " << b << L", c = " << c << L", d = "
             << d << L", is any odds? = " << is_odd << L"\n";
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  std::wcout << L"\nInput n:";
  int n = static_cast<int>(input_number());

  bool is_ok = false;

  std::wstring ws_n = std::to_wstring(n);
  if (ws_n.find(L'0') != std::wstring::npos ||
      ws_n.find(L'1') != std::wstring::npos) {
    is_ok = true;
  }

  std::wcout << L"n = " << n << L", is any 0's or 1's? = " << is_ok << L"\n";
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  std::wcout << L"\nInput year:";
  int year = static_cast<int>(input_number());

  bool is_leap = false;

  if (year % 4 == 0) {
    if (year % 100 == 0) {
      is_leap = (year % 400 == 0);
    } else {
      is_leap = true;
    }
  }

  std::wcout << L"year = " << year << L", is year leap? = " << is_leap << L"\n";
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  std::wcout << L"\nInput n:";
  int n = static_cast<int>(input_number());

  bool is_ok = true;

  std::wstring ws_n = std::to_wstring(n);
  std::wstring temp = std::wstring();
  for (std::wstring::iterator iter = ws_n.begin(); iter != ws_n.end(); ++iter) {
    if (temp.find(*iter) != std::wstring::npos) {
      is_ok = false;
      break;
    }
    temp += *iter;
  }

  std::wcout << L"n = " << n << L", is all digits unique? = " << is_ok << L"\n";
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  std::wcout << L"\nInput a:";
  int a = static_cast<int>(input_number());
  std::wcout << L"Input b:";
  int b = static_cast<int>(input_number());

  bool is_proper = false;

  if (abs(a) < abs(b)) {
    is_proper = true;
  }

  std::wcout << L"a = " << a << L", b = " << b << L", a/b = "
             << static_cast<double>(a) / static_cast<double>(b)
             << L", is proper fraction? = " << is_proper << L"\n";
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  std::wcout << L"\nInput n:";
  int n = static_cast<int>(input_number());

  int buff = n;
  int sum = 0;

  do {
    sum += (buff % 10);
    buff /= 10;
  } while (buff / 10 != 0);

  sum += (buff % 10);

  std::wcout << L"n = " << n << L", is dividable on 3? = " << (sum % 3 == 0)
             << L"\n";
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  const wchar_t* ends[] = { L"год", L"года", L"года", L"года", L"лет",
                            L"лет", L"лет",  L"лет",  L"лет" };

  std::wcout << L"\nInput k:";
  int k = static_cast<int>(input_number());

  switch (k) {
    case 1 ... 9:
      std::wcout << L"\nМне " << k << L" " << ends[k - 1] << L"!\n";
      break;
    default:
      std::wcout << L"\nInvalid input!\n";
      break;
  }
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  std::wcout << L"\nInput n:";
  int n = static_cast<int>(input_number());

  bool is_ok = false;

  std::wstring ws_n = std::to_wstring(n);
  if (ws_n.find(L'9') != std::wstring::npos ||
      ws_n.find(L'1') != std::wstring::npos) {
    is_ok = true;
  }

  std::wcout << L"n = " << n << L", is any 1's or 9's? = " << is_ok << L"\n";
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{

  const wchar_t* ends[] = { L"ов", L"",   L"а",  L"а",  L"ов", L"ов", L"ов",
                            L"ов", L"ов", L"ов", L"ов", L"ов", L"ов", L"ов",
                            L"ов", L"ов", L"ов", L"ов", L"ов", L"ов" };

  std::wcout << L"\nInput k:";
  int k = static_cast<int>(input_number());

  const wchar_t* end;

  if (k < 20) {
    end = ends[k];
  } else {
    end = ends[k % 10];
  }

  std::wcout << L"\nМы нашли " << k << L" гриб" << end << L" в лесу!\n";
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  std::wcout << L"\nInput a:";
  double a = input_number();
  std::wcout << L"Input b:";
  double b = input_number();
  std::wcout << L"Input c:";
  double c = input_number();

  double d = 0.0;

  if (a > d) {
    d = a;
  }
  if (b > d) {
    d = b;
  }
  if (c > d) {
    d = c;
  }

  std::wcout << L"a = " << a << L", b = " << b << L", c = " << c << L", d = "
             << d << L"\n";
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  std::wcout << L"\nInput a:";
  int a = static_cast<int>(input_number());
  std::wcout << L"Input b:";
  int b = static_cast<int>(input_number());
  std::wcout << L"Input c:";
  int c = static_cast<int>(input_number());
  std::wcout << L"Input d:";
  int d = static_cast<int>(input_number());

  bool is_even = false;

  if (a % 2 == 0) {
    is_even = true;
  } else if (b % 2 == 0) {
    is_even = true;
  } else if (c % 2 == 0) {
    is_even = true;
  } else if (d % 2 == 0) {
    is_even = true;
  }
  std::wcout.setf(std::ios::boolalpha);
  std::wcout << L"a = " << a << L", b = " << b << L", c = " << c << L", d = "
             << d << L", is any evens? = " << is_even << L"\n";
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  const wchar_t* ends[] = { L"Нуль", L"Один",  L"Два",  L"Три",    L"Четыре",
                            L"Пять", L"Шесть", L"Семь", L"Восемь", L"Девять" };

  std::wcout << L"\nInput k:";
  int k = static_cast<int>(input_number());

  switch (k) {
    case 0 ... 9:
      std::wcout << L"\nDigit name is " << ends[k] << L"!\n";
      break;
    default:
      std::wcout << L"\nInvalid input!\n";
      break;
  }
}
#pragma endregion Sixteenth_Variant
#pragma region Dialog
void
dialog()
{
  srand(time(NULL));
restart:
  int number = rand() % 100 + 1;
  std::wcout << L"Guess the number!\n";
  for (;;) {
    std::wcout << L"Your guess is ";
    int guess = static_cast<int>(input_number());

    switch (partial_cmp(guess, number)) {
      case Order::EQUAL: {
        std::wcout << L"You won!\n";
        std::wcout << L"Are you wanna another number?(1-yes, 0-no)\n";
        int inner_choice = static_cast<int>(input_number());
        switch (inner_choice) {
          case 1:
            goto restart;
            break;
          case 0:
          default:
            goto exit;
            break;
        }
      } break;
      case Order::LESS: {
        std::wcout << L"Your guess is lower than actual number!\n";
        goto choicer;
      } break;
      case Order::GREATER: {
        std::wcout << L"Your guess is greater than actual number!\n";
        goto choicer;
      } break;
    }

  choicer:
    std::wcout << L"Are you wanna another try?(1-yes, 0-no)\n";
    int choice = static_cast<int>(input_number());
    switch (choice) {
      case 1:
        continue;
        break;
      case 0:
      default:
        goto exit;
        break;
    }
  }
exit:
  return;
}
#pragma endregion Dialog
}