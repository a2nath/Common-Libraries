#include <list>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include "spdlog/spdlog.h"

using namespace std;


template <typename T> inline std::string str(T const& value)
{
    return std::to_string(value);
}

template <typename T> inline std::string nstr(T const& value)
{
    auto data_precision = std::numeric_limits<T>::digits10 + 1;
    std::stringstream sstr;
    sstr << std::setprecision(data_precision) << value;
    return sstr.str();
}

// [frame] inside the memory can be word
template<class frame_t>
class simple_lru_cache
{
    struct DataItem
    {
        size_t address;
        frame_t value;

        inline string str() const
        {
            return "{address:" + std::to_string(address) + ",value:" + nstr(value) + "}";
        }

        friend std::ostream& operator<<(std::ostream& os, const DataItem& dataitem)
        {
            os << dataitem.str() << std::flush;
            return os;
        }
    };


    using DataItemIterator = typename list<DataItem>::iterator;
    unordered_map<size_t, DataItemIterator> ulist;
    list<DataItem> items;

    frame_t data_precision;
    size_t num_capacity;

public:
    void read(const size_t& address, frame_t& output)
    {
        auto pite = ulist.find(address);
        if (pite != ulist.end())
        {
            auto& dataitem = pite->second;
            output = dataitem->value;

            items.splice(items.begin(), items, dataitem); // promote

            spdlog::info("-read at: " + str(address) + " value:" + nstr(output));

        }
        else
        {
            spdlog::info("-miss:" + str(address));
            output = 0;
        }

        recent();

    }

    void write(const size_t& address, const frame_t& item)
    {
        auto pite = ulist.find(address);
        if (pite != ulist.end()) // cache hit
        {
            auto previous_value = pite->second->value;

            pite->second->value = item;
            items.splice(items.begin(), items, pite->second); // promote

            spdlog::info("-write at:" + str(address) + \
                " value:" + nstr(pite->second->value) + \
                " prev-value:" + nstr(previous_value));
        }
        else // cache miss
        {
            if (num_capacity == ulist.size())
            {
                auto& data = items.back();
                spdlog::info("-evicting:" + data.str());

                ulist.erase(data.address);
                items.pop_back();
            }

            items.emplace_front(DataItem{ address, item });
            ulist.emplace(address, items.begin());

            spdlog::info("-write at:" + str(address) + " value:" + nstr(items.front().value));
        }
    }

    void recent() const
    {
        if (items.size())
        {
            spdlog::info("front is " + items.front().str());
            //return items.front();
        }
        else
        {
            spdlog::info("front is {0, 0}, cache empty");
            //return { 0, 0 };

        }
    }

    const size_t& capacity() const
    {
        return num_capacity;
    }

    const size_t& size() const
    {
        return ulist.size();
    }

    void reset()
    {
        ulist.clear();
        items.clear();
        cache_size = 0;
    }


    simple_lru_cache(const size_t& isize, unsigned precision) : num_capacity(isize), data_precision(precision)
    {
    }

    /* set the [size] of the cache, default [precision] is numeric_limits<"data_type_t"> */
    simple_lru_cache(const size_t& isize) : num_capacity(isize), data_precision(std::numeric_limits<frame_t>::digits10 + 1)
    {
    }
};

void lru_int_cache_test(size_t size = 3)
{
    simple_lru_cache<int> cache(size);

    int output = 0;
    spdlog::info("-- start with cache (data:INT32) size:" + str(size));
    cache.read(0, output);
    cache.write(1, 10);
    cache.write(2, 11);
    cache.recent();
    cache.read(1, output);
    cache.read(3, output);
    cache.write(1, 0);
    cache.recent();
    cache.read(3, output);
    cache.read(1, output);    // this should get evicted afterwards (size:3)
    cache.read(2, output);
    cache.write(3, 100);
    cache.recent();
    cache.write(4, 2);
    cache.recent();
    cache.read(1, output);    // now create a miss
    spdlog::info("--------------------------------------");
}


void lru_double_cache_test(size_t size = 3)
{
    simple_lru_cache<double> cache(size);

    double output = 0;

    spdlog::info("-- start with cache (data:INT32) size:" + str(size));
    cache.read(0, output);
    cache.write(1, 10.99019199019);
    cache.write(2, 11.11118777811111);
    cache.recent();
    cache.read(1, output);
    cache.read(3, output);
    cache.write(1, 0.0000000000001);
    cache.recent();
    cache.read(3, output);
    cache.read(1, output);    // this should get evicted afterwards
    cache.read(2, output);
    cache.write(3, 100.0000000009);
    cache.recent();
    cache.write(4, 2.0);
    cache.recent();
    cache.read(1, output);    // now create a miss
    spdlog::info("--------------------------------------");
}

int main()
{
    lru_int_cache_test(3);
    lru_double_cache_test(3);
    lru_int_cache_test(10);
    lru_int_cache_test(1000);

    return 0;
}
