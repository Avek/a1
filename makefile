#Assigment1s

rule:
	cc -o sem a1.c -lrt
	sem
	cat PROCTAB.txt
n:
	cc -o sem a1.c -lrt
	sem
	cat -n PROCTAB.txt
compile:
	cc -o sem a1.c -lrt
clean:
	rm PROCTAB.txt
	rm sem
