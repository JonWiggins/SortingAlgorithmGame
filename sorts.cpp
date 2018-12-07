/* CS 3505 A8: Educational Game
 *
 * Purpose: This class contains versions of the sorting algorithms that the game teaches.
 *  Each sort is capable of 'halting' at a specified iteration count so that the user can see the ordering of the elemtns
 *  part of the way through the sorting process.
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

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
    for(int iterator = 0; iterator < static_cast<int>(list.size() - 1); iterator++)
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
    for(int i = 1; i < static_cast<int>(list.size()); i++)
    {
        if(iterationCount >= iterationStep)
        {
            break;
        }
        int temp = list.at(static_cast<unsigned long>(i));
        int j = i - 1;
        while( j >= 0 && temp < list.at(static_cast<unsigned long>(j)))
        {
            swap(&list.at(static_cast<unsigned long>(j + 1)), &list.at(static_cast<unsigned long>(j)));
            j--;
        }
        list.at(static_cast<unsigned long>(j + 1)) = temp;
        iterationCount++;
    }
    return list;
}

std::vector<int> sorts::bubble(std::vector<int> list, int iterationStep)
{
    int iterationCount = 1;

    for(int i = 0; i < static_cast<int>(list.size()-1);i++)
    {
        if(iterationCount == iterationStep)
        {
             break;
        }
        for(int j=0; j < static_cast<int>(list.size()-static_cast<unsigned long>(i)-1);j++)
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

