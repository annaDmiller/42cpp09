#include "PmergeMe.hpp"

void inputArgumentsToVector(std::vector<int> &vec, char** args)
{
    int num;

    for (unsigned long ind = 0; args[ind] != NULL; ind++)
    {
        num = atoi(args[ind]);
        vec.push_back(num);
    }
    return ;
}

void printArr(std::vector<int> &vec)
{
    for (unsigned long ind = 0; ind < vec.size(); ind++)
        std::cout << vec[ind] << " ";
    std::cout << std::endl;
    return ;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return (1);

    std::vector<int> temp_args;
    inputArgumentsToVector(temp_args, &(argv[1]));
    PmergeMe lists(argc - 1);

    std::clock_t start_vector = std::clock();
    try
    {
        lists.fillVector(&(argv[1]));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    lists.sortVector();
    std::clock_t end_vector = std::clock();

    std::clock_t start_deque = std::clock();
    lists.fillDeque(&(argv[1]));
    lists.sortDeque();
    std::clock_t end_deque = std::clock();

    std::cout << "Before:\t";
    printArr(temp_args);
    std::cout << "After: \t";
    lists.printArr();
    std::cout << "Time to process a range of " << lists.getSize() << " elements with std::vector : " << (end_vector - start_vector) << " us" << std::endl;
    std::cout << "Time to process a range of " << lists.getSize() << " elements with std::deque : " << (end_deque - start_deque) << " us" << std::endl;
    
    return (0);
}