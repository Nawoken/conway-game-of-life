CC = gcc
CFLAGS = -g -std=c99 -Wall -I ./include

.PHONY: clean doc

doc:
	doxygen conf/doxygen.conf

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

compile-all: src/cell.c src/load.c src/generate-image.c src/app-conway.c
	$(CC) $(CFLAGS) -o $@ $^

generate-animation:
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif
	convert out/animation.gif -scale 800% out/animation.gif
	eog -f out/animation.gif

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	rm -f *.o read-file conway-naive write-fact
