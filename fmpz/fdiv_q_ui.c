/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2009 William Hart
    
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

void fmpz_fdiv_q_ui(fmpz_t f, const fmpz_t g, ulong h)
{
    fmpz c1  = *g;
    ulong c2 =  h;
    
    if (h == 0)
    {
        printf("Exception: division by zero in fmpz_fdiv_q_ui\n");
        abort();
    }

    if (!COEFF_IS_MPZ(c1)) // g is small
    {
        fmpz q = c1 / c2; // compute C quotient
        fmpz r = c1 - c2*q; // compute remainder
    
        if (r < 0L) q--; // q cannot overflow as remainder implies |c2| != 1
    
        fmpz_set_si(f, q);
    }
    else // g is large
    {   
        __mpz_struct * mpz_ptr = _fmpz_promote(f);
        
        mpz_fdiv_q_ui(mpz_ptr, COEFF_TO_PTR(c1), c2);
        _fmpz_demote_val(f); // division by h may result in small value		
    }
}

