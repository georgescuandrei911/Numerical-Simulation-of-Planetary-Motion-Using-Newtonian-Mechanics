#pragma once
#include "agmath.h"

class Vector2D
{

    public:

    double x = 0;
    double y = 0;

    Vector2D();
    Vector2D(double x, double y);

};

class Quantities {

    friend class Physics;

private:

    class Position{

        friend class Quantities;
        friend class Physics;

        private:
            double x = 0;
            double y = 0;
    };

    class Velocity{

        friend class Quantities;
        friend class Physics;

        private:
            double x = 0;
            double y = 0;
    };

    class Acceleration{

        friend class Quantities;
        friend class Physics;

        private:
            double x = 0;
            double y = 0;
    };

    Position position;
    Velocity velocity;
    Acceleration acceleration;

    double mass = 0;

public:

    Quantities();
    Quantities(const double x, const double y, const double m);
    Quantities(const double x, const double y, const double m, const double vx, const double vy);
    Quantities(const double x, const double y, const double m, const double vx, const double vy,
                         const double ax, const double ay);

    double GetMass();

    Vector2D GetPosition();
    Vector2D GetVelocity();
    Vector2D GetAcceleration();

    void SetMass(double m);

    void SetPosition(double x, double y);
    void SetVelocity(double x, double y);
    void SetAcceleration(double x, double y);
    
};

class Physics{

    private:

    Quantities A, B;

    double rezultant_force;
    double distance;

    class ForceVector{

        private:

        friend class Physics;

        double x;
        double y;

    };

    ForceVector force_vector;

    public:

    Physics();
    Physics(const Quantities b1, const Quantities b2);

    //getters
    double GetDistance();
    double GetRezultantForce();
    double GetForceVectorX();
    double GetForceVectorY();

    //functions
    double CalculateDistance();

    double CalculateCos();
    double CalculateSin();

    double CalculateRezultantForce();

};

Vector2D SumOfForcesK(Quantities celestial_bodies[], int number_of_celestial_bodies, int current_celestial_body);

Vector2D* GetGlobalForces(Quantities celestial_bodies[], int number_of_celestial_bodies);

Quantities CalculatePositionVelocityAcceleration(Quantities celestial_body, double step);

Quantities CalculateNextPositionVelocityAcceleration(Quantities celestial_body, Vector2D Force, double step);