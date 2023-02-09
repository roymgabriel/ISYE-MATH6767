//
// Created by Roy Makkar Gabriel on 10/13/22.
//

#include "unit_test.h"
#include "DeltaHedgerWithInputData.h"

// unit tests to check implied vol calculation and delta calculation
void unit_test::check_iv() {
    DeltaHedgerWithInput DHWI("2011-07-05", "2011-07-29", "2011-09-17", 500);
    DHWI.get_IV();
    cout << "Successfully Ran IV tests!" << endl;
};

void unit_test::check_delta() {
    DeltaHedgerWithInput DHWI("2011-07-05", "2011-07-29", "2011-09-17", 500);
    DHWI.get_Delta();
    cout << "Successfully Ran Delta tests!" << endl;
};