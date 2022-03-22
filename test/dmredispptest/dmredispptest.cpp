
#include "dmredispp.h"

int main( int argc, char* argv[] ) {

    Idmredispp* module = dmredisppGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
    return 0;
}
