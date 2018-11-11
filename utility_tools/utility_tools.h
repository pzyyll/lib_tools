// utility_tools.cpp
// @date 2018-11-10
// @author caizhili
// @brief utility_tools

#include <algorithm>

namespace lib_tools {


/**
 *  @brief 找到有序（升序）数组区间对应的下标，左开右闭，例如提供有序数组 [10, 20, 500]
 *         则有区间对应关系 ：
 *         (无穷小, 10] => 0, (10, 20] => 1, (20,500] => 2, (500, 无穷大) => 3
 *  @param  begin_iter   An iterator.
 *  @param  end_iter     Another iterator.
 *  @param  val          The search term.
 *  @return  返回区间对应的 index
*/
template <typename Iter, typename Tp>
unsigned IndexLowerBound(Iter begin_iter, Iter end_iter, const Tp &val) {
    Iter first_iter = std::lower_bound(begin_iter, end_iter, val);
    return std::distance(begin_iter, first_iter);
}


template <typename Iter, typename Tp, typename Compare>
unsigned IndexLowerBound(Iter begin_iter, Iter end_iter, const Tp &val, Compare comp) {
    Iter first_iter = std::lower_bound(begin_iter, end_iter, val, comp);
    return std::distance(begin_iter, first_iter);
}


/**
 * @brief 找到有序（升序）数组区间对应的下标，左闭右开，例如提供有序数组 [10, 20, 500]
 *        则有区间对应关系 ：
 *        (无穷小, 10) => 0, [10, 20) => 1, [20, 500) => 2, [500, 无穷大) => 3
 * @param begin_iter An iterator.
 * @param end_iter   Another iterator.
 * @param val        The search term.
 * @return 返回区间对应的 index
 */
template <typename Iter, typename Tp>
unsigned IndexLowerBoundRightOpen(Iter begin_iter, Iter end_iter, const Tp &val) {
    Iter first_iter = std::lower_bound(begin_iter, end_iter, val);
    unsigned distance = std::distance(begin_iter, first_iter);

    if (first_iter != end_iter && val == *first_iter) {
        ++distance;
    }

    return distance;
};


template <typename Iter, typename Tp, typename Compare>
unsigned IndexLowerBoundRightOpen(Iter begin_iter, Iter end_iter, const Tp &val, Compare comp) {
    Iter first_iter = std::lower_bound(begin_iter, end_iter, val, comp);
    unsigned distance = std::distance(begin_iter, first_iter);

    if (first_iter != end_iter && val == *first_iter) {
        ++distance;
    }

    return distance;
};


} // namespace lib_tools
