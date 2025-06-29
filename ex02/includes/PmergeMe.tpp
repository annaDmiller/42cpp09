template <typename Container> bool PmergeMe::isSorted(Container& cont) const
{
    for (unsigned long ind = 0; ind < cont.size() - 1; ind++)
    {
        if (cont[ind] > cont[ind + 1])
            return (false);
    }
    return (true);
}
