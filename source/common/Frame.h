#ifndef _FRAME_H
#define _FRAME_H

#include <stdint.h>
#include <stdlib.h>
#include "IFrame.h"

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

// return value from pixel
template<class T>
T Frame<T>::get_pixel_value( const int& x, const int& y ) const
{
    return frame_array[y][x];
}

// populate frame pixel by pixel
template<class T>
void Frame<T>::set_pixel_value( const int& x, const int& y, const T& value )
{
    frame_array[y][x] = value;
} 
 
// set frame with another frame
template<class T>
const Frame<T>& Frame<T>::operator=( const Frame& other )
{
	// check if the row and col size are correct
	
    // Copy piece by piece.
    for (uint32_t y = 0; y < col_size; y++) {
        for (uint32_t x = 0; x < row_size; x++) {
            set_pixel_value( x, y, other.get_pixel_value(x, y) );
        }
    }
    return *this;
}

template<class T>
void Frame<T>::deallocate() 
{
    for(uint32_t i = 0; i < col_size; i++)
        delete[] frame_array[i];
    delete[] frame_array;
}

#endif  // _FRAME_H
