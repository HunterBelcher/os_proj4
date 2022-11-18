#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
  auto decision = std::make_shared<SchedulingDecision>();
  if(!this->queue.empty())
  {
    if(this->queue.top()->current_state == READY)
    {
      decision->explanation = "Selected from " + std::to_string(this->size()) + " threads. Will run to completion of burst.";
      decision->thread = this->queue.top();
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

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
  this->queue.push(thread->get_next_burst(BurstType::CPU)->length, thread);
}

size_t SPNScheduler::size() const {
    return this->queue.size();
}
