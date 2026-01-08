#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> out(n,-1);
    stack<int> st;

    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top() <= nums[i]){
            st.pop();
        }

        if(!st.empty()){
            out[i] = st.top();
        }
        st.push(nums[i]);
    }
    return out;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = nextGreaterElements(arr);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}
