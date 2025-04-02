/***********************************************************/
// 실습 1. BMP 헤더, DIB 모델링
/***********************************************************/
 
#pragma pack(push, 2)
 
// 필요시 추가적인 구조체, 공용체 등 설계
 
typedef struct
{
    unsigned char magic_num[2];
    unsigned int bmpfile_size;
    unsigned short rsvd1;
    unsigned short rsvd2;
    unsigned int offset;
    unsigned int DIB_size;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes_num;
    unsigned short bpp;
    unsigned int compression;
    unsigned int image_size;
    unsigned int horizontal;
    unsigned int vertical;
    unsigned int color_num;
    unsigned int important_num;
}BMP_HDR;
 
#pragma pack(pop)
/**************************************************************
    Problem: 6975
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 2. BMP 파일 정보 인쇄
/***********************************************************/
 
#define BMP_FILE        ((BMP_HDR *)fp)
 
void Lcd_Print_BMP_Info(void * fp)
{
    // 코드 작성
    // 필요시 변수나 코드 설계
#if 01
    Uart_Printf("MAGIC = %c%c\n", BMP_FILE->magic_num[0], BMP_FILE->magic_num[1]);
    Uart_Printf("BMP SIZE = %d\n", BMP_FILE->bmpfile_size);
    Uart_Printf("RAW OFFSET = %d\n", BMP_FILE->offset);
    Uart_Printf("DIB SIZE = %d\n", BMP_FILE->DIB_size);
    Uart_Printf("WIDTH = %d, HEIGHT = %d\n", BMP_FILE->width, BMP_FILE->height);
    Uart_Printf("BPP = %d\n", BMP_FILE->bpp);
#endif
}
/**************************************************************
    Problem: 6976
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/

/***********************************************************/
// 실습 4. Lcd_Draw_BMP_File_24bpp 함수 설계
/***********************************************************/
typedef struct
{
    unsigned char : 3;
    unsigned char b : 5;
    unsigned char : 2;
    unsigned char g : 6;
    unsigned char : 3;
    unsigned char r : 5;
}ORG_24BPP;
typedef union
{
    unsigned short data;
    struct
    {
        unsigned short b : 5;
        unsigned short g : 6;
        unsigned short r : 5;
    }pix;
}CONV_565;
void Lcd_Draw_BMP_File_24bpp(int x, int y, void * fp)
{
    int width = BMP_FILE->width;
    int height = BMP_FILE->height;
    int xx, yy;
    unsigned char *pix = (unsigned char *)fp + BMP_FILE->offset;
    for(yy = height-1; yy >= 0; yy--)
    {
        for (xx = 0; xx < width; xx++)
        {
            CONV_565 dst;
            dst.pix.b = ((ORG_24BPP*)pix)[xx].b;
            dst.pix.g = ((ORG_24BPP*)pix)[xx].g;
            dst.pix.r = ((ORG_24BPP*)pix)[xx].r;
            Lcd_Put_Pixel(xx, yy, dst.data);
        }
 
        pix += width * sizeof(ORG_24BPP);
    }
}
/**************************************************************
    Problem: 8297
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 4. Lcd_Draw_BMP_File_24bpp 함수 설계
/***********************************************************/
typedef struct
{
    unsigned char : 3;
    unsigned char b : 5;
    unsigned char : 2;
    unsigned char g : 6;
    unsigned char : 3;
    unsigned char r : 5;
}ORG_24BPP;
typedef union
{
    unsigned short data;
    struct
    {
        unsigned short b : 5;
        unsigned short g : 6;
        unsigned short r : 5;
    }pix;
}CONV_565;
void Lcd_Draw_BMP_File_24bpp(int x, int y, void * fp)
{
    int width = BMP_FILE->width;
    int height = BMP_FILE->height;
    int xx, yy;
    unsigned char *pix = (unsigned char *)fp + BMP_FILE->offset;
    for(yy = height-1; yy >= 0; yy--)
    {
        for (xx = 0; xx < width; xx++)
        {
            CONV_565 dst;
            dst.pix.b = ((ORG_24BPP*)pix)[xx].b;
            dst.pix.g = ((ORG_24BPP*)pix)[xx].g;
            dst.pix.r = ((ORG_24BPP*)pix)[xx].r;
            Lcd_Put_Pixel(x + xx, y + yy, dst.data);
        }
 
        pix += width * sizeof(ORG_24BPP);
    }
}
/**************************************************************
    Problem: 8298
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/


/***********************************************************/
// 실습 4. Lcd_Draw_BMP_File_24bpp 함수 설계
/***********************************************************/
typedef struct
{
    unsigned char : 3;
    unsigned char b : 5;
    unsigned char : 2;
    unsigned char g : 6;
    unsigned char : 3;
    unsigned char r : 5;
}ORG_24BPP;
typedef union
{
    unsigned short data;
    struct
    {
        unsigned short b : 5;
        unsigned short g : 6;
        unsigned short r : 5;
    }pix;
}CONV_565;
void Lcd_Draw_BMP_File_24bpp(int x, int y, void * fp)
{
    int width = BMP_FILE->width;
    int height = BMP_FILE->height;
    int xx, yy;
    unsigned char *pix = (unsigned char *)fp + BMP_FILE->offset;
    int pad = (4 - width * sizeof(ORG_24BPP) % 4) % 4;
    for(yy = height-1; yy >= 0; yy--)
    {
        for (xx = 0; xx < width; xx++)
        {
            CONV_565 dst;
            dst.pix.b = ((ORG_24BPP*)pix)[xx].b;
            dst.pix.g = ((ORG_24BPP*)pix)[xx].g;
            dst.pix.r = ((ORG_24BPP*)pix)[xx].r;
            Lcd_Put_Pixel(x + xx, y + yy, dst.data);
        }
 
        pix += width * sizeof(ORG_24BPP) + pad;
    }
}
/**************************************************************
    Problem: 8299
    Language: Bash
    Result: Accepted
    Time:0 ms
    Memory:0 kb
****************************************************************/
