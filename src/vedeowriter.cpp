#include "simulator/vedeowriter.h"
#include <cstdint>
#include <cstring>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui.hpp>  // Video write
#include <string>

namespace {
std::ofstream logFile;

void Log(const std::string &str) {
  logFile.open("VideoIO.log", std::ofstream::app);
  logFile.write(str.c_str(), str.size());
  logFile.close();
}

void Debug(const std::string &str, int err) {
  Log(str + " error code:" + std::to_string(err));
}
}  // namespace

namespace sim {
using namespace std;

VideoWriterWrapper::VideoWriterWrapper(const std::string &filename, int width,
                                       int height, int channel, int fps)
    : mWidth{width}, mHeight{height}, mChannel{channel}, mFilename{filename} {
  // int fourcc = cv::VideoWriter::fourcc('X', '2', '6', '4');
  int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
  mVid = std::make_unique<cv::VideoWriter>(mFilename, fourcc, fps,
                                           cv::Size(width, height));
  if (!mVid->isOpened()) {
    Debug("Error opening video stream or file", 1);
  }
  mMatBuf = std::make_unique<cv::Mat>(cv::Size(width, height), CV_8UC3);
  mMatBufCopy = std::make_unique<cv::Mat>(cv::Size(width, height), CV_8UC3);
}

VideoWriterWrapper::~VideoWriterWrapper() {}

void VideoWriterWrapper::addFrame(const uint8_t *data) {
  size_t base;
  if (mChannel == 1) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = i * mWidth + j;
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base], data[base]};
      }
  } else if (mChannel == 3) {
    memcpy(mMatBuf->data, data, mWidth * mHeight * 3);
  } else if (mChannel == 4) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = mChannel * (i * mWidth + j);
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base + 1], data[base + 2]};
      }
  }

  mVid->write(*mMatBuf);
}

void VideoWriterWrapper::addFrameFlipY(const uint8_t *data) {
  size_t base;
  if (mChannel == 1) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = (mHeight - 1 - i) * mWidth + j;
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base], data[base]};
      }
  } else if (mChannel == 3) {
    memcpy(mMatBuf->data, data, mWidth * mHeight * 3);
    cv::flip(*mMatBuf, *mMatBufCopy, 0);
  } else if (mChannel == 4) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = mChannel * ((mHeight - 1 - i) * mWidth + j);
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base + 1], data[base + 2]};
      }
  }

  mVid->write(mChannel == 3 ? *mMatBufCopy : *mMatBuf);
}

void VideoWriterWrapper::addFrameBGR(const uint8_t *data) {
  size_t base;
  // rgb to bgr
  if (mChannel == 1) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = i * mWidth + j;
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base], data[base]};
      }
  } else {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = mChannel * (i * mWidth + j);
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base + 2], data[base + 1], data[base]};
      }
  }

  mVid->write(*mMatBuf);
}

void VideoWriterWrapper::addFrameBGRFlipY(const uint8_t *data) {
  size_t base;
  // flip up side down and rgb to bgr
  if (mChannel == 1) {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = (mHeight - 1 - i) * mWidth + j;
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base], data[base], data[base]};
      }
  } else {
    for (size_t i = 0; i < mHeight; ++i)
      for (size_t j = 0; j < mWidth; ++j) {
        base = mChannel * ((mHeight - 1 - i) * mWidth + j);
        mMatBuf->at<cv::Vec3b>(i, j) =
            cv::Vec3b{data[base + 2], data[base + 1], data[base]};
      }
  }

  // imgcodecs required
  // cv::imwrite(cv::String("aa.png"), *mMatBuf)
  mVid->write(*mMatBuf);
}

void VideoWriterWrapper::finish() { mVid.release(); }
}  // namespace sim
