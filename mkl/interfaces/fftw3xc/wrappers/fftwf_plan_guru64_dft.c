/*******************************************************************************
* Copyright 2008-2017 Intel Corporation All Rights Reserved.
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
 * fftwf_plan_guru64_dft - FFTW wrapper to Intel(R) MKL.
 *
 ******************************************************************************
 */

#include "fftw3_mkl.h"

static void execute_fi(fftw_mkl_plan p);
static void execute_bi(fftw_mkl_plan p);
static void execute_fo(fftw_mkl_plan p);
static void execute_bo(fftw_mkl_plan p);

fftwf_plan
fftwf_plan_guru64_dft(int rank, const fftwf_iodim64 *dims, int howmany_rank,
                     const fftwf_iodim64 *howmany_dims, fftwf_complex *in,
                     fftwf_complex *out, int sign, unsigned flags)
{
    fftw_mkl_plan mkl_plan;
    MKL_LONG periods[MKL_MAXRANK];
    MKL_LONG istrides[MKL_MAXRANK + 1];
    MKL_LONG ostrides[MKL_MAXRANK + 1];
    MKL_LONG s = 0;                    /* status */
    int i;

    if (rank > MKL_MAXRANK || howmany_rank > MKL_ONE)
        return NULL;

    if (dims == NULL || (howmany_rank > 0 && howmany_dims == NULL))
        return NULL;

    mkl_plan = fftw3_mkl.new_plan();
    if (!mkl_plan)
        return NULL;

    istrides[0] = 0;
    ostrides[0] = 0;

    for (i = 0; i < rank; ++i)
    {
        periods[i] = (MKL_LONG)dims[i].n;
        istrides[i + 1] = (MKL_LONG)dims[i].is;
        ostrides[i + 1] = (MKL_LONG)dims[i].os;

        /* check if MKL_LONG is sufficient to hold dims */
        if (periods[i] != dims[i].n)
            goto broken;
        if (istrides[i + 1] != dims[i].is)
            goto broken;
        if (ostrides[i + 1] != dims[i].os)
            goto broken;
    }
    if (rank == 1)
        s = DftiCreateDescriptor(&mkl_plan->desc, DFTI_SINGLE, DFTI_COMPLEX,
                                 (MKL_LONG)rank, periods[0]);
    else
        s = DftiCreateDescriptor(&mkl_plan->desc, DFTI_SINGLE, DFTI_COMPLEX,
                                 (MKL_LONG)rank, periods);
    if (BAD(s))
        goto broken;

    if (flags & FFTW_CONSERVE_MEMORY)
    {
        s = DftiSetValue(mkl_plan->desc, DFTI_WORKSPACE, DFTI_AVOID);
        if (BAD(s))
            goto broken;
    }

    s = DftiSetValue(mkl_plan->desc, DFTI_INPUT_STRIDES, istrides);
    if (BAD(s))
        goto broken;

    if (in == out)
    {
        mkl_plan->io[0] = in;
        mkl_plan->execute = (sign == FFTW_FORWARD) ? execute_fi : execute_bi;

        /* check if in-place has valid strides */
        for (i = 0; i < rank; ++i)
        {
            if (dims[i].is != dims[i].os)
                goto broken;
        }
        for (i = 0; i < howmany_rank; ++i)
        {
            if (howmany_dims[i].is != howmany_dims[i].os)
                goto broken;
        }
    }
    else
    {
        mkl_plan->io[0] = in;
        mkl_plan->io[1] = out;
        mkl_plan->execute = (sign == FFTW_FORWARD) ? execute_fo : execute_bo;

        s = DftiSetValue(mkl_plan->desc, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
        if (BAD(s))
            goto broken;

        s = DftiSetValue(mkl_plan->desc, DFTI_OUTPUT_STRIDES, ostrides);
        if (BAD(s))
            goto broken;
    }

    if (howmany_rank == 1)
    {
        MKL_LONG howmany = (MKL_LONG)howmany_dims[0].n;
        MKL_LONG idistance = (MKL_LONG)howmany_dims[0].is;
        MKL_LONG odistance = (MKL_LONG)howmany_dims[0].os;

        /* check if MKL_LONG is sufficient to hold dims */
        if (howmany != howmany_dims[0].n)
            goto broken;
        if (idistance != howmany_dims[0].is)
            goto broken;
        if (odistance != howmany_dims[0].os)
            goto broken;

        s = DftiSetValue(mkl_plan->desc, DFTI_NUMBER_OF_TRANSFORMS, howmany);
        if (BAD(s))
            goto broken;

        s = DftiSetValue(mkl_plan->desc, DFTI_INPUT_DISTANCE, idistance);
        if (BAD(s))
            goto broken;

        s = DftiSetValue(mkl_plan->desc, DFTI_OUTPUT_DISTANCE, odistance);
        if (BAD(s))
            goto broken;
    }

    if (fftw3_mkl.nthreads >= 0)
    {
        s = DftiSetValue(mkl_plan->desc, DFTI_THREAD_LIMIT,
                         (MKL_LONG)fftw3_mkl.nthreads);
        if (BAD(s))
            goto broken;
    }

    s = DftiCommitDescriptor(mkl_plan->desc);
    if (BAD(s))
        goto broken;

    return (fftwf_plan)mkl_plan;

  broken:
    /* possibly report the reason before returning NULL */
    mkl_plan->destroy(mkl_plan);
    return NULL;
}

static void
execute_fi(fftw_mkl_plan p)
{
    DftiComputeForward(p->desc, p->io[0]);
}

static void
execute_bi(fftw_mkl_plan p)
{
    DftiComputeBackward(p->desc, p->io[0]);
}

static void
execute_fo(fftw_mkl_plan p)
{
    DftiComputeForward(p->desc, p->io[0], p->io[1]);
}

static void
execute_bo(fftw_mkl_plan p)
{
    DftiComputeBackward(p->desc, p->io[0], p->io[1]);
}
