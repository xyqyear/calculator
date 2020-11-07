#include "calculator.h"

double evalSingleExpression(double operand0, double operand1, char _operator)
{
    switch (_operator)
    {
    case '+':
        return operand0 + operand1;
    case '-':
        return operand0 - operand1;
    case '*':
        return operand0 * operand1;
    case '/':
        return operand0 / operand1;
    case '%':
        return fmod(operand0, operand1);
    case '^':
        return pow(operand0, operand1);
    case '&':
        return pow(operand0, 1 / operand1);
    }
    return 0;
}

int getInStackPrecedence(char _operator)
{
    switch (_operator)
    {
    case '=':
        return 0;
    case '+':
        return 3;
    case '-':
        return 3;
    case '*':
        return 5;
    case '/':
        return 5;
    case '%':
        return 5;
    case '(':
        return 1;
    case ')':
        return 8;
    case '^':
        return 6;
    case '&':
        return 6;
    }
    return -1;
}

int getOutStackPrecedence(char _operator)
{
    switch (_operator)
    {
    case '=':
        return 0;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 4;
    case '/':
        return 4;
    case '%':
        return 4;
    case '(':
        return 8;
    case ')':
        return 1;
    case '^':
        return 7;
    case '&':
        return 7;
    }
    return -1;
}

void tokenizeExpression(vector<string>& tokens, string& expression)
{
    size_t start = 0;
    size_t expression_size = expression.size();
    for (size_t i = 0; i < expression_size; i++)
    {
        char current_char = expression[i];
        // if the current char isn't a digit nor a part of a number
        if (!(isdigit(current_char) || current_char == '.'))
        {
            // if we have digits left to parse
            if (i - start > 0)
            {
                string current_token = expression.substr(start, i - start);
                tokens.push_back(current_token);
            }

            // if the currernt char is a space then we ignore it
            if (current_char == ' ')
                continue;

            // if the current char is '-', then we need to know
            // if it's and unary operator or an binocular operator
            // (if it's an negative number then we can also treat it as an unary '-' plus a nubmer)
            if (current_char == '-')
            {
                // if this is the first token we've ever parsed
                // then it must be an unary operator
                // then we simply push a '0' to the stack
                if (tokens.empty())
                {
                    tokens.push_back("0");
                    continue;
                }

                char lastChar = expression[i - 1];
                // if the charact before '-' is not a nubmer nor a right parenthesis
                // then it it an unary operator
                if (!(lastChar == ')' || isdigit(lastChar)))
                {
                    tokens.push_back("0");
                    continue;
                }
            }
            tokens.push_back(string(1, current_char));
            start = i + 1;
        }
    }
    // if we still have digits left to parse
    if (start < expression_size)
    {
        string current_token = expression.substr(start, expression_size - start);
        tokens.push_back(current_token);
    }
    if (tokens.back() != "=")
        tokens.push_back("=");
}

// the return value is for error detection
bool evaluateTokenizedExpression(vector<string>& expression_tokens, double* result)
{
    LStack<char> operatorStack;
    LStack<double> operandStack;

    for (auto token : expression_tokens)
    {
        // we use the last character of the token string 
        // to see if it's a number or not
        char tokenLastChar = token.back();
        if (isdigit(tokenLastChar))
        {
            operandStack.push(stod(token));
        }
        else if (getInStackPrecedence(tokenLastChar) != -1)
        {
            int tokenOutStackPrecedence = getOutStackPrecedence(tokenLastChar);
            while (1)
            {
                int stackTopInStackPrecedence;
                // if operator stack is empty, we simply put the operator in
                if (operatorStack.length() == 0)
                    stackTopInStackPrecedence = -1;
                else
                    stackTopInStackPrecedence = getInStackPrecedence(operatorStack.topValue());

                if (stackTopInStackPrecedence < tokenOutStackPrecedence)
                {
                    operatorStack.push(tokenLastChar);
                    break;
                }
                else if (stackTopInStackPrecedence == tokenOutStackPrecedence)
                {
                    if (operatorStack.length() > 0)
                        operatorStack.pop();
                    else
                        return false;
                    break;
                }
                else
                {
                    if (operandStack.length() < 2 || operatorStack.length() == 0)
                        return false;
                    double operand0 = operandStack.topValue();
                    operandStack.pop();
                    double operand1 = operandStack.topValue();
                    operandStack.pop();
                    char stackTopOperator = operatorStack.topValue();
                    operatorStack.pop();
                    operandStack.push(evalSingleExpression(operand1, operand0, stackTopOperator));
                }
            }
        }
        else
            return false;
    }
    *result = operandStack.topValue();
    return true;
}

// the return value is for error detection
bool evaluateStringExpression(string& expression, double* result)
{
    vector<string> tokens;
    tokenizeExpression(tokens, expression);
    return evaluateTokenizedExpression(tokens, result);
}
