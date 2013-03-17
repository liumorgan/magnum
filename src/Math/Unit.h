#ifndef Magnum_Math_Unit_h
#define Magnum_Math_Unit_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class Magnum::Math::Unit
 */

#include "Math/TypeTraits.h"

namespace Magnum { namespace Math {

/**
@brief Base class for units
@tparam T Underlying data type

@see Deg, Rad
*/
template<template<class> class Derived, class T> class Unit {
    template<template<class> class, class> friend class Unit;

    public:
        typedef T Type;             /**< @brief Underlying data type */

        /** @brief Default constructor */
        inline constexpr /*implicit*/ Unit(): value(T(0)) {}

        /** @brief Explicit conversion from unitless type */
        inline constexpr explicit Unit(T value): value(value) {}

        /** @brief Construct from another underlying type */
        template<class U> inline constexpr explicit Unit(Unit<Derived, U> value): value(value.value) {}

        /** @brief Explicit conversion to underlying type */
        #ifndef CORRADE_GCC44_COMPATIBILITY
        inline constexpr explicit operator T() const { return value; }
        #else
        inline constexpr operator T() const { return value; }
        #endif

        /** @brief Equality comparison */
        inline constexpr bool operator==(Unit<Derived, T> other) const {
            return TypeTraits<T>::equals(value, other.value);
        }

        /** @brief Non-equality comparison */
        inline constexpr bool operator!=(Unit<Derived, T> other) const {
            return !operator==(other);
        }

        /** @brief Less than comparison */
        inline constexpr bool operator<(Unit<Derived, T> other) const {
            return value < other.value;
        }

        /** @brief Greater than comparison */
        inline constexpr bool operator>(Unit<Derived, T> other) const {
            return value > other.value;
        }

        /** @brief Less than or equal comparison */
        inline constexpr bool operator<=(Unit<Derived, T> other) const {
            return !operator>(other);
        }

        /** @brief Greater than or equal comparison */
        inline constexpr bool operator>=(Unit<Derived, T> other) const {
            return !operator<(other);
        }

        /** @brief Negated value */
        inline constexpr Unit<Derived, T> operator-() const {
            return Unit<Derived, T>(-value);
        }

        /** @brief Add and assign value */
        inline Unit<Derived, T>& operator+=(Unit<Derived, T> other) {
            value += other.value;
            return *this;
        }

        /** @brief Add value */
        inline constexpr Unit<Derived, T> operator+(Unit<Derived, T> other) const {
            return Unit<Derived, T>(value + other.value);
        }

        /** @brief Subtract and assign value */
        inline Unit<Derived, T>& operator-=(Unit<Derived, T> other) {
            value -= other.value;
            return *this;
        }

        /** @brief Subtract value */
        inline constexpr Unit<Derived, T> operator-(Unit<Derived, T> other) const {
            return Unit<Derived, T>(value - other.value);
        }

        /* These are conflicting with builtin operators because of non-explicit
           conversion to T */
        #ifndef CORRADE_GCC44_COMPATIBILITY
        /** @brief Multiply with number and assign */
        inline Unit<Derived, T>& operator*=(T number) {
            value *= number;
            return *this;
        }

        /** @brief Multiply with number */
        inline constexpr Unit<Derived, T> operator*(T number) const {
            return Unit<Derived, T>(value*number);
        }

        /** @brief Divide with number and assign */
        inline Unit<Derived, T>& operator/=(T number) {
            value /= number;
            return *this;
        }

        /** @brief Divide with number */
        inline constexpr Unit<Derived, T> operator/(T number) const {
            return Unit<Derived, T>(value/number);
        }

        /** @brief Ratio of two values */
        inline constexpr T operator/(Unit<Derived, T> other) const {
            return value/other.value;
        }
        #endif

    private:
        T value;
};

/* This is conflicting with builtin operator because of non-explicit conversion to T */
#ifndef CORRADE_GCC44_COMPATIBILITY
/** @relates Unit
@brief Multiply number with value
*/
template<template<class> class Derived, class T> inline constexpr Unit<Derived, T> operator*(typename std::common_type<T>::type number, const Unit<Derived, T>& value) {
    return value*number;
}
#endif

}}

#endif
