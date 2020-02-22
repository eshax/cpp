/*
使用 mingw gcc 将二进制Blob嵌入到exe文件中

将 txt 文件打包成 .o 资源文件
ld -r -b binary -o binary.o input.txt

查看 .o 文件资源描述
objdump -x binary.o

_binary_input_txt_start
_binary_input_txt_end
_binary_input_txt_size

然后，C程序中访问它们：

#include <stdlib.h>
#include <stdio.h>

extern char binary_input_txt_start[];

int main (int argc, char *argv[])
{
    char *p;
    p = binary_input_txt_start;
    return 0;
}
*/

#include <stdlib.h>
#include <stdio.h>

extern char binary_input_txt_start;
extern char binary_input_txt_end;

int main ()
{
    char *p = &binary_input_txt_start;
	while ( p != &binary_input_txt_end ) putchar(*p++);
    return 0;
}