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
    for(int iterator = 0; iterator < static_cast<int>(list.size()); iterator++)
    {
        if(iterationCount >= iterationStep)
        {
            break;
        }
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
    while(i < static_cast<int>(list.size()))
    {
        if(iterationCount >= iterationStep) break;
        int j = i;
        while( j > 0 && list[static_cast<unsigned long>(j - 1)] > list[static_cast<unsigned long>(j)])
        {
            int temp = list[static_cast<unsigned long>(j - 1)];
            list[static_cast<unsigned long>(j - 1)] = list[static_cast<unsigned long>(j)];
            list[static_cast<unsigned long>(j)] = temp;
            j = i + 1;
            iterationCount++;
        }
    }
    return list;
}

std::vector<int> sorts::bubble(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    for(int i = 0; i < static_cast<int>(list.size()); i++)
    {
        if(iterationCount >= iterationStep)
        {
             break;
        }
        for(int j=0; j < static_cast<int>(list.size())-i; j++)
        {
            if(list.at(static_cast<unsigned long>(j)) > list.at(static_cast<unsigned long>(j+1)))
            {
                swap(&list.at(static_cast<unsigned long>(j)), &list.at(static_cast<unsigned long>(j+1)));
            }
        }
        iterationCount++;
    }
    return list;
}

std::vector<int> sorts::merge(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;
    //Break into lists
    std::vector<std::vector<int>> listOfLists;
    for(int i = 0; i < static_cast<int>(list.size()); i++)
    {
        std::vector<int> temp {list[static_cast<unsigned long>(i)]};
        listOfLists.push_back(temp);
    }
    //Sort
    int i = 0;
    int j = 0;
    int k = 0;
    while(iterationCount < iterationStep)
    {
        std::vector<int> temp;
        while (j < static_cast<int>(listOfLists[static_cast<unsigned long>(i)].size()) && k < static_cast<int>(listOfLists[static_cast<unsigned long>(i+1)].size()))
        {
            if(listOfLists[static_cast<unsigned long>(i)][static_cast<unsigned long>(j)] < listOfLists[static_cast<unsigned long>(i+1)][static_cast<unsigned long>(k)])
            {
                temp.push_back(listOfLists[static_cast<unsigned long>(i)][static_cast<unsigned long>(j)]);
                j++;
            }
            else
            {
                temp.push_back(listOfLists[static_cast<unsigned long>(i+1)][static_cast<unsigned long>(k)]);
                k++;
            }
        }
        while(j < static_cast<int>(listOfLists[static_cast<unsigned long>(i)].size()))
        {
            temp.push_back(listOfLists[static_cast<unsigned long>(i)][static_cast<unsigned long>(j)]);
            j++;
        }
        while(k < static_cast<int>(listOfLists[static_cast<unsigned long>(i+1)].size()))
        {
            temp.push_back(listOfLists[static_cast<unsigned long>(i+1)][static_cast<unsigned long>(k)]);
            k++;
        }
        j = 0;
        k = 0;
        listOfLists[static_cast<unsigned long>(i)] = temp;
        listOfLists.erase(listOfLists.begin()+i+1);
        //if finished
        if (listOfLists.size() == 1)
        {
            break;
        }
        i++;
        if (i >= static_cast<int>(listOfLists.size()-1))
        {
            i = 0;
        }
        iterationCount++;
    }
    //Combine into one list
    return mergeHelper(listOfLists);
}

std::vector<int> sorts::mergeHelper(std::vector<std::vector<int>> listOfLists)
{
    std::vector<int> list;
    for(int i = 0; i < static_cast<int>(listOfLists.size()); i++)
    {
        for(int j = 0; j < static_cast<int>(listOfLists[static_cast<unsigned long>(i)].size()); j++)
        {
            list.push_back(listOfLists[static_cast<unsigned long>(i)][static_cast<unsigned long>(j)]);
        }
    }
    return list;
}

