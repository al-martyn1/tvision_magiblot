#ifndef TVISION_EVENTS_H
#define TVISION_EVENTS_H

#define Uses_TEvent
#include <tvision/tv.h>
#include <atomic>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <tvision/compat/windows/windows.h>
#endif

namespace tvision
{

#if defined(TV_BARE_METAL)

//TODO: !!! Dirty implementation, need rewrite

class TBareMetalEventHandle
{
    constexpr static const size_t s_totalHandles = 32;
    // -1 - unassigned, 0 - non-signaled, 1 - signaled
    static int s_handles[s_totalHandles]; // = {-1};

public:

    using SysHandle = size_t;

    constexpr static const size_t invalidHandleValue = (size_t)-1;


    static SysHandle create() noexcept
    {
        for(auto i=0u; i!=s_totalHandles; ++i)
        {
            if (s_handles[i]<0)
            {
                s_handles[i] = 0;
                return i;
            }
        }

        return invalidHandleValue;
    }

    static bool valid(SysHandle h) noexcept
    {
        if (h<s_totalHandles)
        {
            return s_handles[h]>=0;
        }

        return false;
    }

    static bool close(SysHandle h) noexcept
    {
        if (h<s_totalHandles)
        {
            s_handles[h] = -1;
            return true;
        }
        else
        {
            //TODO: !!! Dirty implementation, need rewrite (assert here?)
            return false;
        }
    }

    static void signal(SysHandle h) noexcept
    {
        if (h<s_totalHandles)
        {
            s_handles[h] = 1;
        }
        else
        {
            //TODO: !!! Dirty implementation, need rewrite (assert here?)
        }
    }

    static void clear(SysHandle h) noexcept
    {
        if (h<s_totalHandles)
        {
            s_handles[h] = 0;
        }
        else
        {
            //TODO: !!! Dirty implementation, need rewrite (assert here?)
        }
    }

    static bool signaled(SysHandle h) noexcept
    {
        if (h<s_totalHandles)
        {
            return s_handles[h]!=0;
        }
        else
        {
            //TODO: !!! Dirty implementation, need rewrite (assert here?)
        }

        return true;
    }
    
};


#endif


#if defined(TV_BARE_METAL)
using SysHandle = TBareMetalEventHandle::SysHandle;
#elif defined(_WIN32)
using SysHandle = HANDLE;
#else
using SysHandle = int;
#endif

struct SysManualEvent
{
#if defined(TV_BARE_METAL)
    //TODO: !!! Dirty implementation, need rewrite
    using Handle = TBareMetalEventHandle::SysHandle;
    Handle state;
#elif defined(_WIN32)
    using Handle = HANDLE;
    Handle hEvent;
#else
    using Handle = int[2];
    Handle fds;
#endif

    static bool createHandle(Handle &handle) noexcept;
    static SysHandle getWaitableHandle(Handle handle) noexcept;

    SysManualEvent(Handle aHandle) noexcept;
    ~SysManualEvent();
    void signal() noexcept;
    void clear() noexcept;
};

inline SysManualEvent::SysManualEvent(Handle aHandle) noexcept :
#if defined(TV_BARE_METAL)
    state(aHandle)
#elif defined(_WIN32)
    hEvent {aHandle}
#else
    fds {aHandle[0], aHandle[1]}
#endif
{
}

inline SysHandle SysManualEvent::getWaitableHandle(Handle handle) noexcept
{
#if defined(TV_BARE_METAL)
    return handle;
#elif defined(_WIN32)
    return handle;
#else
    return handle[0];
#endif
}

class EventSource
{
public:

    const SysHandle handle;

    EventSource(SysHandle handle) noexcept :
        handle(handle)
    {
    }

    virtual ~EventSource() {}

    virtual bool hasPendingEvents() noexcept;
    virtual bool getEvent(TEvent &) noexcept;
};

class WakeUpEventSource : public EventSource
{
    SysManualEvent sys;
    bool (*callback) (void *, TEvent &) noexcept;
    void *callbackArgs;
    std::atomic<bool> signaled {false};

    bool clear() noexcept;

public:

    // Pre: if 'callback' or 'callbackArgs' are not null, their lifetime must
    // exceed that of 'this'. 'callback' must be noexcept.
    WakeUpEventSource( SysManualEvent::Handle aHandle,
                       bool (*aCallback) (void *, TEvent &),
                       void *aCallbackArgs ) noexcept;

    WakeUpEventSource &operator=(const WakeUpEventSource &) = delete;

    void signal() noexcept; // Multiple producers.
    bool getEvent(TEvent &event) noexcept override; // Single consumer.
};

inline WakeUpEventSource::WakeUpEventSource( SysManualEvent::Handle aHandle,
                                             bool (*aCallback) (void *, TEvent &),
                                             void *aCallbackArgs ) noexcept :
    EventSource(SysManualEvent::getWaitableHandle(aHandle)),
    sys(aHandle),
    callback((bool (*)(void *, TEvent &) noexcept) aCallback),
    callbackArgs(aCallbackArgs)
{
}

enum PollState : uint8_t
{
    psNothing,
    psReady,
    psDisconnect,
};

struct PollData
{
    std::vector<SysHandle> handles;
    std::vector<PollState> states;

    void push_back(SysHandle h)
    {
        handles.push_back(h);
        states.push_back(psNothing);
    }

    void erase(size_t i)
    {
        handles.erase(handles.begin() + i);
        states.erase(states.begin() + i);
    }

    size_t size()
    {
        return handles.size();
    }
};

class EventWaiter
{
    std::vector<EventSource *> sources;
    PollData pd;
    std::unique_ptr<WakeUpEventSource> wakeUp {nullptr};
    TEvent readyEvent;
    bool readyEventPresent {false};

    void removeSource(size_t i) noexcept;
    void pollSources(int timeoutMs) noexcept;
    bool hasReadyEvent() noexcept;
    void getReadyEvent(TEvent &ev) noexcept;

public:

    EventWaiter() noexcept;

    void addSource(EventSource &) noexcept;
    void removeSource(EventSource &) noexcept;

    bool getEvent(TEvent &ev) noexcept;
    void waitForEvent(int ms) noexcept;
    void interruptEventWait() noexcept;
};

} // namespace tvision

#endif // TVISION_EVENTS_H
