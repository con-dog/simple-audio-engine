#include "init.h"

/* ----------------
 * Header init
 * --------------*/
WavHeader *wav_header_setup(void)
{
  WavHeader *header = malloc(sizeof(WavHeader));
  if (header == NULL)
  {
    fprintf(stderr, "WAV header init failed\n");
    exit(EXIT_FAILURE);
  }
  // RIFF header
  header->riff.file_type_bloc_id = *(DWord *)"RIFF";
  header->riff.file_format_id = *(DWord *)"WAVE";
  // Format chunk
  header->format.format_bloc_id = *(DWord *)"fmt ";
  header->format.bloc_size = 16;
  header->format.audio_format = 1;
  header->format.nbr_channels = 2;
  header->format.frequency = SAMPLE_RATE;
  header->format.bits_per_sample = 8;
  header->format.byte_per_bloc = (header->format.nbr_channels * header->format.bits_per_sample) / 8;
  header->format.byte_per_sec = header->format.frequency * header->format.byte_per_bloc;
  // Data chunk
  header->sample.data_bloc_id = *(DWord *)"data";

  return header;
}
