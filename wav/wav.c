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
RIFFvWAVEfmt D¬ˆXLISTöINFOIART3freesound.org/people/s-cheremisinov/sounds/402183/ICMT(swoosh woosh transition sfx swish; 53msICOPGCC:0 / Public Domain http://creativecommons.org/publicdomain/zero/1.0/IGNRambientINAMswooshISFTLavf58.20.100dataTnıDıSı¢ışÌıuıSıfırı:ıı#ıæü:ıáıaş{ş¨şóşWÿyÿßÿ;"ßÿòÿ°\}dd`”×«}Û*OÛ‰«`Ã·ÃÎ¿¬ş'Ê5¢ÿÿÿŠş_ıÍü0üµûµû‡ûDû9û&ûHûûoúúÜù¡ùNùùÛøÄøÓøüøÓø}øøÈøÀøÌøæø­øSø}øüøiùBúæúõú[ûVüÜüŠüVü¶ü}ıaş¶ş¨şØşnÿâÿ)-)t!£¾Ÿ¨\ºr_«øiŸ”œo§+îÿÿwş}ıIü-û”ú‰úú$úZù¹ø¼øÌø§ø2ø¿÷]÷SöØõóõ7õô»ôLôÍóÁóôô9ô“ô±ôõ÷õ}ö©öö¼ö}öDöÈöV÷»÷IøJù ú…úÛúû"ûîúœúû­ûVü-ırı¼ı²ş§ÿ6ĞÊæ{ü¡Ÿ×H	Z	ãò	«UXÀS-W6|øÿ
ÿ¼ısüµû_û*ûúæø£øø2ö‹ôêóóÏñ ğïÜîî9í‚ì[ë”ê`êÎé³éé.èÀèxéÎé÷éêë¬ëéë²ìÎí­ï†ğ·ğIñHòŸóµôŠõSöa÷ˆøBúÎûÚıcÿæÿ1ÖÑ‰+
ß
jZÂ:
À
Û
à@1»"h
¿	ÈÑØ…q¿óşòüùüšı#ıÓú5ù:øØ÷†÷0õáò…ñİï†îôí­íµíQìƒéé‘é¼èèóçOè2èèuè¹èƒéêê8ëì$ìíÖísî²îÑîùî¢ï~ğò¾ónöÜ÷Äø]ùiù”ú»ûÒûü¶ü…ıŠşÿş¦ıiş,şÖıåıÿ²ş©ıàş†øÿIÿÿÕşeşsş~şÌı0üòú,ú¤ù'øOö¾õ‘õ‹ôòšï¶îší~ì7ìøëpë®ê\ê-é2æpä‹ä
ãáàUàbá@â`ã†åè2èèéÒéoêmë
ìæìíÍî\ñ“ô7÷øÛúyıÀıÔü‹ı:ÿóÛÖøydY
P¢€ó	IxZ+ošDyoş0úéöüôÄñ”ïéí›êİæ†ãáÙİÿÚÄØõÕ¿ÒoĞPÎ¬ËBÉÆ«ÄIÃ#ÃÇÃíÃïÄùÅ¯ÆÇÈlË)ÍfÍ³Í®ÎáÏÑãÒõÕT×²Ú/Şá,å5é<ëÚíğÒğŠó÷Oûíı•ÊÍW×x-µ”Íí	
    Sùo#ÿ‚ü¿÷[ôò¤ğˆìÊæDâ2ßæÜaÛªÚàÙnØÔWÑêÎ¦Ì}ÊÊ^ÊíÇªÅ’ÆšÈ.ÈdÄ³Ä!ÆlÄìÁÁÀBÂ]Ä«ÄcÅÒÆcÅ)ÆlÆ@ÄWÁÂÂŒÃÙÁÄÃÄUÂ»ÂÇÁTÃïÂ*ÁÁÀ\¾¤½¸¼C½G½¯½½â¼š½%¿f¿Ğ¾E¼é¼Àì¿ïÂ@ÆhÆÈEÊèÊãËDÍ‰ÎjÑíÓ@ÔÊÖ	Ú°ÛÒÛ
ÚÛİùÜõŞ@ßÉàùã¾åÒä åç§è
ê§ê¤ëÅìõì)ë\ìæìkê§èæAãáTŞ?Ü¦Ó»Í%ËıÅ¤Â+¾ø¸G´W¯N©¦è¢Â Ÿ‚›ş–ş”“†’V–Œ0‹Ñ‰ß‡ç†¨†Dˆâ‰
‰‚‰É‹.ŒnÇ‘”™Ó„¨¯:³·rºO¿ëÂ7Å‚ÉÍRĞ‡ÖxİÃäFçFéÜì¾îñLôøÊû-ıÿöï	`¶
ã
Çñ)­ıgú»ôÑî1ë ç âußtÛõ×·ÒĞPÎ\ÌfÊùÅÿÁ¸¼Û·±¥«C©£LŸŞšÓ—E•Í’ßÀÄû®‘’È•#šÒš¢œ¡£Ì¥ª¯m²¦¶'ºö»8¿
Å«ÉkÎ%Ô%ÙnßcãÒæfíİòjø2’c¶û. "†¦ ì#Á$'Û(–%Â#î#c$
$
#$Š#˜ÂwÜP`ıq…‰R	|ªÊş[ûùMúŸúîøjøÅ÷@ù-ûôûXü¡ù;÷òø}úüšı€(‹|!ÄZoæÌº¹/{‰%Ë'›)ü+A0œ4è5f7T;?}BÅC©D¿E§FFD»E;H¥IJLTMıMÃNpPàQ™QÈRJSSDUåUõTSARyP²OğNOTOïLjKÔHîFŸDØC¿E?HîHRH]G.IKYLéN+R\TXÃ\^I__¼`,dsf~fe
d±b¡a#`;__^´\¬\]6]¾]^Š]2]^Ÿ_d_[^:]a\^¿^!_P`“`®][ÀY`X¬XtZÀ[YçXÓYÅXWxWSY-\p^à_Abee;h	ihÕffgÄg¦i¿j‰i£kGm‰iÖg%hohŠj~mÂm×m4q‡sÒscuÑt»sËuvòt‹sÌrŠqVqsörZq»nVlãk\kágdf`´\úZÄYWòV9W‹UaU6TkQµP•QQØQîR=R·SdV§V)UnT°U­WLWdVŒVŸV£V6VaUßTëUùVŠVÖU·U¬UV‡WÚW‹U÷S'TuT
TITÃU¤UTS[R%S`TÏTTâT
VUêTDU
TêRİROR¬QçQrRİRJSlSS_R†Q¬Q•QÎP1PQàQ QzQ?Q¸PXQ†QçQ°S²TuT›TmUÃUdTİRRP0O(OQO@N¿LÎL™L[KnIªFÒEËDå@S>—==ó<ó<B;Q86ß4’3l1%/..ú-~-‡,à**“)è' &c$ø"¦"3"!dœ8¸Šd?èD 	"$%£&,(K*J-ç/¨14G5"5V5Z5°5Y6‚6÷5Ç5d6*7i7õ7Ô6q5ä5;6.5w3ş1é0T0Q/M-Ş+w*Ù('G%<#ö!“ ,Öxöcû‰™å	ÉıÂyvÿŞı[ı4ü@ûrûmû“û²úÑúküÂü~ü§ü¾ü…ı¬şNOÉdøƒ¬Št»ådäğü¿;±ÿeş•şÅş-ı¢ûrû¶ú¨ù‡ùJùôø1ùù­øEø7÷fö[öùõönöö†õ±ô,óEñğïğ¹ï>ïéïëğ:ññ"ò¤òTóºópôö`ø®ú`üıùüSıüı•ş…ÿÃæÊ,(‚²ám§èCÿişbıCüSûëùİöô,óºñNğóîLíWëébè(çŸå»äaä£ãTã`ã®ã%ääìäÃäDäÅããŒãxä£ãÔâëâãÒâÆâ³ââˆá¼á#áğßŒßNà„á8âîãØåYçˆèléˆê‹ë ìCìâìëîÜğrñÈñîñ<òóõ±ônôRõönöŠ÷2øa÷"÷÷HöDö…öNõæóÙò¿òòàğ¶î^íìaë
êAèØçØç¶çşçèáææ<æ–æÒæ]çèèüèCé‡éÆéïésêë‡ëáëÊëmëÙë§ì¶ì§ì›ìÁìLí0îCî©í(î²îÉîfïÏï–ï¦ïNğ•ğ‚ğ‚ğüïıî¨îîÔîØîºîÑîøízì´ëpëIêpéyèRçOæîåÍåTåå¿ä·ä,åÅåæKæyæÈæç¨ç6èuèËèîè¼è%é
ê,êïé˜êxë¤ëéë£ì9í¼í~î>ï}ïéïğ?ğşğdñò
óÛó¦ôºõµöG÷Søùêøøä÷üöjöïõkõÎô¢ô“ôµôƒô«óVò¶ñòñˆñ¬ğ–ïÑîwîÑîïï#ïçîXî,î3îüíıìQìzì²ìíÉìÖë×ê.êşéAê˜êëÄêAêäé;é5éÎé¿éJéäéäé³é÷éêê»éFéaé¿é éçé6êXêùê¨ëTìÏìíïşğò°ò«ó?õ¢ö»÷¹øxùûù¶úõúû9ûüöü“ı¦ı1ıŸükü‘ü¾ü~üŠü£üùüıòü§üéû1û²úú°ù]ùnøt÷¦ökõLôŠóƒòrñÒğağğuïÍîÅîóîïaîVîÖíDíjí‡ífí‡íÊí¼íğíîîaîÚí©íkî:ïÛï|ğñ&òŸóxôğôÔõ÷Š÷:øù)ùZùÇùyúiû·ûÃû±û“û‡û[ûûÄúgú6úú-û|ûÇûüü@ûwúú»ùÀø7÷äõFõ?õRõÊôfôô0õ•õ~õøôHôxôíôğôÇôáô†õDöyöLöfö×ö™÷›ørøÉ÷ë÷ë÷o÷”öçõ²õö[ööÛöÃ÷ŸøeùZù1ù¬ù
úBúæúLûûiûû€û“û|ûaûÒûü,üı¼ı…ı+ıäüùü	ıÜü;ü[û&û¾ú(úÃùòøë÷~÷V÷V÷J÷_ö\õÎôxôjô×ówóoóÅófô‹ô¢ôéô¢ô†ó°ò9òÏñÈñºññÅğAñ#ñúğºñ)òˆññIñ£ñâñŸñ‚ğ­ï"ğ¬ğˆñ"ò&òòñòºñıñóEóÙò‚óxôåôJõSö‚÷ø"ù\úaûüûÃû­ûMüäüıPı>ı	ı#ı¢ıåıÒıåı,şwş{ş&şşíıSıÍüCüHûãúdúiùnøøx÷}ö`õpôêówóiò…ñ‘ğfï~î!îšíOíí»ìípí8í—ììñëì0ííŞìhííÔíî÷íWîéî3ï¡ïğxğ*ñÚñ=ò¨ò’óÙôö÷Qø5ùûùû0ü8ı@şÕşNÿ-1ÿ€[+€³.‚“!^îµ$Iy
"°æÿìşş ı;ü(û>ú¡ùìøuøø(÷šöqöÈõ¶ôô¦óóò5ò›ñçğEğï.ïÅîÁî¢î½îïyïÀïÅï6ğ©ğÿğpñ%òÄòó.ó{óéóQô¢ôSõëõö‰öW÷ø³øŒùpúdûîûKü­ü>ıùı°şQÿôÿuB!‡úL2óÒ£-Ú°vÿ.ÿÕşişşLıgüüpûÆúIúÖù+ù«ø3ø÷2÷ÿöóö°ögöoöuö]ö…öÕö÷ ÷/÷÷,÷G÷e÷¬÷
ø}øÌø=ù¼ùEúâúLûÁûwü)ı­ıOşCÿ˜½%· ®W®ìà³Šh"Æ‹@Ú]2ëÃ¥™ze"æÿ¢ÿiÿ/ÿ¡şBşçıwıı›ü‹üÑü¹ü–üüLü
ürû,ûIû7ûû9û®ûñûü;üWüüÆüØü
ı[ıyı£ışFşş
ÿ*ÿ(ÿKÿÿçÿA\l¡¬¼ÿâÇnyGìÿËÿ¡ÿWÿÿş¢şgşQş:ş@ş8şşÕı¾ı¶ı›ı‰ıqıwı‡ını\ıSıuıƒıƒı‰ı‹ı´ıüıJşzşş•ş×ş+ÿyÿ¸ÿçÿ7NduŒ¥Ëææ1%)*òïîìö÷şóÊj]U:Äÿÿrÿ>ÿùşÉş¦şqş$şııáıÁı¹ı¨ı‘ı†ıı‡ıı‹ı¨ıÅıÉıÔıñı$şSşoş‚şşÈşåşşşÿ(ÿUÿrÿ‰ÿÿ¹ÿêÿ%X}„ˆŸ­±½Èâ÷óèØÒÃ¤„hN1÷ÿìÿÜÿĞÿ½ÿ¢ÿ†ÿxÿiÿUÿ>ÿ/ÿ*ÿ#ÿ$ÿ ÿÿ#ÿ*ÿ/ÿ5ÿ;ÿCÿKÿNÿRÿVÿZÿaÿeÿmÿxÿ€ÿˆÿ‘ÿ ÿ«ÿ°ÿ¸ÿÄÿĞÿÛÿçÿóÿüÿ#)/311

*/