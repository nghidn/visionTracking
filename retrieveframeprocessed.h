#include <opencv2\opencv.hpp>

namespace trackingobjects
{
	class TrackingObjectsImpl;
	class RetrieveFrameProcessed
	{
	public:
		RetrieveFrameProcessed();
		~RetrieveFrameProcessed();
		void startRetrieveFrame();
		cv::Mat getFrameProcessed();
		cv::Mat getViolationImage();
		cv::Mat getPlateNumber();
	private:
		TrackingObjectsImpl* tracking_object_impl;
	};
}