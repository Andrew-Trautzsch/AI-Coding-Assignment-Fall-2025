#include "hmm.hpp"

int main()
{
    // given info

    HMM model;

    for(int i=0; i<goal.size(); i++)
    {
        model.calculateStep(i);
    }
    
    model.backTrack();
}