#ifndef WAV_DEFINITIONS_H
#define WAV_DEFINITIONS_H

#include <stdlib.h>

#include "../binary-definitions.h"

#pragma pack(push, 1)
typedef struct MasterRIFFChunk
{
  DWord file_type_bloc_id; // Identifier « RIFF »
  DWord file_size;         // Overall file size minus 8 bytes
  DWord file_format_id;    // Format = « WAVE »
} MasterRIFFChunk;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct WavDataFormatChunk
{
  DWord format_bloc_id; // Identifier « fmt␣ »
  DWord bloc_size;      // Chunk size minus 8 bytes
  Word audio_format;    // Audio format (1: PCM integer, 3: IEEE 754 float)
  Word nbr_channels;    // Number of channels
  DWord frequency;      // Sample rate (Hz)
  DWord byte_per_sec;   // Number of bytes to read per second (Frequency * BytePerBloc)
  Word byte_per_bloc;   // Number of bytes per block (NbrChannels * BitsPerSample / 8)
  Word bits_per_sample; // Number of bits per sample
} WavDataFormatChunk;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SampledDataChunk
{
  DWord data_bloc_id; // Identifier « data »
  DWord data_size;    // SampledData size
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

#endif