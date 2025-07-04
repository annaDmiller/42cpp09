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

std::string getSeparator(std::string& line)
{
    if (line.empty())
        throw BitcoinExchange::EmptyFileException();
    return (" | ");
}

float getValueOfInput(std::string& line, std::string& sep)
{
    int len_before_value = 10 + sep.length();
    float value;

    if (line.find('.', len_before_value) == std::string::npos)
        value = static_cast<float>(atol(line.substr(len_before_value, line.length() - len_before_value).c_str()));
    else
        value = atof(line.substr(len_before_value, line.length() - len_before_value).c_str());

    return (value);
}

void verifyLine(std::string& line, std::string& sep)
{
    if (line[4] != '-' || line[7] != '-')
        throw BitcoinExchange::NotValidDateFormat();
    if (line.substr(10, sep.length()) != sep)
    {
        std::cerr << "Error: bad input => " << line;
        throw BitcoinExchange::EmptyException();
    }
    
    int year = atoi(line.substr(0, 4).c_str());
    int month = atoi(line.substr(5, 2).c_str());
    int day = atoi(line.substr(8, 2).c_str());

    if (!checkValidDate(year, month, day))
        throw BitcoinExchange::NotValidDate();

    float value = getValueOfInput(line, sep);
    if (value < 0)
        throw BitcoinExchange::NegativeValue();
    if (value > 1000)
        throw BitcoinExchange::TooLargeValue();
    return ;
}

void verifyCalculateAndPrint(std::string& line, std::string& sep, BitcoinExchange& ex_rates)
{
    try
    {
        verifyLine(line, sep);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return ;
    }

    int len_before_value = 10 + sep.length();
    float value = getValueOfInput(line, sep);
    std::string date = line.substr(0, 10);

    std::cout << line.substr(0, 10) << " => ";
    std::cout << line.substr(len_before_value, line.length() - len_before_value) << " => ";
    std::cout << value * ex_rates.findExchangeRate(date) << std::endl;
    return;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cerr << "Error: waiting for input file path as argument." << std::endl;
        return (1);
    }
    
    BitcoinExchange exchange_rates;
    if (exchange_rates.getExceptionFlag())
        return (1);

    std::ifstream* input_file = NULL;
    std::string line;
    try
    {
        input_file = open_input_file(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    getline(*input_file, line);   
    std::string separator;     
    try
    {
        separator = getSeparator(line);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        input_file->close();
        delete input_file;
        return (1);
    }
    
    while(getline(*input_file, line))
    {
        verifyCalculateAndPrint(line, separator, exchange_rates);
    }

    input_file->close();
    delete input_file;
    return (0);
}

