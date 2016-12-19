#include "NavTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NavTest);

void NavTest::initNav() {
    init_nav(&NavStruct);

    init_rep(&RepStruct, &FCStruct, &LaserStruct, &SonarStruct, &IrTopStruct, &IrBottomStruct);
}

void NavTest::alignToGrid_bottomOfRoom_expectBottomEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_HEIGHT * CENTIMETERS_PR_FIELD / 2), yCoord = MAP_MIDDLE;
    map_coord_t pixel = align_to_map(xCoord, yCoord);

    CPPUNIT_ASSERT_EQUAL(0, (int)pixel.x);
}

void NavTest::alignToGrid_centerOfRoom_expectCenterOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);

    const int assertX = MAP_WIDTH / 2, assertY = MAP_HEIGHT / 2;
    CPPUNIT_ASSERT_EQUAL(assertX, (int)pixel.x);
    CPPUNIT_ASSERT_EQUAL(assertY, (int)pixel.y);
}

void NavTest::alignToGrid_leftInRoom_expectLeftEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - (MAP_WIDTH * CENTIMETERS_PR_FIELD / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int)pixel.y);
}

void NavTest::alignToGrid_rightInRoom_expectRightEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_WIDTH * CENTIMETERS_PR_FIELD / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int)pixel.y);
}

void NavTest::alignToGrid_topOfRoom_expectTopEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT * CENTIMETERS_PR_FIELD / 2), yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int)pixel.x);
}

void NavTest::alignToGrid_outOfBoundsBottom_expectWarningAndY0() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - ((MAP_WIDTH + 10) * CENTIMETERS_PR_FIELD / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int)pixel.y);
}

void NavTest::alignToGrid_outOfBoundsLeft_expectWarningAndX0() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_WIDTH + 10) * CENTIMETERS_PR_FIELD / 2, yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int)pixel.x);
}

void NavTest::alignToGrid_outOfBoundsRight_expectWarningAndX64() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_FIELD / 2, yCoord = MAP_HEIGHT;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int)pixel.x);
}

void NavTest::alignToGrid_outOfBoundsTop_expectWarningAndY64() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_FIELD / 2;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int)pixel.y);
}

void NavTest::calculateXDistance_ang0Dist10_expect10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(0, distance);
    fix16_t expected = fix16_from_int(10);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang0Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_y_dist(0, distance);
    fix16_t expected = fix16_from_int(0);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang90Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(9000, distance);
    fix16_t expected = fix16_from_int(0);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateYDistance_ang90Dist10_expect10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_y_dist(9000, distance);
    fix16_t expected = fix16_from_int(10);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateXDistance_ang45Dist10_expect7dot07() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(4500, distance);
    fix16_t expected = fix16_from_float(7.07106f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateYDistance_ang45Dist10_expect7dot07() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(4500, distance);
    fix16_t expected = fix16_from_float(7.07106f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateXDistance_ang180Dist10_expectMinus10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(18000, distance);
    fix16_t expected = fix16_from_float(-10.0f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateYDistance_ang180Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_y_dist(18000, distance);
    fix16_t expected = fix16_from_float(0.0f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateXDistance_ang270Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_x_dist(27000, distance);
    fix16_t expected = fix16_from_float(0.0f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}

void NavTest::calculateYDistance_ang270Dist10_expectMinus10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calc_y_dist(27000, distance);
    fix16_t expected = fix16_from_float(-10.0f);

    float conv_result = fix16_to_float(result);
    float conv_expected = fix16_to_float(expected);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected)) + ", result: " +
                      std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, (int)(conv_expected * 10), (int)(conv_result * 10));
}
