#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) {
    this->time_slice = slice;
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
  auto decision = std::make_shared<SchedulingDecision>();
  if(this->queue.front())
  {
    if(this->queue.front()->current_state == READY)
    {
      decision->explanation = "Selected from " + std::to_string(this->size()) + " threads. Will run for at most " + std::to_string(this->time_slice) + " ticks.";
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
  decision->time_slice = this->time_slice;
  return decision;
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
  this->queue.push(thread);
}

size_t RRScheduler::size() const {
  return this->queue.size();
}
