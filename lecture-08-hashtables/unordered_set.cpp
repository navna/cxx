#include <cstdio>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// TKey - тип ключей, хранимых в хеш-таблице
// THash - алгоритм вычисления хеша для типа TKey
// TEqualComparer - алгоритм сравнения объектов типа TKey
template<typename TKey, typename THash = std::hash<TKey>, typename TEqualComparer = std::equal_to<TKey>>
class unordered_set {
    struct node {
        TKey key;
        node* next;

        node(const TKey& key, node* next) : key(key), next(next) { }
    };

    node** table;
    const size_t tableSize;

public:
    class iterator {
        // TODO Поля
        // TODO Конструктор

    public:
        friend class unordered_set<TKey, THash, TEqualComparer>;
    };

    unordered_set(size_t tableSize) : table(nullptr), tableSize(tableSize) { }

    bool contains(const TKey& key) {
        const auto index = THash()(key) % tableSize;
        if (table[index] == nullptr) {
            return false;
        }
        // TODO
    }
};

std::vector<std::string> remove_duplicates(std::vector<std::string>& data) {
    std::unordered_set<std::string> set;
    std::vector<std::string> result;
    for (auto& s : data) {
        if (set.find(s) == set.end()) {
            set.insert(s);
            result.push_back(s);
        }
    }

    return result;
}

int main() {
    // Дан std::vector, состоящий из большого количества небольших строк с повторениями. Сформировать новый вектор, содержащий строки в том же порядке, но с удалёнными дубликатами.
    // Пример входного вектора : {"brave", "new", "brave", "world", "new"}.
    // Пример выходного вектора : {"brave", "new", "world"}.
    std::vector<std::string> data = { "brave", "new", "brave", "world", "new" };
    for (auto& s : data) {
        printf("%s\n", s.c_str());
    }
    printf("\n");

    data = remove_duplicates(data);
    for (auto& s : data) {
        printf("%s\n", s.c_str());
    }
    printf("\n");



    // Дан std::vector, состоящий из строк с повторениями. Посчитать, сколько раз встречается каждая строка.
    data = { "brave", "new", "brave", "world", "brave", "new" };

    for (auto& s : data) {
        printf("%s\n", s.c_str());
    }
    printf("\n");

    std::unordered_map<std::string, size_t> map;
    for (auto& s : data) {
        auto it = map.find(s);
        if (it != map.end()) {
            ++(it->second);
        }
        else {
            map.insert({ s, 1 });
        }
    }

    for (auto& kv : map) {
        printf("%s: %zu\n", kv.first.c_str(), kv.second);
    }
    printf("\n");
}
