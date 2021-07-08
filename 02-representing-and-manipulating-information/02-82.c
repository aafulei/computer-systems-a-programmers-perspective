// 21/07/08 = Thu

/* Homework Problem 2.82 (*)

We are running programs where values of type int are 32 bits. They represented
in two's complement, and they are right shifted arithmetically. Values of type
unsigned are also 32 bits.

We generate arbitrary values x and y, and convert them to unsigned values as
follows:

// Create some arbitrary values
int x = random();
int y = random();
// Convert to unsigned
unsigned ux = (unsigned)x;
unsigned uy = (unsigned)y;

For each of the following C expressions, you are to indicate whether or not the
expression always yield 1. If it alwyas yields 1, describe the underlying
mathematical principles. Otherwise, given an example of arguments that make it
yield 0.

A. (x < y) == (-x > -y)

B. ((x + y) << 4) + y - x == 17 * y + 15 * x

C. ~x + ~y + 1 == ~(x + y)

D. (ux - uy) == -(unsigned)(y - x)

E. ((x >> 2) << 2) <= x

*/

// Answer: (A) Not always true. The negation of INT_MIN is itself (or lead to
//             undefined behavior by the standard). Thus let x = INT_MIN,
//             y = 0, and the left-hand side is 1 while the right-hand side is
//             0.
//
//         (B) Always true. Since 17 = (1 << 4) + 1, and 15 = (1 << 4) - 1,
//             both sides represent the lower 32 bits of the mathematical
//             result.
//
//         (C) Always true. Note that ~x + ~y + 1 = (-x-1) + (-y-1) + 1
//             = (x + y) - 1  = ~(x + y).
//
//         (D) Always true. Note that ux - uy = (unsigned)x - (unsigned)y
//             = (unsigned)(x - y) = -(unsigned)(y - x).
//
//         (E) Always true. This says that if we set the lowest 2 bits of x to
//             0, its value must be the same or becomes smaller. This is true.
