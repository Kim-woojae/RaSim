CC = gcc
CFLAGS = -W -Wall
TARGET = RaSim

OBJECTS = main.o rasim.o message.o thing.o location.o sensor.o resource.o discovery.o scheduler.o link.o event.o role.o

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS)	-g -o	$@ $^ -lpthread -lm -lrt

clean :
	rm *.o RaSim