#pragma once
using namespace cv::xfeatures2d;


class HomographyModel{
private : 
	Mat H;
	Mat Htr;
	int pano_w;
	int pano_h;
	Mat srcImage;
	Mat destImage;
	Mat srcDescriptors;
public : 
	HomographyModel(Mat homographie, Mat homoTr, int tam_x, int tam_y) {
		H = homographie;
		Htr = homoTr;
		pano_w = tam_x;
		pano_h = tam_y;
	}

	HomographyModel(Mat homographie, Mat homoTr, int tam_x, int tam_y, Mat Im1, Mat Im2, Mat descriptors1) {
		H = homographie;
		Htr = homoTr;
		pano_w = tam_x;
		pano_h = tam_y;
		srcImage = Im1;
		destImage = Im2;
		srcDescriptors = descriptors1;
	}

	Mat getH() {
		return H;
	}; 
	Mat getHtr() {
		return Htr;
	};
	Mat setH(Mat h) {
		H = h;
	};
	Mat setHtr(Mat htr) {
		Htr = htr;
	};
	int getPanoW() { return pano_w; };
	int getPanoH() { return pano_h; };
	
	int countInliers(vector<KeyPoint> keyPoints, int allowedError) {
		int res = 0;
		vector<Point2f> points;
		for (auto i = keyPoints.begin(); i < keyPoints.end(); i++)
			points.push_back(i->pt);
		vector<Point2f> transformedPoints;
		vector<KeyPoint> tranformedKeyPoints;
		perspectiveTransform(points, transformedPoints, H);
		for (auto i = transformedPoints.begin(); i < transformedPoints.end(); i++)
			tranformedKeyPoints.push_back(KeyPoint(*i, 1));
		Ptr<SiftDescriptorExtractor> extractor = SiftDescriptorExtractor::create();
		Mat descriptors1, descriptors2;
		extractor->compute(destImage, tranformedKeyPoints, descriptors2);
		BFMatcher matcher(NORM_L2);
		/*vector<DMatch> matches;
		matcher.match(descriptors1, descriptors2, matches);*/
		double max_dist = 0; double min_dist = 10000;
		for (int i = 0; i < srcDescriptors.rows; i++)
		{
			if (!(tranformedKeyPoints.at(i).pt.x < 0
				|| tranformedKeyPoints.at(i).pt.x >= destImage.cols
				|| tranformedKeyPoints.at(i).pt.y < 0
				|| tranformedKeyPoints.at(i).pt.y >= destImage.rows))
			{
				double dist = norm(srcDescriptors.row(i) - descriptors2.row(i), NORM_L2);
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
				res += (dist < allowedError ? 1 : 0);
			}
		}
		return res;
	}

	void printClass() {
		cout << "HomographyModel : H is of size " << H.size() << endl;
	}
};

