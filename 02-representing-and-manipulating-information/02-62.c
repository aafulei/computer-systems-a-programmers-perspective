// 21/07/05 = Mon

/* Practice Problem 2.62 (***)

Write a function int_shifts_are_arithmetic() that yields 1 when run on a
machine that uses arithmetic right shifts for data type int and yields 0
otherwise. You code should work on a machine with any word sizes. Test you code
on several machines */

/* ------------------------------
   Bit-Level Integer Coding Rules
   ------------------------------

  - Assumptions

    - two's-complement form

    - right shifts performed arithmetically

    - int is w bits long (use sizeof(int) << 3 to compute w)

  - Forbidden

    - conditionals, loops, switch, function calls, and macro invocations

    - division, modulus, and multiplication

    - relative comparisons (<, >, <=, and >=)

  - Allowed

    - all bit-level and logic operations

    - left and right shifts, with amounts between 0 and w - 1

    - addition and subtraction

    - equality (==) and inequality (!=) (some problems do not allow these)

    - INT_MIN and INT_MAX

    - casting between int and unsigned */

// ----------
// Sample Run
// ----------
// int_shifts_are_arithmetic() = 1

#include <stdio.h>

int int_shifts_are_arithmetic()
{
  return (-1 >> 1) == -1;
}

int main()
{
  printf("int_shifts_are_arithmetic() = %d\n", int_shifts_are_arithmetic());
  return 0;
}
