#ifndef SAMPLING_8BIT_H
#define SAMPLING_8BIT_H

#include <math.h>

#include "../../config/constants.h"
#include "../../lib/audio-definitions.h"
#include "../../lib/binary-definitions.h"
#include "../../lib/binary-constants.h"

/*
 * Returns the 8-bit amplitude of the wave at the given sample number + frequency using sin approximation
 */
extern Byte sinusoidal_sample_8bit(DWord sample_no, Frequency note);

/*
 * Returns the 8-bit amplitude of the wave at the given sample number + frequency using square waves
 */
extern Byte square_sample_8bit(DWord sample_no, Frequency note);


#endif