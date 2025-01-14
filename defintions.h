#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t DWord;
typedef uint64_t QWord;

typedef double Frequency;
typedef float Seconds;

#pragma pack(push, 1)
typedef struct MasterRIFFChunk
{
  DWord file_type_bloc_id; // Identifier « RIFF »
  DWord file_size; // Overall file size minus 8 bytes
  DWord file_format_id; // Format = « WAVE »
} MasterRIFFChunk;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct WavDataFormatChunk {
  DWord format_bloc_id; // Identifier « fmt␣ »
  DWord bloc_size; // Chunk size minus 8 bytes
  Word audio_format; // Audio format (1: PCM integer, 3: IEEE 754 float)
  Word nbr_channels; // Number of channels
  DWord frequency; // Sample rate (Hz)
  DWord byte_per_sec; // Number of bytes to read per second (Frequency * BytePerBloc)
  Word byte_per_bloc; // Number of bytes per block (NbrChannels * BitsPerSample / 8)
  Word bits_per_sample; // Number of bits per sample
} WavDataFormatChunk;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SampledDataChunk {
  DWord data_bloc_id; // Identifier « data »
  DWord data_size; // SampledData size
  // SampledData
} SampledDataChunk;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct WavHeader
{
  MasterRIFFChunk riff;
  WavDataFormatChunk format;
  SampledDataChunk sample;
} WavHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SimpleNote {
  Seconds   duration;
  Frequency freq;
} SimpleNote;
#pragma pack(pop)


Word le_word_hex_builder(Byte *arr, size_t len);
DWord le_dword_hex_builder(Byte *arr, size_t len);

#endif