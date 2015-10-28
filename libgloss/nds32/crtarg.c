/*
Copyright (c) 2013-2014 Andes Technology Corporation.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    The name of the company may not be used to endorse or promote
    products derived from this software without specific prior written
    permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL RED HAT INCORPORATED BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*
   crtarg.c: This is designed for passing arguments to a program.

   The Andes simulator -- SID -- has special syscall which
   would prepare user-specified arguments in the memory.
   We use _arg_init function to create necessary content
   onto stack so that main function can access them.
   See crt0.S or crt1.S for more implementation of how we
   invoke _arg_init function.
 */


#include <stdio.h>
#include <string.h>

/* Set up argc and argv, up to 64 arguments is allowed.
   CMD points to a complete command string prpared by simulator.
   ARGV will hold the beginning location of each argument string.  */
int
_arg_init(char *cmd, char *argv[])
{
  int count = 0;
  char *sep = " \t";

  if (cmd = strtok (cmd, sep))
    {
      do
        {
          argv[count] = cmd;
          count++;

          if (count == 64)
            break;
        }
      while (cmd = strtok (NULL, sep));
    }

  return count;
}
