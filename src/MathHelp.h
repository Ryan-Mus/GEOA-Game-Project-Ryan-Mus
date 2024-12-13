#include "FlyFish.h"


namespace math
{
	//Calculate Distance
	float GetDistance(const TwoBlade line,const ThreeBlade& point)
	{
		return TwoBlade::LineFromPoints(line[0], line[1], line[2], point[0], point[1], point[2]).Norm();
	}

	float GetDistance(const OneBlade plane,const ThreeBlade& point)
	{
		return ((plane | point).VNorm()-plane[0]);
	}
	float GetDistance(const ThreeBlade point1,const ThreeBlade& point2)
	{
		return TwoBlade::LineFromPoints(point1[0], point1[1], point1[2], point2[0], point2[1], point2[2]).Norm();
	}

	//Check Normalise
	bool IsNormalized(const OneBlade& plane) 
	{
		return std::abs(plane.Norm() - 1.f) < 1e-6;
	}
	bool IsNormalized(const TwoBlade& line) 
	{
		return std::abs(line.Norm() - 1.f) < 1e-6;
	}
	bool IsNormalized(const ThreeBlade& point) {
		return std::abs(point.Norm() - 1.f) < 1e-6;
	}

	//Rotate around a given line
	void RotateAroundLine(TwoBlade& line, const TwoBlade& rotationLine, float degrees)
	{
		Motor Translator1{ Motor::Translation(-rotationLine.VNorm(),TwoBlade::LineFromPoints(0,0,1,rotationLine[0],rotationLine[1],1).Normalized()) };
		Motor Rotator{ Motor::Rotation(degrees,rotationLine) };
		Motor Translator2{ Motor::Translation(rotationLine.VNorm(),TwoBlade::LineFromPoints(0,0,1,rotationLine[0],rotationLine[1],1).Normalized()) };

		line = (Translator2* Rotator* Translator1* line * ~Translator1 * ~Rotator * ~Translator2).Grade2();
	}
	void RotateAroundLine(ThreeBlade& point, const TwoBlade& rotationLine, float degrees)
	{
		Motor Translator1{ Motor::Translation(-rotationLine.VNorm(),rotationLine) };
		Motor Rotator{ Motor::Rotation(degrees,rotationLine) };
		Motor Translator2{ Motor::Translation(rotationLine.VNorm(),rotationLine) };

		point = (Translator2* Rotator* Translator1* point * ~Translator1 * ~Rotator * ~Translator2).Grade3();
	}
}