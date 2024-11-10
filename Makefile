brainfry: brainfry.c
	$(CC) -I ./libs/libjas/include brainfry.c -o $@ -L ./libs/libjas/lib -ljas -lstdc++ -g

# libs/libjas:
# 	cd libs
# 	git clone https://github.com/cheng-alvin/jas.git/ 
# 	$(MAKE) -C libs/jas
# 	mv libs/jas/build libs/libjas
# 	rm -rf libs/jas

clean:
	rm -rf brainfry *.o 
	mkdir -p libs

.PHONY: clean