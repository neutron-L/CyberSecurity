#include <stdio.h>
//
//void function(int a, int b, int c) {
//    char buffer[8];
//    int * r;
//    r = (int*) (buffer+16);
//    (*r) += 8;
//}
//
//int main() {
//    int x;
//    x= 0;
//    function(1,2,3);
//    x = 1;
//    printf("%d\n", x);
//    return 0;
//}
int main() {
    int num = 0x12345678;
    char * pc = (char*)&num;
    for (int i = 0; i < sizeof num; i++)
        printf("%p: %02x \n", pc, (unsigned char)*pc++);
    return 0;
}