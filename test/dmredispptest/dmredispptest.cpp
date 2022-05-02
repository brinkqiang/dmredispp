// The MIT License (MIT)
//
// Copyright (c) 2015-2017 Simon Ninon <simon.ninon@gmail.com>
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

#include <cpp_redis/cpp_redis>

#include <iostream>

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */
#include "dmevent/dmevent_module.h"
#include "dmrand.h"

// 注意client生命周期

cpp_redis::client client;

int
main(void) {
#ifdef _WIN32
    //! Windows netword DLL init
    WORD version = MAKEWORD(2, 2);
    WSADATA data;

    if (WSAStartup(version, &data) != 0) {
        std::cerr << "WSAStartup() failure" << std::endl;
        return -1;
    }
#endif /* _WIN32 */

    DMEVENT_INIT();
    DMEVENT_BEGIN
    {
        fmt::print("---------------------------------------------------------------\n");
        fmt::print("{} dmevent loop {} ...\n", DMGetExeName(), "running");
        fmt::print("---------------------------------------------------------------\n");
    }
    DMEVENT_END;


    //! Enable logging
    cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);


    client.connect("127.0.0.1", 6379, [&](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        DMEVENT_BEGIN
        {
            if (status == cpp_redis::client::connect_state::dropped) {
                fmt::print("client disconnected from {}:{} isMain:{}\n", host, port, isMain());
            }
        }
        DMEVENT_END;
    });

    // ZRANGEBYSCORE
    //client.zrangebyscore();

    int roleid = 0x1234;

    client.get("hello2345", [&](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("get hello: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    client.set("hello", "42", [&](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("set hello 42: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    // same as client.send({ "DECRBY", "hello", 12 }, ...)
    client.decrby("hello", 12, [=](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("decrby hello 12: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    // same as client.send({ "GET", "hello" }, ...)
    client.get("hello", [=](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("get hello: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    for (size_t i = 0; i < 100; i++)
    {
        int rand = gDMRand.GetRandRange(1, 100);
        std::vector<std::string> opt;
        std::multimap<std::string, std::string> map;
        auto value = fmt::format("{}{}", "hello", rand);
        auto key = fmt::format("{}", rand);
        map.insert(std::make_pair(key, value));
        client.zadd("hellogroup", opt, map, [=](cpp_redis::reply& reply) {
            DMEVENT_BEGIN
            {
                fmt::print("zadd {} {}: {} roleid: {} isMain:{}\n", fmt::format("{}{}", "hello", rand), fmt::format("{}", rand), reply, roleid, isMain());
            }
            DMEVENT_END;
        });
    }

    client.zrangebyscore("hellogroup", "50", "60", true, [=](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            if (reply.is_array())
            {
                auto arr = reply.as_array();
                for (auto i = 0; i < arr.size(); i += 2)
                {
                    fmt::print("zrangebyscore : {} {} roleid: {} isMain:{}\n", arr[i], arr[i + 1], roleid, isMain());
                }
            }
        }
        DMEVENT_END;
    });


    // commands are pipelined and only sent when client.commit() is called
    client.commit();

    DMEVENT_RUN_UNTIL();
    // synchronous commit, no timeout
    //client.sync_commit();

    // synchronous commit, timeout
    // client.sync_commit(std::chrono::milliseconds(100));

#ifdef _WIN32
    WSACleanup();
#endif /* _WIN32 */

    return 0;
}
