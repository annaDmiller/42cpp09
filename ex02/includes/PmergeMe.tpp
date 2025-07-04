template <typename Container> bool PmergeMe::isSorted(Container& cont) const
{
    for (unsigned long ind = 0; ind < cont.size() - 1; ind++)
    {
        if (cont[ind] > cont[ind + 1])
            return (false);
    }
    return (true);
}

template <typename Container> Container PmergeMe::generateJacobsthalSequence(size_t size)
{
    Container result;
    std::set<size_t> used;
    size_t j0 = 0, j1 = 1;
    size_t jn;

    while ((jn = j1 + 2 * j0) < size)
    {
        if (used.insert(j1).second)
            result.push_back(j1);
        j0 = j1;
        j1 = jn;
    }

    for (size_t ind = 0; ind < size; ind++)
    {
        if (used.insert(ind).second)
            result.push_back(ind);
    }
    return (result);
}