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

#ifndef VPVOID_HPP
#define VPVOID_HPP

#include "vptype.hpp"
#include <boost/lexical_cast.hpp>

namespace vapor
{

typedef const int vpvoid_t;

class vpvoid: public vptype
{
public:
    static const char *SERIALIZED;

    vpvoid() : _v(0) {}

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        return SERIALIZED;
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format");
    }

    vpvoid operator=(const vpvoid&) const
    {
        return *this;
    }

    VPTYPE_CLASS_DECL(void, vpvoid)

protected:
    vpvoid_t _v;
};

inline bool operator==(const vpvoid& l, const vpvoid& r)
{
    return true;
}

inline std::ostream& operator<< (std::ostream& os, const vpvoid& x)
{
    return os;
}

} // End namespace vapor.

#endif // VPVOID_HPP
