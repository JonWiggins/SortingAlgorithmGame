#ifndef SORTS_H
#define SORTS_H

#include <vector>

class sorts
{

public:
    sorts();
    std::vector<int> sorter(int sort, std::vector<int> list, int iterationStep);

private:
    std::vector<int> insertion(std::vector<int> list, int iterationStep);
    std::vector<int> selection(std::vector<int> list, int iterationStep);
    std::vector<int> merge(std::vector<int> list, int iterationStep);
    std::vector<int> bubble(std::vector<int> list, int iterationStep);

    void swap(int *itemOne, int *itemTwo);
};

#endif // SORTS_H
