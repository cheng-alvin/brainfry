all: clean libs/libjas brainfry

brainfry:
	clang -I ./libs/libjas/include brainfry.c -o $@ -L ./libs/libjas/lib -ljas -lstdc++ -g

libs/libjas:
	git clone https://github.com/cheng-alvin/jas.git/ 
	mv jas libs/jas
	$(MAKE) -C libs/jas
	mv libs/jas/build libs/libjas
	rm -rf libs/jas

clean:
	rm -rf libs/
	rm -rf brainfry *.o 
	mkdir -p libs

.PHONY: all clean
