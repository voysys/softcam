#include "softcam.h"

// clang-format off
#include <olectl.h>
#include <initguid.h>
// clang-format on

#include <softcamcore/DShowSoftcam.h>
#include <softcamcore/SenderAPI.h>

#define TEXT_JOIN_HELPER(_x, _y) _x##_y
#define TEXT_JOIN(_x, _y) TEXT_JOIN_HELPER(_x, _y)

#define INSTANCE_NAME(number) TEXT_JOIN(CreateSoftcamInstance_, number)
#define FILTER_NAME(number) TEXT_JOIN(FILTER_NAME_, number)
#define FILTER_CLSID(number) TEXT_JOIN(CLSID_DShowOdenVirtual_, number)

#define CREATE_INSTANCE_FUNC(number)                                                                                   \
    CUnknown *WINAPI INSTANCE_NAME(number)(LPUNKNOWN lpunk, HRESULT * phr)                                             \
    {                                                                                                                  \
        return softcam::Softcam::CreateInstance(FILTER_NAME(number), lpunk, FILTER_CLSID(number), phr);                \
    }

#define FILTER_TEMPLATE(number)                                                                                        \
    {                                                                                                                  \
        FILTER_NAME(number), &FILTER_CLSID(number), &INSTANCE_NAME(number), NULL, nullptr                              \
    }

#define REGISTER_FILTER(number)                                                                                        \
    {                                                                                                                  \
        IFilterMapper2 *pFM2 = nullptr;                                                                                \
        hr = CoCreateInstance(CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER, IID_IFilterMapper2, (void **)&pFM2); \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
        pFM2->UnregisterFilter(&CLSID_VideoInputDeviceCategory, 0, FILTER_CLSID(number));                              \
        hr = pFM2->RegisterFilter(FILTER_CLSID(number), FILTER_NAME(number), 0, &CLSID_VideoInputDeviceCategory,       \
                                  FILTER_NAME(number), &s_reg_filter2);                                                \
        pFM2->Release();                                                                                               \
    }

#define UNREGISTER_FILTER(number)                                                                                      \
    {                                                                                                                  \
        IFilterMapper2 *pFM2 = nullptr;                                                                                \
        hr = CoCreateInstance(CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER, IID_IFilterMapper2, (void **)&pFM2); \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            break;                                                                                                     \
        }                                                                                                              \
        hr = pFM2->UnregisterFilter(&CLSID_VideoInputDeviceCategory, FILTER_NAME(number), FILTER_CLSID(number));       \
        pFM2->Release();                                                                                               \
    }

// Generated with GUIDGEN.exe

// {DA1C0DC0-6A2E-4983-BFB8-D9B446D0D3E2}
DEFINE_GUID(FILTER_CLSID(1), 0xda1c0dc0, 0x6a2e, 0x4983, 0xbf, 0xb8, 0xd9, 0xb4, 0x46, 0xd0, 0xd3, 0xe2);

// {37CF3542-3B79-4E74-88BA-269AA4007FE2}
DEFINE_GUID(FILTER_CLSID(2), 0x37cf3542, 0x3b79, 0x4e74, 0x88, 0xba, 0x26, 0x9a, 0xa4, 0x0, 0x7f, 0xe2);

// {CBC28B62-FE41-4466-8576-659A2DE09809}
DEFINE_GUID(FILTER_CLSID(3), 0xcbc28b62, 0xfe41, 0x4466, 0x85, 0x76, 0x65, 0x9a, 0x2d, 0xe0, 0x98, 0x9);

// {81C16FB2-873D-43E8-9697-206EB4E74671}
DEFINE_GUID(FILTER_CLSID(4), 0x81c16fb2, 0x873d, 0x43e8, 0x96, 0x97, 0x20, 0x6e, 0xb4, 0xe7, 0x46, 0x71);

// {4EA97013-E144-4392-829A-6DF9370EB943}
DEFINE_GUID(FILTER_CLSID(5), 0x4ea97013, 0xe144, 0x4392, 0x82, 0x9a, 0x6d, 0xf9, 0x37, 0xe, 0xb9, 0x43);

// {5C45B8F9-E720-45FB-8121-7BA1F304A343}
DEFINE_GUID(FILTER_CLSID(6), 0x5c45b8f9, 0xe720, 0x45fb, 0x81, 0x21, 0x7b, 0xa1, 0xf3, 0x4, 0xa3, 0x43);

// {DC9F355A-3C0D-4155-B848-855386D1CC58}
DEFINE_GUID(FILTER_CLSID(7), 0xdc9f355a, 0x3c0d, 0x4155, 0xb8, 0x48, 0x85, 0x53, 0x86, 0xd1, 0xcc, 0x58);

// {02226985-7AB8-48A3-BEB1-810637062DFB}
DEFINE_GUID(FILTER_CLSID(8), 0x2226985, 0x7ab8, 0x48a3, 0xbe, 0xb1, 0x81, 0x6, 0x37, 0x6, 0x2d, 0xfb);

namespace
{

// Setup data

const wchar_t FILTER_NAME_1[] = L"Oden Virtual Webcam 1";
const wchar_t FILTER_NAME_2[] = L"Oden Virtual Webcam 2";
const wchar_t FILTER_NAME_3[] = L"Oden Virtual Webcam 3";
const wchar_t FILTER_NAME_4[] = L"Oden Virtual Webcam 4";
const wchar_t FILTER_NAME_5[] = L"Oden Virtual Webcam 5";
const wchar_t FILTER_NAME_6[] = L"Oden Virtual Webcam 6";
const wchar_t FILTER_NAME_7[] = L"Oden Virtual Webcam 7";
const wchar_t FILTER_NAME_8[] = L"Oden Virtual Webcam 8";

const AMOVIESETUP_MEDIATYPE s_pin_types[] = {{
    &MEDIATYPE_Video,  // Major type
    &MEDIASUBTYPE_NULL // Minor type
}};

const AMOVIESETUP_PIN s_pins[] = {{
    const_cast<LPWSTR>(L"Output"), // Pin string name
    FALSE,                         // Is it rendered
    TRUE,                          // Is it an output
    FALSE,                         // Can we have none
    FALSE,                         // Can we have many
    &CLSID_NULL,                   // Connects to filter
    NULL,                          // Connects to pin
    1,                             // Number of types
    s_pin_types                    // Pin details
}};

const REGFILTER2 s_reg_filter2 = {1, MERIT_DO_NOT_USE, 1, s_pins};

CREATE_INSTANCE_FUNC(1)
CREATE_INSTANCE_FUNC(2)
CREATE_INSTANCE_FUNC(3)
CREATE_INSTANCE_FUNC(4)
CREATE_INSTANCE_FUNC(5)
CREATE_INSTANCE_FUNC(6)
CREATE_INSTANCE_FUNC(7)
CREATE_INSTANCE_FUNC(8)

} // namespace

// COM global table of objects in this dll

CFactoryTemplate g_Templates[] = {
    FILTER_TEMPLATE(1), FILTER_TEMPLATE(2), FILTER_TEMPLATE(3), FILTER_TEMPLATE(4),
    FILTER_TEMPLATE(5), FILTER_TEMPLATE(6), FILTER_TEMPLATE(7), FILTER_TEMPLATE(8),
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

STDAPI DllRegisterServer()
{
    HRESULT hr = AMovieDllRegisterServer2(TRUE);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = CoInitialize(nullptr);
    if (FAILED(hr))
    {
        return hr;
    }
    do
    {

        REGISTER_FILTER(1);
        REGISTER_FILTER(2);
        REGISTER_FILTER(3);
        REGISTER_FILTER(4);
        REGISTER_FILTER(5);
        REGISTER_FILTER(6);
        REGISTER_FILTER(7);
        REGISTER_FILTER(8);

    } while (0);
    CoFreeUnusedLibraries();
    CoUninitialize();
    return hr;
}

STDAPI DllUnregisterServer()
{
    HRESULT hr = AMovieDllRegisterServer2(FALSE);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = CoInitialize(nullptr);
    if (FAILED(hr))
    {
        return hr;
    }
    do
    {

        UNREGISTER_FILTER(1);
        UNREGISTER_FILTER(2);
        UNREGISTER_FILTER(3);
        UNREGISTER_FILTER(4);
        UNREGISTER_FILTER(5);
        UNREGISTER_FILTER(6);
        UNREGISTER_FILTER(7);
        UNREGISTER_FILTER(8);

    } while (0);
    CoFreeUnusedLibraries();
    CoUninitialize();
    return hr;
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}

//
// Softcam Sender API
//

extern "C" scCamera scCreateCamera(int width, int height, float framerate)
{
    return softcam::sender::CreateCamera(width, height, framerate);
}

extern "C" void scDeleteCamera(scCamera camera)
{
    return softcam::sender::DeleteCamera(camera);
}

extern "C" void scSendFrame(scCamera camera, const void *image_bits)
{
    return softcam::sender::SendFrame(camera, image_bits);
}

extern "C" bool scWaitForConnection(scCamera camera, float timeout)
{
    return softcam::sender::WaitForConnection(camera, timeout);
}

extern "C" const char *scGetCameraName(scCamera camera)
{
    return softcam::sender::GetCameraName(camera);
}