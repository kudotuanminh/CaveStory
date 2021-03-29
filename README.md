# ntm's Cave Story

This is a remake of Studio Pixel's Cave Story in C++ and SDL2 library, based on a guide by Limeoats.

My project for INT2215 6 class - Advanced Programming, lectured by [@chauttm](https://github.com/chauttm "chauttm's GitHub").

# Dependencies

## Software

I use _VSCode_ on Windows, compiled with _mingw-w64-gcc-8.1.0-x86_64-posix-seh_ in default _VSCode_'s debugging.
I ported the maps for the game with [Tiled](https://www.mapeditor.org/)

## External Libraries

Libraries required to compile are:

- [SDL2-2.0.14-x86_64-w64-mingw32](https://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz)
- [SDL2_image-2.0.5-x86_64-w64-mingw32](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz)
- ~~[TinyXML2](https://github.com/leethomason/tinyxml2)~~ Migrated to [pugixml-1.11.4](https://github.com/zeux/pugixml/releases/) since I cannot get TinyXML2 to work ==

```cpp
//	Uncomment this to switch to header-only version
#define PUGIXML_HEADER_ONLY
```

# Credit

- Limeoats's [Course](https://www.youtube.com/playlist?list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa "Link to original YouTube playlist")
- Assets by [cavestory.org](http://cavestory.org/)
