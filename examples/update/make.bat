::::::::::::::::::::::::::::::::::::::::::::
:: 将 dll exe 等文件以资源文件的方式打包并嵌入到即将发布的 exe 文件中
:: 最终发布时 仅发布一个 exe 的文件即可, exe 在初次运行时会自动释放被打包的资源
::::::::::::::::::::::::::::::::::::::::::::

ld -r -b binary -o nssm.o nssm.exe --leading-underscore

ld -r -b binary -o libcurl.o libcurl.dll --leading-underscore
ld -r -b binary -o libssl32.o libssl32.dll --leading-underscore
ld -r -b binary -o libeay32.o libeay32.dll --leading-underscore

ld -r -b binary -o bat.o bat.exe --leading-underscore

ld -r -b binary -o install.o install.bat --leading-underscore

gcc -o main.exe main.c bat.o nssm.o libcurl.o install.o libssl32.o libeay32.o

rm *.o

pause