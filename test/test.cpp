#include <era/buffer.h>
#include <era/blackboard.h>
#include <era/component.h>
#include <era/engine.h>

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

// ----------------------------------------------------------------------------------------------------

class TestComponentA : public era::Component
{

public:

    void initialize(era::InitializationData& init)
    {
        p_test_ = init.blackboard->openBuffer<double>("test");
        value_ = 0;
    }

    void process()
    {
        p_test_.buffer->insert(0, value_);
        ++value_;
    }

private:

    era::Port<double> p_test_;
    double value_;

};

// ----------------------------------------------------------------------------------------------------

class TestComponentB : public era::Component
{

public:

    void initialize(era::InitializationData& init)
    {
        p_test_ = init.blackboard->openBuffer<double>("test");
    }

    void process()
    {
        double d;
        if (p_test_.buffer->latest(d))
        {
            std::cout << "Latest value: " << d << std::endl;
        }
    }

private:

    era::Port<double> p_test_;

};

// --------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    era::Engine engine;

    era::Component* comp_a = new TestComponentA;
    era::Component* comp_b = new TestComponentB;

    engine.registerComponent("component_a", comp_a);
    engine.registerComponent("component_b", comp_b);

    while(true)
    {
        engine.step();
    }

//    era::Blackboard bb;
//    era::Port<double> p = bb.openBuffer<double>("test");
//    era::Port<std::string> p3 = bb.openBuffer<std::string>("bla");

//    std::cout << "Start" << std::endl;

//    for(unsigned int i = 1000; i > 0; --i)
//    {
//        p.buffer->insert(era::Time((double)i / 10), i);
//    }

//    era::Buffer<double>::const_iterator it1, it2;

//    era::Port<double> p2 = bb.openBuffer<double>("test");

//    p2.buffer->getLowerUpper(2, it1, it2);

//    if (it1 != p2.buffer->end())
//        std::cout << "Lo: " << asTime(it1->first) << ": " << it1->second << std::endl;

//    if (it2 != p2.buffer->end())
//        std::cout << "Hi: " << asTime(it2->first) << ": " << it2->second << std::endl;

//    era::Port<int> p4 = bb.openBuffer<int>("test");

//    std::cout << bb.ok() << std::endl;

    return 0;
}
