#include "expression_evaluator.h"
#include <iostream>
#include <ctime>
#include <cmath>


// 生成随机数
double random_double() {
    return static_cast<double>(rand()) / RAND_MAX * 100; // 生成0到100之间的随机浮点数
}

// 生成随机操作符
char random_operator() {
    int op = rand() % 4;
    switch (op) {
        case 0: return '+';
        case 1: return '-';
        case 2: return '*';
        case 3: return '/';
        default: return '+';
    }
}

// 生成随机表达式
std::string generate_random_expression(int depth) {
    if (depth == 0) {
        return std::to_string(random_double());
    } else {
        std::string expr = "(" + generate_random_expression(depth - 1) + random_operator() + generate_random_expression(depth - 1) + ")";
        return expr;
    }
}

// 测试函数
void test_expression(const std::string &expr) {
    std::string postfix;
    std::cout << "Testing expression: " << expr << std::endl;

    if (!infix_check(expr)) {
        std::cout << "ILLEGAL" << std::endl;
        return;
    }

    infix2postfix(expr, postfix);
    double result = cal_post(postfix);
    std::cout << "Calculated result: " << result << std::endl;
}

void test_with_random_expression() {
    srand(time(0)); // 初始化随机数种子
    int num_tests = 10; // 测试次数

    for (int i = 0; i < num_tests; ++i) {
        int depth = rand() % 5 + 1; // 随机深度，1到10
        std::string expr = generate_random_expression(depth);

        test_expression(expr);
        std::cout << std::endl;
    }
}

void test_with_fix_expression() {
    std::vector<std::string> expressions = {
        ".1+1", "0.99+.88", "e12", "3+1.02e1.9", "22e2e4*8", 
        "(10+5", "10+5)", "(*3.003)", "(1.9+)", 
        "+10-5", "*7+8", "--7+8", "1++2.1"
        "0.0/0.00", "(5+3)/0", 
        "ten+five", "3.14.5.2", "(10a+5)", 
        "-7+8", "5+-7", "7*-7", 
        "(-7)*8+9", "(-5.5+9)*7-1", "-6.3+(-7*9)+-1.8", 
        "1.2e-10+11", "22.34e-1*10", 
        "1+1/(1-1)", 
        "(10+(5*2))-3", "((10.9+3.0)*9.6/8.1)", "10+(5-3)/2"
    };

    for (const std::string& exp : expressions) {
        test_expression(exp);
        std::cout << std::endl;
    }
}

int main() {
    test_with_fix_expression(); 
    test_with_random_expression();

    return 0;
}

