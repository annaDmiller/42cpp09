#pragma once

# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <vector>
# include <deque>
# include <ctime>

class PmergeMe
{
    private:
        int _size;
        std::vector<int> _vector_arr;
        std::deque<int> _deq_arr;

        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        void vectorMergeInsertSort(int ind_begin, int ind_end);
        bool isVectorSorted(void) const;


        bool isDequeSorted(void) const;

    public:
        PmergeMe(void);
        PmergeMe(int size, char** args);
        ~PmergeMe(void);

        void printArr(void) const;

        double sortingVector(void);
        double sortingDeque(void);
        int getSize(void) const;

    class CustomErrorException : public std::exception
    {
        virtual const char* what(void) const throw();
    };
};