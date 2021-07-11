// 21/07/11 = Sun

/* Homework Problem 2.90 (*)

You have been assigned the task of writing a C function to compute a floating-
point representation of 2^x. You decide that the best way to do this is to
directly construct the IEEE single-precision representation of the result. When
x is too small, you routine will return 0.0. When x is large, it will return
+inf. Fill in the blank portions of the code that follows to compute the
correct result. Assume the function u2f returns a floating-point value having
an identical bit representation as its unsigned argument.

float fpwr2(int x)
{
  unsigned exp, frac;
  unsigned u;

  if (x < __________) {
    // Too small. Return 0.0.
    exp = __________;
    frac = __________;
  }
  else if (x < __________) {
    // Denormalized result
    exp = __________;
    frac = __________;
  }
  else if (x < __________) {
    // Normalized result
    exp = __________;
    frac = __________;
  }
  else {
    // Too big. Return +inf.
    exp = __________;
    frac = __________;
  }

  // Pack exp and frac into 32 bits
  u = exp << 23 | frac;
  // Return as float
  return u2f(u);
}

*/

// ----------
// Sample Run
// ----------
// fpwr2(-150)         = 0, while
// (float)pow(2, -150) = 0
// ----------------------------------------------------------------
// fpwr2(-149)         = 1.4013e-45, while
// (float)pow(2, -149) = 1.4013e-45
// fpwr2(-148)         = 2.8026e-45, while
// (float)pow(2, -148) = 2.8026e-45
// fpwr2(-130)         = 7.34684e-40, while
// (float)pow(2, -130) = 7.34684e-40
// fpwr2(-128)         = 2.93874e-39, while
// (float)pow(2, -128) = 2.93874e-39
// fpwr2(-127)         = 5.87747e-39, while
// (float)pow(2, -127) = 5.87747e-39
// ----------------------------------------------------------------
// fpwr2(-126)         = 1.17549e-38, while
// (float)pow(2, -126) = 1.17549e-38
// fpwr2(-120)         = 7.52316e-37, while
// (float)pow(2, -120) = 7.52316e-37
// fpwr2(-100)         = 7.88861e-31, while
// (float)pow(2, -100) = 7.88861e-31
// fpwr2( -50)         = 8.88178e-16, while
// (float)pow(2,  -50) = 8.88178e-16
// fpwr2(  -1)         = 0.5, while
// (float)pow(2,   -1) = 0.5
// fpwr2(   0)         = 1, while
// (float)pow(2,    0) = 1
// fpwr2(   1)         = 2, while
// (float)pow(2,    1) = 2
// fpwr2(  50)         = 1.1259e+15, while
// (float)pow(2,   50) = 1.1259e+15
// fpwr2( 100)         = 1.26765e+30, while
// (float)pow(2,  100) = 1.26765e+30
// fpwr2( 120)         = 1.32923e+36, while
// (float)pow(2,  120) = 1.32923e+36
// fpwr2( 126)         = 8.50706e+37, while
// (float)pow(2,  126) = 8.50706e+37
// fpwr2( 127)         = 1.70141e+38, while
// (float)pow(2,  127) = 1.70141e+38
// ----------------------------------------------------------------
// fpwr2( 128)         = inf, while
// (float)pow(2,  128) = inf
// fpwr2( 130)         = inf, while
// (float)pow(2,  130) = inf
// fpwr2( 150)         = inf, while
// (float)pow(2,  150) = inf

#include <math.h>
#include <stdio.h>

static float u2f(unsigned u)
{
  return *(float *)&u;
}

// IEEE 754 single-precision
// -------------------------
// sign bit s = 1, exp bits k = 8, frac bits n = 23
// exponent bias = 2^{k-1} - 1 = 127
// denormalized E = 1 - bias = 1 - 127 = -126
// denormalized smallest M = 2^m = 2^-23 => m = -23
// x for smallest 2^x representable = -126 + (-23) = -149
// normalized E = e - bias => [0x1, 0xfe] - bias = [1, 254] - 127 = [-126, 127]
// x for smallest 2^x as normalized = -126
// x for largest 2^x representable = 127
float fpwr2(int x)
{
  unsigned exp, frac;
  unsigned u;

  if (x < -149) {
    // Too small. Return 0.0.
    exp = 0x0;
    frac = 0x0;
  }
  else if (x < -126) {
    // Denormalized result
    exp = 0x0;
    frac = 0x000400000u >> (-x - 127);
  }
  else if (x < 128) {
    // Normalized result
    exp = x + 127;
    frac = 0x0;
  }
  else {
    // Too big. Return +inf.
    exp = 0xff;
    frac = 0x0;
  }

  // Pack exp and frac into 32 bits
  u = exp << 23 | frac;
  // Return as float
  return u2f(u);
}

void test(int x)
{
  printf("fpwr2(%4d)         = %g, while\n(float)pow(2, %4d) = %g\n", x,
         fpwr2(x), x, (float)pow(2, x));
}

int main()
{
  test(-150);
  printf("----------------------------------------------------------------\n");
  test(-149);
  test(-148);
  test(-130);
  test(-128);
  test(-127);
  printf("----------------------------------------------------------------\n");
  test(-126);
  test(-120);
  test(-100);
  test(-50);
  test(-1);
  test(0);
  test(1);
  test(50);
  test(100);
  test(120);
  test(126);
  test(127);
  printf("----------------------------------------------------------------\n");
  test(128);
  test(130);
  test(150);
  return 0;
}
