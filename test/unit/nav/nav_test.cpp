#include "nav_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NavTest);

void NavTest::alignToGrid_bottomOfRoom_expectBottomEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2), yCoord = MAP_MIDDLE;
    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);

    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.x);
}

void NavTest::alignToGrid_centerOfRoom_expectCenterOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE;

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);

    const int assertX = MAP_WIDTH / 2, assertY = MAP_HEIGHT / 2;
    CPPUNIT_ASSERT_EQUAL(assertX, (int) pixel.x);
    CPPUNIT_ASSERT_EQUAL(assertY, (int) pixel.y);
}

void NavTest::alignToGrid_leftInRoom_expectLeftEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - (MAP_WIDTH * CENTIMETERS_PR_PIXEL / 2);

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.y);
}

void NavTest::alignToGrid_rightInRoom_expectRightEdgeOfMap() {
    const  uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_WIDTH * CENTIMETERS_PR_PIXEL / 2);

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int) pixel.y);
}

void NavTest::alignToGrid_topOfRoom_expectTopEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2), yCoord = MAP_MIDDLE;

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsBottom_expectWarningAndY0() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - ((MAP_WIDTH + 10) * CENTIMETERS_PR_PIXEL / 2);

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.y);
}

void NavTest::alignToGrid_outOfBoundsLeft_expectWarningAndX0() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_WIDTH + 10) * CENTIMETERS_PR_PIXEL / 2, yCoord = MAP_MIDDLE;

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsRight_expectWarningAndX64() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_PIXEL / 2, yCoord = MAP_HEIGHT;

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsTop_expectWarningAndY64() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_PIXEL / 2;

    pixel_coord_t pixel = align_to_pixel(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int) pixel.y);
}

