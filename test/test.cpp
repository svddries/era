#include <era/buffer.h>
#include <era/blackboard.h>

#include <iostream>

// --------------------------------------------------------------------------------------------------------------

struct asTime
{
    asTime(const era::Time& t) : t_(t) {}

    era::Time t_;

    friend std::ostream& operator<< (std::ostream& out, const asTime& t)
    {
        out << "[" << t.t_ << "]";
        return out;
    }
};

// --------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    era::Blackboard bb;
    era::Port<double> p = bb.openBuffer<double>("test");
    era::Port<std::string> p3 = bb.openBuffer<std::string>("bla");

    std::cout << "Start" << std::endl;

    for(unsigned int i = 1000; i > 0; --i)
    {
        p.buffer->insert(era::Time((double)i / 10), i);
    }

    era::Buffer<double>::const_iterator it1, it2;

    era::Port<double> p2 = bb.openBuffer<double>("test");

    p2.buffer->getLowerUpper(2, it1, it2);

    if (it1 != p2.buffer->end())
        std::cout << "Lo: " << asTime(it1->first) << ": " << it1->second << std::endl;

    if (it2 != p2.buffer->end())
        std::cout << "Hi: " << asTime(it2->first) << ": " << it2->second << std::endl;

    return 0;
}
