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

#ifndef VPCLASSTYPE_HPP
#define VPCLASSTYPE_HPP

#include "vptype.hpp"

namespace vapor
{

#define VPTYPE_CLASS_TYPE_GET_DECL(c, t) \
public: \
    static c& get(vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        t *to = cast(o); \
        return static_cast<c&>(*to); \
    } \
    static const c& get(const vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        const t *to = cast_const(o); \
        return static_cast<const c&>(*to); \
    }

#define VPTYPE_CLASS_TYPE_GET_OTHER_TYPE_DECL(TYPE_NAME, c, t) \
    static const c& get_##TYPE_NAME(vptype *o) throw (std::invalid_argument, null_pointer) \
    { \
        const t *to = cast_const(o); \
        return static_cast<const c&>(*to); \
    }

} // End namespace vapor.

#endif // VPCLASSTYPE_HPP
