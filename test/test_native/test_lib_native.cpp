/*
 * BasicTenFeatureExtractor, A simple PlatformIO Arduino library to extract ten features per x, y,
 * and z axis of the collected accelerometer or similar sensor data from a window
 * Copyright (c) 2024 Inmoresentum and contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "FeatureExtractor.h"
#include "unity.h"

float sampleOneWindow[9][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
};

float expectedFeatures[30] = {
        9, 1, 1, 9, 0, 0, 1, 1, 1, 1,
        18, 2, 2, 9, 0, 0, 2, 2, 2,2,
        27, 3, 3, 9, 0, 0, 3, 3, 3, 3
};


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_calculate_features() {
    FeatureExtractor::TimeDomain::BasicFeature extractor;
    float *features = extractor.calculateFeatures(sampleOneWindow, 9);

    for (int i = 0; i < 30; i++) {
        TEST_ASSERT_FLOAT_WITHIN(0.0001, expectedFeatures[i], features[i]);
    }

    delete[] features;
}

int runUnityTests(void) {
    UNITY_BEGIN();
//    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_calculate_features);
    return UNITY_END();
}

int main(int argc, char **argv) {
    runUnityTests();
    return 0;
}