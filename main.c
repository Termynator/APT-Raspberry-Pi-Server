

/////////////////////////////////////////////
//          SPA TESTER for SPA.C           //
//                                         //
//      Solar Position Algorithm (SPA)     //
//                   for                   //
//        Solar Radiation Application      //
//                                         //
//             August 12, 2004             //
//                                         //
//   Filename: SPA_TESTER.C                //
//                                         //
//   Afshin Michael Andreas                //
//   afshin_andreas@nrel.gov (303)384-6383 //
//                                         //
//   Measurement & Instrumentation Team    //
//   Solar Radiation Research Laboratory   //
//   National Renewable Energy Laboratory  //
//   1617 Cole Blvd, Golden, CO 80401      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// This sample program shows how to use    //
//    the SPA.C code.                      //
/////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "spa.h"  //include the SPA header file

void help(void) {
    printf("Usage: spa ");
    printf("<year> ");
    printf("<month> ");
    printf("<day> ");
    printf("<hour> ");
    printf("<minute> ");
    printf("<second> ");
    printf("<timezone> ");
    printf("<delta_t> ");
    printf("<longitude> ");
    printf("<latitude> ");
    printf("<elevation> ");
    printf("<pressure> ");
    printf("<temperature> ");
    printf("<slope> ");
    printf("<azm_rotation> ");
    printf("<atmos_refract> ");
    // printf("<function> ");
    printf("\n");
}

int main (int argc, char *argv[])
{
    if (argc != 17) {
        help();
        return(1);
    }

    spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

    //enter required input values into SPA structure

    spa.year          = atoi(argv[1]);
    spa.month         = atoi(argv[2]);
    spa.day           = atoi(argv[3]);
    spa.hour          = atoi(argv[4]);
    spa.minute        = atoi(argv[5]);
    spa.second        = atoi(argv[6]);
    spa.timezone      = atof(argv[7]);
    spa.delta_t       = atof(argv[8]);
    spa.longitude     = atof(argv[9]);
    spa.latitude      = atof(argv[10]);
    spa.elevation     = atof(argv[11]);
    spa.pressure      = atof(argv[12]);
    spa.temperature   = atof(argv[13]);
    spa.slope         = atof(argv[14]);
    spa.azm_rotation  = atof(argv[15]);
    spa.atmos_refract = atof(argv[16]);
    spa.function      = SPA_ZA_INC;

    //call the SPA calculate function and pass the SPA structure

    result = spa_calculate(&spa);

    if (result == 0)  //check for SPA errors
    {
        printf("Zenith:        %.6f degrees\n",spa.zenith);
        printf("Azimuth:       %.6f degrees\n",spa.azimuth);
        printf("Incidence:     %.6f degrees\n",spa.incidence);
    } else printf("SPA Error Code: %d\n", result);

    return 0;
}

/////////////////////////////////////////////
// The output of this program should be:
//
//Julian Day:    2452930.312847
//L:             2.401826e+01 degrees
//B:             -1.011219e-04 degrees
//R:             0.996542 AU
//H:             11.105902 degrees
//Delta Psi:     -3.998404e-03 degrees
//Delta Epsilon: 1.666568e-03 degrees
//Epsilon:       23.440465 degrees
//Zenith:        50.111622 degrees
//Azimuth:       194.340241 degrees
//Incidence:     25.187000 degrees
//Sunrise:       06:12:43 Local Time
//Sunset:        17:20:19 Local Time
//
/////////////////////////////////////////////

