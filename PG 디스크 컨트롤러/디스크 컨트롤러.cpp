#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int N = jobs.size();
    sort(jobs.begin(), jobs.end(), [&](vector<int> a, vector<int> b) {
        if (a[0] == b[0]) {
            return a[1] < b[1];
        } else {
            return a[0] < b[0];
        }
    });
    deque<vector<int>> schedules;
    int start = 0;
    for (int i = 0; i < N; i++) {
        vector<int> job;
        job.push_back(jobs[i][0]);
        job.push_back(jobs[i][1]);
        job.push_back(jobs[i][0]);
        job.push_back(jobs[i][0] + jobs[i][1]);
        schedules.push_back(job);
    }
    sort(schedules.begin(), schedules.end(), [&](vector<int> a, vector<int> b) {
        if (a[2] == b[2]) {
            return a[3] < b[3];
        } else {
            return a[2] < b[2];
        }
    });
    int current = 0;
    int sum = 0;
    while (!schedules.empty()) {
        vector<int> currentJob = schedules.front();
        schedules.pop_front();
        current = currentJob[3];
        sum += currentJob[3] - currentJob[0];
        if (schedules.empty()) {
            break;
        }
        for (int i = 0; i < schedules.size(); i++) {
            vector<int> job = schedules.front();
            schedules.pop_front();
            if (job[2] < currentJob[3]) {
                int diff = currentJob[3] - job[2];
                job[2] += diff;
                job[3] += diff;
            }
            schedules.push_back(job);
        }
        sort(schedules.begin(), schedules.end(), [&](vector<int> a, vector<int> b) {
            if (a[2] == b[2]) {
                return a[3] < b[3];
            } else {
                return a[2] < b[2];
            }
        });
    }
    
    answer = sum / N;
    
    return answer;
}