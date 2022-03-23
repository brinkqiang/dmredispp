# dmredispp

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmredispp](https://img.shields.io/badge/brinkqiang-dmredispp-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmredispp)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmredispp/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmredispp.svg?label=Stars)](https://github.com/brinkqiang/dmredispp) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmredispp.svg?label=Fork)](https://github.com/brinkqiang/dmredispp)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmredispp/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmredispp/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmredispp/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmredispp/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmredispp/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmredispp/actions/workflows/win.yml "win build status"

## Intro
dmredispp
```cpp

#include <cpp_redis/cpp_redis>

#include <iostream>

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */
#include "dmevent/dmevent_module.h"


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

    cpp_redis::client client;

    client.connect("127.0.0.1", 6379, [&](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        DMEVENT_BEGIN
        {
            if (status == cpp_redis::client::connect_state::dropped) {
                fmt::print("client disconnected from {}:{} isMain:{}\n", host, port, isMain());
            }
        }
        DMEVENT_END;
    });

    int roleid = 0x1234;
    // same as client.send({ "SET", "hello", "42" }, ...)
    client.set("hello", "42", [&](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("set hello 42: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    // same as client.send({ "DECRBY", "hello", 12 }, ...)
    client.decrby("hello", 12, [&](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("decrby hello 12: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
        }
        DMEVENT_END;
    });

    // same as client.send({ "GET", "hello" }, ...)
    client.get("hello", [&](cpp_redis::reply& reply) {
        DMEVENT_BEGIN
        {
            fmt::print("get hello: {} roleid: {} isMain:{}\n", reply, roleid, isMain());
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
```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmredispp/Lobby.svg)](https://gitter.im/brinkqiang/dmredispp)

## Thanks
