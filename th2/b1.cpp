#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>

using namespace std;

// Hàm kiểm tra tính hợp lệ của biểu thức
bool isValidExpression(const string &expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

// Hàm tính giá trị của biểu thức logic
bool evaluateExpression(const string &expr, const unordered_map<char, bool> &values) {
    stack<bool> operands;
    stack<char> operators;

    auto applyOperator = [](bool a, bool b, char op) -> bool {
        if (op == '&') return a && b;
        if (op == '|') return a || b;
        if (op == '-') return !a; // Đảo ngược (NOT)
        return false;
    };

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        
        if (isspace(c)) continue; // Bỏ qua khoảng trắng

        if (isalpha(c)) {
            operands.push(values.at(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool b = operands.top(); operands.pop();
                bool a = operands.top(); operands.pop();
                operands.push(applyOperator(a, b, op));
            }
            operators.pop(); // Bỏ dấu '(' khỏi stack
        } else if (c == '&' || c == '|') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool b = operands.top(); operands.pop();
                bool a = operands.top(); operands.pop();
                operands.push(applyOperator(a, b, op));
            }
            operators.push(c);
        } else if (c == '-') { // Toán tử NOT
            bool a = operands.top(); operands.pop();
            operands.push(!a);
        }
    }

    while (!operators.empty()) {
        char op = operators.top(); operators.pop();
        bool b = operands.top(); operands.pop();
        bool a = operands.top(); operands.pop();
        operands.push(applyOperator(a, b, op));
    }

    return operands.top();
}

int main() {
    string expression;
    unordered_map<char, bool> values;

    cout << "Nhap bieu thuc logic : ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Bieu thuc khong hop le!" << endl;
        return 1;
    }

    int n;
    cout << "Nhap so luong bien logic: ";
    cin >> n;

    cout << "Nhap gia tri cho cac bien logic:\n";
    for (int i = 0; i < n; ++i) {
        char var;
        int val;
        cin >> var >> val;
        values[var] = (val == 1);
    }

    try {
bool result = evaluateExpression(expression, values);
        cout << "Ket qua bieu thuc: " << (result ? "True" : "False") << endl;
    } catch (const out_of_range &e) {
        cout << "Loi." << endl;
    }

    return 0;
}