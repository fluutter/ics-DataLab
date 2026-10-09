/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(~x&y)&~(x&~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int m = x >> 31;
  return ~(x&m)+1;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int y=x>>(src<<3);
  y=y&0xFF;
  x=x&~(0xFF<<(dst<<3));
  x=x+(y<<(dst<<3));
  return x;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int a = ~(((1<<31)>>n)<<1);
  return (x>>n)&a;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0xF0 | (0xF0 << 8); 
  mask = mask | (mask << 16); 
  return ((x & ~mask) << 4) | (((x & mask) >> 4) & ~mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y=~x^(~x&(x+1));
  return y&(~y+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  int y = ~ x;
  y = y & 1;
  return y;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int t = (~n + 1) & 31;
  int a = ~(((1<<31)>>n)<<1);
  int y = (x >> n) & a;
  int z = (x & ~(~0 << n)) << t;
  return y | z;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
    int r = x & ~(~0 << n);  //余数：x 的最低 n 位
    int down = x + (~r + 1);  //x-r 向下取整
    int half = 1 << (n + ~0);  //2^(n-1)

    int up = ((r + half) >> n) &
             ((!!(r ^ half)) | ((x >> n) & 1));
//up的条件：r+half>=2^n并且((r不等于half)或者(x/2^n为奇数))
    return down + (up << n);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
    int sx = x >> 31;//x的符号位
    int sign = sx ^ (y >> 31);//异号

    int diff = x + (~y + 1);//差

    int gt = (sign & !sx) | (~sign & !(diff >> 31));//x正y负，或者xy同号并且不相等。

    int base = (x >> 1) + (y >> 1) + ((x & 1) & (y & 1));//（x+y）/2向下取整

    int odd = (x ^ y) & 1;//x+y为奇数

    return base + (odd & gt);
}//找到并且列出要+1的全部条件就好。

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int sx = x >> 31;//x的符号位（最高位填充）
    int sa = a >> 31;//a的符号位（最高位填充）
    int sb = b >> 31;//b的符号位（最高位填充）

    int diffA = x + (~a + 1);//x-a
    int diffB = x + (~b + 1);//x-b

    int signA = (sx ^ sa) & sx; //-1（111……11）时，xa异号并且x为负，即x-a为负
    signA = signA | (~(sx ^ sa) & (diffA >> 31)); //-1时，x-a为负（xa异号且x负，或者xa同号且x-a为负）。

    int signB = (sx ^ sb) & sx;
    signB = signB | (~(sx ^ sb) & (diffB >> 31));//同理，x-b为负

    int inside = !!(signA ^ signB);//如果signA和signB异号那么inside为真
    int equalA = !(x ^ a);
    int equalB = !(x ^ b);

    return inside | equalA | equalB;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int top = (x >> 29) & 7;              // x 的最高3位
    int ov4 = !!((top ^ (top >> 1)) & 3); // x << 2 是否溢出。top=000或111时都不溢出，所以就用异或判断top的3位是否相同。

    int y = x << 2;                       // 4x
    int z = y + x;                        // 5x

    //int ov5 = ((y ^ z) >> 31) & 1;
    //int ov5 = !((y ^ x) >> 31) & ((y ^ z) >> 31);但((y ^ z) >> 31)可能返回-1，不行
    //只要z和x的符号位不同，就可以判断y+x这一步发生溢出了吗？不是的，可能x和z符号位相同但已经溢出（和y符号位不同）。
    int ov5 = (!((y ^ x) >> 31)) & (!!((y ^ z) >> 31));
    int ov = ov4 | ov5;                   // 总溢出

    int sign = x >> 31;                   // 取符号位。0: 正数，-1: 负数
    int mask = ~ov + 1;                   // ov=1 → -1；ov=0 → 0

    int min = 1 << 31;                    // INT_MIN
    int max = ~min;                        // INT_MAX

    int sat = (sign & min) | (~sign & max);//如果溢出那么就取sat，sat根据x的符号分配到时候是min还是max

    return (mask & sat) | (~mask & z);//返回最终结果，如果ov那么用sat，如果不ov（mask=0）那么用z
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int sx = x >> 31;
    int sy = y >> 31;
    int s = x + y;
    int ss = s >> 31;

    int pos1 = !(sx | sy) & !!ss;
    int neg1 = !!(sx & sy) & !ss;
    int o1 = pos1 + (~neg1 + 1);

    int sz = z >> 31;
    int t = s + z;
    int st = t >> 31;

    int pos2 = !(ss | sz) & !!st;
    int neg2 = !!(ss & sz) & !st;
    int o2 = pos2 + (~neg2 + 1);

    return o1 + o2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    /* NaN or infinity */
    if (exp == 0xFF)
        return uf;

    /* Zero or subnormal */
    if (exp == 0) {
        unsigned val = frac + (frac >> 1);

        /*
         * Round-to-nearest-even.
         * The discarded bit is the lowest bit of frac.
         */
        //if ((frac & 1) && ((val & 1) || (frac & 2)))
          //  val++;

        /*
         * A subnormal result may become a normal number.
         */
        if (val >= 0x800000) {
            exp = 1;
            frac = val - 0x800000;
        } else {
            frac = val;
        }

        return sign | (exp << 23) | frac;
    }

    /* Normalized number */
    {
        unsigned sig = frac | 0x800000;
        unsigned product = sig + (sig << 1);
        unsigned result = product >> 1;

        /*
         * Round-to-nearest-even.
         * product's lowest bit is the discarded bit.
         */
        if ((product & 1) && (result & 1))
            result++;

        /*
         * 10.xxxxx -> 1.0xxxxx × 2
         */
        if (result & 0x1000000) {
            result >>= 1;
            exp++;
        }

        /* Overflow -> infinity */
        if (exp >= 0xFF)
            return sign | 0x7F800000;

        frac = result & 0x7FFFFF;
        return sign | (exp << 23) | frac;
    }
}


// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF)
        return uf;

    /* |f| < 1 */
    if (exp < 126)
        return sign;

    /* |f| >= 2^24 */
    if (exp >= 150)
        return uf;

    {
        int E = exp - 127;
        int shift = 23 - E;
        unsigned sig = frac | 0x800000;
        unsigned intpart = sig >> shift;
        unsigned rem = sig & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);

        /* round to nearest even */
        if (rem > half || (rem == half && (intpart & 1)))
            intpart++;

        /* Convert rounded integer back to float */
        if (intpart == 0)
            return sign;

        {
            unsigned msb = 0;
            unsigned t = intpart;

            while (t >> 1) {
                t >>= 1;
                msb++;
            }

            {
                unsigned newexp = (msb + 127) << 23;
                unsigned newfrac;

                if (msb <= 23) {
                    newfrac = intpart << (23 - msb);
                } else {
                    unsigned s = msb - 23;
                    unsigned r = intpart & ((1 << s) - 1);
                    unsigned h = 1 << (s - 1);

                    newfrac = intpart >> s;

                    if (r > h || (r == h && (newfrac & 1)))
                        newfrac++;

                    if (newfrac == 0x800000) {
                        newfrac = 0;
                        newexp += 1 << 23;
                    }

                    newfrac &= 0x7FFFFF;
                }

                return sign | newexp | newfrac;
            }
        }
    }
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned absx;
    unsigned msb = 0;
    unsigned frac;
    unsigned exp;

    if (x == 0)
        return 0;

    if (x < 0) {
        sign = 0x80000000;
        absx = (~x + 1);
    } else {
        absx = x;
    }

    /* Find the position of the highest 1 bit */
    {
        unsigned t = absx;

        while (t >> 1) {
            t >>= 1;
            msb++;
        }
    }

    exp = (msb + 127) << 23;

    /*
     * If the integer fits into the 24 significant bits
     * (hidden 1 + 23 fraction bits), no rounding is needed.
     */
    if (msb <= 23) {
        frac = (absx << (23 - msb)) & 0x7FFFFF;
        return sign | exp | frac;
    }

    /*
     * Otherwise shift right and round.
     */
    {
        unsigned shift = msb - 23;
        unsigned sig = absx >> shift;
        unsigned rem = absx & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);

        /* round to nearest even */
        if (rem > half || (rem == half && (sig & 1)))
            sig++;

        /*
         * Rounding can create 100...0,
         * so the exponent must increase by 1.
         */
        if (sig == 0x1000000) {
            sig >>= 1;
            exp += 1 << 23;
        }

        frac = sig & 0x7FFFFF;

        return sign | exp | frac;
    }
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    int mask1 = 0x55 | (0x55 << 8);
    int mask2;
    int mask3;

    mask1 = mask1 | (mask1 << 16);

    mask2 = 0x33 | (0x33 << 8);
    mask2 = mask2 | (mask2 << 16);

    mask3 = 0x0F | (0x0F << 8);
    mask3 = mask3 | (mask3 << 16);

    x = (x & mask1) + ((x >> 1) & mask1);
    x = (x & mask2) + ((x >> 2) & mask2);
    x = (x & mask3) + ((x >> 4) & mask3);

    int a = 0xFF | (0xFF<<16);
    int b = 0xFF | (0xFF<<8);

    x = (x & a) + ((x >> 8) & a);
    x = (x & b) + (x >> 16);

    return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
    int mask16 = 0xFF | (0xFF << 8);
    int mask8 = mask16 ^ (mask16 << 8);
    int mask4 = mask8 ^ (mask8 << 4);
    int mask2 = mask4 ^ (mask4 << 2);
    int mask1 = mask2 ^ (mask2 << 1);

    x = ((x & mask1) << 1) | ((x >> 1) & mask1);
    x = ((x & mask2) << 2) | ((x >> 2) & mask2);
    x = ((x & mask4) << 4) | ((x >> 4) & mask4);
    x = ((x & mask8) << 8) | ((x >> 8) & mask8);

    return (x << 16) | ((x >> 16) & mask16);
}
