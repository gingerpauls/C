//#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#define CHUNK_ID_SIZE 4

typedef struct {
    unsigned char RIFFID[CHUNK_ID_SIZE];
    unsigned int RIFFSize;
    unsigned char RIFFFormType[CHUNK_ID_SIZE];
} RIFF;

typedef struct {
    unsigned char fmtID[CHUNK_ID_SIZE];
    unsigned int fmtSize;
    unsigned short AudioFormat;
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitsPerSample;
} fmt;

typedef struct {
    unsigned char listID[CHUNK_ID_SIZE];
    unsigned int listSize;
    unsigned char listType[CHUNK_ID_SIZE];
    unsigned char *listString;
} list;

typedef struct {
    unsigned char infoID[CHUNK_ID_SIZE];
    unsigned int infoSize;
    unsigned char *infoString;
} info;

typedef struct {
    unsigned char junkID[CHUNK_ID_SIZE];
    unsigned int junkSize;
    unsigned char *junkString;
} junk;

typedef struct {
    unsigned char dataID[CHUNK_ID_SIZE];
    unsigned int dataSize;
    float *Data;
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

int main(void) {
    FILE *wav = NULL;
    errno_t err;
    err = fopen_s(&wav, "swoosh.wav", "r+");
    WAVE wavefile1 = {0};
    wavefile1.Data = NULL;
    unsigned char chunk_id[CHUNK_ID_SIZE];
    int count = 0;

    fseek(wav, 0, SEEK_END);
    wavefile1.file_size = ftell(wav);
    rewind(wav);

    while(!feof(wav)) {
        count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
        if(strncmp(chunk_id, "RIFF", CHUNK_ID_SIZE) == 0) {
            fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
            count = fread_s(&wavefile1.RIFFID, sizeof(wavefile1.RIFFID) * CHUNK_ID_SIZE, 1, sizeof(wavefile1.RIFFID), wav);
            count = fread_s(&wavefile1.RIFFSize, sizeof(wavefile1.RIFFSize) * CHUNK_ID_SIZE, 1, sizeof(wavefile1.RIFFSize), wav);
            count = fread_s(&wavefile1.RIFFFormType, sizeof(wavefile1.RIFFFormType) * CHUNK_ID_SIZE, 1, sizeof(wavefile1.RIFFFormType), wav);
        }
        if(strncmp(chunk_id, "fmt ", CHUNK_ID_SIZE) == 0) {
            fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
            count = fread_s(&wavefile1.fmtID, sizeof(wavefile1.fmtID), 1, sizeof(wavefile1.fmtID), wav);
            count = fread_s(&wavefile1.fmtSize, sizeof(wavefile1.fmtSize), 1, sizeof(wavefile1.fmtSize), wav);
            count = fread_s(&wavefile1.AudioFormat, sizeof(wavefile1.AudioFormat), 1, sizeof(wavefile1.AudioFormat), wav);
            count = fread_s(&wavefile1.NumChannels, sizeof(wavefile1.NumChannels), 1, sizeof(wavefile1.NumChannels), wav);
            count = fread_s(&wavefile1.SampleRate, sizeof(wavefile1.SampleRate), 1, sizeof(wavefile1.SampleRate), wav);
            count = fread_s(&wavefile1.ByteRate, sizeof(wavefile1.ByteRate), 1, sizeof(wavefile1.ByteRate), wav);
            count = fread_s(&wavefile1.BlockAlign, sizeof(wavefile1.BlockAlign), 1, sizeof(wavefile1.BlockAlign), wav);
            count = fread_s(&wavefile1.BitsPerSample, sizeof(wavefile1.BitsPerSample), 1, sizeof(wavefile1.BitsPerSample), wav);
        }
        if(strncmp(chunk_id, "LIST", CHUNK_ID_SIZE) == 0) {
            fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
            count = fread_s(&wavefile1.listID, sizeof(wavefile1.listID), 1, sizeof(wavefile1.listID), wav);
            count = fread_s(&wavefile1.listSize, sizeof(wavefile1.listSize), 1, sizeof(wavefile1.listSize), wav);
            count = fread_s(&wavefile1.listType, sizeof(wavefile1.listType), 1, sizeof(wavefile1.listType), wav);

            if(strncmp(wavefile1.listType, "INFO", CHUNK_ID_SIZE) == 0) {
                count = fread_s(&wavefile1.infoID, sizeof(wavefile1.infoID), 1, sizeof(wavefile1.infoID), wav);
                count = fread_s(&wavefile1.infoSize, sizeof(wavefile1.infoSize), 1, sizeof(wavefile1.infoSize), wav);
                wavefile1.infoString = malloc(wavefile1.infoSize);
                count = fread_s(&wavefile1.infoString, wavefile1.infoSize, 1, wavefile1.infoSize, wav);
            }
        }
        //else if(strncmp(chunk_id, "data", 4) == 0) {
            // TODO: is this necessary?
            //fseek(wav, -4, SEEK_CUR); 
        //}
    }

    printf("RIFFID: \t%s\n", &wavefile1.RIFFID);
    printf("RIFFSize: \t%u\n", wavefile1.RIFFSize);
    printf("RIFFFormType: \t%s\n", &wavefile1.RIFFFormType);
    printf("fmtID: \t\t%s\n", &wavefile1.fmtID);
    printf("fmtSize: \t%u\n", wavefile1.fmtSize);
    printf("AudioFormat: \t%u\n", wavefile1.AudioFormat);
    printf("NumChannels: \t%u\n", wavefile1.NumChannels);
    printf("SampleRate: \t%u\n", wavefile1.SampleRate);
    printf("ByteRate: \t%u\n", wavefile1.ByteRate);
    printf("BlockAlign: \t%u\n", wavefile1.BlockAlign);
    printf("BitsPerSample: \t%u\n", wavefile1.BitsPerSample);
    printf("listID: \t%s\n", &wavefile1.listID);
    printf("listSize: \t%u\n", wavefile1.listSize);
    printf("listType: \t%s\n", &wavefile1.listType);
    printf("infoString: \t%s\n", &wavefile1.infoString);


    free(wavefile1.infoString);
    printf("program success\n");
    return 0;
}

/*
RIFFvWAVEfmt D��XLIST�INFOIART3freesound.org/people/s-cheremisinov/sounds/402183/ICMT(swoosh woosh transition sfx swish; 53msICOPGCC:0 / Public Domain http://creativecommons.org/publicdomain/zero/1.0/IGNRambientINAMswooshISFTLavf58.20.100dataTn�D�S������u�S�f�r�:��#���:���a�{�����W�y���;"�����\}dd`���}�*O����`÷�ο��'�5��������_���0�������D�9�&�H��o������N������������}�������������S�}���i�B�����[�V�����V���}�a�������n���)-)t!�����\�r_��i���o�+���w�}�I�-�������$�Z���������2���]�S�����7�����L�������9��������}�������}�D���V���I�J� ������"��������V�-�r��������6���{����H	Z	��	�UX��S-�W6|��
���s���_�*�������2��������������9��[��`�����.���x����������������I�H����S�a���B�����c���1���+
�
jZ�:
�
�
�@1�"h
�	����q���������#���5�:�����0�����������Q��������O�2��u�����8��$����s�������~���n�����]�i������������������i�,���������������I����e�s�~���0���,���'�O�����������~�7���p��\�-�2�p��
���U�b�@�`���2�����o�m�
������\��7����y�������:�����ydY
P���	IxZ+o�Dyo�0����������������������տ�o�Pά�Bɝƫ�I�#��������ů���l�)�fͳͮ��������Tײ�/��,�5�<���������O������W�x-����	
    S�o#�����[�������D�2���a۪���n؎�W��Φ�}��^��ǪŒƚ�.�dĳ�!�l�����B�]ī�c���c�)�l�@�W��������U»���T���*���\�����C�G����⼚�%�f�оE������@�h��E�����D͉�j���@���	ڰ���
�������@�������� ���
�������)�\���k���A��T�?ܦӻ�%��Ť�+���G�W�N��� ����������V����0�щ߇熨�D��
���ɋ.�n�Ǒ���Ӟ���:��r�O���7ł��RЇ�x���F�F�����L����-����	`�
�
��)��g�����1���u�t��׷��P�\�f�������۷���C��L�ޚӗE�͒ߐ��Ď������ȕ#�Қ�����̥���m���'���8�
ū�k�%�%�n�c���f���j�2��c���. "�� �#�$'�(�%�#�#c$
$
#$�#��w�P`�q��R	|���[��M�����j���@�-���X���;���}�����(�|!�Zo����/{�%�'�)�+A0�4�5f7T;�?}B�C�D�E�FF�D�E;H�IJLTM�M�NpP�Q�Q�RJSSDU�U�T�SARyP�O�NOTO�LjK�H�F�D�C�E?H�HRH]G.IKYL�N+R\TX�\^I__�`,dsf~fe
d�b�a#`;__^�\�\]6]�]^�]2]^�_d_[^:]a\^�^!_P`�`�][�Y`X�XtZ�[�Y�X�Y�XWxWSY-\p^�_Abee;h	ih�ffg�g�i�j�i�kGm�i�g%hoh�j~m�m�m4q�s�scu�t�s�uv�t�s�r�qVqs�rZq�nVl�k\k�gdf`�\�Z�YW�V9W�UaU6TkQ�P�QQ�Q�R=R�SdV�V)UnT�U�WLWdV�V�V�V6VaU�T�U�V�V�U�U�UV�W�W�U�S'TuT
TIT�U�U�TS[R%S`T�TT�T
VU�TDU
T�R�ROR�Q�QrR�RJSlSS_R�Q�Q�Q�P1PQ�Q�QzQ?Q�PXQ�Q�Q�S�TuT�TmU�UdT�RR�P0O(OQO@N�L�L�L[KnI�F�E�D�@S>�==�<�<B;Q86�4�3l1%/..�-~-�,�**�)�' &c$�"�"3"!d�8��d?�D 	"$%�&,(K*J-�/�14G5"5V5Z5�5Y6�6�5�5d6*7i7�7�6q5�5;6.5w3�1�0T0Q/M-�+w*�(�'G%<#�!� ,�x�c����	���yv���[�4�@�r�m�������k���~���������NO�d����t��d����;��e�����-���r�������J���1����E�7�f�[����n������,�E�����>�����:��"��T��p��`���`����S����������,(���m��C�i�b�C�S������,��N���L�W��b�(���a��T�`��%������D�����x���������������#��ߌ�N���8�����Y��l��� �C�������r�����<�����n�R��n���2�a�"��H�D���N����������^��a�
�A������������<����]�����C������s�������m���������L�0�C��(����f�����N���������������������z��p�I�p�y�R�O�����T����,����K�y�����6�u������%�
�,����x�����9��~�>�}����?���d��
��������G�S����������j���k������������V���������w�����#���X�,�3�����Q�z���������.���A�����A���;�5����J�����������F�a�����6�X����T����������?�������x��������9��������1���k�����~��������������1������]�n�t���k�L���r���a��u��������a�V���D�j��f���������a����k�:���|��&��x��������:��)�Z���y�i�����������[����g�6���-�|�����@�w������7���F�?�R���f���0���~���H�x����������D�y�L�f�������r�������o��������[���������e�Z�1���
�B���L��i�������|�a����,������+�����	���;�[�&���(�������~�V�V�J�_�\���x�j���w�o���f����������9���������A�#����)���I�������"����"�&��������E����x���J�S����"�\�a�������M����P�>�	�#���������,�w�{�&����S���C�H���d�i�n��x�}�`�p���w�i���f�~�!��O����p�8������0����h�������W���3���x�*���=�������Q�5����0�8�@���N�-1��[+��.��!^��$Iy
"������ �;�(�>�����u��(���q����������5����E��.��������y�����6����p�%����.�{���Q���S������W������p�d���K���>�����Q���uB!��L2���-ڰv�.���i��L�g��p���I���+���3���2�������g�o�u�]������ �/��,�G�e���
�}���=���E���L���w�)���O�C���%� �W�����h"��@��]2�å�ze"����i�/���B���w�������������L�
�r�,�I�7��9������;�W�������
�[�y����F���
�*�(�K�����A\l�����ǍnyG������W�����g�Q�:�@�8������������q�w���n�\�S�u�������������J�z�������+�y�����7Ndu�����1%)*��������ʐj]U:����r�>�������q�$��������������������������������$�S�o������������(�U�r���������%X}�������������ä�hN1��������������x�i�U�>�/�*�#�$� ��#�*�/�5�;�C�K�N�R�V�Z�a�e�m�x���������������������������#)/311

*/