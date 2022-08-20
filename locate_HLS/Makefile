gcc: main.c top.c read.c 
	riscv64-unknown-elf-gcc -march=rv64gcv main.c top.c read.c -lm -o main
	spike pk main

clang: main.c top.c read.c
	clang --target=riscv64-unknown-elf -O2 -march=rv64gcv1p0 -menable-experimental-extensions -mllvm --riscv-v-vector-bits-min=256 --gcc-toolchain=$(RISCV) main.c top.c read.c -lm -o main
	spike --isa=rv64gcv --varch="vlen:4096,elen:64" pk main

llvm-objdump: main
	llvm-objdump --mattr=+v -S main > main.dump

riscv64-objdump: main
	riscv64-unknown-elf-objdump -d main > main.dump

clean:
	rm main main.dump
