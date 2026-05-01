#include <unordered_map>
using namespace std;
class LRUCache {
    private:
    struct Cache {
        int key;
        int value;
        Cache* next;
        Cache* prev;
        Cache(int k, int v, Cache* p = nullptr, Cache* n = nullptr) : key(k), value(v), prev(p), next(n) {}
    };
    unordered_map<int, Cache*> caches;
    Cache* head;
    Cache* tail;
    int capacity;
    void unlink(Cache* cache) {
        cache->prev->next = cache->next;
        cache->next->prev = cache->prev;        
    }
    void push_back(Cache* cache) {
        tail->prev->next = cache;
        cache->prev = tail->prev;
        cache->next = tail;
        tail->prev = cache;
    }
    void move_to_back(Cache* cache) {
        unlink(cache);
        push_back(cache);
    }
public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Cache(-1, -1);
        tail = new Cache(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    ~LRUCache() {
        Cache* cache = head;
        while (cache) {
            Cache* next = cache->next;
            delete cache;
            cache = next;
        }
    }
    
    int get(int key) {
        auto it = caches.find(key);
        if (it != caches.end()) {
            Cache* cache = it->second;
            move_to_back(cache);
            return cache->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (caches.find(key) != caches.end()) {
            Cache* cache = caches[key];
            cache->value = value;
            move_to_back(cache);
            caches[key] = cache;            
        } else if (caches.size() == capacity) {
            Cache* lru_cache = head->next;
            caches.erase(lru_cache->key);
            lru_cache->key = key;
            lru_cache->value = value;
            move_to_back(lru_cache);
            caches[key] = lru_cache;        
        } else {
            Cache* new_cache = new Cache(key, value);
            push_back(new_cache);
            caches[key] = new_cache;        
        }
    }
};