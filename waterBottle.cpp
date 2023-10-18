#include <iostream>
#include "waterBottle.hpp"

/*
    Redes de computacion I

    José González 15-10627
    Ana Santos. 17-10602
    Amaranta Villegas 16-11247

*/

    WaterBottle::WaterBottle(int capacity): Capacity(capacity), CurrentValue(0){}

    void WaterBottle::fill()
    {
        setCurrentValue(Capacity);
    }

    void WaterBottle::empty()
    {
        setCurrentValue(0);
    }

    int WaterBottle::getCapacity()
    {
        return Capacity;
    }

    int WaterBottle::getCurrentValue()
    {
        return CurrentValue;
    }

    void WaterBottle::setCapacity(int capacity)
    {
        Capacity = capacity;
    }

    void WaterBottle::setCurrentValue(int currentValue)
    {
        CurrentValue = currentValue;
    }

    char *WaterBottle::toString()
    {
        char *str = new char[100];
        sprintf(str, "(Capacidad: %d, Valor actual: %d)", Capacity, CurrentValue);
        return str;
    }


/*
           La primera botella es la que es vaciada sobre la segunda botella
           Se obtienen los valores de ambas botellas, si la suma del valor actual
           de la primera y segunda botella es menor a la capacidad de la segunda botella
           entonces se le asigna ese valor al valor actual de la botella 2 y se vacia la botella 1.
           En caso de que la suma sea mayor o igual a la capacidad de la botella 2, entonces se le asigna
           el valor de la capacidad de la botella 2 al valor actual de la botella 2 y se realiza el calculo
           del valor que hizo falta de la botella 2 para ser llenada.
       */
void fillOtherBottle(WaterBottle &firstBottle, WaterBottle &secondBottle)
{
    int firstBottleCapacity = firstBottle.getCapacity();
    int secondBottleCapacity = secondBottle.getCapacity();
    int firstBottleCurrentValue = firstBottle.getCurrentValue();
    int secondBottleCurrentValue = secondBottle.getCurrentValue();

    if (firstBottleCurrentValue + secondBottleCurrentValue < secondBottleCapacity)
    {
        secondBottle.setCurrentValue(firstBottleCurrentValue + secondBottleCurrentValue);
        firstBottle.setCurrentValue(firstBottleCurrentValue - secondBottle.getCurrentValue());
    }
    else
    {
        secondBottle.setCurrentValue(secondBottleCapacity);
        firstBottle.setCurrentValue(firstBottleCapacity - (secondBottleCapacity - secondBottleCurrentValue));
    }
}