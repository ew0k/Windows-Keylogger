/*
Jacob Brown jmb7438@rit.edu
Geoffrey Kanteles gdk7676@rit.edu
*/

#ifndef EXTRAFUNCTS_H
#define EXTRAFUNCTS_H

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

namespace Helper
{
    template <class T>

    std::string ToString(const T &);

    struct DateTime
    {
        DateTime()
        {
            time_t ms;
            time(&ms);

            struct tm *info = localtime(&ms);

            D = info->tm_mday;
            m = info->tm_mon + 1;
            y = 1900 + info->tm_year;
            M = info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        }
        DateTime(int D, int m, int y, int M, int H, int S) : D(D), m(m), y(y), M(M), H(H), S(S) {}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), M(0), H(0), S(0) {}

        DateTime Now() const
        {
            return DateTime();
        }

        int D, m, y, M, H, S;

        /**
            Gets the date and returns it as a string
            @return a string including the date
        */
        std::string GetDateString() const
        {
            return std::string(D < 10 ? "0" : "") + ToString(D) +
                    std::string(m < 10 ? ".0" : ".") + ToString(m) +
                    "." + ToString(y);
        }

        /**
            Gets the time and returns it as a string
            @param sep separator used for the returned string
            @return a string including the time
        */
        std::string GetTimeString(const std::string &sep = ":") const
        {
            return std::string(H < 10 ? "0" : "") + ToString(H) + sep +
                    std::string(M < 10 ? "0" : "") + ToString(M) + sep +
                    std::string(S < 10 ? sep : "") + ToString(S);
        }

        /**
            Gets the date and time and returns it as a string
            @param sep separator used for the returned string
            @return a string including the date
        */
        std::string GetDateTimeString(const std::string &sep = ":") const
        {
            return GetDateString() + " " + GetTimeString(sep);
        }
    };

    template <class T>

    /**
        return a string given any input
        @param e input to convert
        @return string of the given input
    */
    std::string ToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }

    /**
        Write to a log
        @param s stream to write
        @return void
    */
    void WriteAppLog(const std::string &s)
    {
        std::ofstream file("AppLog.txt", std::ios::app);
        file << "[" << Helper::DateTime().GetDateTimeString() << "]" << "\n" << s << std::endl << "\n";
        file.close();
    }
}

#endif // EXTRAFUNCTS_H

