all: CPU_Benchmark Memory_Benchmark Disk_Benchmark

CPU_Benchmark: CPU_Benchmark.c
	gcc CPU_Benchmark.c -lm -pthread -o CPU_Benchmark -Ofast

Memory_Benchmark: Memory_Benchmark.c
	gcc Memory_Benchmark.c -lm -pthread -o Memory_Benchmark -Ofast

Disk_Benchmark: Disk_Benchmark.c
	gcc Disk_Benchmark.c -lm -pthread -o Disk_Benchmark -Ofast

run_all:
	./CPU_Benchmark
	./Memory_Benchmark
	./Disk_Benchmark

clean:
	rm -f CPU_Benchmark Memory_Benchmark Disk_Benchmark
