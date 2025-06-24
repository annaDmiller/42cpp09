#include "RPN.hpp"

RPN::RPN(void)
{
    return ;
}

RPN::~RPN(void)
{
    return ;
}

RPN::RPN(const RPN& other)
{
    (void) other;
    return ;
}

RPN& RPN::operator=(const RPN& other)
{
    (void) other;
    return (*this);
}

void RPN::push(int value)
{
    this->_stack.push_front(value);
    return ;
}

int RPN::pop(void)
{
    int ret_value = this->_stack.front();
    this->_stack.pop_front();
    return (ret_value);
}

bool RPN::isEmpty(void) const
{
    if (this->_stack.empty())
        return (true);
    return (false);
}

const char* RPN::CustomErrorException::what(void) const throw()
{
    return ("Error");
}
