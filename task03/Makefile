NVCC = nvcc
COMPILER_BIN = "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Tools\MSVC\14.42.34433\bin\Hostx64\x64"

NVCCFLAGS = -O3 -allow-unsupported-compiler -ccbin $(COMPILER_BIN) -Xcompiler "/W4 /WX" -arch=sm_86

TARGET = task03.exe

all: $(TARGET)

$(TARGET): main.cu matrix_ops.cu
	$(NVCC) $(NVCCFLAGS) main.cu matrix_ops.cu -o $(TARGET)

clean:
	del $(TARGET) *.lib *.exp *.obj