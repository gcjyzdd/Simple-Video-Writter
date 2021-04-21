#include "simulator/vedeowriter.h"
#include <opencv2/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui.hpp>  // Video write
#include <cstring>

namespace {
std::ofstream logFile;

void Log(const std::string& str) {
  logFile.open("VideoIO.log", std::ofstream::app);
  logFile.write(str.c_str(), str.size());
  logFile.close();
}

void Debug(const std::string& str, int err) {
  Log(str + " error code:" + std::to_string(err));
}
}  // namespace

namespace sim {
using namespace std;

VideoWriterWrapper::VideoWriterWrapper(const std::string& filename, int width, int height, int fps)
  : mFilename{filename}
  , mWidth{width}
  , mHeight{height} {
  mVid =
      std::make_unique<cv::VideoWriter>(mFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));
  if (!mVid->isOpened()) {
    Debug("Error opening video stream or file", 1);
  }
  mMatBuf = std::make_unique<cv::Mat>(cv::Size(width, height), CV_8UC3);
}

VideoWriterWrapper::~VideoWriterWrapper() {}

void VideoWriterWrapper::addFrame(const uint8_t* data) {
  size_t base;
  // flip up side down and rgb to bgr
  for (size_t i = 0; i < mHeight; ++i)
    for (size_t j = 0; j < mWidth; ++j) {
      base = 3 * ((mHeight - 1 - i) * mWidth + j);
      mMatBuf->at<cv::Vec3b>(i, j) = cv::Vec3b{data[base + 2], data[base + 1], data[base]};
    }
  // cv::Mat mat(cv::Size(mWidth, mHeight), CV_8UC3, data, cv::Mat::AUTO_STEP)
  // imgcodecs required
  // cv::imwrite(cv::String("aa.png"), mat)
  mVid->write(*mMatBuf);
}

void VideoWriterWrapper::finish() {
  mVid.release();
}
}  // namespace sim
