#ifndef ERA_BUFFER_H_
#define ERA_BUFFER_H_

#include "era/types.h"
#include <map>

namespace era
{

template<typename T>
class Buffer
{

public:

    typedef typename std::map<Time, T>::const_iterator const_iterator;

    Buffer(std::size_t max_size = 0) : max_size_(max_size) {}

    ~Buffer() {}

    void insert(const Time& t, const T& value)
    {
        if (max_size_ > 0 && cache_.size() == max_size_)
        {
            if (cache_.begin()->first > t)
                return;
            cache_.erase(cache_.begin());
        }
        cache_[t] = value;
    }

    void getLowerUpper(const Time& t, const_iterator& lower, const_iterator& upper) const
    {
        if (cache_.empty())
        {
            lower = cache_.end();
            upper = cache_.end();
            return;
        }

        // std::map::upper_bound returns first iterator after key
        upper = cache_.upper_bound(t);

        if (upper == cache_.begin())
        {
            lower = cache_.end();
        }
        else
        {
            lower = upper;
            --lower;
        }
    }

    bool latest(T& data, era::Time& t) const
    {
        if (cache_.empty())
            return false;

        typename std::map<Time, T>::const_iterator it = --cache_.end();

        data = it->second;
        t = it->first;

        return true;
    }

    inline const_iterator begin() const { return cache_.begin(); }
    inline const_iterator end() const { return cache_.end(); }

    inline const std::size_t& size() const { return cache_.size(); }

    void setMaxSize(unsigned int n) { max_size_ = n; }

private:

    // Cache with items ordered in time
    std::map<Time, T> cache_;

    unsigned int max_size_;

};
} // end namespace era

#endif
