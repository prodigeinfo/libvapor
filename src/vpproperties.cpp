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

#include <vapor/vpproperties.hpp>
#include <vapor/vpstring.hpp>

using namespace std;

namespace vapor
{

VPTYPE_CLASS_DEF(vpproperties)

vpproperties::~vpproperties()
{
    for (vpproperties::const_iterator it=begin(); it != end(); it++)
    {
        if (it->second) it->second->autodelete();
    }
}

//TODO null type creation for nullptr
vparchive_t vpproperties::serialize() const throw(std::runtime_error)
{
    string content;

    for (vpproperties::const_iterator it=begin(); it != end(); it++)
    {
        content += vpstring(it->first).serialize() + (it->second ? it->second->serialize() : NULLPTR_SERIALIZED);
    }

    return string(TYPE) + VPARCHIVE_TOKEN_SEP + boost::lexical_cast<string>(content.length()) + VPARCHIVE_TOKEN_SEP + content;
}

void vpproperties::deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument)
{
    const char *p1, *p2;
    pair<string, string> rs = vptype::split(s);

    if (rs.first != TYPE) throw invalid_argument("bad format");

    clear();

    p1 = rs.second.c_str();        // pointer on the content
    p2 = p1 + rs.second.size();    // size of the end of the content
    while (p1 < p2)
    {
        std::pair<vptype *, const char *> rs_name = newfrom(p1);                // extract name
        std::pair<vptype *, const char *> rs_value = newfrom(rs_name.second);   // extract value
        vpstring *name = reinterpret_cast<vpstring*>(rs_name.first);
        insert(pair<string, vptype *>(*name, rs_value.first));
        delete rs_name.first;
        p1 = rs_value.second;
    }
}

} // End namespace vapor.
