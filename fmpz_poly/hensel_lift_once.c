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

    Copyright (C) 2011 Andy Novocin
    Copyright (C) 2011 William Hart
    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include "flint.h"
#include "fmpz_poly.h"
#include "nmod_poly.h"

/*
    This function does a Hensel lift. 

    It lifts local factors (stored in \code{local_fac}) of $f$ to $p^N$. 
    The lifted factors will be stored in \code{lifted_fac}. This lift can't 
    be restarted. This function is a convenience function intended for end 
    users. The product of local factors must be squarefree.
 */
void fmpz_poly_hensel_lift_once(fmpz_poly_factor_t lifted_fac, fmpz_poly_t f, 
                                const nmod_poly_factor_t local_fac, long N)
{
    const long r = local_fac->num_factors;

    long i;
    long link[2*r - 2];
    fmpz_poly_t v[2*r - 2];
    fmpz_poly_t w[2*r - 2];

    for(i = 0; i < 2*r - 2; i++)
    {
        fmpz_poly_init(v[i]);
        fmpz_poly_init(w[i]);
    }

    _fmpz_poly_start_hensel_lift(lifted_fac, link, v, w, f, local_fac, N);

    for (i = 0; i < 2*r - 2; i++)
    {
        fmpz_poly_clear(v[i]);
        fmpz_poly_clear(w[i]);
    }
}
