#include "nav_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NavTest);

void NavTest::alignToGrid_bottomOfRoom_expectBottomEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2), yCoord = MAP_MIDDLE;
    map_coord_t pixel = align_to_map(xCoord, yCoord);

    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.x);
}

void NavTest::alignToGrid_centerOfRoom_expectCenterOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);

    const int assertX = MAP_WIDTH / 2, assertY = MAP_HEIGHT / 2;
    CPPUNIT_ASSERT_EQUAL(assertX, (int) pixel.x);
    CPPUNIT_ASSERT_EQUAL(assertY, (int) pixel.y);
}

void NavTest::alignToGrid_leftInRoom_expectLeftEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - (MAP_WIDTH * CENTIMETERS_PR_PIXEL / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.y);
}

void NavTest::alignToGrid_rightInRoom_expectRightEdgeOfMap() {
    const  uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_WIDTH * CENTIMETERS_PR_PIXEL / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int) pixel.y);
}

void NavTest::alignToGrid_topOfRoom_expectTopEdgeOfMap() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT * CENTIMETERS_PR_PIXEL / 2), yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsBottom_expectWarningAndY0() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE - ((MAP_WIDTH + 10) * CENTIMETERS_PR_PIXEL / 2);

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.y);
}

void NavTest::alignToGrid_outOfBoundsLeft_expectWarningAndX0() {
    const uint16_t xCoord = MAP_MIDDLE - (MAP_WIDTH + 10) * CENTIMETERS_PR_PIXEL / 2, yCoord = MAP_MIDDLE;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(0, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsRight_expectWarningAndX64() {
    const uint16_t xCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_PIXEL / 2, yCoord = MAP_HEIGHT;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_WIDTH, (int) pixel.x);
}

void NavTest::alignToGrid_outOfBoundsTop_expectWarningAndY64() {
    const uint16_t xCoord = MAP_MIDDLE, yCoord = MAP_MIDDLE + (MAP_HEIGHT + 10) * CENTIMETERS_PR_PIXEL / 2;

    map_coord_t pixel = align_to_map(xCoord, yCoord);
    CPPUNIT_ASSERT_EQUAL(MAP_HEIGHT, (int) pixel.y);
}

void NavTest::fixRadAngle_0_expect0() {
    fix16_t result = fix_rad_angle(0);
    fix16_t expected = fix16_from_int(0);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::fixRadAngle_9000_expectHalfPi() {
    fix16_t result = fix_rad_angle(9000);
    fix16_t expected = fix16_div(fix16_pi, fix16_from_int(2));

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::fixRadAngle_18000_expectPi() {
    fix16_t result = fix_rad_angle(18000);
    fix16_t  expected = fix16_pi;

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::fixRadAngle_27000_expectOneAndAHalfPi() {
    fix16_t result = fix_rad_angle(27000);
    fix16_t expected = fix16_mul(fix16_pi, fix16_from_float(1.5f));

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::fixRadAngle_36000_expectWarningAndMinusOne() {
    fix16_t result = fix_rad_angle(36000);
    fix16_t expected = fix16_from_float(-1.0f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang0Dist10_expect10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(0, distance);
    fix16_t expected = fix16_from_int(10);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang0Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_y_distance(0, distance);
    fix16_t expected = fix16_from_int(0);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang90Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(9000, distance);
    fix16_t expected = fix16_from_int(0);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang90Dist10_expect10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_y_distance(9000, distance);
    fix16_t expected = fix16_from_int(10);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang45Dist10_expect7dot07() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(4500, distance);
    fix16_t expected = fix16_from_float(7.07106f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang45Dist10_expect7dot07() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(4500, distance);
    fix16_t expected = fix16_from_float(7.07106f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang180Dist10_expectMinus10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(18000, distance);
    fix16_t expected = fix16_from_float(-10.0f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang180Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_y_distance(18000, distance);
    fix16_t expected = fix16_from_float(0.0f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateXDistance_ang270Dist10_expect0() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_x_distance(27000, distance);
    fix16_t expected = fix16_from_float(0.0f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::calculateYDistance_ang270Dist10_expectMinus10() {
    fix16_t distance = fix16_from_int(10);
    fix16_t result = calculate_y_distance(27000, distance);
    fix16_t expected = fix16_from_float(-10.0f);

    std::string msg = "Converted to floats: expected: " + std::to_string(fix16_to_float(expected))
                      + ", result: " + std::to_string(fix16_to_float(result));
    CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, result);
}

void NavTest::updateAngle_0_expect0() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(0);
    uint16_t expected = 0;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_90_expect9000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(90);
    uint16_t expected = 9000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_180_expect18000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(180);
    uint16_t expected = 18000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_270_expect27000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(270);
    uint16_t expected = 27000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_360_expect0() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(360);
    uint16_t expected = 0;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_minus90_expect27000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(-90);
    uint16_t expected = 27000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_minus180_expect18000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(-180);
    uint16_t expected = 18000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}

void NavTest::updateAngle_minus270_expect9000() {
    nav_t *nav = (nav_t*) malloc(sizeof(nav_t));
    init_nav(nav);
    fix16_t rotation = fix16_from_int(-270);
    uint16_t expected = 9000;

    update_angle(nav, rotation);
    uint16_t result = nav->angle;

    CPPUNIT_ASSERT_EQUAL(expected, result);
    free(nav);
}



