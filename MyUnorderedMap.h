#ifndef MY_UNORDERED_MAP_H
#define MY_UNORDERED_MAP_H

#include <vector>
#include <list>
#include <utility>
#include <functional>   // fallback hash
#include <cstddef>
#include <type_traits>  // is_integral, is_same
#include <string>       // string
#include <cmath>        // floor
using namespace std;

template<typename K, typename V>
class MyUnorderedMap {
private:
    vector<list<pair<K, V>>> buckets;
    size_t count;   

public:
    // constructor: bucket_count default 101 (a small prime-like)
    MyUnorderedMap(size_t bucket_count = 101) : buckets(bucket_count), count(0) {}

    // number of stored elements
    size_t size() const { return count; }

    // is empty?
    bool empty() const { return count == 0; }

    // ------------------------------
    // HÀM BĂM NHÂN (multiplication hash)
    // ------------------------------
    size_t custom_hash(const K& key) const {
        // Nếu là kiểu số nguyên
        if constexpr (is_integral<K>::value) {
            const double A = 0.6180339887; // (sqrt(5) - 1) / 2
            double temp = static_cast<double>(key) * A;
            double fractional = temp - floor(temp); // lấy phần thập phân
            return static_cast<size_t>(static_cast<double>(buckets.size()) * fractional);
        }
        // Nếu là kiểu chuỗi
        else if constexpr (is_same<K, string>::value) {
            // hash chuỗi đơn giản: nhân dồn (P là cơ số)
            const unsigned long long P = 131ULL;
            unsigned long long hashVal = 0ULL;
            for (unsigned char c : key)
                hashVal = hashVal * P + c;
            return static_cast<size_t>(hashVal % buckets.size());
        }
        else {
            // fallback cho kiểu dữ liệu khác: dùng hash rồi map về bucket
            return static_cast<size_t>(hash<K>{}(key) % buckets.size());
        }
    }

    // simple hash -> index
    size_t index_for(const K& key) const {
        return custom_hash(key);
    }

    // insert or update
    void insert(const K& key, const V& value) {
        size_t idx = index_for(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = value; // update existing
                return;
            }
        }
        buckets[idx].push_back(make_pair(key, value));
        ++count;
    }

    // find value pointer (nullptr if not found)
    V* find(const K& key) {
        size_t idx = index_for(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) return &kv.second;
        }
        return nullptr;
    }

    // const find
    const V* find(const K& key) const {
        size_t idx = index_for(key); // SỬA: dùng index_for thay vì hasher
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key) return &kv.second;
        }
        return nullptr;
    }

    // erase key, return true if erased
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

    // iterate: call f(key, value) for each element
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
