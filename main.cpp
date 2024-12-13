
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

class InfixToPostfixConverter {
private:
    string postfix;

    // Function to determine precedence of operators
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

public:
    // Function to convert infix to postfix
    void Convert(const string& infix) {
        stack<char> operators;
        postfix.clear();

        for (char ch : infix) {
            if (isalpha(ch)) {
                // Append operands to postfix
                postfix += ch;
            } else if (ch == '(') {
                // Push '(' onto stack
                operators.push(ch);
            } else if (ch == ')') {
                
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                if (!operators.empty()) {
                    operators.pop(); 
                }
            } else if (isspace(ch)) {
              
                continue;
            } else {
                // Handle operators
                while (!operators.empty() && precedence(ch) <= precedence(operators.top())) {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
            }
        }

        
        while (!operators.empty()) {
            postfix += operators.top();
            operators.pop();
        }
    }

    // Accessor function to retrieve the postfix expression
    string getPostfix() const {
        return postfix;
    }
};

int main() {
    InfixToPostfixConverter converter;
    ifstream inputFile("InfixData.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open input file!\n";
        return 1;
    }

    string infix;
    while (getline(inputFile, infix)) {
        converter.Convert(infix);
        cout << "Infix Expression: " << infix << "\n";
        cout << "Postfix Expression: " << converter.getPostfix() << "\n\n";
    }

    inputFile.close();
    return 0;
}