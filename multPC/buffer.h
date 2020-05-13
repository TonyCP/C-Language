/* Class buffer.h */

typedef int buff_item;
#define BUFF_SIZE 10
buff_item buffer[BUFF_SIZE];
int insert_item(buff_item item);
int remove_item(buff_item *item);

