#include <stack>
#include <vector>
#include <string>
#include <iostream>


bool is_operator(const char & c){
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':   return true; 
        default:    return false; 
    }
}

bool is_num(const char & c){
    if (((c >= '0') && (c <= '9')) || (c == '.') || (c == 'E') || (c == 'e'))
        return true; 
    return false; 
}

bool is_bracket(const char & c){
    if ((c == '(') || (c == ')'))
        return true; 
    return false;
}


bool infix_check(const std::string &str){
    std::stack<char> bracket_stack;

    // 表达式以运算符开头或结尾
    if (is_operator(str[0]) || is_operator(str[str.size()-1])){
        if (str[0] == '-') {
            if (!is_num(str[1])){    // 不是负数
                std::cout << "Expressions begin or end with an operator. "; 
                return false; 
            }
        } else {
            std::cout << "Expressions begin or end with an operator. "; 
            return false; 
        }
    }

    // 存在非法字符
    for(std::string::size_type i = 0; i < str.size(); ++i){
        if ((!is_operator(str[i])) && (!is_num(str[i])) && (!is_bracket(str[i]))){
            std::cout << "Illegal characters are present. "; 
            return false; 
        }
    }

    // 数字不合法，如 .10, 0.43.5, 1.23e1.23 等
    for(std::string::size_type i = 0; i < (str.size()-1); ++i){
        if (is_num(str[i])) {
            if ((str[i] == '.') || (str[i] == 'e') || (str[i] == 'E')) {
                std::cout << "Numbers are not legitimate. "; 
                return false; 
            }
            
            std::string::size_type j = i+1; 
            int dot_num = 0, e_num = 0; 
            while (is_num(str[j])){
                if (str[j] == '.')
                    ++dot_num;
                if ((str[j] == 'e') || (str[j] == 'E')){
                    ++e_num;
                    if ((str[j+1] == '-') && (!is_num(str[j+2]))) {
                        std::cout << "Numbers are not legitimate. "; 
                        return false; 
                    } else if (!is_num(str[j+1]) && (str[j+1] != '-')){
                        std::cout << "Numbers are not legitimate. "; 
                        return false; 
                    } 
                }
                if ((dot_num > 1) || (e_num > 1)) {
                    std::cout << "Numbers are not legitimate. "; 
                    return false; 
                }
                ++j;
            }
            i = j-1; 
        }
    }

    
    // 括号不匹配
    for(std::string::size_type i = 0; i < str.size(); ++i){
        if (str[i] == '('){ 
            bracket_stack.push(str[i]);
        } else if (str[i] == ')'){ 
            if(!bracket_stack.empty())
                bracket_stack.pop(); 
            else {
                std::cout << "The parentheses do not match. "; 
                return false; 
            }
        }
    }
    if (!bracket_stack.empty()){
        std::cout << "The parentheses do not match. "; 
        return false; 
    }

    // 运算符连续使用
    for(std::string::size_type i = 0; i < (str.size()-1); ++i){
        if ((is_operator(str[i])) && (is_operator(str[i+1]))) {
            if (str[i+1] == '-') { 
                if (!is_num(str[i+2])){    // 不是负数
                    std::cout << "The operator is used continuously. "; 
                    return false; 
                }
            } else {
                std::cout << "The operator is used continuously. "; 
                return false; 
            }
        } 
    }

    // 左括号后和右括号前不能是运算符
    for(std::string::size_type i = 0; i < (str.size()-1); ++i){
        if ((str[i] == '(') && (is_operator(str[i+1]))) {
            if (str[i+1] != '-') {
                std::cout << "After the opening parenthesis cannot be operators. "; 
                return false; 
            } else if (!is_num(str[i+2])) {    // 不是负数
                std::cout << "After the opening parenthesis cannot be operators. "; 
                return false; 
            }
        } else if (is_operator(str[i]) && (str[i+1] == ')')) {
            std::cout << "Before the closing parenthesis cannot be operators. "; 
            return false; 
        }
    }

    // 除数是 0
    for(std::string::size_type i = 0; i < (str.size()-1); ++i){
        if (str[i] == '/') {
            if (str[i+1] != '(') {
                std::string::size_type j = i+1;
                while ((str[j] != '\0') && (!is_operator(str[j]))){
                    ++j;  
                }
                std::string divisor(str, i+1, j-1);
                double num = std::stod(divisor);
                if (num == 0.0){
                    std::cout << "divisor = " << num << ". ";
                    return false;
                }
                i = j-1; 
            }
        }
    }

    return true; 
}



void infix2postfix(const std::string &str, std::string &post){
    std::stack<char> infix_stack;
    std::string::size_type i = 0; 

    if (str[0] == '-'){
        post.push_back(str[0]);
        i = 1; 
    }

    for( ; i < str.size(); ++i){
        if (str[i] == '('){ 
            // 遇到左括号就放入 stack 中
            infix_stack.push(str[i]);
        } else if (str[i] == ')'){    
            // 遇到右括号则将左括号之前的都弹出
            while(infix_stack.top() != '('){
                post.push_back(infix_stack.top()); 
                infix_stack.pop();
            }
            infix_stack.pop();      // 不要忘记把'(' pop 出去
            post.push_back(' ');
        } else if ((str[i] == '*') || (str[i] == '/')){
            // 遇到乘除则将栈中的(*, /)全部弹出
            while ((!infix_stack.empty()) && ((infix_stack.top() == '*') || (infix_stack.top() == '/'))){
                post.push_back(infix_stack.top());
                infix_stack.pop();
            }
            infix_stack.push(str[i]);
            post.push_back(' ');
        } else if ((str[i] == '+') || (str[i] == '-')){
            if ((str[i] == '-') && (is_operator(str[i-1]) || (str[i-1] == '(') || (str[i-1] == 'e') || (str[i-1] == 'E'))){
                post.push_back(str[i]);
            } else {
                // 遇到加减则将栈中的(+, -, *, /)全部弹出
                while ((!infix_stack.empty()) && (is_operator(infix_stack.top()))){
                    post.push_back(infix_stack.top());
                    infix_stack.pop();
                }
                infix_stack.push(str[i]);
                post.push_back(' ');
            }
        } else {
            post.push_back(str[i]);
        }
    }
    // 式子结束则将 stack 中的内容全部弹出
    while (!infix_stack.empty()) {
        post.push_back(infix_stack.top()); 
        infix_stack.pop();
    }
    
    std::cout << "postfix: " << post << std::endl;
}



double cal_post(const std::string &str){
    std::stack<double> num_stack;

    for(std::string::size_type i = 0; i < str.size(); ++i){ 
        if ((is_num(str[i])) || ((str[i] == '-') && is_num(str[i+1]))) {
            std::string::size_type j = i+1;
            while (is_num(str[j])){
                if ((str[j] == 'e') || (str[j] == 'E')) {
                    if (str[j+1] == '-')
                        j = j+2; 
                } else {
                    ++j;
                }
            }
            std::string num = str.substr(i, j-i);
            double number = std::stod(num);
            num_stack.push(number);
            // std::cout << "num = " << num << ", ";
            i = j-1; 
        } else if (is_operator(str[i])) {
            double a = num_stack.top();     // get the first operator
            num_stack.pop();
            double b = num_stack.top();     // get the second operator
            num_stack.pop();

            switch (str[i]) {
                case '+': num_stack.push(a + b); break; 
                case '-': num_stack.push(b - a); break; 
                case '*': num_stack.push(a * b); break;
                case '/': 
                    if (a == 0)
                        std::cout << "divisor = 0, Invalid. "; 
                    num_stack.push(b / a); 
                    break;
                default: break;
            }
        }
    } 

    return num_stack.top();
}