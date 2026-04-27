#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <iostream>
using namespace std;
const unordered_map<string, int> numOfSeconds = {
    {"minute", 60},
    {"hour", 3600},
    {"day", 86400}
};

class TweetCounts {
public:
    TweetCounts() {
        
    }
    
    void recordTweet(const string& tweetName, int time) {
        tweetTimes[tweetName].insert(time);
    }
    
    vector<int> getTweetCountsPerFrequency(const string& freq, const string& tweetName, int startTime, int endTime) {
        vector<int> chunks;
        auto tweetTimesIt = tweetTimes.find(tweetName);
        if (tweetTimesIt == tweetTimes.end() || tweetTimesIt->second.empty()) return chunks;

        auto& recordedTimes = tweetTimesIt->second; 
        const int numSeconds = numOfSeconds.at(freq);

        auto it = recordedTimes.begin();
       
        while (it != recordedTimes.end() && *it < startTime) it++;

        int thisChunkStart = startTime;

        while (thisChunkStart <= endTime) {
            int thisChunkEnd = min(thisChunkStart + numSeconds, endTime + 1);
            int thisChunkCount = 0;
            while (it != recordedTimes.end() && *it < thisChunkEnd) {
                thisChunkCount++;
                it++;
            }
            chunks.push_back(thisChunkCount);
            thisChunkStart = thisChunkEnd;
        }
        return chunks;
    }
private:
unordered_map<string, multiset<int>> tweetTimes;
};
int main() {
    TweetCounts obj;
    obj.recordTweet("tweet3", 0);
    obj.recordTweet("tweet3", 60);
    obj.recordTweet("tweet3", 10);
    vector<int> param_2 = obj.getTweetCountsPerFrequency("minute", "tweet3", 0, 59);
    for (int count : param_2) {
        cout << count << " ";
    }
    cout << endl;
    param_2 = obj.getTweetCountsPerFrequency("minute", "tweet3", 0, 60);
    for (int count : param_2) {
        cout << count << " ";
    }
    cout << endl;
    obj.recordTweet("tweet3", 210);
    param_2 = obj.getTweetCountsPerFrequency("hour", "tweet3", 0, 210);
    for (int count : param_2) {
        cout << count << " ";
    }
    cout << endl;
}
/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */