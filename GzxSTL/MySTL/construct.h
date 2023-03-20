#ifndef MYSTL_CONSTRUCT_H
#define MTSTL_CONSTRUCT_H

#include <new>

#include "../Copy/iterator.h"
#include "../Copy/type_traits.h"



namespace mystl
{

/*****************************************************************/
//constrct函数：构造对象
/*****************************************************************/

template <class Ty>
void construct(Ty* ptr) {
    ::new ((void*)ptr) Ty();
}

template <class Ty1, class Ty2>
void construct(Ty1* ptr, const Ty2& value) {
    ::new ((void*)ptr) Ty1(value);
}

template <class Ty, class... Args>
void construct(Ty* ptr, Args&& ...args) {
    ::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);
}






/*****************************************************************/
//destroy函数：析构对象
/*****************************************************************/

//true_type，什么都不做
template <class Ty>
void destroy_one(Ty*, std::true_type) {}

//false_type，调用对象本身的析构函数
template <class Ty>
void destroy_one(Ty* pointer, std::false_type) {
  if (pointer != nullptr)
  {
    //pointer->~Ty();
    destroy(&*pointer);
  }
}

//true_type，什么都不做
template <class ForwardIter>
void destroy_cat(ForwardIter , ForwardIter , std::true_type) {}


//false_type，调用对象本身的析构函数
template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
  for (; first != last; ++first)
    destroy(&*first);
}

template <class Ty>
void destroy(Ty* pointer) {
  destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}

template <class ForwardIter>
void destroy(ForwardIter first, ForwardIter last) {
  destroy_cat(first, last, std::is_trivially_destructible<
              typename iterator_traits<ForwardIter>::value_type>{});
}


} //namespace



#endif