# 📋 Clipboard Watcher

A lightweight C++ program that runs in the background and **automatically saves clipboard content**, such as:

- 🖼️ Images (as `.jpg`)
- 📝 Text (as `.txt`)

It checks for new clipboard content periodically (every 250ms).

---

## ✨ Features

- Runs quietly in the background (console-based)
- Saves clipboard **images as compressed JPEG**
- Saves clipboard **text as UTF-8 plain text**
- Creates a time-stamped file for each clipboard entry
- Saves files in `History/` folder

---

## 🧩 Dependencies

| Library             | Usage                             |
|---------------------|-----------------------------------|
| **WinAPI**          | Clipboard access, file operations |
| **GDI+**            | Bitmap and image decoding         |
| **stb_image_write** | Image writing (JPEG/PNG/BMP)      |

> `stb_image_write.h` is included in the `include/` folder.

---

## 🛠️ Building

### 📦 Requirements

- Windows OS  
- [MSYS2](https://www.msys2.org/) (recommended) with:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc \
          mingw-w64-ucrt-x86_64-make \
          mingw-w64-ucrt-x86_64-gdiplus
```

### ⚙️ Makefile Commands

| Command              | Description                      |
|----------------------|----------------------------------|
| `mingw32-make build` | Compile the project              |
| `mingw32-make run`   | Run the compiled binary          |
| `mingw32-make clean` | Remove compiled outputs          |

---

## 📂 Output Files

Clipboard contents are saved in the `History/` folder in the following format:

- Images: `2025-02-25 14-35-30.jpg`  
- Text: `2025-02-25 14-35-30.txt`

Files are only saved if clipboard content has changed since last check.

---

## 📜 License

This project uses the [stb_image_write](https://github.com/nothings/stb) library (public domain / MIT) and is free to use or modify.

---

## 🙌 Acknowledgements

- [nothings/stb](https://github.com/nothings/stb) for `stb_image_write.h`  
- Microsoft Windows API and GDI+
