// 21/07/01 = Thu

/* Practice Problem 2.26

You are given the assignment of writing a function that determines whether one
string is longer than another. You decide to make use of the string library
function strlen having the following declaration:

// Prototype for library function strlen
size_t strlen(const char *s);

// Determine whether string s is longer than string t
// WARNING: This function is buggy
int strlonger(char *s, char *t)
{
  return strlen(s) - strlen(t) > 0;
}

When you test this on some sample data, things do·not seem to work quite right.
You investigate further and determine that, when compiled as a 32-bit program,
data type size_t is defined (via typedef) in header file stdio.h to be
unsigned.

A. For what cases will this function produce an incorrect result?
B. Explain how this incorrect result comes about.
C. Show how to fix the code so that it will work reliably. */

// Answer:
//
// (A) whenever string s is shorter than t, the result is incorrectly 1.
// (B) strlen(s) - strlen(t) is computed as a subtraction between unsigned
//     integers, and will always yield an nonnegative unsigned result.
// (C) compare the length directly, instead of doing a subtraction.

#include <stdio.h>
#include <string.h>

int strlonger(char *s, char *t)
{
  return strlen(s) > strlen(t);
}

void test(char *s, char *t)
{
  printf("is \"%s\" longer than \"%s\"? %d\n", s, t, strlonger(s, t));
}

int main()
{
  test("hello", "world");
  test("hello", "my friend");
  test("hello", "c");
  return 0;
}
