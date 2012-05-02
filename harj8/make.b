EXEC1 = h8b1
EXEC2 = h8b2
all:	${EXEC1} ${EXEC2}

${EXEC1}:
	gcc -lrt ${EXEC1}.c -o ${EXEC1}

${EXEC2}:
	gcc -lrt ${EXEC2}.c -o ${EXEC2}

clean:
	rm -f *.txt ${EXEC1} ${EXEC2}
