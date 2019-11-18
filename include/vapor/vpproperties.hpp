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

#ifndef VPPROPERTIES_HPP
#define VPPROPERTIES_HPP

#include "vpclasstype.hpp"
#include <string>
#include <map>

namespace vapor
{

typedef std::map<const std::string, vptype *> vppropertiesbase_t;

class vpproperties: public vppropertiesbase_t, public vptype
{
public:
    explicit vpproperties(const key_compare& comp = key_compare(),
                          const allocator_type& alloc = allocator_type()) : vppropertiesbase_t(comp, alloc) {}
    explicit vpproperties(const allocator_type& alloc) : vppropertiesbase_t(alloc) {}
    template <class InputIterator>
    vpproperties(InputIterator first, InputIterator last,
                 const key_compare& comp = key_compare(),
                 const allocator_type& alloc= allocator_type()) : vppropertiesbase_t(first, last, comp, alloc) {}
    vpproperties(const vpproperties& x) : vppropertiesbase_t(x) {}
    vpproperties(const vpproperties& x, const allocator_type& alloc) : vppropertiesbase_t(x, alloc) {}
    vpproperties(vpproperties&& x) : vppropertiesbase_t(x) {}
    vpproperties(vpproperties&& x, const allocator_type& alloc) : vppropertiesbase_t(x, alloc) {}

    ~vpproperties();

    vpproperties& operator=(const vpproperties& p)
    {
        vppropertiesbase_t::operator=(p);
    }

    virtual vparchive_t serialize() const throw(std::runtime_error);
    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument);

    VPTYPE_CLASS_TYPE_GET_DECL(vppropertiesbase_t, vpproperties)
    VPTYPE_CLASS_TYPE_READ_DECL(vppropertiesbase_t, vpproperties)
    VPTYPE_CLASS_DECL(properties, vpproperties)
};

} // End namespace vapor.

#endif // VPPROPERTIES_HPP
