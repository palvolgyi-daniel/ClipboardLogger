STB_HEADER = include/stb_image_write.h
EXECUTABLE = "ClipboardLogger.exe"
SRC = src/main.cpp src/Clipboard.cpp src/IO.cpp
INC = -Iinclude

build: $(STB_HEADER)
	g++ -std=c++17 $(INC) -o $(EXECUTABLE) $(SRC) -lgdi32

run:
	./$(EXECUTABLE)

all: build run

clean:
	del /Q $(EXECUTABLE) 2>nul || rm -f $(EXECUTABLE)

$(STB_HEADER):
	curl -L -o $(STB_HEADER) https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
