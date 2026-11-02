#ifndef SCREEN_BITMATH_H
#define SCREEN_BITMATH_H

#include <stdint.h>

/* lookup for base-2 logarithm of a single bit */

#if defined HAVE_FFS || defined HAVE_FFSLL
/* Headers for system-supplied ffs…() functions */
# if defined HAVE_STRINGS_H
#  include <strings.h>
# elif defined HAVE_STRING_H
#  include <string.h>
# endif
#else
/* Windows intrinsics if compiling natively on MSVC */
# ifdef _MSC_VER
#  include <intrin.h>
# endif
#endif

# define bitmap_ffs_DB(x)  ((x) * bitmap_ffs_DB_factor >> bitmap_ffs_DB_shift)
# define bitmap_ffs_DB1(x) [bitmap_ffs_DB((bitmap_ffs_TYPE)1U << (x))] = (x)+1
# define bitmap_ffs_DB8(x) bitmap_ffs_DB1(x|0), bitmap_ffs_DB1(x|1), bitmap_ffs_DB1(x|2), bitmap_ffs_DB1(x|3), \
                    bitmap_ffs_DB1(x|4), bitmap_ffs_DB1(x|5), bitmap_ffs_DB1(x|6), bitmap_ffs_DB1(x|7)

# define bitmap_ffs_MO(x)  ((x) % bitmap_ffs_MO_modulus)
# define bitmap_ffs_MO1(x) [bitmap_ffs_MO((bitmap_ffs_TYPE)1U << (x))] = (x)+1
# define bitmap_ffs_MO8(x) bitmap_ffs_MO1(x+0), bitmap_ffs_MO1(x+1), bitmap_ffs_MO1(x+2), bitmap_ffs_MO1(x+3), \
		    bitmap_ffs_MO1(x+4), bitmap_ffs_MO1(x+5), bitmap_ffs_MO1(x+6), bitmap_ffs_MO1(x+7)

#ifndef HAVE_FFSLL
# define bitmap_ffs_TYPE unsigned long long

# if defined __GNUC__ || defined __clang__
#  define ffsll __builtin_ffsll
# elif defined _MSC_VER
#  include <intrin.h>
# elif defined HAVE_FFS
static inline int ffsll(uint64_t x)
{
	int r = ffs((unsigned int)x);
	if (r) return r;
	r = ffs((unsigned int)(x >> 32));
	if (r) return r+32;
	return 0;
}
# elif PREFER_DEBRUIN_BITCOUNT
/* DeBruin method */
static inline int ffsll(long long x) {
	if (x == 0) return 0;
	/*
	 * parameters for DeBruin sequence derived from primitive polynomial x⁶ + x + 1.
	 */
	# define bitmap_ffs_DB_factor 0x022FDD63CC95386DULL
	# define bitmap_ffs_DB_shift 58
	static const int8_t map[64] = {
		bitmap_ffs_DB8(0),  bitmap_ffs_DB8(8),  bitmap_ffs_DB8(16), bitmap_ffs_DB8(24),
		bitmap_ffs_DB8(32), bitmap_ffs_DB8(40), bitmap_ffs_DB8(48), bitmap_ffs_DB8(56)
	};
	x &= -x;
	return map[bitmap_ffs_DB(x)];
	# undef bitmap_ffs_DB_factor
	# undef bitmap_ffs_DB_shift
}
# elif PREFER_MODULUS_BITCOUNT
/* Modulus method */
static inline int ffsll(uint64_t x) {
	#define bitmap_ffs_MO_modulus 67
	static const int8_t map[64] = {
		bitmap_ffs_MO8(0),  bitmap_ffs_MO8(8),  bitmap_ffs_MO8(16), bitmap_ffs_MO8(24),
		bitmap_ffs_MO8(32), bitmap_ffs_MO8(40), bitmap_ffs_MO8(48), bitmap_ffs_MO8(56),
	};
	x &= x-1;
	return map[bitmap_ffs_MO(x)];
	#undef bitmap_ffs_MO_modulus
}
# elif PREFER_MASKING_BITCOUNT
/* bit-masking method */
static inline int ffsll(uint64_t x) {
	x &= -x;
	if (!x) return -1;
	int r = 0;
	if (x & 0xffffffff00000000ULL) r |= 32;
	if (x & 0xffff0000ffff0000ULL) r |= 16;
	if (x & 0xff00ff00ff00ff00ULL) r |= 8;
	if (x & 0xf0f0f0f0f0f0f0f0ULL) r |= 4;
	if (x & 0xccccccccccccccccULL) r |= 2;
	if (x & 0x5555555555555555ULL) r |= 1;
	return r;
}
# else
/* Walk across the bits; slow but obvious */
static inline int ffsll(uint64_t x) {
	for (int r=1; r<= 64; ++r, x>>=1)
		if (x & 1)
			return r;
	return -1;
}
# endif

# undef bitmap_ffs_TYPE
# define HAVE_FFSLL 1	/* we do now! */
#endif

#ifndef HAVE_FFS
# define bitmap_ffs_TYPE unsigned int
# if defined __GNUC__ || defined __clang__
#  define ffs   __builtin_ffs
# elif defined(_MSC_VER)
    /* 3. Native Windows (MSVC) bit-scan fallback */
    static inline int ffs(unsigned int x) {
        unsigned long index;
        return _BitScanForward(&index, x) ? (int)(index + 1) : 0;
    }
# elif PREFER_DEBRUIN_BITCOUNT
/* DeBruin method */
static inline int ffs(uint32_t x) {
	if (x == 0) return 0;
	/*
	 * parameters for DeBruin sequence derived from primitive polynomial x⁵ + x + 1.
	 */
	# define bitmap_ffs_DB_factor 0x077CB531U
	# define bitmap_ffs_DB_shift  27
	static const uint8_t map[32] = {
		bitmap_ffs_DB8(0),  bitmap_ffs_DB8(8),  bitmap_ffs_DB8(16), bitmap_ffs_DB8(24)
	};
	return map[bitmap_ffs_DB(x)];
	# undef bitmap_ffs_DB_factor
	# undef bitmap_ffs_DB_shift
}
# elif PREFER_MODULUS_BITCOUNT
/* Modulus method */
static inline int ffs(uint32_t x) {
	#define bitmap_ffs_MO_modulus 37
	static const int8_t map[32] = {
		bitmap_ffs_MO8(0),  bitmap_ffs_MO8(8),  bitmap_ffs_MO8(16), bitmap_ffs_MO8(24),
	};
	x &= x - 1;
	return map[bitmap_ffs_MO(x)];
	# undef bitmap_ffs_MO_modulus
}
# elif PREFER_MASKING_BITCOUNT
/* bit-masking method */
static inline int ffs(uint32_t x) {
	x &= -x;
	if (!x) return -1;
	int r = 0;
	if (x & 0xffff0000U) r |= 16;
	if (x & 0xff00ff00U) r |= 8;
	if (x & 0xf0f0f0f0U) r |= 4;
	if (x & 0xccccccccU) r |= 2;
	if (x & 0x55555555U) r |= 1;
	return r;
}
# else
static inline int ffs(unsigned x)
{
	return ffsll(x);
}
# endif

# define HAVE_FFS 1	/* we do now! */
# undef bitmap_ffs_TYPE
#endif

# undef bitmap_ffs_DB
# undef bitmap_ffs_DB
# undef bitmap_ffs_DB1
# undef bitmap_ffs_DB8
# undef bitmap_ffs_MO
# undef bitmap_ffs_MO1
# undef bitmap_ffs_MO8
# undef bitmap_ffs_MO1
# undef bitmap_ffs_MO8

static inline uint64_t  lo_bit(uint64_t i)        { return i & -i; }
static inline uint64_t  hi_bits(uint64_t i)       { return i ^ lo_bit(i); }
static inline uint64_t  range_end_bit(uint64_t i) { return (i + lo_bit(i)) >> 1; }	// top of a consecutive range
static inline bool      is_single_bit(uint64_t i) { return ! hi_bits(i); }

#if 0
# define log_lo_bit(x) _Generic(x,\
			char:          ffs((unsigned char)(x))-1, \
			unsigned char: ffs(x)-1, \
			signed char:   ffs((unsigned char)(x))-1, \
			unsigned int:  ffs(x)-1, \
			int:           ffs((unsigned int)(x))-1, \
			default:       ffsll((unsigned long long int)x)-1)
#else
/* Work correctly with enums... */
# define log_lo_bit(x) ( sizeof(x) <= 4 ? ffs((uint32_t)x) - 1 : ffsll((uint64_t)x) - 1 )
#endif

#endif /*SCREEN_BITMATH_H*/
