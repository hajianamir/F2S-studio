# مستندات API
**پلتفرم حفاظت در برابر حریق - راهنمای OpenAPI 3.1**

---

### مسیرهای اصلی (Endpoints)

#### `GET /api/health`
بررسی سلامت سرویس بک‌اند.

#### `POST /api/hydraulics/calculate`
ارسال درخواست محاسبات هیدرولیک به هسته C++.

#### `GET /api/jobs/{jobId}`
دریافت آخرین وضعیت و نتایج پردازش ناهمگام.

#### `GET /api/units/gpm-to-lpm?gpm={value}`
تبدیل واحد دبی از GPM به لیتر بر دقیقه.
