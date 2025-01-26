#include "DeckLinkAPI.h"
#include "DeckLinkAPIDispatch_v10_8.cpp"
#include <iostream>

int main(int argc, char *argv[])
{
    IDeckLinkIterator *deckLinkIterator = CreateDeckLinkIteratorInstance();
    if (deckLinkIterator == nullptr)
    {
        std::cerr << "Could not create DeckLink iterator. Are you sure a Decklink device is connected?" << std::endl;
        return 1;
    }

    IDeckLink *deckLink;
    while (deckLinkIterator->Next(&deckLink) == S_OK)
    {
        // Do something with deckLink
        const char *deviceName;
        if (deckLink->GetDisplayName(&deviceName) == S_OK)
        {
            // Device is found
            std::cout << deviceName << std::endl;
        }
        IDeckLinkAPIInformation *apiInfo = CreateDeckLinkAPIInformationInstance();
        if (apiInfo == nullptr)
        {
            std::cerr << "Could not create DeckLink API information instance." << std::endl;
            return 1;
        }
        else
        {
            // Do something with apiInfo
            const char *apiVersion;
            if (apiInfo->GetString(BMDDeckLinkAPIVersion, &apiVersion) == S_OK)
            {
                std::cout << "API version: " << apiVersion << std::endl;
            }
            else
            {
                std::cerr << "Could not get API version." << std::endl;
            }
            apiInfo->Release();
        }

        IDeckLinkStatus *deckLinkStatus;
        deckLink->QueryInterface(IID_IDeckLinkStatus, (void **)&deckLinkStatus);
        if (deckLinkStatus == nullptr)
        {
            std::cerr << "Could not create DeckLink status instance." << std::endl;
            return 1;
        }
        else
        {
            int64_t deviceTemp = -1;
            if (deckLinkStatus->GetInt(bmdDeckLinkStatusDeviceTemperature, &deviceTemp) == S_OK)
            {
                std::cout << "Device Temperature: " << deviceTemp << " °C" << std::endl;
            }
            else
            {
                std::cerr << "Could not get device temperature." << std::endl;
            }

            int64_t pcieLinkWidth = -1;
            int64_t pcieLinkSpeed = -1;

            if ((deckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkWidth, &pcieLinkWidth) == S_OK) && (deckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkSpeed, &pcieLinkSpeed) == S_OK))
            {
                std::cout << "PCIe info: " << pcieLinkSpeed << " Gb/s" << " (" << pcieLinkWidth << " lanes)" << std::endl;
            }

            int64_t videoDisplayMode = -1;
            int64_t videoPixelFormat = -1;
            int64_t videoColorSpace = -1;

            if ((deckLinkStatus->GetInt(bmdDeckLinkStatusCurrentVideoInputMode, &videoDisplayMode) == S_OK) && (deckLinkStatus->GetInt(bmdDeckLinkStatusCurrentVideoOutputMode, &videoPixelFormat) == S_OK) && (deckLinkStatus->GetInt(bmdDeckLinkStatusDetectedVideoInputColorspace, &videoColorSpace) == S_OK))
            {
                std::cout << "Video display mode:" << videoDisplayMode << " (" << videoPixelFormat << ")" << std::endl;
            }
            else
            {
                std::cerr << "Could not get video display mode. Are you sure a video input is connected?" << std::endl;
            }

            deckLinkStatus->Release();
        }

        IDeckLinkProfileAttributes *profileAttributes;
        deckLink->QueryInterface(IID_IDeckLinkProfileAttributes, (void **)&profileAttributes);
        if (profileAttributes == nullptr)
        {
            std::cerr << "Could not create DeckLink profile attributes instance." << std::endl;
            return 1;
        }
        else
        {
            // Do something with profileAttributes
            int64_t persistentID = -1;
            if (profileAttributes->GetInt(BMDDeckLinkPersistentID, &persistentID) == S_OK)
            {
                std::cout << "Device ID: " << persistentID << std::endl;
            }
            profileAttributes->Release();
        }

        // BMDDeckLinkPersistentID
        deckLink->Release();
    }

    deckLinkIterator->Release();
    return 0;
}