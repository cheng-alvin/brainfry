all: libs/libjas brainfry

CFLAGS := -lstdc++ -I ./libs/libjas/include -L ./libs/libjas/lib

brainfry: brainfry.o
	clang $^ -o $@ $(CFLAGS) -O3 -ljas

# Note when compiling code: `all` target must be fulfilled before the 
# compilation of this target, otherwise dependant source files would be
# considered missing and fail.

brainfry_debug: brainfry.o
	clang $^ -o $@ $(CFLAGS) -g -ljas_debug

libs/libjas:
	git clone https://github.com/cheng-alvin/jas.git/ 
	mv jas libs/jas
	$(MAKE) -C libs/jas
	mv libs/jas/build libs/libjas
	rm -rf libs/jas

clean:
	rm -rf libs/
	rm -rf brainfry *.o 
	rm -rf jas
	mkdir -p libs

.PHONY: all clean
