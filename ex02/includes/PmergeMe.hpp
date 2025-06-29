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

    public:
        PmergeMe(void);
        PmergeMe(int size);
        ~PmergeMe(void);

        void fillVector(char** args);
        
        void fillDeque(char** args);

        void printArr(void) const;

        int getSize(void) const;

    class CustomErrorException : public std::exception
    {
        virtual const char* what(void) const throw();
    };
};