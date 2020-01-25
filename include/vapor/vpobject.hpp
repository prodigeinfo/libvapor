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

#ifndef VPOBJECT_HPP
#define VPOBJECT_HPP

#include "vpclasstype.hpp"
#include "vpproperties.hpp"
#include "vpboolean.hpp"
#include "vpstring.hpp"
#include "vpbyte.hpp"
#include "vpshort.hpp"
#include "vpint.hpp"
#include "vplong.hpp"
#include "vpunsignedbyte.hpp"
#include "vpunsignedshort.hpp"
#include "vpunsignedint.hpp"
#include "vpunsignedlong.hpp"
#include "vpfloat.hpp"
#include "vpdouble.hpp"

namespace vapor
{

#define VPTYPE_BASIC_TYPE_GET_SET_DECL(TYPE_NAME, b, t) \
b get_##TYPE_NAME(const char *name) const throw(std::out_of_range) \
{ \
    const vptype *o = get(name); \
    return static_cast<b>(t::read_##TYPE_NAME(o)); \
} \
b get_##TYPE_NAME(const std::string& name) const throw(std::out_of_range) \
{ \
    return get_##TYPE_NAME(name.c_str()); \
} \
void set_##TYPE_NAME(const char *name, b value) throw(std::out_of_range, std::invalid_argument) \
{ \
    t *o = new t(static_cast<b>(value)); \
    set(name, o); \
} \
void set_##TYPE_NAME(const std::string& name, b value) throw(std::out_of_range, std::invalid_argument) \
{ \
    set_##TYPE_NAME(name.c_str(), value); \
}

#define VPTYPE_COMPLEX_TYPE_GET_SET_DECL(TYPE_NAME, c, t) \
const c& get_##TYPE_NAME(const char *name) const throw(std::out_of_range) \
{ \
    const vptype *o = get(name); \
    return t::get(o); \
} \
const c& tet_##TYPE_NAME(const std::string& name) const throw(std::out_of_range) \
{ \
    return get_##TYPE_NAME(name.c_str()); \
} \
c& get_##TYPE_NAME(const char *name) throw(std::out_of_range) \
{ \
    vptype *o = get(name); \
    return t::get(o); \
} \
c& get_##TYPE_NAME(const std::string& name) throw(std::out_of_range) \
{ \
    return get_##TYPE_NAME(name.c_str()); \
} \
void set_##TYPE_NAME(const char *name, const c& value) throw(std::out_of_range, std::invalid_argument) \
{ \
    t *o = new t(value); \
    set(name, o); \
} \
void set_##TYPE_NAME(const std::string& name, const c& value) throw(std::out_of_range, std::invalid_argument) \
{ \
    set_##TYPE_NAME(name.c_str(), value); \
}

class vpobject : public vptype
{
public:
    vpobject() {}
    vpobject(const vpobject& x) : _properties(x._properties) {}

    const vptype *get(const char *name) const throw(std::out_of_range)
    {
        return _properties.at(name);
    }
    const vptype *get(const std::string& name) const throw(std::out_of_range)
    {
        return get(name.c_str());
    }

    vptype *get(const char *name) throw(std::out_of_range)
    {
        return _properties.at(name);
    }
    vptype *get(const std::string& name) throw(std::out_of_range)
    {
        return get(name.c_str());
    }

    void set(const char *name, vptype *o) throw(std::out_of_range, std::invalid_argument)
    {
        vpproperties::iterator it;
        chkprop(name, o);
        it = _properties.find(name);
        if (it != _properties.end() && it->second) {
            it->second->autodelete();
            it->second = o;
        }
        else _properties[name] = o;
    }
    void set(const std::string& name, vptype *o) throw(std::out_of_range, std::invalid_argument)
    {
        set(name.c_str(), o);
    }

    VPTYPE_BASIC_TYPE_GET_SET_DECL(bool, bool, vpboolean)

    VPTYPE_COMPLEX_TYPE_GET_SET_DECL(string, std::string, vpstring)
    void set_string(const char *name, const char *s) throw(std::out_of_range, std::invalid_argument)
    {
        set(name, new vpstring(s));
    }
    void set_string(const std::string& name, const char *s) throw(std::out_of_range, std::invalid_argument)
    {
        set_string(name.c_str(), s);
    }

    VPTYPE_BASIC_TYPE_GET_SET_DECL(char, char, vpbyte)
    VPTYPE_BASIC_TYPE_GET_SET_DECL(short, short, vpshort)
#if UINT_MAX >> 16 != 0
    VPTYPE_BASIC_TYPE_GET_SET_DECL(int, int, vpint)
#endif
#if UINT_MAX >> 32 != 0
    VPTYPE_BASIC_TYPE_GET_SET_DECL(long, long, vplong)
#endif
    VPTYPE_BASIC_TYPE_GET_SET_DECL(uchar, unsigned char, vpunsignedbyte)
    VPTYPE_BASIC_TYPE_GET_SET_DECL(ushort, unsigned short, vpunsignedshort)
#if UINT_MAX >> 16 != 0
    VPTYPE_BASIC_TYPE_GET_SET_DECL(unsigned, unsigned, vpunsignedint)
#endif
#if UINT_MAX >> 32 != 0
    VPTYPE_BASIC_TYPE_GET_SET_DECL(ulong, unsigned long, vpunsignedlong)
#endif
    VPTYPE_BASIC_TYPE_GET_SET_DECL(float, float, vpfloat)
    VPTYPE_BASIC_TYPE_GET_SET_DECL(double, double, vpdouble)


    void unset(const char *name) throw(std::out_of_range)
    {
        vpproperties::iterator it = _properties.find(name);
        if (it == _properties.end()) throw std::out_of_range("unknown parameter");
        if (_properties[name])
        {
            _properties[name]->autodelete();
            _properties.erase(name);
        }
    }
    void unset(const std::string& name) throw(std::out_of_range)
    {
        return unset(name.c_str());
    }

    vpobject& operator=(const vpobject& x)
    {
        _properties = x._properties;
        return *this;
    }

    size_t size()
    {
        return _properties.size();
    }
    
    //TODO Optimize the serialization to use the char * instead of making string copies to avoid loosing time with big variables
    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        std::string content = _properties.serialize();
        return std::string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<std::string>(content.length()) + VPARCHIVE_TOKEN_SEP + content;
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format");
        _properties.deserialize(rs.second.c_str());
    }

protected:
    vpproperties _properties;

    virtual void chkprop(const char *name, const vptype *o) const throw(std::out_of_range, std::invalid_argument) {}

    VPTYPE_CLASS_DECL(object, vpobject)
};

} // End namespace vapor.

#endif // VPOBJECT_HPP
