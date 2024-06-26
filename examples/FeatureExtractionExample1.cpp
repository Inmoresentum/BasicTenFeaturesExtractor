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


#include <Arduino.h>
#include "FeatureExtractor.h"

// Here define the length of the window or hardcode
#define SLIDING_WINDOW_LENGTH 101
// Here the row number should be 3 (tri axis accelerometer or similar sensor)
#define ROW_NUMBER 3

FeatureExtractor::TimeDomain::BasicFeature basicFeatureExtractor;

float sampleOneWindow[SLIDING_WINDOW_LENGTH][ROW_NUMBER] = {
        {-0.7236328125,   0.545654296875,  0.18212890625},
        {-0.7236328125,   0.545654296875,  0.18212890625},
        {-0.770751953125, 0.546875,        0.1796875},
        {-0.770751953125, 0.546875,        0.1796875},
        {-0.770751953125, 0.546875,        0.1796875},
        {-0.770751953125, 0.546875,        0.1796875},
        {-0.770751953125, 0.546875,        0.1796875},
        {-0.756591796875, 0.54443359375,   0.16015625},
        {-0.756591796875, 0.54443359375,   0.16015625},
        {-0.723876953125, 0.552490234375,  0.158203125},
        {-0.737060546875, 0.643798828125,  0.1728515625},
        {-0.746337890625, 0.5576171875,    0.25048828125},
        {-0.739013671875, 0.589599609375,  0.17431640625},
        {-0.819580078125, 0.633544921875,  0.170166015625},
        {-0.744140625,    0.53271484375,   0.176513671875},
        {-0.7744140625,   0.578125,        0.17919921875},
        {-0.77783203125,  0.5888671875,    0.170654296875},
        {-0.730712890625, 0.535888671875,  0.167236328125},
        {-0.77978515625,  0.544677734375,  0.258544921875},
        {-0.779296875,    0.635498046875,  0.228271484375},
        {-0.775390625,    0.553955078125,  0.323974609375},
        {-0.78076171875,  0.642333984375,  0.31298828125},
        {-0.763427734375, 0.66064453125,   0.404541015625},
        {-0.8134765625,   0.673583984375,  0.450439453125},
        {-0.77685546875,  0.802490234375,  0.578125},
        {-0.727294921875, 0.901123046875,  0.607177734375},
        {-0.728515625,    0.888671875,     0.75439453125},
        {-0.788818359375, 0.974853515625,  0.830322265625},
        {-0.778076171875, 1.0302734375,    0.693359375},
        {-0.674560546875, 0.96240234375,   0.67431640625},
        {-0.647216796875, 0.76611328125,   0.53564453125},
        {-0.513916015625, 0.612548828125,  0.759521484375},
        {-0.38720703125,  0.461669921875,  0.77978515625},
        {-0.222412109375, 0.5166015625,    0.802001953125},
        {-0.14697265625,  0.345703125,     0.823486328125},
        {0.00146484375,   0.272216796875,  0.787841796875},
        {0.113037109375,  0.30517578125,   0.841064453125},
        {0.234619140625,  0.06103515625,   0.84033203125},
        {0.35986328125,   0.211181640625,  0.892578125},
        {0.464599609375,  0.072998046875,  0.84814453125},
        {0.513427734375,  0.128173828125,  0.8388671875},
        {0.572021484375,  0.0439453125,    0.819580078125},
        {0.597412109375,  0.076904296875,  0.65283203125},
        {0.597412109375,  0.076904296875,  0.65283203125},
        {0.730224609375,  0.211181640625,  0.586669921875},
        {0.730224609375,  0.211181640625,  0.586669921875},
        {0.790771484375,  0.12841796875,   0.571533203125},
        {0.83740234375,   0.015869140625,  0.576416015625},
        {0.83154296875,   -0.19677734375,  0.647705078125},
        {0.719970703125,  -0.237060546875, 0.609619140625},
        {0.67041015625,   -0.4111328125,   0.6484375},
        {0.607666015625,  -0.69189453125,  0.68994140625},
        {0.6259765625,    -0.6025390625,   0.69140625},
        {0.58447265625,   -0.60595703125,  0.56982421875},
        {0.644775390625,  -0.835693359375, 0.505859375},
        {0.54931640625,   -0.6142578125,   0.35693359375},
        {0.64794921875,   -0.8955078125,   0.40283203125},
        {0.56982421875,   -1.0234375,      0.450927734375},
        {0.6259765625,    -0.612060546875, 0.50830078125},
        {0.558349609375,  -0.856689453125, 0.603271484375},
        {0.719970703125,  -0.19140625,     0.636962890625},
};

void setup() {
    Serial.begin(115200);
    Serial.println("Starting MCU");
    delay(500);
}

void loop() {
    // pass the window and window length
    auto extractedFeature = basicFeatureExtractor.calculateFeatures(sampleOneWindow, SLIDING_WINDOW_LENGTH);
    // Now you can feed the extracted features to model(s)
    for (int i = 0; i < 30; i++) {
        Serial.println(extractedFeature[i]);
    }

    Serial.println("Done printing features");
    delay(2000);
}