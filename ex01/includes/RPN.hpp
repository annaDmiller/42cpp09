#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <exception>
# include <list>
# include <cstdlib>

class RPN
{
    private:
        std::list<int> _stack;

        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

    public:
        RPN(void);
        ~RPN(void);

        void push(int value);
        int pop(void);
        bool isEmpty(void) const;
    
    class CustomErrorException : public std::exception
    {
        virtual const char* what(void) const throw();
    };
};

#endif