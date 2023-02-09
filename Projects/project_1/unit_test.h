//
// Created by Roy Makkar Gabriel on 10/13/22.
//

#ifndef unit_test_h
#define unit_test_h

#include "Option.h"
#include "DeltaHedgerWithInputData.h"
#include <vector>

class unit_test {
public:
    // unit tests to check implied vol calculation and delta calculation
    void check_iv();
    void check_delta();
};


#endif //unit_test_h
