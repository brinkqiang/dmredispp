
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <memory>
#include <atomic>

#include "asio.hpp"

#include "dmutil.h"
#include "dmformat.h"

class Cdmevent_module :
    public std::enable_shared_from_this<Cdmevent_module>
{
public:
    Cdmevent_module();

    virtual ~Cdmevent_module();

    virtual void Init(void);

    virtual bool Run(int event);

    virtual bool RunUntil();

    virtual void OnStop();

    template <typename... Args>
    void Post(Args&& ... args)
    {
        m_io_event.post(std::forward<Args>(args)...);
    }
    asio::io_context& GetIO();

private:
    asio::io_context m_io_event;
    asio::io_context::work m_io_work;
    asio::signal_set m_signals;
    std::atomic_bool m_stop;
};


std::shared_ptr<Cdmevent_module> dmeventGetModule();

static std::shared_ptr<Cdmevent_module> dmevent_module = dmeventGetModule();

#define DMEVENT_INIT() dmevent_module->Init()
#define DMEVENT_BEGIN dmevent_module->Post([&]()
#define DMEVENT_END )

#define DMEVENT_RUNUNTIL() dmevent_module->RunUntil()
#define DMEVENT_RUN(n) dmevent_module->Run(n)
