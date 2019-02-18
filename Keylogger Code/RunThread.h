/*
Jacob Brown jmb7438@rit.edu
Geoffrey Kanteles gdk7676@rit.edu
*/

#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <thread>
#include <chrono>

class RunThread
{
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L;
    long repeat_count = -1L;
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;

    /**
        Sleeps and runs the timer thread
        @return void
    */
    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();
    }
    /**
        Function passed to thread
        @return void
    */
    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Alive) SleepAndRun();
        else
            while(repeat_count--) SleepAndRun();
    }

public:
    static const long Infinite = -1L;

    //Constructors for this class
    RunThread(){}
    RunThread(const std::function<void(void)> &f) : funct(f) {}
    RunThread(const std::function<void(void)> &f, const unsigned long &i, const long repeat = RunThread::Infinite) : funct(f), interval(std::chrono::milliseconds(i)), CallNumber(repeat) {}

    /**
        Start thread
        @param Async imports async tag
        @return void
    */
    void Start(bool Async = true)
    {
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            ThreadFunc();
    }

    /**
        Stop thread
        @return void
    */
    void Stop()
    {
        Alive = false;
        Thread.join();
    }

    /**
        Sets function attribute in class
        @param f function to import
        @return void
    */
    void SetFunction(const std::function<void(void)> &f)
    {
        funct = f;
    }

    /**
        Checks if thread is alive
        @return void
    */
    bool IsAlive() const
    {
        return Alive;
    }

    /**
        Sets a repeat count
        @param r repeat count to set
        @return void
    */
    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }

    /**
        Get count left
        @return void
    */
    long GetLeftCount() const
    {
        return repeat_count;
    }

    /**
        Return call number
        @return callnumber
    */
    long RepeatCount() const
    {
      return CallNumber;
    }

    /**
        Set an interval
        @param i interval to set
        @return void
    */
    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }

    /**
        return interval
        @return interval
    */
    unsigned long Interval() const
    {
        return interval.count();
    }

    /**
        Set function
        @return function
    */
    const std::function<void(void)> &Function() const
    {
        return funct;
    }
};

#endif // RUNTHREAD_H

