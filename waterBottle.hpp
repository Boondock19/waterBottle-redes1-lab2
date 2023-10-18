class WaterBottle
{
private:
    int Capacity;
    int CurrentValue;

public:
    WaterBottle(int capacity);
   

    void fill(); 

    void empty(); 

    int getCapacity(); 

    int getCurrentValue();

    void setCapacity(int capacity); 

    void setCurrentValue(int currentValue);

    char *toString(); 
};

/*
           La primera botella es la que es vaciada sobre la segunda botella
           Se obtienen los valores de ambas botellas, si la suma del valor actual
           de la primera y segunda botella es menor a la capacidad de la segunda botella
           entonces se le asigna ese valor al valor actual de la botella 2 y se vacia la botella 1.
           En caso de que la suma sea mayor o igual a la capacidad de la botella 2, entonces se le asigna
           el valor de la capacidad de la botella 2 al valor actual de la botella 2 y se realiza el calculo
           del valor que hizo falta de la botella 2 para ser llenada.
       */
void fillOtherBottle(WaterBottle &firstBottle, WaterBottle &secondBottle);