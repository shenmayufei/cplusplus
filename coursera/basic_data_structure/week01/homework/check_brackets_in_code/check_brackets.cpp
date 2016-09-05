#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

std::string checkBrackets(const std::string text) {
    std::stack <Bracket> opening_brackets_stack;
    int failedPos = -1;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
            continue;
        }

        if (next == ')' || next == ']' || next == '}') {
            // check empty stack
            if (opening_brackets_stack.empty()){
                failedPos = position+1;
                break;
            }
            // get the top element
            Bracket b = opening_brackets_stack.top();
            if (b.type == next) {
                opening_brackets_stack.pop();
            } else {
                // top element does not match 
                failedPos = position + 1;
                break;
            }
        }
    }

    // if failedPos >= 0, there must be a consistency
    if (failedPos >= 0) return std::to_string(failedPos);
    // stack is empty, all brackets self matches; otherwise all "{[(" 
    if (opening_brackets_stack.empty()) return "Success";
    
    Bracket b = opening_brackets_stack.top();
    return std::to_string(b.position+1);
}

int main() {
    std::string text;
    getline(std::cin, text);
    std::string res = checkBrackets(text);
    std::cout << res << std::endl;
    return 0;
}
