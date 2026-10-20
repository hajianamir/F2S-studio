# راهنمای توسعه‌دهندگان

---

## پیش‌نیازها
- کامپایلر G++ نسخه ۱۳ به بالا (+C++20)
- CMake نسخه ۳.۲۰ به بالا
- .NET SDK نسخه ۸ یا ۱۰
- Node.js نسخه ۲۰ به بالا

## ساخت و اجرای تست‌های هسته C++
```bash
cd core
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```
