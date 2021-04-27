all:  clean main

main:
	cl /o ADS_Coursework_40432878 main.c games.c

tests:
	cl /o ADS_CWK_Tests tests.c games.c

clean:
	del *.exe
	del *.obj
	del *.asm