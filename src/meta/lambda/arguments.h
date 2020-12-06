#pragma once
#ifndef META_LAMBDA_ARGUMENT_H
#define META_LAMBDA_ARGUMENT_H

namespace meta {

namespace details {

  template <typename> 
  struct arguments_impl;

  template <typename Class, typename Type, typename... Args>
  struct arguments_impl<Type(Class::*)(Args...) const> {
    using type = std::tuple<Args...>;
  };
}

  /*!
   * returns the list of arguments of a lambda
   */
  template <typename Func>
  struct arguments : public details::arguments_impl<decltype(&Func::operator())> {};
}

#endif // META_LAMBDA_ARGUMENT_H