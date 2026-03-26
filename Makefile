generate: clean
	cmake -S . -B build -DUSE_APL=1 -DBUILD_TESTS=1

build: generate
	cd build && cmake --build . --target all

clean:
	rm -rf ./build*

build-all-configs:
	@set -e; \
	for use_apl in 0 1; do \
	  for build_tests in 0 1; do \
	    build_dir="build-$${use_apl}-$${build_tests}"; \
	    printf "USE_APL=%s BUILD_TESTS=%s ... " "$$use_apl" "$$build_tests"; \
	    if cmake -S . -B "$$build_dir" \
	         -DUSE_APL=$$use_apl \
	         -DBUILD_TESTS=$$build_tests \
	         > /dev/null 2>&1 && \
	       cmake --build "$$build_dir" --target all -- -s \
	         > /dev/null 2>&1; then \
	      echo "OK"; \
	    else \
	      echo "FAILED"; \
	      exit 1; \
	    fi; \
	  done; \
	done

run-all-binaries:
	@failed=0; \
	for dir in build-0-0 build-0-1 build-1-0 build-1-1; do \
	  [ -d "$$dir" ] || continue; \
	  for bin in \
	    "$$dir/src/main" \
	    "$$dir/src/main_with_apl" \
	    "$$dir/tests/generate_visualization_baseline" \
	    "$$dir/tests/generate_visualization_with_apl" \
	    "$$dir/tests/sweep_microbench_baseline" \
	    "$$dir/tests/sweep_microbench_with_apl"; do \
	    [ -x "$$bin" ] || continue; \
	    printf "RUN   %s ... " "$$bin"; \
	    if "$$bin" > /dev/null 2>&1; then \
	      echo "OK"; \
	    else \
	      echo "FAILED"; \
	      failed=1; \
	    fi; \
	  done; \
	done; \
	exit $$failed

check-all: clean build-all-configs run-all-binaries