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

#include <vapor/vptype.hpp>
#include <sysexits.h>
#include <err.h>

using namespace std;

namespace vapor
{

const char VPTYPE_NULLPTR_SERIALIZED_DATA[] = { VPARCHIVE_TOKEN_SEP, '0', VPARCHIVE_TOKEN_SEP, '\0' };
const char *vptype::NULLPTR_SERIALIZED = VPTYPE_NULLPTR_SERIALIZED_DATA;

vptype::vptypevector_t *vptype::_typevector = nullptr;

const char *vptype::getnexttoken(const char *s) throw(invalid_argument)
{
    const char *p;

    for (p=s; *p != VPARCHIVE_TOKEN_SEP; p++) if (p-s == INT8_MAX) throw invalid_argument("bad format: token too large!");

    return ++p;
}

pair<string, string> vptype::split(const char *s) throw(invalid_argument)
{
    string lenbuf, type, content;
    string::size_type len;
    const char *p2, *p3;

    p2 = getnexttoken(s);
    type = readtoken(s, p2);

    p3 = getnexttoken(p2);
    len = readsize(p2, p3);

    content = readcontent(p3, len);

    return make_pair(type, content);
}

std::pair<vptype *, const char *> vptype::newfrom(const char *s) throw (out_of_range, invalid_argument)
{
    const char *p1 = getnexttoken(s), *p2 = getnexttoken(p1);
    string t = readtoken(s, p1);
    string::size_type len = readsize(p1, p2);
    vptype* o;

    if (!t.empty())
    {
        o = newobj(t);
        o->deserialize(s);
    }
    else o = nullptr;

    return make_pair(o, p2+len);
}

vptype::vpptrfn_t vptype::getnewobjfn(const char *t)
{
    for(const vptyperec_t& rec: *_typevector)
    {
        register const char *p1, *p2;
        for (p1=rec.t, p2=t; (*p1 == *p2) && (*p1 != '\0'); p1++, p2++);
        if (*p1 == *p2) return rec.f;
    }
    return nullptr;
}

void vptype::addtype(const char *t, vpptrfn_t f) throw (invalid_argument)
{
    // create the vector on first use
    if (!_typevector) _typevector = new vptypevector_t;

    // two types can't have the same type name
    if (getnewobjfn(t) != nullptr)
    {
        throw invalid_argument("serializable type already exists: " + string(t));
    }

    _typevector->push_back({t, f});
}

} // End namespace vapor.
