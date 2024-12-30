CFLAGS := -I/usr/include/libxml2
LDFLAGS := /usr/lib/x86_64-linux-gnu/libxml2.a -lm -lz -llzma -licuuc -licudata
all: fp
	./fp
fp: xml.o
	$(CC) xml.o $(LDFLAGS) -o fp
