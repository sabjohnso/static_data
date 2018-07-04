#ifndef IMPORT_HPP_INCLUDED_1543702165180478652
#define IMPORT_HPP_INCLUDED_1543702165180478652 1

//
// ... Standard header files
//
#include <cstddef>
#include <utility>
#include <type_traits>
#include <iterator>

//
// ... External library header files
//
#include <type_utility/type_utility.hpp>



namespace StaticData
{
  namespace Core
  {
    using std::size_t;

    using std::pair;
    using std::forward;
    using std::move;

    using std::declval;

    using std::decay_t;
    using std::conditional_t;
    using std::enable_if_t;
    using std::is_same;

    using std::bool_constant;
    using std::false_type;

    using TypeUtility::Type;
    using TypeUtility::type;
    
  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined IMPORT_HPP_INCLUDED_1543702165180478652
