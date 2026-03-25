generate: clean
	cmake -S . -B build -DUSE_APL=1 -DBUILD_TESTS=1

build: generate
	cd build && cmake --build . --target all

clean:
	rm -rf ./build/*
