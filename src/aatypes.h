#ifndef SCREEN_AATYPES_H
#define SCREEN_AATYPES_H

#include <stdint.h>

typedef uint32_t image_t;
typedef uint32_t color_t;
typedef uint8_t font_t;
typedef uint32_t mbcs_t;

typedef enum attr_e {
			// attribute            terminfo code   termcap code    ECMA-48 SGR     custom SGR
			//                      (on   / off)    (on / off)      (on / off)      (on / off)
			//
	ATTR_BD,	// bold mode            bold  / *       md / *          1 / 22
	ATTR_DI,	// dim mode             dim   / *       mh / *          2 / 22
	ATTR_IT,	// italicized           sitm  / ritm    ZH / ZR         3 / 23          3:1 / 23:1
	ATTR_US,	// underscore mode      smul  / rmul    us / ue         4 / 24
	ATTR_BL,	// slow blinking        blink / *       mb / *          5 / 25                          (> 0.4s; < 2.5Hz; < 150/min)
	ATTR_FB,	// fast blinking        -               -               6 / 25                          (≤ 0.4s; ≥ 2.5Hz; ≥ 150/min; SGR only)
	ATTR_RV,	// reverse video        rev   / *       mr / *          7 / 27
	ATTR_HI,	// hidden               invis / *       mk / *          8 / 28
	ATTR_ST,	// strikethru           smxx  / rmxx    -               9 / 29                          (terminfo only)
	ATTR_SO,	// standout             smso  / rmso    so / se         - / -           3:2 / 23:2
	NATTR		//
			//      * reset all     -     / sgr0    -  / me         - / 0
} attr_t;

typedef enum attr_mask_e {

	A_BD = 1U << ATTR_BD,
	A_DI = 1U << ATTR_DI,
	A_IT = 1U << ATTR_IT,
	A_US = 1U << ATTR_US,
	A_BL = 1U << ATTR_BL,
	A_FB = 1U << ATTR_FB,
	A_RV = 1U << ATTR_RV,
	A_HI = 1U << ATTR_HI,
	A_ST = 1U << ATTR_ST,
	A_SO = 1U << ATTR_SO,

	A__UNSET = 1U << NATTR,
	A__MASK = A__UNSET - 1U,

	A_DFT_COLOR = 1U << NATTR+1,	/* what "\e[0m" does */
} attr_mask_t;

/* Spare bits in the packed rendition encode attribute operations.
 * TODO: these bits are not as spare as they seem, since attr_mask_e
 *       requires at least 9 bits, one of which is *already* being lost.
 *
 * Proposal: allocate 25 bits for each colour: 1 that signals 24-bit color, and
 * then (otherwise) 8 code bits and 16 colour bits.
 *
 * Option 1: "KEEP" would be one of those codes.
 * Option 2: pass these render control flags as separate parameter(s), without
 *           mashing them into the attribute words.
 */

enum rend_flags_e {

        REND_ADD	= (uint64_t)1 << 51,
        REND_SUB	= (uint64_t)1 << 55,
        REND_XOR	= REND_ADD | REND_SUB,
        REND_SET	= (uint64_t)1 << 63,

        /* Colour mode 3 preserves the current foreground/background. */
        REND_KEEP_FG	= (uint64_t)3 << 48,
        REND_KEEP_BG	= (uint64_t)3 << 52,

};

#endif				/*SCREEN_AATYPES_H */
