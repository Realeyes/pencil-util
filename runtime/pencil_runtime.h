/*
 * Copyright (c) 2014, ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef PENCIL_RUNTIME_H
#define PENCIL_RUNTIME_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum PENCIL_INIT_FLAG
{
    PENCIL_TARGET_DEVICE_GPU_ONLY,
    PENCIL_TARGET_DEVICE_CPU_ONLY,
    PENCIL_TARGET_DEVICE_GPU_THEN_CPU,
    PENCIL_TARGET_DEVICE_CPU_THEN_GPU,
    PENCIL_TARGET_DEVICE_DYNAMIC
};

/** Memory allocation. Can be used in the same way, malloc is used.  */
extern void * pencil_alloc (size_t size);

/** Free memory allocated by pencil_alloc.  */
extern void pencil_free (void * ptr);

/** Initialize PENCIL runtime.  */
extern void pencil_init (enum PENCIL_INIT_FLAG flag);

/** Release PENCIL runtime.  */
extern void pencil_shutdown (void);


/** smaller of two numbers, 
    potentially called by ppcg generated code */
static inline int __attribute__((const)) __ppcg_min(int a, int b) 
{
    if (a < b)
        return a;
    return b;
}

/** greater of two numbers, 
    potentially called by ppcg generated code */
static inline int __attribute__((const)) __ppcg_max(int a, int b) 
{
    if (a > b)
        return a;
    return b;
}

/** floored division (round to negative infinity), 
    potentially called by ppcg generated code      */
static inline int __attribute__((const)) __ppcg_floord(int n, int d)
{
    if (n<0)
        return -((-n+d-1)/d);
    return n/d;
}

#ifdef __cplusplus
}
#endif

#endif
