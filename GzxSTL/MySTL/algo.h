#ifndef MYSTL_ALGO_H
#define MYSTL_ALGO_H


#include <stddef.h>
#include <algorithm>

#include "../Copy/algobase.h"



namespace mystl {

/*****************************************************************************************/
// count
// 对[first, last)区间内的元素与给定值进行比较，返回元素相等的个数
/*****************************************************************************************/
template <class InputIter, class T>
size_t count(InputIter first, InputIter last, const T& value) {
    size_t n = 0;
    for(; first != last; first++) {
        if(*first == value) ++n;
    }
    return n;
}

/*****************************************************************************************/
// find
// 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
/*****************************************************************************************/
template <class InputIter, class T>
InputIter find(InputIter first, InputIter last, const T& value)
{
  while (first != last && *first != value)
    ++first;
  return first;
}

/*****************************************************************************************/
// search
// 在[first1, last1)中查找[first2, last2)的首次出现点，没有返回last1
/*****************************************************************************************/
template <class ForwardIter1, class ForwardIter2>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2) {
    auto d1 = mystl::distance(first1, last1);
    auto d2 = mystl::distance(first2, last2);
    if(d1 < d2) return last1;
    auto cur1 = first1;
    auto cur2 = first2;
    while(cur2 != last2) {
        if(*cur1 == *cur2) {
            cur1++;
            cur2++;
        }
        else {
            if(d1 == d2) return last1;  //当不等时，且d1 == d2说明不可能出现了，直接返回
            else {
                cur1 = ++first1;  //重新开始比较
                cur2 = first2;
                --d1;
            }
        }

    }
    return first1;  //每次从first1开始比较，比较完返回first1
}

/*****************************************************************************************/
// lower_bound
// 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
/*****************************************************************************************/

//1、ForwardIter版本
template <class ForwardIter, class T>
ForwardIter _lower_bound(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
    auto len = mystl::distance(first, last);
    auto middle = len; 
    ForwardIter cur;
    while(len > 0) {
        cur = first;
        middle = len >> 1; // 找到中间长度
        mystl::advance(cur, middle);  //前进到中间位置
        if(*cur < value) {
            first = cur;
            ++first;
            len = len - middle - 1;
        }
        else len = middle;
    }
    return first;

}

//2、RandomIter版本
template <class RandomIter, class T>
RandomIter _lower_bound(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag) {
    auto len = last - first;
    auto middle = len; 
    RandomIter cur;
    while(len > 0) {
        middle = len >> 1; // 找到中间长度
        cur = first + middle;
        if(*cur < value) {
            first = cur + 1;
            len = len - middle - 1;
        }
        else len = middle;
    }
    return first;
}

template <class ForwardIter, class T>
ForwardIter
lower_bound(ForwardIter first, ForwardIter last, const T& value)
{
  return mystl::_lower_bound(first, last, value, iterator_category(first));
}
    


/*****************************************************************************************/
// upper_bound
// 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
/*****************************************************************************************/
// 1、forward_iterator_tag 版本
template <class ForwardIter, class T>
ForwardIter _upper_bound(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
  auto len = mystl::distance(first, last);
  auto middle = len;
  ForwardIter cur;
  while (len > 0) {
    middle = len >> 1;
    cur = first;
    mystl::advance(cur, middle);
    if (*cur > value) {
      len = middle;
    }
    else {
      first = middle;
      ++first;
      len = len - middle - 1;
    }
  }
  return first;
}

// 2、random_access_iterator_tag 版本
template <class RandomIter, class T>
RandomIter _upper_bound(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag)
{
  auto len = last - first;
  auto middle = len;
  RandomIter cur;
  while (len > 0) {
    middle = len >> 1;
    cur = first + middle;
    if (*cur > value) {
      len = middle;
    }
    else {
      first = middle + 1;
      len = len - middle - 1;
    }
  }
  return first;
}

template <class ForwardIter, class T>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const T& value)
{
  return mystl::_upper_bound(first, last, value, iterator_category(first));
}


/*****************************************************************************************/
// equal_range
// 查找[first,last)区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首尾
// 第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素
/*****************************************************************************************/
//forwardIter 版本
template <class ForwardIter, class T>
mystl::pair<ForwardIter, ForwardIter> _equal_range(ForwardIter first, ForwardIter last, const T& value, forward_iterator_tag) {
  auto len = mystl::distance(first, last);
  auto middle = len;
  ForwardIter cur, left, right;
  while (len > 0)
  {
    middle = len >> 1;
    cur = first;
    mystl::advance(cur, middle);
    if (*cur < value) {
      first = cur;
      ++first;
      len = len - middle - 1;
    }
    else if (value < *cur) {
      len = middle;
    }
    else {
      left = mystl::lower_bound(first, last, value);
      mystl::advance(first, len);  //调整到更新过的last位置
      right = mystl::upper_bound(++middle, first, value);
      return mystl::pair<ForwardIter, ForwardIter>(left, right);
    }
  }
  return mystl::pair<ForwardIter, ForwardIter>(last, last);  //不存在
}

//2、randomIter 版本
template <class RandomIter, class T>
mystl::pair<RandomIter, RandomIter> _equal_range(RandomIter first, RandomIter last, const T& value, random_access_iterator_tag) {
  auto len = last - first;
  auto middle = len;
  RandomIter cur, left, right;
  while (len > 0) {
    middle = len >> 1;
    cur = first + middle;
    if (*cur < value) {
      first = cur + 1;
      len = len - middle - 1;
    }
    else if (value < *cur) {
      len = middle;
    }
    else {
      left = mystl::lower_bound(first, last, value);
      right = mystl::upper_bound(++middle, first + len, value); //调整到更新过的last位置
      return mystl::pair<RandomIter, RandomIter>(left, right);
    }
  }
  return mystl::pair<RandomIter, RandomIter>(last, last);  //不存在
}

template <class ForwardIter, class T>
mystl::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const T& value) {
  return mystl::_equal_range(first, last, value, iterator_category(first));
}


/*****************************************************************************************/
// reverse
// 将[first, last)区间内的元素反转
/*****************************************************************************************/
// reverse_dispatch 的 bidirectional_iterator_tag 版本
template <class BidirectionalIter>
void _reverse(BidirectionalIter first, BidirectionalIter last, bidirectional_iterator_tag) {
  while (true) {
    if (first == last || first == --last) return;
    mystl::iter_swap(first++, last);
  }
}

// reverse_dispatch 的 random_access_iterator_tag 版本
template <class RandomIter>
void _reverse(RandomIter first, RandomIter last, random_access_iterator_tag) {
  while (first < last)
    mystl::iter_swap(first++, --last);
}

template <class BidirectionalIter>
void reverse(BidirectionalIter first, BidirectionalIter last) {
  mystl::_reverse(first, last, iterator_category(first));
}

/*****************************************************************************************/
// median
// 找出三个值的中间值
/*****************************************************************************************/
template <class T>
const T& median(const T& left, const T& mid, const T& right) {
  if (left < mid)
    if (mid < right)        // left < mid < right
      return mid;
    else if (left < right)  // left < right <= mid
      return right;
    else                    // right <= left < mid
      return left;
  else if (left < right)      // mid <= left < right
    return left;
  else if (mid < right)       // mid < right <= left
    return right;
  else                        // right <= mid <= left
    return mid;
}

/*****************************************************************************************/
// sort
// 将[first, last)内的元素以递增的方式排序
/*****************************************************************************************/
constexpr static size_t changeSort= 128;  // 在这个大小内采用插入排序

template <class Size>
Size slg2(Size n) { // 找出 lgn <= k 的 k 的最小值
  Size k = 0;
  for (; n > 1; n >>= 1)
    ++k;
  return k;
}

// 分割函数 unchecked_partition
template <class RandomIter, class T>
RandomIter
unchecked_partition(RandomIter first, RandomIter last, const T& pivot) {
  while (true) {
    while (*first < pivot) ++first;
    --last;
    while (pivot < *last) --last;
    if (!(first < last)) return first;
    mystl::iter_swap(first, last);
    ++first;
  }
}


// 内省式排序，先进行快速排序，超过depth_limit，采用堆排序
template <class RandomIter, class Size>
void intro_sort(RandomIter first, RandomIter last, Size depth_limit) {
  while (static_cast<size_t>(last - first) > changeSort) {
    if (depth_limit == 0) {                     // 到达最大深度
      std::partial_sort(first, last, last);  // 改用 heap_sort
      return;
    }
    --depth_limit;
    auto mid = mystl::median(*(first), *(first + (last - first) / 2), *(last - 1));    //找中间值
    auto cut = mystl::unchecked_partition(first, last, mid);  //cur前小于mid，cut后大于mid
    mystl::intro_sort(cut, last, depth_limit);  //快排后面
    last = cut;  //快排前面
  }
}

// 插入排序辅助函数 unchecked_linear_insert
//last前为有序数组，将last的值，从后向前插入
template <class RandomIter, class T>
void unchecked_linear_insert(RandomIter last, const T& value) {
  auto next = last;
  --next;
  while (value < *next) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

// 插入排序函数 unchecked_insertion_sort
template <class RandomIter>
void unchecked_insertion_sort(RandomIter first, RandomIter last)
{
  for (auto i = first; i != last; ++i)
  {
    mystl::unchecked_linear_insert(i, *i);
  }
}


// 插入排序函数 insertion_sort
template <class RandomIter>
void insertion_sort(RandomIter first, RandomIter last) {
  if (first == last) return;
  for (auto i = first + 1; i != last; ++i) {
    auto value = *i;
    if (value < *first) {
      mystl::copy_backward(first, i, i + 1);  //从后向前拷贝
      *first = value;  //将最小的copy到first位置
    }
    else {
      mystl::unchecked_linear_insert(i, value);
    }
  }
}

// 最终插入排序函数 final_insertion_sort
//对小区间进行插入排序
template <class RandomIter>
void final_insertion_sort(RandomIter first, RandomIter last) {
  if (static_cast<size_t>(last - first) > changeSort) {
    mystl::insertion_sort(first, first + changeSort);  //排序changeSort大小
    mystl::unchecked_insertion_sort(first + changeSort, last);  //后面的依次执行插入排序
  }
  else {
    mystl::insertion_sort(first, last); //排序changeSort大小
  }
}

template <class RandomIter>
void sort(RandomIter first, RandomIter last) {
  if (first != last) {
    // 内省式排序将区间分为一个个小区间
    mystl::intro_sort(first, last, slg2(last - first) * 2);
    //对小区间进行插入排序
    mystl::final_insertion_sort(first, last);
  }
}

}  //namespace


#endif














