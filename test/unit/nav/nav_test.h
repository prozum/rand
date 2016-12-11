#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

#include <stdlib.h>

extern "C" {
#include "nav/nav.h"
#include "map/map.h"
#include "../../../src/task.h"
}

class NavTest : public CppUnit::TestCase {
CPPUNIT_TEST_SUITE(NavTest);
    CPPUNIT_TEST(alignToGrid_centerOfRoom_expectCenterOfMap);
    CPPUNIT_TEST(alignToGrid_leftInRoom_expectLeftEdgeOfMap);
    CPPUNIT_TEST(alignToGrid_rightInRoom_expectRightEdgeOfMap);
    CPPUNIT_TEST(alignToGrid_topOfRoom_expectTopEdgeOfMap);
    CPPUNIT_TEST(alignToGrid_bottomOfRoom_expectBottomEdgeOfMap);
    CPPUNIT_TEST(alignToGrid_outOfBoundsLeft_expectWarningAndX0);
    CPPUNIT_TEST(alignToGrid_outOfBoundsRight_expectWarningAndX64);
    CPPUNIT_TEST(alignToGrid_outOfBoundsTop_expectWarningAndY64);
    CPPUNIT_TEST(alignToGrid_outOfBoundsBottom_expectWarningAndY0);

    CPPUNIT_TEST(fixRadAngle_0_expect0);
    CPPUNIT_TEST(fixRadAngle_9000_expectHalfPi);
    CPPUNIT_TEST(fixRadAngle_18000_expectPi);
    CPPUNIT_TEST(fixRadAngle_27000_expectOneAndAHalfPi);
    CPPUNIT_TEST(fixRadAngle_36000_expectWarningAndMinusOne);

    CPPUNIT_TEST(calculateXDistance_ang0Dist10_expect10);
    CPPUNIT_TEST(calculateYDistance_ang0Dist10_expect0);
    CPPUNIT_TEST(calculateXDistance_ang90Dist10_expect0);
    CPPUNIT_TEST(calculateYDistance_ang90Dist10_expect10);
    CPPUNIT_TEST(calculateXDistance_ang45Dist10_expect7dot07);
    CPPUNIT_TEST(calculateYDistance_ang45Dist10_expect7dot07);
    CPPUNIT_TEST(calculateXDistance_ang180Dist10_expectMinus10);
    CPPUNIT_TEST(calculateYDistance_ang180Dist10_expect0);
    CPPUNIT_TEST(calculateXDistance_ang270Dist10_expect0);
    CPPUNIT_TEST(calculateYDistance_ang270Dist10_expectMinus10);

    CPPUNIT_TEST(updateAngle_0_expect0);
    CPPUNIT_TEST(updateAngle_90_expect9000);
    CPPUNIT_TEST(updateAngle_180_expect18000);
    CPPUNIT_TEST(updateAngle_270_expect27000);
    CPPUNIT_TEST(updateAngle_360_expect0);
    CPPUNIT_TEST(updateAngle_minus90_expect27000);
    CPPUNIT_TEST(updateAngle_minus180_expect18000);
    CPPUNIT_TEST(updateAngle_minus270_expect9000);
CPPUNIT_TEST_SUITE_END();


public:
    void alignToGrid_centerOfRoom_expectCenterOfMap();
    void alignToGrid_leftInRoom_expectLeftEdgeOfMap();
    void alignToGrid_rightInRoom_expectRightEdgeOfMap();
    void alignToGrid_topOfRoom_expectTopEdgeOfMap();
    void alignToGrid_bottomOfRoom_expectBottomEdgeOfMap();
    void alignToGrid_outOfBoundsLeft_expectWarningAndX0();
    void alignToGrid_outOfBoundsRight_expectWarningAndX64();
    void alignToGrid_outOfBoundsTop_expectWarningAndY64();
    void alignToGrid_outOfBoundsBottom_expectWarningAndY0();

    void fixRadAngle_0_expect0();
    void fixRadAngle_9000_expectHalfPi();
    void fixRadAngle_18000_expectPi();
    void fixRadAngle_27000_expectOneAndAHalfPi();
    void fixRadAngle_36000_expectWarningAndMinusOne();

    void calculateXDistance_ang0Dist10_expect10();
    void calculateYDistance_ang0Dist10_expect0();
    void calculateXDistance_ang90Dist10_expect0();
    void calculateYDistance_ang90Dist10_expect10();
    void calculateXDistance_ang45Dist10_expect7dot07();
    void calculateYDistance_ang45Dist10_expect7dot07();
    void calculateXDistance_ang180Dist10_expectMinus10();
    void calculateYDistance_ang180Dist10_expect0();
    void calculateXDistance_ang270Dist10_expect0();
    void calculateYDistance_ang270Dist10_expectMinus10();

    void updateAngle_0_expect0();
    void updateAngle_90_expect9000();
    void updateAngle_180_expect18000();
    void updateAngle_270_expect27000();
    void updateAngle_360_expect0();
    void updateAngle_minus90_expect27000();
    void updateAngle_minus180_expect18000();
    void updateAngle_minus270_expect9000();
};
