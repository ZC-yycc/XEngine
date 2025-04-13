#ifndef XARRAYVEC_H
#define XARRAYVEC_H
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>


template<class K, class V>
struct XPair {
	XPair(const K &key, const V &val) {
		key_ = key; val_ = val;
	}
	K key_; V val_;
};

template<class K, class V>
class XKeyVector
{
public:
	XKeyVector() {};
	~XKeyVector() {};

	inline void pushBack(const K& key,const V &val) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		pair_array_.push_back({key, val});
		key_ull_hash_.insert(std::pair<K, size_t>(key, pair_array_.size() - 1));
	}

	inline void insert(const size_t& index, const K& key,const V &val) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		pair_array_.insert(index, { key, val });
		key_ull_hash_.insert(std::pair<K, size_t>(key, index));
	}

	inline void erase(const K& key) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		if (key_ull_hash_.find(key) == key_ull_hash_.end()) return;
		size_t index = key_ull_hash_[key];
		pair_array_.erase(pair_array_.begin() + key_ull_hash_[key]);
		for (index; index != pair_array_.size(); index++)
		{
			key_ull_hash_[pair_array_[index].key_]--;
		}
		key_ull_hash_.erase(key);
	}

	inline void clear() {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		pair_array_.clear();
		key_ull_hash_.clear();
	}

	inline bool find(const K& key) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return key_ull_hash_.find(key) != key_ull_hash_.end();
	}

	inline size_t count() {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return pair_array_.size();
	}

	inline size_t size() {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return pair_array_.max_size();
	}

	//为遍历提供接口
	V& operator[](const size_t& index){
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return pair_array_[index].val_;
	}

	//根据键值获取对象
	V& atKey(const K& key){
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return pair_array_[key_ull_hash_[key]].val_;
	}

	//获取表中第index的键值
	K& getKey(const size_t& index) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return pair_array_[index].key_;
	}

	size_t getIndex(const K& key) {
		std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return key_ull_hash_[key];
	}
private:
	std::vector<XPair<K, V>>						pair_array_;
	std::unordered_map<K, size_t>					key_ull_hash_;

	std::mutex										mutex_fixed_run_;

};

#endif
