#ifndef RUN_H
#define RUN_H
#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

class runaction : public G4UserRunAction
{
    public:
        runaction();
        ~runaction();
        
        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
};

#endif