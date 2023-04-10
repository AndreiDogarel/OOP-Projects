#include <bits/stdc++.h>

using namespace std;

class Client{
    private:
        const int idClient;
        static int contorIdClient;
        int varsta;
        char* numeDeFamilie;
        string prenume;
        bool membru;
        float buget;
    
    public:
        /// Constructori
        Client();
        Client(int varsta, char* numeDeFamilie, string prenume, bool membru, float buget);
        Client(int varsta, char* numeDeFamilie, string prenume);
        Client(string prenume, float buget);
        Client(const Client& Pers);

        /// Operatori
        Client& operator = (const Client& Pers);
        bool operator > (const Client& Pers);
        bool operator < (const Client& Pers);
        bool operator == (const Client& Pers);
        operator float(){return this->buget;}
        operator float() const {return this->buget;}
        Client operator + (const Client& Pers);
        Client operator + (int buget);
        Client operator * (const Client& Pers);
        Client operator * (int varsta);
        Client& operator ++ ();
        Client operator ++ (int);
        char operator [] (int index);
        friend Client operator + (int varsta, Client Pers);
        friend Client operator * (int varsta, Client Pers);
        friend istream& operator >> (istream& in, Client& Pers);
        friend ostream& operator << (ostream& out, const Client& Pers);

        /// Metode
        void intraInMagazin();

        /// Setters
        void setVarsta(int varsta){this->varsta = varsta;}
        void setNumeDeFamilie(char* numeDeFamilie){
            if(this->numeDeFamilie != NULL){
                delete[] this->numeDeFamilie;
                this->numeDeFamilie = NULL;
            }
            this->numeDeFamilie = new char[strlen(numeDeFamilie) + 1];
            strcpy(this->numeDeFamilie, numeDeFamilie);
        }
        void setPrenume(string prenume){this->prenume = prenume;}
        void setMembership(bool membru){this->membru = membru;}
        void setBuget(float buget){this->buget = buget;}

        /// Getters
        static int getContorIdClient(){return Client::contorIdClient;}
        int getIdClient() const {return this->idClient;}
        int getVarsta() const {return this->varsta;}
        const char* getNumeDeFamilie() const {return this->numeDeFamilie;}
        string getPrenume() const {return this->prenume;}
        bool getMembership() const {return this->membru;}
        float getBuget() const {return this->buget;}

        /// Destructor
        ~Client();
};

int Client::contorIdClient = 0;

/// --------CONSTRUCTORI--------
Client::Client():idClient(++contorIdClient){        // CONSTRUCTOR FARA PARAMETRII
    this->varsta = 0;
    this->numeDeFamilie = NULL;
    this->prenume = "";
    this->membru = false;
    this->buget = 0.0;
}

Client::Client(int varsta, char* numeDeFamilie, string prenume, bool membru, float buget):idClient(++contorIdClient){
    this->varsta = varsta;
    this->numeDeFamilie = new char[strlen(numeDeFamilie) + 1];
    strcpy(this->numeDeFamilie, numeDeFamilie);
    this->prenume = prenume;
    this->membru = membru;
    this->buget = buget;
}

Client::Client(int varsta, char* numeDeFamilie, string prenume):idClient(++contorIdClient){
    this->varsta = varsta;
    this->numeDeFamilie = new char[strlen(numeDeFamilie) + 1];
    strcpy(this->numeDeFamilie, numeDeFamilie);
    this->membru = false;
    this->prenume = prenume;
    this->buget = 0.0;
}

Client::Client(string prenume, float buget):idClient(++contorIdClient){
    this->varsta = 0;
    this->numeDeFamilie = NULL;
    this->prenume = prenume;
    this->membru = false;
    this->buget = buget;
}

Client::Client(const Client& Pers):idClient(Pers.idClient){     // COPY CONSTRUCTOR
    this->varsta = Pers.varsta;
    this->numeDeFamilie = new char[strlen(Pers.numeDeFamilie) + 1];
    strcpy(this->numeDeFamilie, Pers.numeDeFamilie);
    this->prenume = Pers.prenume;
    this->membru = Pers.membru;
    this->buget = Pers.buget;
}
///####################################################

/// --------OPERATORI--------
Client& Client::operator = (const Client& Pers){
    if(this != &Pers){
        if(this->numeDeFamilie != NULL){
            delete[] this->numeDeFamilie;
            this->numeDeFamilie = NULL;
        }
        this->varsta = varsta;
        this->numeDeFamilie = new char[strlen(Pers.numeDeFamilie) + 1];
        strcpy(this->numeDeFamilie, Pers.numeDeFamilie);
        this->prenume = Pers.prenume;
        this->membru = Pers.membru;
        this->buget = Pers.buget;
    }
    return *this;
}

bool Client::operator > (const Client& Pers){
    return this->varsta > Pers.varsta;
}

bool Client::operator < (const Client& Pers){
    return this->varsta < Pers.varsta;
}

bool Client::operator == (const Client& Pers){
    return this->idClient == Pers.idClient && this->varsta == Pers.varsta && strcmp(this->numeDeFamilie, Pers.numeDeFamilie) == 0 && this->prenume == Pers.prenume && this->buget == Pers.buget;
}

Client Client::operator + (const Client& Pers){
    Client aux(*this);
    aux.buget += Pers.buget;
    return aux;
}

Client Client::operator + (int update){
    Client aux(*this);
    aux.buget += update;
    return aux;
}

Client operator + (int buget, Client Pers){
    return (Pers + buget);
}

Client Client::operator * (const Client& Pers){
    Client aux(*this);
    aux.varsta *= Pers.varsta;
    return aux;
}

Client Client::operator * (int varsta){
    Client aux(*this);
    aux.varsta *= varsta;
    return aux;
}

Client operator * (int varsta, Client Pers){
    return (Pers * varsta);
}

Client& Client::operator ++ (){
    this->varsta++;
    return *this;
}

Client Client::operator ++ (int){
    Client aux(*this);
    ++(*this);
    return aux;
}

char Client::operator [] (int index){
    if(index >= this->prenume.size() || index < 0){
        throw runtime_error("Index invalid!");
    }
    else{
        return this->prenume[index];
    }
}

istream& operator >> (istream& in, Client& C){
    cout << "Nume: ";
    char aux[100];
    in >> aux;
    aux[0] = toupper(aux[0]);
    if(C.numeDeFamilie != NULL){
        delete[] C.numeDeFamilie;
        C.numeDeFamilie = NULL;
    }
    C.numeDeFamilie = new char[strlen(aux) + 1];
    strcpy(C.numeDeFamilie, aux);

    cout << "Prenume: ";
    in >> C.prenume;
    C.prenume[0] = toupper(C.prenume[0]);

    cout << "Varsta: ";
    in >> C.varsta;

    return in;
}

ostream& operator << (ostream& out, const Client& C){
    out << "Nume: " << C.numeDeFamilie << "\n";
    out << "Prenume: " << C.prenume << "\n";
    out << "ID de Client: " << C.idClient << "\n";
    out << "Varsta: " << C.varsta << "\n";
    out << "Membru: ";
    if(C.membru == false){
        out << "Nu\n";
    }
    else{
        out << "Da\n";
    }
    return out;
}
///####################################################

/// --------METODE--------
void Client::intraInMagazin(){
    cout << "Prenume client: ";
    string prenume;
    cin >> prenume;
    prenume[0] = toupper(prenume[0]);
    setPrenume(prenume);

    cout << "Buget: ";
    float buget;
    cin >> buget;
    setBuget(buget);
}
///####################################################

/// --------DESTRUCTOR--------
Client::~Client(){
    if(this->numeDeFamilie != NULL){
        delete[] this->numeDeFamilie;
        this->numeDeFamilie = NULL;
    }
    this->varsta = 0;
    this->prenume = "";
    this->membru = false;
    this->buget = 0;
}
///####################################################

class Manga{
    private:
        string nume;
        float pret;
        int nrRating;
        int* ratings;
        int nrPagini;
        int nrBucatiDispon;
        
    public:
        /// Constructori
        Manga();
        Manga(string nume, int nrRating, int* ratings, float pret, int nrPagini, int nrBucatiDispon);
        Manga(string nume, int nrRating, int* ratings);
        Manga(int nrRating, int* ratings);
        Manga(const Manga& M);

        /// Operatori
        Manga& operator = (const Manga& M);
        bool operator > (const Manga& M);
        bool operator == (const Manga& M);
        operator float(){return this->pret;}
        operator float() const {return this->pret;}
        Manga operator + (const Manga& M);
        Manga operator + (float pret);
        Manga operator * (const Manga& M);
        Manga operator * (float pret);
        Manga& operator -- ();
        Manga operator -- (int);
        int operator [] (int index);
        friend Manga operator + (float pret, Manga M);
        friend Manga operator * (float pret, Manga M);
        friend istream& operator >> (istream& in, Manga& M);
        friend ostream& operator << (ostream& out, const Manga& M);

        /// Metode

        float afisMedieRating() const;
        void afisDate() const;
        void giveRating(int rating);
        void scumpeste();

        /// Setters
        void setNume(string nume){this->nume = nume;}
        void setPret(float pret){this->pret = pret;}
        void setNrRating(int nrRating){this->nrRating = nrRating;}
        void setRatings(int* ratings){
            if(this->ratings != NULL){
                delete[] this->ratings;
                this->ratings = NULL;
            }
            this->ratings = new int[this->nrRating + 1];
            for(int i = 0; i < this->nrRating; ++i){
                this->ratings[i] = ratings[i];
            }
        }
        void setNrPagini(int nrPagini){this->nrPagini = nrPagini;}
        void setNrBucatiDispon(int nrBucatiDispon){this->nrBucatiDispon = nrBucatiDispon;}

        /// Getters
        string getNume() const {return this->nume;}
        float getPret() const {return this->pret;}
        int getNrRating() const {return this->nrRating;}
        const int* getRatings() const {return this->ratings;}
        int getNrPagini() const {return this->nrPagini;}
        int getNrBucatiDispon() const {return this->nrBucatiDispon;}

        /// Destructor
        ~Manga();
};

/// --------CONSTRUCTORI--------
Manga::Manga(){
    this->nume = "";
    this->pret = 0.0;
    this->nrRating = 0;
    this->ratings = NULL;
    this->nrPagini = 0;
    this->nrBucatiDispon = 0;
}

Manga::Manga(string nume, int nrRating, int* ratings, float pret, int nrPagini, int nrBucatiDispon){
    this->nume = nume;
    this->nrRating = nrRating;
    this->ratings = new int[nrRating + 1];
    for(int i = 0; i < nrRating; ++i){
        this->ratings[i] = ratings[i];
    }
    this->pret = pret;
    this->nrPagini = nrPagini;
    this->nrBucatiDispon = nrBucatiDispon;
}

Manga::Manga(string nume, int nrRating, int* ratings){
    this->nume = nume;
    this->nrRating = nrRating;
    this->ratings = new int[nrRating + 1];
    for(int i = 0; i < nrRating; ++i){
        this->ratings[i] = ratings[i];
    }
    this->pret = 0.0;
    this->nrPagini = 0;
    this->nrBucatiDispon = 0;
}

Manga::Manga(int nrRating, int* ratings){
    this->nume = "";
    this->nrRating = nrRating;
    this->ratings = new int[nrRating + 1];
    for(int i = 0; i < nrRating; ++i){
        this->ratings[i] = ratings[i];
    }
    this->pret = 0.0;
    this->nrPagini = 0;
    this->nrBucatiDispon = 0;
}

Manga::Manga(const Manga& M){
    this->nume = M.nume;
    this->nrRating = M.nrRating;
    this->ratings = new int[M.nrRating + 1];
    for(int i = 0; i < M.nrRating; ++i){
        this->ratings[i] = M.ratings[i];
    }
    this->pret = M.pret;
    this->nrPagini = M.nrPagini;
    this->nrBucatiDispon = M.nrBucatiDispon;
}
///####################################################

/// --------OPERATORI--------
Manga& Manga::operator = (const Manga& M){
    if(this != &M){
        this->nume = M.nume;
        this->nrRating = M.nrRating;
        if(this->ratings != NULL){
            delete[] this->ratings;
            this->ratings = NULL;
        }
        this->ratings = new int[M.nrRating + 1];
        for(int i = 0; i < M.nrRating; ++i){
            this->ratings[i] = M.ratings[i];
        }
        this->pret = M.pret;
        this->nrPagini = M.nrPagini;
        this->nrBucatiDispon = M.nrBucatiDispon;
    }
    return *this;
}

bool Manga::operator > (const Manga& M){
    return this->afisMedieRating() > M.afisMedieRating();
}

bool Manga::operator == (const Manga& M){
    return this->nume == M.nume;
}

Manga Manga::operator + (const Manga& M){
    Manga aux(*this);
    aux.pret += M.pret;
    return aux;
}

Manga Manga::operator + (float pret){
    Manga aux(*this);
    aux.pret += pret;
    return aux;
}

Manga operator + (float pret, Manga M){
    return (M + pret);
}

Manga Manga::operator * (const Manga& M){
    Manga aux(*this);
    aux.pret *= M.pret;
    return aux;
}

Manga Manga::operator * (float pret){
    Manga aux(*this);
    aux.pret *= pret;
    return aux;
}

Manga operator * (float pret, Manga M){
    return (M * pret);
}

Manga& Manga::operator -- (){
    this->nrBucatiDispon--;
    return (*this);
}

Manga Manga::operator -- (int){
    Manga aux(*this);
    --(*this);
    return aux;
}

int Manga::operator [] (int index){
    if(index < 0 || index >= this->nrRating){
        throw runtime_error("Index invalid!");
    }
    else{
        return this->ratings[index];
    }
}

istream& operator >> (istream& in, Manga& M){
    cout << "Numele seriei: ";
    in.get();
    getline(in, M.nume);

    cout << "Numarul de pagini: ";
    in >> M.nrPagini;

    cout << "Numarul de bucati disponibile: ";
    in >> M.nrBucatiDispon;

    cout << "Pret: ";
    in >> M.pret;

    return in;
}

ostream& operator << (ostream& out, const Manga& M){
    out << "Nume: " << M.nume << "\n";

    float medieRating = M.afisMedieRating();
    if(medieRating == 0.0){
        out << "Aceasta serie inca nu a primit rating-uri!\n";
    }
    else{
        out << "Rating: " << fixed << setprecision(1) << medieRating << "\n";
    }

    out << "Numar de pagini: " << M.nrPagini << "\n";

    out << "Pret: " << M.pret << " lei\n";

    return out;
}
///####################################################

/// --------Metode--------
float Manga::afisMedieRating() const {
    if(this->ratings == NULL){
        return 0.0;
    }
    else{
        float medieRating = 0.0;
        for(int i = 0; i < this->nrRating; ++i){
            medieRating += (float)this->ratings[i];
        }
        return (medieRating / this->nrRating);
    }
}

void Manga::afisDate() const {
    cout << "Nume: " << this->nume << "\n";
    if(this->ratings != NULL){
        cout << "Rating: " << fixed << setprecision(1) << this->afisMedieRating() << "\n\n";
    }
    else{
        cout << "Aceasta serie inca nu a primit un rating\n\n";
    }
}

void Manga::giveRating(int rating){
    this->nrRating++;
    this->ratings[this->nrRating - 1] = rating;
}

void Manga::scumpeste(){
    this->pret = this->pret + (0.1 * this->pret);
}
///####################################################

/// --------DESTRUCTOR--------
Manga::~Manga(){
    if(this->ratings != NULL){
        delete[] this->ratings;
        this->ratings = NULL;
    }
    this->nume = "";
    this->pret = 0.0;
    this->nrRating = 0;
    this->nrPagini = 0;
    this->nrBucatiDispon = 0;
}
///####################################################


class Tricouri{
    private:
        char marime;    // S, M sau L
        float pret;
        string culoare;
        string numeProducator;
        int nrBucatiDispon;

    public:
        /// Constructori
        Tricouri();
        Tricouri(char marime, float pret, string culoare, string numeProducator, int nrBucatiDispon);
        Tricouri(char marime, float pret);
        Tricouri(string culoare, string numeProducator);
        Tricouri(const Tricouri& T);

        /// Operatori
        Tricouri& operator = (const Tricouri& T);
        bool operator > (const Tricouri& T);
        bool operator == (const Tricouri& T);
        operator float(){return this->pret;}
        operator float() const {return this->pret;}
        Tricouri operator + (const Tricouri& T);
        Tricouri operator + (float pret);
        Tricouri operator * (const Tricouri& T);
        Tricouri operator * (float pret);
        Tricouri& operator -- ();
        Tricouri operator -- (int);
        char operator [] (int index);
        friend Tricouri operator + (float pret, Tricouri T);
        friend Tricouri operator * (float pret, Tricouri T);
        friend float operator + (Manga M, Tricouri T);
        friend float operator + (Tricouri T, Manga M);
        friend istream& operator >> (istream& in, Tricouri& T);
        friend ostream& operator << (ostream& out, const Tricouri& T);

        /// Metode
        void scumpeste();

        /// Setters
        void setMarime(char marime){this->marime = marime;}
        void setPret(float pret){this->pret = pret;}
        void setCuloare(string culoare){this->culoare = culoare;}
        void setNumeProducator(string numeProducator){this->numeProducator = numeProducator;}
        void setNrBucatiDispon(int nrBucatiDispon){this->nrBucatiDispon = nrBucatiDispon;}

        /// Getters
        char getMarime() const {return this->marime;}
        float getPret() const {return this->pret;}
        string getCuloare() const {return this->culoare;}
        string getNumeProducator() const {return this->numeProducator;}
        int getNrBucatiDispon() const {return this->nrBucatiDispon;}

        /// Destructor
        ~Tricouri();
};

/// --------CONSTRUCTORI--------
Tricouri::Tricouri(){
    this->marime = '/';
    this->pret = 0.0;
    this->culoare = "";
    this->numeProducator = "";
    this->nrBucatiDispon = 0;
}

Tricouri::Tricouri(char marime, float pret, string culoare, string numeProducator, int nrBucatiDispon){
    this->marime = marime;
    this->pret = pret;
    this->culoare = culoare;
    this->numeProducator = numeProducator;
    this->nrBucatiDispon = nrBucatiDispon;
}

Tricouri::Tricouri(string culoare, string numeProducator){
    this->marime = '/';
    this->pret = 0.0;
    this->culoare = culoare;
    this->numeProducator = numeProducator;
    this->nrBucatiDispon = 0;
}

Tricouri::Tricouri(char marime, float pret){
    this->marime = marime;
    this->pret = pret;
    this->culoare = "";
    this->numeProducator = "";
    this->nrBucatiDispon = 0;
}

Tricouri::Tricouri(const Tricouri& T){
    this->marime = T.marime;
    this->pret = T.pret;
    this->culoare = T.culoare;
    this->numeProducator = T.numeProducator;
    this->nrBucatiDispon = T.nrBucatiDispon;
}
///####################################################

/// --------OPERATORI--------
Tricouri& Tricouri::operator = (const Tricouri& T){
    if(this != &T){
        this->marime = T.marime;
        this->pret = T.pret;
        this->culoare = T.culoare;
        this->numeProducator = T.numeProducator;
        this->nrBucatiDispon = T.nrBucatiDispon;
    }
    return *this;
}

bool Tricouri::operator > (const Tricouri& T){
    return this->marime < T.marime && this->pret > T.pret;
}

bool Tricouri::operator == (const Tricouri& T){
    return this->marime == T.marime && this->pret == T.pret && this->culoare == T.culoare && this->numeProducator == T.numeProducator && this->nrBucatiDispon == T.nrBucatiDispon;
}

Tricouri Tricouri::operator + (const Tricouri& T){
    Tricouri aux(*this);
    aux.pret += T.pret;
    return aux;
}

Tricouri Tricouri::operator + (float pret){
    Tricouri aux(*this);
    aux.pret += pret;
    return aux;
}

Tricouri operator + (float pret, Tricouri T){
    return (T + pret);
}

Tricouri Tricouri::operator * (const Tricouri& T){
    Tricouri aux(*this);
    aux.pret *= T.pret;
    return aux;
}

Tricouri Tricouri::operator * (float pret){
    Tricouri aux(*this);
    aux.pret *= pret;
    return aux;
}

Tricouri operator * (float pret, Tricouri T){
    return (T * pret);
}

Tricouri& Tricouri::operator -- (){
    this->nrBucatiDispon--;
    return (*this);
}

Tricouri Tricouri::operator -- (int){
    Tricouri aux(*this);
    this->nrBucatiDispon--;
    return aux;
}

char Tricouri::operator [] (int index){
    if(index < 0 || index >= this->numeProducator.size()){
        throw runtime_error("Index invalid!");
    }
    else{
        return this->numeProducator[index];
    }
}

float operator + (Manga M, Tricouri T){
    return (M + T.pret);
}

float operator + (Tricouri T, Manga M){
    return (M + T);
}

istream& operator >> (istream& in, Tricouri& T){
    cout << "Marime: ";
    in >> T.marime;

    cout << "Culoare: ";
    in >> T.culoare;

    cout << "Numele Producatorului: ";
    in.get();
    getline(in, T.numeProducator);

    cout << "Numarul de bucati disponibile: ";
    in >> T.nrBucatiDispon;

    cout << "Pret: ";
    in >> T.pret;

    return in;
}

ostream& operator << (ostream& out, const Tricouri& T){
    out << "Marime: " << T.marime << "\n";

    out << "Culoare: " << T.culoare << "\n";

    out << "Numele Producatorului: " << T.numeProducator << "\n";

    out << "Pret: " << T.pret << " lei\n";

    return out;
}
///####################################################

/// --------METODE--------
void Tricouri::scumpeste(){
    this->pret = this->pret + (0.1 * this->pret);
}
///####################################################

/// --------DESTRUCTOR--------
Tricouri::~Tricouri(){
    this->marime = '\0';
    this->pret = 0.0;
    this->culoare = "";
    this->numeProducator = "";
    this->nrBucatiDispon = 0;
}
///####################################################


class Figurina{
    private:
        string numeCaracter;
        int inaltime;
        float pret;
        string numeProducator;
        string numeSerie;
        int nrBucatiDispon;

    public:
        /// Constructori
        Figurina();
        Figurina(string numeCaracter, int inaltime, float pret, string numeProducator, string numeSerie, int nrBucatiDispon);
        Figurina(string numeCaracter, int inaltime);
        Figurina(string numeCaracter, string numeProducator, string numeSerie);
        Figurina(const Figurina& F);

        /// Operatori
        Figurina& operator = (const Figurina& F);
        bool operator < (const Figurina& F);
        bool operator == (const Figurina& F);
        operator float(){return this->pret;}
        operator float() const {return this->pret;}
        Figurina operator + (const Figurina& F);
        Figurina operator + (float pret);
        Figurina operator * (const Figurina& F);
        Figurina operator * (float pret);
        Figurina& operator -- ();
        Figurina operator -- (int);
        char operator [] (int index);
        friend Figurina operator + (float pret, Figurina F);
        friend Figurina operator * (float pret, Figurina F);
        friend float operator + (Manga M, Figurina F);
        friend float operator + (Figurina F, Manga M);
        friend float operator + (Tricouri T, Figurina F);
        friend float operator + (Figurina F, Tricouri T);
        friend istream& operator >> (istream& in, Figurina& F);
        friend ostream& operator << (ostream& out, const Figurina& F);

        /// Metode
        void scumpeste();

        /// Setters
        void setNumeCaracter(string numeCaracter){this->numeCaracter = numeCaracter;}
        void setPret(float pret){this->pret = pret;}
        void setNumeProducator(string numeProducator){this->numeProducator = numeProducator;}
        void setNumeSerie(string numeSerie){this->numeSerie = numeSerie;}
        void setInaltime(int inaltime){this->inaltime = inaltime;}
        void setNrBucatiDispon(int nrBucatiDispon){this->nrBucatiDispon = nrBucatiDispon;}

        /// Getters
        string getNumeCaracter() const {return this->numeCaracter;}
        float getPret() const {return this->pret;}
        string getNumeProducator() const {return this->numeProducator;}
        string getNumeSerie() const {return this->numeSerie;}
        int getInaltime() const {return this->inaltime;}
        int getNrBucatiDispon() const {return this->nrBucatiDispon;}

        /// Destructor
        ~Figurina();
};

/// --------CONSTRUCTORI--------
Figurina::Figurina(){
    this->numeCaracter = "";
    this->pret = 0.0;
    this->numeProducator = "";
    this->numeSerie = "";
    this->inaltime = 0;
    this->nrBucatiDispon = 0;
}

Figurina::Figurina(string numeCaracter, int inaltime, float pret, string numeProducator, string numeSerie, int nrBucatiDispon){
    this->numeCaracter = numeCaracter;
    this->pret = pret;
    this->numeProducator = numeProducator;
    this->numeSerie = numeSerie;
    this->inaltime = inaltime;
    this->nrBucatiDispon = nrBucatiDispon;
}

Figurina::Figurina(string numeCaracter, int inaltime){
    this->numeCaracter = numeCaracter;
    this->pret = 0.0;
    this->numeProducator = "Anonim";
    this->numeSerie = "Anonim";
    this->inaltime = inaltime;
    this->nrBucatiDispon = 0;
}

Figurina::Figurina(string numeCaracter, string numeProducator, string numeSerie){
    this->numeCaracter = numeCaracter;
    this->pret = 0.0;
    this->numeProducator = numeProducator;
    this->numeSerie = numeSerie;
    this->inaltime = 0;
    this->nrBucatiDispon = 0;
}

Figurina::Figurina(const Figurina& F){
    this->numeCaracter = F.numeCaracter;
    this->pret = F.pret;
    this->numeProducator = F.numeProducator;
    this->numeSerie = F.numeSerie;
    this->inaltime = F.inaltime;
    this->nrBucatiDispon = F.nrBucatiDispon;
}
///####################################################

/// --------OPERATORI--------
Figurina& Figurina::operator = (const Figurina& F){
    if(this != &F){
        this->numeCaracter = F.numeCaracter;
        this->pret = F.pret;
        this->numeProducator = F.numeProducator;
        this->numeSerie = F.numeSerie;
        this->inaltime = F.inaltime;
        this->nrBucatiDispon = F.nrBucatiDispon;
    }
    return *this;
}

bool Figurina::operator < (const Figurina& F){
    return this->pret < F.pret;
}

bool Figurina::operator == (const Figurina& F){
    return this->numeCaracter == F.numeCaracter && this->pret == F.pret && this->numeProducator == F.numeProducator && this->numeSerie == F.numeSerie && this->inaltime == F.inaltime && this->nrBucatiDispon == F.nrBucatiDispon;
}

Figurina Figurina::operator + (const Figurina& F){
    Figurina aux(*this);
    aux.pret += F.pret;
    return aux;
}

Figurina Figurina::operator + (float pret){
    Figurina aux(*this);
    aux.pret += pret;
    return aux;
}

Figurina operator + (float pret, Figurina F){
    return (F + pret);
}

Figurina Figurina::operator * (const Figurina& F){
    Figurina aux(*this);
    aux.pret *= F.pret;
    return aux;
}

Figurina Figurina::operator * (float pret){
    Figurina aux(*this);
    aux.pret *= pret;
    return aux;
}

Figurina operator * (float pret, Figurina F){
    return (F * pret);
}

Figurina& Figurina::operator -- (){
    this->nrBucatiDispon--;
    return (*this);
}

Figurina Figurina::operator -- (int){
    Figurina aux(*this);
    this->nrBucatiDispon--;
    return aux;
}

char Figurina::operator [] (int index){
    if(index < 0 || index >= this->numeCaracter.size()){
        throw runtime_error("Index invalid!");
    }
    else{
        return this->numeCaracter[index];
    }
}

float operator + (Manga M, Figurina F){
    return M + F.pret;
}

float operator + (Figurina F, Manga M){
    return (M + F);
}

float operator + (Tricouri T, Figurina F){
    return T + F.pret;
}

float operator + (Figurina F, Tricouri T){
    return (T + F);
}

istream& operator >> (istream& in, Figurina& F){
    cout << "Numele caracterului: ";
    in.get();
    getline(in, F.numeCaracter);

    cout << "Numele seriei din care face parte caracterul: ";
    in.get();
    getline(in, F.numeSerie);

    cout << "Numele producatorului: ";
    in.get();
    getline(in, F.numeProducator);

    cout << "Inaltime: ";
    in >> F.pret;

    cout << "Numarul de bucati disponibile: ";
    in >> F.nrBucatiDispon;

    cout << "Pret: ";
    in >> F.pret;

    return in;
}

ostream& operator << (ostream& out, const Figurina& F){
    out << "Numele seriei: " << F.numeSerie << "\n";

    out << "Numele caracterului: " << F.numeCaracter << "\n";

    out << "Numele producatorului: " << F.numeProducator << "\n";

    out << "Inaltime: " << F.inaltime << " cm\n";

    out << "Pret: " << F.pret << " lei\n";
    
    return out;
}
///####################################################

/// --------METODE--------
void Figurina::scumpeste(){
    this->pret = this->pret + (0.1 * this->pret);
}
///####################################################

/// --------DESTRUCTOR--------
Figurina::~Figurina(){
    this->numeCaracter = "";
    this->pret = 0.0;
    this->numeProducator = "";
    this->numeSerie = "";
    this->inaltime = 0;
    this->nrBucatiDispon = 0;
}
///####################################################


class Meniu{
    private:
        Client C;
        vector<Client*> database;
        vector<Manga*> listaManga;
        vector<Tricouri*> listaTricouri;
        vector<Figurina*> listaFigurine;
    public:
        /// Main
        void umpleStoc();
        void start();
        void clearScreen();

        /// Client
        void becomeMember();
        bool checkBalance(float pret);

        /// Manga
        void sortareDupaRating();
        void afisListaDupaRating();

        /// Tricou
        void afisListaTricouri(char marime);
        int checkMarime(char marime);
        int realIndex(int response, char marime);

        /// Figurina
        void sortareDupaPret();
        void afisListaFigurine();

        /// Destructor
        ~Meniu();
};

void Meniu::umpleStoc(){
    int r1[] = {7, 6, 10, 8, 9, 9, 10, 8, 7, 10};
    int r2[] = {10, 6, 9, 6, 10, 8, 9, 10, 10, 8};
    int r3[] = {10, 10, 9, 8, 9, 7, 8, 9, 10, 9};
    int r4[] = {8, 8, 8, 6, 7, 10, 10, 9, 10, 9};
    int r5[] = {8, 7, 9, 4, 7, 8, 9, 9, 5, 10};
    int r6[] = {7, 7, 10, 8, 2, 6, 8, 5, 6, 2};
    int r7[] = {7, 7, 8, 2, 9, 10, 9, 2, 7, 6};
    int r8[] = {9, 6, 6, 5, 7, 9, 9, 6, 8, 4};
    int r9[] = {8, 8, 7, 6, 10, 8, 9, 6, 9, 5};
    int r10[] = {6, 8, 10, 4, 8, 5, 5, 10, 4, 7};
    Manga M1("Bleach", 10, r1, 52.0, 272, 10);
    Manga M2("Naruto", 10, r2, 52.0, 200, 10);
    Manga M3("One Piece", 10, r3, 50.0, 254, 10);
    Manga M4("Demon Slayer", 10, r4, 70.0, 232, 10);
    Manga M5("Dragon Ball", 10, r5, 45.5, 255, 10);
    Manga M6("Gintama", 10, r5, 60.0, 197, 10);
    Manga M7("Death Note", 10, r5, 52.0, 249, 10);
    Manga M8("Attack on Titan", 10, r5, 70.0, 299, 10);
    Manga M9("Black Clover", 10, r5, 50.0, 147, 10);
    Manga M10("My Hero Academia", 10, r5, 52.0, 251, 10);
    this->listaManga.push_back(new Manga(M1));
    this->listaManga.push_back(new Manga(M2));
    this->listaManga.push_back(new Manga(M3));
    this->listaManga.push_back(new Manga(M4));
    this->listaManga.push_back(new Manga(M5));
    this->listaManga.push_back(new Manga(M6));
    this->listaManga.push_back(new Manga(M7));
    this->listaManga.push_back(new Manga(M8));
    this->listaManga.push_back(new Manga(M9));
    this->listaManga.push_back(new Manga(M10));

    Tricouri T1('L', 70.0, "negru", "PCMerch", 10);
    Tricouri T2('S', 83.5, "alb", "Difuzed", 20);
    Tricouri T3('M', 69.5, "verde", "Difuzed", 20);
    Tricouri T4('L', 83.5, "roz", "Difuzed", 10);
    Tricouri T5('M', 116.0, "albastru", "Spiral Direct", 20);
    Tricouri T6('L', 80.0, "alb", "AbyStyle", 20);
    Tricouri T7('S', 139.0, "negru", "CRUSH PUBLISHING", 20);
    Tricouri T8('M', 100.0, "verde", "Difuzed", 20);
    Tricouri T9('L', 55.0, "rosu", "CRUSH PUBLISHING", 20);
    Tricouri T10('M', 90.0, "negru", "Spiral Direct", 20);
    this->listaTricouri.push_back(new Tricouri(T1));
    this->listaTricouri.push_back(new Tricouri(T2));
    this->listaTricouri.push_back(new Tricouri(T3));
    this->listaTricouri.push_back(new Tricouri(T4));
    this->listaTricouri.push_back(new Tricouri(T5));
    this->listaTricouri.push_back(new Tricouri(T6));
    this->listaTricouri.push_back(new Tricouri(T7));
    this->listaTricouri.push_back(new Tricouri(T8));
    this->listaTricouri.push_back(new Tricouri(T9));
    this->listaTricouri.push_back(new Tricouri(T10));

    Figurina F1("Akaza", 19, 1126.0, "Aniplex", "Demon Slayer", 1);
    Figurina F2("Levi Ackerman", 17, 1196.25, "Kotobukiya", "Attack On Titan", 1);
    Figurina F3("Nezuko", 18, 987.0, "MegaHouse", "Demon Slayer", 1);
    Figurina F4("Katsuki Bakugo", 21, 1081.5, "Takara Tomy", "My Hero Academia", 1);
    Figurina F5("Gojo Satoru", 22, 892.0, "Kotobukiya", "Jujutsu Kaisen 0", 1);
    this->listaFigurine.push_back(new Figurina(F1));
    this->listaFigurine.push_back(new Figurina(F2));
    this->listaFigurine.push_back(new Figurina(F3));
    this->listaFigurine.push_back(new Figurina(F4));
    this->listaFigurine.push_back(new Figurina(F5));

    cout << "Hai sa adaugam produse in stoc! Ce ati dori sa adaugati?\n 1 -> Manga\n 2 -> Tricou\n 3 -> Figurina\n 4 -> Nu doresc sa adaug\n";
    int response;
    cout << "Raspuns: ";
    cin >> response;
    switch(response){
        case 1:{
            clearScreen();
            cout << "\nAceasta este lista cu produsele disponibile:\n\n";
            for(int i = 0; i < this->listaManga.size(); ++i){
                cout << i + 1 << ". " << (*this->listaManga[i]) << "\n\n";
            }
            cout << "Introduceti numarul de Manga pe care doriti sa le adaugati: ";
            cin >> response;
            clearScreen();
            cout << "Introduceti detaliile despre cele " << response << " Manga pe care doriti sa le adaugati:\n\n";
            while(response){
                Manga Add;
                cin >> Add;
                this->listaManga.push_back(new Manga(Add));
                response--;
            }
            break;
        }
        case 2:{
            clearScreen();
            cout << "\nAceasta este lista cu produsele disponibile:\n\n";
            for(int i = 0; i < this->listaTricouri.size(); ++i){
                cout << i + 1 << ". " << (*this->listaTricouri[i]) << "\n\n";
            }
            cout << "Introduceti numarul de tricouri pe care doriti sa le adaugati: ";
            cin >> response;
            clearScreen();
            cout << "Introduceti detaliile despre cele " << response << " tipuri de tricouri pe care doriti sa le adaugati:\n\n";
            while(response){
                Tricouri Add;
                cin >> Add;
                this->listaTricouri.push_back(new Tricouri(Add));
                response--;
            }
            break;
        }
        case 3:{
            clearScreen();
            cout << "\nAceasta este lista cu produsele disponibile:\n\n";
            for(int i = 0; i < this->listaFigurine.size(); ++i){
                cout << i + 1 << ". " << (*this->listaFigurine[i]) << "\n\n";
            }
            cout << "Introduceti numarul de Manga pe care doriti sa le adaugati: ";
            cin >> response;
            clearScreen();
            cout << "Introduceti detaliile despre cele " << response << " figurine pe care doriti sa le adaugati:\n\n";
            while(response){
                Figurina Add;
                cin >> Add;
                this->listaFigurine.push_back(new Figurina(Add));
                response--;
            }
            break;
        }
        case 4:{
            break;
        }
    }
}

void Meniu::sortareDupaRating(){
    sort(this->listaManga.begin(), this->listaManga.end(), [] (auto const& M1, auto const& M2){
        return *M1 > *M2;
    });
}

void Meniu::afisListaDupaRating(){
    int cnt = 1;
    for(auto m : this->listaManga){
        cout << cnt << ": ";
        (*m).afisDate();
        cnt++;
    }
    cout << "\n";
}

void Meniu::clearScreen(){
    system("CLS");
}

bool Meniu::checkBalance(float pret){
    if(this->C.getBuget() >= pret){
        return true;
    }
    return false;
}

void Meniu::afisListaTricouri(char marime){
    int cnt = 0;
    for(int i = 0; i < this->listaTricouri.size(); ++i){
        if((*this->listaTricouri[i]).getMarime() == marime){
            cout << ++cnt << ". " << (*this->listaTricouri[i]) << "\n";
        }
    }
    cout << "\n";
}

int Meniu::checkMarime(char marime){
    int cnt = 0;
    for(auto it : this->listaTricouri){
        if((*it).getMarime() == marime){
            cnt++;
        }
    }
    return cnt;
}

int Meniu::realIndex(int response, char marime){
    int index = 0;
    int cnt = 0;
    for(auto it : this->listaTricouri){
        if((*it).getMarime() == marime){
            cnt++;
            if(cnt == response){
                return index;
            }
        }
        index++;
    }
}

void Meniu::sortareDupaPret(){
    sort(this->listaFigurine.begin(), this->listaFigurine.end(), [] (auto const& F1, auto const& F2){
        return *F1 < *F2;
    });
}

void Meniu::afisListaFigurine(){
    int cnt = 0;
    for(int i = 0; i < this->listaFigurine.size(); ++i){
        cout << i + 1 << ". " << (*this->listaFigurine[i]) << "\n";
    }
    cout << "\n";
}

void Meniu::becomeMember(){
    cout << "Super! Introduceti urmatoarele date: \n\n";
    cin >> this->C;
    this->C.setMembership(true);
    this->database.push_back(new Client(C));
    cout << "\n\nAcestea sunt detaliile de pe carnetul tau de membru: \n\n";
    cout << this->C;
}

void Meniu::start(){
    umpleStoc();
    clearScreen();
    C.intraInMagazin();
    cout << "Salut " << this->C.getPrenume() << "! Bine ai venit la MangaShop! Ce ai dori sa cumperi?\n\n";
    bool on = true;
    while(on){
        cout << " 1 -> Manga\n 2 -> Tricou\n 3 -> Figurina\n\n";
        int response;
        cout << "Raspuns: ";
        cin >> response;
        clearScreen();
        switch(response){
            case 1:{
                cout << "Aici ai o lista cu seriile aflate in stoc:\n";
                sortareDupaRating();
                afisListaDupaRating();
                cout << "Ce Manga va intereseaza?\n";
                Manga M;
                string nume;
                cin >> nume;
                M.setNume(nume);
                for(int i = 0; i < this->listaManga.size(); ++i){
                    if((*this->listaManga[i]) == M){
                        cout << (*this->listaManga[i]) << "\n";
                        cout << "Buget: " << this->C.getBuget() << " lei\n\n";
                        cout << "Cumparati?\n 1 -> Da\n 2 -> Nu\n";
                        cout << "Raspuns: ";
                        cin >> response;
                        cout << "\n";
                        if(response == 2){
                            break;
                        }
                        else{
                            if(checkBalance((*this->listaManga[i]).getPret())){
                                this->C.setBuget(this->C.getBuget() - (*this->listaManga[i]).getPret());
                                if((*this->listaManga[i]).getNrBucatiDispon() > 1){
                                    (*this->listaManga[i])--;
                                    if((*this->listaManga[i]).getNrBucatiDispon() < 10){
                                        (*this->listaManga[i]).scumpeste();
                                    }
                                }
                                else{
                                    (*this->listaManga[i]).setNrBucatiDispon(0);
                                    this->listaManga.erase(this->listaManga.begin() + i);
                                }
                                cout << "Doriti sa acordati o nota acestei serii?\n";
                                cout << " 1 -> Da\n 2 -> Nu\n";
                                cout << "Raspuns: ";
                                cin >> response;
                                cout << "\n";
                                if(response == 1){
                                    cout << "Super! Scrieti o nota de la 1 la 10 corespunzatoare feedback-ului vostru: ";
                                    int nota;
                                    cin >> nota;
                                    if(nota >= 1 && nota <= 10){
                                        (*this->listaManga[i]).giveRating(nota);
                                    }
                                    else{
                                        throw runtime_error("Nu se poate acorda aceasta nota!");
                                    }
                                }
                            }
                            else{
                                cout << "Nu ai suficienti bani... Mai ai " << this->C.getBuget() << " lei\n";
                            }
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{
                cout << "Ce marime porti? (S, M sau L)\n";
                cout << "Raspuns: ";
                char marime;
                cin >> marime;
                marime = toupper(marime);
                int cnt = checkMarime(marime);
                if(cnt){
                    cout << "\nAici ai o lista cu toate tricourile aflate in stoc:\n\n";
                    afisListaTricouri(marime);
                    cout << "Buget: " << this->C.getBuget() << " lei\n\n";
                    cout << "Ce v-ar interesa?\nIntroduceti indexul tricoului corespunzator: ";
                    cin >> response;
                    if(response >= 1 && response <= cnt){
                        response = realIndex(response, marime);
                        if(checkBalance((*this->listaTricouri[response]).getPret())){
                            this->C.setBuget(this->C.getBuget() - (*this->listaTricouri[response]).getPret());
                            if((*this->listaTricouri[response]).getNrBucatiDispon() > 1){
                                (*this->listaTricouri[response])--;
                                if((*this->listaTricouri[response]).getNrBucatiDispon() < 10){
                                    (*this->listaTricouri[response]).scumpeste();
                                }
                            }
                            else{
                                (*this->listaTricouri[response]).setNrBucatiDispon(0);
                                this->listaTricouri.erase(this->listaTricouri.begin() + response);
                            }
                        }
                        else{
                            cout << "\nNu ai suficienti bani... Mai ai " << this->C.getBuget() << " lei\n\n";
                        }
                    }
                    else{
                        throw runtime_error("Nu exista un tricou cu acest numar!");
                    }
                }
                else{
                    cout << "\nNe pare rau, aceasta marime nu mai este disponibila.\n";
                }
                break;
            }
            case 3:{
                cout << "Aceastea sunt figurinele aflate in stoc (ordine crescatoare dupa pret):\n\n\n";
                sortareDupaPret();
                afisListaFigurine();
                cout << "\nSe afla in aceasta lista o figurina pe care doriti sa o cumparati?\n 1 -> Da\n 2 -> Nu\n";
                cout << "Raspuns: ";
                cin >> response;
                if(response == 1){
                    cout << "\n\nIntroduceti indexul figurinei corespunzatoare: ";
                    cin >> response;
                    if(checkBalance((*this->listaFigurine[response - 1]).getPret())){
                        this->C.setBuget(this->C.getBuget() - (*this->listaFigurine[response - 1]).getPret());
                        if((*this->listaFigurine[response - 1]).getNrBucatiDispon() > 1){
                            (*this->listaFigurine[response - 1])--;
                            if((*this->listaFigurine[response - 1]).getNrBucatiDispon() < 10){
                                (*this->listaFigurine[response - 1]).scumpeste();
                            }
                        }
                        else{
                            (*this->listaFigurine[response - 1]).setNrBucatiDispon(0);
                            this->listaFigurine.erase(this->listaFigurine.begin() + response - 1);
                        }
                    }
                    else{
                        cout << "\nNu ai suficienti bani... Mai ai " << this->C.getBuget() << " lei\n";
                    }
                }
                break;
            }
            default:{
                throw runtime_error("Index invalid!");
            }
        }
        cout << "\nMai doriti sa cumparati ceva?\n";
        cout << "Buget: " << this->C.getBuget() << " lei\n";
        cout << " 1 -> Da\n 2 -> Nu\n";
        cout << "Raspuns: ";
        cin >> response;
        if(response == 2){
            clearScreen();
            cout << "Doriti sa deveniti membru MangaShop? :)\n 1 -> Da\n 2 -> Nu\n";
            cout << "Raspuns: ";
            cin >> response;
            cout << "\n";
            if(response == 1){
                becomeMember();
                cout << "\nMultumim pentru timpul acordat, o zi buna!";
            }
            else{
                cout << "Multumim pentru timpul acordat, o zi buna!\n";
            }
            on = false;
        }
        else{
            clearScreen();
        }
    }
}

Meniu::~Meniu(){
    this->listaFigurine.clear();
    this->listaTricouri.clear();
    this->listaManga.clear();
    this->database.clear();
    this->C.~Client();
}

int main(){
    Meniu M;
    M.start();
    return 0;
}