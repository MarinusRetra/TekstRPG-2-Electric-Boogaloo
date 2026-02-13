If you just want to play the game, you only need Dude.exe and BearlibTerminal.dll
It's found in the build folder. (If there is no build or out folder the game isn't finished yet.)

If you want to build it yourself you need:
1. CMake > 3.1.0.
2. BearLibTerminal. (http://foo.wyrd.name/en:bearlibterminal#download)
3. REXSpeeder. for reading .xp files (https://github.com/pyridine/REXSpeeder)
4. ZLIB. (https://zlib.net/)
5. Put your libraries in one folder.
6. The names of your libraries should match: BearLibTerminal, REXSpeeder, ZLIB (if the names are differenct just rename them).

#
Go to CMakeLists.txt and set the LIBRARY_FOLDER to where your libraries are installed.
~~~Cmake
set(LIBRARY_FOLDER ../Librarby) 
~~~
#

If anything doesn't work let me know, I'm pretty new with all this and would love to know what breaks.

