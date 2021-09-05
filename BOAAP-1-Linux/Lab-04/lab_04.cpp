#include "lab_04.h"
#include <cmath>
#include <iostream>
#include <string>
#include <wchar.h>

namespace lab_04 {

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

void
sixth_variant()
{
  std::wcout << L"\nInput n:";
  int n = static_cast<int>(input_number());

  bool is_ok = false;

  std::wstring ws_n = std::to_wstring(n);
  if (ws_n.find(L'0') != std::wstring::npos ||
      ws_n.find(L'9') != std::wstring::npos) {
    is_ok = true;
  }

  std::wcout << L"n = " << n << L", is any 0's or 9's? = " << is_ok << L"\n";
}

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

void
ninth_variant()
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

void
eleventh_variant()
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

void
twelfth_variant()
{
  std::wcout << L"\nInput x:";
  double x = input_number();
  std::wcout << L"Choose measurement:\n1)km\n2)m\n3)mm\n4)sm\nYour choice is:";
  int choice = static_cast<int>(input_number());

  switch (choice) {
    case 1:
      std::wcout << L"X in meters:" << x * 1000.0 << L"!\n";
      break;
    case 2:
      std::wcout << L"X in meters:" << x << L"!\n";
      break;
    case 3:
      std::wcout << L"X in meters:" << x / 1000.0 << L"!\n";
      break;
    case 4:
      std::wcout << L"X in meters:" << x / 100.0 << L"!\n";
      break;
    default:
      std::wcout << L"Invalid choice!\n";
      break;
  }
}

void
thirteenth_variant()
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

void
fourteenth_variant()
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

}