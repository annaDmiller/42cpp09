#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fstream>
# include <cstdlib>
# include <map>
# include <ctime>

class   BitcoinExchange
{
    private:
        std::map<std::string, float> _rates;
        bool _exception_caught;

        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);

        std::ifstream* openCSVFile(void);
        void checkDate(std::string& line, int& line_num) const;
        void addValueToMap(std::string& line, int& line_num,
        std::pair<std::map<std::string, float>::iterator, bool> &dupl_check);

    public:
        BitcoinExchange();
        ~BitcoinExchange();

        float findExchangeRate(std::string& date) const;
        bool getExceptionFlag(void) const;

    class NotValidDateFormat : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class CanNotOpenFile : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class DuplicateValueInMap : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class NotValidDate : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class NegativeValue : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class TooLargeValue : public std::exception
    {
        virtual const char* what(void) const throw();
    };

    class EmptyException : public std::exception
    {
        virtual const char* what(void) const throw();
    };
};

bool checkValidDate(int& year, int& month, int& day);
bool isLeapYear(int& year);

#endif