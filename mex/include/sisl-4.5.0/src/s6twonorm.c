//===========================================================================
// SISL - SINTEF Spline Library, version 4.5.0.
// Definition and interrogation of NURBS curves and surfaces. 
//
// Copyright (C) 2000-2005, 2010 SINTEF ICT, Applied Mathematics, Norway.
//
// This program is free software; you can redistribute it and/or          
// modify it under the terms of the GNU General Public License            
// as published by the Free Software Foundation version 2 of the License. 
//
// This program is distributed in the hope that it will be useful,        
// but WITHOUT ANY WARRANTY; without even the implied warranty of         
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          
// GNU General Public License for more details.                           
//
// You should have received a copy of the GNU General Public License      
// along with this program; if not, write to the Free Software            
// Foundation, Inc.,                                                      
// 59 Temple Place - Suite 330,                                           
// Boston, MA  02111-1307, USA.                                           
//
// Contact information: E-mail: tor.dokken@sintef.no                      
// SINTEF ICT, Department of Applied Mathematics,                         
// P.O. Box 124 Blindern,                                                 
// 0314 Oslo, Norway.                                                     
//
// Other licenses are also available for this software, notably licenses
// for:
// - Building commercial software.                                        
// - Building software whose source code you wish to keep private.        
//===========================================================================

#include "sisl-copyright.h"

/*
 *
 * $Id: s6twonorm.c,v 1.1 1994-04-21 12:10:42 boh Exp $
 *
 */


#define S6TWONORM

#include "sislP.h"

#if defined(SISLNEEDPROTOTYPES)
void 
s6twonorm(double evec[],double enorm1[],double enorm2[],int *jstat)
#else
void s6twonorm(evec,enorm1,enorm2,jstat)
     double evec[];
     double enorm1[];
     double enorm2[];
     int    *jstat;
#endif
/*
*********************************************************************
*                                                                   
* PURPOSE    : To make two normal vectors of length 1 to the input
*              vector which should be 3-dimensional
*
* INPUT      : evec    - The input vector (3-D)
*
* OUTPUT     : enorm1  - First normal vector
*              enorm2  - Second normal vector
*                        enorm1 and enorm2 are normal to each other
*
*              jstat   - Status message
*                         0 - The length of the vector is zero
*                         1 - The length of the vector is one
*
*
* METHOD     : The length of the input vector is calulated, and the
*              output is assigned the values of the input vector and 
*              divided by the length.
*-
* CALLS      :
*
* WRITTEN BY : Tor Dokken, SI, Oslo, Norway. 1988-may-03
*                                  
*********************************************************************
*/
{
  int kstat;                 /* Local status variable                        */
  int kdim = 3;              /* We work in 3-D                               */
  int kpos=0;                /* Position of eror                             */
  double svec[3],sdum[3];    /* Local dummy arrays                           */
  double t1,t2,t3;           /* Absolute value of components of svec         */
  
  
  /* If the dimension is 1 the length of the vector is the same as the
     absolute value of the number */
  
  
  /* Normalize input vector */
  
  (void)s6norm(evec,kdim,svec,&kstat);
  
  if (kstat == 0) goto err174;
  
  t1 =fabs(svec[0]);
  t2 =fabs(svec[1]);
  t3 =fabs(svec[2]);
  
  /* Make along one of the main axis that has component 1 in the direction
     that svec has the smalles component */
  
  sdum[0] = (double)0.0;
  sdum[1] = (double)0.0;
  sdum[2] = (double)0.0;
  
  if (t1 < t2 && t1 < t3)
    {
      sdum[0] = (double)1.0;
    }
  else if (t2 < t3)
    {
      sdum[1] = (double)1.0;
    }
  else
    {
      sdum[2] = (double)1.0;
    }
  
  /* Make normal of sdum and svec */
  
  s6crss(svec,sdum,enorm1);
  
  /* Normalize enorm1 */
  
  (void)s6norm(enorm1,kdim,enorm1,&kstat);
  
  /* Make normal of enorm1 and svec */
  
  s6crss(svec,enorm1,enorm2);
  
  /* Normalize enorm2 */
  
  (void)s6norm(enorm2,kdim,enorm2,&kstat);
  
  *jstat = 0;
  goto out;

/* Direction vector of zero length */

err174: *jstat = -174;
        s6err("s6twonorm",*jstat,kpos);
goto out;
out:
return;
}
