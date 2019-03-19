#pragma once
/* 
 * Acute - A C Unit Testing Environment
 * Copyright (C) 2019 M E Leypold
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "macro-machinery-vec.h"
#include <assert.h>

#define ACUTE_TAKE(N,...)        ACUTE_DISPATCH(ACUTE_TAKE,N,__VA_ARGS__,)
#define ACUTE_CONCATENATE(...)   ACUTE_DISPATCH(ACUTE_CONCATENATE,ACUTE_COUNT_ARGS(__VA_ARGS__),__VA_ARGS__,)

#define ACUTE_ENUMERATE(...)   ACUTE_TAKE(ACUTE_COUNT_ARGS(__VA_ARGS__),ACUTE_APPLY(ACUTE_ZIP_VECS,ACUTE_VEC_INDICES,ACUTE_PAD(,__VA_ARGS__)))

#define ACUTE_EACH_APPLY(M,...)       ACUTE_EACH_APPLY_(ACUTE_COUNT_ARGS(__VA_ARGS__),M,__VA_ARGS__)
#define ACUTE_EACH_APPLY_(N,M,...)    ACUTE_TAKE(N,ACUTE_APPLY(ACUTE_VEC_APPLY,ACUTE_REPEAT(M),ACUTE_PAD(,__VA_ARGS__)))

#define ACUTE_EACH_PREPEND(M,...)     ACUTE_EACH_PREPEND_(ACUTE_COUNT_ARGS(__VA_ARGS__),M,__VA_ARGS__)
#define ACUTE_EACH_PREPEND_(N,M,...)  ACUTE_TAKE(N,ACUTE_APPLY(ACUTE_VEC_PREPEND,ACUTE_REPEAT(M),ACUTE_PAD(,__VA_ARGS__)))

#define ACUTE_EACH_ENUMERATED(M,...)  ACUTE_EACH_PREPEND(M,ACUTE_ENUMERATE(__VA_ARGS__))

#define ACUTE_STRINGIFY(x)          #x
#define ACUTE_EACH_STRINGIFY(...)   ACUTE_EACH_APPLY(ACUTE_STRINGIFY,__VA_ARGS__)

#define ACUTE_TIMES(N,M) ACUTE_EACH_APPLY(M,ACUTE_RANGE(N))

#define ACUTE_EXPAND_CODE(M,N) ACUTE_CONCATENATE(ACUTE_TIMES(N,M))
#define ACUTE_EXPAND_CODE_ENUMERATED(M,...) ACUTE_CONCATENATE(ACUTE_EACH_ENUMERATED(M,__VA_ARGS__))


#define ACUTE_UNPACK(...) ACUTE_DISPATCH(ACUTE_UNPACK,ACUTE_COUNT_ARGS(__VA_ARGS__),__VA_ARGS__)

#define ACUTE_UNPACK_TUPLE(...)  ACUTE_UNPACK_TUPLE_ __VA_ARGS__
#define ACUTE_UNPACK_TUPLE_(...) __VA_ARGS__


#define ACUTE_LID(x) ACUTE_APPLY(ACUTE_PASTE_3,x,_,__LINE__)

#define ACUTE_ENUMDEF(TYPENAME,...)					\
  enum TYPENAME { __VA_ARGS__ };					\
  typedef enum TYPENAME TYPENAME;					\
  const char* TYPENAME##_STRINGS[] =					\
    { ACUTE_EACH_STRINGIFY(__VA_ARGS__) };				\
  static inline const							\
  char * string_from_##TYPENAME(enum TYPENAME value)			\
  {									\
    assert(value<ACUTE_COUNT_ARGS(__VA_ARGS__));			\
    return TYPENAME##_STRINGS[value];					\
  }									\
  static inline const							\
  char * string_from_##TYPENAME(enum TYPENAME value)			\

#define ACUTE_STRUCTDEF(TYPENAME)		\
  struct TYPENAME;				\
  typedef struct TYPENAME TYPENAME;		\
  struct TYPENAME


#define enumdef   ACUTE_ENUMDEF
#define structdef ACUTE_STRUCTDEF

#define ACUTE_RANGE(N) ACUTE_APPLY(ACUTE_TAKE,N,ACUTE_VEC_INDICES)
