all: cuda_mandel clean

cuda_mandel:
	@nvcc -o cuda_mandel cuda_mandel.cu -lpng

clean:
	@./cuda_mandel
	@rm -rf cuda_mandel
