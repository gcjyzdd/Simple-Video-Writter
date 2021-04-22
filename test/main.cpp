#include <cstdint>
#include <vector>
#include "simulator/vedeowriterAPI.h"

int main() {
  int err;

  VideoWriterHandle handle =
      videoWriterCreate("demo.avi", 400, 300, 3, 20, &err);

  std::vector<uint8_t> data(400 * 300 * 3, 255);
  for (size_t i = 0; i < 200 * 300 * 3; ++i) data[i] = 125;

  int n = 100;
  for (int i = 0; i < n; ++i) videoWriterAddFrame(handle, (char *)data.data());

  for (int i = 0; i < n; ++i)
    videoWriterAddFrameFlipY(handle, (char *)data.data());

  for (int i = 0; i < n; ++i)
    videoWriterAddFrameBGR(handle, (char *)data.data());

  for (int i = 0; i < n; ++i)
    videoWriterAddFrameBGRFlipY(handle, (char *)data.data());

  videoWriterFinishVideo(handle);

  videoWriterDestroy(handle);

  return 0;
}
