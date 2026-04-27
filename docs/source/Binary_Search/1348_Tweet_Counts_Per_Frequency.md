# Tweet Counts Per Frequency

## [Problem statement](https://leetcode.com/problems/tweet-counts-per-frequency/description/)
A social media company is trying to monitor activity on their site by analyzing the number of tweets that occur in select periods of time. These periods can be partitioned into smaller time chunks based on a certain frequency (every minute, hour, or day).

For example, the period `[10, 10000]` (in seconds) would be partitioned into the following time chunks with these frequencies:

* Every minute (60-second chunks): `[10,69]`, `[70,129]`, `[130,189]`, ..., `[9970,10000]`
* Every hour (3600-second chunks): `[10,3609]`, `[3610,7209]`, `[7210,10000]`
* Every day (86400-second chunks): `[10,10000]`

Notice that the last chunk may be shorter than the specified frequency's chunk size and will always end with the end time of the period (10000 in the above example).

Design and implement an API to help the company with their analysis.

Implement the `TweetCounts` class:

* `TweetCounts()` Initializes the `TweetCounts` object.
* `void recordTweet(String tweetName, int time)` Stores the `tweetName` at the recorded time (in seconds).
* `List<Integer> getTweetCountsPerFrequency(String freq, String tweetName, int startTime, int endTime)` Returns a list of integers representing the number of tweets with `tweetName` in each time chunk for the given period of time `[startTime, endTime]` (in seconds) and frequency `freq`.
`freq` is one of `"minute"`, `"hour"`, or `"day"` representing a frequency of every minute, hour, or day respectively.

### Example:
```
Input
["TweetCounts","recordTweet","recordTweet","recordTweet","getTweetCountsPerFrequency","getTweetCountsPerFrequency","recordTweet","getTweetCountsPerFrequency"]
[[],["tweet3",0],["tweet3",60],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]

Output
[null,null,null,null,[2],[2,1],null,[4]]

Explanation
TweetCounts tweetCounts = new TweetCounts();
tweetCounts.recordTweet("tweet3", 0);                              // New tweet "tweet3" at time 0
tweetCounts.recordTweet("tweet3", 60);                             // New tweet "tweet3" at time 60
tweetCounts.recordTweet("tweet3", 10);                             // New tweet "tweet3" at time 10
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 59); // return [2]; chunk [0,59] had 2 tweets
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 60); // return [2,1]; chunk [0,59] had 2 tweets, chunk [60,60] had 1 tweet
tweetCounts.recordTweet("tweet3", 120);                            // New tweet "tweet3" at time 120
tweetCounts.getTweetCountsPerFrequency("hour", "tweet3", 0, 210);  // return [4]; chunk [0,210] had 4 tweets
```

### Constraints:

* `0 <= time, startTime, endTime <= 10^9`
* `0 <= endTime - startTime <= 10^4`
* There will be at most `10^4` calls in total to `recordTweet` and `getTweetCountsPerFrequency`.

## First thoughts

At first glance, the problem feels a little abstract. One thing worth noting is that tweets are not necessarily recorded in chronological order — for instance, a tweet at time 10 can be recorded after one at time 60. Keeping that in mind is essential to designing a correct solution.

## Minimum design

The core requirement is straightforward: we need a data structure that maps each `tweetName` to a collection of recorded timestamps. Whenever `recordTweet(tweetName, time)` is called, the timestamp is added to that collection. Then, when `getTweetCountsPerFrequency` is called, we look up the timestamps for the given `tweetName` and count how many fall into each time chunk.

The outer map does not need to maintain any particular order over tweet names, so an `unordered_map` is a natural fit. The more interesting design decision is what collection to use for storing the timestamps — and that's where the three solutions below differ.

## Solution 1: List

The simplest approach is to store timestamps in an unsorted list. When querying, we iterate through every recorded timestamp and determine which chunk it belongs to using this formula:

```cpp
int idx = (*it - startTime) / numSeconds;
```

### Code

```cpp
class TweetCounts {
public:
    TweetCounts() {}
    
    void recordTweet(const string& tweetName, int time) {
        tweetTimes[tweetName].push_back(time);
    }
    
    vector<int> getTweetCountsPerFrequency(const string& freq, const string& tweetName, int startTime, int endTime) {
        auto tweetTimesIt = tweetTimes.find(tweetName);
        if (tweetTimesIt == tweetTimes.end()) return {};

        auto& recordedTimes = tweetTimesIt->second;
        if (recordedTimes.empty()) return {};
        const int numSeconds = numOfSeconds.at(freq);
        const int numOfChunks = (endTime - startTime) / numSeconds + 1;
        vector<int> chunks(numOfChunks);

        auto it = recordedTimes.begin();
        while (it != recordedTimes.end()) {
            if (startTime <= *it && *it <= endTime) {
                int idx = (*it - startTime) / numSeconds;
                chunks[idx]++;                
            }
            it++;
        }
        return chunks;
    }
private:
    unordered_map<string, list<int>> tweetTimes;
    const unordered_map<string, int> numOfSeconds = {
        {"minute", 60},
        {"hour", 3600},
        {"day", 86400}
    };
};
```

A `list` is used here instead of a `vector` to avoid the cost of memory reallocation as new timestamps are appended.

### Runtime analysis

* `recordTweet()` takes `O(1)`.
* `getTweetCountsPerFrequency()` takes `O(N)` where N is the number of recorded timestamps for the given tweet name.

## Solution 2: Multiset

The weakness of Solution 1 is that we always scan the entire collection, even when the query window `[startTime, endTime]` covers only a small range of timestamps. If we keep the timestamps sorted, we can skip directly to the relevant portion.

A `multiset` maintains sorted order while allowing duplicate values. Its `lower_bound` method performs a binary search to find the first timestamp that is at least `startTime`, so we only iterate over the timestamps that actually fall within the query window.

### Code

```cpp
class TweetCounts {
public:
    TweetCounts() {}
    
    void recordTweet(const string& tweetName, int time) {
        tweetTimes[tweetName].insert(time);
    }
    
    vector<int> getTweetCountsPerFrequency(const string& freq, const string& tweetName, int startTime, int endTime) {
        auto tweetTimesIt = tweetTimes.find(tweetName);
        if (tweetTimesIt == tweetTimes.end()) return {};

        auto& recordedTimes = tweetTimesIt->second;
        if (recordedTimes.empty()) return {};
        const int numSeconds = numOfSeconds.at(freq);
        const int numOfChunks = (endTime - startTime) / numSeconds + 1;
        vector<int> chunks(numOfChunks);

        auto it = recordedTimes.lower_bound(startTime);
        while (it != recordedTimes.end() && *it <= endTime) {
            int idx = (*it - startTime) / numSeconds;
            chunks[idx]++;
            it++;                
        }
        return chunks;
    }
private:
    unordered_map<string, multiset<int>> tweetTimes;
    const unordered_map<string, int> numOfSeconds = {
        {"minute", 60},
        {"hour", 3600},
        {"day", 86400}
    };
};
```

### Runtime analysis

* `recordTweet()` takes `O(log N)` where `N` is the current size of the multiset.
* `getTweetCountsPerFrequency()` takes `O(log N + M)` where `N` is the total number of stored timestamps and `M` is the number of timestamps that fall within `[startTime, endTime]`.

## Solution 3: Map

Some test cases on LeetCode contain many duplicate timestamps. While this may seem unusual in a real-world context, it is worth optimizing for. With a `multiset`, duplicate timestamps are stored and iterated over individually. A `map` from timestamp to count avoids this by collapsing all duplicates into a single entry.

### Code
```cpp
class TweetCounts {
public:
    TweetCounts() {}
    
    void recordTweet(const string& tweetName, int time) {
        tweetTimes[tweetName][time]++;
    }
    
    vector<int> getTweetCountsPerFrequency(const string& freq, const string& tweetName, int startTime, int endTime) {
        auto tweetTimesIt = tweetTimes.find(tweetName);
        if (tweetTimesIt == tweetTimes.end()) return {};

        auto& recordedTimes = tweetTimesIt->second;
        if (recordedTimes.empty()) return {};
        const int numSeconds = numOfSeconds.at(freq);
        const int numOfChunks = (endTime - startTime) / numSeconds + 1;
        vector<int> chunks(numOfChunks);

        auto it = recordedTimes.lower_bound(startTime);
        while (it != recordedTimes.end() && it->first <= endTime) {
            int idx = (it->first - startTime) / numSeconds;
            chunks[idx] += it->second;
            it++;                
        }
        return chunks;
    }
private:
    unordered_map<string, map<int, int>> tweetTimes;
    const unordered_map<string, int> numOfSeconds = {
        {"minute", 60},
        {"hour", 3600},
        {"day", 86400}
    };
};
```

Since each unique timestamp is stored only once alongside its count, the query loop skips over all duplicates in a single step.

### Runtime analysis

`getTweetCountsPerFrequency()` takes `O(log N + M)` where `N` is the number of unique timestamps and `M` is the number of unique timestamps within `[startTime, endTime]`. In the presence of many duplicates, this is a meaningful improvement over Solution 2.

## Key takeaways

The three solutions illustrate a classic trade-off in data structure design: the way you store data shapes how efficiently you can query it.

- **Solution 1 (list)** is the most straightforward. Recording a tweet is O(1), but every query requires a full scan. It works, but leaves performance on the table.
- **Solution 2 (multiset)** improves query performance by keeping timestamps sorted. Using `lower_bound` lets us skip directly to the relevant window, reducing query time from O(N) to O(log N + M). The cost is that insertion becomes O(log N), and duplicates are still stored individually.
- **Solution 3 (map)** goes one step further by collapsing duplicate timestamps into a count. When duplicates are frequent, this reduces both the memory footprint and the number of iterations during a query.

A recurring pattern across all three solutions is the chunk index formula `(time - startTime) / numSeconds`, which neatly maps any timestamp to its corresponding bucket regardless of the frequency. It is a small detail, but it is the mathematical core that makes the whole approach work.