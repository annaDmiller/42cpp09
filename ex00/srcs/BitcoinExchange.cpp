#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) 
{
    std::ifstream* csv_file;

    try
    {
        csv_file = openCSVFile();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }

    std::string line;
    int line_num = 0;
    std::pair<std::map<std::string, float>::iterator, bool> dupl_check;

    if (getline(*csv_file, line))
    {
        while (getline(*csv_file, line))
        {
            line_num++;
            try
            {
                checkDate(line, line_num);
                addValueToMap(line, line_num, dupl_check);       
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                csv_file->close();
                delete csv_file;
                return;
            }
        }
    }

    csv_file->close();
    delete csv_file;
}

BitcoinExchange::~BitcoinExchange()
{
    return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    (void) other;
    return ;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    (void) other;
    return (*this);
}

void BitcoinExchange::checkDate(std::string& line, int& line_num) const
{   
    std::string test = "Hello";

    if (line[4] != '-' || line[7] != '-' || line[10] != ',')
    {
        std::cerr << "CSV File : Line " << line_num << " - ";
        throw BitcoinExchange::NotValidDateFormat();
    }
    
    int year = atoi(line.substr(0, 4).c_str());
    int month = atoi(line.substr(5, 2).c_str());
    int day = atoi(line.substr(8, 2).c_str());

    if (!checkValidDate(year, month, day))
    {
        std::cerr << "CSV File : Line " << line_num << " - ";
        throw BitcoinExchange::NotValidDate();
    }
    return ;
}

void BitcoinExchange::addValueToMap(std::string& line, int& line_num,
    std::pair<std::map<std::string, float>::iterator, bool> &dupl_check)
{
    std::string date = line.substr(0, 10);
    float exch_rate = atof(line.substr(11, line.length() - 11).c_str());

    dupl_check = this->_rates.insert(std::make_pair(date, exch_rate));
    if (!dupl_check.second)
    {
        std::cerr << "CSV File : Line " << line_num << " - ";
        throw BitcoinExchange::DuplicateValueInMap();
    }
    return ;
}

std::ifstream* BitcoinExchange::openCSVFile(void)
{
    std::ifstream* filename = new std::ifstream("data.csv");
    if (!filename->is_open())
        throw BitcoinExchange::CanNotOpenFile();
    return (filename);
}

float BitcoinExchange::findExchangeRate(std::string& date) const
{
    return (0);
}

const char* BitcoinExchange::NotValidDateFormat::what(void) const throw()
{
    return ("Error: invalid date format in file.");
}

const char* BitcoinExchange::CanNotOpenFile::what(void) const throw()
{
    return ("Error: could not open file.");
}

const char* BitcoinExchange::DuplicateValueInMap::what(void) const throw()
{
    return ("Error: duplicate dates in CSV file.");
}

const char* BitcoinExchange::NotValidDate::what(void) const throw()
{
    return ("Error: date value is invalid.");
}

bool checkValidDate(int& year, int& month, int& day)
{
    if (month < 1 || month > 12)
        return (false);
    
    const int days_in_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int max_day = days_in_month[month - 1];
    if (month == 2 && isLeapYear(year))
        max_day = 29;
        
    if (day < 1 || day > max_day)
        return (false);

    std::time_t now =  std::time(NULL);
    if (year > 1900 + std::localtime(&now)->tm_year)
        return (false);
    
    return (true);
}

bool isLeapYear(int &year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
