#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int dateToDayOfYear(const string& date) {
        vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        
        int totalDays = day;
        for (int i = 0; i < month - 1; ++i) {
            totalDays += daysInMonth[i];
        }
        
        return totalDays;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int startA = dateToDayOfYear(arriveAlice);
        int endA   = dateToDayOfYear(leaveAlice);
        int startB = dateToDayOfYear(arriveBob);
        int endB   = dateToDayOfYear(leaveBob);
        
        int sharedStart = max(startA, startB);
        int sharedEnd   = min(endA, endB);
        
        if (sharedStart <= sharedEnd) {
            return sharedEnd - sharedStart + 1;
        }
        
        return 0;
    }
};