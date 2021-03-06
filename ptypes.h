#ifndef MPU_PTYPES_H
#define MPU_PTYPES_H

#ifdef _MSC_VER
 /* No stdint.h for MS C, so we lose the chance to possibly optimize
  * some operations on 64-bit machines running a 32-bit Perl.  It's probably
  * a rare enough case that we don't need to be too concerned.  If we do want,
  * see:  http://gauss.cs.ucsb.edu/~aydin/CombBLAS/html/stdint_8h_source.html
  * for some ideas.
  *
  *  Thanks to Sisyphus for bringing the MSC issue to my attention (and even
  *  submitting a working patch!).
  */
#elif defined(__sun) || defined(__sun__)
 /* stdint.h is only in Solaris 10+. */
 #if defined(__SunOS_5_10) || defined(__SunOS_5_11) || defined(__SunOS_5_12)
  #define __STDC_LIMIT_MACROS
  #include <stdint.h>
 #endif
#else
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#endif

#include "EXTERN.h"
#include "perl.h"

/* From perl.h, wrapped in PERL_CORE */
#ifndef U32_CONST
# if INTSIZE >= 4
#  define U32_CONST(x) ((U32TYPE)x##U)
# else
#  define U32_CONST(x) ((U32TYPE)x##UL)
# endif
#endif

/* From perl.h, wrapped in PERL_CORE */
#ifndef U64_CONST
# ifdef HAS_QUAD
#  if INTSIZE >= 8
#   define U64_CONST(x) ((U64TYPE)x##U)
#  elif LONGSIZE >= 8
#   define U64_CONST(x) ((U64TYPE)x##UL)
#  elif QUADKIND == QUAD_IS_LONG_LONG
#   define U64_CONST(x) ((U64TYPE)x##ULL)
#  else /* best guess we can make */
#   define U64_CONST(x) ((U64TYPE)x##UL)
#  endif
# endif
#endif


#ifdef HAS_QUAD
  #define BITS_PER_WORD  64
  #define UVCONST(x)     U64_CONST(x)
#else
  #define BITS_PER_WORD  32
  #define UVCONST(x)     U32_CONST(x)
#endif

/* Try to determine if we have 64-bit available via uint64_t */
#define HAVE_STD_U64 0
#if defined(UINT64_MAX) && defined(__UINT64_C)
  #if (UINT64_MAX >= __UINT64_C(18446744073709551615))
    #undef HAVE_STD_U64
    #define HAVE_STD_U64 1
  #endif
#endif

#define MAXBIT        (BITS_PER_WORD-1)
#define NWORDS(bits)  ( ((bits)+BITS_PER_WORD-1) / BITS_PER_WORD )
#define NBYTES(bits)  ( ((bits)+8-1) / 8 )

#define MPUassert(c,text) if (!(c)) { croak("Math::Prime::Util internal error: " text); }

#endif
