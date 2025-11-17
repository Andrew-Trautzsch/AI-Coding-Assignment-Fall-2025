#include "hmm.hpp"

int main()
{
    // given info

    /*
    NEED TO FIX CODE
    transistion matrix and emission matrix should be generated, not as it currently is
    
    */

    HMM model;

    for(int i=0; i<goal.size(); i++)
    {
        model.calculateStep(i);
    }
    
    model.backTrack();
}