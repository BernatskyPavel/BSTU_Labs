#include "array.hpp"
#include <iostream>
#include <random>
#include <wchar.h>

namespace lab_09::array {
#pragma region Array::Proxy
Array::Proxy::Proxy(Array& array, int& el)
  : element(el)
  , _array(array)
{}

Array::Proxy::operator const int&() const
{
  return element;
}

Array::Proxy&
Array::Proxy::operator=(const int& rhs)
{
  this->element = rhs;
  _array.check_minmax(this->element);
  return *this;
}
#pragma endregion Array::Proxy
#pragma region Array
void
Array::refresh_minmax()
{
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_min > this->_array[i]) {
      this->_min = this->_array[i];
    }
    if (this->_max < this->_array[i]) {
      this->_max = this->_array[i];
    }
  }
}
void
Array::check_minmax(int element)
{
  if (this->_min > element) {
    this->_old_min = this->_min;
    this->_min = element;
  }
  if (this->_max < element) {
    this->_old_max = this->_max;
    this->_max = element;
  }
}
Array::Array()
{
  this->_size = 0;
  this->_array = new int[0];
}
Array::Array(int* array, size_t size)
{
  this->_array = array;
  this->_size = size;
}
Array::Array(size_t len, bool is_generated, int min, int max)
{
  this->_array = new int[len];
  this->_size = len;
  this->_gen_min = min;
  this->_gen_max = max;
  if (is_generated) {
    this->generate_random_array();
  }
};
Array::~Array()
{
  delete[] this->_array;
}
double
Array::avg()
{
  return static_cast<double>(this->sum()) / static_cast<double>(this->_size);
}
size_t
Array::find_first(int element)
{
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] == element) {
      return i;
    }
  }
  return (size_t)-1;
}
size_t
Array::find_last(int element)
{
  for (size_t i = this->_size - 1; i > 0; i--) {
    if (this->_array[i] == element) {
      return i;
    }
  }
  return (size_t)-1;
}
void
Array::generate_random_array()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(_gen_min, _gen_max);
  for (size_t i = 0; i < this->_size; i++) {
    this->_array[i] = distribution(gen);
  }
  refresh_minmax();
};
void
Array::insert_at(size_t index, int element)
{
  if (index >= this->_size) {
    std::wcout << L"Array bounds violation.\n";
    return;
  }

  int* new_array = new int[++this->_size];
  for (size_t i = 0, j = 0; j < this->_size; i++, j++) {
    if (index == j) {
      new_array[j] = element;
      i -= 1;
    } else {
      new_array[j] = this->_array[i];
    }
  }
  check_minmax(element);
  delete[] this->_array;
  this->_array = new_array;
  return;
}
void
Array::insert_after_every(int odd_or_even, int element)
{
  size_t add = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] % 2 == odd_or_even) {
      add += 1;
    }
  }

  int* new_array = new int[this->_size + add];

  for (size_t i = 0, j = 0; i < this->_size; i++, j++) {
    new_array[j] = this->_array[i];
    if (this->_array[i] % 2 == odd_or_even) {
      new_array[++j] = element;
    }
  }
  check_minmax(element);
  delete[] this->_array;
  this->_array = new_array;
  this->_size += add;
  return;
}
void
Array::insert_after_neg(int element)
{
  size_t add = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] < 0) {
      add += 1;
    }
  }

  int* new_array = new int[this->_size + add];

  for (size_t i = 0, j = 0; i < this->_size; i++, j++) {
    new_array[j] = this->_array[i];
    if (this->_array[i] < 0) {
      new_array[++j] = element;
    }
  }
  check_minmax(element);
  delete[] this->_array;
  this->_array = new_array;
  this->_size += add;
  return;
}
int
Array::min()
{
  return this->_min;
}
int
Array::max()
{
  return this->_max;
}
void
Array::print(bool is_endline)
{
  std::wcout << L"[";
  for (size_t i = 0; i < this->_size; i++) {
    std::wcout << this->_array[i];
    if (i != this->_size - 1) {
      std::wcout << L", ";
    }
  }
  std::wcout << L"]" << (is_endline ? L"\n" : L"");
}
void
Array::push(int element, Push place)
{
  size_t start, index;
  switch (place) {
    case Push::FRONT: {
      start = 1;
      index = 0;
    } break;
    case Push::BACK: {
      start = 0;
      index = this->_size;
    } break;
  }

  int* new_array = new int[++this->_size];
  size_t i;
  for (i = start; i < this->_size - (1 - start); i++) {
    new_array[i] = this->_array[i - start];
  }
  new_array[index] = element;
  check_minmax(element);
  delete[] this->_array;
  this->_array = new_array;
  return;
}
int
Array::remove_all(int element, bool is_logged)
{
  size_t remove = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] == element) {
      remove += 1;
    }
  }

  int* new_array = new int[this->_size - remove];
  for (size_t i = 0, j = 0; i < this->_size; i++, j++) {
    if (this->_array[i] == element) {
      if (is_logged) {
        std::wcout << L"Removing element " << element << L" from position " << i
                   << L"\n";
      }
      j -= 1;
    } else {
      new_array[j] = this->_array[i];
    }
  }

  delete[] this->_array;
  this->_array = new_array;
  this->_size -= remove;
  if (element == this->_max) {
    this->_max = this->_old_max;
  }
  if (element == this->_min) {
    this->_min = this->_old_min;
  }
  return remove;
}
int
Array::remove_at(size_t index, bool is_logged)
{
  if (index >= this->_size) {
    return -1;
  }

  int* new_array = new int[--this->_size];
  int deleted = -1;
  for (size_t i = 0, j = 0; i < this->_size + 1; i++, j++) {
    if (i == index) {
      if (is_logged) {
        std::wcout << L"Removing element " << this->_array[i]
                   << L" from position " << i << L"\n";
      }
      deleted = this->_array[i];
      j -= 1;
    } else {
      new_array[j] = this->_array[i];
    }
  }
  delete[] this->_array;
  this->_array = new_array;
  if (deleted == this->_max) {
    this->_max = this->_old_max;
  }
  if (deleted == this->_min) {
    this->_min = this->_old_min;
  }
  return deleted;
}
void
Array::set_generator_bounds(int min, int max)
{
  this->_gen_min = min;
  this->_gen_max = max;
}
size_t
Array::size()
{
  return this->_size;
}
int
Array::sum()
{
  int sum = 0;
  for (size_t i = 0; i < this->_size; i++) {
    sum += this->_array[i];
  }
  return sum;
}
void
Array::swap(size_t from, size_t to)
{
  if (from == to)
    return;
  if (from >= this->_size || to >= this->_size) {
    std::wcout << L"Invalid parameters!\n";
    return;
  }

  this->_array[from] += this->_array[to];
  this->_array[to] = this->_array[from] - this->_array[to];
  this->_array[from] -= this->_array[to];
  return;
}
Array::Proxy
Array::operator[](size_t index)
{
  static int iErr = -1;
  if (index >= this->_size) {
    std::wcout << L"Array bounds violation.\n";
    return Proxy(*this, iErr);
  } else {
    return Proxy(*this, this->_array[index]);
  }
}
#pragma endregion Array
}