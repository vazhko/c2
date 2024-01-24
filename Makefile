TARGET = libC3.so 

.PHONY: all clean install

all: $(TARGET)
	
clean:
			rm -rf $(TARGET) *.*o

$(TARGET):  
			rm -rf *.*o
			gcc -lwiringPi -lm -D USE_WIRINGPI_LIB -g -O0 -Wall -c  -fpic *.c 
			gcc -shared -o libtest.so *.o
			sudo yes | sudo cp -rf libtest.so /usr/lib
			
install:
			sudo yes | sudo cp -rf libtest.so /usr/lib


			
