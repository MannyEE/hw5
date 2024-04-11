#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day, 
    int spot,
    vector<int>& workerShifts
)
{

    if(day == sched.size() /*&& spot == dailyNeed - 1*/) return true;

    for(int i = 0; i < avail[day].size(); ++i) {
        // cout << std::count(sched[day].begin(), sched[day].end(), 0) << "\n";
        if (avail[day][i] == 1 && workerShifts[i] < maxShifts && (std::find(sched[day].begin(), sched[day].end(), i) == sched[day].end())){
            sched[day][spot] = i;
            workerShifts[i]++; 
            bool status;

            if (spot == dailyNeed - 1) {
                status = scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0, workerShifts);
            } else {
                status = scheduleHelper(avail, dailyNeed, maxShifts, sched, day, spot + 1, workerShifts);
            }

            if(status) return true;
            else {
                workerShifts[i]--; 
                sched[day][spot] = -1;
            }
        }
    }
    // avail[0] is day 0, avail[0][0] is worker 1 on day 0
    //sched[0] refers to day 0, sched[0][0] refers to person 0 working is the person working 0th e\person working on day 0
    return false;


}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    
    vector<int> workerShifts;
    // vector<set<int>> workers

    int numWorkers = avail[0].size();
    for (int i = 0; i < numWorkers; ++i) {
        workerShifts.push_back(0);
    }

    for(int i = 0; i < avail.size(); ++i){
        vector<Worker_T> workDay(dailyNeed, -1);
        sched.push_back(workDay);
    }

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, workerShifts);
}

