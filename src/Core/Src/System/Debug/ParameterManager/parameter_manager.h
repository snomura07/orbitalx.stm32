#ifndef SYSTEM_PARAMETER_MANAGER_H_
#define SYSTEM_PARAMETER_MANAGER_H_

#include <cstring>
#include "UtilInterface/util_interface.h"

namespace Debug {
class ParameterManager : public UtilInterface {
public:
    ParameterManager();
    ~ParameterManager();

    bool comCheck();
    // void sendParameters();
    // void updateParameter(const char* data);

private:
    char rxBuffer[32];
    int rxIndex;
};
};
#endif
