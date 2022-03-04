#include<math.h>
#include <stdexcept>
#include "anomaly_detection_util.h"

/**
 * Ex1: this assignment is about a Anomaly Detector.
 *
 * @authors: Naser Dawod
 *           Hiba Shahbari
 * */

/**
 * average - given a array x calculate the average of the the values given in the vector.
 * @param x - array of x points.
 * @param size - the length of the array.*/
float average(float* x, int size) {
    if (size == 0) {
        /* if the size is 0 then we cant divide by 0 */
        throw std::overflow_error("Divide by zero exception");
    }
    float sum = 0;
    for(int i = 0; i < size; i++){
        sum += x[i];
    }
    return sum/(float)size;
}

/** var - returns the variance of X and Y.
 * @param x - array of x points.
 * @param size - the length of the vector.
 * */
float var(float* x, int size){
    if (size == 0) {
        /* if the size is 0 then we cant divide by 0 */
        throw std::overflow_error("Divide by zero exception");
    }
    float sum_pow = 0;
    for(int i =0; i < size; i++){
        /* the sum of all the values powered by 2 */
        sum_pow += pow(x[i], (float )2);
    }
    float temp = sum_pow/ (float )size;
    /* the variance of X */
    return temp - pow(average(x, size), (float)2);
}

/** cov - returns the covariance of X and Y.
 * @param x - array of x points.
 * @param y - array of y points.
 * @param size - the amount of values (length).*/
float cov(float* x, float* y, int size){
    float Ex = average(x, size);
    float Ey = average(y, size);
    /* create a new array to save the values */
    float x_new[size],y_new[size];
    for (int i = 0; i < size ; i++){
        x_new[i] = x[i] - Ex;
        y_new[i] = y[i] - Ey;
    }
    float * z;
    z = new float[size];
    for (int i = 0; i < size ; i++){
        z[i] = x_new[i] * y_new[i];
    }
    /* the covariance of X and Y */
    return average(z, size);
}


/**
 * pearson function - returns the Pearson correlation coefficient of X and Y
 * @param x - array of x's points
 * @param y - array of y's points
 * @param size - the length of the attay
 * @return - the Pearson correlation coefficient of X and Y
 */
float pearson(float* x, float*y, int size){
    if (var(x, size) * var(y, size) == 0) {
        throw std::overflow_error("Divide by zero exception");
    }
    return cov(x, y, size)/sqrt(var(x, size) * var(y, size));
}

/**
 * linear_reg function - performs a linear regression and returns the line equation
 * @param points - array of points
 * @param size - the length of the attay
 * @return - line equation
 */
Line linear_reg(Point** points,int size){
    float *x, *y;
    x = new float[size]; // array of x's points
    y = new float[size]; // array of y's points
    for (int i = 0; i < size; i++){
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    /*calculate 'a' for the line equation */
    float a = cov(x,y,size)/var(x,size);

    /*calculate 'b' for the line equation */
    float b = average(y,size) - (a * average(x,size));
    Line l(a, b);
    delete x; //remove x from memory
    delete y; //remove y from memory
    return l;
}

/**
 * dev function : returns the deviation between point p and the line
 * @param p - point
 * @param l - line
 * @return - the deviation between point p and the line
 */
float dev(Point p,Line l){
    float s = l.f(p.x) - p.y;
    /* if the deviation is negative */
    if (s < 0) {
        return -1 * s;
    }
    return s;
}

/**
 * dev function - returns the deviation between point p and the line equation of the points
 * @param p - point
 * @param points - array of points
 * @param size - The length of the array
 * @return - deviation between point p and the line equation of the points
 */
float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}





