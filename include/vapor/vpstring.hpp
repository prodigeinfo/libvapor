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

#ifndef VPSTRING_HPP
#define VPSTRING_HPP

#include "vpclasstype.hpp"
#include <boost/lexical_cast.hpp>

namespace vapor
{

typedef std::string vpstringbase_t;

class vpstring: public vpstringbase_t, public vptype
{
public:
    vpstring() {}
    vpstring(const vpstring& s) : vpstringbase_t(s) {}
    vpstring(const vpstring& s, size_t pos, size_t len = npos) : vpstringbase_t(s, pos, len) {}
    vpstring(const vpstringbase_t& s) : vpstringbase_t(s) {}
    vpstring(const vpstringbase_t& s, size_t pos, size_t len = npos) : vpstringbase_t(s, pos, len) {}
    vpstring(const char *s) : vpstringbase_t(s) {}
    vpstring(const char *s, size_t len) : vpstringbase_t(s, len) {}
    vpstring(size_t n, char c) : vpstringbase_t(n, c) {}
    template <class InputIterator>
    vpstring(InputIterator first, InputIterator last);

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        return std::string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<std::string>(length()) + VPARCHIVE_TOKEN_SEP + (*this);
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format");
        assign(rs.second);
    }

    VPTYPE_CLASS_TYPE_GET_DECL(vpstringbase_t, vpstring)
    VPTYPE_CLASS_TYPE_READ_DECL(vpstringbase_t, vpstring)
    VPTYPE_CLASS_DECL(string, vpstring)
};

} // End namespace vapor.

#endif // VPSTRING_HPP
