#include "stdafx.h"

using namespace std;
using namespace cv;
Mat extract(int r, int b, int g, int delta) {
	//cv::Vec3b color = img->at<Vec3b>(Point(x, y));
	Mat image = imread("a1.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Source", WINDOW_NORMAL);
	imshow("Source", image);
	Vec3b blackColor = Vec3b(0, 0, 0);
	Vec3b whiteColor = Vec3b(255, 255, 255);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b color = image.at<Vec3b>(i, j);
			image.at<Vec3b>(i, j) = blackColor;

			if ((color.val[0] >= b - delta) && (color.val[0] <= b + delta)) {
				if ((color.val[1] >= g - delta) && (color.val[1] <= g + delta)) {
					if ((color.val[2] >= r - delta) && (color.val[2] <= r + delta)) {
						image.at<Vec3b>(i, j) = whiteColor;
					}
				}
			}
		}
	}

	return image;
}
/** @function extractColor_callback */
// void extractColor_callback(int,void*){
// 	Mat img=extract(0,0,0,colorDelta);
// 	namedWindow("Extract color", WINDOW_NORMAL);
// 	imshow("Extract color", img);
// //	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
// //	imshow("Contours", img);
// 	createTrackbar(" Canny thresh:", "Extract color", &thresh, max_thresh, thresh_callback);
// 	thresh_callback(0, 0);
// }
Mat canny_output;
Mat src, src_gray, edges;

int cannyThresh = 100;
int maxCannyThresh = 255;

int maxSizeThresh = 500;
int minContourSize = 0;
int maxContourSize = maxSizeThresh;

int thresh = 127;
int maxThresh = 255;

int lineThresh = 20;

RNG rng(12345);
int colorDelta = 100;

/// Function header
void trackbars_callback(int, void*);
void Probabilistic_Hough(int, void*);
// void extractColor_callback(int,void*);
/** @function main */
int main()
{

	// Khai báo một đối tượng Mat để lưu giữ hình ảnh được đọc vào
	// src: đối tượng kiểu Mat
	// imread: hàm đọc dữ liệu từ file, trả về kiểu Mat
	// imread(Tên_file, kiểu dữ liệu nhập vào)
	// Ở đây mình dùng CV_LOAD_IMAGE_COLOR để lấy dữ liệu là ảnh màu, 
	// nếu muốn đọc thành ảnh đen trắng bạn có thể sử dụng CV_LOAD_IMAGE_GRAYSCALE
	Mat src = imread("image2.jpg", CV_LOAD_IMAGE_COLOR);
	/*cvtColor(src, src_gray, COLOR_BGR2GRAY);
	Canny(src_gray, edges, 50, 200, 3);*/

	// Khai báo một cửa số tên là Image. Các cửa số sẽ được định danh bằng tên.
	namedWindow("Image", WINDOW_AUTOSIZE);
	// Cho hiển thị cửa số có tên là Image, với nội dung là ma trận src
	imshow("Image", src);

	//createTrackbar("Min size:", "GrayScale", &minContourSize, maxSizeThresh, trackbars_callback);
	//createTrackbar("Max size:", "GrayScale", &maxContourSize, maxSizeThresh, trackbars_callback);
	//// createTrackbar("Canny thresh:", "GrayScale", &cannyThresh, maxCannyThresh, trackbars_callback);
	//// createTrackbar("Threshold:", "GrayScale", &thresh, maxThresh, trackbars_callback);
	//// createTrackbar("Line:", "GrayScale", &lineThresh, maxThresh, Probabilistic_Hough);
	//// Probabilistic_Hough(0,0);
	//trackbars_callback(0, 0);
	//Đợi tác động của người dùng
	//0 có nghĩa là đợi mãi mãi, nếu là 1 số x khác 0 thì có nghĩa là đợi x miliseconds
	waitKey(0);
	return(0);
}

// void trackbars_callback1(int, void*)
// {		
// 		Mat drawing;
// 		cvtColor(src, drawing, COLOR_BGR2GRAY);
// 		threshold(drawing,drawing,thresh,maxThresh,THRESH_BINARY_INV);
// 		Canny(drawing, canny_output, cannyThresh, cannyThresh * 2, 3);


// 		vector<vector<Point> > contours;
// 		vector<Vec4i> hierarchy;
// 		//=Mat::zeros(src.size(), CV_8U);
// 		Mat mask=Mat::zeros(src.size(), CV_8U);
// 		mask(Range(0,mask.rows),Range(0,mask.cols))=255;
// 		// src.copyTo(drawing);
// 		// src_gray.copyTo(mask);

// 		/// Find contours
// 		findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
// 		unsigned long ignore=0;
// 		for (size_t i = 0; i< contours.size(); i++ )
// 		{
// 			double area=contourArea(contours[i]);
// 		    if (area>=minContourSize*100 && area<=maxContourSize*100)
// // if(true)
// 			{
// 				ignore++;
// 			}
// 			else{
// 				drawContours(mask, contours, (int)i, 0,-1, 8, hierarchy, 0, Point());
// 			}

// 		}
// 		printf("SIZE RANGE: %d - %d\nIGNORE: %ld COUNTOURS\n",minContourSize*100,maxContourSize*100,ignore);

// 		namedWindow("Mask", WINDOW_NORMAL);
// 		imshow("Mask", mask);
// 		moveWindow("Mask", 500,0);

// 		// bitwise_not(mask,mask);
// 		bitwise_and(drawing,mask,drawing);

// 		namedWindow("Output", WINDOW_NORMAL);
// 		imshow("Output", drawing);
// 		moveWindow("Output", 1000,0);
// }

void trackbars_callback(int, void*)
{
	Mat drawing = src;
	cvtColor(src, drawing, COLOR_BGR2GRAY);
	// cvtColor(src, drawing, COLOR_BGR2GRAY);
	threshold(drawing, drawing, 170, 255, THRESH_BINARY_INV);
	Canny(drawing, canny_output, cannyThresh, cannyThresh * 2, 3);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//=Mat::zeros(src.size(), CV_8U);
	Mat mask = Mat::zeros(src.size(), CV_8U);
	mask(Range(0, mask.rows), Range(0, mask.cols)) = 255;
	// src.copyTo(drawing);
	// src_gray.copyTo(mask);

	/// Find contours
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	unsigned long ignore = 0;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area >= minContourSize * 100 && area <= maxContourSize * 100)
			// if(true)
		{
			ignore++;
		}
		else{
			drawContours(mask, contours, (int)i, 0, -1, 8, hierarchy, 0, Point());
		}

		// drawContours(drawing, contours, (int)i, Scalar(0,255,0),-1, 8, hierarchy, 0, Point());

	}
	printf("SIZE RANGE: %d - %d\nIGNORE: %ld COUNTOURS\n", minContourSize * 100, maxContourSize * 100, ignore);

	namedWindow("Mask", WINDOW_NORMAL);
	imshow("Mask", mask);
	moveWindow("Mask", 500, 0);

	// bitwise_not(mask,mask);
	bitwise_and(drawing, mask, drawing);

	try {
		imwrite("/Users/nam/desktop/opencv_test/output.jpg", drawing);
	}
	catch (runtime_error& ex) {
		printf("Exception converting image to PNG format: %s\n", ex.what());

	}
	namedWindow("Output", WINDOW_NORMAL);
	imshow("Output", drawing);
	moveWindow("Output", 1000, 0);

}

/**
 * @function Probabilistic_Hough
 */
void Probabilistic_Hough(int, void*)
{
	Mat probabilistic_hough;
	vector<Vec4i> p_lines;
	cvtColor(src_gray, probabilistic_hough, COLOR_GRAY2BGR);

	/// 2. Use Probabilistic Hough Transform
	HoughLinesP(edges, p_lines, 1, CV_PI / 180, 0 + thresh, 5, 10);

	/// Show the result
	for (size_t i = 0; i < p_lines.size(); i++)
	{
		Vec4i l = p_lines[i];
		line(probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, LINE_AA);
	}

	imshow("Line detect", probabilistic_hough);
}

