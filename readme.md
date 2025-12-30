If you just want to play the game, you only need Dude.exe and BearlibTerminal.dll
It's found in the build folder. (If there is no build folder the game isn't finished yet.)

If you want to build it yourself you need:
1. CMake > 3.1.0.
2. MSVC (You already have this compiler with visual studio and VScode).
3. BearLibTerminal 0.15.8. (http://foo.wyrd.name/en:bearlibterminal#download)
4. If everything is installed set BLT_FLD to the path of your BearlibTerminal folder.
#
Terminal:
```bash
cmake -S . -B build -D BLT_FLD="Whatever your path is to BearlibTerminal_0.15.8"
```
#
Or go to CMakeLists.txt and change
~~~CMake
set(BLT_FLD "" CACHE PATH "../Librarby/BearLibTerminal_0.15.8")
~~~
to
~~~Cmake
set(BLT_FLD [YOUR PATH HERE])
~~~
#

If anything doesn't work let me know, I'm pretty new with all this and woul love to know what broke.

