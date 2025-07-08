#include "IO.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void EnsureHistoryFolderExists(){
    std::filesystem::create_directory("History");
}

std::string getTimestampedFilename(const std::string& ext){
    time_t now = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "History/%Y-%m-%d_%H-%M-%S", &localTime);
    return std::string(buffer) + "." + ext;
}

void SaveTextToFile(const std::string& text, const std::string& filename){
    std::ofstream file(filename);
    if(file.is_open()){
        file << text;
        file.close();
    }
}

bool SaveBitmapToJPEG(HBITMAP hBitmap, const char* filename, int quality){
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    int width = bmp.bmWidth;
    int height = bmp.bmHeight;

    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // negative for top-down DIB
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;

    int rowSize = ((bi.biBitCount * width + 31) / 32) * 4; // aligned row size
    int dataSize = rowSize * height;

    std::vector<unsigned char> buffer(dataSize);

    HDC hdc = GetDC(nullptr);
    int res = GetDIBits(hdc, hBitmap, 0, height, buffer.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    ReleaseDC(nullptr, hdc);

    if(res == 0) return false; // failed to get bits

    std::vector<unsigned char> rgbData(width * height * 3);

    for(int y = 0; y < height; y++){
        memcpy(&rgbData[y * width * 3], &buffer[y * rowSize], width * 3);
    }

    // swapping BGR to RGB, otherwise discolored
    for(int i = 0; i < width * height * 3; i += 3){
        std::swap(rgbData[i], rgbData[i + 2]);
    }

    return stbi_write_jpg(filename, width, height, 3, rgbData.data(), quality) != 0;
}
