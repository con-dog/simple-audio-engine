#ifndef WAV_INIT_H
#define WAV_INIT_H

#include <stdio.h>
#include <string.h>

#include "./definitions.h"
#include "../binary-definitions.h"
#include "../../config/constants.h"

extern WavHeader *wav_header_setup(void);

#endif