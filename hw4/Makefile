CC=gcc
TARGET1=main
TARGET2=mm

all:
	$(CC) $(TARGET1).c $(TARGET2).c -Wall -o $(TARGET1)

dep:
	$(CC) -MM $(TARGET1).c $(TARGET2).c > dep
	
clean:
	rm -f $(TARGET1)
	rm -f dep

	
