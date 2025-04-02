/***********************************************************/
// 실습 1. MBR을 모델링하기 위한 구조체 타입 선언
/***********************************************************/
 
#pragma pack(push, 1)
 
/* MBR을 모델링하기 위한 구조체 타입 선언 */
typedef struct
{
    unsigned char boot_flag;
    unsigned char chs_start[3];
    unsigned char type;
    unsigned char chs_end[3];
    unsigned int lba_start;
    unsigned int size_in_sector;
}PTABLE;
typedef struct
{
    unsigned char boot_code[446];
    PTABLE ptable[4];
    unsigned short signature;
}MBR;
 
    /***********************************************************/
    // 실습 1. MBR 분석
    /***********************************************************/
 
    SD_Read_Sector(0, 1, (unsigned char *) buf);
 
    /* 다음 코드 작성시는 주석 처리 */
    //Sector_Uart_Printf(buf);
 
    /* MBR에서 첫번째 lba_start 값을 읽어서 parameter 구조체 멤버들에 저장  */
    parameter.lba_start = ((MBR*)buf)->ptable[0].lba_start;
 
    Uart_Printf("LBA_Start = %d\n", parameter.lba_start);
/**************************************************************
    Problem: 6979
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/

/***********************************************************/
// 실습 2. BR을 모델링하기 위한 구조체 타입 선언
/***********************************************************/
 
/* BR을 모델링하기 위한 구조체 타입 선언 */
typedef struct
{
    unsigned char jump_code[11];
    unsigned short byte_per_sector;
    unsigned char sector_per_cluster;
    unsigned short rsvd_sec_cnt;
    unsigned char no_of_fats;
    unsigned short root_entry_cnt;
    unsigned short total_sector;
    unsigned char rsvd;
    unsigned short fat16_size;
}BR;
 
 
    /***********************************************************/
    // 실습 2. BR 분석
    /***********************************************************/
 
    SD_Read_Sector(parameter.lba_start, 1, (unsigned char *) buf);
 
    /* 다음 코드 작성시는 주석 처리 */
    //Sector_Uart_Printf(buf);
 
    /* BR에서 정보들을 읽어서 parameter 구조체 멤버들에 저장 */
    parameter.byte_per_sector = ((BR*)buf)->byte_per_sector;
    parameter.sector_per_cluster = ((BR*)buf)->sector_per_cluster;
    parameter.fat0_start = parameter.lba_start + ((BR*)buf)->rsvd_sec_cnt;
    parameter.root_start = parameter.fat0_start + ((BR*)buf)->no_of_fats * ((BR*)buf)->fat16_size;
    parameter.root_sector_count = ((BR*)buf)->root_entry_cnt * 32 / parameter.byte_per_sector;
    parameter.file_start = parameter.root_start + parameter.root_sector_count;
 
    Uart_Printf("=============================================================\n");
    Uart_Printf("byte_per_sector = %d\n", parameter.byte_per_sector);
    Uart_Printf("sector_per_cluster = %d\n", parameter.sector_per_cluster);
    Uart_Printf("fat0_start = %d\n", parameter.fat0_start);
    Uart_Printf("root_start = %d\n", parameter.root_start);
    Uart_Printf("root_sector_count = %d\n", parameter.root_sector_count);
    Uart_Printf("file_start = %d\n", parameter.file_start);
    Uart_Printf("=============================================================\n");
/**************************************************************
    Problem: 6980
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 3. File Entry 분석을 위한 구조체, 공용체 타입 선언
/***********************************************************/
typedef struct
{
    unsigned char r : 1;
    unsigned char h : 1;
    unsigned char s : 1;
    unsigned char v : 1;
    unsigned char d : 1;
    unsigned char a : 1;
}fat_file;
typedef struct
{
    unsigned char ln : 4;
}long_file;
typedef union
{
    fat_file n;
    long_file l;
    unsigned char c;
}FILE_ATTR;
/* 시간 포맷을 위한 비트필드 구조체 선언 */
typedef struct
{
    unsigned short sec : 5;
    unsigned short min : 6;
    unsigned short hour : 5;
}FAT_TIME;
/* 날짜 포맷을 위한 비트필드 구조체 선언 */
typedef struct{
    unsigned short day : 5;
    unsigned short mon : 4;
    unsigned short year : 7;
}FAT_DATE;
/* 하나의 32B Entry 분석을 위한 구조체 => 아래 구조체는 이름을 바꾸지 말고 내용만 채워서 사용할 것 */
typedef struct
{
    unsigned char name[11];
    FILE_ATTR attr;
    unsigned char rsvd;
    unsigned char creation_time_tenth;
    FAT_TIME creation_time;
    FAT_DATE creation_date;
    FAT_DATE last_access_date;
    unsigned short first_cluster_high;
    FAT_TIME last_write_time;
    FAT_DATE last_write_date;
    unsigned short first_cluster_low;
    unsigned int file_size;
}ENTRY;
 
 
/***********************************************************/
// 실습 3. File Entry Listing
/***********************************************************/
void entry_print(int num, ENTRY* p)
{
    int i;
    Uart_Printf("[%03d]", num);
    for (i = 0; i < 8; i++) Uart_Printf("%c", p->name[i]);
    Uart_Printf(".");
    for (i = 8; i < 11; i++) Uart_Printf("%c", p->name[i]);
 
    Uart_Printf(" 0x%x", p->attr.c);
    Uart_Printf(" %04d/%02d/%02d", p->creation_date.year + 1980, p->creation_date.mon, p->creation_date.day);
    Uart_Printf(" %02d:%02d:%02d", p->creation_time.hour,
            p->creation_time.min, p->creation_time.sec * 2 + p->creation_time_tenth / 100);
    Uart_Printf(" %5d", p->first_cluster_low);
    Uart_Printf(" %8d\n", p->file_size);
}
static void listing_file(void)
{//root directory 만 리스팅함
    int i, j, num = 1;
 
    /* 타이틀 인쇄 => 임의 변경 가능 */
 
    Uart_Printf("[NUM] [NAME .EXT] [AT] [  DATE  ] [TIME] [CLUST] [ SIZE ]\n");
    Uart_Printf("=============================================================\n");
 
    for(i = 0; i < parameter.root_sector_count; i++)
    {
        SD_Read_Sector(parameter.root_start + i, 1, (unsigned char *)buf);
 
        for(j = 0; j < (parameter.byte_per_sector / 32); j++)
        {
            /* Name[0]가 0x0이면 인쇄 종료, 0x05, 0xE5이면 삭제파일 Skip */
            if (((ENTRY*)buf)[j].name[0] == 0x00) goto EXIT;
            if ((((ENTRY*)buf)[j].name[0] == 0x05) || (((ENTRY*)buf)[j].name[0] == 0xE5)) continue;
            /* 파일 속성이 0x3F 또는 0x0F long file name 이므로 Skip */
            if (((ENTRY*)buf)[j].attr.l.ln == 0xF) continue;
            /* Entry 정보 인쇄 */
            /* 인쇄되는 파일 또는 폴더 마다 맨 앞에 1번부터 1씩 증가하며 번호를 인쇄한다 */
            entry_print(num, &((ENTRY*)buf)[j]);
            num++;
        }
    }
EXIT:
    Uart_Printf("=============================================================\n");
}
/**************************************************************
    Problem: 6981
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 4. File Entry Search
/***********************************************************/
 
static ENTRY * search_file(int id)
{
    int i, j, num = 1;
 
    for(i = 0; i < parameter.root_sector_count; i++)
    {
        SD_Read_Sector(parameter.root_start + i, 1, (unsigned char *)buf);
 
        for(j = 0; j < (parameter.byte_per_sector / 32); j++)
        {
            /* Name[0]가 0x0이면 NULL 포인터 리턴, 0x05, 0xE5이면 Skip */
            if (((ENTRY*)buf)[j].name[0] == 0x00) goto EXIT1;
            if ((((ENTRY*)buf)[j].name[0] == 0x05) || (((ENTRY*)buf)[j].name[0] == 0xE5)) continue;
            /* 파일 속성이 0x3F 또는 0x0F long file name 이므로 Skip */
            if (((ENTRY*)buf)[j].attr.l.ln == 0xF) continue;
            /* 정상 Entry(파일, 폴더)일 경우 num이 원하는 ID인지 확인 */
            /* num이 id보다 작으면 num 증가만 하고 계속 탐색 반복, 같으면 Entry 시작 주소 리턴 */
            if (num == id) return &((ENTRY*)buf)[j];
            num++;
        }
    }
EXIT1:
    return (ENTRY *)0;
}
/**************************************************************
    Problem: 6983
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 5. File Type Check
/***********************************************************/
 
static int check_file_type(ENTRY * file)
{
    /* 리턴 값 : C 파일 => 1, TXT 파일 => 2, BMP 파일 => 3, 그외 => 0 리턴 */
    char * type[] = { "C  ", "TXT", "BMP" };
    int i;
 
    if (file->attr.n.d == 1) return 4;//디렉터리면 4리턴
 
    for (i = 0; i < sizeof(type)/sizeof(type[0]); i++)
    {
        if(strncmp(&file->name[8], type[i], 3) == 0) return i + 1;
    }
 
    return 0;
}
/**************************************************************
    Problem: 6984
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 6-1. TXT File Print => 1 Sector 이하 크기
/***********************************************************/
 
#define FAT_NUM_PER_SECTOR  (parameter.byte_per_sector/2)
 
#if 1
 
/* 1 Sector 이하 크기 TXT 파일을 인쇄하는 File_Printf 함수 */
/* TEST1.TXT */
 
static void File_Printf(ENTRY * file, char * data)
{
    // file size가 1 섹터 보다 크면 오류 메시지 인쇄 후 리턴
    // file size가 1 섹터 이하이면 파일 읽어서 for 루프로 인쇄
    // 글자수 만큼 for 루프에서 Uart1_Send_Byte();로 한 글자씩 인쇄
    // Uart1_Send_Byte() 함수 => char를 전달하면 UART에 인쇄함
    int i;
    int sector_num = parameter.file_start + (file->first_cluster_low - 2) * parameter.sector_per_cluster;
    if (file->file_size > parameter.byte_per_sector)
    {
        Uart_Printf("file size %d Byte > %d Byte Over!!\n", file->file_size, parameter.byte_per_sector);
        return;
    }
    SD_Read_Sector(sector_num, 1, data);
    for (i = 0; i < file->file_size; i++)
    {
        Uart1_Send_Byte(data[i]);
    }
    Uart_Printf("\n");
}
 
#endif
/**************************************************************
    Problem: 8300
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 6-2. TXT File Print => 1 Cluster 이하 크기
/***********************************************************/
 
#if 1
 
/* 1 Cluster 이하 크기 TXT 파일을 인쇄하는 File_Printf 함수 */
/* TEST2.TXT */
 
static void File_Printf(ENTRY * file, char * data)
{
    // file size가 1 클러스터 보다 크면 오류 메시지 인쇄 후 리턴
    // 섹터 번호를 증가시키면서 섹터를 읽어서 for 루프로 Uart1_Send_Byte(); 이용하여 인쇄
    // 주의 : 마지막 섹터의 파일 잔량이 섹터 크기 미만일 경우 파일 잔량 만큼만 루프로 인쇄해야 함
    int i, filesize = file->file_size, len;
    int sector_num = parameter.file_start + (file->first_cluster_low - 2) * parameter.sector_per_cluster;
    if (filesize > parameter.byte_per_sector * parameter.sector_per_cluster)
    {
        Uart_Printf("file size %d Byte > %d Byte Over!!\n", filesize, parameter.byte_per_sector * parameter.sector_per_cluster);
        return;
    }
    while (filesize > 0)
    {
        SD_Read_Sector(sector_num++, 1, data);
        len = (filesize > parameter.byte_per_sector) ? parameter.byte_per_sector : filesize;
        filesize -= len;
        for (i = 0; i < len; i++)
        {
            Uart1_Send_Byte(data[i]);
        }
    }
    Uart_Printf("\n");
}
 
#endif
/**************************************************************
    Problem: 8301
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 6-3. TXT File Print => 크기 제한 없음
/***********************************************************/
 
#if 01
 
/* 크기 제한이 없는 TXT 파일을 인쇄하는 File_Printf 함수 */
/* TEST3.TXT */
/* TEST4.TXT */
 
static void File_Printf(ENTRY * file, char * data)
{
    // 한 cluster 읽기가 끝나면 다음 cluster 번호 탐색하여 계속 읽기 진행
    // 마지막 cluster의 마지막 섹터에 섹터 크기 이하 잔량이 있을 경우 잔량 만큼만 루프로 인쇄해야 함
    int i, filesize = file->file_size, len;
    unsigned short c_no = file->first_cluster_low, c_count = 0;
    int fat_idx = parameter.fat0_start + (c_no / FAT_NUM_PER_SECTOR), back = 0;
    int sector_num = parameter.file_start + (c_no - 2) * parameter.sector_per_cluster;
    while (filesize > 0)
    {
        SD_Read_Sector(sector_num++, 1, data);
        len = (filesize > parameter.byte_per_sector) ? parameter.byte_per_sector : filesize;
        filesize -= len;
        for (i = 0; i < len; i++)
        {
            Uart1_Send_Byte(data[i]);
        }
        if (filesize && (++c_count == parameter.sector_per_cluster))
        {
            c_count = 0;
            if (fat_idx != back)
            {
                back = fat_idx;
                SD_Read_Sector(fat_idx, 1, buf);
            }
            c_no = ((unsigned short *)buf)[c_no % FAT_NUM_PER_SECTOR];
            sector_num = parameter.file_start + parameter.sector_per_cluster * (c_no - 2);
            fat_idx = parameter.fat0_start + (c_no / FAT_NUM_PER_SECTOR);
        }
    }
    Uart_Printf("\n");
}
 
#endif
/**************************************************************
    Problem: 8302
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


// mine
/***********************************************************/
// 실습 1. MBR을 모델링하기 위한 구조체 타입 선언
/***********************************************************/
 
#pragma pack(push, 1)
 
/* MBR을 모델링하기 위한 구조체 타입 선언 */
typedef struct {
    unsigned char boot_flag;
    unsigned char chs_start[3];
    unsigned char type;
    unsigned char chs_end[3];
    unsigned int lba_start;
    unsigned int size_in_sector;
}PTABLE;
typedef struct {
    unsigned char bootcode[446];
    PTABLE partition[4];
    unsigned short signature;
}MBRHDR;

     /***********************************************************/
    // 실습 2. BR 분석
    /***********************************************************/
 
    SD_Read_Sector(parameter.lba_start, 1, (unsigned char *) buf);
 
    /* 다음 코드 작성시는 주석 처리 */
    //Sector_Uart_Printf(buf);
 
    /* BR에서 정보들을 읽어서 parameter 구조체 멤버들에 저장 */
    parameter.byte_per_sector = ((struct _parameter *)buf)->byte_per_sector;
    parameter.sector_per_cluster = ((struct _parameter *)buf)->sector_per_cluster;
    parameter.fat0_start = ((struct _parameter *)buf)->fat0_start;
    parameter.root_start = ((struct _parameter *)buf)->root_start;
    parameter.root_sector_count = ((struct _parameter *)buf)->root_sector_count;
    parameter.file_start = ((struct _parameter *)buf)->file_start;
/**************************************************************
    Problem: 6980
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/
 
void FAT16_Test(void)
{
    int i;
 
    Uart_Printf("\nSD FAT16 File Read\n");
 
    /***********************************************************/
    // 실습 1. MBR 분석
    /***********************************************************/
 
    SD_Read_Sector(0, 1, (unsigned char *) buf);    // 0번 sector read
 
    /* 다음 코드 작성시는 주석 처리 */
    //Sector_Uart_Printf(buf);
 
    /* MBR에서 첫번째 lba_start 값을 읽어서 parameter 구조체 멤버들에 저장  */
    parameter.lba_start = ((MBRHDR *)buf)->partition[0].lba_start;
 
    Uart_Printf("LBA_Start = %d\n", parameter.lba_start);
 
/**************************************************************
    Problem: 6979
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


static void File_Printf(ENTRY * file, char * data)
{
    // file size가 1 클러스터 보다 크면 오류 메시지 인쇄 후 리턴
    // 섹터 번호를 증가시키면서 섹터를 읽어서 for 루프로 Uart1_Send_Byte(); 이용하여 인쇄
    // 주의 : 마지막 섹터의 파일 잔량이 섹터 크기 미만일 경우 파일 잔량 만큼만 루프로 인쇄해야 함
    int i,j;
    int sector_num = parameter.file_start + ( file->first_cluster_low -2) * parameter.sector_per_cluster;
    int total_size = file->file_size;
    int read_size = ( total_size > parameter.byte_per_sector) ? parameter.byte_per_sector : file->file_size;
    int loop = file->file_size / parameter.byte_per_sector + 1;
 
    if( file->file_size > parameter.byte_per_sector * parameter.sector_per_cluster ) {
        Uart_Printf("%d Byte : %d Byte Over !\n", file->file_size, parameter.byte_per_sector);
    }
 
    //Uart_Printf("(%d) [%d][%d]\n", loop, sector_num, read_size);
    for(i = 0; i < loop; i++)
    {
        SD_Read_Sector(sector_num, 1, data);
        for( j=0; j< read_size; j++)
        {
            Uart_Send_Byte(data[j]);
        }
 
        sector_num += 1;//parameter.sector_per_cluster;
        total_size -= read_size;
        read_size = ( total_size > parameter.byte_per_sector) ? parameter.byte_per_sector : total_size;
        //Uart_Printf("\n----(%d) [%d][%d]{%d]\n", i,  sector_num, read_size, total_size);
    }
    Uart_Printf("\n");
}
/**************************************************************
    Problem: 8301
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/

static void File_Printf(ENTRY * file, char * data)
{
    // 한 cluster 읽기가 끝나면 다음 cluster 번호 탐색하여 계속 읽기 진행
    // 마지막 cluster의 마지막 섹터에 섹터 크기 이하 잔량이 있을 경우 잔량 만큼만 루프로 인쇄해야 함
 
    int cur_cluster = file->first_cluster_low;
    int nxt_cluster;
 
    // 클러스터 내부 loop
    int i,j;
    int sector_num; // = parameter.file_start + ( cur_cluster -2) * parameter.sector_per_cluster;
    // parameter.byte_per_sector : 512
    // parameter.sector_per_cluster : 32
 
    int total_size = file->file_size;
    int read_size = ( total_size > parameter.byte_per_sector) ? parameter.byte_per_sector : file->file_size;
    int total_loop = file->file_size / parameter.byte_per_sector + 1;
    int loop;
 
    //Uart_Printf("cur cluster = %d\n", cur_cluster);
    do {
        //Uart_Printf("cur cluster = %d\n", cur_cluster);
        sector_num = parameter.file_start + ( cur_cluster -2) * parameter.sector_per_cluster;
 
        if( total_loop > parameter.sector_per_cluster) loop = parameter.sector_per_cluster;
        else loop = total_loop;
        total_loop -= parameter.sector_per_cluster;
 
        for(i = 0; i < loop; i++)        // sector 만큼 반복
        {
            SD_Read_Sector(sector_num, 1, data);
            for( j=0; j< read_size; j++)
            {
                Uart_Send_Byte(data[j]);
            }
 
                sector_num += 1;;
        }
 
        nxt_cluster = cur_cluster / 256;
        sector_num = parameter.fat0_start + nxt_cluster;
        SD_Read_Sector(sector_num, 1, data);
        cur_cluster = ((unsigned short *)data)[cur_cluster%256];
    } while( cur_cluster != 0xFFFF );
 
    Uart_Printf("\n");
 
}
/**************************************************************
    Problem: 8302
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/
