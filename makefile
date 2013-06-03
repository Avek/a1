#Assigment1s

rule:
	cc -o sem a1.c
semstuff:
	cc -o sem a1.c -lrt
	sem
	cat PROCTAB.txt
clean:
	rm PROCTAB.txt
	rm sem
