#include "SenderAPI.h"

#include <atomic>
#include <vector>
#include <shared_mutex>
#include <thread>

#include "FrameBuffer.h"
#include "Misc.h"


namespace {

typedef std::shared_mutex Mutex;
typedef std::shared_lock<std::shared_mutex> ReadLock;
typedef std::unique_lock<std::shared_mutex> WriteLock;

struct Camera
{
    softcam::FrameBuffer    m_frame_buffer;
    softcam::Timer          m_timer;
    std::string             m_name;
};

std::vector<Camera*>    s_cameras;
Mutex s_cameras_mutex;

} //namespace


namespace softcam {
namespace sender {

CameraHandle    CreateCamera(const char * name, int width, int height, float framerate)
{
    if (auto fb = FrameBuffer::create(name, width, height, framerate))
    {
        WriteLock write_lock(s_cameras_mutex);
        {
            s_cameras.erase(std::remove_if(s_cameras.begin(), s_cameras.end(), [name](Camera * cam) {
                if (cam->m_name == name) {
                    cam->m_frame_buffer.deactivate();
                    delete cam;

                    return true;
                } else {
                    return false;
                }
            }), s_cameras.end());

            Camera* camera = new Camera{ fb, Timer(), name };
            s_cameras.push_back(camera);

            return camera;
        }
    }
    return nullptr;
}

void            DeleteCamera(CameraHandle camera)
{
    Camera* target = static_cast<Camera*>(camera);

    if (target == nullptr) {
        return;
    }

    WriteLock write_lock(s_cameras_mutex);
    {
        s_cameras.erase(std::remove_if(s_cameras.begin(), s_cameras.end(), [target](Camera * cam) {
            if (cam == target) {
                target->m_frame_buffer.deactivate();
                delete cam;

                return true;
            } else {
                return false;
            }
        }), s_cameras.end());
    }
}

void            SendFrame(CameraHandle camera, const void* image_bits)
{
    Camera* target = static_cast<Camera*>(camera);

    if (target == nullptr) {
        return;
    }

    ReadLock read_lock(s_cameras_mutex);

    for (Camera * cam : s_cameras) 
    {
        if (cam == target && image_bits != nullptr) 
        {

            auto framerate = target->m_frame_buffer.framerate();
            auto frame_counter = target->m_frame_buffer.frameCounter();

            // To deliver frames in the regular period, we sleep here a bit
            // before we deliver the new frame if it's not the time yet.
            // If it's already the time, we deliver it immediately and
            // let the timer keep running so that if the next frame comes
            // in time the constant delivery recovers.
            // However if the delay grew too much (greater than 50 percent
            // of the period), we reset the timer to avoid continuing
            // irregular delivery.
            if (0.0f < framerate)
            {
                if (0 == frame_counter) // the first frame
                {
                    target->m_timer.reset();
                }
                else
                {
                    auto ref_delta = 1.0f / framerate;
                    auto time = target->m_timer.get();
                    if (time < ref_delta)
                    {
                        Timer::sleep(ref_delta - time);
                    }
                    if (time < ref_delta * 1.5f)
                    {
                        target->m_timer.rewind(ref_delta);
                    }
                    else
                    {
                        target->m_timer.reset();
                    }
                }
            }

            target->m_frame_buffer.write(image_bits);

            break;
        }
    }
}

bool            WaitForConnection(CameraHandle camera, float timeout)
{
    Camera* target = static_cast<Camera*>(camera);

    if (target == nullptr) {
        return false;
    }

    ReadLock read_lock(s_cameras_mutex);

    for (Camera * cam : s_cameras) {
        if (cam == target) {

            Timer timer;
            while (!target->m_frame_buffer.connected())
            {
                if (0.0f < timeout && timeout <= timer.get())
                {
                    return false;
                }
                Timer::sleep(0.001f);
            }
            return true;
        }
    }

    return false;
}

const char * GetWebcamName(CameraHandle camera) {

    Camera* target = static_cast<Camera*>(camera);

    if (target == nullptr) {
        return nullptr;
    }

    ReadLock read_lock(s_cameras_mutex);

    for (Camera * cam : s_cameras) {
        if (cam == target) {
            return cam->m_name.c_str();
        }
    }

    return nullptr;
}

} //namespace sender
} //namespace softcam
