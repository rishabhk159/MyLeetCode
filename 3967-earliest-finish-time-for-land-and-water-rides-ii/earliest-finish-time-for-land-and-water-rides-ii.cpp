class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {

        const int INF = 1e9;

        // Sort water rides by start time
        vector<pair<int, int>> water;

        for (int i = 0; i < waterStartTime.size(); i++) {
            water.push_back({waterStartTime[i], waterDuration[i]});
        }

        sort(water.begin(), water.end());

        int m = water.size();

        // prefixMin[i] = minimum duration among water rides [0...i]
        vector<int> prefixMin(m);

        // suffixMin[i] = minimum (start + duration) among [i...m-1]
        vector<int> suffixMin(m);

        prefixMin[0] = water[0].second;

        for (int i = 1; i < m; i++) {
            prefixMin[i] = min(prefixMin[i - 1], water[i].second);
        }

        suffixMin[m - 1] = water[m - 1].first + water[m - 1].second;

        for (int i = m - 2; i >= 0; i--) {
            suffixMin[i] = min(
                suffixMin[i + 1],
                water[i].first + water[i].second
            );
        }

        int ans = INF;

        // Land -> Water
        for (int i = 0; i < landStartTime.size(); i++) {
            int finishLand = landStartTime[i] + landDuration[i];

            // Find the last water ride with startTime <= finishLand
            int left = 0, right = m - 1;
            int pos = -1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (water[mid].first <= finishLand) {
                    pos = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            // Water ride is already open
            if (pos != -1) {
                ans = min(ans, finishLand + prefixMin[pos]);
            }

            // Water ride opens after we finish land ride
            if (pos + 1 < m) {
                ans = min(ans, suffixMin[pos + 1]);
            }
        }

        // Now do the same for Water -> Land

        vector<pair<int, int>> land;

        for (int i = 0; i < landStartTime.size(); i++) {
            land.push_back({landStartTime[i], landDuration[i]});
        }

        sort(land.begin(), land.end());

        int n = land.size();

        vector<int> landPrefix(n);
        vector<int> landSuffix(n);

        landPrefix[0] = land[0].second;

        for (int i = 1; i < n; i++) {
            landPrefix[i] = min(landPrefix[i - 1], land[i].second);
        }

        landSuffix[n - 1] = land[n - 1].first + land[n - 1].second;

        for (int i = n - 2; i >= 0; i--) {
            landSuffix[i] = min(
                landSuffix[i + 1],
                land[i].first + land[i].second
            );
        }

        // Water -> Land
        for (int i = 0; i < waterStartTime.size(); i++) {
            int finishWater = waterStartTime[i] + waterDuration[i];

            int left = 0, right = n - 1;
            int pos = -1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (land[mid].first <= finishWater) {
                    pos = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            // Land ride is already open
            if (pos != -1) {
                ans = min(ans, finishWater + landPrefix[pos]);
            }

            // Land ride opens after we finish water ride
            if (pos + 1 < n) {
                ans = min(ans, landSuffix[pos + 1]);
            }
        }

        return ans;
    }
};