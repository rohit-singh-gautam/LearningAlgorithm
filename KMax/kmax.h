#include <vector>

template <typename comparator, typename NumType>
size_t CreatePartition(std::vector<NumType> &list, size_t list_start, size_t list_end) {
    const NumType pivot { list[list_start] };
    size_t le_index { list_start };
    size_t g_index { list_start + 1 };
    for(;g_index < list_end; ++g_index) {
        if (comparator {} (list[g_index], pivot)) {
            std::swap(list[++le_index], list[g_index]);
        }
    }
    std::swap(list[list_start], list[le_index]);
    return le_index;
}

template <typename comparator, typename NumType>
std::vector<NumType> GetTopK(std::vector<NumType> &list, size_t k) {
    if (list.size() <= k) return list;
    if (k == 0) return std::vector<NumType> { };
    size_t list_start { 0 };
    size_t list_end = list.size();
    for(;;) {
        auto center = CreatePartition<comparator>(list, list_start, list_end);
        if (center == k - 1) break;
        if (center < k - 1) list_start = center + 1;
        if (center >= k) list_end = center;
        if (list_start == list_end) break;
    }

    std::vector<NumType> ret { std::begin(list), std::begin(list) + k };
    return ret;
}