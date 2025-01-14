#include "main.h"

Byte sinusoidal_sample_8bit(DWord sample_no, Frequency note)
{
  double sample = (BYTE_MIDPOINT - 1) * sin((2 * M_PI * sample_no * note) / SAMPLE_RATE);
  double final_sample = BYTE_MIDPOINT + sample;
  return final_sample < 0 ? 0 : (final_sample > 255 ? 255 : final_sample);
}

int main(void)
{
  WavHeader header = {0};

  /* ----------------
   * Header init
   * --------------*/
  // RIFF header
  header.riff.file_type_bloc_id = *(DWord *)"RIFF";
  header.riff.file_format_id = *(DWord *)"WAVE";
  // Format chunk
  header.format.format_bloc_id = *(DWord *)"fmt ";
  header.format.bloc_size = 16;
  header.format.audio_format = 1;
  header.format.nbr_channels = 2;
  header.format.frequency = SAMPLE_RATE;
  header.format.bits_per_sample = 8;
  header.format.byte_per_bloc = (header.format.nbr_channels * header.format.bits_per_sample) / 8;
  header.format.byte_per_sec = header.format.frequency * header.format.byte_per_bloc;
  // Data chunk
  header.sample.data_bloc_id = *(DWord *)"data";

  /* ----------------
   * Calculate samples
   * --------------*/
  Seconds t = 5;
  int num_samples = SAMPLE_RATE * t * header.format.nbr_channels;
  Byte *stereo_samples = malloc(num_samples);
  if (!stereo_samples)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < num_samples; i += 2)
  {
    int sample_num = i / 2;
    stereo_samples[i] = sinusoidal_sample_8bit(sample_num, C4);
    stereo_samples[i + 1] = sinusoidal_sample_8bit(sample_num, E4);
  }

  /* ----------------
   * Update file size
   * --------------*/

  // Set sizes
  header.sample.data_size = num_samples;
  header.riff.file_size = sizeof(WavHeader) - 8 + num_samples;

  /* ----------------
   * Write to file
   * --------------*/
  FILE *fp = fopen("out.wav", "wb");
  if (fp == NULL)
  {
    fprintf(stderr, "Can't open out.wav\n");
    free(stereo_samples);
    return EXIT_FAILURE;
  }

  fwrite(&header, sizeof(WavHeader), 1, fp);
  fwrite(stereo_samples, sizeof(Byte), num_samples, fp);

  free(stereo_samples);
  fclose(fp);

  return EXIT_SUCCESS;
}