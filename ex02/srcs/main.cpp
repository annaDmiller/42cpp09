#include "PmergeMe.hpp"

void inputArgumentsToVector(std::vector<int> &vec, char** args)
{
    int num;

    for (int ind = 0; args[ind] != NULL; ind++)
    {
        num = atoi(args[ind]);
        vec.push_back(num);
    }
    return ;
}

void printArr(std::vector<int> &vec)
{
    for (int ind = 0; ind < vec.size(); ind++)
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

    std::cout << "Before:\t";
    printArr(temp_args);
    std::cout << "After: \t";
    lists.printArr();
    //std::cout << "Time to process a range of " << lists.getSize() << " elements with std::vector : " << vec_sorting << " us" << std::endl;
    //std::cout << "Time to process a range of " << lists.getSize() << " elements with std::deque : " << deq_sorting << " us" << std::endl;
    
    return (0);
}