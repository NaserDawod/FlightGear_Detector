cmake_minimum_required(VERSION 3.21)
project(FlightGear_Detector1)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 14)

add_executable(FlightGear_Detector1 main.cpp anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h timeseries.h timeseries.cpp SimpleAnomalyDetector.h SimpleAnomalyDetector.cpp HybridAnomalyDetector.h HybridAnomalyDetector.cpp minCircle.cpp minCircle.h commands.h CLI.h CLI.cpp Server.cpp Server.h)
