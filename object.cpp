#include "object.h"

Vector2D :: Vector2D(){}

Vector2D :: Vector2D(double x, double y)
{
    
    this->x = x;
    this->y = y;

}

Quantities :: Quantities(){}

Quantities :: Quantities(const double x, const double y, const double m)
{

    position.x = x;
    position.y = y;
    mass = m;

}

Quantities :: Quantities(const double x, const double y, const double m, const double vx, const double vy)
{

    position.x = x;
    position.y = y;
    
    velocity.x = vx;
    velocity.y = vy;

    mass = m;

}

Quantities :: Quantities(const double x, const double y, const double m, const double vx, const double vy,
                         const double ax, const double ay)
{

    position.x = x;
    position.y = y;
    
    velocity.x = vx;
    velocity.y = vy;

    acceleration.x = ax;
    acceleration.y = ay;
    
    mass = m;

}

double Quantities :: GetMass(){ return mass; }

Vector2D Quantities :: GetPosition(){ return Vector2D(position.x, position.y); }

Vector2D Quantities :: GetVelocity(){ return Vector2D(velocity.x, velocity.y); }

Vector2D Quantities :: GetAcceleration(){ return Vector2D(acceleration.x, acceleration.y); }

void Quantities :: SetMass(double m){ mass = m; }

void Quantities :: SetPosition(double x, double y){ position.x = x; position.y = y; }

void Quantities :: SetVelocity(double x, double y){ velocity.x = x; velocity.y = y; }

void Quantities :: SetAcceleration(double x, double y){ acceleration.x = x; acceleration.y = y; }

Physics :: Physics()
{

    force_vector.x = 0;
    force_vector.y = 0;

    rezultant_force = 0;
    distance = 0;

}

Physics :: Physics(const Quantities b1, const Quantities b2) : A(b1), B(b2)
{

    if(b2.position.x == 0 && b2.position.y == 0 && b2.mass == 0)
    {

        distance = 0;

        force_vector.x = 0;
        force_vector.y = 0;
        rezultant_force = 0;

        return;

    }

    //distance and angles
    distance = CalculateDistance();

    if(distance == 0)
    {

        force_vector.x = 0;
        force_vector.y = 0;
        rezultant_force = 0;

        return;

    }

    double sin_alpha = CalculateSin();
    double cos_alpha = CalculateCos();

    //total force
    rezultant_force = CalculateRezultantForce();
    
    //force applies on X and Y axis
    force_vector.x = cos_alpha * rezultant_force;
    force_vector.y = sin_alpha * rezultant_force;

}

double Physics :: CalculateDistance()
{

    double dist_x = B.position.x - A.position.x;
    double dist_y = B.position.y - A.position.y;

    return root(dist_x * dist_x + dist_y * dist_y);

}

double Physics :: GetDistance(){ return distance; }
double Physics :: GetRezultantForce(){ return rezultant_force; }
double Physics :: GetForceVectorX(){ return force_vector.x; }
double Physics :: GetForceVectorY(){ return force_vector.y; }

double Physics :: CalculateCos(){ return abs(B.position.x - A.position.x) / distance * sign(B.position.x - A.position.x); }
double Physics :: CalculateSin(){ return abs(B.position.y - A.position.y) / distance * sign(B.position.y - A.position.y); }

double Physics :: CalculateRezultantForce(){ return G * A.mass * B.mass / distance / distance; }

Vector2D SumOfForcesK(Quantities celestial_bodies[], int number_of_celestial_bodies, int current_celestial_body)
{

    Vector2D REZ;

    int k = 0;

    while(k < number_of_celestial_bodies)
    {

        if(k != current_celestial_body)
        {

            Physics* AUX = new Physics(celestial_bodies[current_celestial_body], celestial_bodies[k]);

            REZ.x += AUX->GetForceVectorX();
            REZ.y += AUX->GetForceVectorY();

            delete AUX;

        }

        k++;

    }

    return REZ;

}

Vector2D* GetGlobalForces(Quantities celestial_bodies[], int number_of_celestial_bodies)
{

    Vector2D* REZ = new Vector2D[number_of_celestial_bodies];
    
    for(int i = 0; i < number_of_celestial_bodies; i++)
    {

        Vector2D AUX = SumOfForcesK(celestial_bodies, number_of_celestial_bodies, i);
        REZ[i] = AUX;

    }

    return REZ;

}

Quantities CalculateNextPositionVelocityAcceleration(Quantities celestial_body, Vector2D Force, double step)
{

    Quantities next = celestial_body;

    next.SetAcceleration(Force.x / next.GetMass(), Force.y / next.GetMass());

    next.SetVelocity(next.GetVelocity().x + next.GetAcceleration().x * step, 
                     next.GetVelocity().y + next.GetAcceleration().y * step);
    
    next.SetPosition(next.GetPosition().x + next.GetVelocity().x * step, 
                     next.GetPosition().y + next.GetVelocity().y * step);

    return next;

}