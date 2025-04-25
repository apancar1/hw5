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
bool recurse(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& workerShifts, size_t day, size_t numAssigned);
bool conditions(const AvailabilityMatrix& avail, DailySchedule& sched, vector<size_t>& workerShifts, size_t worker, size_t day, size_t maxShifts);

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
    // needs to schedule d (needed) out of k (possible) workers per day 
    size_t numWorkers = avail[0].size(); 
    size_t numDays = avail.size(); 
    // given their availability over n day period 
    // exactly d workers required per day 
    // no one can work more than m (maxshifts) over the n day period 
    // function should schedule the nurses: 
    // exactly d work on each of the n days and no one works more than m shifts 
    
    // avail matrix: n row by k column matrix of booleans 
    // row represents on day of the schedule 
    // column is specific worker's availability on that day 

    // produce a schedule that is n by d matrix 
    // row represents a day in the schedule & stores d (IDs of workers who are scheduled for that day)
    // each entry is a value btwn 0 to k-1 

    // initialize the sched matrix (the one we update as we go on):
    sched = DailySchedule(numDays, vector<Worker_T>());
    // vector of vectors indicating the d workers on each of n days 

    // vector that tracks how many shifts each worker is already assigned (helps in checking conditions)
    vector<size_t> workerShifts(numWorkers,0);

    // start recursion now 
    return recurse(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);
    // recursion starts at 0 


}

bool recurse(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& workerShifts, size_t day, size_t numAssigned)
{
    // must use recurisve backtracking approach 
    // can use functions from algorithm such as find() 

    // only use 3 loops: 
    // 2 for set up and one in recursive search 

    // backtracking: 
    // recursive alg that generates all combos but skips recursion & moves on if any constraints are violated
    // recurse over each place in the schedule 
    // each recursive call fills in one of the n*d openings 
    // make sure that the contrainsts (avaialble & maxshifts) are met

    // general backtrack search approach: 
    // 1. select an item & set it to one of its options 
    // such as constraints are met 

    // update variables: 
    size_t numDays = avail.size(); 
    size_t numWorkers = avail[0].size(); 

    // terminating case: all days are filled 
    if (day == numDays){
        return true; 
    }


    // 2. recursively try to set next item 

    // if the requirements for a day are met, move on to next day: 
    if (numAssigned == dailyNeed){
        return recurse(avail, dailyNeed, maxShifts, sched, workerShifts, day+1, 0);
    }

    // 3. if all items are assigned & constraints met, done
    // return through recursion stack with solution 
    // 4. if no viable value for an item exists, 
    // backtrack to prev item & repeat from top 
    // 5. if viable options for 1st item are exhausted, 
    // no solution 

    // 0 is false, any-non zero value is true (1 means avaliable) 

    // helper function to take care of recursion 
    // 2 loops for set up, 1 for recursion 
    // loop through days & workers 

    // using general approach from slides now: 
    // now for loop does most of work: 
    // goal: loop through all workers (for this day - we are only looking at one day at a time)
    for (size_t cur = 0; cur < numWorkers; ++cur){
        // call helper function to see if this worker can be used 
        if (conditions(avail, sched, workerShifts, cur, day, maxShifts)){
            // update variables (we are adding this worker in)
            sched[day].push_back(cur);
            workerShifts[cur]++;
            // if worker is found, move on to next woker requirement slot & return true 
            if (recurse(avail, dailyNeed, maxShifts, sched, workerShifts, day, numAssigned+1)){
                return true; 
            }
            // if not found, then backtrack
            // update variables 
            sched[day].pop_back();
            workerShifts[cur]--;  
        }
    // at end of this for loop, return false (backtracked too far and no solution)
    }
    return false; 
}

bool conditions(const AvailabilityMatrix& avail, DailySchedule& sched, vector<size_t>& workerShifts, size_t worker, size_t day, size_t maxShifts)
{
    // HELPER FUNCTION THAT CHECKS CONDITIONS
    // 3 conditions: 
    // check if worker is available & has not met max shifts & is not already assigned: 
    if ((avail[day][worker]) && (workerShifts[worker] < maxShifts) && (find(sched[day].begin(), sched[day].end(), worker) == sched[day].end())){
        return true; 
    }
    // need to also create a variable that tracks how many shifts each worker has worked <--
    return false; 
}