#include "PmergeMe.hpp"

void validateArguments(int argc, char **argv)
{
    int num;
    for (int ind = 1; ind < argc; ind++)
    {
        num = atoi(argv[ind]);
        if (num < 0)
            throw PmergeMe::CustomErrorException();
    }
    return ;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return (1);

    try
    {
        validateArguments(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    PmergeMe lists(argc - 1, &(argv[1]));
    std::cout << "Before:\t";
    lists.printArr();

    double vec_sorting = lists.sortingVector();
    double deq_sorting = lists.sortingDeque();

    std::cout << "After: \t";
    lists.printArr();

    std::cout << "Time to process a range of " << lists.getSize() << " elements with std::vector : " << vec_sorting << " us" << std::endl;
    std::cout << "Time to process a range of " << lists.getSize() << " elements with std::deque : " << deq_sorting << " us" << std::endl;
    
    return (0);
}