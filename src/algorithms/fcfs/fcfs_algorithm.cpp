#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
    auto decision = std::make_shared<SchedulingDecision>();
    if(this->queue.front())
    {
      if(this->queue.front()->current_state == READY)
      {
        decision->explanation = "Selected from " + std::to_string(this->size()) + " threads. Will run to completion of burst.";
        decision->thread = this->queue.front();
        this->queue.pop();
      }
      else
      {
        decision->explanation = "No threads available for scheduling.";
      }
    }
    else
    {
      decision->explanation = "No threads available for scheduling.";
    }
    decision->time_slice = -1;
    return decision;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
   this->queue.push(thread);
   return;
}

size_t FCFSScheduler::size() const {
    return this->queue.size();
}
