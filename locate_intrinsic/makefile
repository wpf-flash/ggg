clang: intrinsic_MatrixMul_int32.c
	clang --target=riscv64-unknown-elf -O2 -march=rv64gcv1p0 -menable-experimental-extensions -mllvm --riscv-v-vector-bits-min=256 --gcc-toolchain=/home/wpf/RISCV-software intrinsic_MatrixMul_int32.c -lm -o main
	spike --isa=rv64gcv --varch="vlen:512,elen:64" pk main #elen的值要和前面isa的位宽一致
llvm-objdump: main
	llvm-objdump --mattr=+v -S main > main.dump

clean:
	rm main main.dump