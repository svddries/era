#include "era/engine.h"
#include "era/component.h"

namespace era
{

// ----------------------------------------------------------------------------------------------------

Engine::Engine()
{
}

// ----------------------------------------------------------------------------------------------------

Engine::~Engine()
{
    for(std::map<std::string, Component*>::iterator it = components_.begin(); it != components_.end(); ++it)
    {
        delete it->second;
    }
}

// ----------------------------------------------------------------------------------------------------

void Engine::registerComponent(const std::string& name, Component* component)
{
    std::map<std::string, Component*>::iterator it = components_.find(name);

    if (it == components_.end())
    {
        components_[name] = component;
    }
    else
    {
        delete it->second;
        it->second = component;
    }

    InitializationData init;
    init.blackboard = &blackboard_;

    component->initialize(init);
}

// ----------------------------------------------------------------------------------------------------

void Engine::step()
{
    if (!blackboard_.ok())
        return;

    for(std::map<std::string, Component*>::iterator it = components_.begin(); it != components_.end(); ++it)
    {
        Component* component = it->second;
        component->process();
    }
}

} // end namespace era

