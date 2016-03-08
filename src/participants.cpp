#include "participants.h"

std::atomic<participant *> global_participants;
std::atomic<size_t> n_participants;

participant *get_active_participants() {
    return global_participants.load(std::memory_order_acquire);
}

void add_active_participant(participant *p) {
    std::atomic<participant *> ap(p);

}
