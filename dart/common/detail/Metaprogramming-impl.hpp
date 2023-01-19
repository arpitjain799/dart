/*
 * Copyright (c) 2011-2023, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <dart/common/Metaprogramming.hpp>

#include <type_traits>

// Check for any member with given name, whether var, func, class, union, enum.
#define DETAIL_DART_CREATE_MEMBER_CHECK(member)                                \
                                                                               \
  template <typename T, typename = std::true_type>                             \
  struct Alias_##member;                                                       \
                                                                               \
  template <typename T>                                                        \
  struct Alias_##member<                                                       \
      T,                                                                       \
      ::std::integral_constant<                                                \
          bool,                                                                \
          ::dart::common::detail::got_type<decltype(&T::member)>::value>>      \
  {                                                                            \
    static decltype(&T::member) value;                                         \
  };                                                                           \
                                                                               \
  struct AmbiguitySeed_##member                                                \
  {                                                                            \
    char member;                                                               \
  };                                                                           \
                                                                               \
  template <typename T>                                                        \
  struct has_member_##member                                                   \
  {                                                                            \
    static constexpr bool value = ::dart::common::detail::has_member<          \
        Alias_##member<                                                        \
            ::dart::common::detail::ambiguate<T, AmbiguitySeed_##member>>,     \
        Alias_##member<AmbiguitySeed_##member>>::value;                        \
  };                                                                           \
                                                                               \
  template <typename T>                                                        \
  constexpr bool has_member_##member##_v = has_member_##member<T>::value;

namespace dart::common::detail {

// Inspired by https://stackoverflow.com/a/6324863/3122234

// Variadic to force ambiguity of class members. C++11 and up.
template <typename... Args>
struct ambiguate : public Args...
{
};

// Non-variadic version of the line above.
// template <typename A, typename B> struct ambiguate : public A, public B {};

template <typename A, typename = void>
struct got_type : std::false_type
{
};

template <typename A>
struct got_type<A> : std::true_type
{
  using type = A;
};

template <typename T, T>
struct sig_check : std::true_type
{
};

template <typename Alias, typename AmbiguitySeed>
struct has_member
{
  template <typename C>
  static char (&f(decltype(&C::value)))[1];

  template <typename C>
  static char (&f(...))[2];

  // Make sure the member name is consistently spelled the same.
  static_assert(
      (sizeof(f<AmbiguitySeed>(0)) == 1),
      "Member name specified in AmbiguitySeed is different from member name "
      "specified in Alias, or wrong Alias/AmbiguitySeed has been specified.");

  static bool const value = sizeof(f<Alias>(0)) == 2;
};

} // namespace dart::common::detail
