/*******************************************************************************
 * Copyright (c) 2015, Julien Bigot - CEA (julien.bigot@cea.fr)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of CEA nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific 
 *   prior written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "paraconf.h"

#include "status.h"

#define PC_BUFFER_SIZE 256

void error(PC_status_t *status, PC_errfunc_f *func, PC_errcode_t code, const char *message, ...)
{
	assert(status);
	va_list ap;
	va_start(ap, message);
	status->code = code;
	int bufsize = PC_BUFFER_SIZE;
	status->errmsg = malloc(bufsize);
	while ( vsnprintf(status->errmsg, bufsize, message, ap) >= bufsize ) {
		bufsize *= 2;
		status->errmsg = realloc(status->errmsg, bufsize);
	}
	if ( func ) func(*status);
	va_end(ap);
}