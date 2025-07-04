#include "RPN.hpp"

bool isNumber(char car)
{
    if (car >= '0' && car <= '9')
        return (true);
    return (false);
}

bool isOperCar(char car)
{
    if (car == '+' || car == '-' || car == '*' || car == '/')
        return (true);
    return (false);
}

int calculateOperation(int& first, int& second, char oper)
{
    switch (oper)
    {
        case '+':
            return (first + second);
        
        case '-':
            return (first - second);

        case '*':
            return (first * second);

        case '/':
            return (first / second);

        default:
            throw RPN::CustomErrorException();
    }
    return (-1);
}

void calcNumbers(RPN& temp_stack, char oper)
{
    int nums[2];

    for (int ind = 1; ind >= 0; ind--)
    {
        if (temp_stack.isEmpty())
            throw RPN::CustomErrorException();
        nums[ind] = temp_stack.pop();
    }

    int result = calculateOperation(nums[0], nums[1], oper);
    temp_stack.push(result);
    return ;
}

int calcAndValidateNumber(char* line)
{
    int num = atoi(line);

    if (num < 0 || num > 10)
        throw RPN::CustomErrorException();
    
    return (num);
}

void runCalculation(char* arg)
{
    RPN temp_stack;
    int result;

    if (!arg[0])
        throw RPN::CustomErrorException();

    for (unsigned int ind = 0; arg[ind]; ind++)
    {
        if (arg[ind] == ' ')
            continue ;

        if (!isNumber(arg[ind]) && !isOperCar(arg[ind]))
            throw RPN::CustomErrorException();

        if (isNumber(arg[ind]))
            temp_stack.push(calcAndValidateNumber(&(arg[ind])));
        
        if (isOperCar(arg[ind]))
            calcNumbers(temp_stack, arg[ind]);
    }
    
    result = temp_stack.pop();
    if (!temp_stack.isEmpty())
        throw RPN::CustomErrorException();
    
    std::cout << result << std::endl;
    return ;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    
    try
    {
        runCalculation(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    
    return (0);
}