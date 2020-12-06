#pragma once
#ifndef META_LAMBDA_RETURNS_H
#define META_LAMBDA_RETURNS_H

namespace meta {

namespace details {

  template <typename Func>
  struct returns_impl;

  template <typename Class, typename Type, typename... Args>
  struct returns_impl<Type(Class::*)(Args...) const> {
    using type = Type;
  };
}

  /*!
   * deduction of the return type of a lambda
   */
  template <typename Func>
  struct returns : public details::returns_impl<decltype(&Func::operator())> {};
}

#endif // META_LAMBDA_RETURNS_H