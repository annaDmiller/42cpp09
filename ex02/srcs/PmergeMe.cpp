#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    return ;
}

PmergeMe::PmergeMe(int size) : _size(size)
{
    return ;
}

PmergeMe::~PmergeMe(void)
{
    return ;
}

PmergeMe::PmergeMe(const PmergeMe&other)
{
    (void) other;
    return ;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void) other;
    return (*this);
}

void PmergeMe::printArr(void) const
{
    for (int ind = 0; ind < this->_size; ind++)
        std::cout << this->_vector_arr[ind] << " ";
    std::cout << std::endl;
    return ;
}

const char* PmergeMe::CustomErrorException::what(void) const throw()
{
    return ("Error");
}

void PmergeMe::fillVector(char** args)
{
    int num;

    for (int ind = 0; ind < this->_size; ind++)
    {
        num = atoi(args[ind]);
        if (num < 0)
            throw PmergeMe::CustomErrorException();
        this->_vector_arr.push_back(num);
    }
    return ;
}

void PmergeMe::fillDeque(char** args)
{
    int num;

    for (int ind = 0; ind < this->_size; ind++)
    {
        num = atoi(args[ind]);
        if (num < 0)
            throw PmergeMe::CustomErrorException();
        this->_deq_arr.push_back(num);
    }
    return ;
}

int PmergeMe::getSize(void) const
{
    return (this->_size);
}

