#include <iostream>
#include <stack>
#include <queue>

std::string str;
std::string exp;

int main() {
    std::cin >> str >> exp;

    std::stack<char> stk;
    std::stack<char> tmp;
    for (int i = 0; i < str.size(); i++) {
        auto it = exp.find(str[i]);
        if (it == std::string::npos) {
            stk.push(str[i]);
            continue;
        }

        if (it == 0) {
            if (str.substr(i, exp.size()) == exp) {
                i += exp.size() - 1;
            } else {
                stk.push(str[i]);
            }
        } else if (it == exp.size() - 1) {
            int index = exp.size() - 2;
            if (stk.empty() || stk.size() < exp.size() - 1) {
                stk.push(str[i]);
                continue;
            }
            while (index != -1) {
                if (exp[index] == stk.top()) {
                    tmp.push(stk.top());
                    stk.pop();
                    index--;
                } else {
                    break;
                }
            }
            if (index == -1) {
                while (!tmp.empty()) {
                    tmp.pop();
                }
            } else {
                while (!tmp.empty()) {
                    stk.push(tmp.top());
                    tmp.pop();
                }
                stk.push(str[i]);
            }
        } else {
            if (stk.empty() || stk.size() < it - 1 || str.size() - 1 - it < exp.size() - 1 - it) {
                stk.push(str[i]);
                continue;
            }
            bool check_right = true;
            int index = it;
            for (int j = i; j < i + (exp.size() - it); j++) {
                if (str[j] != exp[index]) {
                    check_right = false;
                    break;
                }
                index++;
            }
            if (!check_right) {
                stk.push(str[i]);
                continue;
            }
            bool check_left = true;
            index = it - 1;
            while (index != -1) {
                if (exp[index] == stk.top()) {
                    tmp.push(stk.top());
                    stk.pop();
                    index--;
                } else {
                    check_left = false;
                    break;
                }
            }
            if (check_left) {
                while (!tmp.empty()) {
                    tmp.pop();
                }
                i += exp.size() - it - 1;
            } else {
                while (!tmp.empty()) {
                    stk.push(tmp.top());
                    tmp.pop();
                }
                stk.push(str[i]);
            }
        }
    }

    if (stk.empty()) {
        std::cout << "FRULA";
        return 0;
    }

    std::deque<char> dq;
    while (!stk.empty()) {
        dq.push_front(stk.top());
        stk.pop();
    }

    while (!dq.empty()) {
        std::cout << dq.front();
        dq.pop_front();
    }
    return 0;
}