#ifndef CTIMER_HPP
#define CTIMER_HPP

#include <bitset>
#include <unordered_map>
#include <condition_variable>
#include <mutex>
#include <chrono>

namespace Evolution::Manager
{
    template <typename Time>
    class Timer
    {
        struct NotifyCallback
        {
            shortBool repeat;
            uint32_t timerValue, timerBackup;
            NotifyAction notifyAction;
        };

    public:
        Timer();
        ~Timer() = default;
        Timer(const Timer &) = delete;
        Timer &operator=(const Timer &) = delete;
        Timer(Timer &&) = delete;
        Timer &operator=(Timer &&) = delete;

        // Registering for the timer notification
        NFResolution32 Register(NFResolution32, NotifyAction, shortBool repeat = 0);

        // To remove particular timer id from the list
        void DeRegister(NFResolution32);

        // To stop the timer.. Mandatory once we created the object of this class
        void Stop();

    private:
        std::unique_ptr<std::thread> m_timerThread, m_notifierThread;
        std::unordered_map<uint8_t, NotifyCallback> m_subscriber;
        shortBool m_IsIntervalFinished, m_TimerStop;
        NFResolution32 m_subscriptionId;
        std::condition_variable m_cvInterval;
        std::mutex m_mutexInterval;

        // Starts the timer.. it will sleep for some time and notify
        void Start();
        // Performs the respective functionality once timer value finished
        void Notify();
    };

    template <typename Time>
    Timer<Time>::Timer() : m_IsIntervalFinished(0), m_TimerStop(0), m_subscriptionId(0)
    {
        m_timerThread = std::make_unique<std::thread>(&Timer::Start, this);
        m_notifierThread = std::make_unique<std::thread>(&Timer::Notify, this);
    }

    template <typename Time>
    void Timer<Time>::Stop()
    {
        m_subscriber.clear();

        m_TimerStop.set();
        m_IsIntervalFinished.set();
        m_cvInterval.notify_all();

        if (nullptr != m_timerThread && m_timerThread->joinable())
        {
            m_timerThread->join();
        }
        if (nullptr != m_notifierThread && m_notifierThread->joinable())
        {
            m_notifierThread->join();
        }
    }

    template <typename Time>
    void Timer<Time>::Start()
    {
        while (!m_TimerStop.all())
        {
            if (!m_IsIntervalFinished.all())
            {
                std::unique_lock<std::mutex> lock(m_mutexInterval);
                std::this_thread::sleep_for(Time(DefaultTime));
                m_IsIntervalFinished.set();
            }
            m_cvInterval.notify_all();
        }
    }

    template <typename Time>
    void Timer<Time>::Notify()
    {
        while (!m_TimerStop.all())
        {
            {
                std::unique_lock<std::mutex> lock(m_mutexInterval);
                m_cvInterval.wait(lock, [&]
                                  { return m_IsIntervalFinished.all(); });
                m_IsIntervalFinished.reset();
            }

            for (auto &it : m_subscriber)
            {
                it.second.timerValue -= DefaultTime;
                if (it.second.timerValue == 0)
                {
                    it.second.notifyAction();
                    if (!it.second.repeat.all())
                        m_subscriber.erase(it.first);

                    else
                        it.second.timerValue = it.second.timerBackup;
                }
            }
        }
    }

    template <typename Time>
    NFResolution32 Timer<Time>::Register(NFResolution32 time, NotifyAction callback, shortBool repeat)
    {
        m_subscriptionId++;
        m_subscriber[m_subscriptionId].repeat = repeat;
        m_subscriber[m_subscriptionId].timerBackup = time;
        m_subscriber[m_subscriptionId].timerValue = std::move(time);
        m_subscriber[m_subscriptionId].notifyAction = std::move(callback);

        return m_subscriptionId;
    }

    template <typename Time>
    void Timer<Time>::DeRegister(NFResolution32 subId)
    {
        m_subscriber.erase(subId);
    }
}

#endif