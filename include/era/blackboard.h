#ifndef ERA_BLACKBOARD_H_
#define ERA_BLACKBOARD_H_

#include <map>
#include <string>
#include <era/buffer.h>

namespace era
{

// ----------------------------------------------------------------------------------------------------

template<typename T>
void deleter(void *ptr)
{
    delete static_cast<T*>(ptr);
}

typedef void (*deleter_func)(void *);

// ----------------------------------------------------------------------------------------------------

template<typename T>
class Port
{
public:
    Port() : buffer(0) {}

    Buffer<T>* buffer;
};

// ----------------------------------------------------------------------------------------------------

class Blackboard
{

public:

    Blackboard() {}

    ~Blackboard()
    {
        for(std::map<std::string, std::pair<void*, deleter_func> >::iterator it = buffers_.begin(); it != buffers_.end(); ++it)
        {
            it->second.second(it->second.first);
        }
    }

    template<typename T>
    Port<T> openBuffer(const std::string& name)
    {
        Port<T> p;

        std::map<std::string, std::pair<void*, deleter_func> >::iterator it = buffers_.find(name);
        if (it == buffers_.end())
        {
            p.buffer = new Buffer<T>;
            buffers_[name] = std::make_pair<void*, deleter_func>(p.buffer, &deleter<T>);
        }
        else
        {
            p.buffer = reinterpret_cast<Buffer<T>*>(it->second.first);
        }

        return p;
    }

private:

    std::map<std::string, std::pair<void*, deleter_func> > buffers_;

};

} // end namespace era

#endif
