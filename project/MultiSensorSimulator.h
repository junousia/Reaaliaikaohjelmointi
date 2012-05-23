// Function starts a multi sensor simulator
// After calling this function with a descriptor array of 20
// descriptor elements, the sensor values can read from the
// descripptors in the array. 
// The parameter steps specifies how many values sensors send
// before the cause an end of file situation
// Function returns the number of opened sensors. It is always 20.

int StartSimulator(int fd_array[], int steps);

// When you read from the descriptors opened with the fúnction 
// StartSimulator, you get structures defined below. 
// This also meanns that sensors create and send these kind
// of data packages 

#include <time.h>
typedef struct {
     struct timespec moment;
     int value;
} Tmeas;  
