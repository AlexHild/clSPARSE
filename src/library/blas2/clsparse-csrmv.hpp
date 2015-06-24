#pragma once
#ifndef _CLSPARSE_CSRMV_HPP_
#define _CLSPARSE_CSRMV_HPP_

#include "include/clSPARSE-private.hpp"
#include "internal/clsparse-control.hpp"
#include "blas2/csrmv-adaptive.hpp"
#include "blas2/csrmv-vector.hpp"
#include "internal/data-types/clvector.hpp"

template <typename T>
clsparseStatus
csrmv (const clsparseScalarPrivate *pAlpha,
       const clsparseCsrMatrixPrivate *pCsrMatx,
       const clsparseVectorPrivate *pX,
       const clsparseScalarPrivate *pBeta,
       clsparseVectorPrivate *pY,
       clsparseControl control)
{
   if( (pCsrMatx->rowBlocks == nullptr) && (pCsrMatx->rowBlockSize == 0) )
   {
        return csrmv_vector<T>(pAlpha, pCsrMatx, pX, pBeta, pY, control);
   }
   else
    {
       if( ( pCsrMatx->rowBlocks == nullptr ) || ( pCsrMatx->rowBlockSize == 0 ) )
       {
            // rowBlockSize varible is not zero but no pointer
            return clsparseStructInvalid;
       }

        // Call adaptive CSR kernels
        return csrmv_adaptive<T>( pAlpha, pCsrMatx, pX, pBeta, pY, control );
    }
}

/*
 * clsparse::array
 */

template <typename T>
clsparseStatus
csrmv (const clsparse::array_base<T>& pAlpha,
       const clsparseCsrMatrixPrivate *pCsrMatx,
       const clsparse::array_base<T>& pX,
       const clsparse::array_base<T>& pBeta,
       clsparse::array_base<T>& pY,
       clsparseControl control)
{

    if( (pCsrMatx->rowBlocks == nullptr) && (pCsrMatx->rowBlockSize == 0) )
    {
        return csrmv_vector<T>(pAlpha, pCsrMatx, pX, pBeta, pY, control);
    }
    else
    {
        if( ( pCsrMatx->rowBlocks == nullptr ) || ( pCsrMatx->rowBlockSize == 0 ) )
        {
            // rowBlockSize varible is not zero but no pointer
            return clsparseStructInvalid;
        }

        // Call adaptive CSR kernels
        return csrmv_adaptive<T>( pAlpha, pCsrMatx, pX, pBeta, pY, control );
    }

}

#endif
