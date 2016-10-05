/* SISL - SINTEF Spline Library version 4.4.                              */
/* Definition and interrogation of NURBS curves and surface.              */
/* Copyright (C) 1978-2005, SINTEF ICT, Applied Mathematics, Norway.      */

/* This program is free software; you can redistribute it and/or          */
/* modify it under the terms of the GNU General Public License            */
/* as published by the Free Software Foundation version 2 of the License. */

/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */

/* You should have received a copy of the GNU General Public License      */
/* along with this program; if not, write to the Free Software            */
/* Foundation, Inc.,                                                      */
/* 59 Temple Place - Suite 330,                                           */
/* Boston, MA  02111-1307, USA.                                           */

/* Contact information: e-mail: tor.dokken@sintef.no                      */
/* SINTEF ICT, Department of Applied Mathematics,                         */
/* P.O. Box 124 Blindern,                                                 */
/* 0314 Oslo, Norway.                                                     */

/* SISL commercial licenses are available for:                            */
/* - Building commercial software.                                        */
/* - Building software whose source code you wish to keep private.        */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "sisl.h"
#include "GoReadWrite.h"

using namespace std;

namespace {
    string IN_FILE_CURVE = "example4_curve.g2";
    string IN_FILE_SURFACE = "example10_surf.g2";
    string OUT_FILE_POINT   = "example12_isectpoints.g2";

    string DESCRIPTION = 
    //==========================================================
    "This program computes all intersection points between a \n"
    "curve and a surface.  The curve and surface in question has \n"
    "been generated by earlier example programs (example4 and \n"
    "example10), so you should run these first.  The resulting \n"
    "points will be written to the file '" + OUT_FILE_POINT + "'.\n\n";
    //==========================================================

}; // end anonymous namespace 

//===========================================================================
int main(int avnum, char** vararg)
//===========================================================================
{
    cout << '\n' << vararg[0] << ":\n" << DESCRIPTION << endl;
    cout << "To proceed, press enter, or ^C to quit." << endl;
    getchar();

    try {
	ifstream is_cv(IN_FILE_CURVE.c_str());
	ifstream is_sf(IN_FILE_SURFACE.c_str());
	if (!is_cv || !is_sf) {
	    throw runtime_error("Could not open input files.  Have you run "
				"the necessary example programs? (example4 "
				"and example 10).");
	}
	ofstream os(OUT_FILE_POINT.c_str());
	if (!os) {
	    throw runtime_error("Unable to open output file.");
	}

	// reading curve and surface
	SISLCurve* curve = readGoCurve(is_cv);
	SISLSurf* surf = readGoSurface(is_sf);

	// calculating intersection points
	double epsco = 1.0e-15; // computational epsilon
	double epsge = 1.0e-5; // geometric tolerance
	int num_int_points = 0; // number of detected intersection points
	double* intpar_surf  = 0; // parameter values for the surface in the intersections
	double* intpar_curve = 0; // parameter values for the curve in the intersections
	int num_int_curves = 0;   // number of intersection curves
	SISLIntcurve** intcurve = 0; // pointer to array of detected intersection curves
	int jstat; // status variable

	s1858(surf,            // the surface
	      curve,           // the curve
	      epsco,           // computational resolution
	      epsge,           // geometry resolution
	      &num_int_points, // number of single intersection points
	      &intpar_surf,    // pointer to array of parameter values for the surface
	      &intpar_curve,   //               -"-                    for the curve
	      &num_int_curves, // number of detected intersection curves
	      &intcurve,       // pointer to array of detected intersection curves.
	      &jstat);         // status variable
	
	if (jstat < 0) {
	    throw runtime_error("Error occured inside call to SISL routine s1858.");
	} else if (jstat > 0) {
	    cerr << "WARNING: warning occured inside call to SISL routine s1858. \n" 
		     << endl;
	}

	// In this example, we do not expect to find intersection curves, since the 
	// assumed curve does not lie in the surface at any interval with measure > 0.

	cout << "Number of intersection points detected: " << num_int_points << endl;
	cout << "Number of intersection curves detected: " << num_int_curves << endl;
	
	// evaluating intersection points and writing them to file
	vector<double> point_coords_3D(3 * num_int_points);
	int i;
	for (i = 0; i < num_int_points; ++i) {
	    // calculating position, using the curve
	    // (we could also have used the surface, which would give approximately
	    // the same points).
	    int temp;
	    s1227(curve,           // we evaluate on the first curve
		  0,               // calculate no derivatives
		  intpar_curve[i], // parameter value on which to evaluate
		  &temp,           // not used for our purposes (gives parameter interval)
		  &point_coords_3D[3 * i], // result written here
		  &jstat);         // status variable
	    if (jstat < 0) {
		throw runtime_error("Error occured inside call to SISL routine s1227.");
	    } else if (jstat > 0) {
		cerr << "WARNING: warning occured inside call to SISL routine s1227. \n" 
		     << endl;
	    }
	}

	// writing intersection points to file
	writeGoPoints(num_int_points, &point_coords_3D[0], os);

	// cleaning up
	freeSurf(surf);
	freeCurve(curve);
	os.close();
	is_sf.close();
	is_cv.close();
	free(intpar_surf);
	free(intpar_curve);
	for (i = 0; i < num_int_curves; ++i) {
	    freeIntcurve(intcurve[i]);
	}
	free(intcurve);

    } catch (exception& e) {
	cerr << "Exception thrown: " << e.what() << endl;
	return 0;
    }

    return 1;
};
