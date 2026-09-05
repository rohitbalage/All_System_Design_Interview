/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
An LRU cache evicts the least recently used item when the cache reaches capacity. Both get and put operations count as "using" an item.
Implement the following methods:
LRUCache(capacity: number) → void: Initialize the cache with a positive capacity.
get(key: number) → number: Return the value associated with key if it exists in the cache, otherwise return -1.
put(key: number, value: number) → void: Update the value of key if it exists, or insert the key-value pair. If inserting causes the cache to exceed its capacity, evict the least recently used key before inserting.
Example 1:
Input:
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
  
Output:
[null, null, null, 1, null, -1, null, -1, 3, 4]
  
Explanation:
cache = LRUCache(2)              # capacity = 2
  
cache.put(1, 1)                  # cache: {1=1}
cache.put(2, 2)                  # cache: {1=1, 2=2}
cache.get(1)                     # → 1     (key 1 is now most recently used)
cache.put(3, 3)                  # evicts key 2 (LRU), cache: {1=1, 3=3}
cache.get(2)                     # → -1    (key 2 was evicted)
cache.put(4, 4)                  # evicts key 1 (LRU), cache: {3=3, 4=4}
cache.get(1)                     # → -1    (key 1 was evicted)
cache.get(3)                     # → 3
cache.get(4)                     # → 4
Constraints:
1 <= capacity <= 3000
0 <= key <= 10⁴
0 <= value <= 10⁵
At most 10⁴ total calls will be made to get and put.
Follow-up: Can you implement get and put in O(1) average time complexity?
*/



#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }

    int get(int key) {
        auto it = cache_.find(key);

        // Key does not exist
        if (it == cache_.end()) {
            return -1;
        }

        // Key was used, so move it to the front (MRU)
        order_.splice(order_.begin(), order_, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        auto it = cache_.find(key);

        // Case 1: key already exists
        if (it != cache_.end()) {
            // Update value
            it->second->second = value;

            // Mark as most recently used
            order_.splice(order_.begin(), order_, it->second);

            return;
        }

        // Case 2: cache is full
        if (cache_.size() == capacity_) {
            // Last element is least recently used
            int lruKey = order_.back().first;

            cache_.erase(lruKey);
            order_.pop_back();
        }

        // Insert new key at front = most recently used
        order_.push_front({key, value});

        // Store iterator pointing to new list node
        cache_[key] = order_.begin();
    }

private:
    int capacity_;

    // Front = Most Recently Used
    // Back  = Least Recently Used
    list<pair<int, int>> order_;

    // key -> location inside order_
    unordered_map<int, list<pair<int, int>>::iterator> cache_;
};