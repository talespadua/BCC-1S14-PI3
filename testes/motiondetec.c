//#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <math.h>
#include <stdio.h>

int main()
{
	CvCapture *camera = 0;
	IplImage *frame = 0, *image = 0, *result = 0;
	int i, j, k, n = 0;
	char filename[256];
	char c;

	camera = cvCaptureFromCAM(CV_CAP_ANY);

	if (!camera)
	{
		fprintf(stderr, "Cant initialize camera\n");
		return -1;
	}

	cvNamedWindow("video", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("video", 150, 200);
	//image = cvQueryFrame(camera);
	for (i = 0; i < 6000; i++)
	{
		image = cvQueryFrame(camera);
		if (!image)
		{
			printf("Capture failed ");
		}
		else
		{
			if(n == 0)
			{
				frame = cvCloneImage(image);
				result = cvCloneImage(image);
				n = 1;
			}			
		}
		
		c = cvWaitKey(100);		
		
		if (c > 0)
			break;

		if(frame)
		{
			if (n != 0)
			{
				for (j = 0; j < frame->height; j++)
				{
					for (k = 0; k < frame->width; k++)
					{
						if (((uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 0] >((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 0] + 30) ||
							(uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 0] < ((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 0] - 30)) &&
							((uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 1] > ((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 1] + 30) ||
							(uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 1] < ((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 1] - 30)) &&
							((uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 2] > ((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 2] + 30) ||
							(uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 2] < ((uchar)(frame->imageData + j*frame->widthStep)[k*frame->nChannels + 2] - 30)))
						{
							(result->imageData + j*result->widthStep)[k*result->nChannels + 0] = (uchar)255;
							(result->imageData + j*result->widthStep)[k*result->nChannels + 1] = (uchar)255;
							(result->imageData + j*result->widthStep)[k*result->nChannels + 2] = (uchar)255;
						}
						else
						{
							(result->imageData + j*result->widthStep)[k*result->nChannels + 0] = (uchar)0;
							(result->imageData + j*result->widthStep)[k*result->nChannels + 1] = (uchar)0;
							(result->imageData + j*result->widthStep)[k*result->nChannels + 2] = (uchar)0;
						}
					}
				}
			}
			frame = cvCloneImage(image);
		}
		if(n!= 0)cvShowImage("video", result);
	}

	cvReleaseCapture(&camera);
	cvWaitKey(0);
	return 0;
}