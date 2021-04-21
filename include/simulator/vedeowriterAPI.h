#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_
#include "videowriter/VideoWriterExports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VideoWriter_t* VideoWriterHandle;

VideoWriterHandle VIDEOWRITER_API videoWriterCreate(const char* fileName,
                                                    int width, int height,
                                                    int fps, int* err);

void VIDEOWRITER_API videoWriterDestroy(VideoWriterHandle handle);

int VIDEOWRITER_API videoWriterAddFrame(VideoWriterHandle handle,
                                        const char* data);

int VIDEOWRITER_API videoWriterFinishVideo(VideoWriterHandle handle);

#ifdef __cplusplus
}
#endif

#endif