CFLAGS := `pkg-config --cflags libxml-2.0`
LDFLAGS := `pkg-config --libs libxml-2.0` -lm -lz -llzma -licuuc -licudata

all: fp
	./fp

FILES := src/xml.o src/cli.o src/raw.o src/data.o

fp: $(FILES)
	$(CC) $(FILES) $(LDFLAGS) -o fp

clean:
	rm -rf src/*.o *.out fp
