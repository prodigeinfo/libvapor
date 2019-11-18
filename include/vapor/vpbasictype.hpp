/*
 * Copyright (c) 2019 Prodige Informatique, s.a.  All rights reserved.
 * Copyright (c) 2019 Stephane Russell.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Prodige Informatique nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef VPBASICTYPE_HPP
#define VPBASICTYPE_HPP

#include "vptype.hpp"
#include <iostream>

namespace vapor
{

template<class T>
class vpbasictype
{
public:
    vpbasictype() {}
    vpbasictype(const T v) : _v(v) {}
    vpbasictype(const vpbasictype& x) : _v(x._v) {}

    T value() const
    {
        return _v;
    }

    vpbasictype& operator=(const T v)
    {
        _v = v;
        return *this;
    }
    vpbasictype& operator=(const vpbasictype& x)
    {
        _v = x._v;
        return *this;
    }

    bool operator<(const T v)
    {
        return _v < v;
    }
    bool operator<(const vpbasictype& x)
    {
        return _v < x.v;
    }

    bool operator<=(const T v)
    {
        return _v <= v;
    }
    bool operator<=(const vpbasictype& x)
    {
        return _v <= x.v;
    }

    bool operator>(const T v)
    {
        return _v > v;
    }
    bool operator>(const vpbasictype& x)
    {
        return _v > x.v;
    }

    bool operator>=(const T v)
    {
        return _v >= v;
    }
    bool operator>=(const vpbasictype& x)
    {
        return _v >= x.v;
    }

    vpbasictype& operator++()
    {
        ++_v;
        return *this;
    }
    vpbasictype& operator--()
    {
        --_v;
        return *this;
    }

    vpbasictype operator++(int)
    {
        vpbasictype t = *this;
        _v++;
        return t;
    }
    vpbasictype operator--(int)
    {
        vpbasictype t = *this;
        _v--;
        return t;
    }

    template<class Type>
    friend vpbasictype<Type> operator+(Type, const vpbasictype<Type>&);
    template<class Type>
    friend vpbasictype<Type> operator+(const vpbasictype<Type>&, const vpbasictype<Type>&);

    template<class Type>
    friend bool operator==(Type, const vpbasictype<Type>&);
    template<class Type>
    friend bool operator==(const vpbasictype<Type>&, Type);
    template<class Type>
    friend bool operator==(const vpbasictype<Type>&, const vpbasictype<Type>&);

    template<class Type>
    friend std::istream& operator>> (std::istream&, vpbasictype<Type>&);
    template<class Type>
    friend std::ostream& operator<< (std::ostream&, const vpbasictype<Type>&);

protected:
    T _v;
};

template<class Type>
inline vpbasictype<Type> operator+(Type lv, const vpbasictype<Type>& r)
{
    return lv + r._v;
}
template<class Type>
inline vpbasictype<Type> operator+(const vpbasictype<Type>& l, const vpbasictype<Type>& r)
{
    return l._v + r._v;
}

template<class Type>
inline bool operator==(Type lv, const vpbasictype<Type>& r)
{
    return lv == r._v;
}
template<class Type>
inline bool operator==(const vpbasictype<Type>& l, Type rv)
{
    return l._v == rv;
}
template<class Type>
inline bool operator==(const vpbasictype<Type>& l, const vpbasictype<Type>& r)
{
    return l._v == r._v;
}

template<class Type>
inline std::istream& operator>> (std::istream& is, vpbasictype<Type>& x)
{
    return is >> x._v;
}
template<class Type>
inline std::ostream& operator<< (std::ostream& os, const vpbasictype<Type>& x)
{
    return os << x._v;
}

#define VPTYPE_BASIC_TYPE_GET_DECL(b, t) \
public: \
    static b& get(vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        t *to = cast(o); \
        return static_cast<b&>(to->_v); \
    }

#define VPTYPE_BASIC_TYPE_READ_DECL(b, t) \
    static b read(const vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        const t *to = cast_const(o); \
        return static_cast<b>(to->_v); \
    }

#define VPTYPE_BASIC_TYPE_READ_TO_OTHER_TYPE_DECL(TYPE_NAME, b, t) \
    static b read_##TYPE_NAME(const vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        const t *to = cast_const(o); \
        return static_cast<b>(to->_v); \
    }

} // End namespace vapor.

#endif // VPBASICTYPE_HPP
