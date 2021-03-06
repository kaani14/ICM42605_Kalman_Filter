# ICM42605_Kalman_Filter

# Description

The project interfaces ICM-42605 with STM32G473CET6. To fuse the data from the gyroscope and the accelerometer, the Kalman filter has been implemented.

# Connections

**STM32G473CET6**  | **ICM-42605**
------------- | -------------
PB8  | SCL
PB9  | SDA
GND  | ADO

# Includes

 * **ICM42605.h:** Configuring ICM42605, reading accelerometer and gyroscope data, computing orientation from the accelerometer and angular velocity from the gyroscope.
 
 * **Kalman.h:** Kamlan Filter implementation, computation of a running variance

 * **Matrix_math.h:** Operator overloading for operations in Kalman.cpp.
 
 # Kalman Filter Parameters
 
* Process noise covariance matrix (Q)= {{0.005, 0}, {0, 0.005}};

* State transition matrix (A) = {{1, 0}, {0, 1}};

* Control input matrix, time constant (B) = {{0.004, 0}, {0, 0.004}};

* Initial value (x_e) = {{10, 0}, {0, 10}};

* State error variance (p_e) = {{0.10, 0}, {0, 0.10}};

* Measurement Matrix(H) = {{1, 0}, {0, 1}};

* Measurement noise matrix (R) = {{Running variance of the last 100 values of pitch, 0},{0, Running variance of the last 100 values of Roll}}

# Results

**Noise Evaluation of Roll:** The PCB was shaken up and down rapidly and was hit on a surface.

* Standard deviation of accelerometer when computing roll: 5.02°

* Standard deviation of accelerometer when computing roll: 3.05° 

**Noise Evaluation of Roll:**

* Standard deviation of accelerometer when computing pitch: 5.29°

* Standard deviation of accelerometer when computing pitch: 3.52°

# Tuning Kalman Filter


* Measurement noise matrix: The matrix is composed of running variance of the last 100 values of pitch and roll. The number of values can be changed in main.cpp

* Process noise covariance matrix: Decreasing the elements of this matrix, results in better noise filtering, however it slows down the response.
