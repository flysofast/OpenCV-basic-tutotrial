#include "stdafx.h"

using namespace std;
using namespace cv;

int thresh = 127;
int maxThresh = 255;
Mat src;



/// Function header
void trackbars_callback(int, void*);


/** @function main */
int main()
{

	// Khai báo một đối tượng Mat để lưu giữ hình ảnh được đọc vào
	// src: đối tượng kiểu Mat
	// imread: hàm đọc dữ liệu từ file, trả về kiểu Mat
	// imread(Tên_file, kiểu dữ liệu nhập vào)
	// Ở đây mình dùng CV_LOAD_IMAGE_COLOR để lấy dữ liệu là ảnh màu, 
	// nếu muốn đọc thành ảnh đen trắng bạn có thể sử dụng CV_LOAD_IMAGE_GRAYSCALE
	src = imread("image2.jpg", CV_LOAD_IMAGE_COLOR);


	// Khai báo một cửa số tên là Image. Các cửa số sẽ được định danh bằng tên.
	namedWindow("Image", WINDOW_AUTOSIZE);
	// Cho hiển thị cửa số có tên là Image, với nội dung là ma trận src
	imshow("Image", src);

	//Tạo 1 trackbar vào cửa sổ có tên Image.
	// thresh là tham biến giữ giá trị của thanh trượt
	// maxThresh là giá trị tối đa của thanh trượt
	// trackbar_callback là hàm sẽ được gọi mỗi khi có thay đổi giá trị ở trackbar
	createTrackbar("Line", "Image", &thresh, maxThresh, trackbars_callback);

	//Gọi hàm 1 lần cho lần chạy đầu tiên 
	//để cập nhật kết quả hiển thị cho khớp với thanh trượt
	trackbars_callback(0, 0);


	//Đợi tác động của người dùng
	//0 có nghĩa là đợi mãi mãi, nếu là 1 số x khác 0 thì có nghĩa là đợi x miliseconds
	waitKey(0);
	return(0);
}

void trackbars_callback(int, void*)
{
	Mat src_gray;
	//Chuyển hình về grayscale, lưu vào biến src_gray
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	//Threshold(hình gốc, hình đích, ngưỡng chọn màu, giá trị màu tối đa, loại threshold)
	//Ý nghĩa:
	//Chuyển src_gray về dạng nhị phân và lưu lại đúng vào biến src_gray, những điểm ảnh có giá trị màu
	//lớn hơn thresh sẽ được chuyển thành màu trắng (255), ngược lại thì thành màu đen (0).
	threshold(src_gray, src_gray, thresh, 255, THRESH_BINARY);
	
	namedWindow("Output", WINDOW_NORMAL);
	imshow("Output", src_gray);

	//Di chuyển cửa sổ qua phải 1000 pixel (x+1000)
	moveWindow("Output", 1000, 0);

}
