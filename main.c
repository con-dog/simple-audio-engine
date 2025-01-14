#include "main.h"

int main(void)
{
  WavHeader *header = wav_header_setup();

  /* ----------------
   * Calculate samples
   * --------------*/
  Seconds t = 5;
  int num_samples = SAMPLE_RATE * t * header->format.nbr_channels;
  Byte *stereo_samples = malloc(num_samples);
  if (!stereo_samples)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < num_samples; i += 2)
  {
    int sample_num = i / 2;
    stereo_samples[i] = 0.7 * sinusoidal_sample_8bit(sample_num, C3) + 0.3 * square_sample_8bit(sample_num, CSH2);
    stereo_samples[i + 1] = sinusoidal_sample_8bit(sample_num, D3);
  }

  Byte *stereo_square_samples = malloc(num_samples);
  for (int i = 0; i < num_samples; i += 2)
  {
    int sample_num = i / 2;
    stereo_square_samples[i] = square_sample_8bit(sample_num, CSH2);
    stereo_square_samples[i + 1] = square_sample_8bit(sample_num, D4);
  }

  /* ----------------
   * Update file size
   * --------------*/

  // Set sizes
  header->sample.data_size = num_samples;
  header->riff.file_size = sizeof(WavHeader) - 8 + num_samples;

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

  FILE *fp2 = fopen("out-2.wav", "wb");

  fwrite(header, sizeof(WavHeader), 1, fp);
  fwrite(stereo_samples, sizeof(Byte), num_samples, fp);

  fwrite(header, sizeof(WavHeader), 1, fp2);
  fwrite(stereo_square_samples, sizeof(Byte), num_samples, fp2);

  free(header);
  free(stereo_samples);
  free(stereo_square_samples);
  fclose(fp);
  fclose(fp2);

  return EXIT_SUCCESS;
}