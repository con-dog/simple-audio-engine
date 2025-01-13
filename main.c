#include "main.h"

// Write WAV file headers

// Make a simple note
// Play note

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

int main(void)
{
  Byte file_type_bloc_id[] = {0x52, 0x49, 0x46, 0x46};

  MasterRIFFChunk master_riff_chunk;
  master_riff_chunk.file_type_bloc_id = le_dword_hex_builder((Byte[]){0x52, 0x49, 0x46, 0x46}, 4);
  master_riff_chunk.file_format_id = le_dword_hex_builder((Byte[]){0x66, 0x6D, 0x74, 0x20}, 4);

  // master_riff_chunk.file_size // TODO! Do later
}