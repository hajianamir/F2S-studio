# Fire Protection Design & Simulation Platform | پلتفرم یکپارچه طراحی و شبیه‌سازی سیستم‌های حفاظت در برابر حریق

[English](#english) | [فارسی](#فارسی)

---

<a name="english"></a>
## English

An integrated, cloud-native, open-architecture platform for fire suppression (sprinkler/standpipe/water mist) and fire alarm system design, hydraulic calculation, rule compliance verification, and BIM/IFC integration.

### Core Features (MVP)
- **C++20 High-Performance Computational Core**:
  - Hazen-Williams and Darcy-Weisbach head loss equations.
  - Hardy Cross iterative loop solver for closed grid and looped fire networks.
  - Demand point analysis and operating point calculation against fire pump curves.
  - NFPA 72 NAC circuit voltage drop and battery backup duration calculator.
- **Rule Engine**:
  - Versioned NFPA standard compliance verification (e.g. `NFPA13-2022`, `NFPA72-2022`).
  - Pre-seeded with >=30 actionable design rules (spacing, pipe sizing, pressure limits, battery margins).
- **Backend API (.NET 8 ASP.NET Core)**:
  - Clean Architecture with CQRS pattern and OpenAPI 3.1 specifications.
  - P/Invoke interop layer with native C++ calculation engine.
  - Async job queue with status polling for long-running calculations.
  - IFC4 BIM model import/export (using xBIM Toolkit) and JSON schema network adapter.
- **Interactive 3D Web UI (React + Three.js + TypeScript)**:
  - WebGL 3D pipe network viewer with color-coded pressure heatmaps.
  - BCF-style 3D element annotation pinning.
  - Full English/Persian bilingual support with RTL mirroring and Vazirmatn typography.

### Quick Start
Build C++ Core and Run Tests:
  cd core && mkdir build && cd build && cmake .. && make && ctest

Run Backend (.NET 8):
  cd backend/src/Api && dotnet run

Run Frontend (React/Vite):
  cd web && npm install && npm run build

---

<a name="فارسی"></a>
## فارسی

پلتفرم یکپارچه و ابری برای طراحی، محاسبات هیدرولیک، بررسی انطباق با استانداردها و مدلسازی BIM سیستم‌های اعلام و اطفای حریق.

### قابلیت‌های اصلی (نسخه MVP)
- **هسته محاسباتی پرسرعت +C++20**:
  - محاسبات افت فشار Hazen-Williams و Darcy-Weisbach.
  - حل‌کننده حلقوی Hardy Cross برای شبکه‌های شبکه‌ای (Grid) و حلقه‌ای (Loop) اسپرینکلر.
  - تحلیل نقطه تقاضا و تعیین نقطه کارکرد پمپ آتش‌نشانی.
  - محاسبات افت ولتاژ مدار NAC و ظرفیت باتری مطابق NFPA 72.
- **موتور قوانین (Rule Engine)**:
  - ارزیابی انطباق نسخه به نسخه استانداردهای NFPA (شامل NFPA 13 نسخه ۲۰۲۲ و NFPA 72 نسخه ۲۰۲۲).
  - دارای حداقل ۳۰ قانون از پیش تعریف‌شده برای فاصله‌گذاری اسپرینکلرها، سایزینگ لوله‌ها و بارگذاری مدارها.
- **سرویس بک‌اند (NET 8.)**:
  - معماری پاک (Clean Architecture) مبتنی بر الگوی CQRS با مستندات OpenAPI 3.1.
  - ارتباط مستقیم و پرسرعت (P/Invoke) با هسته محاسباتی C++.
  - صف پردازش ناهمگام (Async Job Queue) برای محاسبات و پردازش فایل‌های سنگین BIM.
  - ورود و خروج فایل‌های BIM با فرمت IFC4 و JSON.
- **رابط کاربری وب سه‌بعدی (React + Three.js)**:
  - مشاهده‌گر سه‌بعدی WebGL با نقشه حرارتی (Heatmap) فشار و دبی.
  - قابلیت ثبت نشانه‌گذاری و کامنت‌گذاری سه‌بعدی (BCF Annotations).
  - پشتیبانی کامل دو زبانه (فارسی/انگلیسی) با چیدمان راست‌به‌چپ (RTL) و فونت وزیرمتن.
