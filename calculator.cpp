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

void tokenizeExpression(vector<string>& tokens, string expression)
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
                string& current_token = expression.substr(start, i - start);
                tokens.push_back(current_token);
            }

            // if the currernt char is a space then we ignore it
            if (current_char == ' ')
                continue;

            // if the current char is '-', then we need to know
            // if it belongs to a nubmer or it's an operator
            if (current_char == '-')
            {
                // if this is the first token we've ever parsed
                // then it must belong to the next number
                if (tokens.empty())
                    continue;
                char lastChar = expression[i - 1];
                // if the charact before '-' is not a nubmer nor a right parenthesis
                // then it means this '-' belongs to the next number
                if (!(lastChar == ')' || isdigit(lastChar)))
                    continue;
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
    vector<char> operatorStack;
    vector<double> operandStack;

    for (auto token : expression_tokens)
    {
        // we use the last character of the token string 
        // to see if it's a number or not
        char tokenLastChar = token.back();
        if (isdigit(tokenLastChar))
        {
            operandStack.push_back(stod(token));
        }
        else if (getInStackPrecedence(tokenLastChar) != -1)
        {
            int tokenOutStackPrecedence = getOutStackPrecedence(tokenLastChar);
            while (1)
            {
                int stackTopInStackPrecedence;
                // if operator stack is empty, we simply put the operator in
                if (operatorStack.empty())
                    stackTopInStackPrecedence = -1;
                else
                    stackTopInStackPrecedence = getInStackPrecedence(operatorStack.back());

                if (stackTopInStackPrecedence < tokenOutStackPrecedence)
                {
                    operatorStack.push_back(tokenLastChar);
                    break;
                }
                else if (stackTopInStackPrecedence == tokenOutStackPrecedence)
                {
                    operatorStack.pop_back();
                    break;
                }
                else
                {
                    if (operandStack.size() < 2 || operatorStack.size() == 0)
                        return false;
                    double operand0 = operandStack.back();
                    operandStack.pop_back();
                    double operand1 = operandStack.back();
                    operandStack.pop_back();
                    char stackTopOperator = operatorStack.back();
                    operatorStack.pop_back();
                    operandStack.push_back(evalSingleExpression(operand1, operand0, stackTopOperator));
                    continue;
                }
            }
        }
        else
            return false;
    }
    *result = operandStack.back();
    return true;
}

// the return value is for error detection
bool evaluateStringExpression(string& expression, double* result)
{
    vector<string> tokens;
    tokenizeExpression(tokens, expression);
    return evaluateTokenizedExpression(tokens, result);
}
