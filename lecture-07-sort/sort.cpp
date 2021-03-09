#include <algorithm>
#include <forward_list>
#include <cstdio>
#include <vector>

template<typename It>
void selection_sort(It begin, It end) {
    while (begin != end) {
        auto min = std::min_element(begin, end);
        if (begin != min) {
            std::swap(*begin, *min);
        }
        ++begin;
    }
}

void print_item(int value) {
    printf("%d ", value);
}

template<typename Container>
void print(const Container& container) {
    std::for_each(container.begin(), container.end(), print_item);
}

int main() {
    std::vector<int> c1 = { 7, 3, 4, 5, 1, 2 };
    std::forward_list<int> c2 = { 7, 3, 4, 5, 1, 2 };

    print(c1);
    printf("\n");

    print(c2);
    printf("\n");

    selection_sort(c1.begin(), c1.end());
    selection_sort(c2.begin(), c2.end());
    //std::sort(c1.begin(), c1.end());

    print(c1);
    printf("\n");

    print(c2);
    printf("\n");
}
