#include <mfapi.h>
#include <mfplay.h>
#include <mfreadwrite.h>
#include <iostream>

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

#ifndef FAILURE
    #define FAILURE(HR_NAME, THROW_MESSAGE) \
        if(FAILED(HR_NAME)) { \
            throw THROW_MESSAGE; \
        }
#endif // FAILURE

#ifdef FAILURE
    #ifndef FAILURE_HR
        #define FAILURE_HR(MESSAGE) \
            FAILURE(hr, MESSAGE)
    #endif 
#endif // FAILURE_HR

std::string GetString(IMFActivate* pDevice);

int main() {
    setlocale(0, "");
    try {
        IMFAttributes* pAtr = nullptr;
        HRESULT hr = MFStartup(MF_VERSION); // Инициализация Media Foundation
        FAILURE_HR("во время инициализации Media Foundation пройзошел сбой!");

        std::cout << "Слава богу что Media Foundation успешно инициализировался!" << std::endl;

        hr = MFCreateAttributes(&pAtr, 1);
        FAILURE_HR("во время создания атрибута возникла дрянь!");

        hr = pAtr->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
        FAILURE_HR("во время привязки GUID пройзошла ошибка!");

        IMFActivate** ppDev = nullptr;
        UINT32 count{ 0 };
        hr = MFEnumDeviceSources(pAtr, &ppDev, &count);
        FAILURE_HR("во время пойска пройзошла ошибка!");
        if (count == 0)
        {
            throw "не было найдено не единого устройства с таким атрибутом!";
        }

        for (int i = 0; i < count; i++)
        {
            std::cout << "Name of [" << i << "] is: " << GetString(ppDev[i]) << std::endl;
            ppDev[i]->Release();
        }
        
        CoTaskMemFree(ppDev);
        pAtr->Release();
    }
    catch (const char* err_msg)
    {
        std::cerr << "Черт, " << err_msg << std::endl;
    }

    MFShutdown();

    return 0;
}

std::string GetString(IMFActivate* pDevice)
{
    WCHAR* friendlyName = nullptr;
    UINT32 nameLength = 0;

    HRESULT hr = pDevice->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &friendlyName, &nameLength);

    if (FAILED(hr))
    {
        return "";
    }

    std::wstring wstr(friendlyName);
    CoTaskMemFree(friendlyName);
    std::string str(wstr.begin(), wstr.end());
    return str;
}