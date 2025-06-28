#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    return ;
}

PmergeMe::PmergeMe(int size, char** args) : _size(size)
{
    int num;

    for (int ind = 0; ind < size; ind++)
    {
        num = atoi(args[ind]);
        _vector_arr.push_back(num);
        _deq_arr.push_back(num);
    }
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

double PmergeMe::sortingVector(void)
{
    if (this->_size <= 1)
        return (0);

    if (this->isVectorSorted())
        return (0);
    
    std::clock_t start = std::clock();

    
    std::clock_t end = std::clock();

    return (end - start);
}

double PmergeMe::sortingDeque(void)
{
    if (this->_size <= 1)
        return (0);

    if (this->isDequeSorted())
        return (0);

    std::clock_t start = std::clock();
    

    std::clock_t end = std::clock();
    return (end - start);
}

int PmergeMe::getSize(void) const
{
    return (this->_size);
}

bool PmergeMe::isVectorSorted(void) const
{
    for (int ind = 0; ind < this->_size - 1; ind++)
        if (this->_vector_arr[ind] > this->_vector_arr[ind + 1])
            return (false);
    return (true);
}

bool PmergeMe::isDequeSorted(void) const
{
    for (int ind = 0; ind < this->_size - 1; ind++)
        if (this->_deq_arr[ind] > this->_deq_arr[ind + 1])
            return (false);
    return (true);
}

