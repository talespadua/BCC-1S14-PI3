//#include <opencv/cv.h>
#include <opencv2/highgui/highgui_c.h>
#include <stdio.h>

int main()
{
	CvCapture *camera = 0;
	IplImage *frame = 0, *image = 0;
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

	for (i = 0; i < 6000; i++)
	{
		image = cvQueryFrame(camera);
		if (!image)
		{
			printf("Capture failed ");
		}
		else
		{
			frame = cvCloneImage(image);
		}			
		
		c = cvWaitKey(100);
		if (c > 0)
			break;
		
		if (frame)
		{
			for (j = 0; j < frame->height; j++)
			{
				for (k = 0; k < frame->width; k++)
				{
					if ((uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 0] < 70 &&
						(uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 1] < 70 &&
						(uchar)(image->imageData + j*image->widthStep)[k*image->nChannels + 2] < 70)
					{
						if (k > 0 && k < frame->width - 1 && j > 0 && j < frame->height - 1)
						{
							for (int w = 0; w <= 2; w++)
							{
								(frame->imageData + (j - 1)*frame->widthStep)[(k + 1)*frame->nChannels + w] = (uchar)0;
								(frame->imageData + (j - 1)*frame->widthStep)[k*frame->nChannels + w] = (uchar)0;
								(frame->imageData + (j - 1)*frame->widthStep)[(k - 1)*frame->nChannels + w] = (uchar)0;
								(frame->imageData + j*frame->widthStep)[(k + 1)*frame->nChannels + w] = (uchar)0;
								(frame->imageData + j*frame->widthStep)[k*frame->nChannels + w] = (uchar)0;
								(frame->imageData + j*frame->widthStep)[(k - 1)*frame->nChannels + w] = (uchar)0;
								(frame->imageData + (j + 1)*frame->widthStep)[(k + 1)*frame->nChannels + w] = (uchar)0;
								(frame->imageData + (j + 1)*frame->widthStep)[k*frame->nChannels + w] = (uchar)0;
								(frame->imageData + (j + 1)*frame->widthStep)[(k - 1)*frame->nChannels + w] = (uchar)0;
							}
						}
					}
				}
			}
		}
		cvShowImage("video", frame);
	}

	cvReleaseCapture(&camera);
	cvWaitKey(0);
	return 0;
}