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


// 283. Move Zeroes
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] != 0) {
                swap(nums[right], nums[left]);
                left++;
            }
        }        
    }
};


// 290. Word Pattern
class Solution {
public:
    bool wordPattern(std::string pattern, std::string s) {
        std::istringstream iss(s);
        std::vector<std::string> words;
        std::string word;
        
        while (iss >> word) {
            words.push_back(word);}
        
        if (pattern.size() != words.size()) {
            return false;}

        std::unordered_map<char, std::string> charToWord;
        std::unordered_set<std::string> seenWords;

        for (int i = 0; i < pattern.size(); ++i) {
            char c = pattern[i];
            const std::string& w = words[i];

            if (charToWord.count(c)) {
                if (charToWord[c] != w) {
                    return false;}
            } else {
                if (seenWords.count(w)) {
                    return false;}
                charToWord[c] = w;
                seenWords.insert(w); }
        }
        return true;}
};


// 292. Nim Game
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};

// 303. Range Sum Query - Immutable
class NumArray { // 12 ms, faster than 99.87%
public:
    vector<int>& preSum; // `preSum` will reference to `nums` array, no copy at all!
    
    NumArray(vector<int>& nums) : preSum(nums) {
        for (int i = 1; i < preSum.size(); ++i)
            preSum[i] += preSum[i-1]; 
    }
    
    int sumRange(int left, int right) {
        if (left == 0) return preSum[right];
        return preSum[right] - preSum[left-1];
    }
};

// 326. Power of Three


// C++
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};

// 338. Counting Bits

class Solution {
public:
    vector<int> countBits(int n) {
       std::vector<int> dp(n + 1, 0);
        int sub = 1;

        for (int i = 1; i <= n; i++) {
            if (sub * 2 == i) {
                sub = i;
            }

            dp[i] = dp[i - sub] + 1;
        }

        return dp;        
    }
};

// 344. Reverse String
class Solution {
public:
    void reverseString(vector<char>& s) {

        int start = 0;
        int end = s.size() - 1;

        while(start <= end){

            swap(s[start], s[end]);

            start++;
            end--;
        }
    }
};

// 345. Reverse Vowels of a String
class Solution {
public:
    string reverseVowels(string s) {
        // Convert the input string to a character array.
        string word = s;
        int start = 0;
        int end = s.length() - 1;
        string vowels = "aeiouAEIOU";
        
        // Loop until the start pointer is no longer less than the end pointer.
        while (start < end) {
            // Move the start pointer towards the end until it points to a vowel.
            while (start < end && vowels.find(word[start]) == string::npos) {
                start++;
            }
            
            // Move the end pointer towards the start until it points to a vowel.
            while (start < end && vowels.find(word[end]) == string::npos) {
                end--;
            }
            
            // Swap the vowels found at the start and end positions.
            swap(word[start], word[end]);
            
            // Move the pointers towards each other for the next iteration.
            start++;
            end--;
        }
        
        // Return the modified string.
        return word;
    }
};


// 374. Guess Number Higher or Lower
class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int result = guess(mid);

            if (result == 0) return mid;
            else if (result == 1) left = mid + 1;
            else right = mid - 1;
        }

        return -1;
    }
};

// 383. Ransom Note
class Solution {
    public boolean canConstruct(String ransomNote, String magazine) {
        HashMap<Character, Integer> magaHash = new HashMap<>();

        for (char c : magazine.toCharArray()) {
            magaHash.put(c, magaHash.getOrDefault(c, 0) + 1);
        }

        for (char c : ransomNote.toCharArray()) {
            if (!magaHash.containsKey(c) || magaHash.get(c) <= 0) {
                return false;
            }
            magaHash.put(c, magaHash.get(c) - 1);
        }

        return true;
    }
}

// 389. Find the Difference
class Solution {
public:
    char findTheDifference(string s, string t) {
        std::unordered_map<char, int> count;
        
        for (char c : t) {
            count[c]++;
        }
        
        for (char c : s) {
            count[c]--;
            if (count[c] == 0) {
                count.erase(c);
            }
        }
        
        return count.begin()->first;        
    }
};


// 387. First Unique Character in a String
class Solution {
public:
    int firstUniqChar(string s) {
        int freq[26]={0};
        for(auto i:s) freq[i-'a']++;
        for(int i=0;i<s.length();i++){
            if(freq[s[i]-'a']==1) return i;
        }
        return -1;
    }
};


// 392. Is Subsequence
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


// 401. Binary Watch
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> ans;
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                    ans.push_back(to_string(h) + ":" + (m < 10 ? "0" : "") +
                                  to_string(m));
                }
            }
        }
        return ans;
    }
};


// 404. Sum of Left Leaves
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) return 0;

        int ans = 0;

        if (root->left != nullptr) {
            if (root->left->left == nullptr &&
                root->left->right == nullptr) {

                ans += root->left->val;
            } 
            else {
                ans += sumOfLeftLeaves(root->left);
            }
        }

        ans += sumOfLeftLeaves(root->right);

        return ans;
    }
};


//405. Convert a Number to Hexadecimal
class Solution {
public:
    string toHex(int num) {
        unsigned int ourNum = num;
        // Implicitly cast negative numbers.
        // -1 turns to the maximum number representable
        // as an unsigned int.
        
        string str; // Our result
        char ourArray[17] = "0123456789abcdef"; // We will pick from this set of characters

        // While our number exists, convert it into base 16.
        // We are going from left to right, so we need to reverse our result
        // when we return it.
        do {
            str += ourArray[ourNum % 16];
            ourNum /= 16;
        } while (ourNum); 

        return {str.rbegin(), str.rend()};
    }
}; 


class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 0 || num == 1) return true;

        int L = 1;
        int R = num;

        while (L <= R) {
            long long M = L + (R - L) / 2;
            long long sqr = M * M;

            if (sqr == num) return true;
            else if (sqr > num) R = M - 1;
            else L = M + 1;
        }
        return false;
    }
};

// 409. Longest Palindrome
class Solution {
public:
    int longestPalindrome(string s) {
        // Map to store frequency of occurrence of each character
        unordered_map<char, int> frequencyMap;
        // Count frequencies
        for (char c : s) {
            frequencyMap[c]++;
        }

        int res = 0;
        bool hasOddFrequency = false;
        for (auto& entry : frequencyMap) {
            int freq = entry.second;
            // Check if the frequency is even
            if (freq % 2 == 0) {
                res += freq;
            } else {
                // If the frequency is odd, one occurrence of the
                // character will remain without a match
                res += freq - 1;
                hasOddFrequency = true;
            }
        }
        // If hasOddFrequency is true, we have at least one unmatched
        // character to make the center of an odd length palindrome.
        if (hasOddFrequency) return res + 1;

        return res;
    }
};

// 412. Fizz Buzz

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans;

        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 == 0) {
                ans.push_back("FizzBuzz");
            } else if (i % 3 == 0) {
                ans.push_back("Fizz");
            } else if (i % 5 == 0) {
                ans.push_back("Buzz");
            } else {
                ans.push_back(to_string(i));
            }
        }

        return ans;
    }
};

// 414. Third Maximum Number
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        // Sort the array in non-increasing order.
        sort(nums.begin(), nums.end(), greater<int>());
        
        int elemCounted = 1;
        int prevElem = nums[0];
        
        for (int index = 1; index < nums.size(); ++index) {
            // Current element is different from previous.
            if (nums[index] != prevElem) {
                elemCounted += 1;
                prevElem = nums[index];
            }
            
            // If we have counted 3 numbers then return current number.
            if (elemCounted == 3) {
                return nums[index];
            }
        }
        
        // We never counted 3 distinct numbers, return largest number.
        return nums[0];
    }
};



// 415. Add Strings
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        string result = "";

        while (i >= 0 || j >= 0 || carry != 0) {
            int d1 = (i >= 0) ? num1[i] - '0' : 0;
            int d2 = (j >= 0) ? num2[j] - '0' : 0;
            int sum = d1 + d2 + carry;
            carry = sum / 10;
            result += to_string(sum % 10);
            i--;
            j--;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};


// 434. Number of Segments in a String
class Solution {
public:
    int countSegments(string s) {
        int count=0;
        for(int i=0;i<s.length();i++){
            if(s[i]!=' '&&(i==0||s[i-1]==' ')){
                count++;
            }
        }
        return count;
    }
};



// 441. Arranging Coins

class Solution {
public:
    int arrangeCoins(int n) {
        long left = 1, right = n;
        while(left <= right){
            long mid = left + (right - left) / 2;
            long coins_needed = mid * (mid + 1) / 2;
            if(coins_needed == n) return mid;
            else if(coins_needed < n) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
};


// 448. Find All Numbers Disappeared in an Array
class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g.sort()
        s.sort()
        content_children = 0
        cookie_index = 0
        while cookie_index < len(s) and content_children < len(g):
            if s[cookie_index] >= g[content_children]:
                content_children += 1
            cookie_index += 1
        return content_children

// 455. Assign Cookies
class Solution {
public:
    int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        int contentChildren = 0;
        int cookieIndex = 0;
        while (cookieIndex < s.size() && contentChildren < g.size()) {
            if (s[cookieIndex] >= g[contentChildren]) {
                contentChildren++;
            }
            cookieIndex++;
        }
        return contentChildren;
    }
};


// 459. Repeated Substring Pattern
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.length();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string repeated = "";
                for (int j = 0; j < n / i; j++) {
                    repeated += s.substr(0, i);
                }
                if (repeated == s) {
                    return true;
                }
            }
        }
        return false;
    }
};


// 461. Hamming Distance
class Solution {
public:
    int hammingDistance(int x, int y) {
        int n = x ^ y;
        int count = 0;

        while (n) {
            n &= (n - 1);
            count++;
        }

        return count;
    }
};


// 463. Island Perimeter
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    perimeter += 4;
                    if (r > 0 && grid[r-1][c] == 1) {
                        perimeter -= 2;
                    }
                    if (c > 0 && grid[r][c-1] == 1) {
                        perimeter -= 2;
                    }
                }
            }
        }
        
        return perimeter;
    }
};



// 476. Number Complement
class Solution {
public:
    int findComplement(int num) {
        if (num == 0) return 1;
        
        unsigned int mask = ~0;
        
        while (num & mask) {
            mask <<= 1;
        }
        
        return ~mask & ~num;
    }
};


// 482. License Key Formatting
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        int count = 0;
        int n = s.length();
        string ans = "";
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] != '-') {
                ans.push_back(toupper(s[i]));
                count++;
                if (count == k) {
                    ans.push_back('-');
                    count = 0;
                }
            }
        }
        // Make sure that the last character is not a dash
        if (ans.size() > 0 && ans.back() == '-') {
           ans.pop_back();
        }
        // Reversing the string
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


// 485. Max Consecutive Ones
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0;
        int count = 0;


        for (int n : nums) {
            if (n == 0) {
                count = 0;
            } else {
                count++;
            }

            if (res < count) {
                res = count;
            }
        }

        return res;        
    }
};

// 492. Construct the Rectangle
class Solution {
public:
        vector<int> constructRectangle(int area) {
    for (int W = sqrt(area); W >= 1; W--) {
        if (area % W == 0) {
            return {area / W, W};
        }
    }
    return {};
    }
};



// 495. Teemo Attacking
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int ans=0;
        for(int i=0;i<timeSeries.size();++i){
            if(i!=timeSeries.size()-1){
                if(timeSeries[i+1]-timeSeries[i]>=duration){
                    ans+=duration;
                }
                else{
                    ans+=timeSeries[i+1]-timeSeries[i];
                }
            }
            else{
                ans+=duration;
            }
        }
        return ans;
    }
};


// 496. Next Greater Element I
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> next;
        stack<int> s;

        for (int i = nums2.size() - 1; i >= 0; --i) {
            while (!s.empty() && s.top() <= nums2[i]) {
                s.pop();
            }
            next[nums2[i]] = s.empty() ? -1 : s.top();
            s.push(nums2[i]);
        }

        vector<int> res;
        for (int num : nums1) {
            res.push_back(next[num]);
        }
        return res;
    }
};



//500. Keyboard Row
 class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        std::string s1="qwertyuiop";
        std::string s2="asdfghjkl";
        std::string s3="zxcvbnm";
        std::vector<std::string> ans;
        for(int i=0;i<words.size();++i){
            bool same=1;int prev=0;
            for(int j=0;j<words[i].size();++j){
                if(s1.contains(std::tolower(words[i][j]))){
                    if(prev!=0&&prev!=1){
                        same=false;
                        break;
                    }
                    prev=1;
                }
                else if(s2.contains(std::tolower(words[i][j]))){
                    if(prev!=0&&prev!=2){
                        same=false;
                        break;
                    }
                    prev=2;
                }
                else{
                    if(prev!=0&&prev!=3){
                        same=false;
                        break;
                    }
                    prev=3;
                }
            }
            if(same){
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
};


// 501. Find Mode in Binary Search Tree
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> counter;
        dfs(root, counter);
        int maxFreq = 0;

        for (auto& [key, val] : counter) {
            maxFreq = max(maxFreq, val);
        }
        
        vector<int> ans;
        for (auto& [key, val] : counter) {
            if (val == maxFreq) {
                ans.push_back(key);
            } 
        }
        
        return ans;
    }
    
    void dfs(TreeNode* node, unordered_map<int, int>& counter) {
        if (node == nullptr) {
            return;
        }

        counter[node->val]++;
        dfs(node->left, counter);
        dfs(node->right, counter);
    }
};

// 504. Base 7
class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";

        bool sign = num < 0 ? true : false;
        num = abs(num);
        string ans = "";

        while(num){
            ans += (num % 7 + '0');
            num /= 7;
        }
        reverse(ans.begin(), ans.end());
        
        return sign ? "-"+ans : ans;
    }
};


// 506. Relative Ranks
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int N = score.size();
        vector<int> scoreCopy(N);
        copy(score.begin(), score.end(), scoreCopy.begin());
        
        // Save the index of each athlete
        unordered_map<int, int> scoreToIndex;
        for (int i = 0; i < N; i++) {
            scoreToIndex[scoreCopy[i]] = i;
        }
        
        // Sort scoreCopy in descending order
        sort(scoreCopy.begin(), scoreCopy.end(), greater<int>());

        // Assign ranks to athletes
        vector<string> rank(N);
        for (int i = 0; i < N; i++) {
            if (i == 0) {
                rank[scoreToIndex[scoreCopy[i]]] = "Gold Medal";
            } else if (i == 1) {
                rank[scoreToIndex[scoreCopy[i]]] = "Silver Medal";
            } else if (i == 2) {
                rank[scoreToIndex[scoreCopy[i]]] = "Bronze Medal";
            } else {
                rank[scoreToIndex[scoreCopy[i]]] = to_string(i + 1);
            }
        }
        
        return rank;
    }
};



// 507. Perfect Number
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num <= 1) {
            return false;
        }

        int sum{1};

        for (int i{2}; i * i <= num; ++i) {
            if (num % i == 0) {
                sum += i;
                if (i * i != num) {
                    sum += (num / i);
                }
            }
        }

        return sum == num;
    }
};


// 509. Fibonacci Number


class Solution {
public:
    int fib(int n) {
        int fib_nums[] = {
            0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
            6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040,
            1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986,
            102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903
        };

        return fib_nums[n];
    }
};

// 520. Detect Capital
bool detectCapitalUse(string word) {
    for(int i = 1; i < word.size(); i++){
        if(isupper(word[1]) != isupper(word[i]) || 
           islower(word[0]) && isupper(word[i])) return false;
    }        
    return true;
}


// 521. Longest Uncommon Subsequence I

class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a == b) {
            return -1;
        } else {
            return max(a.length(), b.length());
        }    
    }
};


// 530. Minimum Absolute Difference in BST
class Solution {
public:
    int diff = INT_MAX;
    TreeNode *prev = NULL;
    void dfs(TreeNode *root) {
        // moving to the left as much as we can
        if (root->left) dfs(root->left);
        // if we find at least a node before, we update diff
        if (prev) diff = min(diff, abs(prev->val - root->val));
        prev = root;
        // moving to the right as much as we can
        if (root->right) dfs(root->right);
    }
    int getMinimumDifference(TreeNode *root) {
        dfs(root);
        return diff;
    }
};


//541. Reverse String II
class Solution {
public:
    string reverseStr(string s, int k) {

        int step = 2 * k;

        for(int i = 0; i < s.length(); i += step){

            int start = i;
            int end = min(i + k - 1, (int)s.length() - 1);

            while(start < end){
                swap(s[start], s[end]);
                start++;
                end--;
            }
        }

        return s;
    }
};


//543. Diameter of Binary Tree
 class Solution {
    int res = 0;

public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return res;        
    }

private:
    int dfs(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int l = dfs(root->left);
        int r = dfs(root->right);

        res = std::max(res, l + r);

        return 1 + std::max(l, r);
    }    
};



//551. Student Attendance Record I
bool checkRecord(string s) {
    int a=0, l=0;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='A') a++;
        if(s[i]=='L') l++;
        else l=0;
        if(a>=2||l>2) return false;
    }
    return true;
}



//557. Reverse Words in a String III
class Solution {
public:
    string reverseWords(string s) {
        string result;
        int lastSpaceIndex = -1;
        for (int strIndex = 0; strIndex < s.length(); strIndex++) {
            if ((strIndex == s.length() - 1) || s[strIndex] == ' ') {
                int reverseStrIndex =
                    (strIndex == s.length() - 1) ? strIndex : strIndex - 1;
                for (; reverseStrIndex > lastSpaceIndex; reverseStrIndex--) {
                    result += s[reverseStrIndex];
                }
                if (strIndex != s.length() - 1) {
                    result += ' ';
                }
                lastSpaceIndex = strIndex;
            }
        }
        return result;
    }
}; 


// 559. Maximum Depth of N-ary Tree
class Solution {
public:
    int maxDepth(Node* root) {
        if(root == nullptr) return 0;

        int maxHeight = 0;
        for(Node* child : root->children){
            maxHeight = max(maxHeight, maxDepth(child));
        }

        return 1 + maxHeight;
    }
};


// 561. Array Partition

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
        }
        return sum;
    }
};



//563. Binary Tree Tilt
class Solution {
public:

    int solve(TreeNode* root, int& ans) {
        if (root == nullptr) {
            return 0;
        }

        int left = solve(root->left, ans);
        int right = solve(root->right, ans);

        // Tilt of current node
        ans += abs(left - right);

        // Return sum of current subtree
        return root->val + left + right;
    }

    int findTilt(TreeNode* root) {
        int ans = 0;

        solve(root, ans);

        return ans;
    }
}; 


//566. Reshape the Matrix

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int m = mat.size();
        int n = mat[0].size();
        if (m * n != r * c) return mat;

        vector<vector<int>> reshaped(r, vector<int>(c));
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                reshaped[count / c][count % c] = mat[i][j];
                count++;
            }
        }

        return reshaped;
    }
};

// 572. Subtree of Another Tree
class Solution {
    bool isSame(TreeNode* root,TreeNode* subRoot){
        if(subRoot!=nullptr&&root!=nullptr){
            if(root->val==subRoot->val){
                return isSame(root->left,subRoot->left)&&isSame(root->right,subRoot->right);
            }
            return false;
        }
        if(subRoot==root){
            return true;
        }
        else{return false;}
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root!=nullptr){
            if(root->val==subRoot->val){
                if(isSame(root,subRoot)){
                    return true;
                }
            }
            return isSubtree(root->left,subRoot)||isSubtree(root->right,subRoot);
        }
        return false;
    }
};



// 575. Distribute Candies
class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        int x = candyType.size() / 2, count = 0;
        sort(candyType.begin(),candyType.end());
        for(int i = 0; i < candyType.size()-1; i++){
            if(candyType[i] != candyType[i+1]) count++;
        }
        count++;
        if(x < count) return x;
        return count;
    }
};



// 589. N-ary Tree Preorder Traversal

class Solution {
public:
    // To store the output result...
    vector<int> output;
    void traverse(Node* root) {
        // Base case: if the tree is empty...
        if(root == NULL) return;
        // Push the value of the root node to the output...
        output.push_back(root->val);
        // Recursively traverse each node in the children array...
        for(auto node:root->children)
            traverse(node);
    }
    vector<int> preorder(Node* root) {
        output.clear();
        traverse(root);
        return output;
    }
};




// 590. N-ary Tree Postorder Traversal
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        traversePostorder(root, result);
        return result;
    }

private:
    void traversePostorder(Node* currentNode, vector<int>& postorderList) {
        if (currentNode == nullptr) {
            return;
        }

        // First, visit all children
        for (Node* childNode : currentNode->children) {
            traversePostorder(childNode, postorderList);
        }

        // Then, add the current node's value
        postorderList.push_back(currentNode->val);
    }
};


// 594. Longest Harmonious Subsequence
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) freq[num]++;
        
        int ans = 0;
        for (auto& [key, val] : freq) {
            if (freq.count(key + 1)) {
                ans = max(ans, val + freq[key + 1]);
            }
        }
        return ans;
    }
};


// 599. Minimum Index Sum of Two Lists
 

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1,
                                  vector<string>& list2) {
        map<string, int> mp;
        mp[list1[0]] = INT_MIN;
        for (int i = 1; i < list1.size(); i++) {
            mp[list1[i]] = -i;
        }
        if (!mp.contains(list2[0]))
            mp[list2[0]] = INT_MIN;

        else {
            if (mp[list2[0]] != INT_MIN)
                mp[list2[0]] = abs(mp[list2[0]]);
            else
                mp[list2[0]] = 0;
        }

        for (int i = 1; i < list2.size(); i++) {
            if (mp.contains(list2[i])) {
                if (mp[list2[i]] != INT_MIN)
                    mp[list2[i]] = abs(mp[list2[i]]) + i;
                else
                    mp[list2[i]] = i;
            } else
                mp[list2[i]] = -i;
        }
        int minVal = INT_MAX;
        vector<string> ans;
        for (auto& it : mp) {
            if (it.second >= 0 && it.second < minVal) {
                minVal = it.second;
            }
        }
        for (auto& it : mp) {
            if (it.second >= 0 && it.second <= minVal) {
                ans.push_back(it.first);
            }
        }
        return ans;
    }
};


//598. Range Addition II
 class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int min_row = m;
        int min_col = n;
        for (int i=0; i<ops.size(); i++){
            if (ops[i][0]<min_row) min_row=ops[i][0];
            if (ops[i][1]<min_col) min_col=ops[i][1];
        }        
        return min_row*min_col;
        
    }
};


// 605. Can Place Flowers

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        for (int i = 0; i < flowerbed.size(); i++) {
            // Check if the current plot is empty.
            if (flowerbed[i] == 0) {
                // Check if the left and right plots are empty.
                bool emptyLeftPlot = (i == 0) || (flowerbed[i - 1] == 0);
                bool emptyRightPlot = (i == flowerbed.size() - 1) || (flowerbed[i + 1] == 0);
                
                // If both plots are empty, we can plant a flower here.
                if (emptyLeftPlot && emptyRightPlot) {
                    flowerbed[i] = 1;
                    count++;
                }
            }
        }
        return count >= n;
    }
};

//617. Merge Two Binary Trees
 
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if ( t1 && t2 ) {
            TreeNode * root = new TreeNode(t1->val + t2->val);
            root->left = mergeTrees(t1->left, t2->left);
            root->right = mergeTrees(t1->right, t2->right);
            return root;
        } else {
            return t1 ? t1 : t2;
        }
    }
};

 
// 628. Maximum Product of Three Numbers
class Solution {
public:
    int maximumProduct(vector<int>& A) {
        ranges::sort(A);
        return max(
            A.back() * A[A.size() - 2] * A[A.size() - 3],
            A.back() * A.front() * A[1]
        );
    }
};



// 637. Average of Levels in Binary Tree
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            double sum = 0;

            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front(); q.pop();
                sum += node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            res.push_back(sum / size);
        }

        return res;
    }
};

// 643. Maximum Average Subarray I
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        for (int i = 0; i < k; i++) sum += nums[i];
        int maxSum = sum;
        
        for (int i = k; i < nums.size(); i++) {
            sum = sum - nums[i - k] + nums[i];
            maxSum = max(maxSum, sum);
        }
        
        return (double) maxSum / k;
    }
};


//645. Set Mismatch


class Solution {
public:
    std::vector<int> findErrorNums(std::vector<int>& nums) {
        int dup = -1, missing = -1;
        
        for (int i = 1; i <= nums.size(); i++) {
            int count = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] == i) {
                    count++;
                }
            }
            if (count == 2) {
                dup = i;
            } else if (count == 0) {
                missing = i;
            }
        }
        
        return {dup, missing};
    }
};


// 653. Two Sum IV - Input is a BST
class Solution {
    unordered_set<int> set;

public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        if (set.count(k - root->val)) return true;
        set.insert(root->val);
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
};



//657. Robot Return to Origin
 class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0, y = 0;
        for (char m : moves) {
            if (m == 'R') x++;
            else if (m == 'L') x--;
            else if (m == 'U') y++;
            else if (m == 'D') y--;
        }
        return x == 0 && y == 0;
    }
};




// 661. Image Smoother
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        // Save the dimensions of the image.
        int m = img.size();
        int n = img[0].size();

        // Create a new image of the same dimension as the input image.
        vector<vector<int>> smoothImg(m, vector<int>(n));

        // Iterate over the cells of the image.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Initialize the sum and count
                int sum = 0;
                int count = 0;

                // Iterate over all plausible nine indices.
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        // If the indices form valid neighbor
                        if (0 <= x && x < m && 0 <= y && y < n) {
                            sum += img[x][y];
                            count += 1;
                        }
                    }
                }

                // Store the rounded down value in smoothImg[i][j].
                smoothImg[i][j] = sum / count;
            }
        }

        // Return the smooth image.
        return smoothImg;
    }
};


// 671. Second Minimum Node In a Binary Tree
class Solution {
public:

    void solve(TreeNode* root, long long& small, long long& ans){
        if(root == nullptr){
            return;
        }

        // Found a new smallest value
        if(root->val < small){
            ans = small;
            small = root->val;
        }

        // Found a possible second smallest distinct value
        else if(root->val > small && root->val < ans){
            ans = root->val;
        }

        solve(root->left, small, ans);
        solve(root->right, small, ans);
    }

    int findSecondMinimumValue(TreeNode* root) {
        long long small = LLONG_MAX;
        long long ans = LLONG_MAX;

        solve(root, small, ans);

        return ans == LLONG_MAX ? -1 : ans;
    }
};




// # # # # ## # # # ## # # # ## # # # ## # # # ## # # # ## # # # ## # # # #


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