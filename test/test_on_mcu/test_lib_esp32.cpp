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

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_calculate_features);
    UNITY_END();
}

void loop() {
    // nothing needed here
}
