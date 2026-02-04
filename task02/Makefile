CXX = cl
CXXFLAGS = /W4 /WX /EHsc /std:c++17 

TARGET = matrix_add.exe

SRCS = main.cpp matrix_ops.cpp
OBJS = main.obj matrix_ops.obj

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) /Fe:$(TARGET)

clean:
	del /Q *.obj $(TARGET)