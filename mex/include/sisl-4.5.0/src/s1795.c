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
 * $Id: s1795.c,v 1.2 2001-03-19 15:58:54 afr Exp $
 *
 */


#define S1795

#include "sislP.h"

#if defined(SISLNEEDPROTOTYPES)
void
     s1795(SISLSurf *ps1,SISLSurf *ps2,double aepsge,double aang,int *jstat)
#else
void s1795(ps1,ps2,aepsge,aang,jstat)
     SISLSurf   *ps1;
     SISLSurf   *ps2;
     double aepsge;
     double aang;
     int    *jstat;
#endif
/*
*********************************************************************
*
*********************************************************************
*                                                                   
* PURPOSE    : To make the orientation surface on the unit sphere to
*	       a b-spline surface, the surface is representated with
*	       a surrounding cone piced from the unit sphere.
*
*
*
* INPUT      : ps1,ps2  - The B-spline surfaces.
*              aang     - The angel beetween the center axes
*                         in the direction cones.
*              aepsge -   Geometry resolution.
*
*
* OUTPUT     : jstat  - status messages  
*                                         = 1      : Simpel case
*                                         = 0      : No simpel case
*                                         < 0      : error
*
*
* METHOD     : We are making a cone surrounding the orientating surface
*	       on the unit sphere. The cone is representated with senter
*	       coordinates and an angle. The orientation is computed
*	       from aproximation of the normal to the surface.
*
*
* REFERENCES :
*
*-
* CALLS      :
*
* WRITTEN BY : Arne Laksaa, SI, 89-01.
*
*********************************************************************
*/
{
  int kpos = 0;     /* Position of the error.                             */
  int kstat;        /* Local status variable.                             */
  int ki;           /* Counter.                                           */
  int kn1;          /* Number of vertices of surface in 1. par. direction.*/
  int kn2;          /* Number of vertices of surface in 2. par. direction.*/
  int kdim;	   /* Dimension of the space in which the objects lie.   */
  int kdim4;	   /* Help variable to contain  4*kdim.			 */
  int kver,khor;    /* The index to the vertice in the upper left corner 
		       to the patch to treat.				 */
  int k1,k2,k3,k4;  /* Control variables in loop. 			 */
  double *t=SISL_NULL;     /* Allocating t[5][kdim]. Five tangents around the
			 patch, the first and the last is the same.         */
  double *tn;         /* Allocating tn[4][kdim]. Four normals in the corner
		         of the patch.					 */
  double *scen1;     /* The orginal basis vector to the projection plan. */
  double *scen2;     /* The computed basis vector to the projection plan.*/
  double tlen;       /* The length of a vector.				 */
  double tang;	     /* An angle between two vectors.			 */
  double tang1=DZERO;/* An angle between two vectors.			 */
  double tang2=DZERO;/* An angle between two vectors.			 */
  double t1,t2;      /* Help variables.					 */
  double slen[5];   /* Distances between coefficients.                    */
  double scorn[4];  /* Angle between derivatives in corner of patch.      */
  
  
  /* Initialate dimentions. */
  
  kdim = ps1 -> idim;
  kdim4 = 4*kdim;
  
  
  /* Allocate local used matrices, t[5][kdim] and tn[4][kdim]. */
  
  if ((t = newarray(10*kdim,double)) == SISL_NULL) goto err101;
  
  tn   = t + 5*kdim;
  
  
  if (aang > PIHALF)
    aang = PI - aang;
  
  scen1 = ps1->pdir->ecoef;
  scen2 = tn + 4*kdim;
  tlen = s6scpr(scen1,ps2->pdir->ecoef,kdim);
  for (k1=0; k1 < kdim; k1++)
    scen2[k1] = ps2->pdir->ecoef[k1] - tlen*scen1[k1];
  tlen = s6length(scen2,kdim,&kstat);
  for (k1=0; k1 < kdim; k1++)
    scen2[k1] /= tlen;
  
  kn1  = ps1 -> in1;
  kn2  = ps1 -> in2;
  
  /* Here we are treating each patch in the control polygon separately.*/
  
  for (kver=0; kver < (kn2-1); kver++)
    for (khor=0; khor < (kn1-1); khor++)
      {
	slen[0] = slen[1] = slen[2] = slen[3] = DZERO;
	scorn[0] = scorn[1] = scorn[2] = scorn[3] = DZERO;
	
	/* Here we make the tangents in each corner of the patch,
           and in direction with the clock. The first and the last
	   vector contains both the first tangent. */
	
	k2 = (kver*kn1+khor)*kdim;
	
	for (k1=0; k1 < kdim; k1++,k2++)
	  {
	    t[kdim+k1]   = ps1->pdir->esmooth[k2+kdim] - ps1->pdir->esmooth[k2];
	    t[2*kdim+k1] = ps1->pdir->esmooth[k2+(kn1+1)*kdim]-ps1->pdir->esmooth[k2+kdim];
	    t[3*kdim+k1] = ps1->pdir->esmooth[k2+kn1*kdim]-ps1->pdir->esmooth[k2+(kn1+1)*kdim];
	    t[kdim4+k1] = t[k1] = ps1->pdir->esmooth[k2]-ps1->pdir->esmooth[k2+kn1*kdim];
	    
	    slen[0] += t[k1]*t[k1];
	    slen[1] += t[k1+kdim]*t[k1+kdim];
	    slen[2] += t[k1+2*kdim]*t[k1+2*kdim];
	    slen[3] += t[k1+3*kdim]*t[k1+3*kdim];
	  }
	slen[4] = slen[0] = sqrt(slen[0]);
	slen[1] = sqrt(slen[1]);
	slen[2] = sqrt(slen[2]);
	slen[3] = sqrt(slen[3]);
	
	scorn[0] = s6ang(t,t+kdim,kdim);
	scorn[1] = s6ang(t+kdim,t+2*kdim,kdim);
	scorn[2] = s6ang(t+2*kdim,t+3*kdim,kdim);
	scorn[3] = s6ang(t+3*kdim,t,kdim);

	
	/* Here we makes the normales in each corner of the patch.
	   We are using a cross product between two tangents.
	   The normals is also normalized by deviding with its
	   own length. */
	
	
	for (k1=0, ki=0; k1<kdim4; k1+=kdim, ki++)
	  {
	    
	    for (tlen=DZERO,k2=0,k3=1,k4=2; k2 < kdim; k2++,k3++,k4++)
	      {
		
		if(k3 == kdim) k3 = 0;
		if(k4 == kdim) k4 = 0;
		tn[k1+k2] = t[k1+k3]*t[k1+kdim+k4]-t[k1+k4]*t[k1+kdim+k3];
		
		tlen += tn[k1+k2]*tn[k1+k2];
	      }
	    
	    tlen = sqrt(tlen);
	    if (slen[ki]>aepsge && slen[ki+1]>aepsge &&
		scorn[ki] > ANGULAR_TOLERANCE)
	      for (k2=0; k2 < kdim; k2++) tn[k1+k2] /= tlen;
	    else 
	      for (k2=0; k2 < kdim; k2++) tn[k1+k2] = scen1[k2];
	    
	  }
	
	for (k1=0; k1<kdim4; k1+=kdim)
	  {
	    t2 = scen2[0]*tn[k1];
	    for (k2=1,k3=k1+1;k2<kdim;k2++,k3++)
	      t2 += scen2[k2]*tn[k3];
	    
	    if (t2 <= DZERO) continue;
	    
	    t1 = scen1[0]*tn[k1];
	    for (k2=1,k3=k1+1;k2<kdim;k2++,k3++)
	      t1 += scen1[k2]*tn[k3];
	    
	    tang = t1/sqrt(t1*t1 + t2*t2);
	    
	    if (tang >= DZERO) tang = min((double)1,tang);
	    else               tang = max((double)-1,tang);
	    
	    tang = acos(tang);
	    
	    tang1 = max(tang1,tang);
	  }
      }			
  
  scen1 = ps2 ->pdir-> ecoef;
  tlen = s6scpr(scen1,ps1->pdir->ecoef,kdim);
  for (k1=0; k1 < kdim; k1++)
    scen2[k1] = ps1->pdir->ecoef[k1] - tlen*scen1[k1];
  tlen = s6length(scen2,kdim,&kstat);
  for (k1=0; k1 < kdim; k1++)
    scen2[k1] /= tlen;
  
  kn1  = ps2 -> in1;
  kn2  = ps2 -> in2;
  
  /* Here we are treating each patch in the control polygon separately.*/
  
  for (kver=0; kver < (kn2-1); kver++)
    for (khor=0; khor < (kn1-1); khor++)
      {
	slen[0] = slen[1] = slen[2] = slen[3] = DZERO;
	scorn[0] = scorn[1] = scorn[2] = scorn[3] = DZERO;
	
	/* Here we make the tangents in each corner of the patch,
           and in direction with the clock. The first and the last
	   vector contains both the first tangent. */
	
	k2 = (kver*kn1+khor)*kdim;
	
	for (k1=0; k1 < kdim; k1++,k2++)
	  {
	    t[kdim+k1]   = ps2->pdir->esmooth[k2+kdim] - ps2->pdir->esmooth[k2];
	    t[2*kdim+k1] = ps2->pdir->esmooth[k2+(kn1+1)*kdim]-ps2->pdir->esmooth[k2+kdim];
	    t[3*kdim+k1] = ps2->pdir->esmooth[k2+kn1*kdim]-ps2->pdir->esmooth[k2+(kn1+1)*kdim];
	    t[kdim4+k1] = t[k1] = ps2->pdir->esmooth[k2]-ps2->pdir->esmooth[k2+kn1*kdim];
	    
	    slen[0] += t[k1]*t[k1];
	    slen[1] += t[k1+kdim]*t[k1+kdim];
	    slen[2] += t[k1+2*kdim]*t[k1+2*kdim];
	    slen[3] += t[k1+3*kdim]*t[k1+3*kdim];
	  }
	slen[4] = slen[0] = sqrt(slen[0]);
	slen[1] = sqrt(slen[1]);
	slen[2] = sqrt(slen[2]);
	slen[3] = sqrt(slen[3]);
	
	scorn[0] = s6ang(t,t+kdim,kdim);
	scorn[1] = s6ang(t+kdim,t+2*kdim,kdim);
	scorn[2] = s6ang(t+2*kdim,t+3*kdim,kdim);
	scorn[3] = s6ang(t+3*kdim,t,kdim);

	
	/* Here we makes the normales in each corner of the patch.
	   We are using a cross product between two tangents.
	   The normals is also normalized by deviding with its
	   own length. */
	
	
	for (k1=0, ki=0; k1<kdim4; k1+=kdim, ki++)
	  {
	    
	    for (tlen=DZERO,k2=0,k3=1,k4=2; k2 < kdim; k2++,k3++,k4++)
	      {
		
		if(k3 == kdim) k3 = 0;
		if(k4 == kdim) k4 = 0;
		tn[k1+k2] = t[k1+k3]*t[k1+kdim+k4]-t[k1+k4]*t[k1+kdim+k3];
		
		tlen += tn[k1+k2]*tn[k1+k2];
	      }
	    
	    tlen = sqrt(tlen);
	    if (slen[ki]>aepsge && slen[ki+1]>aepsge &&
		scorn[ki] > ANGULAR_TOLERANCE)
	      for (k2=0; k2 < kdim; k2++) tn[k1+k2] /= tlen;
	    else 
	      for (k2=0; k2 < kdim; k2++) tn[k1+k2] = scen1[k2];
	    
	  }
	
	
	for (k1=0; k1<kdim4; k1+=kdim)
	  {
	    t2 = scen2[0]*tn[k1];
	    for (k2=1,k3=k1+1;k2<kdim;k2++,k3++)
	      t2 += scen2[k2]*tn[k3];
	    
	    if (t2 <= DZERO) continue;
	    
	    t1 = scen1[0]*tn[k1];
	    for (k2=1,k3=k1+1;k2<kdim;k2++,k3++)
	      t1 += scen1[k2]*tn[k3];
	    
	    tang = t1/sqrt(t1*t1+t2*t2);
	    
	    if (tang >= DZERO) tang = min((double)1,tang);
	    else               tang = max((double)-1,tang);
	    
	    tang = acos(tang);
	    
	    tang2 = max(tang2,tang);
	  }
      }			
  
  
  /* Performing a simple case check. */
  
  if (tang1 + tang2 <= aang)
    *jstat = 1;       /* A simpel case.*/
  else
    *jstat = 0;
  
  goto out;
  
  
  /* Error in space allacation.  */
  
  err101: *jstat = -101;
  s6err("s1795",*jstat,kpos);
  goto out;
  
  
  
  /* Free local used memory. */
  
  out:    if (t != SISL_NULL) freearray(t);
}
