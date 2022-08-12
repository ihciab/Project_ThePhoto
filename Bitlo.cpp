#include "BitlO.h"
bool pushBit(BIT* buffer, const bool istrue) {
    if (buffer->p >= BITBUFFSIZE * 8)
        return EOF;
    else if (istrue)
        buffer->b[buffer->p >> SHIFT] |= 128u >> buffer->p % 8; //p所指位置填1
    else
        buffer->b[buffer->p >> SHIFT] &= ~(128u >> buffer->p % 8); //p所指位置填0
    buffer->p++;
    return istrue;
}
int fPushBit(BIT* buffer, FILE* fp) {
    memset(buffer, 0, sizeof(BIT));
    if (buffer->p = fread(buffer->b, sizeof(char), BITBUFFSIZE, fp) && feof(fp)) {
        buffer->p = (buffer->p - 2) * 8 + buffer->b[buffer->p - 1] + 1;
    }
    else
        buffer->p *= 8;
    return buffer->p;
}
int changeBit(BIT* buffer, const int istrue, const int position) {
    if (position >= buffer->p)
        return EOF;
    else if (istrue)
        buffer->b[position >> SHIFT] |= 128u >> position % 8;
    else
        buffer->b[position >> SHIFT] &= ~(128u >> position % 8);
    return istrue;
}
int readBit(BIT* buffer, const int position) {
    if (position >= buffer->p)
        return EOF;
    else
        return buffer->b[position >> SHIFT] & (128u >> position % 8);
}
int popBit(BIT* buffer) {
    if (buffer->p >= BITBUFFSIZE || buffer->p < 0)
        return EOF;
    buffer->p--;
    return buffer->b[(buffer->p + 1) >> SHIFT] & (128u >> (buffer->p + 1) % 8);
}
