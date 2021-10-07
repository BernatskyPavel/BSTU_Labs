#pragma once
#include <cstddef>
#include <inttypes.h>

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

  struct Proxy
  {
  private:
    Array& _array;

  public:
    int& element;
    Proxy(Array& array, int& el);
    operator const int&() const;
    Proxy& operator=(const int& rhs);
  };

private:
  int* _array;
  size_t _size;
  int _max = INT32_MIN;
  int _old_max = INT32_MIN;
  int _min = INT32_MAX;
  int _old_min = INT32_MAX;
  int _gen_min = 0;
  int _gen_max = 0;

  void refresh_minmax();
  void check_minmax(int element);

public:
  Array();
  Array(int* array, size_t size);
  Array(size_t len, bool is_generated = false, int min = 0, int max = 99);
  ~Array();
  double avg();
  size_t find_first(int element);
  size_t find_last(int element);
  void generate_random_array();
  void insert_at(size_t index, int element);
  void insert_after_every(int odd_or_even, int element);
  void insert_after_neg(int element);
  int min();
  int max();
  void print(bool is_endline = false);
  void push(int element, Push place);
  int remove_all(int element, bool is_logged = false);
  int remove_at(size_t index, bool is_logged = false);
  void set_generator_bounds(int min, int max);
  size_t size();
  int sum();
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
