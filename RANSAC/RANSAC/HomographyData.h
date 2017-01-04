#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "HomographyModel.h"

using namespace cv;
using namespace cv::xfeatures2d;


class HomographyData {
	private :
		Mat Im1;
		Mat Im2; // Try to make a vector of anny number of Mat at the end
		Mat Im1_gray; //for cornerHarris function
		Mat Im2_gray;
		Mat img_matches;
		Mat img_transformed;
		Mat descriptors1, descriptors2;
		vector< DMatch > matches;
		vector<KeyPoint> Im1_keypoints;
		vector<KeyPoint> Im2_keypoints;
		int minDist = -1;
		vector<double> dists;
		int meanDist = -1;
	
	public :
		HomographyData() {
			Im1 = imread("Images/image0006.jpg", CV_LOAD_IMAGE_COLOR);
			Im2 = imread("Images/image0007.jpg", CV_LOAD_IMAGE_COLOR);
			cvtColor(Im1, Im1_gray, CV_BGR2GRAY); //harris needs gray image
			cvtColor(Im2, Im2_gray, CV_BGR2GRAY);
			Im1_keypoints = findHarris(Im1_gray);
			Im2_keypoints = findHarris(Im2_gray);
			Ptr<SiftDescriptorExtractor> extractor = SiftDescriptorExtractor::create();
			extractor->compute(Im1_gray, Im1_keypoints, descriptors1);
			extractor->compute(Im2_gray, Im2_keypoints, descriptors2);
			//FlannBasedMatcher matcher;
			matches = findMatches();
		} 

		HomographyData(Mat Image1, Mat Image2) {
			Im1 = Image1;
			Im2 = Image2;
			if (Im1.type() != CV_8U)
				cvtColor(Im1, Im1_gray, CV_BGR2GRAY); //harris needs gray image
			else
				Im1_gray = Im1;
			if (Im2.type() != CV_8U)
				cvtColor(Im2, Im2_gray, CV_BGR2GRAY);
			else
				Im2_gray = Im2;
			Im1_keypoints = findHarris(Im1_gray);
			Im2_keypoints = findHarris(Im2_gray);
			Ptr<SiftDescriptorExtractor> extractor = SiftDescriptorExtractor::create();
			extractor->compute(Im1_gray, Im1_keypoints, descriptors1);
			extractor->compute(Im2_gray, Im2_keypoints, descriptors2);
			//FlannBasedMatcher matcher;
			matches = findMatches();
		}

		auto begin() {
			return Im1_keypoints.begin();
		}

		auto end() {
			return Im1_keypoints.end();
		}

		double getMinDist() {
			return dists.at(0);
		}

		double getDistsAt(int i) {
			return dists.at(i);
		}

		int getMeanDist() {
			return meanDist;
		}
		
		vector<KeyPoint> getInOutliersData() const
		{
			return Im1_keypoints;
		}

		HomographyModel* computeModel(int k) {
			// compute descriptors
			vector<DMatch> sub_matches = RansacUtils::getSubVector(matches,k);
			//vector<DMatch> sub_matches = matches;
			//-- Quick calculation of max and min distances between keypoints
			double max_dist = 0; double min_dist = 10000;
			for (int i = 0; i < sub_matches.size(); i++)
			{
				double dist = sub_matches[i].distance;
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
			}

			//-- Find the Homography
			vector<Point2f> obj;
			vector<Point2f> scene;
			for (int i = 0; i < sub_matches.size(); i++)
			{
				obj.push_back(Im1_keypoints[sub_matches[i].queryIdx].pt);
				scene.push_back(Im2_keypoints[sub_matches[i].trainIdx].pt);
			}
			Mat H = findHomography(obj, scene);
			return computeHomographyModel(H);
		}

		HomographyModel* computeHomographyModel(Mat H) {
			vector<Point2f> cadre;
			cadre.push_back(Point2f(0, 0));
			cadre.push_back(Point2f(Im1_gray.size().width, 0));
			cadre.push_back(Point2f(0, Im1_gray.size().height));
			cadre.push_back(Point2f(Im1_gray.size().width, Im1_gray.size().height));
			Mat MDest;
			try {
				perspectiveTransform(Mat(cadre), MDest, H);
			}
			catch (...) { 
				return NULL;
			}

			// Compute the fra:e in image 2
			double min_x, min_y, tam_x, tam_y;
			float min_x1, min_x2, min_y1, min_y2, max_x1, max_x2, max_y1, max_y2;
			min_x1 = min(MDest.at<Point2f>(0).x, MDest.at<Point2f>(1).x);
			min_x2 = min(MDest.at<Point2f>(2).x, MDest.at<Point2f>(3).x);
			min_y1 = min(MDest.at<Point2f>(0).y, MDest.at<Point2f>(1).y);
			min_y2 = min(MDest.at<Point2f>(2).y, MDest.at<Point2f>(3).y);
			max_x1 = max(MDest.at<Point2f>(0).x, MDest.at<Point2f>(1).x);
			max_x2 = max(MDest.at<Point2f>(2).x, MDest.at<Point2f>(3).x);
			max_y1 = max(MDest.at<Point2f>(0).y, MDest.at<Point2f>(1).y);
			max_y2 = max(MDest.at<Point2f>(2).y, MDest.at<Point2f>(3).y);
			min_x = min(min_x1, min_x2);
			min_y = min(min_y1, min_y2);
			tam_x = max(max_x1, max_x2);
			tam_y = max(max_y1, max_y2);

			// Matric de transformation
			Mat Htr = Mat::eye(3, 3, CV_64F);
			if (min_x < 0) {
				tam_x = Im2_gray.size().width - min_x;
				Htr.at<double>(0, 2) = -min_x;
			}
			if (min_y < 0) {
				tam_y = Im2_gray.size().height - min_y;
				Htr.at<double>(1, 2) = -min_y;
			}
			return new HomographyModel(H,Htr,tam_x,tam_y, Im1_gray, Im2_gray, descriptors1);
		}

		vector<DMatch> findMatches() {
			BFMatcher matcher(NORM_L2);
			matcher.match(descriptors1, descriptors2, matches);
			double max_dist = 0; double min_dist = 10000;
			double mean_dist = 0;
			//-- Quick calculation of max and min distances between keypoints

			dists.clear();
			for (int i = 0; i < descriptors1.rows; i++)
			{
				double dist = matches[i].distance;
				if (dist < min_dist) min_dist = dist;
				if (dist > max_dist) max_dist = dist;
				dists.push_back(dist);
				mean_dist += dist;
			}

			sort(dists.begin(), dists.end());
			printf("-- min-Max dist : %f - %f [%f] / %f\n", dists.at(0), dists.at(dists.size()-1), mean_dist / descriptors1.rows, dists.at(10));

			minDist = min_dist;
			meanDist = mean_dist / descriptors1.rows;
			//return matches;

			//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
			vector<DMatch> good_matches;
			int scale = 3;
			while (good_matches.size() < 30)
			{
				good_matches.clear();
				for (int i = 0; i < descriptors1.rows; i++)
				{
					if (matches[i].distance <= scale * min_dist)
					{
						good_matches.push_back(matches[i]);
					}
				}
				scale++;
			}
			cout << "points reduced from " << matches.size() << " to " << good_matches.size() << "[scale : "<< scale - 1 << "]" << endl;
			return good_matches;
		}

		void show(HomographyModel model) {
			// Construire panorama
			Mat Panorama = getPanorama(model);
			imshow("Panorama", Panorama);
			waitKey(0);
		}

		Mat getPanorama(HomographyModel model) {
			Mat H = model.getH();
			Mat Htr = model.getHtr();
			// Construir panorama
			Mat Panorama;
			Panorama = Mat(Size(model.getPanoW(), model.getPanoW()), CV_32F);
			warpPerspective(Im2_gray, Panorama, Htr, Panorama.size(), INTER_LINEAR, BORDER_CONSTANT, 0);
			warpPerspective(Im1_gray, Panorama, (Htr*H), Panorama.size(), INTER_LINEAR, BORDER_TRANSPARENT, 0);
			return Panorama;
		}

		vector<KeyPoint> findHarris(Mat img, bool verbose = false)
		{
			Mat dst, dst_norm, dst_norm_scaled;
			dst = Mat::zeros(img.size(), CV_32FC1);

			/// Detector parameters
			int blockSize = 2;
			int apertureSize = 5;
			double k = 0.04;
			int thresh = 30;

			/// Detecting corners
			cornerHarris(img, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

			/// Normalizing
			normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
			convertScaleAbs(dst_norm, dst_norm_scaled);
			vector<KeyPoint> res;
			bool restart = true; 
			while (restart == true)
			{
				restart = false;
				for (int j = 0; j < dst_norm.rows; j++)
				{
					for (int i = 0; i < dst_norm.cols; i++)
					{
						if ((int)dst_norm.at<float>(j, i) > thresh)
						{
							res.push_back(KeyPoint(i, j, 1));
							if (res.size() > 500) {
								thresh += 10;
								res.clear();
								restart = true;
								i = dst_norm.cols;
								j = dst_norm.rows;
							}
						}
					}
				}
			}
			cout << "Harris Points Found : " << res.size() << " (threshhold is : " << thresh << ")" << endl;

			Mat temp;
			img.copyTo(temp);
			/// Showing the result
			if (verbose) {
				/// Drawing a circle around corners
					for (int j = 0; j < dst_norm.rows; j++)
					{
						for (int i = 0; i < dst_norm.cols; i++)
						{
							if ((int)dst_norm.at<float>(j, i) > thresh)
							{
								circle(temp, Point(i, j), 5, Scalar(0), 2, 8, 0);
							}
						}
					}
					namedWindow("Harris Points", CV_WINDOW_AUTOSIZE);
					imshow("Harris Points", temp);
					waitKey(0);
			}
			return res;
		}




};