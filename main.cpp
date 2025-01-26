#include "DeckLinkAPI.h"
#include "DeckLinkAPIDispatch_v10_8.cpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    std::unique_ptr<IDeckLinkIterator> pDeckLinkIterator(CreateDeckLinkIteratorInstance());

    if (pDeckLinkIterator == nullptr)
    {
        std::cerr << "Could not create DeckLink iterator. Are you sure a Decklink device is connected?" << std::endl;
        return 1;
    }

    std::shared_ptr<IDeckLink> pDeckLink;
    IDeckLink* pRawDecklinkPtr = pDeckLink.get();

    while (pDeckLinkIterator->Next(&pRawDecklinkPtr) == S_OK)
    {
        std::string deviceName;
        const char* cstrDeviceName = deviceName.c_str();

        if (pDeckLink->GetDisplayName(&cstrDeviceName) == S_OK)
        {
            // Device is found
            std::cout << deviceName << std::endl;
        }

        IDeckLinkAPIInformation* pApiInfo = CreateDeckLinkAPIInformationInstance();

        if (pApiInfo == nullptr)
        {
            std::cerr << "Could not create DeckLink API information instance." << std::endl;
            return 1;
        }
        else
        {
            std::string apiVersion;
            const char* cstrApiVersion = apiVersion.c_str();

            if (pApiInfo->GetString(BMDDeckLinkAPIVersion, &cstrApiVersion) == S_OK)
            {
                std::cout << "API version: " << apiVersion << std::endl;
            }
            else
            {
                std::cerr << "Could not get API version." << std::endl;
            }
            pApiInfo->Release();
        }

        IDeckLinkStatus* pDeckLinkStatus;
        pDeckLink->QueryInterface(IID_IDeckLinkStatus, reinterpret_cast<void **>(&pDeckLinkStatus));

        if (pDeckLinkStatus == nullptr)
        {
            std::cerr << "Could not create DeckLink status instance." << std::endl;
            return 1;
        }
        else
        {
            int64_t deviceTemp = -1;
            
            if (pDeckLinkStatus->GetInt(bmdDeckLinkStatusDeviceTemperature, &deviceTemp) == S_OK)
            {
                std::cout << "Device Temperature: " << deviceTemp << " °C" << std::endl;
            }
            else
            {
                std::cerr << "Could not get device temperature." << std::endl;
            }

            int64_t pcieLinkWidth = -1;
            int64_t pcieLinkSpeed = -1;

            if ((pDeckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkWidth, &pcieLinkWidth) == S_OK) && (pDeckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkSpeed, &pcieLinkSpeed) == S_OK))
            {
                std::cout << "PCIe info: " << pcieLinkSpeed << " Gb/s" << " (" << pcieLinkWidth << " lanes)" << std::endl;
            }

            int64_t videoDisplayMode = -1;
            int64_t videoPixelFormat = -1;
            int64_t videoColorSpace = -1;

            if ((pDeckLinkStatus->GetInt(bmdDeckLinkStatusCurrentVideoInputMode, &videoDisplayMode) == S_OK) && (pDeckLinkStatus->GetInt(bmdDeckLinkStatusCurrentVideoOutputMode, &videoPixelFormat) == S_OK) && (pDeckLinkStatus->GetInt(bmdDeckLinkStatusDetectedVideoInputColorspace, &videoColorSpace) == S_OK))
            {
                std::cout << "Video display mode:" << videoDisplayMode << " (" << videoPixelFormat << ")" << std::endl;
            }
            else
            {
                std::cerr << "Could not get video display mode. Are you sure a video input is connected?" << std::endl;
            }

            pDeckLinkStatus->Release();
        }

        IDeckLinkProfileAttributes* pProfileAttributes;
        pDeckLink->QueryInterface(IID_IDeckLinkProfileAttributes, reinterpret_cast<void **>(&pProfileAttributes));

        if (pProfileAttributes == nullptr)
        {
            std::cerr << "Could not create DeckLink profile attributes instance." << std::endl;
            return 1;
        }
        else
        {
            int64_t persistentID = -1;

            if (pProfileAttributes->GetInt(BMDDeckLinkPersistentID, &persistentID) == S_OK)
            {
                std::cout << "Device ID: " << persistentID << std::endl;
            }
            else
            {
                std::cerr << "Could not get device ID." << std::endl;
            }

            pProfileAttributes->Release();
        }

        pDeckLink->Release();
    }

    pDeckLinkIterator->Release();
    return 0;
}