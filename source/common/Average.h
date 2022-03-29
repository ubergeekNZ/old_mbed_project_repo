#ifndef _AVERAGE_H
#define _AVERAGE_H

#include <stdint.h>
#include <stdlib.h>

template<class T>
class Frame : IFrame<T>
{
 private:
  T** frame_array;
  uint32_t col_size;
  uint32_t row_size;
 public:
  explicit Frame(uint32_t col_size, uint32_t row_size);
  T get_pixel_value( const int& x, const int& y ) const;
  void set_pixel_value( const int& x, const int& y, const T& value );
  const Frame<T>& operator=( const Frame& other );
  void deallocate();
};

template<class T>
Frame<T>::Frame(uint32_t col_size, uint32_t row_size): 
	col_size(col_size), 
	row_size(row_size) 
{
  // dynamic allocation
  frame_array = new T*[col_size];
  for(int i = 0; i < col_size; ++i)
      frame_array[i] = new T[row_size];
}


#endif  // _AVERAGE_H
