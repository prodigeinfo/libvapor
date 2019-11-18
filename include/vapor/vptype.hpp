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

/*
 * Copyright (c) 2013
 *	Prodige Informatique, s.a.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef VPTYPE_HPP
#define VPTYPE_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "exceptions/null_pointer.hpp"

namespace vapor
{

typedef std::string vparchive_t;

#define VPARCHIVE_TOKEN_SEP    ';'

class vptype
{
public:
    static const char *NULLPTR_SERIALIZED;

    virtual std::string gettype() const = 0;
    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        throw std::runtime_error("serialization not implemented for this type: " + gettype());
    }
    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        throw std::runtime_error("deserialization not implemented for this type: " + gettype());
    }
    virtual void deserialize(const vparchive_t& a) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        return deserialize(a.c_str());
    }
    virtual void autodelete() = 0;
    virtual void copy(const vptype *) throw (std::invalid_argument, null_pointer) = 0;

    static vptype *newobj(const char *t) throw(std::out_of_range)
    {
        vpptrfn_t newobj = getnewobjfn(t);
        if (newobj == nullptr) throw std::out_of_range("serializable type \"" + std::string(t) + "\" not registered");
        return newobj();
    }
    static vptype *newobj(const std::string& t) throw(std::out_of_range)
    {
        return newobj(t.c_str());
    }

//protected:
    static std::pair<std::string, std::string> split(const char *) throw(std::invalid_argument);
    static std::pair<std::string, std::string> split(const std::string& s) throw(std::invalid_argument)
    {
        return split(s.c_str());
    };
    static const char *getnexttoken(const char *s) throw(std::invalid_argument);
    static std::string readtoken(const char *p1, const char *p2)
    {
        return p2>p1 ? std::string(p1, p2-p1-1) : std::string();
    }
    static std::string::size_type readsize(const char *p1, const char *p2)
    {
        std::string buf = readtoken(p1, p2);
        return boost::lexical_cast<std::string::size_type>(buf);
    }
    static std::string readcontent(const char *s, std::string::size_type len)
    {
        return std::string(s, len);
    }
    static std::pair<vptype *, const char *> newfrom(const char *) throw (std::out_of_range, std::invalid_argument);

protected:
    typedef vptype *(*vpptrfn_t)();
    typedef struct vptyperec
    {
        const char *t;
        vpptrfn_t f;
    } vptyperec_t;
    static vpptrfn_t getnewobjfn(const char *);
    typedef std::vector<vptyperec_t> vptypevector_t;
    static vptypevector_t *_typevector;
    static void addtype(const char *, vpptrfn_t) throw (std::invalid_argument);
};

#define VPTYPE_CLASS_DECL(TYPE_STRING, t) \
public: \
    static constexpr const char *TYPE = (#TYPE_STRING); \
    virtual std::string gettype() const \
    { \
        return TYPE; \
    }; \
    virtual void autodelete() \
    { \
        delete this; \
    } \
    virtual void copy(const vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        const t *to; \
        if (!o) throw null_pointer(); \
        if (o->gettype() != gettype()) throw std::invalid_argument("bad type: " + o->gettype()); \
        to = reinterpret_cast<const t *>(o); \
        *this = *to; \
    } \
    static vptype *newobj() \
    { \
        return new t; \
    } \
    static t *cast(vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        if (!o) throw null_pointer(); \
        if (o->gettype() != t::TYPE) throw std::invalid_argument("bad type: " + o->gettype()); \
        return reinterpret_cast<t *>(o); \
    } \
    static const t *cast_const(const vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        if (!o) throw null_pointer(); \
        if (o->gettype() != t::TYPE) throw std::invalid_argument("bad type: " + o->gettype()); \
        return reinterpret_cast<const t *>(o); \
    } \
private: \
    typedef class vpautoreg \
    { \
    public: \
        vpautoreg() \
        { \
            vptype::addtype(TYPE, newobj); \
        } \
    } vpautoreg_t; \
    static vpautoreg_t vpautoreg1;

#define VPTYPE_CLASS_DEF(t) \
    t::vpautoreg_t t::vpautoreg1; \

} // End namespace vapor.

#endif // VPTYPE_HPP
