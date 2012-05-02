EXEC1 = h15_1
EXEC2 = h15_2
all:	${EXEC1} ${EXEC2}

${EXEC1}:
	gcc -lrt h15_1.c -o ${EXEC1}

${EXEC2}:
	gcc -lrt h15_2.c -o ${EXEC2}

clean:
	rm -f *.txt ${EXEC1} ${EXEC2}
