# Laboratory work 1

Subject area: **botanical garden, variant 9**. The class `Plant` has four private
fields, a constructor, const accessors, and the meaningful method
`isOlderThan(int year) const`.

## Tool versions for the report

Run these commands in Terminal from the project folder:

```bash
clang++ --version
cmake --version
git --version
```

At the time of setup this Mac has Apple Clang 16.0.0, CMake 4.4.3 and Git 2.39.5.
The assignment asks for Clang 17 or newer, so Xcode / Command Line Tools need an
update before final submission.

## CMake build

```bash
cmake -S . -B build
cmake --build build
./build/Lab1
```

## Build with diagnostics and sanitizers

```bash
cmake -S . -B build-sanitized -DENABLE_SANITIZERS=ON
cmake --build build-sanitized
./build-sanitized/Lab1
```

## Xcode

The Xcode target is configured to use the `src` folder and C++17. Open
`Lab1.xcodeproj`, select the `Lab1` target and press Run. If files do not appear
immediately, close and re-open the project window.
