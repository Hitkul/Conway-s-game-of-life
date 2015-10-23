#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

int canvas[200][200];
int trigger=1;

using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{     int adjust_x,adjust_y;
     if  ( event == EVENT_LBUTTONDOWN )
     {
		adjust_y=y%4;
	adjust_x=x%4;
	  canvas[(x-adjust_x)/4][(y-adjust_y)/4]=1;  
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
	//  cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
	  trigger=0;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
	  adjust_y=y%4;
	  adjust_x=x%4;
	  canvas[(x-adjust_x)/4][(y-adjust_y)/4]=1;
      }
}


int main(int argc, char** argv)
{
     // Read image from file 
    Mat img1 = imread("1.jpg",1),img;
    int life_status[200][200],i,j,k,l,count[2]={0,0};
    for (i = 0; i < 200; ++i)
    {
      for ( j = 0; j < 200; ++j)
      {
	life_status[i][j]=0;
	canvas[i][j]=0;
      }
    }

      //if fail to read the image
     if ( img1.empty() ) 
     { 
	  cout << "Error loading the image" << endl;
	  return -1;
     }
     
     
     Size size(800,800);
     resize(img1, img,size);
      //Create a window
      int check;
     namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", img);
	check= waitKey(0);
      setMouseCallback("My Window", CallBackFunc, NULL); 
      while(check)
      {
	
	  for (i = 0; i < 200; ++i)
	  {
	    for (j = 0; j < 200; ++j)
	    {
	      if(canvas[i][j]==0){
		for (k = 4*i; k < 4*i+4; ++k)
		{
		  for (l = 4*j; l < 4*j+4; ++l)
		  {
		      img.at<cv::Vec3b>(l,k)[0] =255;
		      img.at<cv::Vec3b>(l,k)[1] =255;
		      img.at<cv::Vec3b>(l,k)[2] =255;
		  }
		}
	      }else{
		for (k = 4*i; k < 4*i+4; ++k)
		{
		  for (l = 4*j; l < 4*j+4; ++l)
		  {
		      img.at<cv::Vec3b>(l,k)[0] =0;
		      img.at<cv::Vec3b>(l,k)[1] =0;
		      img.at<cv::Vec3b>(l,k)[2] =255;
		  }
		}
	      }
	    }
	  }
	  imshow("My Window", img);
	  waitKey(1); 
	  check = trigger;
      }


      imshow("My Window", img);
      waitKey(1000);
     while(1){
	for (i = 0; i < 200; ++i)
	{ 
	 for (j = 0; j < 200; ++j)
	  {  
	      count[0]=0;count[1]=0;

	    if(canvas[i][j-1]==1)
		count[0]++;
	    else
		count[1]++;

	    if(canvas[i][j+1]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i+1][j]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i-1][j]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i-1][j-1]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i-1][j+1]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i+1][j+1]==1)
		count[0]++;
	    else
		count[1]++;
	    if(canvas[i+1][j-1]==1)
		count[0]++;
	    else
		count[1]++;
	  
	    if(count[0]<2 && canvas[i][j]==1){
		life_status[i][j]=0;
	      }

	    if((count[0]==2 || count[0]==3 )&& canvas[i][j]==1){
		life_status[i][j]=1;
			  }
	    if(count[0]>3 && canvas[i][j]==1){
		life_status[i][j]=0;
		
	      }
	    if(count[0]==3 &&canvas[i][j]==0){
		life_status[i][j]=1;
	      }
		     
	  }
	}
	
	 
	  for (i = 0; i < 200; ++i)
	  {
	    for (j = 0; j < 200; ++j)
	    {
	      if(life_status[i][j]==0){
		for (k = 4*i; k < 4*i+4; ++k)
		{
		  for (l = 4*j; l < 4*j+4; ++l)
		  {
		      img.at<cv::Vec3b>(l,k)[0] =255;
		      img.at<cv::Vec3b>(l,k)[1] =255;
		      img.at<cv::Vec3b>(l,k)[2] =255;
		  }
		}
		
	      }else{
		for (k = 4*i; k < 4*i+4; ++k)
		{
		  for (l = 4*j; l < 4*j+4; ++l)
		  {
		      img.at<cv::Vec3b>(l,k)[0] =0;
		      img.at<cv::Vec3b>(l,k)[1] =0;
		      img.at<cv::Vec3b>(l,k)[2] =255;
		  }
		}
	      }
	    }
	  }
	  

	      imshow("My Window", img);
	      waitKey(50);

	      for ( i = 0; i < 200; ++i)
	      {
		for ( j = 0; j < 200; ++j)
		{
		  canvas[i][j]=life_status[i][j];
		}
	      }
      }
      
  
      return 0;

}
