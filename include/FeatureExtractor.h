/*
 * BasicTenFeaturesExtractor, A simple PlatformIO Arduino library to extract ten features per x, y,
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


#ifndef BASICTENFEATURESEXTRACTOR_FEATUREEXTRACTOR_H
#define BASICTENFEATURESEXTRACTOR_FEATUREEXTRACTOR_H

#ifdef NATIVE_ENV
#include <cmath>
#else
#include <Arduino.h>
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

            float *calculateFeatures(float (*data)[3], int n) {
                auto *features = new float[3 * 10];
                for (int i = 0; i < 3; i++) {
                    // Extract the column data
                    float columnData[n];
                    for (int j = 0; j < n; j++) {
                        columnData[j] = data[j][i];
                    }

                    bubbleSort(columnData, n);
                    float sum = 0;
                    float sq_sum = 0;
                    float min_val = columnData[0];
                    float max_val = columnData[0];

                    for (int j = 0; j < n; j++) {
                        float val = columnData[j];
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
                    float median = columnData[n / 2];

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
