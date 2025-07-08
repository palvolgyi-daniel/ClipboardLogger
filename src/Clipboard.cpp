#include "Clipboard.h"
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <winuser.h>
#include <objidl.h>
#include <gdiplus.h>
#include <shlwapi.h>

static std::string CalculateChecksum(const std::vector<unsigned char>& data){
    unsigned int hash = 2166136261u;
    for(unsigned char byte : data){
        hash ^= byte;
        hash *= 16777619;
    }
    std::ostringstream oss;
    oss << std::hex << hash;
    return oss.str();
}

static std::string CalculateChecksum(const std::string& data){
    return CalculateChecksum(std::vector<unsigned char>(data.begin(), data.end()));
}

ClipboardContent GetClipboardContent(){
    ClipboardContent result;
    if(!OpenClipboard(nullptr)) return result;

    // text
    HANDLE hText = GetClipboardData(CF_TEXT);
    if(hText){
        char* text = static_cast<char*>(GlobalLock(hText));
        if(text){
            result.text = std::string(text);
            result.textChecksum = CalculateChecksum(result.text);
            GlobalUnlock(hText);
        }
    }

    // image
    HANDLE hImage = GetClipboardData(CF_BITMAP);
    if(hImage){
        HBITMAP hBitmap = (HBITMAP)hImage;
        result.hBitmap = hBitmap;

        BITMAP bmp;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);
        int width = bmp.bmWidth;
        int height = bmp.bmHeight;
        int size = width * height * 4;

        std::vector<unsigned char> buffer(size);
        GetBitmapBits(hBitmap, size, buffer.data());
        result.imageData = buffer;
        result.imageChecksum = CalculateChecksum(buffer);
    }

    CloseClipboard();
    return result;
}
