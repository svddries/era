#ifndef ERA_BLACKBOARD_H_
#define ERA_BLACKBOARD_H_

#include <map>
#include <string>
#include "era/buffer.h"

#include <typeinfo>
#include <iostream>

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

struct BufferInfo
{
    void* buffer;
    std::string type_name;
    deleter_func deleter;
};

// ----------------------------------------------------------------------------------------------------

class Blackboard
{

public:

    Blackboard() {}

    ~Blackboard()
    {
        for(std::map<std::string, BufferInfo>::iterator it = buffers_.begin(); it != buffers_.end(); ++it)
        {
            it->second.deleter(it->second.buffer);
        }
    }

    template<typename T>
    Port<T> openBuffer(const std::string& name)
    {
        Port<T> p;

        std::map<std::string, BufferInfo>::iterator it = buffers_.find(name);
        if (it == buffers_.end())
        {
            p.buffer = new Buffer<T>(10);   // TODO: get rid of hard-coded buffer size
            BufferInfo& info = buffers_[name];
            info.buffer = p.buffer;
            info.deleter = &deleter<Buffer<T> >;
            info.type_name = typeid(T).name();
        }
        else
        {
            if (std::string(typeid(T).name()) == it->second.type_name)
            {
                p.buffer = reinterpret_cast<Buffer<T>*>(it->second.buffer);
            }
            else
            {
                std::string error = "ERROR: trying to open buffer '" + name + "' with wrong type '" + typeid(T).name()
                        + "'. Buffer has type: '" + it->second.type_name + "'.";

                std::cout << error << std::endl;
                error_ += error + '\n';
            }
        }

        return p;
    }

    bool ok() const { return error_.empty(); }

    const std::string& error_message() const { return error_; }

private:

    std::map<std::string, BufferInfo> buffers_;

    std::string error_;

};

} // end namespace era

#endif
