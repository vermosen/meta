#pragma once
#ifndef META_LAMBDA_ARITY_H
#define META_LAMBDA_ARITY_H

namespace meta {

namespace details {

  template <typename>
  struct arity_impl;

  template <typename Class, typename Type, typename... Args>
  struct arity_impl<Type(Class::*)(Args...) const> {
    static constexpr std::size_t value = sizeof...(Args);
  };

  template <typename Class, typename Type, typename... Args>
  struct arity_impl<Type(Class::*)(Args...)> {
    static constexpr std::size_t value = sizeof...(Args);
  };
}

  /*!
   * @brief returns arity of a lambda
   */
  template <typename Func>
  struct arity : public details::arity_impl<decltype(&Func::operator())> {};
}

#endif // META_LAMBDA_ARITY_H