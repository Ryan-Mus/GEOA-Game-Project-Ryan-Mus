#pragma once
#include "FlyFish.h"
#include <iostream>
namespace math
{
    //Calculate Display Distance 
    inline float GetDistance(const TwoBlade& line, const TwoBlade& line2)
    {
        return TwoBlade::LineFromPoints(line[0], line[1], 0.f, line2[0], line2[1], 0.f).Norm();
    }
    inline float GetDistance(const TwoBlade& line, const ThreeBlade& point)
    {
        return TwoBlade::LineFromPoints(line[0], line[1], 0.f, point[0], point[1], 0.f).Norm();
    }
    inline float GetDistance(const OneBlade& plane, const TwoBlade& line)
    {
        return (line ^ plane).VNorm();
    }
    inline float GetDistance(const OneBlade& plane, const ThreeBlade& point)
    {
        return abs((point * plane)[7]);// I value = distance 
    }
    inline float GetDistance(const ThreeBlade& point1, const ThreeBlade& point2)
    {
        return TwoBlade::LineFromPoints(point1[0], point1[1], 0.f, point2[0], point2[1], 0.f).Norm();
    }

    //Check Normals
    inline bool IsNormalized(const OneBlade& plane)
    {
        return std::abs(plane.Norm() - 1.f) < 1e-6;
    }
    inline bool IsNormalized(const TwoBlade& line)
    {
        return std::abs(line.Norm() - 1.f) < 1e-6;
    }
    inline bool IsNormalized(const ThreeBlade& point)
    {
        return std::abs(point.Norm() - 1.f) < 1e-6;
    }

    //Rotate around a given Line
    inline void RotateAroundLine(TwoBlade& line, const TwoBlade& rotationLine, float degrees)
    {
        Motor Translator1{ Motor::Translation(-rotationLine.VNorm(), TwoBlade::LineFromPoints(0, 0, 1, rotationLine[0], rotationLine[1], 1).Normalized()) };
        Motor Rotator{ Motor::Rotation(degrees, rotationLine) };
        Motor Translator2{ Motor::Translation(rotationLine.VNorm(), TwoBlade::LineFromPoints(0, 0, 1, rotationLine[0], rotationLine[1], 1).Normalized()) };

        line = (Translator2 * Rotator * Translator1 * line * ~Translator1 * ~Rotator * ~Translator2).Grade2();
    }
    inline void RotateAroundLine(ThreeBlade& point, const TwoBlade& rotationLine, float degrees)
    {
        Motor Translator1{ Motor::Translation(-rotationLine.VNorm(), rotationLine) };
        Motor Rotator{ Motor::Rotation(degrees, rotationLine) };
        Motor Translator2{ Motor::Translation(rotationLine.VNorm(), rotationLine) };

        point = (Translator2 * Rotator * Translator1 * point * ~Translator1 * ~Rotator * ~Translator2).Grade3();
    }

    //Translate with Line as direction
    inline void Translate(ThreeBlade& point, const TwoBlade& direction, float distance)
    {
        Motor translator{ Motor::Translation(distance, direction) };
        point = (translator * point * ~translator).Grade3();
    }
    inline void Translate(TwoBlade& m_Line, const TwoBlade& direction, float distance)
    {
        Motor translator{ Motor::Translation(distance, TwoBlade{-direction[1],direction[0],0,0,0,0})};
        m_Line = (translator * m_Line * ~translator).Grade2();
    }
    inline void Translate(OneBlade& plane, const TwoBlade& direction, float distance)
    {
        Motor translator{ Motor::Translation(distance, direction) };
        plane = (translator * plane * ~translator).Grade1();
    }
}
