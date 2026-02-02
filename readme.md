If you just want to play the game, you only need Dude.exe and BearlibTerminal.dll
It's found in the build folder. (If there is no build folder the game isn't finished yet.)

If you want to build it yourself you need:
1. CMake > 3.1.0.
2. A C++ compiler (I'm using MSVC because I use Visual studio).
3. BearLibTerminal 0.15.8. (http://foo.wyrd.name/en:bearlibterminal#download)
4. REXSpeeder for reading .xp files.
5. REXSpeeder depends on ZLib.
6. If everything is installed set BLT_FLD to the path of your BearlibTerminal folder.
(You don't have to edit the cmake files if you put all the libraries in a folder called librarby in the same directory as the project.)

[These instructions are temporary and the libraries will later be listed as submodules along with changes to the CmakeLists.txt so that it works for everyone from the start.]

#
Go to CMakeLists.txt and set the BLT_FLD variable to where your BearLibTerminal is installed.
~~~Cmake
set(BLT_FLD YOUR PATH HERE)
~~~
#

If anything doesn't work let me know, I'm pretty new with all this and would love to know what breaks.

