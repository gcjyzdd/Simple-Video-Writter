#include <vector>
#include "simulator/vedeowriterAPI.h"

int main() {
  int err;

  VideoWriterHandle handle = videoWriterCreate("demo.avi", 400, 300, 20, &err);

  std::vector<uint8_t> data(400 * 300 * 3, 255);
  for (size_t i = 0; i < 200 * 300 * 3; ++i) data[i] = 125;

  for (int i = 0; i < 200; ++i) videoWriterAddFrame(handle, (char*)data.data());

  videoWriterFinishVideo(handle);

  videoWriterDestroy(handle);

  return 0;
}
