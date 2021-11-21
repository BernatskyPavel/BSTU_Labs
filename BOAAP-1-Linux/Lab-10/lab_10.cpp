#include "lab_10.hpp"
#include <bitset>
#include <iostream>
#include <math.h>
#include <string>

#define INT_BITS sizeof(int) * 8

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
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  int zero_counter = 0;
  std::wcout << L"A: " << std::bitset<sizeof(A) * 8>(A) << L"\n";
  int32_t temp = A;
  for (size_t i = 0; i < sizeof(temp) * 8; i++) {
    if (i >= 3 && i <= 13) {
      zero_counter += !(temp & 1);
    }
    temp >>= 1;
    if (i == 14) {
      break;
    }
  }

  std::wcout << L"The number of zeros in bits from 3 to 13 of number A is "
             << zero_counter << L"\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  if (p < n) {
    n = p;
  }

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  mask <<= (p - n);

  int32_t inv_bits_from_A = ~(A & mask) & mask;
  inv_bits_from_A >>= (p - n);

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask, right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part |= inv_bits_from_A;
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion First_Variant
#pragma region Second_Variant
void
second_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();

  int32_t mask = 0x7C;
  int32_t bits_from_A = (A & mask) >> 2, right_part = B & 0x7, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B <<= 2;
  new_B |= bits_from_A;
  new_B <<= 3;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  if (n > p) {
    n = p;
  }

  int32_t new_A =
    A | (static_cast<int32_t>(pow(2, p)) - static_cast<int32_t>(pow(2, p - n)));

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(new_A) * 8>(new_A) << L"(" << new_A
             << L")\n";
}
#pragma endregion Second_Variant
#pragma region Third_Variant
void
third_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  std::wcout << L"A: " << std::bitset<sizeof(A) * 8>(A) << L"\n";
  size_t new_A = A | 0x00007FFC;
  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(new_A) << L"(" << new_A << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  p = std::min(INT_BITS - 1, p + n + 1);

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  mask <<= (p - n);

  int32_t inv_bits_from_A = ~(A & mask) & mask;
  inv_bits_from_A >>= (p - n);

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask, right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part |= inv_bits_from_A;
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Third_Variant
#pragma region Fourth_Variant
void
fourth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  std::wcout << L"Is number A divisible by 4? " << std::boolalpha
             << ((A & 0x3) == 0x0) << std::noboolalpha << L"\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  p = std::min(INT_BITS - 1, p + n + 1);

  int32_t new_A =
    A | (static_cast<int32_t>(pow(2, p)) - static_cast<int32_t>(pow(2, p - n)));

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(new_A) * 8>(new_A) << L"(" << new_A
             << L")\n";
}
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
void
fifth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  int32_t diff = 0;

  for (size_t i = 0; i < sizeof(A) * 8 - 2; i++) {
    diff += A & 0x1 ? 1 : -1;
    A >>= 1;
  }

  std::wcout << L"Difference in number of 1's and 0's in A is " << diff
             << L"\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  n = std::min(n, p);

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  int32_t bits_for_b = mask;
  mask <<= (p - n);

  A |= mask;

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask, right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part |= bits_for_b;
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
void
sixth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  A |= 0x2aaaaaaa;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  int32_t mask = 0x7 << n;
  int32_t b_mask = static_cast<int32_t>(std::pow(2, m)) - 1;
  int32_t bits_from_A = (A & mask) >> n, right_part = B & b_mask, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B |= bits_from_A;
  new_B <<= m;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";
}
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
void
seventh_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();

  int32_t mask = 0x1E0;

  B <<= 5;
  B |= ((A & mask) >> 5);

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(B) * 8>(B) << L"(" << B << L")\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  p = std::min(INT_BITS - 1, p + n + 1);

  mask = static_cast<int32_t>(pow(2, n)) - 1;
  int32_t bits_for_b = mask;
  mask <<= (p - n);

  A |= mask;

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask, right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part |= bits_for_b;
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
void
eighth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  A &= 0xdb6db6db;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  int32_t mask = 0x7 << n;
  int32_t b_mask = static_cast<int32_t>(std::pow(2, m)) - 1;
  int32_t bits_from_A = (A & mask) >> n, right_part = B & b_mask, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B |= bits_from_A;
  new_B <<= m;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";
}
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
void
ninth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();

  int32_t mask = 0xF8;
  int32_t bits_from_A = (A & mask) >> 3, right_part = B & 0x3, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B <<= 2;
  new_B |= bits_from_A;
  new_B <<= 2;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  n = std::min(n, p);

  int32_t new_A = A & ~(static_cast<int32_t>(pow(2, p)) -
                        static_cast<int32_t>(pow(2, p - n)));

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(new_A) * 8>(new_A) << L"(" << new_A
             << L")\n";
}
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  int32_t bits = A & 0xFC;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<6>(bits) << L"(" << bits << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  bits = ~A & ((static_cast<int32_t>(pow(2, n)) - 1) << (p + 1));
  int32_t right_part = A & (static_cast<int32_t>(pow(2, p + 1)) - 1);
  A &= (0xFFFFFFFF << (n + p + 1));
  A |= bits;
  A |= right_part;
  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";
}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  std::wcout << L"Is number A divisible by 16? " << std::boolalpha
             << ((A & 0xF) == 0x0) << std::noboolalpha << L"\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  p = std::min(INT_BITS - 1, p + n + 1);

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  int32_t bits_for_b = mask;
  mask <<= (p - n);
  mask = ~mask;

  A &= mask;

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask, right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part &= (0xFFFFFFFF << n);
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  int32_t bits = ~A & 0x1F0;
  int32_t right_part = A & 0xF;
  A &= 0xFFFFFE00;
  A |= bits;
  A |= right_part;
  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  n = std::min(n, p);

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  mask <<= (p - n);
  mask = ~mask;

  A &= mask;

  int32_t left_mask = INT32_MAX - static_cast<int32_t>(pow(2, m + q)) + 1,
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = B & left_mask;
  right_part = B & right_mask;

  left_part >>= (q + m);
  left_part <<= n;
  left_part &= (0xFFFFFFFF << n);
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();

  int32_t mask = 0x60;
  int32_t bits_from_A = (A & mask), right_part = B & 0x1F, new_B = B;

  new_B &= 0xFFFFFFE0;
  new_B <<= 2;
  new_B |= bits_from_A;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";

  std::wcout << L"\nSecond part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  n = std::min(n, p);

  mask = static_cast<int32_t>(pow(2, n)) - 1 << (p - n);

  int32_t inv_bits_from_A = ~(A & mask) & mask;

  A &= ~mask;
  A |= inv_bits_from_A;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";
}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  int ones_counter = 0;
  std::wcout << L"A: " << std::bitset<sizeof(A) * 8>(A) << L"\n";
  int32_t temp = A;
  for (size_t i = 0; i < sizeof(temp) * 8; i++) {
    if (i >= 5 && i <= 10) {
      ones_counter += (temp & 1);
    }
    temp >>= 1;
    if (i == 11) {
      break;
    }
  }

  std::wcout << L"The number of ones in bits from 5 to 10 of number A is "
             << ones_counter << L"\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();
  std::wcout << L"Input q:";
  size_t q = input_value<size_t>();

  int32_t mask = 0x7 << n;
  int32_t b_mask = static_cast<int32_t>(std::pow(2, m)) - 1;
  int32_t bits_from_A = (A & mask) >> n, right_part = B & b_mask, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B |= bits_from_A;
  new_B <<= m;
  new_B |= right_part;

  int32_t left_mask = ~(static_cast<int32_t>(pow(2, m + q)) - 1),
          right_mask = static_cast<int32_t>(pow(2, q)) - 1;

  int32_t left_part = new_B & left_mask;
  right_part = new_B & right_mask;

  left_part >>= (q + m);
  left_part <<= 3;
  left_part |= bits_from_A;
  left_part <<= q;
  left_part |= right_part;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(left_part) * 8>(left_part) << L"("
             << left_part << L")\n";
}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();

  std::wcout << L"Is number A divisible by 2? " << std::boolalpha
             << ((A & 0x1) == 0x0) << std::noboolalpha << L"\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();
  std::wcout << L"Input p:";
  size_t p = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  p = std::min(INT_BITS - 1, p + n + 1);

  int32_t mask = static_cast<int32_t>(pow(2, n)) - 1;
  int32_t bits_for_b = mask;
  mask <<= (p - n);
  mask = ~mask;

  A &= mask;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";
}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{
  std::wcout << L"First part:\n";
  std::wcout << L"Input A:";
  int32_t A = input_value<int32_t>();
  std::wcout << L"Input B:";
  int32_t B = input_value<int32_t>();

  int32_t mask = 0x1C;
  int32_t bits_from_A = (A & mask) >> 3, right_part = B & 0x1, new_B = B;

  new_B &= 0xFFFFFFF8;
  new_B |= bits_from_A;
  new_B <<= 1;
  new_B |= right_part;

  std::wcout << L"Number B after all changes is equal to "
             << std::bitset<sizeof(new_B) * 8>(new_B) << L"(" << new_B
             << L")\n";

  std::wcout << L"Second part:\n";
  std::wcout << L"Input A:";
  A = input_value<int32_t>();

  A |= 0x18;

  std::wcout << L"Number A after all changes is equal to "
             << std::bitset<sizeof(A) * 8>(A) << L"(" << A << L")\n";
}
#pragma endregion Sixteenth_Variant
}