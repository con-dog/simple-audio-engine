#include "./sampling.h"

Byte sinusoidal_sample_8bit(DWord sample_no, Frequency note)
{
  double sample = (BYTE_MIDPOINT - 1) * sin((2 * M_PI * sample_no * note) / SAMPLE_RATE);
  double shifted_sample = BYTE_MIDPOINT + sample;
  return shifted_sample < 0
             ? 0
         : shifted_sample > UINT8_MAX
             ? UINT8_MAX
             : shifted_sample;
}

Byte square_sample_8bit(DWord sample_no, Frequency note)
{
  double sample = sinusoidal_sample_8bit(sample_no, note);
  return sample >= BYTE_MIDPOINT
             ? UINT8_MAX
             : 0;
}
