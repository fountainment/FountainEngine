#include <fountain/ft_debug.h>
#include <fountain/ft_data.h>
#include <fountain/ft_math.h>
#include <cstdio>
#include <cstring>

namespace fountain {

winState mainWin;

};

//class ftVec2
ftVec2::ftVec2()
{
	x = 0;
	y = 0;
}

ftVec2::ftVec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void ftVec2::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

float ftVec2::length()
{
	return std::pow(x * x + y * y, 0.5);
}

float ftVec2::getDegree()
{
	float d = std::atan(y / x);
	if (x > 0) d -= FT_Pi / 2.0f;
	else d += FT_Pi / 2.0f;
	return d;
}

const ftVec2 ftVec2::operator-(const ftVec2 & v)
{
	return ftVec2(x - v.x, y - v.y);
}

void ftVec2::operator-=(const ftVec2 & v)
{
	x -= v.x;
	y -= v.y;
}

const ftVec2 ftVec2::operator+(const ftVec2 & v)
{
	return ftVec2(x + v.x, y + v.y);
}

void ftVec2::operator+=(const ftVec2 & v)
{
	x += v.x;
	y += v.y;
}

const ftVec2 ftVec2::operator*(float k)
{
	return ftVec2(x * k, y * k);
}

void ftVec2::operator*=(float k)
{
	x *= k;
	y *= k;
}

const ftVec2 ftVec2::operator/(float k)
{
	return ftVec2(x / k, y / k);
}

const ftVec2 ftVec2::operator/(const ftVec2 & v)
{
	return ftVec2(x / v.x, y / v.y);
}

//class ftVec3
ftVec3::ftVec3()
{
	xyz[0] = 0;
	xyz[1] = 0;
	xyz[2] = 0;
}

ftVec3::ftVec3(float x, float y, float z)
{
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
}

//class ftRect
ftRect::ftRect(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

ftRect::ftRect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

ftRect::ftRect(const ftVec2 & pos, const ftVec2 & rSize)
{
	x = pos.x;
	y = pos.y;
	w = rSize.x;
	h = rSize.y;
}

ftVec2 ftRect::getCenter()
{
	ftVec2 p;
	p.x = x + w / 2.0f;
	p.y = y + h / 2.0f;
	return p;
}

void ftRect::setCenter(const ftVec2 & p)
{
	x = p.x - ftRect::w / 2.0f;
	y = p.y - ftRect::h / 2.0f;
}

ftVec2 ftRect::getSize()
{
	ftVec2 p(ftRect::w, ftRect::h);
	return p;
}

void ftRect::setSize(const ftVec2 & sz)
{
	w = sz.x;
	h = sz.y;
}

ftVec2 ftRect::getXY()
{
	return ftVec2(ftRect::x, ftRect::y);
}

void ftRect::setXY(const ftVec2 & XY)
{
	x = XY.x;
	y = XY.y;
}

float ftRect::getX()
{
	return x;
}

float ftRect::getY()
{
	return y;
}

float ftRect::getW()
{
	return w;
}

float ftRect::getH()
{
	return h;
}

const ftVec2 ftRect::getLB()
{
	return ftVec2(x, y);
}

const ftVec2 ftRect::getLT()
{
	return ftVec2(x, y + h);
}

const ftVec2 ftRect::getRT()
{
	return ftVec2(x + w, y + h);
}

const ftVec2 ftRect::getRB()
{
	return ftVec2(x + w, y);
}

void ftRect::getFloatVertex(float *v)
{
	v[0] = x;
	v[1] = y;
	v[2] = x + w;
	v[3] = y;
	v[4] = x + w;
	v[5] = y + h;
	v[6] = x;
	v[7] = y + h;
}

void ftRect::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void ftRect::inflate(float x, float y)
{
	this->x *= x;
	this->y *= y;
	this->w *= x;
	this->h *= y;
}

void ftRect::normalize()
{
	if (w < 0) {
		x += w;
		w *= -1;
	}
	if (h < 0) {
		y += h;
		h *= -1;
	}
}

bool ftRect::collidePoint(const ftVec2 & p)
{
	int xx = x + w;
	int yy = y + h;
	return ((((x - p.x) * (xx - p.x)) <= 0) && (((y - p.y) * (yy - p.y)) <= 0));
}

bool ftRect::collideRect(const ftRect & r)
{
	ftRect rect = r;
	ftVec2 dv = getCenter() - rect.getCenter();
	float wSum = getW() + rect.getW();
	float hSum = getH() + rect.getH();
	float xD = FT_ABS(dv.x * 2.0f);
	float yD = FT_ABS(dv.y * 2.0f);
	return (xD <= wSum) && (yD <= hSum);
}

std::vector<ftVec2> ftRect::collideSegment(const ftVec2 & pa, const ftVec2 & pb)
{
	std::vector<ftVec2> prev;
	std::vector<ftVec2> v;
	ftVec2 kv(pb.x - pa.x, pb.y - pa.y);
	ftVec2 tmp;
	float k, b;
	float rX, rY;
	if (kv.x == 0.0f) {
		//TODO: finish this function
	} else {
		k = kv.y / kv.x;
		b = pa.y - k * pa.x;
		rX = x;
		rY = k * rX + b;
		prev.push_back(ftVec2(rX, rY));
		rX = x + w;
		rY = k * rX + b;
		prev.push_back(ftVec2(rX, rY));
		if (k != 0.0f) {
			rY = y;
			rX = (rY - b) / k;
			prev.push_back(ftVec2(rX, rY));
			rY = y + h;
			rX = (rY - b) / k;
			prev.push_back(ftVec2(rX, rY));
		}
	}
	for (unsigned i = 0; i < prev.size(); i++) {
		tmp = prev[i];
		if (collidePoint(tmp)) {
			if ((tmp.x - pa.x) * (tmp.x - pb.x) <= 0 &&
				(tmp.y - pa.y) * (tmp.y - pb.y) <= 0) v.push_back(prev[i]);
		}
	}
	return v;
}

//class ftShape
ftShape::ftShape(ftRect rct)
{
	setN(1);
	type = FT_Rect;
	loop = true;
	data[0] = rct.getSize().x;
	data[1] = rct.getSize().y;
}

ftShape::ftShape(float r)
{
	setN(0);
	type = FT_Circle;
	loop = true;
	this->r = r;
}

ftShape::ftShape(const std::vector<ftVec2> & a, int n, bool loop)
{
	setN(n);
	if (loop == true)
		type = FT_Polygon;
	else
		type = FT_Line;
	this->loop = loop;
	setData(a);
}

ftShape::~ftShape()
{
}

const float * ftShape::getData()
{
	return data;
}

void ftShape::setData(const std::vector<ftVec2> & a)
{
	for (unsigned i = 0; i < a.size(); i++) {
		data[i * 2] = a[i].x;
		data[i * 2 + 1] = a[i].y;
	}
}

int ftShape::getN()
{
	return n;
}

void ftShape::setN(int n)
{
	this->n = n;
}

void ftShape::setR(float r)
{
	this->r = r;
}

float ftShape::getR()
{
	return r;
}

int ftShape::getType()
{
	return type;
}

ftShape ftShape::makeRegularPolygonShape(int edgeN, float r)
{
	float d = FT_Pi * 2.0f / edgeN;
	std::vector<ftVec2> v;
	for (int i = 0; i < edgeN; i++) {
		v.push_back(ftVec2(std::cos(d * i) * r, std::sin(d * i) * r));
	}
	return ftShape(v, edgeN, true);
}

//class ftSprite
ftSprite::ftSprite()
{
	color = FT_White;
	setPosition(0, 0);
	setRectSize(0, 0);
	scale = 1.0f;
	die = false;
	enable = true;
}

void ftSprite::setColor(const ftColor & c)
{
	color = c;
}

const ftColor & ftSprite::getColor()
{
	return color;
}

void ftSprite::setPosition(const ftVec2 & pos)
{
	position = pos;
}

void ftSprite::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

ftVec2 ftSprite::getPosition()
{
	return position;
}

void ftSprite::setAngle(float agl)
{
	agl = FT_R2D(agl);
	angle = agl;
}

float ftSprite::getAngle()
{
	return angle;
}

void ftSprite::setRectSize(const ftVec2 & rts)
{
	rectSize = rts;
}

void ftSprite::setRectSize(float x, float y)
{
	rectSize.x = x;
	rectSize.y = y;
}

ftVec2 ftSprite::getRectSize()
{
	return rectSize;
}

void ftSprite::setRect(ftRect rct)
{
	setPosition(rct.getCenter());
	setRectSize(rct.getSize());
}

ftRect ftSprite::getRect()
{
	ftRect rct;
	rct.setSize(rectSize);
	rct.setCenter(position);
	return rct;
}

void ftSprite::draw()
{
}

void ftSprite::update()
{
}

void ftSprite::move(const ftVec2 & x)
{
	position += x;
}

void ftSprite::move(float x, float y)
{
	position.x += x;
	position.y += y;
}

void ftSprite::rotate(float aSpeed)
{
	angle += aSpeed;
}

void ftSprite::setTag(int tag)
{
	this->tag = tag;
}

int ftSprite::getTag()
{
	return tag;
}

//class ftColor
float ftColor::checkValue(float v)
{
	if (v > 1.0f) v = 1.0f;
	else if (v < 0.0f) v = 0.0f;
	return v;
}

ftColor::ftColor()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}

int Hex2Dec(std::string hexs)
{
	int ans = 0;
	if (hexs.length() == 0) return ans;
	for (unsigned i = 0; i < hexs.length(); i++) {
		if (i != 0) ans *= 16;
		if (hexs[i] >= '0' && hexs[i] <= '9') {
			ans += hexs[i] - '0';
		}
		else if (hexs[i] >= 'A' && hexs[i] <= 'F') {
			ans += 10 + hexs[i] - 'A';
		}
		else if (hexs[i] >= 'a' && hexs[i] <= 'f') {
			ans += 10 + hexs[i] - 'a';
		}
		else {
			//TODO: debug output
		}
	}
	return ans;
}

ftColor::ftColor(std::string s, float a)
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	bool correct = false;
	if (s.length() > 0 && s[0] == '#') {
		std::string ss = s.substr(1, s.length() - 1);
		std::string sss;
		if (ss.length() == 3) {
			sss = ss.substr(0, 1);
			sss = sss + sss;
			r = Hex2Dec(sss) / 255.0f;
			sss = ss.substr(1, 1);
			sss = sss + sss;
			g = Hex2Dec(sss) / 255.0f;
			sss = ss.substr(2, 1);
			sss = sss + sss;
			b = Hex2Dec(sss) / 255.0f;
			correct = true;
		} else if (ss.length() == 6) {
			r = Hex2Dec(ss.substr(0, 2)) / 255.0f;
			g = Hex2Dec(ss.substr(2, 2)) / 255.0f;
			b = Hex2Dec(ss.substr(4, 2)) / 255.0f;
			correct = true;
		}
	}
	if (!correct) {
		//TODO: debug output
		return;
	}
	setR(r);
	setG(g);
	setB(b);
	setAlpha(a);
}

ftColor::ftColor(float r, float g, float b, float a)
{
	setR(r);
	setG(g);
	setB(b);
	setAlpha(a);
}

void ftColor::inverse()
{
	r = 1.0f - r;
	g = 1.0f - g;
	b = 1.0f - b;
}

void ftColor::setR(float r)
{
	r = checkValue(r);
	this->r = r;
}

void ftColor::setG(float g)
{
	g = checkValue(g);
	this->g = g;
}

void ftColor::setB(float b)
{
	b = checkValue(b);
	this->b = b;
}

void ftColor::setAlpha(float a)
{
	a = checkValue(a);
	this->a = a;
}

float ftColor::getR()
{
	return r;
}

float ftColor::getG()
{
	return g;
}

float ftColor::getB()
{
	return b;
}

float ftColor::getAlpha()
{
	return a;
}

//class ftFile
ftFile::ftFile()
{
	str = NULL;
}

ftFile::~ftFile()
{
	free();
}

ftFile::ftFile(const char *filename)
{
	str = NULL;
	load(filename);
}

bool ftFile::isLoad()
{
	return str != NULL;
}

void ftFile::free()
{
	if (str != NULL) {
		delete [] str;
		str = NULL;
	}
}

bool ftFile::load(const char *filename)
{
	free();
	std::strcpy(name, filename);
	FILE *f = std::fopen(filename, "r");
	int length;
	int index = 0;
	char tmpChar;
	if (f != NULL) {
		std::fseek(f, 0, SEEK_END);
		length = std::ftell(f);
		str = new char[length + 1];
		std::fseek(f, 0, SEEK_SET);
		while (std::fscanf(f, "%c", &tmpChar) != EOF) {
			str[index] = tmpChar;
			index++;
		}
		str[index] = '\0';
		std::fclose(f);
		FT_OUT("%s: size %d\n", filename, index);
		return true;
	} else {
		FT_OUT("Open \"%s\" error!\n", filename);
		return false;
	}
}

bool ftFile::reload()
{
	return load(name);
}

const char* ftFile::getStr()
{
	return str;
}
