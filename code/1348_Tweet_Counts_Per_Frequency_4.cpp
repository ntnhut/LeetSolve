#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
using namespace std;
class TweetCounts {
public:
    TweetCounts() {
        
    }
    
    void recordTweet(const string& tweetName, int time) {
        tweetTimes[tweetName][time]++;
    }
    
    vector<int> getTweetCountsPerFrequency(const string& freq, const string& tweetName, int startTime, int endTime) {
        auto tweetTimesIt = tweetTimes.find(tweetName);
        if (tweetTimesIt == tweetTimes.end() || tweetTimesIt->second.empty()) return {};

        auto& recordedTimes = tweetTimesIt->second;
        const int numSeconds = numOfSeconds.at(freq);
        const int numOfChunks = (endTime - startTime) / numSeconds + 1;
        vector<int> chunks(numOfChunks);

        auto it = recordedTimes.lower_bound(startTime);
        while (it != recordedTimes.end() && it->first <= endTime) {
            const int idx = (it->first - startTime) / numSeconds;
            chunks[idx] += it->second;
            ++it;
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