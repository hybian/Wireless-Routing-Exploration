#include "toolbox.h"
#include "math.h"

double get_distance(int rssi, int txPower) {
    return pow(10.0, ((double) txPower - rssi) / (10 * 2));
}