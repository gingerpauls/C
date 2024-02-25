#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

typedef struct {
    int ChunkID;
    int ChunkSize;
    int Format;
} RIFF;

typedef struct {
    unsigned char SubChunk1ID;
    int SubChunk1Size;
    short AudioFormat;
    short NumChannels;
    int SampleRate;
    int ByteRate;
    short BlockAlign;
    short BitsPerSample;
} fmt;

typedef struct {
    int SubChunk2ID;
    int SubChunk2Size;
    int *Data;
} data;

typedef struct {
    RIFF;
    fmt;
    data;
} WAVE;

int main(void) {
    FILE *wav = NULL;
    //errno_t err;
    
    
    wav = fopen("swoosh.wav", "r+");

    WAVE wavefile1 = {0};
    wavefile1.Data = NULL;
    
    fscanf(wav, "%d", wavefile1.ChunkID);
    fscanf(wav, "%d", wavefile1.ChunkSize);
    fscanf(wav, "%d", wavefile1.Format);

    fscanf(wav, "%d", wavefile1.SubChunk1ID);
    fscanf(wav, "%d", wavefile1.SubChunk1Size);
    fscanf(wav, "%d", wavefile1.AudioFormat);
    fscanf(wav, "%d", wavefile1.NumChannels);
    fscanf(wav, "%d", wavefile1.SampleRate);
    fscanf(wav, "%d", wavefile1.ByteRate);
    fscanf(wav, "%d", wavefile1.BlockAlign);
    fscanf(wav, "%d", wavefile1.BitsPerSample);

    fscanf(wav, "%d", wavefile1.SubChunk2ID);
    fscanf(wav, "%d", wavefile1.SubChunk2Size);


    fclose(wav);
    printf("program success\n");
    return 0;
}