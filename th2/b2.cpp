#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// Hàm kiểm tra và đánh giá biểu thức
bool evaluateExpression(const string& expression, const map<char, bool>& var_values) {
    string modified_expr = expression;
    
    // Thay thế các biến trong biểu thức bằng giá trị tương ứng (True/False)
    for (auto& entry : var_values) {
        char var = entry.first;
        bool value = entry.second;
        
        // Tìm tất cả các biến trong biểu thức và thay thế bằng giá trị T/F
        replace(modified_expr.begin(), modified_expr.end(), var, value ? 'T' : 'F');
    }

    // Đánh giá các toán tử logic (¬, ∧, ∨)
    while (modified_expr.find("¬") != string::npos) {
        size_t pos = modified_expr.find("¬");
        char var = modified_expr[pos + 1];
        modified_expr.replace(pos, 2, (var == 'T') ? "F" : "T");
    }
    
    // Xử lý toán tử ∧ (AND)
    while (modified_expr.find("∧") != string::npos) {
        size_t pos = modified_expr.find("∧");
        char left = modified_expr[pos - 1];
        char right = modified_expr[pos + 1];
        modified_expr.replace(pos, 1, ((left == 'T' && right == 'T') ? "T" : "F"));
    }

    // Xử lý toán tử ∨ (OR)
    while (modified_expr.find("∨") != string::npos) {
        size_t pos = modified_expr.find("∨");
        char left = modified_expr[pos - 1];
        char right = modified_expr[pos + 1];
        modified_expr.replace(pos, 1, ((left == 'T' || right == 'T') ? "T" : "F"));
    }
    
    return modified_expr == "T"; // Trả về true nếu kết quả cuối cùng là T, ngược lại false
}

// Hàm tạo bảng chân trị
void truthTable(const string& expression) {
    // Tìm ra các biến trong biểu thức
    vector<char> variables;
    for (char c : expression) {
        if (isalpha(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
        }
    }
    
    // In tiêu đề bảng
    for (char var : variables) {
        cout << var << "\t";
    }
    cout << "Ket qua" << endl;
    
    // Số tổ hợp giá trị của các biến
    int numCombinations = pow(2, variables.size());

    // Duyệt qua tất cả các tổ hợp giá trị true/false cho các biến
    for (int i = 0; i < numCombinations; ++i) {
        map<char, bool> var_values;

        // Gán giá trị true/false cho các biến
        for (int j = 0; j < variables.size(); ++j) {
            var_values[variables[j]] = (i & (1 << (variables.size() - j - 1))) != 0;
        }

        // In giá trị các biến
        for (char var : variables) {
            cout << (var_values[var] ? "T" : "F") << "\t";
        }

        // Đánh giá biểu thức cho tổ hợp giá trị hiện tại
        bool result = evaluateExpression(expression, var_values);
        cout << (result ? "T" : "F") << endl;
    }
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logiclogic: ";
    getline(cin, expression);

    truthTable(expression);

    return 0;
}