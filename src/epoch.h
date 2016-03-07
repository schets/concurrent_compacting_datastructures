#pragma once
#include "participants.h"
// Since this doesn't scan stacks/registers, there must be a way to determine
// whether readers are currently active or not

struct Guard {
    participant *p;
    Guard();
    ~Guard();
};

inline Guard::Guard(): p(get_current_participant()) {
    p->enter();
}

inline Guard::~Guard() {
    p->exit();
}
