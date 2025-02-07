## **3️⃣ Build & Run**
### **🔨 Linux (Ubuntu)**
```sh
mkdir build && cd build
cmake ..
make -j$(nproc)
./MyGame
```

### **🖥 Windows (Using MinGW)**
```sh
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
MyGame.exe
```

---

## **4️⃣ Deployment for Windows**
If you're cross-compiling on **Ubuntu for Windows**, use MinGW:
```sh
sudo apt install mingw-w64
cmake -DCMAKE_TOOLCHAIN_FILE=../external/raylib/src/mingw-w64.toolchain.cmake ..
make -j$(nproc)
```
Then copy the required `.dll` files and package your game.

---

## **🔥 Why This Setup?**
✅ Uses **submodules** for clean dependency management  
✅ Works on **both Linux & Windows**  
✅ Keeps **header-only libraries simple** (no need to build them)  
✅ **Easy deployment** with `CMake`  

Would you like to add cross-compilation for Windows from Ubuntu? 🚀