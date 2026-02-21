#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace exemplar {

// A pedagogical hash map using separate chaining.
// Buckets are vectors of key-value entries.
// Rehashing keeps average operations close to O(1).
template <typename K, typename V, typename Hash = std::hash<K>>
class HashMap {
public:
    HashMap() : buckets_(k_default_bucket_count) {}

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    // Insert new key or update existing key.
    // Returns true if inserted new key, false if updated existing key.
    bool insert_or_assign(const K& key, const V& value) {
        maybe_rehash_for_insert();
        auto& bucket = buckets_[bucket_index(key)];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                entry.value = value;
                return false;
            }
        }

        bucket.push_back(Entry{key, value});
        ++size_;
        return true;
    }

    bool insert_or_assign(K&& key, V&& value) {
        maybe_rehash_for_insert();
        auto& bucket = buckets_[bucket_index(key)];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                entry.value = std::move(value);
                return false;
            }
        }

        bucket.push_back(Entry{std::move(key), std::move(value)});
        ++size_;
        return true;
    }

    [[nodiscard]] bool contains(const K& key) const {
        const auto& bucket = buckets_[bucket_index(key)];
        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return true;
            }
        }
        return false;
    }

    std::optional<V> get(const K& key) const {
        const auto& bucket = buckets_[bucket_index(key)];
        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        return std::nullopt;
    }

    V& at(const K& key) {
        auto& bucket = buckets_[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::out_of_range("HashMap::at key not found");
    }

    const V& at(const K& key) const {
        const auto& bucket = buckets_[bucket_index(key)];
        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::out_of_range("HashMap::at key not found");
    }

    // operator[] inserts a default value if key is missing.
    V& operator[](const K& key) {
        maybe_rehash_for_insert();
        auto& bucket = buckets_[bucket_index(key)];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        bucket.push_back(Entry{key, V{}});
        ++size_;
        return bucket.back().value;
    }

    bool erase(const K& key) {
        auto& bucket = buckets_[bucket_index(key)];
        for (std::size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i].key == key) {
                bucket[i] = std::move(bucket.back());
                bucket.pop_back();
                --size_;
                return true;
            }
        }
        return false;
    }

    void clear() {
        buckets_.assign(k_default_bucket_count, {});
        size_ = 0;
    }

    [[nodiscard]] double load_factor() const noexcept {
        if (buckets_.empty()) {
            return 0.0;
        }
        return static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

private:
    struct Entry {
        K key;
        V value;
    };

    static constexpr std::size_t k_default_bucket_count = 8;
    static constexpr double k_max_load_factor = 0.75;

    [[nodiscard]] std::size_t bucket_index(const K& key) const {
        return hasher_(key) % buckets_.size();
    }

    void maybe_rehash_for_insert() {
        const std::size_t next_size = size_ + 1;
        const double next_load = static_cast<double>(next_size) / static_cast<double>(buckets_.size());
        if (next_load > k_max_load_factor) {
            rehash(buckets_.size() * 2);
        }
    }

    void rehash(std::size_t new_bucket_count) {
        std::vector<std::vector<Entry>> new_buckets(new_bucket_count);

        for (auto& bucket : buckets_) {
            for (auto& entry : bucket) {
                const std::size_t index = hasher_(entry.key) % new_bucket_count;
                new_buckets[index].push_back(std::move(entry));
            }
        }

        buckets_ = std::move(new_buckets);
    }

    std::vector<std::vector<Entry>> buckets_;
    std::size_t size_{0};
    Hash hasher_{};
};

} // namespace exemplar
