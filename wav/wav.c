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
    err = fopen_s(&wav, "sounds/swoosh.wav", "r");
    if(err != 0) {
        perror("fopen");
    }
    
    WAVE wavefile1 = {0};
    wavefile1.Data = NULL;
    char chunk_id[CHUNK_ID_SIZE];
    int count = 0;
    info info;

    fseek(wav, 0, SEEK_END);
    wavefile1.file_size = ftell(wav);
    rewind(wav);

    //PrintFilePos(wav);
    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav); // remove later
    //PrintFilePos(wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR); // remove later
    //PrintFilePos(wav);
    if(strncmp(chunk_id, "RIFF", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.RIFFID, sizeof(wavefile1.RIFFID), 1, sizeof(wavefile1.RIFFID), wav);
        count = fread_s(&wavefile1.RIFFSize, sizeof(wavefile1.RIFFSize), 1, sizeof(wavefile1.RIFFSize), wav);
        count = fread_s(&wavefile1.RIFFFormType, sizeof(wavefile1.RIFFFormType), 1, sizeof(wavefile1.RIFFFormType), wav);
    }
    printf("RIFFID: \t%.4s\n", &wavefile1.RIFFID);
    printf("RIFFSize: \t%u\n", wavefile1.RIFFSize);
    printf("RIFFFormType: \t%.4s\n", &wavefile1.RIFFFormType);

    //PrintFilePos(wav);
    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav); // remove later
    //PrintFilePos(wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR); // remove later
    //PrintFilePos(wav);
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

    //PrintFilePos(wav);
    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav); // remove later
    //PrintFilePos(wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR); // remove later
    //PrintFilePos(wav);

    if(strncmp(chunk_id, "LIST", CHUNK_ID_SIZE) == 0) {
        count = fread_s(&wavefile1.listID, sizeof(wavefile1.listID), 1, sizeof(wavefile1.listID), wav);
        count = fread_s(&wavefile1.listSize, sizeof(wavefile1.listSize), 1, sizeof(wavefile1.listSize), wav);
        count = fread_s(&wavefile1.listType, sizeof(wavefile1.listType), 1, sizeof(wavefile1.listType), wav);
        printf("listID: \t%.4s\n", &wavefile1.listID);
        printf("listSize: \t%u\n", wavefile1.listSize);
        printf("listType: \t%.4s\n", &wavefile1.listType);

        if(strncmp(wavefile1.listType, "INFO", CHUNK_ID_SIZE) == 0) {
            do 
            {
                count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
                fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
                if(strncmp(chunk_id, "data", 4) != 0) {
                    count = fread_s(&info.infoID, sizeof(info.infoID), 1, sizeof(info.infoID), wav);
                    count = fread_s(&info.infoSize, sizeof(info.infoSize), 1, sizeof(info.infoSize), wav);
                    info.infoString = malloc(info.infoSize);
                    count = fread_s(&info.infoString, info.infoSize, 1, info.infoSize, wav);
                    printf("%.4s \t\t%s\n", &info.infoID, &info.infoString);
                    fseek(wav, 1, SEEK_CUR);
                    wavefile1.numInfo++;
                    //free(info.infoString);
                }
                count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
                fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
                if(strncmp(chunk_id, "data", 4) != 0) {
                    count = fread_s(&info.infoID, sizeof(info.infoID), 1, sizeof(info.infoID), wav);
                    count = fread_s(&info.infoSize, sizeof(info.infoSize), 1, sizeof(info.infoSize), wav);
                    info.infoString = malloc(info.infoSize);
                    count = fread_s(&info.infoString, info.infoSize, 1, info.infoSize, wav);
                    printf("%.4s \t\t%s\n", &info.infoID, &info.infoString);
                    fseek(wav, 0, SEEK_CUR);
                    wavefile1.numInfo++;
                    //free(info.infoString);
                }
            }
            while(strncmp(chunk_id, "data", 4) != 0);
        }
    }
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

    PrintFilePos(wav);
    count = fread_s(&chunk_id, CHUNK_ID_SIZE, 1, CHUNK_ID_SIZE, wav);
    fseek(wav, -CHUNK_ID_SIZE, SEEK_CUR);
    PrintFilePos(wav);
    if(strncmp(chunk_id, "data", 4) == 0) {
        count = fread_s(&wavefile1.dataID, sizeof(wavefile1.dataID), 1, sizeof(wavefile1.dataID), wav);
        PrintFilePos(wav);
        count = fread_s(&wavefile1.dataSize, sizeof(wavefile1.dataSize), 1, sizeof(wavefile1.dataSize), wav);
        PrintFilePos(wav);
        printf("dataID: \t%.4s\n", &wavefile1.dataID);
        printf("dataSize: \t%u\n", wavefile1.dataSize);
        wavefile1.Data = malloc(wavefile1.dataSize);

        //count = fread_s(&wavefile1.Data, wavefile1.dataSize, sizeof(wavefile1.Data[0]), wavefile1.dataSize / sizeof(wavefile1.Data[0]), wav);
        
        PrintFilePos(wav);
        int count2 = 0;
        //for(size_t i = 0; i < (wavefile1.dataSize / sizeof(wavefile1.Data[0])); i++) {
        for(size_t i = 0; i < wavefile1.dataSize / sizeof(wavefile1.Data[0]); i++) {
            count = fread_s(&wavefile1.Data[i], wavefile1.dataSize, sizeof(wavefile1.Data[0]), 1, wav);
            printf("Data: \t%i\n", wavefile1.Data[i]);
            count2 += count;
        }
        printf("count2: %i", count2);
    }
    //free(info.infoString);
    printf("program success\n");
    return 0;
}

/*
RIFF@WAVEfmt D��XLIST�INFOIART1freesound.org/people/dayvonjersen/sounds/156295/ICMT,modulation frequency effect synthesis; 70msICOPGCC:0 / Public Domain http://creativecommons.org/publicdomain/zero/1.0/IGNRambientINAMdropISFTLavf58.20.100data��-�����l�oG}:��`����������u���j�kʺ�?���������=�
y��7"�+0/�+{))P%���/K����ۊ��א��̸��ϒԡ�3���z��
�V�
"9�$�(�*�-�1R2a0�-;*%��F`���<�U�/��Ԅ�]α�y���{�}٨��������:�WD�%;+�.N/�0"1]/
,&]`.����'������ڪ�m�И�6�"�6՞�\ݙ�X�X����
C��"*�-�,�-�/=0
-b'- u�
�|�����E���ו��ғ�|�X�~���#�N�&��w���r�,!�&
+.�/�/�.,(�"�� �������+��Y�AӉ�=�Q��ԛ؍ݎ�g�������	y�p$�(�+�-.-�*'2"Z�T�����/����N�����
ӆ�DӞ�:��q�[���7�ڏ	k�
� �&�*3+)�'�(�&� �6��	����9����F��սՕ���'��������c�MQ	#���!U&�(p(�&%'"����	;�������o�D�Mڽء��������Q�D��L�	�X�.!E$�%&�$�!�i�������X�d��ۨ���b�������O��/��"b$z$�" �#������
���g�dޭ��ܞބ�b�����	�� �!w!�!s Y��
m)���H���G���Y�p�
�����W��~����4� � �4z��G���?����;���ߥ�8�)����!}M\)�U�.B�g����-����������X� �������>
&�zx���a��	����������u�����V��D�1�	L>���n��	R*����G��x�W�������u�_�����	�4��Wy�[�i��>�I������#�5��������
Ox_��,��+���`����<���Z�����#�����
�x�������
H������������w����j�
���	��������	��f������&�y��K�p��L�� u9H���id�����~���L������_���}�	�]���mL��.�4�,���G�����������
!�����%
�x�,���8�H��������
���c
�(�������J�����e���������U�$�������
UA�2�������{��+��j�6���
L��0��������	���b��W�u������
%N
0��
���P����������5������#	�
 ��d�	��t�����"�P�+����t�����	�J^�k|�����#���-��S�g��J�!��Qq
�,������Y�W���6������3&	,
�+��7�|,�>�)�R��X�D���)�mTd5�?Q�
��X����������]��������$N<
�	uq_����������������3
�
���!5�����c�U���W�^�{�L�B��1B��p	/`����j���
��L����Q

{���	��,���`�5��b��,�����	c�
��	d��������!��O���=��@�	��
�
�DK����d�������a���-Pz
sG
�j
��E�
�t�����s�Z�v�n���|��Iw�l�D�P���f��-�����/
�nn	��`�|�`�g������+�$�X5d	jW5	!�$�����;����$����
��
�����2�'�?���q�����u�o	�
La
4�6J�����P���a���n�C�E	�
�
�	���.�����`������%����	�

o�*���9�^���l�X�Y�����;�	�	�kc��c�N�%�-�d���h���	�Z	�	�'�{�y�����w����"����u_		Z�����y� ���������(�L8	�.��O�-���C���9�#�Mg�Z�O-��������Z�j�������e���~�n���������=���m��l��875���~���\���|�)��������9� $�l�S�4�:�O�^���t�������k���S�����������n�U���A�r������8����7���<x�������������Z���������`�d�;������#��QP{��������x�K����/��6.Nt������������p�*�v��R',5D�D��m�������������,Z�����S�C����`���m�����U�m$3��������[���3�&�s�ie��d[���R�{�����)�:�hY�d R;�4���~��y�F�]q4�
�����������r�������p�����'�#�����1�
���	���;F<�����F�������q����p������e�����M�&x[������P��������7��K3n��P���r�������"�������n�(���u��� ���\������zJ�������]�H���H���:t��r���>�������8����&��T���c�����_��JL�u�T��_�;�����+�F���/wN�<S���.�!�����m���p�Qs��D������������E��FC��`��������=����L?�n@���2���<�&�m������8F����������������������*�G��������������o���<�N����;I��i�^8�9���I���E�H�irH��(ZI��z�a���v�p���k�l�	�����s���������i�t�������������������h�I�����������6������fzYPI�u�������}�H�6)�E7�.2,�k��������c�zs�- ������J�����������q�7|�����%�����R����Ƒ3�4h����(����}�3���?\�����������E�+��5b���2��J�����l6����:���'��_������;���U����s��'�w�����N���"q����f�'�6���<����X����D}���`�1�U���f�#�l��g�c���Y�@�r�����K�p��@�F���U�N������p������;���o�h���+����d�Z�j�����q�����o��]��v�A������r������H�D��E�{�����t������O�W�p.���8���������=���q�BhS�v��J���y�~���U���{�V�O�E��%���������^����_k,�*������������7�B6�����������;����[F�h��j���������Y���O�-A �[��Q���������|�����-)�D��8�������.��������!�����
�[���-���|��|�������_���$�B(�D��y�"������k���m���7��_������%�z���u�
�!��I������4���y�	��t��:�����"�Z���j���k����:���5�|���I����I��t�+������g���7���Ȉ)��h����>�����P����~%��d�$��!�W���g��߹n��h�+��.�g���s��ձd��g�1�*�9�p���o��˧i��p�9�*�=�u���`��Ȩg��w�D�.�D�k���W����}3����E�F�u�����g��Ưu��q�,�
��?�����B��±�C����:���A�����a��Σf��p�;�#�/�R���f���͠C����l�E�+�5�x���0p�ϼ�b2����S�@�H�i�����A��ѿ�U����g�K�J�s���\��ɱ~@����v�P�J�k�����o����p6����}�o�n�m�����$m����i2����s�F�T�z�����Y����h.������p�Y�h�����>}����^����u�i�b�|�����"g����u5����f�N�W�n�������I�����_ ����|�d�b�r�����P�����D������}�{�{�t�����E�����vM����d�f���������+v����l;������y�~�������2e�����M	������x�f�����In|����U����w�Z�]�w�����M��ͼ�x<������f�Y�n�������,s�»��^�����n�o�}�������9~�γ�{U����w�Y�Z�������P�����j@�����x�t�������M�����s8����{�`�q���������3f�����X����������������1?]���zL*�����������������)c��|vjD������������������9Jb��|I+	��������z���������;W}�|aW<������������������Ikuont_1��������y���������Go���rN��������p�q���������"Fjy��i.������������������)QhvpcQ7��������������������3SouYH:"����������������������;IMY^G)��������������������2TacS1
����������������������2CIIHP8������������������������0KORM@*����������������������&ACMQI?(
������������������������7FGAB7%��������������������������,3:?@?-��

*/