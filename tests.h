/*
 * tests.h
 *
 *  Created on: Sep 9, 2021
 *      Author: CyberPower
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "production.h"
#include "AdjMat.h"
bool tests();

bool testReadFile();
bool testGotAdjacencyMatrix();
bool testMakeLList();
bool testEnqueue();
bool testRemoveFromList();
bool testPrintHistory(); // Im testing
bool testSavePayload(); //Im testing


#endif /* TESTS_H_ */
