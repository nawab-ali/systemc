/**
 * @file util.h
 * @brief This file implements common functions.
 * @author Nawab Ali
 */

#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

int random(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

#endif //UTIL_H