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

bool scheduleHelper (DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t row, size_t col, vector<size_t>& numShifts);
bool DailyScheduleComplete(DailySchedule& sched);


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
    //resie and initalize
    sched.resize(avail.size(), vector<Worker_T>());
    vector<size_t> numShifts(avail[0].size(), 0);
    return scheduleHelper(sched, avail, dailyNeed, maxShifts, 0,0, numShifts);





}
//recursive schedule function to generate shedule
bool scheduleHelper (DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t row, size_t col, vector<size_t>& numShifts)
{
  //base case if all days are scheduled
  if (row == avail.size())
  {
    return true;
  }
  //iterate over shifts for current day
  else{
    for(size_t i = col; i <avail[0].size(); i++)
    {
      //check if exceeds number
      if(avail[row][i] && numShifts[i] < maxShifts)
      {
        sched[row].push_back(i);
        numShifts[i]++;
        if(sched[row].size() == dailyNeed)
        {
          //assign worker to the currents day scheduled
          if(scheduleHelper(sched, avail, dailyNeed, maxShifts, row+1, 0, numShifts))
          {
            return true;
          }
        }
        //recursively call with the next shift for the current day
        bool status = scheduleHelper(sched, avail, dailyNeed, maxShifts, row, i+1, numShifts);
        if(status)
        {
          return true;
        }
        //if not backtrack
        sched[row].pop_back();
        numShifts[i]--;
      }
    }
    return false;
  }
}

