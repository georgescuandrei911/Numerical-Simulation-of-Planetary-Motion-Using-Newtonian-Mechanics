//g++ *.cpp -o main && ./main

#include "manager.h"
#include <iomanip>

int main()
{

    ofstream output("output.txt");

    //number of celestial bodies;
    int number_of_celestial_bodies = 3;

    Quantities* celestial_bodies = new Quantities[number_of_celestial_bodies];

// Sun
celestial_bodies[0] = Quantities(
    0.0, 0.0,
    1.9884e30,
    0.0, 0.0
);

// Earth
celestial_bodies[1] = Quantities(
    1.496e11, 0.0,
    5.9722e24,
    0.0, 29780.0
);

// Moon: 384,400 km farther from the Sun than Earth
celestial_bodies[2] = Quantities(
    1.496e11 + 3.844e8, 0.0,
    7.342e22,
    0.0, 29780.0 + 1022.0
);
    Vector2D* initial_position = new Vector2D[number_of_celestial_bodies];

    double initial_distance = Physics(celestial_bodies[0], celestial_bodies[1]).GetDistance();

    double step = 360;
    double tmax = 3600 * 24 * 100;

    output << number_of_celestial_bodies << ", " << step << ", " << (int) tmax << endl;

    output << scientific << setprecision(16);

    for(int i = 0; i <= tmax; i += step)
    {

        Vector2D* forces = GetGlobalForces(celestial_bodies, number_of_celestial_bodies);

        for(int j = 0; j < number_of_celestial_bodies; j++)
        {
            output
            << "Planet " << j << ": time: " << i << " : X Y : "
            << celestial_bodies[j].GetPosition().x <<" " << celestial_bodies[j].GetPosition().y << endl;
            celestial_bodies[j] = CalculateNextPositionVelocityAcceleration(celestial_bodies[j], forces[j], step);

        }

        output << endl;

        if(i % 1000 == 0)cout << 100.0 * i / tmax << "'%' completed" << endl;

        delete[] forces;

    }

    delete[] celestial_bodies;

    output.close();

}