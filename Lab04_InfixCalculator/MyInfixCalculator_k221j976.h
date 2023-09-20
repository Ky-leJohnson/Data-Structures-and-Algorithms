#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>

#include "MyStack_k221j976.h"
#include "MyVector_k221j976.h"


class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s)
    {
        // code begins
        MyVector<std::string> tokens;
        return tokenize(s, tokens);
        
        // code ends
    }

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 3;
            case '/':
                return 3;
            case '+':
                return 2;
            case '-':
                return 2;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    // tokenizes an infix string s into a set of tokens (operands or operators)
    double tokenize(const std::string& s, MyVector<std::string>& tokens)
{
    for (int i = 0; i < s.size(); ++i) {
        if (isdigit(s[i]) || s[i] == '.') {
            std::string num;
            while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) {
                num += s[i++];
            }
            tokens.push_back(num);
            --i;
        } else if (s[i] == '-') {
            if (i == 0 || (!isdigit(s[i-1]) && s[i-1] != ')')) {
                std::string num = "-";
                ++i;
                while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) {
                    num += s[i++];
                }
                tokens.push_back(num);
                --i;
            } else {
                tokens.push_back("-");
            }
        } else {
            tokens.push_back(std::string(1, s[i]));
        }
    }
    MyVector<std::string> postfix_tokens;
    return (infixToPostfix(tokens, postfix_tokens));
}



    // converts a set of infix tokens to a set of postfix tokens
    double infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        // code begins
        MyStack<std::string>stack;
    
        for(int c = 0; c < infix_tokens.size();c++)
        {
            if (infix_tokens[c] == "(")
            {
                stack.push(infix_tokens[c]);
            }
            if ((infix_tokens[c] == "+") or (infix_tokens[c] == "-") or (infix_tokens[c] == "*") or (infix_tokens[c] == "/"))
                {
                if (stack.size() != 0 and (stack.top() != "("))
                {
                    while((operatorPrec(infix_tokens[c][0]))<= (operatorPrec(stack.top()[0])) and (stack.top()!= "(") )
                    {
                    std::string temp = stack.top();
                    stack.pop();
                    postfix_tokens.push_back(temp);
                    if (stack.empty())
                    {
                        break;
                    }
                    }
                stack.push(infix_tokens[c]);
                }
                else
                {
                    stack.push(infix_tokens[c]);
                    }
                }

            if (infix_tokens[c] == ")")
            {
                while(stack.top() != "(")
                {
                    std::string temp = stack.top();
                    stack.pop();
                    postfix_tokens.push_back(temp);
                }
            stack.pop();
            }

            if ((infix_tokens[c] != "+") and (infix_tokens[c] != "-") and (infix_tokens[c] != "*") and (infix_tokens[c] != "/") and (infix_tokens[c] != "(") and (infix_tokens[c] != ")")) 
            {
            postfix_tokens.push_back(infix_tokens[c]);
            }

            
        // code ends

        }
        while (!stack.empty())
        {
            std::string temp = stack.top();
            stack.pop();
            postfix_tokens.push_back(temp);

        }

        return (calPostfix(postfix_tokens));
    }
    

    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        // code begins
         MyStack<std::string>stack;
        for(int c = 0; c < postfix_tokens.size();c++)
        {
        if ((postfix_tokens[c] != "+") and (postfix_tokens[c] != "-") and (postfix_tokens[c] != "*") and (postfix_tokens[c] != "/"))
        {
            stack.push(postfix_tokens[c]);
        }
        else{
            std::string temp1 = stack.top();
            stack.pop();
            std::string temp2 = stack.top();
            stack.pop();
            double calculate = computeBinaryOperation(temp2,temp1,postfix_tokens[c]);
            std::string s = std::to_string(calculate);
            stack.push(s);
        }
        }
        double return_val = std::stod(stack.top());
        return return_val;
        // code ends
    }
};

#endif // __MYINFIXCALCULATOR_H__