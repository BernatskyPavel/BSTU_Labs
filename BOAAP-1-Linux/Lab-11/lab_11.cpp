#include "lab_11.hpp"
#include <bitset>
#include <iostream>
#include <math.h>
#include <random>
#include <string>

namespace lab_11 {

int32_t _MIN_INT = INT32_MIN;

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

template<typename T>
void
print_array(T* array, size_t size, const wchar_t* name, bool is_endline)
{
  std::wcout << L"Array " << name << L": [";
  for (size_t i = 0; i < size; i++) {
    std::wcout << *(array + i);
    if (i != size - 1) {
      std::wcout << L", ";
    }
  }
  std::wcout << L"]" << (is_endline ? L"\n" : L"");
}

int32_t
compare(const void* a, const void* b)
{
  return (*(int32_t*)a - *(int32_t*)b);
}

bool
is_number_fits(size_t number)
{
  switch (number) {
    case 1:
      return false;
    case 2:
    case 3:
    case 4:
      return true;
    default: {
      bool result = true;
      for (size_t i = 5; i < static_cast<size_t>(sqrt(number)); i++) {
        if (number % i == 0 && is) {
          result = false;
          break;
        }
      }
      return result;
    } break;
  }
}

#pragma endregion Helpers
#pragma region First_Variant
#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#define ARRAY_SIZE 10

void
first_variant()
{
  std::wcout << L"Input N:";
  int32_t N = input_value<int32_t>();
  std::wcout << L"Input m (1..9):";
  size_t m = input_value<size_t>();

  if (m == 0 || m > 9) {
    std::wcout << L"Wrong parameter m!" << std::endl;
    return;
  }

  int32_t* digits = new int32_t[ARRAY_SIZE];
  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    *(digits + i) = -1;
  }
  int32_t index = 0;

  do {
    int32_t temp = N % 10;
    if (temp % m == 0) {
      *(digits + index) = temp;
      index += 1;
    }
    N /= 10;
  } while (N != 0);

  if (index == 0) {
    std::wcout
      << L"There are no digits in the number N which are multiples of m!\n";
  } else {
    std::wcout << L"Digits of the number N which are multiples of m are ";
    for (size_t i = 0; i < index - 1; i++) {
      std::wcout << *(digits + i) << L", ";
    }
    std::wcout << *(digits + index - 1) << L".\n";
  }

  delete[] digits;
  return;
}
#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#pragma endregion First_Variant
#pragma region Second_Variant

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -1000

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 1000

void
second_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[n];
  int32_t* S = new int32_t[n];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
    *(B + i) = distribution(gen);
    *(S + i) = *(A + i) + *(B + i);
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<int32_t>(B, n, L"B", true);
  print_array<int32_t>(S, n, L"S", true);
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif

#pragma endregion Second_Variant
#pragma region Third_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
third_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input t:";
  int32_t t = input_value<int32_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[n];

  size_t t_counter_A = 0, t_counter_B = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
    if (*(A + i) < t)
      t_counter_A += 1;
    *(B + i) = distribution(gen);
    if (*(B + i) < t)
      t_counter_B += 1;
  }

  std::wcout << L"A(t) = " << t_counter_A << L" and B(t) = " << t_counter_B
             << L'\n';
  if (t_counter_A >= t_counter_B) {
    print_array<int32_t>(A, n, L"A", true);
    print_array<int32_t>(B, n, L"B", true);
  } else {
    print_array<int32_t>(B, n, L"B", true);
    print_array<int32_t>(A, n, L"A", true);
  }
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Third_Variant
#pragma region Fourth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
fourth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input k:";
  int32_t k = input_value<int32_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[k];

  int32_t** C = new int32_t*[n + 1];
  for (size_t i = 0; i <= n; i++) {
    *(C + i) = new int32_t[k + 1];
    for (size_t j = 0; j <= k; j++) {
      *(*(C + i) + j) = 0;
    }
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
  }
  for (size_t i = 0; i < k; i++) {
    *(B + i) = distribution(gen);
  }

  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= k; j++) {
      if (*(A + i - 1) == *(B + j - 1)) {
        *(*(C + i) + j) = *(*(C + i - 1) + j - 1) + 1;
      } else {
        *(*(C + i) + j) = std::max(*(*(C + i - 1) + j), *(*(C + i) + j - 1));
      }
    }
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<int32_t>(B, k, L"B", true);

  std::wcout << L"Length of max subsequence is " << *(*(C + n) + k) << L"\n";

  delete[] A;
  delete[] B;
  for (size_t i = 0; i < n; i++) {
    delete[] * (C + i);
  }
  delete[] C;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Fourth_Variant
#pragma region Fifth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
fifth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input m:";
  int32_t m = input_value<int32_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[m];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
  }
  for (size_t i = 0; i < m; i++) {
    *(B + i) = distribution(gen);
  }

  int32_t* max_elem_A = &_MIN_INT;

  for (size_t i = 0; i < n; i++) {
    if (*(A + i) > *max_elem_A) {
      max_elem_A = &(*(A + i));
    }
  }

  bool is_max_elem_in_B = false;

  for (size_t i = 0; i < m; i++) {
    if (*(B + i) == *max_elem_A) {
      is_max_elem_in_B = true;
      break;
    }
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<int32_t>(B, m, L"B", true);

  std::wcout << L"Is max element of the array A is presented in the array B? "
             << std::boolalpha << is_max_elem_in_B << std::noboolalpha << "\n";

  delete[] A;
  delete[] B;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Fifth_Variant
#pragma region Sixth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
sixth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input k:";
  int32_t k = input_value<int32_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[k];

  int32_t** C = new int32_t*[n + 1];
  for (size_t i = 0; i <= n; i++) {
    *(C + i) = new int32_t[k + 1];
    for (size_t j = 0; j <= k; j++) {
      *(*(C + i) + j) = 0;
    }
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
  }
  for (size_t i = 0; i < k; i++) {
    *(B + i) = distribution(gen);
  }

  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= k; j++) {
      if (*(A + i - 1) == *(B + j - 1)) {
        *(*(C + i) + j) = *(*(C + i - 1) + j - 1) + 1;
      } else {
        *(*(C + i) + j) = std::max(*(*(C + i - 1) + j), *(*(C + i) + j - 1));
      }
    }
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<int32_t>(B, k, L"B", true);

  std::wcout << L"Is sequence B a subsequence of sequence A? " << std::boolalpha
             << (*(*(C + n) + k) == k) << std::noboolalpha << L"\n";

  delete[] A;
  delete[] B;
  for (size_t i = 0; i < n; i++) {
    delete[] * (C + i);
  }
  delete[] C;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Sixth_Variant
#pragma region Seventh_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
seventh_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input k:";
  int32_t k = input_value<int32_t>();

  int32_t* A = new int32_t[n];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
  }

  size_t** indexes = new size_t*[3];
  for (size_t i = 0; i < 3; i++) {
    *(indexes + i) = new size_t[n + 1];
    for (size_t j = 0; j <= n; j++) {
      *(*(indexes + i) + j) = 0;
    }
  }

  for (size_t i = 0; i < n; i++) {
    size_t temp = 0;
    if (*(A + i) > k) {
      temp = 2;
    } else if (*(A + i) < k) {
      temp = 0;
    } else {
      temp = 1;
    }

    **(indexes + temp) += 1;
    *(*(indexes + temp) + **(indexes + temp)) = i;
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<size_t>(*indexes + 1, **indexes, L"LT", true);
  print_array<size_t>(*(indexes + 1) + 1, **(indexes + 1), L"EQ", true);
  print_array<size_t>(*(indexes + 2) + 1, **(indexes + 2), L"GT", true);

  delete[] A;
  for (size_t i = 0; i < 3; i++) {
    delete[] * (indexes + i);
  }
  delete[] indexes;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Seventh_Variant
#pragma region Eighth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -10

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 10
void
eighth_variant()
{
  std::wcout << L"Input k:";
  size_t k = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  int32_t* X = new int32_t[k];
  int32_t* Y = new int32_t[n];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < k; i++) {
    *(X + i) = distribution(gen);
  }
  for (size_t i = 0; i < n; i++) {
    *(Y + i) = distribution(gen);
  }

  qsort(X, k, sizeof(int32_t), compare);
  qsort(Y, n, sizeof(int32_t), compare);

  int32_t* intersect = new int32_t[std::min(n, k)];
  size_t intersect_size = 0;

  for (size_t i = 0, j = 0; i < k, j < n;) {
    if (*(X + i) == *(Y + j)) {
      *(intersect + intersect_size) = *(X + i);
      intersect_size += 1;
      i += 1;
      j += 1;
    } else if (*(X + i) > *(Y + j)) {
      j += 1;
    } else {
      i += 1;
    }
  }

  print_array<int32_t>(X, k, L"X", true);
  print_array<int32_t>(Y, n, L"Y", true);
  print_array<int32_t>(intersect, intersect_size, L"intersect", true);

  delete[] X;
  delete[] Y;
  delete[] intersect;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Eighth_Variant
#pragma region Ninth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 2

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 100
void
ninth_variant()
{
  std::wcout << L"Input N:";
  size_t n = input_value<size_t>();

  int32_t* X = new int32_t[n];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(X + i) = distribution(gen);
  }

  qsort(X, n, sizeof(int32_t), compare);

  print_array<int32_t>(X, n, L"X", true);

  delete[] X;
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
void
tenth_variant()
{}
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
void
twelfth_variant()
{}
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
void
thirteenth_variant()
{}
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
void
fourteenth_variant()
{}
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
void
fifteenth_variant()
{}
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
void
sixteenth_variant()
{}
#pragma endregion Sixteenth_Variant
}