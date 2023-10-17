#include <iostream>
#include "waterBottle.hpp"
using namespace std;

/*
    Redes de computacion I

    José González 15-10627
    Ana Santos. 17-10602
    Amaranta Villegas 16-11247

*/

int main()
{
    cout << "Test de las propiedades de esta clase de WaterBottle" << endl;
    cout << "Inicializacion de las botellas de agua:" << endl;
    WaterBottle bottle1(5);
    WaterBottle bottle2(3);

    cout << "Capacidad de la botella 1: " << bottle1.getCapacity() << endl;
    cout << "Capacidad de la botella 2: " << bottle2.getCapacity() << endl;

    cout << "Vamos a llenar la primera botella para vaciarlo sobre la segunda" << endl;

    bottle1.fill();
    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    cout << "Transvasar de la botella 1 a la botella 2:  Primera vez" << endl;
    fillOtherBottle(bottle1, bottle2);

    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    bottle2.empty();
    cout << "Vaciamos la botella 2: Primera vez" << endl;
    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    cout << "Transvasar de la botella 1 a la botella 2: Segunda vez" << endl;
    fillOtherBottle(bottle1, bottle2);
    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    cout << "Llenamos la botella 1: Segunda vez" << endl;
    bottle1.fill();
    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    cout << "Transvasar de la botella 1 a la botella 2: Tercera vez" << endl;
    fillOtherBottle(bottle1, bottle2);

    cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    if (bottle1.getCurrentValue() == 4)
    {
        cout << "Test passed" << endl;
    }
    else
    {
        cout << "Test failed" << endl;
    }

    return 0;
}
