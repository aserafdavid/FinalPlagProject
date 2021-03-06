/*******************************************************************************
* Copyright 2005-2017 Intel Corporation All Rights Reserved.
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*******************************************************************************/

/*
 *
 * dfftw_plan_guru_r2r - FFTW3 Fortran 77 wrapper to Intel(R) MKL.
 *
 ******************************************************************************
 */

#include "fftw3_mkl_f77.h"

void
dfftw_plan_guru_r2r(PLAN *p, INTEGER *rank, INTEGER *n, INTEGER *is,
                    INTEGER *os, INTEGER *howmany_rank, INTEGER *howmany_n,
                    INTEGER *howmany_is, INTEGER *howmany_os, REAL8 *in,
                    REAL8 *out, INTEGER *kind, INTEGER *flags)
{
    fftw_iodim64 dims64[MKL_MAXRANK];
    fftw_iodim64 howmany_dims64[MKL_ONE];
    fftw_r2r_kind knd[MKL_MAXRANK];
    int i;

    if (p == NULL || rank == NULL || n == NULL || kind == NULL || flags == NULL)
        return;
    if (is == NULL || os == NULL) return;
    if (howmany_rank == NULL) return;
    if (*howmany_rank > 0 && (howmany_n == NULL || howmany_is == NULL || howmany_os == NULL)) return;

    *(MKL_INT64 *)p = 0;
    if (*rank > MKL_MAXRANK || *howmany_rank > MKL_ONE) return;

    for (i = 0; i < *rank; ++i)
    {
        dims64[i].n = n[*rank - i - 1];
        dims64[i].is = is[*rank - i - 1];
        dims64[i].os = os[*rank - i - 1];
        knd[i] = (fftw_r2r_kind) kind[*rank - i - 1];
    }
    for (i = 0; i < *howmany_rank; ++i)
    {
        howmany_dims64[i].n = howmany_n[*rank - i - 1];
        howmany_dims64[i].is = howmany_is[*rank - i - 1];
        howmany_dims64[i].os = howmany_os[*rank - i - 1];
    }
    *(fftw_plan *)p =
        fftw_plan_guru64_r2r(*rank, dims64, *howmany_rank, howmany_dims64, in,
                             out, knd, *flags);
}
