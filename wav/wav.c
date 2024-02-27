//#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "windows.h"

#define CHUNK_ID_SIZE 4

typedef struct {
    char RIFFID[CHUNK_ID_SIZE];
    unsigned int RIFFSize;
    char RIFFFormType[CHUNK_ID_SIZE];
} RIFF;

typedef struct {
    char fmtID[CHUNK_ID_SIZE];
    unsigned int fmtSize;
    unsigned short AudioFormat;
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitsPerSample;
} fmt;

typedef struct {
    char listID[CHUNK_ID_SIZE];
    unsigned int listSize;
    char listType[CHUNK_ID_SIZE];
    char *listString;
    unsigned int numInfo;
} list;

typedef struct {
    char infoID[CHUNK_ID_SIZE];
    unsigned int infoSize;
    char *infoString;
} info;

typedef struct {
    char junkID[CHUNK_ID_SIZE];
    unsigned int junkSize;
    char *junkString;
} junk;

typedef struct {
    char dataID[CHUNK_ID_SIZE];
    unsigned int dataSize;
    short *Data;
} data;

typedef struct {
    RIFF;
    fmt;
    list;
    info;
    junk;
    data;
    unsigned long file_size;
} WAVE;

void PrintFilePos(FILE *wav) {
    int file_pos = ftell(wav);
    printf("file_pos: \t%i\n", file_pos);
}

int main(void) {
    FILE *wav = NULL;
    errno_t err;
    //err = fopen_s(&wav, "sounds/sine_44k_16b_1ch.wav", "rb");
    err = fopen_s(&wav, "sounds/ambient-swoosh.wav", "rb");
    //err = fopen_s(&wav, "sounds/ambient-drop.wav", "rb");
    //err = fopen_s(&wav, "sounds/sine_192k_32b_2ch.wav", "rb");
    if(err != 0) {
        perror("fopen\n");
    }

    WAVE wavefile1 = {0};
    wavefile1.Data = NULL;
    char chunk_id[CHUNK_ID_SIZE];
    int count = 0;
    info info;

    fseek(wav, 0, SEEK_END);
    wavefile1.file_size = ftell(wav);
    rewind(wav);

    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
    if(ferror(wav)) {
        perror("read error\n");
    }
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
    if(strncmp(chunk_id, "RIFF", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.RIFFID, sizeof(wavefile1.RIFFID), 1, sizeof(wavefile1.RIFFID), wav);
        count = fread_s(&wavefile1.RIFFSize, sizeof(wavefile1.RIFFSize), 1, sizeof(wavefile1.RIFFSize), wav);
        count = fread_s(&wavefile1.RIFFFormType, sizeof(wavefile1.RIFFFormType), 1, sizeof(wavefile1.RIFFFormType), wav);
    }
    printf("RIFFID: \t%.4s\n", &wavefile1.RIFFID);
    printf("RIFFSize: \t%u\n", wavefile1.RIFFSize);
    printf("RIFFFormType: \t%.4s\n", &wavefile1.RIFFFormType);

    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
    if(strncmp(chunk_id, "fmt ", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.fmtID, sizeof(wavefile1.fmtID), 1, sizeof(wavefile1.fmtID), wav);
        count = fread_s(&wavefile1.fmtSize, sizeof(wavefile1.fmtSize), 1, sizeof(wavefile1.fmtSize), wav);
        count = fread_s(&wavefile1.AudioFormat, sizeof(wavefile1.AudioFormat), 1, sizeof(wavefile1.AudioFormat), wav);
        count = fread_s(&wavefile1.NumChannels, sizeof(wavefile1.NumChannels), 1, sizeof(wavefile1.NumChannels), wav);
        count = fread_s(&wavefile1.SampleRate, sizeof(wavefile1.SampleRate), 1, sizeof(wavefile1.SampleRate), wav);
        count = fread_s(&wavefile1.ByteRate, sizeof(wavefile1.ByteRate), 1, sizeof(wavefile1.ByteRate), wav);
        count = fread_s(&wavefile1.BlockAlign, sizeof(wavefile1.BlockAlign), 1, sizeof(wavefile1.BlockAlign), wav);
        count = fread_s(&wavefile1.BitsPerSample, sizeof(wavefile1.BitsPerSample), 1, sizeof(wavefile1.BitsPerSample), wav);
    }
    printf("fmtID: \t\t%.4s\n", &wavefile1.fmtID);
    printf("fmtSize: \t%u\n", wavefile1.fmtSize);
    printf("AudioFormat: \t%u\n", wavefile1.AudioFormat);
    printf("NumChannels: \t%u\n", wavefile1.NumChannels);
    printf("SampleRate: \t%u\n", wavefile1.SampleRate);
    printf("ByteRate: \t%u\n", wavefile1.ByteRate);
    printf("BlockAlign: \t%u\n", wavefile1.BlockAlign);
    printf("BitsPerSample: \t%u\n", wavefile1.BitsPerSample);

    // TODO turn all of this into a loop
    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
    if(strncmp(chunk_id, "LIST", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.listID, sizeof(wavefile1.listID), 1, sizeof(wavefile1.listID), wav);
        count = fread_s(&wavefile1.listSize, sizeof(wavefile1.listSize), 1, sizeof(wavefile1.listSize), wav);
        count = fread_s(&wavefile1.listType, sizeof(wavefile1.listType), 1, sizeof(wavefile1.listType), wav);
        printf("listID: \t%.4s\n", &wavefile1.listID);
        printf("listSize: \t%u\n", wavefile1.listSize);
        printf("listType: \t%.4s\n", &wavefile1.listType);

        if(strncmp(wavefile1.listType, "INFO", CHUNK_ID_SIZE) == 0) {
            do {
                count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
                fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
                if(strncmp(chunk_id, "data", 4) != 0) {
                    count = fread_s(&info.infoID, sizeof(info.infoID), 1, sizeof(info.infoID), wav);
                    count = fread_s(&info.infoSize, sizeof(info.infoSize), 1, sizeof(info.infoSize), wav);
                    info.infoString = malloc(info.infoSize);
                    count = fread_s(info.infoString, info.infoSize, 1, info.infoSize, wav);
                    printf("%.4s \t\t%s\n", &info.infoID, info.infoString);
                    free(info.infoString);
                    fseek(wav, 1, SEEK_CUR); // TODO why is this needed?
                }
                count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
                fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
                if(strncmp(chunk_id, "data", 4) != 0) {
                    count = fread_s(&info.infoID, sizeof(info.infoID), 1, sizeof(info.infoID), wav);
                    count = fread_s(&info.infoSize, sizeof(info.infoSize), 1, sizeof(info.infoSize), wav);
                    info.infoString = malloc(info.infoSize);
                    count = fread_s(info.infoString, info.infoSize, 1, info.infoSize, wav);
                    printf("%.4s \t\t%s\n", &info.infoID, info.infoString);
                    free(info.infoString);
                    //fseek(wav, 0, SEEK_CUR); // TODO and this is not?
                }
            }
            while(strncmp(chunk_id, "data", 4) != 0);
        }
    }
    // TODO finish junk chunk
    if(strncmp(chunk_id, "junk", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.junkID, sizeof(wavefile1.junkID), 1, sizeof(wavefile1.junkID), wav);
        count = fread_s(&wavefile1.junkSize, sizeof(wavefile1.junkSize), 1, sizeof(wavefile1.junkSize), wav);
        //wavefile1.junkString = malloc(wavefile1.junkSize);
        //count = fread_s(&wavefile1.junkString, wavefile1.junkString, 1, wavefile1.junkString, wav);
        printf("junkID: \t%.4s\n", &wavefile1.junkID);
        printf("junkSize: \t%u\n", wavefile1.junkSize);
        fseek(wav, wavefile1.junkSize, SEEK_CUR);
        //printf("junkString: \t%s\n", &wavefile1.junkString);
        //free(wavefile1.junkString);
    }

    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
    if(strncmp(chunk_id, "data", 4) == 0) {
        count = fread_s(&wavefile1.dataID, sizeof(wavefile1.dataID), 1, sizeof(wavefile1.dataID), wav);
        count = fread_s(&wavefile1.dataSize, sizeof(wavefile1.dataSize), 1, sizeof(wavefile1.dataSize), wav);
        printf("dataID: \t%.4s\n", &wavefile1.dataID);
        printf("dataSize: \t%u\n", wavefile1.dataSize);
        wavefile1.Data = malloc(wavefile1.dataSize);
        //TODO why does this cause printf to cause exception
        //count = fread_s(&wavefile1.Data, wavefile1.dataSize, 1, wavefile1.dataSize / sizeof(*wavefile1.Data), wav);
        int total_count = 0;
        for(size_t i = 0; i < wavefile1.dataSize / sizeof(*wavefile1.Data); i++) {
            count = fread_s(&wavefile1.Data[i], wavefile1.dataSize, sizeof(*wavefile1.Data), 1, wav);
            printf("Data[%i]: \t%hi\n", i, wavefile1.Data[i]);
            total_count += count;
        }
        free(wavefile1.Data);
        printf("total_count: %i\n", total_count);
    }
    fclose(wav);
    
    printf("program success\n");
    return 0;
}