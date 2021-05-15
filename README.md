# ntm's Cave Story

This is a remake of Studio Pixel's Cave Story in C++ with SDL2 library, based on a guide by Limeoats.

My project for INT2215 6 class - Advanced Programming, lectured by [@chauttm](https://github.com/chauttm "chauttm's GitHub") and [@ndinhtuan](https://github.com/ndinhtuan "ndinhtuan's GitHub").

# Dependencies

## Software

I use [_VSCode_](https://code.visualstudio.com/download) on Windows, compiled with [_mingw-w64-gcc-8.1.0-x86_64-posix-seh_](https://sourceforge.net/projects/mingw-w64/) in default _VSCode_'s debugging.
I ported the maps for the game with [Tiled](https://www.mapeditor.org/)

## External Libraries

Libraries required for compilation are:

- [SDL2-2.0.14-x86_64-w64-mingw32](https://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz)
- [SDL2_image-2.0.5-x86_64-w64-mingw32](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz)
- ~~[TinyXML2](https://github.com/leethomason/tinyxml2)~~ Migrated to [pugixml-1.11.4](https://github.com/zeux/pugixml/releases/) since I cannot get TinyXML2 to work ==

```cpp
//	Uncomment this to switch to header-only version
#define PUGIXML_HEADER_ONLY
```

## Compile and Run

To start the game, just hit F5 (or any key-binding according to your _VSCode_'s global setting) to start debugging. Remember to place all the listed dependencies (with a leading '.' letter, follows by **the exact name**) to the _root directory_ of the project. Required Dlls are already included in the "_build_" folder.

## Some highlights of what this code is capable of

- Since the maps weren't hard-coded to the source and made by a map editor, you can easily scale up (with any extra tilesets, spritesheets linked to that map) without modifying the source code itself.
-

# Credit

- Limeoats's [Tutorial](https://www.youtube.com/playlist?list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa "Link to original YouTube playlist")
- Assets by [cavestory.org](http://cavestory.org/)
