CC=C:\MinGW\mingw64\bin\g++
LDFLAGS=-LSFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -std=c++11
CFLAGS=-c -std=c++11 -Iheaders -ISFML\include -DSFML_STATIC

define OBJECTFILES
objs/main.o\
objs/ImageProcessing.o\
objs/ColorUtils.o\
objs/Blur.o\
objs/Contrast.o\
objs/Border.o\
objs/ColorSet.o\
objs/RGBBalance.o\
objs/SetSimplify.o\
objs/TransformStack.o\
objs/ModeBlur.o\
objs/SaveImage.o\
objs/SetBrightness.o
endef

all: process.exe resize.exe

resize.exe: objs/resize.o objs/Blur.o objs/ColorUtils.o
	$(CC) objs/resize.o objs/Blur.o objs/ColorUtils.o -o resize.exe $(LDFLAGS)

process.exe: $(OBJECTFILES)
	$(CC) $(OBJECTFILES) -o process.exe $(LDFLAGS)

objs/resize.o: sources/resize.cpp
	$(CC) sources/resize.cpp -o objs/resize.o $(CFLAGS)

objs/main.o: sources/main.cpp
	$(CC) sources/main.cpp -o objs/main.o $(CFLAGS)

objs/ImageProcessing.o: sources/ImageProcessing.cpp
	$(CC) sources/ImageProcessing.cpp -o objs/ImageProcessing.o $(CFLAGS)

objs/ColorUtils.o: sources/ColorUtils.cpp
	$(CC) sources/ColorUtils.cpp -o objs/ColorUtils.o -lm $(CFLAGS)

objs/Blur.o: sources/Blur.cpp
	$(CC) sources/Blur.cpp -o objs/Blur.o $(CFLAGS)

objs/Contrast.o: sources/Contrast.cpp
	$(CC) sources/Contrast.cpp -o objs/Contrast.o $(CFLAGS)

objs/Border.o: sources/Border.cpp
	$(CC) sources/Border.cpp -o objs/Border.o $(CFLAGS)

objs/ColorSet.o: sources/ColorSet.cpp
	$(CC) sources/ColorSet.cpp -o objs/ColorSet.o $(CFLAGS)

objs/RGBBalance.o: sources/RGBBalance.cpp
	$(CC) sources/RGBBalance.cpp -o objs/RGBBalance.o $(CFLAGS)

objs/SetSimplify.o: sources/SetSimplify.cpp
	$(CC) sources/SetSimplify.cpp -o objs/SetSimplify.o $(CFLAGS)

objs/TransformStack.o: sources/TransformStack.cpp
	$(CC) sources/TransformStack.cpp -o objs/TransformStack.o $(CFLAGS)

objs/ModeBlur.o: sources/ModeBlur.cpp
	$(CC) sources/ModeBlur.cpp -o objs/ModeBlur.o $(CFLAGS)

objs/SaveImage.o: sources/SaveImage.cpp
	$(CC) sources/SaveImage.cpp -o objs/SaveImage.o $(CFLAGS)

objs/SetBrightness.o: sources/SetBrightness.cpp
	$(CC) sources/SetBrightness.cpp -o objs/SetBrightness.o $(CFLAGS)
