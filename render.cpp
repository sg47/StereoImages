// Skeleton code for B657 A4 Part 1.
// D. Crandall
//
// Rest of the program done by Manikandan Murugesan, Pradeep Ravilla, Sreekanth HS
// Code generates a stereo image from the given image and disparity map
//
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <CImg.h>
#include <assert.h>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    cerr << "usage: " << argv[0] << " image_file disp_file" << endl;
    return 1;
  }

  string input_filename1 = argv[1], input_filename2 = argv[2];

  // read in image
  CImg<double> image_rgb(input_filename1.c_str());

  // read in disparity image
  CImg<double> image_disp(input_filename2.c_str());

  CImg<double> image_result =image_rgb;
  CImg<double> image_right_stereo = image_rgb ;

  double constant_add_factor = 0;
  double constant_multiply_factor = 20;

  
  //creating left and right stereo images

  for(int i = 0; i < image_rgb.width() ; i++)
  {
    for(int j = 0 ; j < image_rgb.height() ; j++)
    {
      constant_add_factor = int(image_disp(i,j)/255 * constant_multiply_factor);

      for(k=0; k<3; k++)
      {
        image_right_stereo(i,j,0,k) = image_rgb(i + constant_add_factor , j,0,k)   ; 
      }
    }
  }

  image_right_stereo.save("right_stereo.png");


  for(double i = 0; i < image_rgb.width() ; i++)
  {
    for(double  j = 0 ; j < image_rgb.height() ; j++)
    {	
      for(k=0; k<3; k++)
      {
        image_result(i,j,0,k) = image_rgb(i,j,0,k);
      }
    }
  }


  image_result.get_normalize(0,255).save((input_filename1 + "-stereogram.png").c_str());

  image_result.save("result.png");
  
  return 0;
}
