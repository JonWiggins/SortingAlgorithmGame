/* CS 3505 A8: Educational Game
 *
 * Purpose: This class contains versions of the sorting algorithms that the game teaches.
 *  Each sort is capable of 'halting' at a specified iteration count so that the user can see the ordering of the elemtns
 *  part of the way through the sorting process.
 *
 * @author Zak Bastiani, Alex Fritz, Conner Soule, Ryan Outtrim, Jonathan Wiggins, Will Stout, Ciaochuang Huang, and Mingqiu Zhang
 * @version 12/07/18
 */

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
    std::vector<int> mergeHelper(std::vector<std::vector<int>> listOfLists);

    void swap(int *itemOne, int *itemTwo);
};

#endif // SORTS_H
