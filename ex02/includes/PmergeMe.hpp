#pragma once

# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <vector>
# include <deque>
# include <ctime>
# include <algorithm>

class PmergeMe
{
    private:
        int _size;
        std::vector<int> _vector_arr;
        std::deque<int> _deq_arr;

        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        std::vector<int> sortingLogic(std::vector<int> cont);
        void insertFromLoser(std::vector<int> &sorted, std::vector<int> &winner, std::vector<int> &loser);
        void insertLeftNumber(std::vector<int> &sorted, int& last_num);

        std::deque<int> sortingLogic(std::deque<int> cont);
        void insertFromLoser(std::deque<int> &sorted, std::deque<int> &winner, std::deque<int> &loser);
        void insertLeftNumber(std::deque<int> &sorted, int& last_num);

        template <typename Container>
        bool isSorted(Container& cont) const;

    public:
        PmergeMe(void);
        PmergeMe(int size);
        ~PmergeMe(void);

        void fillVector(char** args);
        void sortVector(void);

        void fillDeque(char** args);
        void sortDeque(void);

        void printArr(void) const;

        int getSize(void) const;

    class CustomErrorException : public std::exception
    {
        virtual const char* what(void) const throw();
    };
};

# include "PmergeMe.tpp"