#include <bits/stdc++.h>

using namespace std;

class IOSystem{
    virtual void citire(istream& in) = 0;
    virtual void afisare(ostream& out) const = 0;
};

class User : public IOSystem{
    protected:
        string numeUtilizator;
        string nume;
        string prenume;
        string email;
        string parola;
        int varsta;
        int range;      /// raza de cautare pentru match-uri
        bool restrict;
    
    public:
        virtual void autentificare(istream& in){
            cout << "Nume: ";
            in >> this->nume;

            cout << "Prenume: ";
            in >> this->prenume;

            cout << "Varsta: ";
            in >> this->varsta;

            cout << "E-Mail: ";
            in >> this->email;

            cout << "Parola: ";
            in >> this->parola;

            cout << "Afiseaza persoane la o distanta maxima de: ";
            in >> this->range;

            cout << "Doriti ca afisarea sa se realizeze doar in acesta raza?\n 1 -> Da\n 2 -> Nu\n";
            int response;
            cout << "Raspuns: ";
            in >> response;
            if(response == 1 || response == 2){
                if(response == 1){
                    this->restrict = true;
                }
                else{
                    this->restrict = false;
                }
            }
            else{
                while(true){
                    cout << "Raspuns invalid, incercati inca o data: \n";
                    cout << "Raspuns: ";
                    in >> response;
                    if(response == 1 || response == 2){
                        if(response == 1){
                            this->restrict = true;
                        }
                        else{
                            this->restrict = false;
                        }
                        break;
                    }
                }
            }

            cout << "Sub ce nume doresti sa apari celorlalti utilizatori?\n";
            in >> this->numeUtilizator;
        }

        virtual void afisareProfil(ostream& out) const {
            cout << this->numeUtilizator << "\n";
            cout << "Varsta: " << this->varsta << "\n";
            
        }
};

int main(){

}