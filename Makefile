brainfry: brainfry.c
	$(CC) -I ./libs/libjas/include brainfry.c -o $@ -L ./libs/libjas/lib -ljas -lstdc++
