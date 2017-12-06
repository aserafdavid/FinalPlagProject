!===============================================================================
! Copyright 2010-2017 Intel Corporation All Rights Reserved.
!
! The source code,  information  and material  ("Material") contained  herein is
! owned by Intel Corporation or its  suppliers or licensors,  and  title to such
! Material remains with Intel  Corporation or its  suppliers or  licensors.  The
! Material  contains  proprietary  information  of  Intel or  its suppliers  and
! licensors.  The Material is protected by  worldwide copyright  laws and treaty
! provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
! modified, published,  uploaded, posted, transmitted,  distributed or disclosed
! in any way without Intel's prior express written permission.  No license under
! any patent,  copyright or other  intellectual property rights  in the Material
! is granted to  or  conferred  upon  you,  either   expressly,  by implication,
! inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
! property rights must be express and approved by Intel in writing.
!
! Unless otherwise agreed by Intel in writing,  you may not remove or alter this
! notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
! suppliers or licensors in any way.
!===============================================================================

!  Content:
!   Intel(R) Math Kernel Library (Intel(R) MKL) FORTRAN 95 interface for service routines
!*******************************************************************************

MODULE MKL_SERVICE

    IMPLICIT NONE

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DOMAIN_ALL  = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DOMAIN_BLAS = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DOMAIN_FFT  = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DOMAIN_VML  = 3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DOMAIN_PARDISO = 4

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DYNAMIC_TRUE  = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_DYNAMIC_FALSE = 0

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_SSE4_2        = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_AVX           = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_AVX2          = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_AVX512_MIC    = 3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_AVX512        = 4
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_ENABLE_AVX512_MIC_E1 = 5

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_INTERFACE_LP64  = Z"00000000"
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_INTERFACE_ILP64 = Z"00000001"
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_INTERFACE_GNU   = Z"00000002"
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_THREADING_INTEL = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_THREADING_SEQUENTIAL = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_THREADING_PGI = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_THREADING_GNU = 3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_THREADING_TBB = 4

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_BRANCH         = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ALL            = -1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_OFF            = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_UNSET_ALL      = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_BRANCH_OFF     = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AUTO           = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_COMPATIBLE     = 3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SSE2           = 4
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SSSE3          = 6
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SSE4_1         = 7
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SSE4_2         = 8
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AVX            = 9
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AVX2           = 10
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AVX512_MIC     = 11
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AVX512         = 12
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_AVX512_MIC_E1  = 13

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SUCCESS                 =  0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ERR_INVALID_SETTINGS    = -1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ERR_INVALID_INPUT       = -2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ERR_UNSUPPORTED_BRANCH  = -3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ERR_UNKNOWN_BRANCH      = -4
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_ERR_MODE_CHANGE_FAILURE = -8

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_PEAK_MEM_DISABLE        =  0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_PEAK_MEM_ENABLE         =  1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_PEAK_MEM_RESET          = -1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_PEAK_MEM                =  2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MEM_MCDRAM              =  1

    INTERFACE
      SUBROUTINE MKL_GET_VERSION_STRING(BUF)
      CHARACTER*(*), INTENT(OUT) :: BUF
      END
    END INTERFACE

    INTERFACE
      DOUBLE PRECISION FUNCTION MKL_GET_CPU_FREQUENCY()
      END
    END INTERFACE

    INTERFACE
      DOUBLE PRECISION FUNCTION MKL_GET_MAX_CPU_FREQUENCY()
      END
    END INTERFACE

    INTERFACE
      DOUBLE PRECISION FUNCTION MKL_GET_CLOCKS_FREQUENCY()
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_GET_CPU_CLOCKS(CPU_CLOCKS)
      INTEGER(8), INTENT(OUT) ::  CPU_CLOCKS
      END
    END INTERFACE

! Threading control functions

    INTERFACE
      INTEGER(4) FUNCTION MKL_GET_MAX_THREADS()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_GET_NUM_STRIPES()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_DOMAIN_GET_MAX_THREADS(DOMAIN)
      INTEGER(4), INTENT(IN) :: DOMAIN
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION  MKL_SET_NUM_THREADS_LOCAL(NTHRS)
      INTEGER(4), INTENT(IN) :: NTHRS
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_SET_NUM_THREADS(NTHRS)
      INTEGER(4), INTENT(IN) :: NTHRS
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_SET_NUM_STRIPES(NSTRP)
      INTEGER(4), INTENT(IN) :: NSTRP
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_DOMAIN_SET_NUM_THREADS(NTHRS,DOMAIN)
      INTEGER(4), INTENT(IN) :: NTHRS
      INTEGER(4), INTENT(IN) :: DOMAIN
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_GET_DYNAMIC()
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_SET_DYNAMIC(MKL_DYNAMIC)
      INTEGER(4), INTENT(IN) :: MKL_DYNAMIC
      END
    END INTERFACE

! Intel(R) MKL Memory functions

    INTERFACE
      FUNCTION MKL_MALLOC(SIZE,ALIGN)
      USE ISO_C_BINDING
      INTEGER(KIND=C_INTPTR_T) MKL_MALLOC
      INTEGER(KIND=C_SIZE_T)   SIZE
      INTEGER(4) ALIGN
      END FUNCTION MKL_MALLOC
    END INTERFACE

    INTERFACE
      FUNCTION MKL_CALLOC(NUM,SIZE,ALIGN)
      USE ISO_C_BINDING
      INTEGER(KIND=C_INTPTR_T) MKL_CALLOC
      INTEGER(KIND=C_SIZE_T)   NUM,SIZE
      INTEGER(4) ALIGN
      END FUNCTION MKL_CALLOC
    END INTERFACE

    INTERFACE
      FUNCTION MKL_REALLOC(PTR,SIZE)
      USE ISO_C_BINDING
      INTEGER(KIND=C_INTPTR_T) MKL_REALLOC,PTR
      INTEGER(KIND=C_SIZE_T)   SIZE
      END FUNCTION MKL_REALLOC
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_FREE(PTR)
      USE ISO_C_BINDING
      INTEGER(KIND=C_INTPTR_T) PTR
      END SUBROUTINE MKL_FREE
    END INTERFACE

    INTERFACE
      INTEGER(8) FUNCTION MKL_MEM_STAT(N_BUFF)
      INTEGER(4), INTENT(OUT) :: N_BUFF
      END
    END INTERFACE

    INTERFACE
      INTEGER(8) FUNCTION MKL_PEAK_MEM_USAGE(RESET)
      INTEGER(4), INTENT(IN) :: RESET
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_FREE_BUFFERS()
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_THREAD_FREE_BUFFERS()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_DISABLE_FAST_MM()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_SET_MEMORY_LIMIT(MEM_TYPE,LIMIT)
      USE ISO_C_BINDING
      INTEGER(4), INTENT(IN) :: MEM_TYPE
      INTEGER(KIND=C_SIZE_T), INTENT(IN) :: LIMIT
      END
    END INTERFACE

! Intel(R) MKL Progress routine

    INTERFACE
      FUNCTION MKL_PROGRESS( THREAD, STEP, STAGE )
      INTEGER(4), INTENT(IN)    :: THREAD,STEP
      CHARACTER*(*), INTENT(IN) :: STAGE
      INTEGER          MKL_PROGRESS
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_ENABLE_INSTRUCTIONS(TYPE)
      INTEGER(4), INTENT(IN) :: TYPE
      END
    END INTERFACE

! Intel(R) MKL layer routines

    INTERFACE
      INTEGER(4) FUNCTION MKL_SET_INTERFACE_LAYER(MKL_INTERFACE)
      INTEGER(4), INTENT(IN) :: MKL_INTERFACE
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_SET_THREADING_LAYER(MKL_THREADING)
      INTEGER(4), INTENT(IN) :: MKL_THREADING
      END
    END INTERFACE

! Intel(R) MKL CBWR routines

    INTERFACE
      INTEGER(4) FUNCTION MKL_CBWR_GET(MKL_CBWR)
      INTEGER(4), INTENT(IN) :: MKL_CBWR
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_CBWR_SET(MKL_CBWR)
      INTEGER(4), INTENT(IN) :: MKL_CBWR
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_CBWR_GET_AUTO_BRANCH()
      END
    END INTERFACE

! Intel(R) MKL MIC service routines

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_TARGET_NONE = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_TARGET_HOST = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_TARGET_MIC  = 2

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_DEFAULT_TARGET_TYPE   = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_DEFAULT_TARGET_NUMBER = 0

    DOUBLE PRECISION, PARAMETER, PUBLIC :: MKL_MIC_AUTO_WORKDIVISION = -1.0
    DOUBLE PRECISION, PARAMETER, PUBLIC :: MKL_MPI_PPN = -1.0

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_ENABLE()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_DISABLE()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_DEVICE_COUNT()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_WORKDIVISION(TARGET_TYPE, TARGET_NUMBER, WD)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      DOUBLE PRECISION, INTENT(OUT) :: WD
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_WORKDIVISION(TARGET_TYPE, TARGET_NUMBER, WD)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      DOUBLE PRECISION, INTENT(IN)  :: WD
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_MAX_MEMORY(TARGET_TYPE, TARGET_NUMBER, MEM)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      INTEGER(8),       INTENT(IN)  :: MEM
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_FREE_MEMORY(TARGET_TYPE, TARGET_NUMBER)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_OFFLOAD_REPORT(ENABLED)
      INTEGER(4),       INTENT(IN)  :: ENABLED
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_DEVICE_NUM_THREADS(TARGET_TYPE, TARGET_NUMBER, NUM_THREADS)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER, NUM_THREADS
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_RESOURCE_LIMIT(FRACTION)
      DOUBLE PRECISION, INTENT(OUT) :: FRACTION
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_RESOURCE_LIMIT(FRACTION)
      DOUBLE PRECISION, INTENT(IN)  :: FRACTION
      END
    END INTERFACE

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_DEFAULT_FLAGS = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_DISABLE_HOST_FALLBACK  = 1

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_FLAGS()
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_SET_FLAGS(FLAG)
      INTEGER(4), INTENT(IN)  :: FLAG
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_MEMINFO(TARGET_TYPE, TARGET_NUMBER, TOTALMEM, FREEMEM)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      INTEGER(4),       INTENT(OUT) :: TOTALMEM
      INTEGER(4),       INTENT(OUT) :: FREEMEM
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_CPUINFO(TARGET_TYPE, TARGET_NUMBER, NCORES, NTHREADS, FREQ)
      INTEGER(4),       INTENT(IN)  :: TARGET_TYPE, TARGET_NUMBER
      INTEGER(4),       INTENT(OUT) :: NCORES
      INTEGER(4),       INTENT(OUT) :: NTHREADS
      DOUBLE PRECISION, INTENT(OUT) :: FREQ
      END
    END INTERFACE

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_SUCCESS           = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_NOT_IMPL          = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_HOST_FALLBACK     = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_DISABLED          = 3
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_FAILED            = -1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_HOST_FALLBACK_DISABLED = -2

    INTERFACE
      INTEGER(4) FUNCTION MKL_MIC_GET_STATUS()
      END
    END INTERFACE

    INTERFACE
      SUBROUTINE MKL_MIC_CLEAR_STATUS()
      END
    END INTERFACE

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_REGISTRATION_DISABLE = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_MIC_REGISTRATION_ENABLE  = 1

    INTERFACE
      SUBROUTINE MKL_MIC_REGISTER_MEMORY(ENABLE)
      INTEGER(4),        INTENT(IN) :: ENABLE
      END SUBROUTINE
    END INTERFACE

    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_BLACS_CUSTOM = 0
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_BLACS_MSMPI = 1
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_BLACS_INTELMPI = 2
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_BLACS_MPICH2 = 3

    INTERFACE
      INTEGER(4) FUNCTION MKL_SET_MPI(VENDOR, CUSTOM_LIBRARY_NAME)
      INTEGER(4), INTENT(IN) :: VENDOR
      CHARACTER*(*) :: CUSTOM_LIBRARY_NAME
      END
    END INTERFACE

! Intel(R) MKL verbose function

    INTERFACE
      INTEGER(4) FUNCTION MKL_VERBOSE(ENABLE)
      INTEGER(4), INTENT(IN) :: ENABLE
      END
    END INTERFACE

    INTERFACE
      INTEGER(4) FUNCTION MKL_SET_ENV_MODE(MODE)
      INTEGER(4), INTENT(IN) :: MODE
      END
    END INTERFACE

! Obsolete names and routines
    INTEGER (KIND=4), PARAMETER, PUBLIC :: MKL_CBWR_SSE3           = 5

!*******************************************************************************

END MODULE MKL_SERVICE
