TARGET = mycpp 

.PHONY: all clean install

all: $(TARGET)
	
clean:
			rm -rf $(TARGET) *.*o

$(TARGET):  
			rm -rf *.*o
			g++ -lwiringPi -lm -D USE_WIRINGPI_LIB -g -O0 -Wall -c  main.cpp
			g++ -L../ -D USE_WIRINGPI_LIB -g -O0 -Wall -o mycpp main.o -ltest -lwiringPi -lm
			


			
