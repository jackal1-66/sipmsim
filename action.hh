#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"

class action : public G4VUserActionInitialization
{
    public:
        action();
        ~action();

        virtual void Build() const;
};

#endif