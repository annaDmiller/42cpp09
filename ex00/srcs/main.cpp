#include "BitcoinExchange.hpp"

std::ifstream *open_input_file(char *addr)
{
    if (addr == NULL)
        throw BitcoinExchange::CanNotOpenFile();
    std::ifstream* file = NULL;
    file = new std::ifstream(addr);
    if (!file->is_open())
    {
        delete file;
        throw BitcoinExchange::CanNotOpenFile();
    }
    return (file);
}

int main(int argc, char** argv)
{
    try
    {
        if (argc == 1)
            open_input_file(NULL);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(1);
    }
    
    BitcoinExchange exchange_rates;
    if (exchange_rates.getExceptionFlag())
        return (1);

    std::ifstream* input_file = NULL;
    try
    {
        input_file = open_input_file(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    input_file->close();
    delete input_file;
    return (0);
}

