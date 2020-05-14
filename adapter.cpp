

#include <iostream>
#include <string>

typedef int Cable; // Cable con electrones

/* Interface Adaptado (fuente) */
class InterfaceEnchufeEuropeo
{
    public:
        virtual int voltaje() = 0;

        virtual Cable vivo() = 0;
        virtual Cable neutral() = 0;
        virtual Cable tierra() = 0;
};

/* Adaptado */
class Enchufe : public InterfaceEnchufeEuropeo
{
    public:
        int voltaje() { return 220; }

        Cable vivo() { return 1; }
        Cable neutral() { return -1; }
        Cable tierra() { return 0; }
};

/* Interface Objetivo */
class InterfaceEnchufeUSA
{
    public:
        virtual int voltaje() = 0;

        virtual Cable vivo() = 0;
        virtual Cable neutral() = 0;
};

/* Adaptador*/
class Adaptador : public InterfaceEnchufeUSA
{
    InterfaceEnchufeEuropeo* enchufe;

    public:
        void Enchufar(InterfaceEnchufeEuropeo* TomaCorriente)
        {
            enchufe = TomaCorriente;
        }

        int voltaje() { return 110; }
        Cable vivo() { return enchufe->vivo(); }
        Cable neutral() { return enchufe->neutral(); }
};

/* Cliente */
class TeteraElectrica
{
    InterfaceEnchufeUSA* energia;

    public:
        void Enchufar(InterfaceEnchufeUSA* suministrar)
        {
            energia = suministrar;
        }

        void Hervir()
        {
            if (energia->voltaje() > 110)
            {
                std::cout << "La tetera está en llamas!" << std::endl;
                return;
            }

            if (energia->vivo() == 1 && energia->neutral() == -1)
            {
                std::cout << "Es hora del cafe!" << std::endl;
            }
        }
};


int main()
{
    Enchufe* enchufe = new Enchufe;
    Adaptador* adaptador = new Adaptador;
    TeteraElectrica* Tetera = new TeteraElectrica;

    /* Conectando. */
    adaptador->Enchufar(enchufe);
    Tetera->Enchufar(adaptador);

    /* Haciendo cafe */
    Tetera->Hervir();

    return 0;
}


