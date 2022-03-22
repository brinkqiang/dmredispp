#include "dmlog.h"
#include "dmutil.h"
int main(int argc, char *argv[])
{
    DMBench oBench;
    LOG_CRITICAL("hello world {}.", 2019);

    for (int i = 0; i < 2000000; i++) {
        oBench++;
        LOG_WARN("This message is 116 characters long including the info that comes before it. {}", i);
    }

    LOG_CRITICAL("This concludes the feature demo for dmlog!");
    return 0;
}