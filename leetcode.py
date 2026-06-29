##EJERCICIO 26

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