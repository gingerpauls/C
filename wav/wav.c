#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#define WAV_HEADER_SIZE 44

typedef struct {
    unsigned int ChunkID;
    unsigned int ChunkSize;
    unsigned int Format;
} RIFF;

typedef struct {
    unsigned int SubChunk1ID;
    unsigned int SubChunk1Size;
    unsigned short AudioFormat;
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitsPerSample;
} fmt;

typedef struct {
    int SubChunk2ID;
    int SubChunk2Size;
    float *Data;
} data;

typedef struct {
    RIFF;
    fmt;
    data;
    unsigned long file_size;
} WAVE;

int main(void) {
    FILE *wav = NULL;
    wav = fopen("swoosh.wav", "r+");
    WAVE wavefile1 = {0};
    wavefile1.Data = NULL;

    fseek(wav, 0, SEEK_END);
    wavefile1.file_size = ftell(wav);
    rewind(wav);

    fread(&wavefile1.ChunkID, 1, sizeof(wavefile1.ChunkID), wav);
    printf("ChunkID %s\n", &wavefile1.ChunkID);

    fread(&wavefile1.ChunkSize, 1, sizeof(wavefile1.ChunkSize), wav);
    printf("ChunkSize %u\n", wavefile1.ChunkSize);

    fread(&wavefile1.Format, 1, sizeof(wavefile1.Format), wav);
    printf("Format %s\n", &wavefile1.Format);

    fread(&wavefile1.SubChunk1ID, 1, sizeof(wavefile1.SubChunk1ID), wav);
    printf("SubChunk1ID %s\n", &wavefile1.SubChunk1ID);

    fread(&wavefile1.SubChunk1Size, 1, sizeof(wavefile1.SubChunk1Size), wav);
    printf("SubChunk1Size %u\n", wavefile1.SubChunk1Size);

    fread(&wavefile1.AudioFormat, 1, sizeof(wavefile1.AudioFormat), wav);
    printf("AudioFormat %u\n", wavefile1.AudioFormat);

    fread(&wavefile1.NumChannels, 1, sizeof(wavefile1.NumChannels), wav);
    printf("NumChannels %u\n", wavefile1.NumChannels);

    fread(&wavefile1.SampleRate, 1, sizeof(wavefile1.SampleRate), wav);
    printf("SampleRate %u\n", wavefile1.SampleRate);

    fread(&wavefile1.ByteRate, 1, sizeof(wavefile1.ByteRate), wav);
    printf("ByteRate %u\n", wavefile1.ByteRate);

    fread(&wavefile1.BlockAlign, 1, sizeof(wavefile1.BlockAlign), wav);
    printf("BlockAlign %u\n", wavefile1.BlockAlign);

    fread(&wavefile1.BitsPerSample, 1, sizeof(wavefile1.BitsPerSample), wav);
    printf("BitsPerSample %u\n", wavefile1.BitsPerSample);

    fclose(wav);

    wav = fopen("swoosh.raw", "r+");
    fseek(wav, 0, SEEK_END);
    wavefile1.file_size = ftell(wav);
    rewind(wav);

    wavefile1.Data = malloc(wavefile1.file_size);
    if(wavefile1.Data == NULL) {
        printf("wave1.data malloc failed\n");
    }

    int count = 0;
    count = fread_s(wavefile1.Data, wavefile1.file_size, sizeof(*wavefile1.Data), (wavefile1.file_size / sizeof(*wavefile1.Data)), wav);
    for(size_t i = 0; i < wavefile1.file_size / sizeof(*wavefile1.Data); i++) 
    {
        printf("Data %f\n", wavefile1.Data[i]);
    }

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