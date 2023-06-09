﻿#ifndef MYSTL_ALLOCATOR_H_
#define MYSTL_ALLOCATOR_H_


#include "construct.h"
#include "../Copy/util.h"

namespace mystl
{

template <class T>
class allocator { 

public:
  typedef T            value_type;
  typedef T*           pointer;
  typedef const T*     const_pointer;
  typedef T&           reference;
  typedef const T&     const_reference;
  typedef size_t       size_type;     //无符号64int
  typedef ptrdiff_t    difference_type;    //64int

public:
  static T*   allocate();                   //分配内存
  static T*   allocate(size_type n);       //分配具体内存

  static void deallocate(T* ptr);            // 释放内存
  static void deallocate(T* ptr, size_type n);   // 释放具体内存

  static void construct(T* ptr);               //构造函数
  static void construct(T* ptr, const T& value);
  static void construct(T* ptr, T&& value);

  template <class... Args>
  static void construct(T* ptr, Args&& ...args);

  static void destroy(T* ptr);                 //析构函数
  static void destroy(T* first, T* last);
};

//allocator 函数定义
template <class T>
T* allocator<T>::allocate() 
{
  return static_cast<T*>(::operator new(sizeof(T)));  //只调用operator new
}

template <class T>
T* allocator<T>::allocate(size_type n) 
{
  if (n == 0) return nullptr;
  return static_cast<T*>(::operator new(n * sizeof(T))); 
}

template <class T>
void allocator<T>::deallocate(T* ptr) 
{
  if (ptr == nullptr) return;       //只调用operator delete
  ::operator delete(ptr);
}

template <class T>
void allocator<T>::deallocate(T* ptr, size_type /*size*/) 
{
  if (ptr == nullptr) return;
  ::operator delete(ptr);
}

//调用construct.h中构造函数
template <class T>
void allocator<T>::construct(T* ptr)
{
  mystl::construct(ptr);   
}

template <class T>
void allocator<T>::construct(T* ptr, const T& value)
{
	mystl::construct(ptr, value);    
}

template <class T>
 void allocator<T>::construct(T* ptr, T&& value)
{
  mystl::construct(ptr, mystl::move(value)); 
}

template <class T>
template <class ...Args>
 void allocator<T>::construct(T* ptr, Args&& ...args)
{
  mystl::construct(ptr, mystl::forward<Args>(args)...); 
}

//调用construct.h中析构函数
template <class T>
void allocator<T>::destroy(T* ptr)
{
  mystl::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(T* first, T* last)
{
  mystl::destroy(first, last);
}

} // namespace mystl
#endif 

