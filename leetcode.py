
##205. Isomorphic Strings
class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        char_index_s = {}
        char_index_t = {}

        for i in range(len(s)):
            if s[i] not in char_index_s:
                char_index_s[s[i]] = i

            if t[i] not in char_index_t:
                char_index_t[t[i]] = i
            
            if char_index_s[s[i]] != char_index_t[t[i]]:
                return False

        return True

##206. Reverse Linked List


class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution(object):
    def reverseList(self, head):
        prev = None  # Initialize prev as None
        curr = head  # Start with curr at the head of the list

        while curr:
            temp = curr.next  # Store the next node
            curr.next = prev  # Reverse the pointer
            prev = curr       # Move prev forward
            curr = temp      # Move curr forward

        return prev  # prev is the new head of the reversed list


##217. Contains Duplicate
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        nums.sort()
        n = len(nums)
        for i in range(1, n):
            if nums[i] == nums[i - 1]:
                return True
        return False


##219. Contains Duplicate II

from typing import List

class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        window_set = set()
        
        for i in range(len(nums)):
            // Remove element that is no longer in the window
            if i > k:
                window_set.remove(nums[i - k - 1])
            
            // Check for duplicate in the current window
            if nums[i] in window_set:
                return True
            
            window_set.add(nums[i])
            
        return False



##225. Implement Stack using Queues
class MyStack:

    def __init__(self):
        self.q = deque()

    def push(self, x: int) -> None:
        self.q.append(x)
        for _ in range(len(self.q) - 1):
            self.q.append(self.q.popleft())

    def pop(self) -> int:
        return self.q.popleft()
        
    def top(self) -> int:
        return self.q[0]

    def empty(self) -> bool:
        return len(self.q) == 0

##226. Invert Binary Tree

class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
    
        if not root:
            return
        
        temp = root.left
        root.left = root.right
        root.right = temp

        self.invertTree(root.left)
        self.invertTree(root.right)

        return root


##228. Summary Ranges
from typing import List

class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        if not nums:
            return []
            
        result = []
        i = 0
        while i < len(nums):
            start = nums[i]
            j = i
            // Expand the range as long as elements are consecutive
            while j + 1 < len(nums) and nums[j + 1] == nums[j] + 1:
                j += 1
            
            // Format the range string
            if nums[j] == start:
                result.append(str(start))
            else:
                result.append(f"{start}->{nums[j]}")
            
            // Move to the next potential start of a range
            i = j + 1
        return result

##231. Power of Two
class Solution(object):
    def isPowerOfTwo(self, n):
        return n and not (n & n - 1)


##232. Implement Queue using Stacks
class MyQueue:

    def __init__(self):
        self.input = []
        self.output = []

    def push(self, x: int) -> None:
        self.input.append(x)

    def pop(self) -> int:
        self.peek()  # Ensure output stack has the current front
        return self.output.pop()

    def peek(self) -> int:
        if not self.output:  # Transfer elements if output stack is empty
            while self.input:
                self.output.append(self.input.pop())
        return self.output[-1]

    def empty(self) -> bool:
        return not self.input and not self.output

##234. Palindrome Linked List
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        slow, fast, prev = head, head, None
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
        prev, slow, prev.next = slow, slow.next, None
        while slow:
            slow.next, prev, slow = prev, slow, slow.next
        fast, slow = head, prev
        while slow:
            if fast.val != slow.val: return False
            fast, slow = fast.next, slow.next
        return True


# 242. Valid Anagram
class Solution:
    def isAnagram(self, s: str, t: str) -> bool:  
        if len(s) != len(t):
            return False

        counter = {}

        for char in s:
            counter[char] = counter.get(char, 0) + 1

        for char in t:
            if char not in counter or counter[char] == 0:
                return False
            counter[char] -= 1

        return True


# 257. Binary Tree Paths
class Solution(object):
    def binaryTreePaths(self, root):
        res = []
        if not root:
            return res
        stack = [(root, str(root.val))]
        while stack:
            node, path = stack.pop()
            if not node.left and not node.right:
                res.append(path)
            if node.right:
                stack.append((node.right, path + "->" + str(node.right.val)))
            if node.left:
                stack.append((node.left, path + "->" + str(node.left.val)))
        return res


# 258. Add Digits


class Solution(object):
    def addDigits(self, num):
        if num == 0:
            return 0
        if num % 9 == 0:
            return 9
        else:
            return num % 9
        
# 263. Ugly Number
class Solution(object):
    def isUgly(self, n):
        if n <= 0:
            return False

        factors = [2, 3, 5]
        for factor in factors:
            while n % factor == 0:
                n //= factor

        return n == 1



# 268. Missing Number
class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        n = len(nums)
        v = [-1] * (n + 1)
        for num in nums:
            v[num] = num
        for i in range(len(v)):
            if v[i] == -1:
                return i
        return 0



#278. First Bad Version 

# The isBadVersion API is already defined for you.
# def isBadVersion(version: int) -> bool:


class Solution:
    def firstBadVersion(self, n: int) -> int:
        first, last = 1, n

        while first < last:
            mid = first + (last - first) // 2

            if isBadVersion(mid):
                last = mid  # The first bad version could be mid or before.
            else:
                first = mid + 1  # The first bad version must be after mid.

        return first  # At the end, first will be the first bad version.

# 283. Move Zeroes
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        left = 0

        for right in range(len(nums)):
            if nums[right] != 0:
                nums[right], nums[left] = nums[left], nums[right]
                left += 1
        
        return nums

# 290. Word Pattern
class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:

        s = s.split()

        return (len(set(pattern)) ==
                len(set(s)) ==
                len(set(zip_longest(pattern,s))))


# 292. Nim Game
class Solution:
    def canWinNim(self, n: int) -> bool:
        return n % 4 != 0


# 303. Range Sum Query - Immutable
class NumArray:  # 68 ms, faster than 97.72%

    def __init__(self, nums: List[int]):
        self.preSum = nums  # pass by pointer!
        for i in range(len(nums)-1):
            self.preSum[i+1] += self.preSum[i]

    def sumRange(self, left: int, right: int) -> int:
        if left == 0: return self.preSum[right]
        return self.preSum[right] - self.preSum[left-1]


# 326. Power of Three
# Python
class Solution:
    def isPowerOfThree(self, n: int) -> bool:
        if n <= 0:
            return False
        while n % 3 == 0:
            n //= 3
        return n == 1

##171. Excel Sheet Column Number
class Solution:
    def titleToNumber(self, columnTitle: str) -> int:
        ans = 0

        # Read left to right like normal positional numbers.
        for ch in columnTitle:
            # Shift existing value one base-26 place to the left,
            # then add current letter value (A=1 ... Z=26).
            ans = ans * 26 + (ord(ch) - ord('A') + 1)

        return ans


##202. Happy Number

class Solution:
    def isHappy(self, n: int) -> bool:    
        visit = set()
        
        def get_next_number(n):    
            output = 0
            
            while n:
                digit = n % 10
                output += digit ** 2
                n = n // 10
            
            return output

        while n not in visit:
            visit.add(n)
            n = get_next_number(n)
            if n == 1:
                return True
        
        return False


##203. Remove Linked List Elements
class Solution:
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        ans = ListNode(0, head)
        dummy = ans

        while dummy:
            while dummy.next and dummy.next.val == val:
                dummy.next = dummy.next.next
            dummy = dummy.next
        
        return ans.next

        

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        i = 1

        for j in range(1, len(nums)):
            if nums[j] != nums[i - 1]:
                nums[i] = nums[j]
                i += 1
        
        return i


##EJERCICIO 27
class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        index = 0
        for i in range(len(nums)):
            if nums[i] != val:
                nums[index] = nums[i]
                index += 1
        return index


#EJERCICIO 28
class Solution:
    def strStr(self, haystack, needle):
        for i in range(len(haystack) - len(needle) + 1):
            if haystack[i:i+len(needle)] == needle:
                return i
        return -1


#EJERCICIO 29
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        if dividend == divisor:
            return 1
        if dividend == -2**31 and divisor == -1:
            return (2**31) - 1 
        
        if divisor == 1:
            return dividend
        
        sign = -1 if (dividend < 0) ^ (divisor < 0) else 1
        
        n, d = abs(dividend), abs(divisor)
        ans = 0

        while n >= d:
            p = 0
            while n >= (d << p):
                p += 1
            
            p -= 1
            n -= (d << p)
            ans += (1 << p)

        return min(max(sign * ans, -2**31), 2**31 - 1)




        #EJERCICIO 31
        class Solution:
    def nextPermutation(self, nums):
        i = len(nums) - 2
        while i >= 0 and nums[i + 1] <= nums[i]:
            i -= 1
        if i >= 0:
            j = len(nums) - 1
            while nums[j] <= nums[i]:
                j -= 1
            self.swap(nums, i, j)
        self.reverse(nums, i + 1)

    def reverse(self, nums, start):
        i, j = start, len(nums) - 1
        while i < j:
            self.swap(nums, i, j)
            i += 1
            j -= 1

    def swap(self, nums, i, j):
        temp = nums[i]
        nums[i] = nums[j]
        nums[j] = temp


        #EJERCICIO 32


        class Solution:
    def longestValidParentheses(self, s: str) -> int:
        stack = [-1]
        max_len = 0

        for i in range(len(s)):
            if s[i] == "(":
                stack.append(i)
            else:
                stack.pop()
                if len(stack) == 0:
                    stack.append(i)
                else:
                    max_len = max(max_len, i - stack[-1])
        
        return max_len


##67. Add Binary
class Solution:
  def addBinary(self, a: str, b: str) -> str:
    s = []
    carry = 0
    i = len(a) - 1
    j = len(b) - 1

    while i >= 0 or j >= 0 or carry:
      if i >= 0:
        carry += int(a[i])
        i -= 1
      if j >= 0:
        carry += int(b[j])
        j -= 1
      s.append(str(carry % 2))
      carry //= 2

    return ''.join(reversed(s))


## 69 Sqrt(x)


##70. Climbing Stairs
class Solution:
    def climbStairs(self, n: int) -> int:
        memo = {}
        return self.helper(n, memo)
    
    def helper(self, n: int, memo: dict[int, int]) -> int:
        if n == 0 or n == 1:
            return 1
        if n not in memo:
            memo[n] = self.helper(n-1, memo) + self.helper(n-2, memo)
        return memo[n]


### 88. Merge Sorted Array
class Solution(object):
    def merge(self, nums1, m, nums2, n):
        i = m - 1
        j = n - 1
        k = m + n - 1
        
        while j >= 0:
            if i >= 0 and nums1[i] > nums2[j]:
                nums1[k] = nums1[i]
                i -= 1
            else:
                nums1[k] = nums2[j]
                j -= 1
            k -= 1


##94. Binary Tree Inorder Traversal
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def inorderTraversal(self, root):
        res = []
        stack = []
        curr = root
        while curr or stack:
            while curr:
                stack.append(curr)
                curr = curr.left
            curr = stack.pop()
            res.append(curr.val)

        return res

##100. Same Tree
class Solution:
    def isSameTree(self, p, q):
        # If both nodes are None, they are identical
        if p is None and q is None:
            return True
        # If only one of the nodes is None, they are not identical
        if p is None or q is None:
            return False
        # Check if values are equal and recursively check left and right subtrees
        if p.val == q.val:
            return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
        # Values are not equal, they are not identical
        return False
        

#345. Reverse Vowels of a String
class Solution(object):
    def reverseVowels(self, s):
        # Convert the input string to a character array.
        word = list(s)
        start = 0
        end = len(s) - 1
        vowels = "aeiouAEIOU"
        
        # Loop until the start pointer is no longer less than the end pointer.
        while start < end:
            # Move the start pointer towards the end until it points to a vowel.
            while start < end and vowels.find(word[start]) == -1:
                start += 1
            
            # Move the end pointer towards the start until it points to a vowel.
            while start < end and vowels.find(word[end]) == -1:
                end -= 1
            
            # Swap the vowels found at the start and end positions.
            word[start], word[end] = word[end], word[start]
            
            # Move the pointers towards each other for the next iteration.
            start += 1
            end -= 1
        
        # Convert the character array back to a string and return the result.
        return "".join(word)


#605. Can Place Flowers
class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        count = 0
        for i in range(len(flowerbed)):
            # Check if the current plot is empty.
            if flowerbed[i] == 0:
                # Check if the left and right plots are empty.
                empty_left_plot = (i == 0) or (flowerbed[i - 1] == 0)
                empty_right_lot = (i == len(flowerbed) - 1) or (flowerbed[i + 1] == 0)
                
                # If both plots are empty, we can plant a flower here.
                if empty_left_plot and empty_right_lot:
                    flowerbed[i] = 1
                    count += 1
                    
        return count >= n

        class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        count = 0
        for i in range(len(flowerbed)):
            # Check if the current plot is empty.
            if flowerbed[i] == 0:
                # Check if the left and right plots are empty.
                empty_left_plot = (i == 0) or (flowerbed[i - 1] == 0)
                empty_right_lot = (i == len(flowerbed) - 1) or (flowerbed[i + 1] == 0)
                
                # If both plots are empty, we can plant a flower here.
                if empty_left_plot and empty_right_lot:
                    flowerbed[i] = 1
                    count += 1
                    if count >= n:
                        return True
                    
        return count >= n

#1431. Kids With the Greatest Number of Candies

class Solution(object):
    def kidsWithCandies(self, candies, extraCandies):
        # Find out the greatest number of candies among all the kids.
        maxCandies = max(candies)
        # For each kid, check if they will have greatest number of candies
        # among all the kids.
        result = []
        for i in range(len(candies)):            
            result.append(candies[i] + extraCandies >= maxCandies)
        return result
        

#739. Daily Temperatures
class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        st = []
        res = [0] * len(temperatures)

        for i in range(len(temperatures)):
            while st and temperatures[i] > temperatures[st[-1]]:
                idx = st.pop()
                res[idx] = i - idx
            st.append(i)
        
        return res

##901. Online Stock Span
class StockSpanner:

    def __init__(self):
        
        # maintain a monotonic stack for stock entry
        
		## definition of stock entry:
        # first parameter is price quote
        # second parameter is price span
        self.monotone_stack = []
              
        
        
    def next(self, price: int) -> int:

        stack = self.monotone_stack
        
        cur_price_quote, cur_price_span = price, 1
        
        # Compute price span in stock data with monotonic stack
        while stack and stack[-1][0] <= cur_price_quote:
            
            prev_price_quote, prev_price_span = stack.pop()
            
            # update current price span with history data in stack
            cur_price_span += prev_price_span
        
        # Update latest price quote and price span
        stack.append( (cur_price_quote, cur_price_span) )
        
        return cur_price_span


        #443. String Compression

class Solution:
    def compress(self, chars: List[str]) -> int:
        i = 0
        res = 0
        while i < len(chars):
            group_length = 1
            while (i + group_length < len(chars)
                   and chars[i + group_length] == chars[i]):
                group_length += 1
            chars[res] = chars[i]
            res += 1
            if group_length > 1:
                str_repr = str(group_length)
                chars[res:res+len(str_repr)] = list(str_repr)
                res += len(str_repr)
            i += group_length
        return res


        #334. Increasing Triplet Subsequence
        class Solution:
    def increasingTriplet(self, nums):
        first = float('inf')
        second = float('inf')
        for n in nums:
            if n <= first:
                first = n
            elif n <= second:
                second = n
            else:
                return True
        return False


        #332. Reconstruct Itinerary
        def findItinerary(self, tickets):
    targets = collections.defaultdict(list)
    for a, b in sorted(tickets)[::-1]:
        targets[a] += b,
    route = []
    def visit(airport):
        while targets[airport]:
            visit(targets[airport].pop())
        route.append(airport)
    visit('JFK')
    return route[::-1]

###1071. Greatest Common Divisor of Strings

class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        len1, len2 = len(str1), len(str2)
        
        def valid(k):
            if len1 % k or len2 % k: 
                return False
            n1, n2 = len1 // k, len2 // k
            base = str1[:k]
            return str1 == n1 * base and str2 == n2 * base 
        
        for i in range(min(len1, len2), 0, -1):
            if valid(i):
                return str1[:i]
        return ""


    ##1768. Merge Strings Alternately

class Solution(object):
    def mergeAlternately(self, word1, word2):
        result = []
        n = max(len(word1), len(word2))
        for i in range(n):
            if i < len(word1):
                result += word1[i]
            if i < len(word2):
                result += word2[i]

        return "".join(result)

##283. Move Zeroes

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        left = 0

        for right in range(len(nums)):
            if nums[right] != 0:
                nums[right], nums[left] = nums[left], nums[right]
                left += 1
        
        return nums


##392. Is Subsequence
class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        sp = tp = 0

        while sp < len(s) and tp < len(t):
            if s[sp] == t[tp]:
                sp += 1
            tp += 1
        
        return sp == len(s)


##11. Container With Most Water
class Solution:
    def maxArea(self, height: List[int]) -> int:
        max_area = 0
        left = 0
        right = len(height) - 1

        while left < right:
            max_area = max(max_area, (right - left) * min(height[left], height[right]))

            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        
        return max_area




##1679. Max Number of K-Sum Pairs
class Solution:
    def maxOperations(self, nums: List[int], k: int) -> int:
        nums.sort()
        i, j = 0, len(nums) - 1
        count = 0

        while i < j:
            total = nums[i] + nums[j]
            if total == k:
                count += 1
                i += 1
                j -= 1
            elif total > k:
                j -= 1
            else:
                i += 1

        return count