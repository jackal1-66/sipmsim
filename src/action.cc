#include "action.hh"

action::action() {
    // empty
}

action::~action() {
    // empty
}

void action::Build() const {
    primarygen* gen = new primarygen();
    SetUserAction(gen);
    runaction* run = new runaction();
    SetUserAction(run);
}