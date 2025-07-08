#include "Clipboard.h"
#include "IO.h"
#include <thread>
#include <chrono>
#include <iostream>

int main(){
    EnsureHistoryFolderExists();

    bool firstRun = true;
    std::string lastImageChecksum;
    std::string lastTextChecksum;
    ClipboardContent content = GetClipboardContent();

    if(!content.imageData.empty()) lastImageChecksum = content.imageChecksum; // to avoid saving data from the clipboard that existed prior to program startup
    if(!content.text.empty()) lastTextChecksum = content.textChecksum;

    while(true){
        content = GetClipboardContent();

        if(!content.imageData.empty() && content.imageChecksum != lastImageChecksum){
            std::string filename = getTimestampedFilename("jpg");
            SaveBitmapToJPEG(content.hBitmap, filename.c_str());
            std::cout << "[Saved image] " << filename << "\n";
            lastImageChecksum = content.imageChecksum;
        }

        if(!content.text.empty() && content.textChecksum != lastTextChecksum){
            std::string filename = getTimestampedFilename("txt");
            SaveTextToFile(content.text, filename);
            std::cout << "[Saved text] " << filename << "\n";
            lastTextChecksum = content.textChecksum;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}
