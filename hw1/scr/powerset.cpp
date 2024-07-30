#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void generate_powerset(const vector<T>& s, vector<vector<T>>& result, vector<T>& current, int index) {
    if (index == s.size()) {
        result.push_back(current);
        return;
    }
    generate_powerset(s, result, current, index + 1); 
    current.push_back(s[index]);                     
    generate_powerset(s, result, current, index + 1); 
    current.pop_back();                               
}

template <typename T>
vector<vector<T>> powerset(const vector<T>& s) {
    vector<vector<T>> result;
    vector<T> current;
    generate_powerset(s, result, current, 0);
    return result;
}

int main() {
    vector<string> s = { "a", "b", "c" };
    vector<vector<string>> result = powerset(s);

    cout << "Powerset:" << endl;
    for (const auto& subset : result) {
        cout << "{ ";
        for (const auto& element : subset) {
            cout << element << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
//參考chatgpt