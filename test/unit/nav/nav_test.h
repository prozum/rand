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
#include "task.h"
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
CPPUNIT_TEST_SUITE_END();

    void initNav();
    nav_t NavStruct;
    rep_t RepStruct;
    fc_t FCStruct;
    ir_t IrTopStruct;
    ir_t IrBottomStruct;
    sonar_t SonarStruct;
    laser_t LaserStruct;

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
};
