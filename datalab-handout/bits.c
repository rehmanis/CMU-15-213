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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  // use 4 NAND gates to get XOR
  int z = ~(x & y);
  int xNandz = ~(x & z);
  int yNandz = ~(y & z);
  int xor = ~(xNandz & yNandz);

  return xor;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

  // add one so that if it is TMAX we now get TMIN(i.e 0x800..)
  int y = x + 1;
  // add logical not of the above result to it. This take care of
  // the case when x is -1 (i.2 0xFF...) and makes it non zero
  int z = y + !y;
  // now add the above result with x + 1. Only for the case of TMAX
  // x + 1 gives TMIN and TMIN + TMIN = 0 since !(x+1) = 1 in all cases
  // except when x = -1
  z = z + y;

  return !z;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {

  int oddBitConst = (0xAA << 24) + (0xAA << 16) + (0xAA << 8) + 0xAA;
  int result = x & oddBitConst;
  result += ~oddBitConst + 1;

  return !result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

  int result = ~x + 1;

  return result;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {

  // check if the MSB 3 and check if the LSB is within 0-9 separately
  int lsbx = 0x07 & x;
  int y = 0x0F & x;
  int shift = y >> 3;
  int result =  ((x >> 4) + (~0x03) + 1) | (shift & lsbx >> 1) | (shift & lsbx >> 2);

  return !result;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {

  // get the logical not of x. This will ensure that
  // we have 1 only for the case when x is 0 and 1 otherwsie
  // we then use this to decide either to chose y if !x = 0
  // and chose z if !x = 1
  int ifXisFalse = !x;
  // gives us either all zeros or all ones(oxFFFFFFFF)
  int allOnesOrZeros = (ifXisFalse << 31) >> 31;
  int result = (allOnesOrZeros & z) + (~allOnesOrZeros & y);

  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

  // we can subtrack y - x as long as their sign are same
  // if there signs are different and we subtract then we
  // will get overflow mainly when tmin and/or tmax is
  // ivolved

  // get the sign bit for x and y. Since right shift is
  // airthmetic, the variables will be either all 1s or 0s
  int signOfX = x >> 31;
  int signOfY = y >> 31;
  // determine if (y - x) is positive or negativ 
  int isYMinusXPos = (y + (~x + 1)) >> 31;
  // determine if x and y have same signs or not
  int isXandYSameSigns = !(signOfX ^ signOfY);
  // get the value of isLessOrEqual for the case when 
  // x and y have same signs or 0 if the signs are different
  int isXLessYForSameSign = isXandYSameSigns & !isYMinusXPos;
  // get the value of isLessOrEqual for the case when
  // x and y have different signs or 0 if the signs are same
  int isXLessYForDiffSign = (!isXandYSameSigns) & (signOfX & (!signOfY));

  return (isXLessYForSameSign | isXLessYForDiffSign);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {

  // using the sign bit, we can easily tell if a number is negative
  // use this to differentiate between 0 and any other number

  // get the sign of x and sign of 2's complement of x
  int signOfNegX = (x >> 31) + 1;
  int signOfX = ((~x  + 1) >> 31) + 1;
  // only for 0 will both signs be same and equal to 1. Since we add 1 
  // at the end it will be 1
  int result = (signOfX & signOfNegX);

  return result;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {

  /* we first convert x to positive if it is negative by flipping all bits */

  // used to count zeros left of most significant bit with 1
  // as explained below. 
  int numZeros;
  int numBits;
  int isAllZeros;
  int isZeroOrNegOne;

  // this will be all zeros or all ones
  int isXNeg = (x >> 31);
  // convert x to positive if it is negative by flipping all bits
  x = (isXNeg & ~x) | (~isXNeg & x);

  //printf("DEBUG: x before numZero: %d\n", x);

  /* now we count all the zeros that are left of the most significant
     bit with 1 and subtract it from 32. If it was originally a
     negative number than we add 1 to this. If it was zero, than
     add one as well.
  */

  /* use binary search to find all zeros left of the most significant
   bit with 1. Ex., 00010...0 should give us 3 zeros
  */
  // check if bits 32 to 16 are all zeros or not
  // Ex 0x00010000 will give numZeros = 0 at this point
  isAllZeros = !(x >> 16);
  numZeros = (isAllZeros << 4) & 16;
  // printf("DEBUG: numZeros for 32 to 16: %d\n", numZeros);

  // check if bits 32 to (24 - numZeros) or not
  // Ex. 0x00010000 will give numZeros = 8 at this point
  isAllZeros = !(x >> (24 + (~numZeros + 1)));
  numZeros += (isAllZeros << 3) & 8;

  // check if bits 32 to (28 - numZeros) are zeros or not
  isAllZeros = !(x >> (28 + (~numZeros + 1)));
  numZeros += (isAllZeros << 2) & 4;

  // check if bits 32 to (30 - numZeros) are zeros or not
  isAllZeros = !(x >> (30 + (~numZeros + 1)));
  numZeros += (isAllZeros << 1) & 2;

  // check if bits 32 to (31 - numZeros) are zeros or not
  isAllZeros = !(x >> (31 + (~numZeros + 1)));
  numZeros += isAllZeros & 1;

  // we subtract numZeros from 32. We also add 1 because
  // any number part from 0 or -1 needs atleast 2bits
  // to be represented since 1 of the bits is used for the sign
  numBits = 32 + (~numZeros + 1) + 1;
  isZeroOrNegOne = (!x << 31) >> 31;

  // if x was 0 or -1 return 1 else return numBits calculated above
  return ((numBits  & ~isZeroOrNegOne) | (1 & isZeroOrNegOne));
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
