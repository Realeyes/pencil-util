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

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pencil_int.h"
#include "pencil_runtime.h"
#include "impl/impl.h"

static const char * env_name = "PENCIL_TARGET_DEVICE";
static const char * GPU_TARGET_DEVICE = "gpu";
static const char * CPU_TARGET_DEVICE = "cpu";
static const char * GPU_CPU_TARGET_DEVICE = "gpu_cpu";
static const char * CPU_GPU_TARGET_DEVICE = "cpu_gpu";

pencil_cl_program opencl_create_program_from_file (const char *filename,
                                                   const char *opts)
{
    return __int_opencl_create_program_from_file (filename, opts);
}

pencil_cl_program opencl_create_program_from_string (const char *program,
                                                     size_t size,
                                                     const char *opts)
{
    return __int_opencl_create_program_from_string (program, size, opts);
}

void opencl_release_program (pencil_cl_program program)
{
    return __int_opencl_release_program (program);
}

pencil_cl_kernel opencl_create_kernel (pencil_cl_program program, const char *name)
{
    return __int_opencl_create_kernel (program, name);
}

void opencl_release_kernel (pencil_cl_kernel kernel)
{
    return __int_opencl_release_kernel (kernel);
}

pencil_cl_mem opencl_create_device_buffer (cl_mem_flags flags, size_t size,
                                    void *host_ptr)
{
    return __int_opencl_create_device_buffer (flags, size, host_ptr);
}

void opencl_release_buffer (pencil_cl_mem buffer)
{;
    return __int_opencl_release_buffer (buffer);
}

void opencl_copy_to_device (pencil_cl_mem dev, size_t size, void *host)
{
    return __int_opencl_copy_to_device (dev, size, host);
}

void opencl_copy_to_host (pencil_cl_mem dev, size_t size, void *host)
{
    return __int_opencl_copy_to_host (dev, size, host);
}

void *pencil_alloc (size_t size)
{
    return __int_pencil_alloc (size);
}

void pencil_free (void *ptr)
{
    return __int_pencil_free (ptr);
}

enum PENCIL_INIT_FLAG check_environment ()
{
    const char * target_device = getenv(env_name);
    if (!target_device)
    {
        return PENCIL_TARGET_DEVICE_DYNAMIC;
    }
    if (!strcmp (target_device, GPU_TARGET_DEVICE))
    {
        return PENCIL_TARGET_DEVICE_GPU_ONLY;
    }
    if (!strcmp (target_device, CPU_TARGET_DEVICE))
    {
        return PENCIL_TARGET_DEVICE_CPU_ONLY;
    }
    if (!strcmp (target_device, GPU_CPU_TARGET_DEVICE))
    {
        return PENCIL_TARGET_DEVICE_GPU_THEN_CPU;
    }
    if (!strcmp (target_device, CPU_GPU_TARGET_DEVICE))
    {
        return PENCIL_TARGET_DEVICE_CPU_THEN_GPU;
    }
    return PENCIL_TARGET_DEVICE_DYNAMIC;
}

void pencil_init (enum PENCIL_INIT_FLAG flag)
{
    static const cl_device_type gpu_only[] = {CL_DEVICE_TYPE_GPU};
    static const cl_device_type cpu_only[] = {CL_DEVICE_TYPE_CPU};
    static const cl_device_type gpu_cpu[] = {CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_CPU};
    static const cl_device_type cpu_gpu[] = {CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU};
    if (flag == PENCIL_TARGET_DEVICE_DYNAMIC)
    {
        flag = check_environment ();
    }
    switch (flag)
    {
        case PENCIL_TARGET_DEVICE_GPU_ONLY: return __int_pencil_init (1, gpu_only);
        case PENCIL_TARGET_DEVICE_CPU_ONLY: return __int_pencil_init (1, cpu_only);
        case PENCIL_TARGET_DEVICE_GPU_THEN_CPU: return __int_pencil_init (2, gpu_cpu);
        case PENCIL_TARGET_DEVICE_CPU_THEN_GPU: return __int_pencil_init (2, cpu_gpu);
        case PENCIL_TARGET_DEVICE_DYNAMIC: return __int_pencil_init (0, NULL);
        default: assert(0);
    }
}

void pencil_shutdown ()
{
    return __int_pencil_shutdown ();
}


void opencl_set_kernel_arg (pencil_cl_kernel kernel, cl_uint idx, size_t size,
                            const void *value, int buffer)
{
    return __int_opencl_set_kernel_arg (kernel, idx, size, value, buffer);
}

void opencl_launch_kernel (pencil_cl_kernel kernel, cl_uint work_dim,
                           const size_t *goffset, const size_t *gws,
                           const size_t *lws)
{
    return __int_opencl_launch_kernel (kernel, work_dim, goffset, gws, lws);
}
