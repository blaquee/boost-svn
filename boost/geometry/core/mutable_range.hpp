// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2010-2011, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP
#define BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP


#include <cstddef>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/range.hpp>


namespace boost { namespace geometry
{


namespace traits
{

/*!
\brief Metafunction to define the argument passed to the three
    traits classes clear, push_back and resize
\ingroup mutable_range
 */
template <typename Range>
struct rvalue_type
{
    typedef typename boost::remove_reference<Range>::type& type;
};


/*!
\brief Traits class to clear a geometry
\ingroup mutable_range
 */
template <typename Range>
struct clear
{
    static inline void apply(typename rvalue_type<Range>::type range)
    {
        range.clear();
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct push_back
{
    typedef typename boost::range_value
        <
            typename boost::remove_reference<Range>::type
        >::type item_type;

    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type const& item)
    {
        range.push_back(item);
    }
};


/*!
\brief Traits class to append a point to a range (ring, linestring, multi*)
\ingroup mutable_range
 */
template <typename Range>
struct resize
{
    static inline void apply(typename rvalue_type<Range>::type range,
                std::size_t new_size)
    {
        range.resize(new_size);
    }
};


} // namespace traits


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_MUTABLE_RANGE_HPP