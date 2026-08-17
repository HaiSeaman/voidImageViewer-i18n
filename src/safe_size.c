
//
// Copyright (C) 2025 voidtools / David Carpenter
// 
// Permission is hereby granted, free of charge, 
// to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), 
// to deal in the Software without restriction, 
// including without limitation the rights to use, 
// copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit 
// persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// safe size arithmetic.
// MUST be used when allocating memory.

#include "viv.h"

// safely add two values.
// SIZE_MAX is used as an invalid value.
// you will be unable to allocate SIZE_MAX bytes.
// always use safe_size when allocating memory.
SIZE_T safe_size_add(SIZE_T a,SIZE_T b)
{
	SIZE_T c;
	
	c = a + b;
	
	if (c < a) 
	{
		return SIZE_MAX;
	}
	
	return c;
}

// safely multiply a by b
// returns a * b
// returns SIZE_MAX if an overflow occurs.
SIZE_T safe_size_mul(SIZE_T a,SIZE_T b)
{
	if (b == 0)
	{
		return 0;
	}

	if (a > SIZE_MAX / b) 
	{
		return SIZE_MAX;
	}

	return a * b;
}

