#ifndef BASICTENFEATURESEXTRACTOR_FEATUREEXTRACTOR_H
#define BASICTENFEATURESEXTRACTOR_FEATUREEXTRACTOR_H

#include <Arduino.h>
#ifndef N_FEATURES
#define N_FEATURES 30
#endif

namespace FeatureExtractor {
    namespace TimeDomain {
        class BasicFeature {
        public:
            void bubbleSort(float arr[], int n) {
                for (int i = 0; i < n - 1; i++) {
                    for (int j = 0; j < n - i - 1; j++) {
                        if (arr[j] > arr[j + 1]) {
                            float temp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = temp;
                        }
                    }
                }
            }

            float *calculateFeatures(float (*data)[N_FEATURES], int n) {
                auto *features = new float[N_FEATURES];
                for (int i = 0; i < 3; i++) {
                    bubbleSort(data[i], n);
                    float sum = 0;
                    float sq_sum = 0;
                    float min_val = data[0][i];
                    float max_val = data[0][i];

                    for (int j = 0; j < n; j++) {
                        float val = data[j][i];
                        sum += val;
                        sq_sum += val * val;
                        min_val = std::min(min_val, val);
                        max_val = std::max(max_val, val);
                    }

                    float mean = sum / (float) n;
                    float variance = sq_sum / (float) n - mean * mean;
                    float std_dev = std::sqrt(variance);
                    float rms = std::sqrt(sq_sum / (float) n);
                    float abs_max = std::max(std::abs(min_val), std::abs(max_val));
                    float median = data[n / 2][i];

                    features[i * 10 + 0] = sum;
                    features[i * 10 + 1] = median;
                    features[i * 10 + 2] = mean;
                    features[i * 10 + 3] = (float) n;
                    features[i * 10 + 4] = std_dev;
                    features[i * 10 + 5] = variance;
                    features[i * 10 + 6] = rms;
                    features[i * 10 + 7] = max_val;
                    features[i * 10 + 8] = abs_max;
                    features[i * 10 + 9] = min_val;
                }
                return features;
            }
        };
    }
}

#endif //BASICTENFEATURESEXTRACTOR_FEATUREEXTRACTOR_H
