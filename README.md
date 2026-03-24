

## Instructions to Builds Example

installation [instructions for AL2023](https://developer.arm.com/documentation/102620/2601/Installation).

```bash
sudo dnf config-manager --add-repo https://developer.arm.com/packages/arm-toolchains:amzn-2023/al2023/arm-toolchains:amzn-2023.repo
sudo dnf install arm-performance-libraries
sudo dnf install environment-modules

echo 'export MODULEPATH=$MODULEPATH:/opt/arm/modulefiles' >> ~/.bashrc
module load arm-performance-libs
```

```bash
# environment variables should be available
echo $ARMPL_DIR
```

## Command to build a staticly-linked binary 
```bash
make
```

To test special functions

```bash
g++ --std=c++20 vect.cpp test_special_functions.cpp -L$ARMPL_DIR/lib/ -I$ARMPL_INCLUDES -lamath -lm -larmpl_lp64 -o test_special && ./test_special

```