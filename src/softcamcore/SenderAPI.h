#pragma once


namespace softcam {
namespace sender {

using CameraHandle = void*;

CameraHandle    CreateCamera(const char * name, int width, int height, float framerate = 60.0f);
void            DeleteCamera(CameraHandle camera);
void            SendFrame(CameraHandle camera, const void* image_bits);
bool            WaitForConnection(CameraHandle camera, float timeout = 0.0f);
const char *    GetWebcamName(CameraHandle camera);

} //namespace sender
} //namespace softcam
