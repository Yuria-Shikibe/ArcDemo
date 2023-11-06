// ReSharper disable CppInconsistentNaming
// ReSharper disable IdentifierTypo
// ReSharper disable CppClangTidyClangDiagnosticImplicitIntFloatConversion
// ReSharper disable CppClangTidyBugproneNarrowingConversions
// ReSharper disable CppClangTidyClangDiagnosticFloatEqual
// ReSharper disable CppClangTidyClangDiagnosticDoublePromotion

#include "Color.h"

#include "convert.h"
Graphic::Color::Color() = default;

Graphic::Color::Color(const colorBits rgba8888V){
	rgba8888(rgba8888V);
}

Graphic::Color::~Color(){
	setForce(NAN, NAN, NAN, NAN);
}

Graphic::Color::Color(const float tr, const float tg, const float tb, const float ta){
	r = tr;
	g = tg;
	b = tb;
	a = ta;
	clamp();
}

Graphic::Color::Color(const float r, const float g, const float b): Color(r, g, b, 1){}

Graphic::Color::Color(Color&& color) noexcept{
	set(color);
}

Graphic::Color::Color(const Color& other) = default;

Graphic::Color& Graphic::Color::operator=(const Color& other){
	if (this == &other) return *this;
	return set(other);  // NOLINT(misc-unconventional-assign-operator)
}

Graphic::Color& Graphic::Color::operator=(Color&& other) noexcept{
	if (this == &other) return *this;
	return set(other);  // NOLINT(misc-unconventional-assign-operator)
}

std::size_t Graphic::Color::hash_value(const Color& obj) const{
	return hashCode();
}

void Graphic::swap(Color& lhs, Color& rhs) noexcept{
	using std::swap;
	swap(lhs.r, rhs.r);
	swap(lhs.g, rhs.g);
	swap(lhs.b, rhs.b);
	swap(lhs.a, rhs.a);
}

std::ostream& Graphic::operator<<(std::ostream& os, const Color& obj){
	return os << obj.toString();
}

bool Graphic::operator==(const Color& lhs, const Color& rhs){
	return lhs.equals(rhs);
}

bool Graphic::operator!=(const Color& lhs, const Color& rhs){
	return !(lhs.equals(rhs));
}

Graphic::Color& Graphic::Color::valueOf(const std::string& hex){
	Color c{};
	return valueOf(c, hex);
}

Graphic::Color& Graphic::Color::valueOf(Color& color, const std::string& hex){
	const int offset = hex[0] == '#' ? 1 : 0;

	const int r = parseHex(hex, offset, offset + 2);
	const int g = parseHex(hex, offset + 2, offset + 4);
	const int b = parseHex(hex, offset + 4, offset + 6);
	const int a = hex.length() - offset != 8 ? 255 : parseHex(hex, offset + 6, offset + 8);
	return color.set(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f);
}

int Graphic::Color::parseHex(const std::string& string, const int from, const int to){
	int total = 0;
	for (int i = from; i < to; i++) {
		total += charToDigitValue(string[i], 16) * (i == from ? 16 : 1);
	}
	return total;
}

float Graphic::Color::toFloatBits(const int r, const int g, const int b, const int a){
	const int color = (a << 24) | (b << 16) | (g << 8) | r;
	return intToFloatColor(color);
}

float Graphic::Color::toFloatBits(const float r, const float g, const float b, const float a){
	const int color = (static_cast<int>(255 * a) << 24) | (static_cast<int>(255 * b) << 16) | (static_cast<int>(255 * g) << 8) | static_cast<int>(255 * r);
	return intToFloatColor(color);
}

double Graphic::Color::toDoubleBits(const float r, const float g, const float b, const float a){
	return longBitsToDouble(rgba8888(r, g, b, a) & INT_MASK_BACK);
}

double Graphic::Color::toDoubleBits(const int r, const int g, const int b, const int a){
	return toDoubleBits(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

Graphic::Color& Graphic::Color::fromDouble(const double value){
	return rgba8888(static_cast<int>(doubleToUnsignedLongBits(value)));
}

Graphic::Color::colorBits Graphic::Color::abgr(const int tr, const int tg, const int tb, const int ta){
	return (ta << 24) | (tb << 16) | (tg << 8) | tr;
}

Graphic::Color::colorBits Graphic::Color::alpha(const float alpha){
	return static_cast<colorBits>(alpha * 255.0f);
}

Graphic::Color::colorBits Graphic::Color::luminanceAlpha(const float luminance, const float alpha){
	return (static_cast<colorBits>(luminance * 255.0f) << 8) | static_cast<colorBits>(alpha * 255.0f);
}

Graphic::Color::colorBits Graphic::Color::rgb565(const float r, const float g, const float b){
	return (static_cast<colorBits>(r * 31) << 11) | (static_cast<colorBits>(g * 63) << 5) | static_cast<colorBits>(b * 31);
}

Graphic::Color::colorBits Graphic::Color::rgba4444(const float r, const float g, const float b, const float a){
	return (static_cast<colorBits>(r * 15) << 12) | (static_cast<colorBits>(g * 15) << 8) | (static_cast<colorBits>(b * 15) << 4) | static_cast<colorBits>(a * 15);
}

Graphic::Color::colorBits Graphic::Color::rgb888(const float r, const float g, const float b){
	return (static_cast<colorBits>(r * 255) << 16) | (static_cast<colorBits>(g * 255) << 8) | static_cast<colorBits>(b * 255);
}

Graphic::Color::colorBits Graphic::Color::rgba8888(const float r, const float g, const float b, const float a){
	return (static_cast<colorBits>(r * 255) << 24) | (static_cast<colorBits>(g * 255) << 16) | (static_cast<colorBits>(b * 255) << 8) | static_cast<colorBits>(a * 255);
}

Graphic::Color::colorBits Graphic::Color::argb8888(const float a, const float r, const float g, const float b){
	return (static_cast<colorBits>(a * 255) << 24) | (static_cast<colorBits>(r * 255) << 16) | (static_cast<colorBits>(g * 255) << 8) | static_cast<colorBits>(b * 255);
}

int Graphic::Color::packRgba(const int r, const int g, const int b, const int a){
	return (r << 24) | (g << 16) | (b << 8) | (a);
}

Graphic::Color::colorBits Graphic::Color::rgb565() const{
	return (static_cast<colorBits>(r * 31) << 11) | (static_cast<colorBits>(g * 63) << 5) | static_cast<colorBits>(b * 31);
}

Graphic::Color::colorBits Graphic::Color::rgba4444() const{
	return (static_cast<colorBits>(r * 15) << 12) | (static_cast<colorBits>(g * 15) << 8) | (static_cast<colorBits>(b * 15) << 4) | static_cast<colorBits>(a * 15);
}

Graphic::Color::colorBits Graphic::Color::rgb888() const{
	return (static_cast<colorBits>(r * 255) << 16) | (static_cast<colorBits>(g * 255) << 8) | static_cast<colorBits>(b * 255);
}

Graphic::Color::colorBits Graphic::Color::rgba8888() const{
	return (static_cast<colorBits>(r * 255) << 24) | (static_cast<colorBits>(g * 255) << 16) | (static_cast<colorBits>(b * 255) << 8) | static_cast<colorBits>(a * 255);
}

Graphic::Color::colorBits Graphic::Color::argb8888() const{
	return (static_cast<colorBits>(a * 255) << 24) | (static_cast<colorBits>(r * 255) << 16) | (static_cast<colorBits>(g * 255) << 8) | static_cast<colorBits>(b * 255);
}

Graphic::Color& Graphic::Color::rgb565(const colorBits value){
	r = ((value & 0x0000F800) >> 11) / 31.0f;
	g = ((value & 0x000007E0) >> 5) / 63.0f;
	b = ((value & 0x0000001F)) / 31.0f;
	return *this;
}

Graphic::Color& Graphic::Color::rgba4444(const colorBits value){
	r = ((value & 0x0000f000) >> 12) / 15.0f;
	g = ((value & 0x00000f00) >> 8) / 15.0f;
	b = ((value & 0x000000f0) >> 4) / 15.0f;
	a = ((value & 0x0000000f)) / 15.0f;
	return *this;
}

Graphic::Color& Graphic::Color::rgb888(const colorBits value){
	r = ((value & 0x00ff0000) >> 16) / 255.0f;
	g = ((value & 0x0000ff00) >> 8) / 255.0f;
	b = ((value & 0x000000ff)) / 255.0f;
	return *this;
}

Graphic::Color& Graphic::Color::rgba8888(const colorBits value){
	r = ((value & 0xff000000) >> 24) / 255.0f;
	g = ((value & 0x00ff0000) >> 16) / 255.0f;
	b = ((value & 0x0000ff00) >> 8) / 255.0f;
	a = ((value & 0x000000ff)) / 255.0f;
	return *this;
}

Graphic::Color& Graphic::Color::argb8888(const colorBits value){
	a = ((value & 0xff000000) >> 24) / 255.0f;
	r = ((value & 0x00ff0000) >> 16) / 255.0f;
	g = ((value & 0x0000ff00) >> 8) / 255.0f;
	b = ((value & 0x000000ff)) / 255.0f;
	return *this;
}

Graphic::Color& Graphic::Color::abgr8888(const float value){
	const unsigned int c = floatToIntColor(value);
	a = ((c & 0xff000000) >> 24) / 255.0f;
	b = ((c & 0x00ff0000) >> 16) / 255.0f;
	g = ((c & 0x0000ff00) >> 8) / 255.0f;
	r = ((c & 0x000000ff)) / 255.0f;
	return *this;
}

Graphic::Color Graphic::Color::grays(const float value){
	return Color{ value, value, value };
}

Graphic::Color Graphic::Color::rgb(const int r, const int g, const int b){
	return Color{ (r / 255.0f), (g / 255.0f), (b / 255.0f) };
}

unsigned Graphic::Color::floatToIntColor(const float value){
	colorBits intBits = floatToUnsignedIntBits(value);
	intBits |= static_cast<colorBits>((intBits >> 24) * (255.0f / 254.0f)) << 24;
	return intBits;
}

float Graphic::Color::intToFloatColor(const int value){
	return intBitsToFloat(value & 0xfeffffff);
}

float Graphic::Color::diff(const Color& other) const {
	return abs(hue() - other.hue()) / 360 + abs(value() - other.value()) + abs(saturation() - other.saturation());
}

int Graphic::Color::rgba() const{
	return rgba8888();
}

Graphic::Color& Graphic::Color::set(const Color& color){
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
	return *this;
}

Graphic::Color& Graphic::Color::set(const Geom::Vector3D vec){
	return set(vec.x, vec.y, vec.z);
}

Graphic::Color& Graphic::Color::mul(const Color& color){
	this->r *= color.r;
	this->g *= color.g;
	this->b *= color.b;
	this->a *= color.a;
	return clamp();
}

Graphic::Color& Graphic::Color::mul_rgb(const float value){
	this->r *= value;
	this->g *= value;
	this->b *= value;
	return clamp();
}

Graphic::Color& Graphic::Color::mul_rgba(const float value){
	this->r *= value;
	this->g *= value;
	this->b *= value;
	this->a *= value;
	return clamp();
}

Graphic::Color& Graphic::Color::add(const Color& color){
	this->r += color.r;
	this->g += color.g;
	this->b += color.b;
	return clamp();
}

Graphic::Color& Graphic::Color::sub(const Color& color){
	this->r -= color.r;
	this->g -= color.g;
	this->b -= color.b;
	return clamp();
}

Graphic::Color& Graphic::Color::clamp(){
	if (r < 0)
		r = 0;
	else if (r > 1) r = 1;

	if (g < 0)
		g = 0;
	else if (g > 1) g = 1;

	if (b < 0)
		b = 0;
	else if (b > 1) b = 1;

	if (a < 0)
		a = 0;
	else if (a > 1) a = 1;
	return *this;
}

Graphic::Color& Graphic::Color::setForce(const float tr, const float tg, const float tb, const float ta){
	this->r = tr;
	this->g = tg;
	this->b = tb;
	this->a = ta;

	return *this;
}

Graphic::Color& Graphic::Color::set(const float tr, const float tg, const float tb, const float ta){
	this->r = tr;
	this->g = tg;
	this->b = tb;
	this->a = ta;
	return clamp();
}

Graphic::Color& Graphic::Color::set(const float tr, const float tg, const float tb){
	this->r = tr;
	this->g = tg;
	this->b = tb;
	return clamp();
}

Graphic::Color& Graphic::Color::set(const int rgba){
	return rgba8888(rgba);
}

float Graphic::Color::sum() const{
	return r + g + b;
}

Graphic::Color& Graphic::Color::add(const float tr, const float tg, const float tb, const float ta){
	this->r += tr;
	this->g += tg;
	this->b += tb;
	this->a += ta;
	return clamp();
}

Graphic::Color& Graphic::Color::add(const float tr, const float tg, const float tb){
	this->r += tr;
	this->g += tg;
	this->b += tb;
	return clamp();
}

Graphic::Color& Graphic::Color::sub(const float tr, const float tg, const float tb, const float ta){
	this->r -= tr;
	this->g -= tg;
	this->b -= tb;
	this->a -= ta;
	return clamp();
}

Graphic::Color& Graphic::Color::sub(const float tr, const float tg, const float tb){
	this->r -= tr;
	this->g -= tg;
	this->b -= tb;
	return clamp();
}

Graphic::Color& Graphic::Color::inv(){
	r = 1 - r;
	g = 1 - g;
	b = 1 - b;
	return *this;
}

Graphic::Color& Graphic::Color::setR(const float tr){
	this->r -= tr;
	return *this;
}

Graphic::Color& Graphic::Color::setG(const float tg){
	this->g -= tg;
	return *this;
}

Graphic::Color& Graphic::Color::setB(const float tb){
	this->b -= tb;
	return *this;
}

Graphic::Color& Graphic::Color::setA(const float ta){
	this->a = ta;
	return *this;
}

Graphic::Color& Graphic::Color::mulA(const float ta){
	this->a *= a;
	return *this;
}

Graphic::Color& Graphic::Color::mul(const float tr, const float tg, const float tb, const float ta){
	this->r *= tr;
	this->g *= tg;
	this->b *= tb;
	this->a *= ta;
	return clamp();
}

Graphic::Color& Graphic::Color::lerp(const Color& target, const float t){
	this->r += t * (target.r - this->r);
	this->g += t * (target.g - this->g);
	this->b += t * (target.b - this->b);
	this->a += t * (target.a - this->a);
	return clamp();
}

Graphic::Color& Graphic::Color::lerp(const float tr, const float tg, const float tb, const float ta, const float t){
	this->r += t * (tr - this->r);
	this->g += t * (tg - this->g);
	this->b += t * (tb - this->b);
	this->a += t * (ta - this->a);
	return clamp();
}

Graphic::Color& Graphic::Color::preMultiplyAlpha(){
	r *= a;
	g *= a;
	b *= a;
	return *this;
}

Graphic::Color& Graphic::Color::write(Color& to) const{
	return to.set(*this);
}

static float TMP_HSV[3];

float Graphic::Color::hue() const{
	toHsv(TMP_HSV);
	return TMP_HSV[0];
}

float Graphic::Color::saturation() const{
	toHsv(TMP_HSV);
	return TMP_HSV[1];
}

float Graphic::Color::value() const{
	toHsv(TMP_HSV);
	return TMP_HSV[2];
}

Graphic::Color& Graphic::Color::hue(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[0] = amount;
	fromHsv(TMP_HSV);
	return *this;
}

Graphic::Color& Graphic::Color::saturation(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[1] = amount;
	fromHsv(TMP_HSV);
	return *this;
}

Graphic::Color& Graphic::Color::value(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[2] = amount;
	fromHsv(TMP_HSV);
	return *this;
}

Graphic::Color& Graphic::Color::shiftHue(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[0] += amount;
	fromHsv(TMP_HSV);
	return *this;
}

Graphic::Color& Graphic::Color::shiftSaturation(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[1] += amount;
	fromHsv(TMP_HSV);
	return *this;
}

Graphic::Color& Graphic::Color::shiftValue(const float amount){
	toHsv(TMP_HSV);
	TMP_HSV[2] += amount;
	fromHsv(TMP_HSV);
	return *this;
}

bool Graphic::Color::equals(const Color& o) const{
	if (this == &o) return true;
	return abgr() == o.abgr();
}

size_t Graphic::Color::hashCode() const{
	return rgba8888();
}

float Graphic::Color::toFloatBits() const{
	const colorBits color = (static_cast<colorBits>(255 * a) << 24) | (static_cast<colorBits>(255 * b) << 16) | (static_cast<colorBits>(255 * g) << 8) | static_cast<colorBits>(255 * r);
	return intToFloatColor(color);
}

double Graphic::Color::toDoubleBits() const{
	return toDoubleBits(r, g, b, a);
}

Graphic::Color::colorBits Graphic::Color::abgr() const{
	return (static_cast<colorBits>(255 * a) << 24) | (static_cast<colorBits>(255 * b) << 16) | (static_cast<colorBits>(255 * g) << 8) | static_cast<colorBits>(255 * r);
}

std::string Graphic::Color::toString() const{
	std::stringstream ss;
	ss << std::hex << ((static_cast<colorBits>(255 * r) << 24) | (static_cast<colorBits>(255 * g) << 16) | (static_cast<colorBits>(255 * b) << 8) | (static_cast<colorBits>(255 * a)));


	const int paddingSize = 8 - static_cast<int>(ss.str().size());

	if (paddingSize > 0) {
		const std::string hex = ss.str();
		ss.str(std::string(paddingSize, '0'));
		ss << hex;
	}

	return ss.str();
}

Graphic::Color& Graphic::Color::fromHsv(float h, const float s, const float v){
	const float x = fmod((h / 60.0f + 6), static_cast<float>(6));
	const int i = static_cast<int>(x);
	const float f = x - i;
	const float p = v * (1 - s);
	const float q = v * (1 - s * f);
	const float t = v * (1 - s * (1 - f));
	switch (i) {
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = v;
		break;
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	default:
		r = v;
		g = p;
		b = q;
	}

	return clamp();
}

Graphic::Color& Graphic::Color::fromHsv(float hsv[]){
	return fromHsv(hsv[0], hsv[1], hsv[2]);
}

Graphic::Color Graphic::Color::HSVtoRGB(const float h, const float s, const float v, const float alpha){
	Color c = HSVtoRGB(h, s, v);
	c.a = alpha;
	return c;
}

Graphic::Color Graphic::Color::HSVtoRGB(float h, float s, float v){
	Color c{ 1, 1, 1, 1 };
	HSVtoRGB(h, s, v, c);
	return c;
}

float* Graphic::Color::toHsv(float hsv[]) const{
	const float max = max(max(r, g), b);
	const float min = min(min(r, g), b);
	const float range = max - min;
	if (range == 0) {
		hsv[0] = 0;
	}
	else if (max == r) {
		hsv[0] = fmod((60 * (g - b) / range + 360), 360.0f);
	}
	else if (max == g) {
		hsv[0] = 60 * (b - r) / range + 120;
	}
	else {
		hsv[0] = 60 * (r - g) / range + 240;
	}

	if (max > 0) {
		hsv[1] = 1 - min / max;
	}
	else {
		hsv[1] = 0;
	}

	hsv[2] = max;

	return hsv;
}

Graphic::Color& Graphic::Color::HSVtoRGB(float h, float s, float v, Color& targetColor){
	if (h == 360) h = 359;
	float r, g, b;
	h = static_cast<float>(max(0.0, min(360.0, h)));
	s = static_cast<float>(max(0.0, min(100.0, s)));
	v = static_cast<float>(max(0.0, min(100.0, v)));
	s /= 100.0f;
	v /= 100.0f;
	h /= 60.0f;
	const int i = Mathf::floor(h);
	const float f = h - i;
	const float p = v * (1 - s);
	const float q = v * (1 - s * f);
	const float t = v * (1 - s * (1 - f));
	switch (i) {
	case 0:
		r = v;
		g = t;
		b = p;
		break;
	case 1:
		r = q;
		g = v;
		b = p;
		break;
	case 2:
		r = p;
		g = v;
		b = t;
		break;
	case 3:
		r = p;
		g = q;
		b = v;
		break;
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	default:
		r = v;
		g = p;
		b = q;
	}

	targetColor.set(r, g, b, targetColor.a);
	return targetColor;
}

int Graphic::Color::clampf(const float value){
	return min(max((int)value, 0), 255);
}

Graphic::Color::colorBits Graphic::Color::ri(const colorBits rgba){
	return (rgba & 0xff000000) >> 24;
}

Graphic::Color::colorBits Graphic::Color::gi(const colorBits rgba){
	return (rgba & 0x00ff0000) >> 16;
}

Graphic::Color::colorBits Graphic::Color::bi(const colorBits rgba){
	return (rgba & 0x0000ff00) >> 8;
}

Graphic::Color::colorBits Graphic::Color::ai(const colorBits rgba){
	return (rgba & 0x000000ff);
}

Graphic::Color::colorBits Graphic::Color::muli(const colorBits ca, const colorBits cb){
	const colorBits
		r = ((ca & 0xff000000) >> 24),
		g = ((ca & 0x00ff0000) >> 16),
		b = ((ca & 0x0000ff00) >> 8),
		a = ((ca & 0x000000ff)),
		r2 = ((cb & 0xff000000) >> 24),
		g2 = ((cb & 0x00ff0000) >> 16),
		b2 = ((cb & 0x0000ff00) >> 8),
		a2 = ((cb & 0x000000ff));
	return (clampf(r * r2 / 255.0f) << 24) | (clampf(g * g2 / 255.0f) << 16) | (clampf(b * b2 / 255.0f) << 8) | (clampf(a * a2 / 255.0f));
}

Graphic::Color::colorBits Graphic::Color::muli(const colorBits rgba, const float value){
	const colorBits
		r = ((rgba & 0xff000000) >> 24),
		g = ((rgba & 0x00ff0000) >> 16),
		b = ((rgba & 0x0000ff00) >> 8),
		a = ((rgba & 0x000000ff));
	return (clampf(r * value) << 24) | (clampf(g * value) << 16) | (clampf(b * value) << 8) | (a);
}
