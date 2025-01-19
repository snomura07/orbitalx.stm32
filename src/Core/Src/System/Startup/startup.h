#ifndef SYSTEM_STARTUP_H_
#define SYSTEM_STARTUP_H_

#include <memory>
#include <ObjectHub/object_hub.h>

class Startup{
public:
    Startup(ObjectHub &objHub_);
    ~Startup();
    void test();

private:
    ObjectHub &objHub;
};

#endif
