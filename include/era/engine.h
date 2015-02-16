#ifndef ERA_ENGINE_H_
#define ERA_ENGINE_H_

#include "era/types.h"
#include "era/blackboard.h"

#include <string>
#include <map>

namespace era
{

class Component;

class Engine
{

public:

    Engine();

    ~Engine();

    void registerComponent(const std::string& name, Component* component);

    void step();

private:

    Blackboard blackboard_;

    std::map<std::string, Component*> components_;

};

} // end namespace era

#endif
