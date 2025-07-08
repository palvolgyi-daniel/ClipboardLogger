#ifndef IO_H
#define IO_H

#include <string>
#include <windows.h>

void EnsureHistoryFolderExists();
std::string getTimestampedFilename(const std::string& ext);
bool SaveBitmapToJPEG(HBITMAP hBitmap, const char* filename, int quality = 85);
void SaveTextToFile(const std::string& text, const std::string& filename);

#endif
