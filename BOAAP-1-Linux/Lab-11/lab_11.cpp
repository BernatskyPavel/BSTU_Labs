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

int32_t
compare_desc(const void* b, const void* a)
{
  return (*(int32_t*)a - *(int32_t*)b);
}

int
is_prime(size_t n)
{
  unsigned int p;
  if (!(n & 1) || n < 2)
    return n == 2;

  for (p = 3; p <= n / p; p += 2)
    if (!(n % p))
      return 0;
  return 1;
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
      for (size_t i = 5; i < number; i++) {
        if (is_prime(i) && number % i == 0) {
          return false;
        }
      }
      return number % 2 == 0 || number % 3 == 0;
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

  delete[] A;
  delete[] B;
  delete[] S;
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

  delete[] A;
  delete[] B;
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
  // In process
}

#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Ninth_Variant
#pragma region Tenth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 0

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 10
#endif

void
tenth_variant()
{
  int32_t *A = new int32_t[ARRAY_SIZE], *B = new int32_t[ARRAY_SIZE];
  int32_t* min = A;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    *(B + i) = distribution(gen);
  }

  for (size_t i = 0; i < ARRAY_SIZE; i++) {
    *(A + i) = distribution(gen);

    int temp = 0;
    for (size_t j = 0; j < ARRAY_SIZE; j++) {
      if (*(A + i) != *(B + j)) {
        temp += 1;
      } else {
        break;
      }
    }
    if (temp == ARRAY_SIZE) {
      if (*(A + i) < *min) {
        min = &*(A + i);
      }
    }
  }

  print_array<int32_t>(A, ARRAY_SIZE, L"A", true);
  print_array<int32_t>(B, ARRAY_SIZE, L"B", true);
  std::wcout << L"Min: " << *min << "\n";
  delete[] A;
  delete[] B;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Tenth_Variant
#pragma region Eleventh_Variant
void
eleventh_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  u_int32_t* A = new u_int32_t[n];

  for (size_t i = 0; i < n; i++) {
    *(A + i) = input_value<u_int32_t>();
  }

  qsort(A, n, sizeof(u_int32_t), compare);

  u_int32_t missing = 0;
  for (size_t i = 0; i < n; i++) {
    if (missing < *(A + i)) {
      break;
    }
    if (missing == *(A + i)) {
      missing += 1;
    }
  }

  print_array<u_int32_t>(A, n, L"A", true);
  std::wcout << L"Min: " << missing << "\n";
  delete[] A;
  return;
}
#pragma endregion Eleventh_Variant
#pragma region Twelfth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 0

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20

void
twelfth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  int32_t* A = new int32_t[n];
  int32_t* B = new int32_t[n];

  size_t lt = 0, eq = 0, gt = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
    *(B + i) = distribution(gen);
    if (*(A + i) > *(B + i)) {
      gt += 1;
    } else if (*(A + i) < *(B + i)) {
      lt += 1;
    } else {
      eq += 1;
    }
  }

  print_array<int32_t>(A, n, L"A", true);
  print_array<int32_t>(B, n, L"B", true);
  std::wcout << L"A[k] > B[k]: " << gt << "\n"
             << L"A[k] < B[k]: " << lt << "\n"
             << L"A[k] == B[k]: " << eq << "\n";

  delete[] A;
  delete[] B;
  return;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Twelfth_Variant
#pragma region Thirteenth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 0

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20

void
thirteenth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  int32_t* X = new int32_t[n];
  bool is_breaked = false;
  size_t counter = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(X + i) = distribution(gen);
    for (size_t j = 0; j < i; j++) {
      if (*(X + i) == *(X + j)) {
        is_breaked = true;
        break;
      }
    }
    if (!is_breaked) {
      counter += 1;
    } else {
      is_breaked = false;
    }
  }

  print_array<int32_t>(X, n, L"X", true);
  std::wcout << L"Number of different values in array X is " << counter << "\n";

  delete[] X;
  return;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Thirteenth_Variant
#pragma region Fourteenth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 0

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20
void
fourteenth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input m:";
  size_t m = input_value<size_t>();

  int32_t* X = new int32_t[n];
  int32_t* Y = new int32_t[m];

  bool is_first = true;
  size_t counter = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(X + i) = distribution(gen);
  }
  for (size_t i = 0; i < m; i++) {
    *(Y + i) = distribution(gen);
  }

  print_array<int32_t>(X, n, L"X", true);
  print_array<int32_t>(Y, m, L"Y", true);
  std::wcout << L"Same elements of array:\n";

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (*(X + i) == *(Y + j)) {
        counter += 1;
        if (!is_first) {
          std::wcout << L", ";
        } else {
          is_first = false;
        }
        std::wcout << L"(X[" << i << L"], Y[" << j << L"])";
      }
    }
  }
  std::wcout << L'\n' << L"Number of same elements: " << counter << L'\n';

  delete[] X;
  delete[] Y;
  return;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Fourteenth_Variant
#pragma region Fifteenth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN -20

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20
void
fifteenth_variant()
{
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();

  int32_t* A = new int32_t[n];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int32_t> distribution(RANDOM_MIN, RANDOM_MAX);
  for (size_t i = 0; i < n; i++) {
    *(A + i) = distribution(gen);
  }

  qsort(A, n, sizeof(int32_t), compare_desc);

  print_array<int32_t>(A, n, L"A", true);

  delete[] A;
  return;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Fifteenth_Variant
#pragma region Sixteenth_Variant
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif
#define RANDOM_MIN 0

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#define RANDOM_MAX 20
void
sixteenth_variant()
{
  std::wcout << L"Input k:";
  size_t k = input_value<size_t>();
  std::wcout << L"Input n:";
  size_t n = input_value<size_t>();
  std::wcout << L"Input q:";
  int32_t q = input_value<int32_t>();

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

  print_array<int32_t>(X, k, L"X", true);
  print_array<int32_t>(Y, n, L"Y", true);

  int32_t dist = INT32_MAX, sum = 0;

  for (size_t i = 0; i < k; i++) {
    for (size_t j = 0; j < n; j++) {
      if (abs(q - *(X + i) - *(Y + j)) < dist) {
        sum = *(X + i) + *(Y + j);
        dist = abs(q - sum);
      }
    }
  }

  std::wcout << L"Closest sum is " << sum << L"\n";

  delete[] X;
  delete[] Y;
  return;
}
#ifdef RANDOM_MIN
#undef RANDOM_MIN
#endif

#ifdef RANDOM_MAX
#undef RANDOM_MAX
#endif
#pragma endregion Sixteenth_Variant
}