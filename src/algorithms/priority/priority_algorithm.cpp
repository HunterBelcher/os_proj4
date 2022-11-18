#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
  auto decision = std::make_shared<SchedulingDecision>();
  if(!this->queue.empty())
  {
    if(this->queue.top()->current_state == READY)
    {
      decision->explanation =
                      "[S: " + std::to_string(this->num_threads[0]) +
                      " I: " + std::to_string(this->num_threads[1]) +
                      " N: " + std::to_string(this->num_threads[2]) +
                      " B: " + std::to_string(this->num_threads[3]) + "] -> ";
      decision->thread = this->queue.top();
      this->queue.pop();
      this->num_threads[decision->thread->priority]--;
      decision->explanation +=
              "[S: " + std::to_string(this->num_threads[0]) +
              " I: " + std::to_string(this->num_threads[1]) +
              " N: " + std::to_string(this->num_threads[2]) +
              " B: " + std::to_string(this->num_threads[3]) + "]."
                                                              " Will run to completion of burst.";
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

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
  this->num_threads[thread->priority]++;
  this->queue.push(thread->priority, thread);
}

size_t PRIORITYScheduler::size() const {
  return this->queue.size();
}
