#pragma once

#include <concepts>

template <class T> class Ptr {
  T *heap_object;
  bool has_ptr;

public:
  Ptr(T *);
  ~Ptr();

  T *release();
  T *get();
  void reset(T *);

  T *operator->();
  T *operator*();
  bool operator==(std::nullptr_t);
};

template <class T>
Ptr<T>::Ptr(T *new_object) : heap_object(new_object), has_ptr(true) {}

template <class T> Ptr<T>::~Ptr() {
  if (this->has_ptr)
    delete this->heap_object;
}

template <class T> T *Ptr<T>::operator->() { return this->heap_object; }
template <class T> T *Ptr<T>::operator*() { return this->heap_object; }
template <class T> bool Ptr<T>::operator==(std::nullptr_t x) {
  return !this->has_ptr;
}

template <class T> T *Ptr<T>::release() {
  this->has_ptr = false;
  T *temp = this->heap_object;
  this->heap_object = nullptr;
  return temp;
}

template <class T> T *Ptr<T>::get() { return this->heap_object; }
template <class T> void Ptr<T>::reset(T *new_ptr) {
  delete this->heap_object;
  this->heap_object = new_ptr;
}

template <class T, class... Args> Ptr<T> make_custom_ptr(Args &&...args) {
  return Ptr<T>(new T(std::forward<Args>(args)...));
}
