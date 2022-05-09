#pragma once
#include <cstddef>
#include <inttypes.h>
#include <iostream>
#include <math.h>
#include <random>
#include <wchar.h>

namespace lab_10::array {

template<class T>
concept Number = std::integral<T>;

template<class T>
requires Number<T>
class Array
{
public:
  const static bool EVEN = 0;
  const static bool ODD = 1;

  enum class Push
  {
    BACK,
    FRONT
  };

  enum class Shift
  {
    LEFT,
    RIGHT
  };

  enum class Order
  {
    ASC,
    DESC
  };

  struct Proxy
  {
  private:
    Array<T>& _array;

  public:
    T& element;
    Proxy(Array<T>& array, T& el);
    operator const T&() const;
    Proxy& operator=(const T& rhs);
  };

private:
  T* _array;
  size_t _size;
  T _max = std::numeric_limits<T>::min();
  T _old_max = std::numeric_limits<T>::min();
  T _min = std::numeric_limits<T>::max();
  T _old_min = std::numeric_limits<T>::max();
  T _gen_min = std::numeric_limits<T>::max();
  T _gen_max = std::numeric_limits<T>::min();

  void refresh_minmax();
  void check_minmax(T element);
  static int32_t compare_asc(const void* a, const void* b);
  static int32_t compare_desc(const void* b, const void* a);

public:
  Array();
  Array(T* array, size_t size);
  Array(size_t len,
        bool is_generated = false,
        T min = std::numeric_limits<T>::min(),
        T max = std::numeric_limits<T>::max());
  ~Array();
  double avg();
  void clear();
  size_t find_first(T element);
  size_t find_last(T element);
  void generate_random_array();
  void insert_at(size_t index, T element);
  void insert_after_every(int odd_or_even, T element);
  void insert_after_neg(T element);
  T min();
  T max();
  void print(bool is_endline = false);
  void push(T element, Push place = Push::BACK);
  int remove_all(T element, bool is_logged = false);
  T remove_at(size_t index, bool is_logged = false);
  void set_generator_bounds(T min, T max);
  size_t size();
  void shiftc(size_t n, Shift direction);
  void sort(Order order);
  double sum();
  void swap(size_t from, size_t to);
  Proxy operator[](size_t index);
  /*int& operator[](size_t index)
  {
    static int iErr = -1;
    if (index >= this->_size) {
      std::wcout << L"Array bounds violation.\n";
      return iErr;
    } else {
      return this->_array[index];
    }
  }*/
};

#pragma region Array::Proxy
template<class T>
Array<T>::Proxy::Proxy(Array& array, T& el)
  : element(el)
  , _array(array)
{}

template<class T>
Array<T>::Proxy::operator const T&() const
{
  return element;
}

template<class T>
Array<T>::Proxy&
Array<T>::Proxy::operator=(const T& rhs)
{
  this->element = rhs;
  _array.check_minmax(this->element);
  return *this;
}
#pragma endregion Array::Proxy
#pragma region Array
template<class T>
void
Array<T>::refresh_minmax()
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
template<class T>
void
Array<T>::check_minmax(T element)
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

template<class T>
int32_t
Array<T>::compare_asc(const void* a, const void* b)
{
  return (*(T*)a - *(T*)b);
}

template<class T>
int32_t
Array<T>::compare_desc(const void* b, const void* a)
{
  return (*(T*)a - *(T*)b);
}

template<class T>
Array<T>::Array()
{
  this->_size = 0;
  this->_array = new T[0];
}
template<class T>
Array<T>::Array(T* array, size_t size)
{
  this->_array = array;
  this->_size = size;
}
template<class T>
Array<T>::Array(size_t len, bool is_generated, T min, T max)
{
  this->_array = new T[len];
  this->_size = len;
  this->_gen_min = min;
  this->_gen_max = max;
  if (is_generated) {
    this->generate_random_array();
  }
};
template<class T>
Array<T>::~Array()
{
  delete[] this->_array;
}
template<class T>
double
Array<T>::avg()
{
  return this->sum() / static_cast<double>(this->_size);
}
template<class T>
void
Array<T>::clear()
{
  this->_size = 0;
  delete[] this->_array;
  this->_array = new T[0];
  this->_max = std::numeric_limits<T>::min();
  this->_old_max = std::numeric_limits<T>::min();
  this->_min = std::numeric_limits<T>::max();
  this->_old_min = std::numeric_limits<T>::max();
  this->_gen_min = std::numeric_limits<T>::max();
  this->_gen_max = std::numeric_limits<T>::min();
}
template<class T>
size_t
Array<T>::find_first(T element)
{
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] == element) {
      return i;
    }
  }
  return (size_t)-1;
}
template<class T>
size_t
Array<T>::find_last(T element)
{
  for (size_t i = this->_size - 1; i > 0; i--) {
    if (this->_array[i] == element) {
      return i;
    }
  }
  return (size_t)-1;
}
template<class T>
void
Array<T>::generate_random_array()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<T> distribution(_gen_min, _gen_max);
  for (size_t i = 0; i < this->_size; i++) {
    this->_array[i] = distribution(gen);
  }
  refresh_minmax();
};
template<class T>
void
Array<T>::insert_at(size_t index, T element)
{
  if (index >= this->_size) {
    std::wcout << L"Array bounds violation.\n";
    return;
  }

  T* new_array = new T[++this->_size];
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
template<class T>
void
Array<T>::insert_after_every(int odd_or_even, T element)
{
  size_t add = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] % 2 == odd_or_even) {
      add += 1;
    }
  }

  T* new_array = new T[this->_size + add];

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
template<class T>
void
Array<T>::insert_after_neg(T element)
{
  size_t add = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] < 0) {
      add += 1;
    }
  }

  T* new_array = new T[this->_size + add];

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
template<class T>
T
Array<T>::min()
{
  return this->_min;
}
template<class T>
T
Array<T>::max()
{
  return this->_max;
}
template<class T>
void
Array<T>::print(bool is_endline)
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
template<class T>
void
Array<T>::push(T element, Push place)
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

  T* new_array = new T[++this->_size];
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
template<class T>
int
Array<T>::remove_all(T element, bool is_logged)
{
  size_t remove = 0;
  for (size_t i = 0; i < this->_size; i++) {
    if (this->_array[i] == element) {
      remove += 1;
    }
  }

  T* new_array = new T[this->_size - remove];
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
template<class T>
T
Array<T>::remove_at(size_t index, bool is_logged)
{
  if (index >= this->_size) {
    return -1;
  }

  T* new_array = new T[--this->_size];
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
template<class T>
void
Array<T>::set_generator_bounds(T min, T max)
{
  this->_gen_min = min;
  this->_gen_max = max;
}
template<class T>
size_t
Array<T>::size()
{
  return this->_size;
}

template<class T>
void
Array<T>::shiftc(size_t n, Shift direction)
{
  if (n == 0 || n % this->_size == 0)
    return;
  size_t offset;
  switch (direction) {
    case Shift::LEFT:
      offset = this->_size - n;
      break;

    case Shift::RIGHT:
      offset = n;
      break;
  }
  size_t new_index = offset % this->_size;
  T next = this->_array[0], buf = this->_array[new_index];
  do {
    this->_array[new_index] = next;
    next = buf;
    new_index = (new_index + offset) % this->_size;
    buf = this->_array[new_index];
  } while (new_index != 0);
  this->_array[new_index] = next;
  if (offset % 2 == 0) {
    new_index = (1 + offset) % this->_size;
    next = this->_array[1];
    buf = this->_array[new_index];
    do {
      this->_array[new_index] = next;
      next = buf;
      new_index = (new_index + offset) % this->_size;
      buf = this->_array[new_index];
    } while (new_index != 1);
    this->_array[new_index] = next;
  }
}

template<class T>
void
Array<T>::sort(Order order)
{
  switch (order) {
    case Order::ASC:
      qsort(this->_array, this->_size, sizeof(T), this->compare_asc);
      break;

    case Order::DESC:
      qsort(this->_array, this->_size, sizeof(T), this->compare_desc);
      break;
  }
}

template<class T>
double
Array<T>::sum()
{
  double sum = 0;
  for (size_t i = 0; i < this->_size; i++) {
    sum += static_cast<double>(this->_array[i]);
  }
  return sum;
}
template<class T>
void
Array<T>::swap(size_t from, size_t to)
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
template<class T>
Array<T>::Proxy
Array<T>::operator[](size_t index)
{
  static T iErr = -1;
  if (index >= this->_size) {
    std::wcout << L"Array bounds violation.\n";
    return Proxy(*this, iErr);
  } else {
    return Proxy(*this, this->_array[index]);
  }
}
#pragma endregion Array

}