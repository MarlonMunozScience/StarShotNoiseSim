all: simulate testProbability

simulate: ./src/LaserCommNoise.cpp noise.o
	g++ -I./include -o simulate ./src/LaserCommNoise.cpp noise.o

testProbability: ./test/erasure_noise_test.cpp noise.o
	g++ -I./include -o testProbability ./test/erasure_noise_test.cpp noise.o

noise.o: ./src/noise.cpp
	g++ -I./include -c ./src/noise.cpp -o noise.o

clean: 
	rm simulate testProbability noise.o



