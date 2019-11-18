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

#ifndef VPBOOLEAN_HPP
#define VPBOOLEAN_HPP

#include "vpbasictype.hpp"
#include <boost/lexical_cast.hpp>

namespace vapor
{

typedef int vpboolean_t;
typedef vpbasictype<vpboolean_t> vpboolbase_t;

#define VPBOOLEAN_FALSE (static_cast<vpboolean_t>(0))

class vpboolean: public vpboolbase_t, public vptype
{
public:
    vpboolean() {}
    vpboolean(vpboolean_t x) : vpboolbase_t(x) {}
    vpboolean(int8_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
    vpboolean(uint8_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
#if UINT_MAX >> 16 != 0
    vpboolean(int16_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
    vpboolean(uint16_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
#endif
#if UINT_MAX >> 32 != 0
    vpboolean(int32_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
    vpboolean(uint32_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
#endif
#if UINT_MAX >> 64 != 0
    vpboolean(int64_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
    vpboolean(uint64_t x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}
#endif
    vpboolean(bool x) : vpboolbase_t(((vpboolean_t)istrue(x))) {}

    bool isfalse() const
    {
        return _v == VPBOOLEAN_FALSE;
    }
    template<class Type>
    static bool isfalse(Type x)
    {
        return x == ((Type)VPBOOLEAN_FALSE);
    }

    bool istrue() const
    {
        return _v != VPBOOLEAN_FALSE;
    }
    template<class Type>
    static bool istrue(Type x)
    {
        return x != ((Type)VPBOOLEAN_FALSE);
    }

    friend bool operator==(bool, const vpboolbase_t&);
    friend bool operator==(const vpboolbase_t&, bool);
    friend bool operator==(const vpboolbase_t&, const vpboolbase_t&);

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        std::string content = boost::lexical_cast<std::string>(_v);
        return std::string(TYPE) + ';' + boost::lexical_cast<std::string>(content.length()) + ';' + content;
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format");
        _v = boost::lexical_cast<vpboolean_t>(rs.second);
    }

    VPTYPE_BASIC_TYPE_GET_DECL(vpboolean_t, vpboolean)
    VPTYPE_BASIC_TYPE_READ_DECL(vpboolean_t, vpboolean)

    static bool read_bool(const vptype *o) throw (std::invalid_argument, null_pointer)
    {
        const vpboolean *to = cast_const(o);
        return to->istrue();
    }

    VPTYPE_CLASS_DECL(boolean, vpboolean)
};

template<class Type>
inline bool operator==(bool lv, const vpboolbase_t& r)
{
    return lv == (r._v ? true : false);
}
template<class Type>
inline bool operator==(const vpboolbase_t& l, bool rv)
{
    return (l._v ? true : false) == rv;
}
template<class Type>
inline bool operator==(const vpboolbase_t& l, const vpboolbase_t& r)
{
    return (l._v ? 1 : 0) == (l._v ? 1 : 0);
}

} // End namespace vapor.

#endif // VPBOOLEAN_HPP
