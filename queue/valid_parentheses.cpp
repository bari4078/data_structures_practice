#include <bits/stdc++.h>
using namespace std;

bool is_valid(string s){
    stack<char> st;
    for(char c:s){
        if(c == '[' || c == '{' || c == '('){
            st.push(c);
        }
        else{
            if(st.empty()){
                return false;
            }
            char top = st.top();

            if(c == ')' && top == '(' ||
                c == '}' && top == '{' ||
                c == ']' && top == '[')
                st.pop();
            else{
                return false;
            }
        }
    }
    return st.empty();  
}

int main(){
    string s = "{[(]})";
    cout << (is_valid(s) ? "Valid" : "Invalid") << endl;
}