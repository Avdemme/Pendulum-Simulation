#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

using namespace std;
double g=9.8; //[m/s^2]
double L = 2.; //[m]
double h=0.001; //[s]
double initial_theta[7] = { 15, 30, 45, 60, 90, 120, 179 };//[degrees]
double final_time=6.;//[s]
double initial_theta_dot=0.;
double initial_time=0.;


double damping_coefficient[2][2][7][4]= {{{{0,2,4.30,6},{0,2,4.30,6},{0,2,4.3,6},{0,2,4.31,6},{0,2,4.31,6},{0,2,4.31,6},{0,2,4.314,6}},{{0,2,4.285,8},{0,2,4.285,8},{0,2,4.2,8},{0,2,4.2,8},{0,2,4.2,8},{0,2,4.2,8},{0,2,4.15,8}}},{{{0,2,4.3,6},{0,2,4.31,6},{0,2,4.32,6},{0,2,4.35,6},{0,2,4.63,6},{0,2,6.032,10},{0,5,11.44353,20}},{{0,2,4.15,8},{0,2,4.15,8},{0,2,4.13,8},{0,2,4.13,8},{0,2,4.13,8},{0,2,4.13,8},{0,2,4.1,8}}}};
double damping;
//arrays for damping constants [1/s]
//[small angle approx vs true angle ], [driven vs non], [initial angle], [damping (none, under, critical, over)]

int main ( int argc, char** argv ) {

  ofstream damping_file;


  double theta[3][2], time[2];
  char buffer[80];
  int i=0;

  for (int m=0; m<2; m++)
    {
      for (int n=0; n<2; n++)
	{
	  for( int i=0; i<7; i++) 
	    {
     

	      theta[0][0] = initial_theta[i];
	      theta[1][0] = initial_theta_dot;
	      theta[0][0] *= (M_PI/180.);
	      theta[1][0] *= (M_PI/180.);
	      int j=0;
      
	      for ( int j=0; j<4 ; j++ )
		{
	 
	  

		  theta[0][0] = initial_theta[i];
		  theta[1][0] = initial_theta_dot;
		  theta[0][0] *= (M_PI/180.);
		  theta[1][0] *= (M_PI/180.);
	  
	  

		  
		  

		  for ( initial_time = 0.; initial_time < final_time ; initial_time += h ) {



		    double theta_inter;
		    double driving_force;
		    
		    if ( n==0 ) {	     
		      driving_force=0;
		    }
		    else if ( n==1 ) {
		      driving_force=sin(sqrt(g/L)*initial_time);
		    }

		    
                    //we are using the euler-cromer method of simulation so that
                    //we do not get weird results after long time periods.


		    theta[2][0] = -(g/L)*sin(theta[0][0]) - damping_coefficient[m][n][i][j]*theta[1][0] + driving_force;
		    theta[1][1] = theta[1][0] + h * theta[2][0];
		    theta[0][1] = sin(theta[0][0]) + h * theta[1][1];

		    sprintf(buffer,"%.0f", double (i));
		    string a(buffer);
		    sprintf(buffer,"%.0f", double (j));
		    string b(buffer);
		    sprintf(buffer,"%.0f", double (m));
		    string m_char(buffer);
		    sprintf(buffer,"%.0f", double (n));
		    string n_char(buffer);
		    string c = "damping_file";
		    
		    string adjusting_filename= c + m_char + "_" + n_char + "_" + a +"_" + b + ".txt";
		    

		    damping_file.open (adjusting_filename, ios::app);
		    damping_file << initial_time << "\t" << theta[0][0]*(180/M_PI) << endl;
		    damping_file.close();

	  

		    
		    
		    theta[0][0] = theta[0][1]; 
		    theta[1][0] = theta[1][1];

		  }
	   
		}
	    }
	}
    }
  return 0; 
}
