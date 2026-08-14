///FACILES

////205. Isomorphic Strings

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, int> charIndexS;
        unordered_map<char, int> charIndexT;

        for (int i = 0; i < s.length(); i++) {
            if (charIndexS.find(s[i]) == charIndexS.end()) {
                charIndexS[s[i]] = i;
            }

            if (charIndexT.find(t[i]) == charIndexT.end()) {
                charIndexT[t[i]] = i;
            }

            if (charIndexS[s[i]] != charIndexT[t[i]]) {
                return false;
            }
        }

        return true;        
    }
};

//217. Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            if (nums[i] == nums[i - 1])
                return true;
        }
        return false;
    }
};


//219. Contains Duplicate II


class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* temp = curr->next; // Store the next node
            curr->next = prev;            // Reverse the current node's pointer
            prev = curr;                  // Move prev to current node
            curr = temp;                  // Move to the next node
        }
        return prev; // New head of the reversed list
    }
};


//225. Implement Stack using Queues

class MyStack {
private:
    std::queue<int> q;

public:
    MyStack() {}

    void push(int x) {
        q.push(x);
        for (int i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int top = q.front();
        q.pop();
        return top;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};



////226. Invert Binary Tree
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        invertTree(root->left);
        invertTree(root->right);
        
        return root;        
    }
};


//228. Summary Ranges

#include <vector>
#include <string>
#include <iostream>

class Solution {
public:
    std::vector<std::string> summaryRanges(std::vector<int>& nums) {
        std::vector<std::string> result;
        if (nums.empty()) {
            return result;
        }

        for (int i = 0; i < nums.size();) {
            int start = nums[i];
            int j = i;
            // Expand the range as long as elements are consecutive
            while (j + 1 < nums.size() && nums[j + 1] == nums[j] + 1) {
                j++;
            }

            // Format the range string
            if (nums[j] == start) {
                result.push_back(std::to_string(start));
            } else {
                result.push_back(std::to_string(start) + "->" + std::to_string(nums[j]));
            }
            
            // Move to the next potential start of a range
            i = j + 1;
        }
        return result;
    }
};


//231. Power of Two
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && not (n & n - 1);
    }
};


///232. Implement Queue using Stacks
class MyQueue {
private:
    stack<int> input;
    stack<int> output;    

public:
    MyQueue() {}

    void push(int x) {
        input.push(x);
    }

    int pop() {
        peek();
        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        return output.top();
    }

    bool empty() {
        return input.empty() && output.empty();
    }
};

// 234. Palindrome Linked List
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head, *prev, *temp;
        while (fast && fast->next)
            slow = slow->next, fast = fast->next->next;
        prev = slow, slow = slow->next, prev->next = NULL;
        while (slow)
            temp = slow->next, slow->next = prev, prev = slow, slow = temp;
        fast = head, slow = prev;
        while (slow)
            if (fast->val != slow->val) return false;
            else fast = fast->next, slow = slow->next;
        return true;
    }
};


// 242. Valid Anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        unordered_map<char, int> counter;

        for (char ch : s) {
            counter[ch] = counter[ch] + 1;
        }

        for (char ch : t) {
            if (counter.find(ch) == counter.end() || counter[ch] == 0) {
                return false;
            }
            counter[ch] = counter[ch] - 1;
        }

        return true;        
    }
};



// 257. Binary Tree Paths
class Solution {
public:
    void findPath(TreeNode* node, vector<string>& ans, string temp) {
        temp += to_string(node->val);  // Add the current node value to the path
        if (node->left) findPath(node->left, ans, temp + "->");  // Traverse left
        if (node->right) findPath(node->right, ans, temp + "->"); // Traverse right
        if (!node->left && !node->right) ans.push_back(temp);  // Add path if leaf node
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        if (root) findPath(root, ans, "");  // Start traversal from the root
        return ans;
    }
};

// 258. Add Digits
class Solution {
public:
    int addDigits(int num) {
        if (num == 0)
            return 0;
        if (num % 9 == 0)
            return 9;
        return num % 9;
    }
};




//263. Ugly Number
bool isUgly(int n) {
    if (n <= 0) {
        return false;
    }
    int factors[] = {2, 3, 5};
    for (int i=0;i<3;i++) {
        while (n % factors[i] == 0) {
            n /= factors[i];
        }
    }
    return n == 1;
}

// 268. Missing Number

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        vector<int>v(n+1,-1);
        for(int i =0;i<nums.size();i++){
            v[nums[i]] = nums[i];
        }
        for(int i =0;i<v.size();i++){
            if(v[i]==-1)return i;
        }
        return 0;
    }
};




// 278. First Bad Version
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left=1,mid;
        while(left<=n){
            mid=left+(n-left)/2;
            if(isBadVersion(mid)){
                n=mid-1;
            }
            else{
                left=mid+1;
            }
        }
        return left;
    }
};


//171. Excel Sheet Column Number
class Solution {
public:
    int titleToNumber(string columnTitle) {
        long long ans = 0;

        // Positional system in base-26 with digits A..Z mapped to 1..26.
        for (char ch : columnTitle) {
            ans = ans * 26 + (ch - 'A' + 1);
        }

        return (int)ans;
    }
};



//202. Happy Number

class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> visit;
        
        while (visit.find(n) == visit.end()) {
            visit.insert(n);
            n = getNextNumber(n);
            if (n == 1) {
                return true;
            }
        }
        
        return false;
    }

private:
    int getNextNumber(int n) {
        int output = 0;
        
        while (n > 0) {
            int digit = n % 10;
            output += digit * digit;
            n = n / 10;
        }
        
        return output;
    }
};

//203. Remove Linked List Elements

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* ans = new ListNode(0, head);
        ListNode* dummy = ans;

        while (dummy != nullptr) {
            while (dummy->next != nullptr && dummy->next->val == val) {
                dummy->next = dummy->next->next;
            }
            dummy = dummy->next;
        }
        
        ListNode* result = ans->next;
        delete ans;

        return result;        
    }
};




///67. Add Binary
class Solution {
 public:
  string addBinary(string a, string b) {
    string ans;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
      if (i >= 0)
        carry += a[i--] - '0';
      if (j >= 0)
        carry += b[j--] - '0';
      ans += carry % 2 + '0';
      carry /= 2;
    }

    reverse(begin(ans), end(ans));
    return ans;
  }
};

/// 69 Sqrt(x)
class Solution {
public:
    int mySqrt(int x) {
        // For special cases when x is 0 or 1, return x.
        if (x == 0 || x == 1)
            return x;
        
        // Initialize the search range for the square root.
        int start = 1;
        int end = x;
        int mid = -1;
        
        // Perform binary search to find the square root of x.
        while (start <= end) {
            // Calculate the middle point using "start + (end - start) / 2" to avoid integer overflow.
            mid = start + (end - start) / 2;
            
            // Convert mid to long to handle large values without overflow.
            long long square = static_cast<long long>(mid) * mid;
            
            // If the square of the middle value is greater than x, move the "end" to the left (mid - 1).
            if (square > x)
                end = mid - 1;
            else if (square == x)
                // If the square of the middle value is equal to x, we found the square root.
                return mid;
            else
                // If the square of the middle value is less than x, move the "start" to the right (mid + 1).
                start = mid + 1;
        }
        
        // The loop ends when "start" becomes greater than "end", and "end" is the integer value of the square root.
        // However, since we might have been using integer division in the calculations,
        // we round down the value of "end" to the nearest integer to get the correct square root.
        return static_cast<int>(std::round(end));
    }
};


///70. Climbing Stairs
class Solution {
public:
    int climbStairs(int n, unordered_map<int, int>& memo) {
        if (n == 0 || n == 1) {
            return 1;
        }
        if (memo.find(n) == memo.end()) {
            memo[n] = climbStairs(n-1, memo) + climbStairs(n-2, memo);
        }
        return memo[n];
    }

    int climbStairs(int n) {
        unordered_map<int, int> memo;
        return climbStairs(n, memo);
    }
};


///88. Merge Sorted Array
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
    }
};
//94. Binary Tree Inorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stack;
        TreeNode* curr = root;
        while (curr != NULL || !stack.empty()) {
            while (curr != NULL) {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.top();
            stack.pop();
            res.push_back(curr->val);
            curr = curr->right;
        }
        return res;
    }
};


//100. Same Tree
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // If both nodes are NULL, they are identical
        if (p == NULL && q == NULL) {
            return true;
        }
        // If only one of the nodes is NULL, they are not identical
        if (p == NULL || q == NULL) {
            return false;
        }
        // Check if values are equal and recursively check left and right subtrees
        if (p->val == q->val) {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        // Values are not equal, they are not identical
        return false;
    }
};



///1071. Greatest Common Divisor of Strings
class Solution {
public:
    bool valid(string str1, string str2, int k) {
        int len1 = str1.size(), len2 = str2.size();
        if (len1 % k > 0 || len2 % k > 0) {
            return false;
        } else {
            string base = str1.substr(0, k);
            int n1 = len1 / k, n2 = len2 / k;
            return str1 == joinWords(base, n1) && str2 == joinWords(base, n2);
        }
    }
    string joinWords(string str, int k) {
        string ans = "";
        for (int i = 0; i < k; ++i) {
            ans += str;
        }
        return ans;
    }
    
    
    string gcdOfStrings(string str1, string str2) {
        int len1 = str1.length(), len2 = str2.length();
        for (int i = min(len1, len2); i >= 1; --i) {
            if (valid(str1, str2, i)) {
                return str1.substr(0, i);
            }
        }
        return "";
    }
};


////1768. Merge Strings Alternately

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        string result = "";

        for (int i = 0; i < max(m, n); i++) {
            if (i < m) {
                result.push_back(word1[i]);
            }
            if (i < n) {
                result.push_back(word2[i]);
            }
        }

        return result;
    }
};


//283. Move Zeroes
class Solution {
public:
  void moveZeroes(vector<int>& nums) {
      int n = nums.size();

      // Count the zeroes
      int numZeroes = 0;
      for (int i = 0; i < n; i++) {
          numZeroes += (nums[i] == 0);
      }

      // Make all the non-zero elements retain their original order.
      vector<int> ans;
      for (int i = 0; i < n; i++) {
          if (nums[i] != 0) {
              ans.push_back(nums[i]);
          }
      }

      // Move all zeroes to the end
      while (numZeroes--) {
          ans.push_back(0);
      }

      // Combine the result
      for (int i = 0; i < n; i++) {
          nums[i] = ans[i];
      }
  }
};


//392. Is Subsequence

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sp = 0;
        int tp = 0;

        while (sp < s.length() && tp < t.length()) {
            if (s[sp] == t[tp]) {
                sp++;
            }
            tp++;
        }

        return sp == s.length();        
    }
};


//11. Container With Most Water

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int left = 0;
        int right = height.size() - 1;

        while (left < right) {
            maxArea = max(maxArea, (right - left) * min(height[left], height[right]));

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxArea;        
    }
};


// 1679. Max Number of K-Sum Pairs
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size() - 1;
        int count = 0;

        while (i < j) {
            int sum = nums[i] + nums[j];
            if (sum == k) {
                count++;
                i++;
                j--;
            } else if (sum > k) {
                j--;
            } else {
                i++;
            }
        }

        return count;
    }
};