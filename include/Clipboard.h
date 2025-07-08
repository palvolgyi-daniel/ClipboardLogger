#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <string>
#include <vector>
#include <windows.h>

struct ClipboardContent{
    std::string text;
    std::string textChecksum;
    HBITMAP hBitmap = nullptr;
    std::vector<unsigned char> imageData;
    std::string imageChecksum;
};

ClipboardContent GetClipboardContent();

#endif
