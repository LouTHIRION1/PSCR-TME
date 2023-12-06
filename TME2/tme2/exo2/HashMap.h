# pragma once
#include <forward_list>
#include <vector>

namespace pr {

template <typename K, typename V>
class HashTable {

public:
	class Entry {
	public:
		const K key;
		V value;
		Entry(const K &k, const V &v):key(k),value(v){}
	};
	
private:
	typedef std::vector<std::forward_list<Entry>> buckets_t;
	
	buckets_t buckets;
	size_t size;

public:
	HashTable(size_t sz): size(0), buckets(sz){}
	
	V* get (const K &key) {
		size_t h = std::hash<K>()(key);
		size_t target = h%buckets.size();
		for(Entry &e : buckets[target]) {
			if(e.key == key)
				return & e.value;
		}
		return nullptr;
	}
	
	bool put (const K& key, const V &val) {
		size_t h = std::hash<K>{}(key);
		size_t target = h%buckets.size();
		for(Entry &e : buckets [target]) {
			if(e.key == key) {
				e.value == val;
				return true;
			}
		}
		++size;
		buckets[target].emplace_front(key,val);
		return false;
	}
};
}
