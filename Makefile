.ONESHELL:
all: libs/libjas/lib/libjas.a brainfry brainfry_debug

brainfry:
	clang -I ./libs/libjas/include brainfry.c -o $@ ./libs/libjas/lib/libjas.a -lstdc++ -Ofast  

# Apply custom build steps here: 
# (e.g patching, branch switching etc. where applicable)
libs/libjas/lib/libjas.a:
	git clone https://github.com/cheng-alvin/jas.git/ 
	cd ./jas && git fetch && git switch elf-rework 
	mv jas libs/jas
	$(MAKE) -C libs/jas
	mv libs/jas/build libs/libjas
	rm -rf libs/jas

jas/build/lib/libjas_debug.a:
	git clone https://github.com/cheng-alvin/jas.git/ 
	cd ./jas && git fetch && git switch elf-rework 
	$(MAKE) -C jas

# cd ./jas && git fetch && git switch elf-rework 
brainfry_debug: jas/build/lib/libjas_debug.a
	clang -I /jas/build/include brainfry.c -o $@ $< -lstdc++ -g

clean:
	rm -rf libs/
	rm -rf brainfry brainfry_debug *.o 
	rm -rf jas
	mkdir -p libs

.PHONY: all clean
