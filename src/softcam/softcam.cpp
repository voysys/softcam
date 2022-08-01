#include "softcam.h"

// clang-format: off
#include <olectl.h>
#include <initguid.h>
// clang-format: on

#include <softcamcore/DShowSoftcam.h>
#include <softcamcore/SenderAPI.h>


// {EA27EAE5-7FA2-432A-9914-F529AE8D0F06}
DEFINE_GUID(CLSID_DShowOdenVirtual,
    0xea27eae5, 0x7fa2, 0x432a, 0x99, 0x14, 0xf5, 0x29, 0xae, 0x8d, 0x0f, 0x06);


namespace {

// Setup data

const wchar_t FILTER_NAME_1[] = L"Oden Virtual Webcam 1";
const wchar_t FILTER_NAME_2[] = L"Oden Virtual Webcam 2";
const wchar_t FILTER_NAME_3[] = L"Oden Virtual Webcam 3";
const wchar_t FILTER_NAME_4[] = L"Oden Virtual Webcam 4";
const wchar_t FILTER_NAME_5[] = L"Oden Virtual Webcam 5";
const wchar_t FILTER_NAME_6[] = L"Oden Virtual Webcam 6";
const wchar_t FILTER_NAME_7[] = L"Oden Virtual Webcam 7";
const wchar_t FILTER_NAME_8[] = L"Oden Virtual Webcam 8";
const GUID &FILTER_CLASSID = CLSID_DShowOdenVirtual;

const AMOVIESETUP_MEDIATYPE s_pin_types[] =
{
    {
        &MEDIATYPE_Video,       // Major type
        &MEDIASUBTYPE_NULL      // Minor type
    }
};

const AMOVIESETUP_PIN s_pins[] =
{
    {
        const_cast<LPWSTR>(L"Output"),  // Pin string name
        FALSE,                  // Is it rendered
        TRUE,                   // Is it an output
        FALSE,                  // Can we have none
        FALSE,                  // Can we have many
        &CLSID_NULL,            // Connects to filter
        NULL,                   // Connects to pin
        1,                      // Number of types
        s_pin_types             // Pin details
    }
};

const REGFILTER2 s_reg_filter2 =
{
    1,
    MERIT_DO_NOT_USE,
    1,
    s_pins
};

CUnknown * WINAPI CreateSoftcamInstance_1(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_1, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_2(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_2, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_3(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_3, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_4(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_4, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_5(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_5, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_6(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_6, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_7(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_7, lpunk, FILTER_CLASSID, phr);
}

CUnknown * WINAPI CreateSoftcamInstance_8(LPUNKNOWN lpunk, HRESULT *phr)
{
    return softcam::Softcam::CreateInstance(FILTER_NAME_8, lpunk, FILTER_CLASSID, phr);
}

} // namespace

// COM global table of objects in this dll

CFactoryTemplate g_Templates[] =
{
    {
        FILTER_NAME_1,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_1,
        NULL,
        nullptr
    },
        {
        FILTER_NAME_2,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_2,
        NULL,
        nullptr
    },
        {
        FILTER_NAME_3,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_3,
        NULL,
        nullptr
    },
        {
        FILTER_NAME_4,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_4,
        NULL,
        nullptr
    },    {
        FILTER_NAME_5,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_5,
        NULL,
        nullptr
    },    {
        FILTER_NAME_6,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_6,
        NULL,
        nullptr
    },
        {
        FILTER_NAME_7,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_7,
        NULL,
        nullptr
    },    {
        FILTER_NAME_8,
        &FILTER_CLASSID,
        &CreateSoftcamInstance_8,
        NULL,
        nullptr
    }
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
        {
            IFilterMapper2 *pFM2 = nullptr;
            hr = CoCreateInstance(
                    CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER,
                    IID_IFilterMapper2, (void**)&pFM2);
            if (FAILED(hr))
            {
                break;
            }
            pFM2->UnregisterFilter(
                    &CLSID_VideoInputDeviceCategory,
                    0,
                    FILTER_CLASSID);
            hr = pFM2->RegisterFilter(
                    FILTER_CLASSID,
                    FILTER_NAME_1,
                    0,
                    &CLSID_VideoInputDeviceCategory,
                    FILTER_NAME_1,
                    &s_reg_filter2);
            pFM2->Release();
        }

                {
            IFilterMapper2 *pFM2 = nullptr;
            hr = CoCreateInstance(
                    CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER,
                    IID_IFilterMapper2, (void**)&pFM2);
            if (FAILED(hr))
            {
                break;
            }
            pFM2->UnregisterFilter(
                    &CLSID_VideoInputDeviceCategory,
                    0,
                    FILTER_CLASSID);
            hr = pFM2->RegisterFilter(
                    FILTER_CLASSID,
                    FILTER_NAME_2,
                    0,
                    &CLSID_VideoInputDeviceCategory,
                    FILTER_NAME_2,
                    &s_reg_filter2);
            pFM2->Release();
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
        {
            IFilterMapper2 *pFM2 = nullptr;
            hr = CoCreateInstance(
                    CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER,
                    IID_IFilterMapper2, (void**)&pFM2);
            if (FAILED(hr))
            {
                break;
            }
            hr = pFM2->UnregisterFilter(
                    &CLSID_VideoInputDeviceCategory,
                    FILTER_NAME_1,
                    FILTER_CLASSID);
            pFM2->Release();
        }

        {
            IFilterMapper2 *pFM2 = nullptr;
            hr = CoCreateInstance(
                    CLSID_FilterMapper2, nullptr, CLSCTX_INPROC_SERVER,
                    IID_IFilterMapper2, (void**)&pFM2);
            if (FAILED(hr))
            {
                break;
            }
            hr = pFM2->UnregisterFilter(
                    &CLSID_VideoInputDeviceCategory,
                    FILTER_NAME_2,
                    FILTER_CLASSID);
            pFM2->Release();
        }
    } while (0);
    CoFreeUnusedLibraries();
    CoUninitialize();
    return hr;
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  dwReason, LPVOID lpReserved)
{
    return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}


//
// Softcam Sender API
//

extern "C" scCamera scCreateCamera(const char * name, int width, int height, float framerate)
{
    return softcam::sender::CreateCamera(name, width, height, framerate);
}

extern "C" void     scDeleteCamera(scCamera camera)
{
    return softcam::sender::DeleteCamera(camera);
}

extern "C" void     scSendFrame(scCamera camera, const void* image_bits)
{
    return softcam::sender::SendFrame(camera, image_bits);
}

extern "C" bool     scWaitForConnection(scCamera camera, float timeout)
{
    return softcam::sender::WaitForConnection(camera, timeout);
}

extern "C" const char * scGetWebcamName(scCamera camera) {
    return softcam::sender::GetWebcamName(camera);
}