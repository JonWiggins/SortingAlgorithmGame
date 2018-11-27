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

void sorts::swap(int *itemOne, int *itemTwo)
{
    int temp = *itemOne;
    *itemOne = *itemTwo;
    *itemTwo = temp;
}

std::vector<int> sorts::selection(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    int minIndex;
    for(int iterator = 0; iterator <= static_cast<int>(list.size()); iterator++)
    {
        if(iterationCount >= iterationStep) break;
        minIndex = iterator;
        for(int mover = iterator + 1; mover < static_cast<int>(list.size()); mover++)
        {
            if(list.at(static_cast<unsigned long>(mover)) < list.at(static_cast<unsigned long>(minIndex)))
            {
                minIndex = mover;
            }
        }
        swap(&list.at(static_cast<unsigned long>(minIndex)), &list.at(static_cast<unsigned long>(iterator)));
        iterationCount++;
    }
    return list;
}

std::vector<int> sorts::insertion(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    int i = 1;
    while(i < list.size()){
        if(iterationCount >= iterationStep) break;
        int j = i;
        while( j > 0 && list[j - 1] > list[j]){
            int temp = list[j - 1];
            list[j - 1] = list[j];
            list[j] = temp;
            j = i + 1;
            iterationCount++;
        }
    }
    return list;
}

std::vector<int> sorts::bubble(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    if(iterationCount == iterationStep) return list; //temp returns
    return list;
}

std::vector<int> sorts::merge(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    if(iterationCount == iterationStep) return list; //temp returns
    return list;
}
