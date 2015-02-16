#ifndef ERA_COMPONENT_H_
#define ERA_COMPONENT_H_

#include "era/types.h"
#include "era/blackboard.h"

#include <string>

namespace era
{

// ----------------------------------------------------------------------------------------------------

struct InitializationData
{
    Blackboard* blackboard;
};

// ----------------------------------------------------------------------------------------------------

class Component
{

public:

    Component() {}

    ~Component() {}

    virtual void initialize(InitializationData& init) {}

    virtual void process() = 0;

    const std::string& name() const { return name_; }

private:

    std::string name_;

};

} // end namespace era

#endif
