#include "simulator/vedeowriterAPI.h"
#include "simulator/vedeowriter.h"

struct VideoWriter_t {
  sim::VideoWriterWrapper *data{nullptr};
};

VideoWriterHandle videoWriterCreate(const char *fileName, int width, int height,
                                    int channel, int fps, int *err) {
  VideoWriterHandle handle = new VideoWriter_t();

  try {
    handle->data =
        new sim::VideoWriterWrapper(fileName, width, height, channel, fps);
  } catch (std::system_error &) {
    *err = 1;
  }

  *err = 0;

  return handle;
}

void videoWriterDestroy(VideoWriterHandle handle) {
  delete handle->data;
  delete handle;
  handle = nullptr;
}

int videoWriterAddFrame(VideoWriterHandle handle, const char *data) {
  handle->data->addFrame((const uint8_t *)data);
  return 0;
}

int videoWriterAddFrameFlipY(VideoWriterHandle handle, const char *data) {
  handle->data->addFrameFlipY((const uint8_t *)data);
  return 0;
}

int videoWriterAddFrameBGR(VideoWriterHandle handle, const char *data) {
  handle->data->addFrameBGR((const uint8_t *)data);
  return 0;
}

int videoWriterAddFrameBGRFlipY(VideoWriterHandle handle, const char *data) {
  handle->data->addFrameBGRFlipY((const uint8_t *)data);
  return 0;
}

int videoWriterFinishVideo(VideoWriterHandle handle) {
  handle->data->finish();
  return 0;
}
