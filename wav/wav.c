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
RIFF@WAVEfmt D¬ˆXLISTöINFOIART1freesound.org/people/dayvonjersen/sounds/156295/ICMT,modulation frequency effect synthesis; 70msICOPGCC:0 / Public Domain http://creativecommons.org/publicdomain/zero/1.0/IGNRambientINAMdropISFTLavf58.20.100data¢ï-îøñ¨ú©l¸oG}:Ë€`úœööÖö÷õÔïuãó×jÏkÊºÏ?Ü÷èÑóôû¡ÿ=Ä
y¼¾7"+0/İ+{))P%š¬—/Kş÷ì’àÛŠÚÔ×ÑÚÌ¸ÌúÏ’Ô¡Ø3ŞÃäzé¦î
úVÄ
"9Ï$Ø(°*õ-…1R2a0²-;*%•¼F`ÿ²ö<îUæ/ßÙÔ„Ğ]Î±ÍyÎÀĞ{Ô}Ù¨ßÊæ“îğöœÿ:–WD•%;+„.N/û0"1]/
,&]`.şîÌ÷'ñ÷éÂáÿÚªÖmÓĞ˜Í6Î"Ò6Õ×\İ™åXîXö©ü²
Cµ¼"*Ê-ä,¯-Ò/=0
-b'- uŒ
’|ıªóôêEâÛÿ×•ÕÕÒ“Ğ|ĞXÒ~ÕÒÙ#ßNå&ìšówû‰šr°,!²&
+.¬/é/­.,(ú"Ç½ Ìı©õÚíœæ+à­ÚYÖAÓ‰Ñ=ÑQÒĞÔ›ØİãgêİñÁùÍË	y p$Å(ä+¦-.-§*'2"Z©T˜¤şÄö/ïèÁáNÜñ×İÔ
Ó†ÒDÓÕ:Ùİqã[êïğ7øÚ	k¯
¢ ‡&è*3+)ä'›(ú&² è6´Ç	û„ò‡î9êÆãİFØÜÕ½Õ•×ÎÙ'Ü×ßåÇëÁócûMQ	#üÌ£!U&ç(p(¿&%'"˜¦ç«	;ÂúóÑì²æoáDİMÚ½Ø¡ØøÙÅÜŞàæQìDó¬úLÌ	ãXØ.!E$è%&¯$Ü!·iªü¯ôÀí„çXâdŞÂÛ¨ÚÛİbàåÚêƒñÈøOÕŒ/£¸"b$z$ş" ª#½—ù§ò
ìñågádŞ­ÜÈÜŞ„ábåêñŞù	Ê¹ Ã!w!›!s Yñ
m)ıüôHíöæGâ¥ßßYßpà
ãÓæìóWûš~Öè–Ş4­ Æ ê4zŒ…GùÙğ?ê¹åúâ;áƒßùß¥ã8è)íãò¿ù!}M\)U”.Bêgıö²ï-êáåüâ¥áôáäãXç ìûñ•øœÿ£>
&ÿzxØ®aï	³¸ûíôÔî¯éÓåuãºâ›ãæêVïõDü1ë	L>Á“Çn–Œ	R*ıöğGêæxãWãæäöæıéuï_÷ñş¸ï	Ê4˜ôWy†[êiûÿ>ùIòäìÓèå#ã5äçëİïõúú
Ox_­ª,ãæ+«Îù`óùí‚é<æÈäZåçëÿï#öğüà—
˜xäŸù¥µ¢
Hıœö’ğ›ëüçøåÊåwçÀê„ïjõ
üó§	¢ˆËÉû€‘	àüfõïæê¨ç&æyæ’èKìpñ‘÷Lş u9HöÖidÿ¾øò~í¼éçLçÄèëë‘ğ_öÒü}è	–]Ô…¡mL¹ÿ.ù4ó,î…êƒèGèÛéíÌñŒ÷ôı©
!²„ƒÑŒ%
îxı,÷ñ8íHêé°éìÅïÛô
ûšäc
İ(Ş£È°¾ÿJùóÂîeëÉéÛéëïôúU$¤Ø¦³°ìÿ
UAÿ2ùšóöîÎë{êë+íµğjõ6û­Ï
Lùó0Õ÷ßüáö¼ñ	îëëbë‘ìWïuó§ø®şéš
%N
0€ş
ŠéşPùôïáìøëÍì5ïóøËı¡#	¿
 öƒdÿ	°ÿtùôğ"îPí+î£ğƒôtùúş‘Â	€J^øk|ıøóğ#îĞí-ïòSögûãJÅ!ÕŞQq
’,ÍúäõññYïWîûî6ñÜôŒùÒş3&	,
ì+·«7­|,ü>÷)óRğïXïDñ¡ôù)şmTd5…?Qü
šXüŠ÷’óÕğ˜ïğò]õÃù¾şÜ¥–$N<
æ	uq_û¥öşòÒğğ»ğóïö­û½¸3
˜
‰éÀ!5‰—ş©ùcõUò°ğ¦ğWò^õ{ùLşBä¬1B×Üp	/`û÷•ójñçğ
òôLøÛüĞQ

{‚ãÄ	¡î,üĞ÷`ô5ò‰ñbòŸô,ø²üˆ»	cõ
‚	d¸üñ÷©ô®ò!òóOõØø=ıâ@ö	£á
€
ƒDK£ûŠ÷dô³òòüó®öaú¸ş-Pz
sG
¦j
âªEş
útöüóöòsóZõvønüÈÆ|àÒIw­lüDøPõ¢ófóšô-÷¾úçş/
÷nn	¦›`ı|ù`ögôÌó©ôßö+ú$şX5d	jW5	!ş$úúöğô;ôîô÷$úşıë
¸ü
êÌûğı2ú'÷?õ¥ôqõ‰÷¥úuşo	Ó
La
4ÿ6Jı¶ùíöPõõöaøŸûnÿC®E	±
Ã
	¼÷ÿ.üæøŒö`õõ÷´ù%ıìŠ™´	—

o¨*‚şû9ø^öÄõlöXøYûîş‚®;À	å	¯kcğÿcüNù%÷-ödöÏ÷húı	„Z	œ	ø'Î{ıyúù÷‚öwöÄ÷ú"ı‚È‹u_		Z¿‚şäúyø ÷éöï÷ÿùÛü(ƒL8	¿.¯œOş-û¡øC÷÷ø9ú#ıMgÏZĞO-ŞıøúÒø‘÷Z÷jø£ú¥ıÊÊeÂû~”nı‘úŠø—÷ç÷=ùƒûmşl©ş875†…ÿ~üòù\øâ÷|ø)ú¥üÿ…â—9÷ $şlûSù4ø:øOù^ûşÜt½éœÿÄükúÜøSøóøŒúúüÏÿ£Ân—U—ÃıAûrùœø×øú8üáş¯7üŞ×<xşíûûùèøäøéùÓûZş¡ÃÜç¡çş`üdú;ùù÷ù¼û#şÌQP{©Ïµÿ–ü£úxùKùúØû/şÀ6.Nt¢é˜ÿ©üÀúªùùpú*üvşúR',5DDºşmüÁúİùÙù×ú“üÕş,Z÷Ó´Ö”SşCü»úú`ú‰ûmı·ÿúôUÙm$3ğÿ«ıÇû¢ú[úçú3ü&şs­ieƒÔd[ÿáüRû{úú…û)ı:ÿhYÅd R;ş4üäú~úûyüFş]q4„
êşùüŒûàúûæûrıƒÿ·‡®˜p©¯ÿÌı'ü#ûıú»û1ı
ÿı¸	É¨¾;F<şœü£ûFûû©üşqÕ”Úp•·şıèûeû­û¸üMş&x[‰ãšÖışPıüšûÑûÁü7şÑK3ná¯Pÿ¬ırüİûùûÄü"şÔÿ‹ó×ˆnà(ÿ“ıuüòû üûü\şşÿ¨ÓızJµÿ˜ı‰üü]üHı±şHÚÓà:tÖşrı†ü>ü¥üŸıÿœ8Ë«íª&˜şTıücüâüóı_ÿìJL´uŸTÕÿ_ş;ıšüü+ıFş²ÿ/wN–<Sş…ÿ.ş!ı§ü¾ümı—şpšQsü±DÿÿııµüíüµıèşE°FC»µ`ÿØııËüış=ÿÈ¾L?„n@ÿøı2ıæü<ı&şmÿ³ËŠãÊ8Fªş™ııı˜ışŸÿÔã‘Ù¯Ãÿş—ı*ıGıÚıÀşÜÿû¯ë± ÿoş£ı<ıNıéıÿ;Iµâi‡^8ÿ9ş…ıIı‹ıEşHÿirH·¥(ZIÿşzıaı¾ıvşpÿ–ªk¤lè	ñşş…ısıãı±ş±ÿ°™iÀt©¿Òÿİşùı„ıışÛş×ÿåÅhšI‹ÿ¦şş¬ı»ı6şüşıÿßfzYPIÿuşïı»ıêı}şHÿ6)ñE7Ú.2,ÿkşùıÜışşcÿzsú- ´ïöÿÿşJşàıËışÏşÂÿ¶qı7|²Ãÿ×ş%şÔıéıRşÿèÿÆ‘3Û4hÿ»ş(şêış}ş3ÿé¨»?\ÿ†şúıÊıüı‚şEÿ+³¼5bÿ«ş2şşJşÑş—ÿl6Ëï‰Ú:ÿş'şş_şîş°ÿ„;½éËUÔÿÿsşş'şwşÿÖÿ¡N¾à©"q©ÿíşfş'ş6şšş<ÿıÿ½X¿ËˆüD}ÿÒş`ş1şUşÄşfÿ#İl¶´gÏcÿÁşYş@şrşêşÿKùp¨Ÿ@ªFÿ®şUşNşşÿ¼ÿp€ ˆİÿ;ÿ´şoşhş©ş+ÿÏÿ„d…ZÑjÿ÷ş¥şqşşãşoÿÀ]¶·vğA”ÿúş™şrş›şÿ ÿHÙDˆ‘E¼{ÿñşšştş£şÿ²ÿOãWƒp.·şÿ8ÿºşƒşşÊş=ÿÓÿqìBhSûvàÿJÿÇşyş~şÊşUÿîÿ{øVOÕE±ÿ%ÿ¼şşŸşçş^ÿôÿ‰_k,´*—ÿÿ¼şŒşªşÿ¤ÿ7®B6öŠ„ÿÿÊşÃşğş;ÿ£ÿ¨[Fàhïÿjÿïş©ş¹şışYÿÊÿOÑ-A Ñ[ÒÿQÿûş·ş­şış|ÿÿÿƒó-)³D¿ÿ8ÿÙş¾şáş.ÿÿ”ôœÿ!ÿØşÑş
ÿ[ÿ¹ÿ- Şê|úÿ|ÿÿñşğşÿ_ÿÃÿ$—B(ÃD×ÿyÿ"ÿáşÒşÿkÿòÿmÍú£7Äÿ_ÿÿéş÷ş%ÿzÿúÿuÌ
é•!¤ÿIÿÿşşış4ÿ ÿyÏ	ûÃt¡ÿ:ÿışış"ÿZÿ²ÿjÊüÉkùÿ‰ÿ:ÿÿÿ5ÿ|ÿæÿI¦æúì¬IÚÿtÿ+ÿùş÷şÿgÿÌÿ7•ÓàÈˆ)Ìÿhÿÿÿÿ>ÿ‹ÿôÿP§ßèÉ~%»ÿdÿ$ÿÿ!ÿWÿ¦ÿg³İß¹n¶ÿhÿ+ÿÿ.ÿgÿºÿs²ÔÕ±dµÿgÿ1ÿ*ÿ9ÿpÿ¾ÿo®ÌË§i»ÿpÿ9ÿ*ÿ=ÿuÿ»ÿ`¦ÌÈ¨gÃÿwÿDÿ.ÿDÿkÿ²ÿW”¾»¦}3ãÿ‹ÿEÿFÿuÿÿÇÿg£ÆÆ¯uÀÿqÿ,ÿ
ÿÿ?ÿ–ÿñÿB‘¿Â±„Cîÿ’ÿ:ÿÿÿAÿ’ÿØÿa®ÚÎ£fÂÿpÿ;ÿ#ÿ/ÿRÿ”ÿf›³ÉÍ CßÿÿlÿEÿ+ÿ5ÿxÿÚÿ0pªÏ¼—b2èÿ‹ÿSÿ@ÿHÿiÿ‘ÿÜÿAœÈÑ¿•U´ÿ€ÿgÿKÿJÿsÿ·ÿ\ÇÉ±~@õÿ±ÿvÿPÿJÿkÿ‘ÿĞÿo¨Á¸—p6éÿ£ÿ}ÿoÿnÿmÿŠÿĞÿ$m ´®—i2ıÿ½ÿsÿFÿTÿzÿªÿÛÿYŒ¯¼¢h.÷ÿÅÿ™ÿpÿYÿhÿÿÌÿ>}®½²^Ëÿ˜ÿuÿiÿbÿ|ÿ©ÿŞÿ"g µ°›u5÷ÿ§ÿfÿNÿWÿnÿ‰ÿ»ÿşÿIˆ®»§†_ Úÿ¢ÿ|ÿdÿbÿrÿÿßÿPƒ¨®¦ƒDşÿÂÿÿ}ÿ{ÿ{ÿtÿ’ÿäÿEˆ¡£švMÁÿ‡ÿdÿfÿ„ÿªÿÊÿíÿ+vŸ¦£‘l;Õÿÿ‚ÿyÿ~ÿ™ÿÅÿüÿ2e“¬©›€M	Èÿ ÿ‰ÿxÿfÿƒÿÍÿIn|š¸¿Uàÿ­ÿwÿZÿ]ÿwÿ¦ÿßÿMƒ¹Í¼›x<õÿµÿŠÿfÿYÿnÿœÿÈÿñÿ,s§Â»­^Íÿÿÿnÿoÿ}ÿŸÿÇÿıÿ9~ÁÎ³“{Uãÿ«ÿwÿYÿZÿ†ÿ¸ÿŞÿPˆ©¶«‘j@×ÿšÿÿxÿtÿ‘ÿ­ÿÒÿM€µÁ¬s8Öÿ¥ÿ{ÿ`ÿqÿ–ÿ¬ÿÁÿöÿ3fŠ˜˜„XôÿÇÿ”ÿ„ÿ˜ÿ£ÿ‘ÿ·ÿ1?]ˆŸ›zL*åÿ´ÿÿÿ‡ÿ«ÿËÿåÿûÿ)c…ˆ|vjDñÿÅÿ©ÿ“ÿÿ ÿ¯ÿÈÿòÿ9Jb…|I+	ŞÿÇÿ³ÿ–ÿzÿŠÿ·ÿÛÿıÿ;W}‰|aW<Æÿÿ™ÿ–ÿ’ÿŠÿ¢ÿÍÿúÿIkuont_1Ğÿ§ÿÿ„ÿyÿƒÿ©ÿËÿçÿGo‰‘ŠrNşÿïÿÅÿÿpÿqÿŒÿªÿÂÿåÿ"Fjy†‚i.şÿİÿºÿ–ÿÿÿÿ¥ÿÃÿäÿ)QhvpcQ7õÿÈÿ¦ÿ˜ÿ’ÿÿ‰ÿ¢ÿÇÿæÿ3SouYH:"ãÿ¾ÿÿ’ÿšÿ’ÿ™ÿµÿØÿèÿüÿ;IMY^G)üÿßÿ¸ÿ¥ÿÿ›ÿšÿ¦ÿ¶ÿÙÿ2TacS1
ôÿĞÿ²ÿ£ÿ–ÿšÿ¨ÿ·ÿÂÿØÿ÷ÿ2CIIHP8ùÿçÿÓÿ¾ÿ´ÿ¦ÿŸÿ›ÿ©ÿÁÿÎÿéÿ0KORM@*êÿÏÿ¬ÿ™ÿ£ÿ¦ÿ¢ÿ£ÿ±ÿàÿóÿ&ACMQI?(
éÿÏÿºÿ±ÿ›ÿ“ÿ˜ÿªÿ»ÿÊÿÙÿùÿ7FGAB7%ìÿÕÿÀÿ¯ÿ¤ÿ ÿ¦ÿŸÿ›ÿ²ÿØÿïÿÿÿ,3:?@?-îÿ

*/