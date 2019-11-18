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

#ifndef VPFIXOBJECT_HPP
#define VPFIXOBJECT_HPP

#include "vpclasstype.hpp"
#include "vpobject.hpp"

namespace vapor
{

class vpfixobject : public vpobject
{
public:
    typedef struct propdef
    {
        const char *name;
        const char *t;
    } propdef_t;

    vpfixobject() : _proptable(nullptr), _pt_size(0) {}
    vpfixobject(const propdef_t *t, size_t sz) : _proptable(t), _pt_size(sz)
    {
        initialize_properties();
    }
    vpfixobject(const vpfixobject& x) : vpobject(x), _proptable(x._proptable), _pt_size(x._pt_size) {}

    virtual vparchive_t serialize() const throw(std::runtime_error)
    {
        std::string content = vpobject::serialize();
        return std::string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<std::string>(content.length()) + VPARCHIVE_TOKEN_SEP + content;
    }

    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
    {
        std::pair<std::string, std::string> rs = vptype::split(s);
        if (rs.first != TYPE) throw std::invalid_argument("bad format: vpfixobject::deserialize: " + rs.first);
        vpobject::deserialize(rs.second.c_str());
    }

protected:
    const propdef_t *_proptable;
    size_t _pt_size;

    void initialize_properties();
    virtual void chkprop(const char *name, const vptype *o) const throw(std::out_of_range, std::invalid_argument);

    VPTYPE_CLASS_DECL(fixobject, vpfixobject)
};

#define VPFO_SIZEOF(table) static_cast<size_t>(sizeof(table)/sizeof(vpfixobject::propdef_t))
#define VPFO_NAME_DEF(SYM, STR) static constexpr const char *SYM = STR

} // End namespace vapor.

#endif // VPFIXOBJECT_HPP
