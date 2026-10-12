OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
calc: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.exe