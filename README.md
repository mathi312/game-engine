# Game Engine

# Build

One option:

```bash
cmake -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Or in one command:

```bash
cmake --build build --target check --config Debug
```
