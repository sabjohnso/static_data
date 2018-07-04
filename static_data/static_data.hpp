#ifndef STATIC_DATA_HPP_INCLUDED_1110871304704831630
#define STATIC_DATA_HPP_INCLUDED_1110871304704831630 1

//
// ... Static Data header files
//
#include <static_data/nothing.hpp>
#include <static_data/list.hpp>
#include <static_data/zipper.hpp>
#include <static_data/stack.hpp>


namespace StaticData {

  using Core::nothing;
  using Core::cons;
  using Core::list;

  using Core::zipper;
  using Core::empty_zipper;
  using Core::make_zipper;

  using Core::stack;
  using Core::empty_stack;
  using Core::make_stack;
  using Core::isstack;

} // end of namespace StaticData

#endif // !defined STATIC_DATA_HPP_INCLUDED_1110871304704831630
