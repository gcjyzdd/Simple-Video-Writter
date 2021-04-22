#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_
#include "videowriter/VideoWriterExports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VideoWriter_t *VideoWriterHandle;

VideoWriterHandle VIDEOWRITER_API videoWriterCreate(const char *fileName,
                                                    int width, int height,
                                                    int channel, int fps,
                                                    int *err);

void VIDEOWRITER_API videoWriterDestroy(VideoWriterHandle handle);

int VIDEOWRITER_API videoWriterAddFrame(VideoWriterHandle handle,
                                        const char *data);

int VIDEOWRITER_API videoWriterAddFrameFlipY(VideoWriterHandle handle,
                                             const char *data);

/**
 * @brief Write a frame and convert it from RGB to BGR such that OpenCV writes it properly
 * 
 * @param handle Video writer handle
 * @param data Frame data, size = width * height * channel
 * @return int 0 if success
 */
int VIDEOWRITER_API videoWriterAddFrameBGR(VideoWriterHandle handle,
                                           const char *data);

/**
 * @brief Write a frame and convert it from RGB to BGR and flip Y(useful for OpenGL buffer)
 * 
 * @param handle Video writer handle
 * @param data Frame data, size = width * height * channel
 * @return int 0 if success
 */
int VIDEOWRITER_API videoWriterAddFrameBGRFlipY(VideoWriterHandle handle,
                                                const char *data);

int VIDEOWRITER_API videoWriterFinishVideo(VideoWriterHandle handle);

#ifdef __cplusplus
}
#endif

#endif