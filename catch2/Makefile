BUILD_DIR = ./build
OPTIONS = -O2 -std=c++14 -pedantic -Wall -Wextra -I.

mini_jit: src/driver.cpp src/instructions/Base.cpp src/instructions/Asimd.cpp src/instructions/Sve.cpp src/backend/Kernel.cpp src/generators/Simple.cpp src/generators/Loop.cpp src/generators/Triad.cpp src/generators/SmallGemmSve.cpp src/generators/myExample.cpp src/benchmarks/SmallGemm.cpp
		g++ ${OPTIONS} -c src/instructions/Base.cpp -o ${BUILD_DIR}/instructions/Base.o
		g++ ${OPTIONS} -c src/instructions/Asimd.cpp -o ${BUILD_DIR}/instructions/Asimd.o
		g++ ${OPTIONS} -c src/instructions/Sve.cpp -o ${BUILD_DIR}/instructions/Sve.o
		g++ ${OPTIONS} -c src/backend/Kernel.cpp -o ${BUILD_DIR}/backend/Kernel.o
		g++ ${OPTIONS} -c src/generators/Simple.cpp -o ${BUILD_DIR}/generators/Simple.o
		g++ ${OPTIONS} -c src/generators/Loop.cpp -o ${BUILD_DIR}/generators/Loop.o
		g++ ${OPTIONS} -c src/generators/Triad.cpp -o ${BUILD_DIR}/generators/Triad.o
		g++ ${OPTIONS} -c src/generators/SmallGemmSve.cpp -o ${BUILD_DIR}/generators/SmallGemmSve.o
		g++ ${OPTIONS} -c src/generators/myExample.cpp -o ${BUILD_DIR}/generators/myExample.o
		g++ ${OPTIONS} -c src/benchmarks/SmallGemm.cpp -o ${BUILD_DIR}/benchmarks/SmallGemm.o

		g++ ${OPTIONS} src/driver.cpp ${BUILD_DIR}/instructions/Base.o \
		                              ${BUILD_DIR}/instructions/Asimd.o \
		                              ${BUILD_DIR}/instructions/Sve.o \
		                              ${BUILD_DIR}/backend/Kernel.o \
		                              ${BUILD_DIR}/generators/Simple.o \
		                              ${BUILD_DIR}/generators/Loop.o \
		                              ${BUILD_DIR}/generators/Triad.o \
		                              ${BUILD_DIR}/generators/SmallGemmSve.o \
		                              ${BUILD_DIR}/generators/myExample.o \
		                              ${BUILD_DIR}/benchmarks/SmallGemm.o \
		                              -o ${BUILD_DIR}/mini_jit

test: src/test.cpp src/driver.cpp src/instructions/Base.cpp src/instructions/Asimd.cpp src/instructions/Sve.cpp src/backend/Kernel.cpp src/generators/Simple.cpp src/generators/Loop.cpp src/generators/Triad.cpp src/instructions/Base.test.cpp src/instructions/Asimd.test.cpp src/instructions/Sve.test.cpp
		g++ ${OPTIONS} -c src/instructions/Base.cpp -o ${BUILD_DIR}/instructions/Base.o
		g++ ${OPTIONS} -c src/instructions/Base.test.cpp -o ${BUILD_DIR}/instructions/Base.test.o
		g++ ${OPTIONS} -c src/instructions/Asimd.cpp -o ${BUILD_DIR}/instructions/Asimd.o
		g++ ${OPTIONS} -c src/instructions/Asimd.test.cpp -o ${BUILD_DIR}/instructions/Asimd.test.o
		g++ ${OPTIONS} -c src/instructions/Sve.cpp -o ${BUILD_DIR}/instructions/Sve.o
		g++ ${OPTIONS} -c src/instructions/Sve.test.cpp -o ${BUILD_DIR}/instructions/Sve.test.o
		g++ ${OPTIONS} -c src/backend/Kernel.cpp -o ${BUILD_DIR}/backend/Kernel.o
		g++ ${OPTIONS} -c src/generators/Simple.cpp -o ${BUILD_DIR}/generators/Simple.o
		g++ ${OPTIONS} -c src/generators/Loop.cpp -o ${BUILD_DIR}/generators/Loop.o
		g++ ${OPTIONS} -c src/generators/Triad.cpp -o ${BUILD_DIR}/generators/Triad.o

		g++ ${OPTIONS} src/test.cpp ${BUILD_DIR}/instructions/Base.o \
		                            ${BUILD_DIR}/instructions/Base.test.o \
		                            ${BUILD_DIR}/instructions/Asimd.o \
		                            ${BUILD_DIR}/instructions/Asimd.test.o \
		                            ${BUILD_DIR}/instructions/Sve.o \
		                            ${BUILD_DIR}/instructions/Sve.test.o \
		                            ${BUILD_DIR}/backend/Kernel.o \
		                            ${BUILD_DIR}/generators/Simple.o \
		                            ${BUILD_DIR}/generators/Loop.o \
		                            ${BUILD_DIR}/generators/Triad.o \
		                            -o ${BUILD_DIR}/test

all: mini_jit test

$(shell mkdir -p build/backend)
$(shell mkdir -p build/instructions)
$(shell mkdir -p build/generators)
$(shell mkdir -p build/benchmarks)
