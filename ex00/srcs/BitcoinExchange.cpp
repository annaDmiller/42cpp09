#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) : _exception_caught(false)
{
    std::ifstream* csv_file;

    try
    {
        csv_file = openCSVFile();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        _exception_caught = true;
        return;
    }

    std::string line;
    int line_num = 0;
    std::pair<std::map<std::string, float>::iterator, bool> dupl_check;

    getline(*csv_file, line);
    if (line.empty())
    {
        csv_file->close();
        delete csv_file;
        this->_exception_caught = true;
        std::cerr << "Error: the CSV file is empty." << std::endl;
        return ;
    }
    
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
            _exception_caught = true;
            return;
        }
    }

    csv_file->close();
    delete csv_file;
    return ;
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

float BitcoinExchange::findExchangeRate(std::string& date)
{
    float ex_rate = 0;

    for (std::map<std::string, float>:: iterator it = this->_rates.begin(); it != this->_rates.end(); it++)
    {
        if (date == it->first)
            return (it->second);

        if (date > it->first)
            ex_rate = it->second;
        
        if (date < it->first)
            return (ex_rate);
    }
    return (0);
}

bool BitcoinExchange::getExceptionFlag(void) const
{
    return (this->_exception_caught);
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

const char* BitcoinExchange::TooLargeValue::what(void) const throw()
{
    return ("Error: too large number.");
}

const char* BitcoinExchange::NegativeValue::what(void) const throw()
{
    return ("Error: not a positive number.");
}

const char* BitcoinExchange::EmptyException::what(void) const throw()
{
    return ("");
}

const char* BitcoinExchange::EmptyFileException::what(void) const throw()
{
    return ("Error: the file is empty.");
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
    struct tm* now_tm = localtime(&now);
    if (!now_tm)
        return (false);

    now_tm->tm_hour = 0;
    now_tm->tm_min = 0;
    now_tm->tm_sec = 0;
    time_t today_time = mktime(now_tm);
    
    struct tm input_tm = {};
    input_tm.tm_year = year - 1900;
    input_tm.tm_mon = month - 1;
    input_tm.tm_mday = day;
    input_tm.tm_hour = 0;
    input_tm.tm_min = 0;
    input_tm.tm_sec = 0;
    time_t input_time = mktime(&input_tm);
    if (input_time == -1)
        return (false);

    if (input_time > today_time)
        return (false);

    return (true);
}

bool isLeapYear(int &year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
