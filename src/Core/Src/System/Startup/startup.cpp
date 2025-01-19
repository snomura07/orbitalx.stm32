#include "startup.h"

Startup::Startup(ObjectHub &objHub_):
    objHub(objHub_)
{}
Startup::~Startup(){}

void Startup::test(){
    objHub.encPtr->dump();
}
