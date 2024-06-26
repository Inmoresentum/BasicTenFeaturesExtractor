<h1 align="center">BasicTenFeatureExtractor</h1>

<h1 align="center">
    <div align="center">
        <a href="https://www.espressif.com">
            <img src="https://img.shields.io/badge/ESP32-E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white"  alt="whatever"/>
        </a>
        <a href="https://github.com/Inmoresentum/BasicTenFeaturesExtractor/actions/workflows/test_lib_native.yml">
            <img src="https://github.com/Inmoresentum/BasicTenFeaturesExtractor/actions/workflows/test_lib_native.yml/badge.svg"  alt="whatever"/>
        </a>
        <a href="https://www.arduino.cc/reference/en/libraries/esp8266-framework/">
            <img src="https://img.shields.io/badge/ESP32 Arduino Framework-00979D?style=for-the-badge&logo=Arduino&logoColor=white"  alt="whatever"/>
        </a>
    </div>
</h1>

A simple PlatformIO Arduino library to extract ten features per x, y,
and z axis of the collected segment of accelerometer or similar sensor data.

The features this library extracts are:

* *sum*,
* *median*,
* *mean*
* *length*,
* *standard deviation*,
* *variance*,
* *root-mean-square*,
* *maximum*,
* *absolute maximum*, and
* *minimum*.
