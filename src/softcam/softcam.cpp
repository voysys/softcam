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
#define FILTER_CLSID_NO_PREFIX(number) TEXT_JOIN(DShowOdenVirtual_, number)

#define CREATE_INSTANCE_FUNC(number)                                                                                   \
    CUnknown *WINAPI INSTANCE_NAME(number)(LPUNKNOWN lpunk, HRESULT * phr)                                             \
    {                                                                                                                  \
        return softcam::Softcam::CreateInstance(FILTER_NAME(number), lpunk, __uuidof(FILTER_CLSID_NO_PREFIX(number)),  \
                                                phr);                                                                  \
    }

#define FILTER_TEMPLATE(number)                                                                                        \
    {                                                                                                                  \
        FILTER_NAME(number), &__uuidof(FILTER_CLSID_NO_PREFIX(number)), &INSTANCE_NAME(number), NULL, nullptr          \
    }

class __declspec(uuid("{DA1C0DC0-6A2E-4983-BFB8-D9B446D0D3E2}")) FILTER_CLSID_NO_PREFIX(1);

class __declspec(uuid("{37CF3542-3B79-4E74-88BA-269AA4007FE2}")) FILTER_CLSID_NO_PREFIX(2);

class __declspec(uuid("{CBC28B62-FE41-4466-8576-659A2DE09809}")) FILTER_CLSID_NO_PREFIX(3);

class __declspec(uuid("{81C16FB2-873D-43E8-9697-206EB4E74671}")) FILTER_CLSID_NO_PREFIX(4);

class __declspec(uuid("{4EA97013-E144-4392-829A-6DF9370EB943}")) FILTER_CLSID_NO_PREFIX(5);

class __declspec(uuid("{5C45B8F9-E720-45FB-8121-7BA1F304A343}")) FILTER_CLSID_NO_PREFIX(6);

class __declspec(uuid("{DC9F355A-3C0D-4155-B848-855386D1CC58}")) FILTER_CLSID_NO_PREFIX(7);

class __declspec(uuid("{02226985-7AB8-48A3-BEB1-810637062DFB}")) FILTER_CLSID_NO_PREFIX(8);

class __declspec(uuid("{F2573F2F-ABBD-4EEB-963C-96494776BE84}")) FILTER_CLSID_NO_PREFIX(9);

class __declspec(uuid("{E4CA698C-A8B2-4DFD-B536-0C0456F87A7C}")) FILTER_CLSID_NO_PREFIX(10);

class __declspec(uuid("{6BE35CE4-22D4-4D0A-ADF8-8F64C05DC0EA}")) FILTER_CLSID_NO_PREFIX(11);

class __declspec(uuid("{E98CF627-D302-4854-B0D7-F67B598DA18A}")) FILTER_CLSID_NO_PREFIX(12);

class __declspec(uuid("{B479A9A1-242C-417B-BA36-CC19D1A1C620}")) FILTER_CLSID_NO_PREFIX(13);

class __declspec(uuid("{306C2382-896B-4A88-9C40-6ADED0536972}")) FILTER_CLSID_NO_PREFIX(14);

class __declspec(uuid("{C1D2438C-CE45-4AB6-AA76-46220BAE4FFC}")) FILTER_CLSID_NO_PREFIX(15);

class __declspec(uuid("{C3E15FCB-519F-46AA-A7DB-899B7A9113E8}")) FILTER_CLSID_NO_PREFIX(16);

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
const wchar_t FILTER_NAME_9[] = L"Oden Virtual Webcam 9";
const wchar_t FILTER_NAME_10[] = L"Oden Virtual Webcam 10";
const wchar_t FILTER_NAME_11[] = L"Oden Virtual Webcam 11";
const wchar_t FILTER_NAME_12[] = L"Oden Virtual Webcam 12";
const wchar_t FILTER_NAME_13[] = L"Oden Virtual Webcam 13";
const wchar_t FILTER_NAME_14[] = L"Oden Virtual Webcam 14";
const wchar_t FILTER_NAME_15[] = L"Oden Virtual Webcam 15";
const wchar_t FILTER_NAME_16[] = L"Oden Virtual Webcam 16";

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
CREATE_INSTANCE_FUNC(9)
CREATE_INSTANCE_FUNC(10)
CREATE_INSTANCE_FUNC(11)
CREATE_INSTANCE_FUNC(12)
CREATE_INSTANCE_FUNC(13)
CREATE_INSTANCE_FUNC(14)
CREATE_INSTANCE_FUNC(15)
CREATE_INSTANCE_FUNC(16)

} // namespace

// COM global table of objects in this dll

CFactoryTemplate g_Templates[] = {
    FILTER_TEMPLATE(1),  FILTER_TEMPLATE(2),  FILTER_TEMPLATE(3),  FILTER_TEMPLATE(4),
    FILTER_TEMPLATE(5),  FILTER_TEMPLATE(6),  FILTER_TEMPLATE(7),  FILTER_TEMPLATE(8),
    FILTER_TEMPLATE(9),  FILTER_TEMPLATE(10), FILTER_TEMPLATE(11), FILTER_TEMPLATE(12),
    FILTER_TEMPLATE(13), FILTER_TEMPLATE(14), FILTER_TEMPLATE(15), FILTER_TEMPLATE(16),
};

int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

static_assert(sizeof(g_cTemplates == sizeof(g_Templates[0]) * 16), "g_Templates should contain 16 filter definitions");

void register_filter(int N)
{
    const WCHAR *filter_name = g_Templates[N].m_Name;
    const CLSID filter_clsid = *g_Templates[N].m_ClsID;

    IFilterMapper2 *pFM2 = nullptr;
    HRESULT hr =
        CoCreateInstance(CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER, IID_IFilterMapper2, (void **)&pFM2);
    if (FAILED(hr))
    {
        return;
    }
    pFM2->UnregisterFilter(&CLSID_VideoInputDeviceCategory, 0, filter_clsid);
    hr = pFM2->RegisterFilter(filter_clsid, filter_name, 0, &CLSID_VideoInputDeviceCategory, filter_name,
                              &s_reg_filter2);
    pFM2->Release();
}

void unregister_filter(int N)
{
    const WCHAR *filter_name = g_Templates[N].m_Name;
    const CLSID filter_clsid = *g_Templates[N].m_ClsID;

    IFilterMapper2 *pFM2 = nullptr;
    HRESULT hr =
        CoCreateInstance(CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER, IID_IFilterMapper2, (void **)&pFM2);
    if (FAILED(hr))
    {
        return;
    }
    hr = pFM2->UnregisterFilter(&CLSID_VideoInputDeviceCategory, filter_name, filter_clsid);
    pFM2->Release();
}

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
        for (int i = 0; i < 16; i++)
        {
            register_filter(i);
        }
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
        for (int i = 0; i < 16; i++)
        {
            unregister_filter(i);
        }
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