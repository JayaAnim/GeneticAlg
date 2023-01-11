OBJS	= bruteForce.o main.o population.o tour.o tourManager.o
SOURCE	= bruteForce.cpp, main.cpp, population.cpp, tour.cpp, tourManager.cpp
HEADER	= bruteForce.h, population.h, tour.h, tourManager.h,
OUT	= a.out
LFLAGS	 = 

all: a.out

a.out: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)