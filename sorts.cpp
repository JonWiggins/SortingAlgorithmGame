#include "sorts.h"

sorts::sorts()
{
}

std::vector<int> sorts::sorter(int sort, std::vector<int> list, int iterationStep)
{
    switch(sort)
    {
    case 1: return selection(list, iterationStep);
    case 2: return insertion(list, iterationStep);
    case 3: return bubble(list, iterationStep);
    case 4: return merge(list, iterationStep);
    }
    return list;
}

std::vector<int> sorts::selection(std::vector<int> list, int iterationStep)
{
    return list;
}

std::vector<int> sorts::insertion(std::vector<int> list, int iterationStep)
{
    return list;
}

std::vector<int> sorts::bubble(std::vector<int> list, int iterationStep)
{
    return list;
}

std::vector<int> sorts::merge(std::vector<int> list, int iterationStep)
{
    return list;
}
