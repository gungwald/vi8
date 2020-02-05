#include <stdio.h>   /* FILE, fopen, gets, fclose */
#include <stdbool.h> /* true, false */
#include <stdint.h>  /* uint8_t, uint16_t */
#include <conio.h>   /* screensize */

/* const */
#define MAX_BUF_LINE_LEN 100
#define MAX_BUF_LINES    400
#define INPUT_BUF_SIZE   256

/* type */
enum ReturnStatus {FAILURE, SUCCESS, EOF_REACHED};

struct BufferLine
{
    char text[MAX_BUF_LINE_LEN];
    uint8_t length;
};

struct Buffer 
{
    struct BufferLine lines[MAX_BUF_LINES];
    uint16_t length;
    uint8_t  cursorX;
    uint16_t cursorY;
};

/* function prototypes */
static void bInit(struct Buffer *b);
static void bOpen(struct Buffer *b, const char *name);
static void bAppendLine(struct Buffer *b, const char *name);

/* var */
struct Buffer b;
unsigned char screenWidth;
unsigned char screenHeight;
char fileInputBuffer[INPUT_BUF_SIZE];

void main()
{
    bInit(&b);
    screensize(&screenWidth, &screenHeight);
}

void bInit(struct Buffer *b)
{
    b->length = 0;
}

void bLoad(struct Buffer *b, const char *name)
{
        FILE *f;
        f = fopen(name, "r");
        if (f != NULL) {
                bRead(b, f);
                fclose(f);
        }
}

bool bIsFull(struct Buffer *b)
{
        return b->length >= MAX_BUF_LINES;
}

void bReadAll(struct Buffer *b, FILE *f)
{
        bInit(b);
        while (! bIsFull(b))
                bReadLine(b, f);
}

bool bReadLine(struct Buffer *b, FILE *f)
{
        int c;
        uint8_t i = 0;
        uint8_t lineIndex;
        char *text;
        struct BufferLine *line;

        lineIndex = b->length;
        line = b->lines[lineIndex];
        text = line.text;
        while (i < MAX_BUF_LINE_LEN && (c = getc(f)) != EOF && c != '\r')
                line[i++] = c;

        if (ferror(f))
                perror("Read failed");

        line.length = i;
        ++(b->length);
        return c != EOF;
}
