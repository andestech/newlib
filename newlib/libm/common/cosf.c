/* Single-precision cos function.
   Copyright (c) 2018 Arm Ltd.  All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
   3. The name of the company may not be used to endorse or promote
      products derived from this software without specific prior written
      permission.

   THIS SOFTWARE IS PROVIDED BY ARM LTD ``AS IS AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL ARM LTD BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "fdlibm.h"
#if !__OBSOLETE_MATH

#include <stdint.h>
#include <math.h>
#include "math_config.h"
#include "sincosf.h"

/* Fast cosf implementation.  Worst-case ULP is 0.56072, maximum relative
   error is 0.5303p-23.  A single-step signed range reduction is used for
   small values.  Large inputs have their range reduced using fast integer
   arithmetic.
*/
float
cosf (float y)
{
  double x = y;
  double s;
  int n;
  sincos_t *p = &sincosf_table[0];

  if (abstop12 (y) < abstop12 (pio4))
    {
      double x2 = x * x;

      if (unlikely (abstop12 (y) < abstop12 (0x1p-12f)))
	return 1.0f;

      return sinf_poly (x, x2, p, 1);
    }
  else if (likely (abstop12 (y) < abstop12 (120.0f)))
    {
      x = reduce_fast (x, p, &n);

      /* Setup the signs for sin and cos.  */
      s = p->sign[n & 3];

      if (n & 2)
	p = &sincosf_table[1];

      return sinf_poly (x * s, x * x, p, n ^ 1);
    }
  else if (abstop12 (y) < abstop12 (INFINITY))
    {
      uint32_t xi = asuint (y);
      int sign = xi >> 31;

      x = reduce_large (xi, &n);

      /* Setup signs for sin and cos - include original sign.  */
      s = p->sign[(n + sign) & 3];

      if ((n + sign) & 2)
	p = &sincosf_table[1];

      return sinf_poly (x * s, x * x, p, n ^ 1);
    }
  else
    return __math_invalidf (y);
}

#endif