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
	bool isInlier(KeyPoint pt, double allowedErr) const {
		vector<Point2f> key;
		vector<Point2f> res(1);
		key.push_back(pt.pt);
		perspectiveTransform(key, res, H);
		res.at(0).x = (int) floor(res.at(0).x);
		res.at(0).y = (int) floor(res.at(0).y);
		if (res.at(0).x < 0 || res.at(0).x >= destImage.cols || res.at(0).y < 0 || res.at(0).y >= destImage.rows)
			return false;
		else {
			return (abs(srcImage.at<uchar>(key.at(0)) - destImage.at<uchar>(res.at(0))) <= allowedErr);
		}
		
	}

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
		extractor->compute(srcImage, keyPoints, descriptors1); //should be able to optimise and use the right rows of srcDescriptors
		extractor->compute(destImage, tranformedKeyPoints, descriptors2);
		BFMatcher matcher(NORM_L2);
		vector<DMatch> matches;
		matcher.match(descriptors1, descriptors2, matches);
		double max_dist = 0; double min_dist = 10000;
		for (int i = 0; i < descriptors1.rows; i++)
		{
			double dist = matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			if (dist > max_dist) max_dist = dist;
		}
		printf("-- min-Max dist in check : %f - %f\n", min_dist, max_dist);
		for (int i = 0; i < descriptors1.rows; i++) {
			res += (matches[i].distance < allowedError ? 1 : 0);
		}
		return res;
	}

	void printClass() {
		cout << "HomographyModel : H is of size " << H.size() << endl;
	}
};

