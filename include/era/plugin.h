#ifndef ERA_PLUGIN_H_
#define ERA_PLUGIN_H_

#include "era/types.h"
#include "era/blackboard.h"

#include <string>

namespace era
{

class Plugin
{

public:

    Plugin() {}

    ~Plugin() {}

    virtual void initialize(Blackboard& bb) {}

    virtual void process(Blackboard& bb) {} = 0;

    const std::string& name() const { return name_; }

private:

    std::string name_;

};

} // end namespace era

#endif
