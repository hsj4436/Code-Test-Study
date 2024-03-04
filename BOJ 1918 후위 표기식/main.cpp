#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::string midterm;
    std::cin >> midterm;

    std::vector<char> answer;
    std::stack<char> operator_stk;

    for (int i = 0; i < midterm.size(); i++) {
        if ('A' <= midterm[i] && midterm[i] <= 'Z') {
            answer.push_back(midterm[i]);
        } else if (midterm[i] == '*' || midterm[i] == '/') {
            if (!operator_stk.empty()) {
                if (operator_stk.top() == '*' || operator_stk.top() == '/') {
                    answer.push_back(operator_stk.top());
                    operator_stk.pop();
                }
            }
            operator_stk.push(midterm[i]);
        } else if (midterm[i] == '+' || midterm[i] == '-') {
            if (!operator_stk.empty()) {
                if (operator_stk.top() == '*' || operator_stk.top() == '/') {
                    while (!operator_stk.empty()) {
                        if (operator_stk.top() == '(') {
                            break;
                        }
                        answer.push_back(operator_stk.top());
                        operator_stk.pop();
                    }
                } else if (operator_stk.top() == '+' || operator_stk.top() == '-') {
                    answer.push_back(operator_stk.top());
                    operator_stk.pop();
                }
            }
            operator_stk.push(midterm[i]);
        } else if (midterm[i] == '(') {
            operator_stk.push(midterm[i]);
        } else {
            while (operator_stk.top() != '(') {
                answer.push_back(operator_stk.top());
                operator_stk.pop();
            }
            operator_stk.pop();
        }
    }

    while (!operator_stk.empty()) {
        answer.push_back(operator_stk.top());
        operator_stk.pop();
    }

    for (char ch : answer) {
        std::cout << ch;
    }

    return 0;
}