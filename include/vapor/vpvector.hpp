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

#ifndef VPVECTOR_HPP
#define VPVECTOR_HPP

#include "vpclasstype.hpp"
#include <vector>

namespace vapor
{

typedef std::vector<vptype*> vpvectorbase_t;

class vpvector: public vpvectorbase_t, public vptype
{
public:
    vpvector() {}
    vpvector(const vpvectorbase_t& v) : vpvectorbase_t(v) {}
    vpvector(size_type count) : vpvectorbase_t(count) {}
    template<class InputIt>
    vpvector(InputIt first, InputIt last) : vpvectorbase_t(first, last) {}
    vpvector(const vpvector& other) : vpvectorbase_t(other) {}
    vpvector(vector&& other ) : vpvectorbase_t(other) {}
    vpvector(std::initializer_list<vptype*> init) : vpvectorbase_t(init) {}

    ~vpvector();

    virtual std::string serialize() const throw(std::runtime_error);
    virtual void deserialize(const char *s) throw(std::runtime_error, std::out_of_range, std::invalid_argument);

    VPTYPE_CLASS_TYPE_GET_DECL(vpvectorbase_t, vpvector)
    VPTYPE_CLASS_DECL(vector, vpvector)
};

} // End namespace vapor.

#endif // VPVECTOR_HPP
