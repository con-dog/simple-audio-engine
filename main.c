#include "main.h"

/*
 * Takes in an array of Bytes in Big-Endian order and converts it to a single Hex
 * value in Little-Endian order
 */
DWord le_dword_hex_builder(Byte *arr, size_t len)
{
  DWord hex = 0;
  for (size_t i = 0; i < len; i++)
  {
    hex |= (arr[i] << BYTE * i);
  }
  return hex;
}

Word le_word_hex_builder(Byte *arr, size_t len)
{
  Word hex = 0;
  for (size_t i = 0; i < len; i++)
  {
    hex |= (arr[i] << BYTE * i);
  }
  return hex;
}

Byte sinusoidal_sample(DWord sample_no, Frequency note)
{
  return BYTE_WAVE_CENTER + BYTE_WAVE_CENTER * sin((2 * M_PI * sample_no * note) / SAMPLE_RATE_CD);
}

int main(void)
{
  WavHeader header;

  header.riff.file_type_bloc_id = le_dword_hex_builder((Byte[]){0x52, 0x49, 0x46, 0x46}, 4);
  header.riff.file_format_id = le_dword_hex_builder((Byte[]){0x57, 0x41, 0x56, 0x45}, 4);
  header.format.format_bloc_id = le_dword_hex_builder((Byte[]){0x66, 0x6D, 0x74, 0x20}, 4);
  header.format.bloc_size = le_dword_hex_builder((Byte[]){0x00, 0x00, 0x00, 0x10}, 4);
  header.format.audio_format = le_word_hex_builder((Byte[]){0x00, 0x01}, 2);
  header.format.nbr_channels = le_word_hex_builder((Byte[]){0x00, 0x02}, 2);
  header.format.frequency = le_dword_hex_builder((Byte[]){0x00, 0x00, 0xAC, 0x44}, 4);
  header.format.bits_per_sample = le_word_hex_builder((Byte[]){0x00, 0x08}, 2);
  header.format.byte_per_bloc = le_word_hex_builder((Byte[]){0x00, 0x02}, 2);
  header.format.byte_per_sec = le_dword_hex_builder((Byte[]){0x00, 0x02, 0xB1, 0x10}, 4);
  header.sample.data_bloc_id = le_dword_hex_builder((Byte[]){0x64, 0x61, 0x74, 0x61}, 4);

  Seconds t = 1;
  int num_samples = SAMPLE_RATE_CD * t * 2;
  Byte stereo_samples[num_samples];
  for (int i = 0; i < num_samples; i += 2)
  {
    DWord sample_num = i / 2;
    stereo_samples[i] = sinusoidal_sample(sample_num, C4);
    stereo_samples[i + 1] = sinusoidal_sample(sample_num, C4);
  }

  header.sample.data_size = num_samples;
  header.riff.file_size = sizeof(WavHeader) + num_samples - 8;
}