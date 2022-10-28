FLAGS = -Wall -ansi -pedantic
OBJS = manipulate_string.o base64.o b64.o
EXEC = b64

$(EXEC): $(OBJS)
	gcc $(FLAGS) -o $(EXEC) $(OBJS)
	
$(EXEC).o: main.c
	gcc $(FLAGS) -c main.c -o $(EXEC).o
	
base64.o: base64.c
	gcc $(FLAGS) -c base64.c

manipulate_string.o: manipulate_string.c
	gcc $(FLAGS) -c manipulate_string.c
	
clean:
	rm $(EXEC) *.o 
