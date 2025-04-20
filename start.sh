cmake -B build \
    -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
    -DCMAKE_EXE_LINKER_FLAGS="-Wl,--rpath=/usr/lib/x86_64-linux-gnu" \
    -DCMAKE_PREFIX_PATH="/usr;/usr/lib/x86_64-linux-gnu" \
    -DCMAKE_LIBRARY_PATH="/usr/lib/x86_64-linux-gnu" \
    -DCMAKE_CXX_FLAGS="-isystem /usr/include -isystem /usr/include/c++/13"

  # Compiler en parallèle avec vérification
  if cmake --build build -j$(nproc); then
    strip build/bot
    echo "Build successful! Starting bot..."
    ./build/bot
  else
    echo "Build failed. Check CMake outputs."
    exit 1
  fi
