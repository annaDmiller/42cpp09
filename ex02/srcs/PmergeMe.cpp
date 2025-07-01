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

int PmergeMe::getSize(void) const
{
    return (this->_size);
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
        if (num <= 0)
            throw PmergeMe::CustomErrorException();
        this->_vector_arr.push_back(num);
    }
    return ;
}

void PmergeMe::sortVector(void)
{
    if (isSorted<std::vector<int> >(this->_vector_arr))
        return ;

    this->_vector_arr = sortingLogic(this->_vector_arr);

    return ;
}

std::vector<int> PmergeMe::sortingLogic(std::vector<int> cont)
{
    std::vector<int> winner;
    std::vector<int> loser;
    std::vector<int> sorted;
    int temp_num = -1;
    size_t size = cont.size();

    for (size_t ind = 0; ind < size - 1; ind += 2)
    {
        if (cont[ind] > cont[ind + 1])
        {
            winner.push_back(cont[ind]);
            loser.push_back(cont[ind + 1]);
        }
        else
        {
            winner.push_back(cont[ind + 1]);
            loser.push_back(cont[ind]);
        }
    }
    if (size % 2 == 1)
        temp_num = cont[size - 1];

    if (winner.size() == 1)
    {
        sorted.push_back(loser[0]);
        sorted.push_back(winner[0]);
        insertLeftNumber(sorted, temp_num);
        return (sorted);
    }

    sorted = sortingLogic(winner);
    insertFromLoser(sorted, winner, loser);
    insertLeftNumber(sorted, temp_num);

    winner.clear();
    loser.clear();

    return (sorted);
}

void PmergeMe::insertFromLoser(std::vector<int> &sorted, std::vector<int> &winner, std::vector<int> &loser)
{
    std::vector<int>::iterator new_ind;
    std::vector<int>::iterator to_insert;

    for (size_t ind = 0; ind < loser.size(); ind++)
    {
        new_ind = std::lower_bound(sorted.begin(), sorted.end(), winner[ind]);
        to_insert = std::lower_bound(sorted.begin(), new_ind, loser[ind]);
        sorted.insert(to_insert, loser[ind]);
    }
    return ;
}

void PmergeMe::insertLeftNumber(std::vector<int> &sorted, int& last_num)
{
    if (last_num == -1)
        return ;

    std::vector<int>::iterator to_insert = std::lower_bound(sorted.begin(), sorted.end(), last_num);
    sorted.insert(to_insert, last_num);
    return ;
}

void PmergeMe::fillDeque(char** args)
{
    int num;

    for (int ind = 0; ind < this->_size; ind++)
    {
        num = atoi(args[ind]);
        if (num <= 0)
            throw PmergeMe::CustomErrorException();
        this->_deq_arr.push_back(num);
    }
    return ;
}

void PmergeMe::sortDeque(void)
{
    if (isSorted<std::deque<int> >(this->_deq_arr))
        return ;

    this->_deq_arr = sortingLogic(this->_deq_arr);

    return ;
}

std::deque<int> PmergeMe::sortingLogic(std::deque<int> cont)
{
    std::deque<int> winner;
    std::deque<int> loser;
    std::deque<int> sorted;
    int temp_num = -1;
    size_t size = cont.size();

    for (size_t ind = 0; ind < size - 1; ind += 2)
    {
        if (cont[ind] > cont[ind + 1])
        {
            winner.push_back(cont[ind]);
            loser.push_back(cont[ind + 1]);
        }
        else
        {
            winner.push_back(cont[ind + 1]);
            loser.push_back(cont[ind]);
        }
    }
    if (size % 2 == 1)
        temp_num = cont[size - 1];

    if (winner.size() == 1)
    {
        sorted.push_back(loser[0]);
        sorted.push_back(winner[0]);
        insertLeftNumber(sorted, temp_num);
        return (sorted);
    }

    sorted = sortingLogic(winner);
    insertFromLoser(sorted, winner, loser);
    insertLeftNumber(sorted, temp_num);

    winner.clear();
    loser.clear();

    return (sorted);
}

void PmergeMe::insertFromLoser(std::deque<int> &sorted, std::deque<int> &winner, std::deque<int> &loser)
{
    std::deque<int>::iterator new_ind;
    std::deque<int>::iterator to_insert;

    for (size_t ind = 0; ind < loser.size(); ind++)
    {
        new_ind = std::lower_bound(sorted.begin(), sorted.end(), winner[ind]);
        to_insert = std::lower_bound(sorted.begin(), new_ind, loser[ind]);
        sorted.insert(to_insert, loser[ind]);
    }
    return ;
}

void PmergeMe::insertLeftNumber(std::deque<int> &sorted, int& last_num)
{
    if (last_num == -1)
        return ;

    std::deque<int>::iterator to_insert = std::lower_bound(sorted.begin(), sorted.end(), last_num);
    sorted.insert(to_insert, last_num);
    return ;
}
