all: libs/libjas/lib/libjas.a brainfry brainfry_debug

brainfry:
	clang -I ./libs/libjas/include brainfry.c -o $@ -L ./libs/libjas/lib -ljas -lstdc++ -Ofast  

# Apply custom build steps here: 
# (e.g patching, branch switching etc. where applicable)
libs/libjas/lib/libjas.a:
	git clone https://github.com/cheng-alvin/jas.git/ 
	mv jas libs/jas
	$(MAKE) -C libs/jas
	mv libs/jas/build libs/libjas
	rm -rf libs/jas

brainfry_debug:
	clang -I ./libs/libjas/include brainfry.c -o $@ -L ./libs/libjas/lib -ljas_debug -lstdc++ -g

clean:
	rm -rf libs/
	rm -rf brainfry brainfry_debug *.o 
	mkdir -p libs

.PHONY: all clean
