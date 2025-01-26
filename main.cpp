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
        const char* deviceName;
        if (deckLink->GetDisplayName(&deviceName) == S_OK)
        {
            std::cout << "Found DeckLink device with name: " << deviceName << std::endl;
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
            const char* apiVersion;
            if (apiInfo->GetString(BMDDeckLinkAPIVersion, &apiVersion) == S_OK)
            {
                std::cout << "DeckLink API version: " << apiVersion << std::endl;
            }
            apiInfo->Release();
        }

        IDeckLinkStatus *deckLinkStatus;
        deckLink->QueryInterface(IID_IDeckLinkStatus, (void**)&deckLinkStatus);
        if (deckLinkStatus == nullptr)
        {
            std::cerr << "Could not create DeckLink status instance." << std::endl;
            return 1;
        }
        else
        {
            int64_t deviceTemp;
            if (deckLinkStatus->GetInt(bmdDeckLinkStatusDeviceTemperature, &deviceTemp) == S_OK)
            {
                std::cout << "DeckLink device temperature: " << deviceTemp << " °C" << std::endl;
            }

            int64_t pcieLinkWidth;
            int64_t pcieLinkSpeed;

            if ((deckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkWidth, &pcieLinkWidth) == S_OK) && (deckLinkStatus->GetInt(bmdDeckLinkStatusPCIExpressLinkSpeed, &pcieLinkSpeed) == S_OK))
            {
                std::cout << "DeckLink device PCIe link speed: " << pcieLinkSpeed << " Gb/s" << std::endl;
                std::cout << "DeckLink device PCIe link width: " << pcieLinkWidth << " lanes" << std::endl;
            }


            deckLinkStatus->Release();
        }

        IDeckLinkProfileAttributes *profileAttributes;
        deckLink->QueryInterface(IID_IDeckLinkProfileAttributes, (void**)&profileAttributes);
        if (profileAttributes == nullptr)
        {
            std::cerr << "Could not create DeckLink profile attributes instance." << std::endl;
            return 1;
        }
        else
        {
            // Do something with profileAttributes
            int64_t persistentID = 0;
            if (profileAttributes->GetInt(BMDDeckLinkPersistentID, &persistentID) == S_OK)
            {
                std::cout << "DeckLink device persistent ID: " << persistentID << std::endl;
            }
            profileAttributes->Release();
        }

        // BMDDeckLinkPersistentID
        deckLink->Release();
    }

    deckLinkIterator->Release();
    return 0;
}