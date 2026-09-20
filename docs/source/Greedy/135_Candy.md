# 135. Candy

## Problem Statement

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104


## Approach

### Idea

Since we want minimum candies, we should give each child just enough candies to satisfy the conditions. 
- if this child has higher rating than previous one, we add 1 candy to this child.
- if this child has lower rating than previous one, we reset the candy count to 1 (this child must have at least 1 candy)

Extreme cases:
- if the ratings are increasing [0,1,2,3,4,5] then the candies must be [1,2,3,4,5,6]
- if the ratings are decreasing [5,4,3,2,1,0] then the candies must be [6,5,4,3,2,1]

It seems the longest monotone sorted sub ratings determines the max candies.

If ratings = [1,6,5,2,3,4,5,3,1], the longest sorted sub ratings is [2,3,4,5]. Its candies should be [1,2,3,4]

[1,3,2,1,2,3,4,2,1]

### Code

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int count = 0;
        int lastCandies = 0;
        for (auto r : ratings) {
            if (r > lastCandies) {
                count += lastCandies + 1;
                lastCandies++;
            } else {
                count += 1;
                lastCandies = 0;
            }   
        }      
    }
};
```

### Complexity

- Time complexity:
- Space complexity:

## Conclusion



## References & Further Reading

**Related LeetCode Problems:**

- 

**Patterns:**

- 
