#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// forward declaration
namespace cv {
class VideoWriter;
class Mat;
}  // namespace cv

namespace sim {

class VideoWriterWrapper {
 public:
  VideoWriterWrapper(const std::string &filename, int width, int height,
                     int channel, int fps);

  ~VideoWriterWrapper();

  void addFrame(const uint8_t *data);

  void addFrameFlipY(const uint8_t *data);

  // add RGB data and convert it to BGR for OpenCV
  void addFrameBGR(const uint8_t *data);

  /**
   * 1. add RGB data and convert it to BGR for OpenCV
   * 2. flip Y
   */
  void addFrameBGRFlipY(const uint8_t *data);

  void finish();

 private:
  std::unique_ptr<cv::VideoWriter> mVid;
  std::unique_ptr<cv::Mat> mMatBuf;
  std::unique_ptr<cv::Mat> mMatBufCopy;

  int mWidth;
  int mHeight;
  int mChannel;
  int frameCounter;
  int fps;
  std::string mFilename;
};
}  // namespace sim