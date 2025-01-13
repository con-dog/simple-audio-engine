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

int main(void)
{
  Byte file_type_bloc_id[] = {0x52, 0x49, 0x46, 0x46};

  MasterRIFFChunk riff_chunk;
  riff_chunk.file_type_bloc_id = le_dword_hex_builder((Byte[]){0x52, 0x49, 0x46, 0x46}, 4);
  riff_chunk.file_format_id = le_dword_hex_builder((Byte[]){0x66, 0x6D, 0x74, 0x20}, 4);

  WavDataFormatChunk data_format_chunk;
  data_format_chunk.format_bloc_id = le_dword_hex_builder((Byte[]){0x66, 0x6D, 0x74, 0x20}, 4);
  data_format_chunk.bloc_size = le_dword_hex_builder((Byte[]){0x00, 0x00, 0x00, 0x10}, 4);
  data_format_chunk.audio_format = le_word_hex_builder((Byte[]){0x00, 0x01}, 2);
  data_format_chunk.nbr_channels = le_word_hex_builder((Byte[]){0x00, 0x02}, 2);
  data_format_chunk.frequency = le_dword_hex_builder((Byte[]){0x00, 0x00, 0xAC, 0x44}, 4);
  data_format_chunk.bits_per_sample = le_word_hex_builder((Byte[]){0x00, 0x10}, 2);
  data_format_chunk.byte_per_bloc = le_word_hex_builder((Byte[]){0x00, 0x04}, 2);
  data_format_chunk.byte_per_sec = le_dword_hex_builder((Byte[]){0x00, 0x02, 0xB1, 0x10}, 4);

  SampledDataChunk sample_data_chunk;
  sample_data_chunk.data_bloc_id = le_dword_hex_builder((Byte[]){0x64, 0x61, 0x74, 0x61}, 4);

  SimpleNote note = {
      .duration = 100,
      .freq = C4,
  };
}