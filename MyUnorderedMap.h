#ifndef MY_UNORDERED_MAP_H
#define MY_UNORDERED_MAP_H

#include <vector>
#include <list>
#include <utility>
#include <functional>   
#include <cstddef>
#include <type_traits>  
#include <string>      
#include <cmath>       
using namespace std;

template<typename K, typename V>
class MyUnorderedMap {
private:
    vector<list<pair<K, V>>> buckets;
    size_t count;   

public:
    MyUnorderedMap(size_t bucket_count = 101) : buckets(bucket_count), count(0) {}

    size_t size() const { return count; }

    bool empty() const { return count == 0; }

    size_t custom_hash(const K& key) const {
        if constexpr (is_integral<K>::value) {
            const double A = 0.6180339887; 
            double temp = static_cast<double>(key) * A;
            double fractional = temp - floor(temp); 
            return static_cast<size_t>(static_cast<double>(buckets.size()) * fractional);
        }
        else if constexpr (is_same<K, string>::value) {
            const unsigned long long P = 131ULL;
            unsigned long long hashVal = 0ULL;
            for (unsigned char c : key)
                hashVal = hashVal * P + c;
            return static_cast<size_t>(hashVal % buckets.size());
        }
        else {
            return static_cast<size_t>(hash<K>{}(key) % buckets.size());
        }
    }

    size_t index_for(const K& key) const {
        return custom_hash(key);
    }

    void insert(const K& key, const V& value) {
        size_t idx = index_for(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = value; 
                return;
            }
        }
        buckets[idx].push_back(make_pair(key, value));
        ++count;
    }

    V* find(const K& key) {
        size_t idx = index_for(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) return &kv.second;
        }
        return nullptr;
    }

    const V* find(const K& key) const {
        size_t idx = index_for(key);
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key) return &kv.second;
        }
        return nullptr;
    }

    bool erase(const K& key) {
        size_t idx = index_for(key);
        auto& bucket = buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --count;
                return true;
            }
        }
        return false;
    }

    template<typename Func>
    void for_each(Func f) const {
        for (const auto& bucket : buckets) {
            for (const auto& kv : bucket) {
                f(kv.first, kv.second);
            }
        }
    }
};

#endif // MY_UNORDERED_MAP_H
