#ifndef IFRAME_H_
#define IFRAME_H_

template<class T>
class IFrame {
 public:
  virtual ~IFrame() {}
  virtual T get_pixel_value( const int& x, const int& y ) const = 0;
  virtual void set_pixel_value( const int& x, const int& y, const T& value ) = 0;
  virtual void deallocate() = 0;
};

#endif  // IFRAME_H_
