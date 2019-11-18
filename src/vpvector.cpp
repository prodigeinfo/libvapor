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

#include <vapor/vpvector.hpp>
#include <boost/lexical_cast.hpp>
#include <vapor/vpint.hpp>

using namespace std;

namespace vapor
{

VPTYPE_CLASS_DEF(vpvector)

vpvector::~vpvector()
{
    for (vptype*& e: *this) if (e) e->autodelete();
}

vparchive_t vpvector::serialize() const throw(std::runtime_error)
{
    string content = vpint(static_cast<vpint_t>(size())).serialize();
    for (vptype *e: *this) content += (e ? e->serialize() : NULLPTR_SERIALIZED);
    return string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<string>(content.length()) + VPARCHIVE_TOKEN_SEP + content;
}

void vpvector::deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
{
    const char *p1, *p2;
    pair<string, string> rs1 = vptype::split(s);

    if (rs1.first != TYPE) throw invalid_argument("bad format");

    clear();

    p1 = rs1.second.c_str();        // pointer on the content
    p2 = p1 + rs1.second.size();    // size of the end of the content

    // resize
    std::pair<vptype *, const char *> rs2 = newfrom(p1);
    vpint *o = reinterpret_cast<vpint *>(rs2.first);
    size_type sz = static_cast<size_type>(o->value());
    delete o;
    resize(sz);

    p1 = rs2.second;
    for (size_type i = 0; i < sz; i++)
    {
        std::pair<vptype *, const char *> rs2 = newfrom(p1);
        vptype* o = rs2.first;
        at(i) = o;
        p1 = rs2.second;
    }
}

} // End namespace vapor.
