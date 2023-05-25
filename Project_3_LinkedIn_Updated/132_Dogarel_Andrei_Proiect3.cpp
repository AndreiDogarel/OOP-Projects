#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <typeinfo>


using namespace std;

ifstream f("accounts.in");
ofstream g("accounts.out");

class IOInterface {
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class PasswordException : public exception{
private:
    string errorMessage;

public:
    PasswordException(string error){
        this->errorMessage = error;
    }
    const string showError() const throw() {
        return this->errorMessage;
    }
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class EmailException : public exception{
private:
    string errorMessage;

public:
    EmailException(string error){
        this->errorMessage = error;
    }
    const string showError() const throw() {
        return this->errorMessage;
    }
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class IndexException : public exception {
public:
    const char* what() const throw() {
        return "Index invalid!";
    }
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Job;

class Client{
protected:
    string email;
    string parola;
    string nume;
    string prenume;
    int varsta;
    string ocupatie;
    int aniExperienta;
    bool licentiat;
    vector<Job*> jobOfferts;

public:
    //------- CONSTRUCTORI -------//
    Client();
    Client(string email, string parola, string nume, string prenume, int varsta, string ocupatie, int aniExperienta, bool licentiat, const vector<Job*>& jobOfferts);
    Client(const Client& obj);

    //------- OPERATORI -------//
    Client& operator = (const Client& obj);
    friend istream& operator >> (istream& in, Client& obj);
    friend ostream& operator << (ostream& out, const Client& obj);
    bool operator < (const Client& obj){
        return this->aniExperienta < obj.aniExperienta;
    }
    bool operator > (const Client& obj){
        return this->aniExperienta > obj.aniExperienta;
    }

    //------- GETTERS & SETTERS -------//
    string getEmail() const {return this->email;}
    string getParola() const {return this->parola;}
    string getNume() const {return this->nume;}
    string getPrenume() const {return this->prenume;}
    int getVarsta() const {return this->varsta;}
    string getOcupatie() const {return this->ocupatie;}
    int getAniExperienta() const {return this->aniExperienta;}
    bool getLicence() const {return this->licentiat;}
    vector<Job*> getJobOfferts() const {return this->jobOfferts;}

    //------- METODE -------//
    virtual istream& creeazaCont(istream& in);
    virtual ostream& afisProfilUser(ostream& out) const;
    void receiveJobOffer(Job* offer){this->jobOfferts.push_back(offer);}
    void showJobOfferts();
    virtual void modificaProfil();

    //------- DESTRUCTOR -------//
    virtual ~Client(){}
};

Client::Client(){
    this->email = "";
    this->parola = "";
    this->nume = "";
    this->prenume = "";
    this->varsta = 0;
    this->ocupatie = "";
    this->aniExperienta = 0;
    this->licentiat = false;
    this->jobOfferts = {};
}

Client::Client(string email, string parola, string nume, string prenume, int varsta, string ocupatie, int aniExperienta, bool licentiat, const vector<Job*>& jobOfferts){
    this->email = email;
    this->parola = parola;
    this->nume = nume;
    this->prenume = prenume;
    this->varsta = varsta;
    this->ocupatie = ocupatie;
    this->aniExperienta = aniExperienta;
    this->licentiat = licentiat;
    this->jobOfferts = jobOfferts;
}

Client::Client(const Client& obj){
    this->email = obj.email;
    this->parola = obj.parola;
    this->nume = obj.nume;
    this->prenume = obj.prenume;
    this->varsta = obj.varsta;
    this->ocupatie = obj.ocupatie;
    this->aniExperienta = obj.aniExperienta;
    this->licentiat = obj.licentiat;
    this->jobOfferts = obj.jobOfferts;
}

Client& Client::operator = (const Client& obj){
    if(this != &obj){
        this->email = obj.email;
        this->parola = obj.parola;
        this->nume = obj.nume;
        this->prenume = obj.prenume;
        this->varsta = obj.varsta;
        this->ocupatie = obj.ocupatie;
        this->aniExperienta = obj.aniExperienta;
        this->licentiat = obj.licentiat;
        this->jobOfferts = obj.jobOfferts;
    }
    return *this;
}

istream& Client::creeazaCont(istream& in){
    cout << "Nume: ";
    in >> this->nume;

    cout << "Prenume: ";
    in >> this->prenume;

    cout << "Varsta: ";
    in >> this->varsta;

    bool valid = false;
    while(!valid){
        cout << "Email: ";
        in >> this->email;
        try{
            if(this->email.find('@') == -1){
                throw EmailException("Adresa de email invalida! Aceasta trebuie sa contina @");
            }
            else{
                valid = true;
            }
        }
        catch(const EmailException& error){
            cout << error.showError() << "\n";
        }
    }

    valid = false;
    while(!valid){
        char ch;
        string password = "";
        const char ENTER = 13;
        cout << "Parola: ";
        while((ch = _getch()) != ENTER){
            if(ch != 8 && ch != 27 && ch != 32){
                password += ch;
                cout << '*';
            }
        }
        this->parola = password;
        bool uppercase = false;
        bool lowercase = false;
        bool digit = false;
        bool minLength = false;
        try{
            for(auto ch : this->parola){
                if(isupper(ch)){
                    uppercase = true;
                }
                if(islower(ch)){
                    lowercase = true;
                }
                if(isdigit(ch)){
                    digit = true;
                }
            }
            if(this->parola.size() >= 8){
                minLength = true;
            }
            if(!uppercase){
                throw PasswordException("Parola trebuie sa contina minim o litera mare!");
            }
            if(!lowercase){
                throw PasswordException("Parola trebuie sa contina minim o litera mica!");
            }
            if(!digit){
                throw PasswordException("Parola trebuie sa contina minim o cifra!");
            }
            if(!minLength){
                throw PasswordException("Parola trebuie sa contina minim 8 caractere!");
            }
            valid = true;
        }
        catch(const PasswordException& error){
            cout << error.showError()<< "\n";
        }
    }

    cout << "\nLucrez ca:\n 1 -> Web Developer\n 2 -> Software Developer\n 3 -> Mobile Application Developer\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            in >> response;
            if(response < 1 || response > 3){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        cout << "Ce specializare?\n 1 -> Front-End Developer\n 2 -> Back-End Developer\n 3 -> Full-Stack Developer\n";
        while(true){
            cout << "Raspuns: ";
            try{
                in >> response;
                if(response < 1 || response > 3){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(response == 1){
            this->ocupatie = "Front-End Developer";
        }
        else if(response == 2){
            this->ocupatie = "Back-End Developer";
        }
        else{
            this->ocupatie = "Full-Stack Developer";
        }
    }
    else if(response == 2){
        this->ocupatie = "Software Developer";
    }
    else{
        this->ocupatie = "Mobile Application Developer";
    }

    cout << "Ani de experienta: ";
    in >> this->aniExperienta;

    cout << "Ai terminat o facultate in domeniu?\n 1 -> Da\n 2 -> Nu\n";
    while(true){
        cout << "Raspuns: ";
        try{
            in >> response;
            if(response < 1 || response > 2){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        this->licentiat = true;
    }
    else{
        this->licentiat = false;
    }

    return in;
}

ostream& Client::afisProfilUser(ostream& out) const {
    out << "Nume: " << this->nume << "\n";
    out << "Prenume: " << this->prenume << "\n";
    out << "Varsta: " << this->varsta << "\n";
    out << "Specializare: " << this->ocupatie << "\n";
    out << "Ani de experienta: " << this->aniExperienta << "\n";
    out << "Licentiat: ";
    if(this->licentiat){
        out << "Da\n";
    }
    else{
        out << "Nu\n";
    }

    return out;
}

void Client::showJobOfferts(){
    for(int i = 0; i < this->jobOfferts.size(); ++i){
        cout << i + 1 << ". " << this->jobOfferts[i] << "\n";
    }
    cout << "1 -> Back\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response != 1){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
}

void Client::modificaProfil(){
    bool update = true;
    while(update){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << " 1 -> Email\n 2 -> Parola\n 3 -> Nume\n 4 -> Prenume\n 5 -> Varsta\n 6 -> Specializare\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 6){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                string email;
                bool valid = false;
                while(!valid){
                    cout << "Introduceti noua adresa de email: ";
                    cin >> email;
                    try{
                        if(email.find('@') == -1){
                            throw EmailException("Adresa de email invalida! Incercati inca o data");
                        }
                        else{
                            valid = true;
                        }
                    }
                    catch(const EmailException& error){
                        cout << error.showError() << "\n";
                    }
                }
                if(this->email != email){
                    this->email = email;
                    cout << "Modificari realizate cu succes!\n";
                }
                else{
                    cout << "Aceasta adresa de email este deja folosita!\n";
                }
                break;
            }
            case 2:{
                string parola;
                bool valid = false;
                while(!valid){
                    cout << "Introduceti noua parola: ";
                    char ch;
                    string password = "";
                    const char ENTER = 13;
                    while((ch = _getch()) != ENTER){
                        if(ch != 8 && ch != 27 && ch != 32){
                            password += ch;
                            cout << '*';
                        }
                    }
                    this->parola = password;
                    bool uppercase = false;
                    bool lowercase = false;
                    bool digit = false;
                    bool minLength = false;
                    try{
                        for(auto ch : parola){
                            if(isupper(ch)){
                                uppercase = true;
                            }
                            if(islower(ch)){
                                lowercase = true;
                            }
                            if(isdigit(ch)){
                                digit = true;
                            }
                        }
                        if(parola.size() >= 8){
                            minLength = true;
                        }
                        if(!uppercase){
                            throw PasswordException("Parola trebuie sa contina minim o litera mare!");
                        }
                        if(!lowercase){
                            throw PasswordException("Parola trebuie sa contina minim o litera mica!");
                        }
                        if(!digit){
                            throw PasswordException("Parola trebuie sa contina minim o cifra!");
                        }
                        if(!minLength){
                            throw PasswordException("Parola trebuie sa contina minim 8 caractere!");
                        }
                        valid = true;
                    }
                    catch(const PasswordException& error){
                        cout << error.showError() << "\n";
                    }
                }
                if(this->parola != parola){
                    this->parola = parola;
                    cout << "Modificari realizate cu succes!\n";
                }
                else{
                    cout << "Aceasta parola este deja folosita!\n";
                }
                break;
            }
            case 3:{
                cout << "Introduceti numele de familie: ";
                cin >> this->nume;
                cout << "Modificari realizate cu succes!\n";
                break;
            }
            case 4:{
                cout << "Introduceti prenumele: ";
                cin >> this->prenume;
                cout << "Modificari realizate cu succes!\n";
                break;
            }
            case 5:{
                cout << "Introduceti varsta: ";
                cin >> this->varsta;
                cout << "Modificari realizate cu succes!\n";
                break;
            }
            case 6:{
                cout << "Lucrez ca:\n 1 -> Web Developer\n 2 -> Software Developer\n 3 -> Mobile Application Developer\n";
                int response;
                while(true){
                    cout << "Raspuns: ";
                    try{
                        cin >> response;
                        if(response < 1 || response > 3){
                            throw IndexException();
                        }
                        else{
                            break;
                        }
                    }
                    catch(const IndexException& error){
                        cout << error.what() << "\n";
                    }
                }
                if(response == 1){
                    cout << "Ce specialitate?\n 1 -> Front-End Developer\n 2 -> Back-End Developer\n 3 -> Full-Stack Developer\n";
                    cout << "Raspuns: ";
                    while(true){
                        try{
                            cin >> response;
                            if(response < 1 || response > 3){
                                throw IndexException();
                            }
                            else{
                                break;
                            }
                        }
                        catch(const IndexException& error){
                            cout << error.what() << "\n";
                        }
                    }
                    if(response == 1){
                        this->ocupatie = "Front-End Developer";
                    }
                    else if(response == 2){
                        this->ocupatie = "Back-End Developer";
                    }
                    else{
                        this->ocupatie = "Full-Stack Developer";
                    }
                    cout << "Modificari realizate cu succes!\n";
                }
                else if(response == 2){
                    this->ocupatie = "Software Developer";
                    cout << "Modificari realizate cu succes!\n";
                }
                else{
                    this->ocupatie = "Mobile Application Developer";
                    cout << "Modificari realizate cu succes!\n";
                }
                break;
            }
        }
        cout << "Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 2){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(response == 2){
            update = false;
        }
    }
}

istream& operator >> (istream& in, Client& obj){
    return obj.creeazaCont(in);
}

ostream& operator << (ostream& out, const Client& obj){
    return obj.afisProfilUser(out);
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Job : public IOInterface{
protected:
    vector<Client*> jobApplicants;
    int nrLocuriDispon;
    string numeJob;
    int salariuDeBaza;
    struct locatie {
        string numeTara;
        string numeOras;
        string numeStrada;
        int nrStrada;
    } locatieJob;
    int nrAniExperientaMin;
    vector<string> limbajeCerute;
    bool easyApply;

public:
    //------- CONSTRUCTORI -------//
    Job();
    Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon);
    Job(const Job& obj);

    //------- OPERATORI -------//
    Job& operator = (const Job& obj);
    friend istream& operator >> (istream& in, Job& obj){
        return obj.citire(in);
    }
    friend ostream& operator << (ostream& out, const Job& obj){
        return obj.afisare(out);
    }

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    int getSalariu() const {return this->salariuDeBaza;}
    string getNumeJob() const {return this->numeJob;}
    locatie getLocatieJob() const {return this->locatieJob;}
    int getNrAniExperienta() const {return this->nrAniExperientaMin;}
    vector<string> getLimbajeNecesare() const {return this->limbajeCerute;}
    bool getEasyApply() const {return this->easyApply;}
    vector<Client*> getJobApplicants() const {return this->jobApplicants;}
    int getNrLocuriDispon() const {return this->nrLocuriDispon;}

    void setSalariu(int salariu){this->salariuDeBaza = salariu;}
    void setNumeJob(string numeJob){this->numeJob = numeJob;}
    void setLocatieJob(locatie loc){this->locatieJob = loc;}
    void setNrAniExpMin(int nrAniExpMin){this->nrAniExperientaMin = nrAniExpMin;}
    void setLimbajeNecesare(const vector<string>& limbajeNecesare){this->limbajeCerute = limbajeNecesare;}
    void setEasyApply(bool easyApply){this->easyApply = easyApply;}
    void setNrLocDispon(int nrLocDispon){this->nrLocuriDispon = nrLocDispon;}

    //------- METODE -------//
    virtual void modificaAnunt() = 0;
    template<class T>
    void addJobApplicant(T* app){
        this->jobApplicants.push_back(app);
    }
    void showJobApplicants();

    //------- DESTRUCTOR -------//
    virtual ~Job();
};

Job::Job(){
    this->numeJob = "";
    this->salariuDeBaza = 0;
    this->locatieJob.nrStrada = 0;
    this->locatieJob.numeOras = "";
    this->locatieJob.numeStrada = "";
    this->locatieJob.numeTara = "";
    this->nrAniExperientaMin = 0;
    this->limbajeCerute = {};
    this->easyApply = false;
    this->jobApplicants = {};
    this->nrLocuriDispon = 0;
}

Job::Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon){
    this->numeJob = numeJob;
    this->salariuDeBaza = salariuDeBaza;
    this->locatieJob = locatieJob;
    this->nrAniExperientaMin = nrAniExperientaMin;
    this->limbajeCerute = limbajeCerute;
    this->easyApply = easyApply;
    this->jobApplicants = jobApplicants;
    this->nrLocuriDispon = 0;
}

Job::Job(const Job& obj){
    this->numeJob = obj.numeJob;
    this->salariuDeBaza = obj.salariuDeBaza;
    this->locatieJob = obj.locatieJob;
    this->nrAniExperientaMin = obj.nrAniExperientaMin;
    this->limbajeCerute = obj.limbajeCerute;
    this->easyApply = obj.easyApply;
    this->jobApplicants = obj.jobApplicants;
    this->nrLocuriDispon = obj.nrLocuriDispon;
}

Job& Job::operator = (const Job& obj){
    if(this != &obj){
        this->numeJob = obj.numeJob;
        this->salariuDeBaza = obj.salariuDeBaza;
        this->locatieJob = obj.locatieJob;
        this->nrAniExperientaMin = obj.nrAniExperientaMin;
        this->limbajeCerute = obj.limbajeCerute;
        this->easyApply = obj.easyApply;
        this->jobApplicants = obj.jobApplicants;
        this->nrLocuriDispon = obj.nrLocuriDispon;
    }
    return *this;
}

istream& Job::citire(istream& in){
    cout << "Numele Job-ului: ";
    in.get();
    getline(in, this->numeJob);

    cout << "Salariu (euro/luna): ";
    in >> this->salariuDeBaza;

    cout << "Locatia Job-ului:\n";
    cout << "  Nume Tara: ";
    in.get();
    getline(in, this->locatieJob.numeTara);
    cout << "  Nume Oras: ";
    getline(in, this->locatieJob.numeOras);
    cout << "  Nume Strada: ";
    getline(in, this->locatieJob.numeStrada);
    cout << "  Numarul Strazii: ";
    in >> this->locatieJob.nrStrada;

    cout << "Numarul minim de ani de experienta necesari: ";
    in >> this->nrAniExperientaMin;

    cout << "In cadrul acestui job se va lucra cu urmatoarele limbaje de programare: ";
    string limbaje;
    in.get();
    getline(in, limbaje);
    stringstream s(limbaje);
    while(getline(s, limbaje, ' ')){
        this->limbajeCerute.push_back(limbaje);
    }

    cout << "Candidatura simpla?\n 1 -> Da\n 2 -> Nu\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 2){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        this->easyApply = true;
    }
    else{
        this->easyApply = false;
    }

    cout << "Numar de locuri disponibile: ";
    in >> this->nrLocuriDispon;

    return in;
}

ostream& Job::afisare(ostream& out) const {
    out << "Nume Job: " << this->numeJob << "\n";
    out << "Salariu de baza (euro/luna): " << this->salariuDeBaza << "\n";
    out << "Locatie Job:\n";
    out << "  Tara: " << this->locatieJob.numeTara << "\n";
    out << "  Oras: " << this->locatieJob.numeOras << "\n";
    out << "  Strada: " << this->locatieJob.numeStrada << "\n";
    out << "  Numarul: " << this->locatieJob.nrStrada << "\n";
    out << "Numar minim de ani de experienta: " << this->nrAniExperientaMin << "\n";
    out << "Limbaje de programare necesare: ";
    for(auto it : this->limbajeCerute){
        out << it << " ";
    }
    out << "\n";
    out << "Candidatura simpla: ";
    if(this->easyApply){
        out << "Da\n";
    }
    else{
        out << "Nu\n";
    }
    out << "Numar de locuri disponibile: " << this->nrLocuriDispon << "\n";

    return out;
}

void Job::showJobApplicants(){
    if(this->jobApplicants.size()){
        for(int i = 0; i < this->jobApplicants.size(); ++i){
            cout << i + 1 << ". " << (*this->jobApplicants[i]) << "\n";
        }
    }
    else{
        cout << "Inca nu a aplicat nimeni pentru acest job!\n";
        Sleep(2000);
    }
}

Job::~Job(){
    this->numeJob = "";
    this->salariuDeBaza = 0;
    this->locatieJob.nrStrada = 0;
    this->locatieJob.numeOras = "";
    this->locatieJob.numeStrada = "";
    this->locatieJob.numeTara = "";
    this->nrAniExperientaMin = 0;
    this->limbajeCerute.clear();
    this->easyApply = false;
    this->jobApplicants.clear();
    this->nrLocuriDispon = 0;
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class WebDeveloper : public Job {
protected:
    vector<string> frameworks;

public:
    //------- CONSTRUCTORI -------//
    WebDeveloper();
    WebDeveloper(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks);
    WebDeveloper(const WebDeveloper& obj);

    //------- OPERATORI -------//
    WebDeveloper& operator = (const WebDeveloper& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    vector<string> getFrameworks() const {return this->frameworks;}

    void setFrameworks(const vector<string>& frameworks){this->frameworks = frameworks;}

    //------- DESTRUCTOR -------//
    virtual ~WebDeveloper(){}
};

WebDeveloper::WebDeveloper() : Job() {
    this->frameworks = {};
}

WebDeveloper::WebDeveloper(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks) : 
    Job(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon){
        this->frameworks = frameworks;
}

WebDeveloper::WebDeveloper(const WebDeveloper& obj) : Job(obj){
    this->frameworks = obj.frameworks;
}

WebDeveloper& WebDeveloper::operator = (const WebDeveloper& obj){
    if(this != &obj){
        Job::operator = (obj);
        this->frameworks = obj.frameworks;
    }
    return *this;
}

istream& WebDeveloper::citire(istream& in){
    Job::citire(in);
    cout << "Framework-uri necesare: ";
    in.get();
    string framework;
    getline(in, framework);
    stringstream s(framework);
    while(getline(s, framework, ' ')){
        this->frameworks.push_back(framework);
    }

    return in;
}

ostream& WebDeveloper::afisare(ostream& out) const {
    Job::afisare(out);
    out << "Framework-uri necesare: ";
    for(auto it : this->frameworks){
        out << it << " ";
    }
    out << "\n";

    return out;
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class FrontEndDev : virtual public WebDeveloper {
protected:
    bool responsiveDesign;

public:
    //------- CONSTRUCTORI -------//
    FrontEndDev();
    FrontEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign);
    FrontEndDev(const FrontEndDev& obj);

    //------- OPERATORI -------//
    FrontEndDev& operator = (const FrontEndDev& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    bool getResponsiveDesign() const {return this->responsiveDesign;}

    void setResponsiveDesign(bool responsiveDesign){this->responsiveDesign = responsiveDesign;}

    //------- METODE -------//
    void modificaAnunt();

    //------- DESTRUCTOR -------//
    virtual ~FrontEndDev(){}
};

FrontEndDev::FrontEndDev() : WebDeveloper() {
    this->responsiveDesign = false;
}

FrontEndDev::FrontEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign) : 
    WebDeveloper(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon, frameworks){
        this->responsiveDesign = false;
}

FrontEndDev::FrontEndDev(const FrontEndDev& obj) : WebDeveloper(obj){
    this->responsiveDesign = obj.responsiveDesign;
}

FrontEndDev& FrontEndDev::operator = (const FrontEndDev& obj){
    if(this != &obj){
        WebDeveloper::operator = (obj);
        this->responsiveDesign = obj.responsiveDesign;
    }
    return *this;
}

istream& FrontEndDev::citire(istream& in){
    WebDeveloper::citire(in);
    cout << "Este necesara cunoasterea unui design responsive?\n 1 -> Da\n 2 -> Nu\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 2){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    in >> response;
    if(response == 1){
        this->responsiveDesign = true;
    }
    else{
        this->responsiveDesign = false;
    }

    return in;
}

ostream& FrontEndDev::afisare(ostream& out) const {
    WebDeveloper::afisare(out);
    out << "Este necesara cunoasterea design-ului responsive? ";
    if(this->responsiveDesign){
        out << "Da\n";
    }
    else{
        out << "Nu\n";
    }

    return out;
}

void FrontEndDev::modificaAnunt(){
    bool updating = true;
    while(updating){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza (euro/luna)\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Cunoasterea design-ului responsive\n";
        cout << "9 -> BACK\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 9){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza (euro/luna): ";
                int salariu;
                cin >> salariu;
                this->salariuDeBaza = salariu;
                break;
            }
            case 3:{
                cout << "Introduceti noua locatie a job-ului:\n";
                locatie newLocation;
                cout << " Nume Tara: ";
                cin >> newLocation.numeTara;
                this->locatieJob.numeTara = newLocation.numeTara;

                cout << " Nume Oras: ";
                cin >> newLocation.numeOras;
                this->locatieJob.numeOras = newLocation.numeOras;

                cout << " Nume Strada: ";
                cin >> newLocation.numeStrada;
                this->locatieJob.numeStrada = newLocation.numeStrada;
                
                cout << " Numar Strada: ";
                cin >> newLocation.nrStrada;
                this->locatieJob.nrStrada = newLocation.nrStrada;
                break;
            }
            case 4:{
                cout << "Introduceti numarul de ani de experienta minimi: ";
                int update;
                cin >> update;
                this->nrAniExperientaMin = update;
                break;
            }
            case 5:{
                this->limbajeCerute.clear();
                cout << "Introduceti limbajele de programare necesare: ";
                string limbaje;
                cin.get();
                getline(cin, limbaje);
                stringstream s(limbaje);
                while(getline(s, limbaje, ' ')){
                    this->limbajeCerute.push_back(limbaje);
                }
                break;
            }
            case 6:{
                cout << "Introduceti numarul de locuri disponibile: ";
                int update;
                cin >> update;
                this->nrLocuriDispon = update;
                break;
            }
            case 7:{
                this->frameworks.clear();
                cout << "Introduceti framework-urile necesare: ";
                string framework;
                cin.get();
                getline(cin, framework);
                stringstream s(framework);
                while(getline(s, framework, ' ')){
                    this->frameworks.push_back(framework);
                }
                break;
            }
            case 8:{
                cout << "Este necesara cunoasterea design-ului responsive? ";
                if(this->responsiveDesign){
                    cout << "Da\n";
                }
                else{
                    cout << "Nu\n";
                }
                cout << "Doriti sa modificati?\n 1 -> Da\n 2 -> Nu\n";
                int response;
                while(true){
                    cout << "Raspuns: ";
                    try{
                        cin >> response;
                        if(response < 1 || response > 2){
                            throw IndexException();
                        }
                        else{
                            break;
                        }
                    }
                    catch(const IndexException& error){
                        cout << error.what() << "\n";
                    }
                }
                if(response == 1){
                    if(this->responsiveDesign){
                        this->responsiveDesign = false;
                    }
                    else{
                        this->responsiveDesign = true;
                    }
                }
                break;
            }
            case 9:{
                updating = false;
                break;
            }
            default:{
                cout << "Index invalid!\n";
            }
        }
        if(response != 9){
            system("CLS");
            cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 2){
                updating = false;
            }
        }
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class BackEndDev : virtual public WebDeveloper {
protected:
    vector<string> databases;

public:
    //------- CONSTRUCTORI -------//
    BackEndDev();
    BackEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, const vector<string>& databases);
    BackEndDev(const BackEndDev& obj);

    //------- OPERATORI -------//
    BackEndDev& operator = (const BackEndDev& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    vector<string> getDatabases() const {return this->databases;}

    void setDatabases(const vector<string>& databases){this->databases = databases;}

    //------- METODE -------//
    void modificaAnunt();

    //------- DESTRUCTOR -------//
    virtual ~BackEndDev(){}
};

BackEndDev::BackEndDev() : WebDeveloper() {
    this->databases = {};
}

BackEndDev::BackEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, const vector<string>& databases) : 
    WebDeveloper(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon, frameworks){
        this->databases = {};
}

BackEndDev::BackEndDev(const BackEndDev& obj) : WebDeveloper(obj){
    this->databases = obj.databases;
}

BackEndDev& BackEndDev::operator = (const BackEndDev& obj){
    if(this != &obj){
        WebDeveloper::operator = (obj);
        this->databases = obj.databases;
    }
    return *this;
}

istream& BackEndDev::citire(istream& in){
    WebDeveloper::citire(in);
    cout << "Se va lucra in urmatoarele baze de date: ";
    string baza;
    getline(in, baza);
    stringstream s(baza);
    while(getline(s, baza, ' ')){
        this->databases.push_back(baza);
    }

    return in;
}

ostream& BackEndDev::afisare(ostream& out) const {
    WebDeveloper::afisare(out);
    out << "Cunostinte in urmatoarele baze de date: ";
    for(auto it : this->databases){
        out << it << " ";
    }
    out << "\n";

    return out;
}

void BackEndDev::modificaAnunt(){
    bool updating = true;
    while(updating){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza (euro/luna)\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Bazele de date necesare\n";
        cout << "9 -> BACK\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 9){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza (euro/luna): ";
                int salariu;
                cin >> salariu;
                this->salariuDeBaza = salariu;
                break;
            }
            case 3:{
                cout << "Introduceti noua locatie a job-ului:\n";
                locatie newLocation;
                cout << " Nume Tara: ";
                cin >> newLocation.numeTara;
                this->locatieJob.numeTara = newLocation.numeTara;

                cout << " Nume Oras: ";
                cin >> newLocation.numeOras;
                this->locatieJob.numeOras = newLocation.numeOras;

                cout << " Nume Strada: ";
                cin >> newLocation.numeStrada;
                this->locatieJob.numeStrada = newLocation.numeStrada;
                
                cout << " Numar Strada: ";
                cin >> newLocation.nrStrada;
                this->locatieJob.nrStrada = newLocation.nrStrada;
                break;
            }
            case 4:{
                cout << "Introduceti numarul de ani de experienta minimi: ";
                int update;
                cin >> update;
                this->nrAniExperientaMin = update;
                break;
            }
            case 5:{
                this->limbajeCerute.clear();
                cout << "Introduceti limbajele de programare necesare: ";
                string limbaje;
                cin.get();
                getline(cin, limbaje);
                stringstream s(limbaje);
                while(getline(s, limbaje, ' ')){
                    this->limbajeCerute.push_back(limbaje);
                }
                break;
            }
            case 6:{
                cout << "Introduceti numarul de locuri disponibile: ";
                int update;
                cin >> update;
                this->nrLocuriDispon = update;
                break;
            }
            case 7:{
                this->frameworks.clear();
                cout << "Introduceti framework-urile necesare: ";
                string framework;
                cin.get();
                getline(cin, framework);
                stringstream s(framework);
                while(getline(s, framework, ' ')){
                    this->frameworks.push_back(framework);
                }
                break;
            }
            case 8:{
                this->databases.clear();
                cout << "Introduceti framework-urile necesare: ";
                string database;
                cin.get();
                getline(cin, database);
                stringstream s(database);
                while(getline(s, database, ' ')){
                    this->databases.push_back(database);
                }
                break;
            }
            case 9:{
                updating = false;
                break;
            }
        }
        if(response != 9){
            system("CLS");
            cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 2){
                updating = false;
            }
        }
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class FullStackDev : public FrontEndDev, public BackEndDev {
private:
    vector<string> serverPlatforms;

public:
    //------- CONSTRUCTORI -------//
    FullStackDev();
    FullStackDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign, const vector<string>& databases, const vector<string>& serverPlatforms);
    FullStackDev(const FullStackDev& obj);

    //------- OPERATORI -------//
    FullStackDev& operator = (const FullStackDev& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    vector<string> getDatabases() const {return this->serverPlatforms;}

    void setPlatforms(const vector<string>& platforms){this->serverPlatforms = platforms;}

    //------- METODE -------//
    void modificaAnunt();

    //------- DESTRUCTOR -------//
    virtual ~FullStackDev(){}
};

FullStackDev::FullStackDev(){
    this->serverPlatforms = {};
}

FullStackDev::FullStackDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign, const vector<string>& databases, const vector<string>& serverPlatforms) : 
    WebDeveloper(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon, frameworks),
    FrontEndDev(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon, frameworks, responsiveDesign),
    BackEndDev(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon, frameworks, databases){
        this->serverPlatforms = {};
    }

FullStackDev::FullStackDev(const FullStackDev& obj) : WebDeveloper(obj), FrontEndDev(obj), BackEndDev(obj){
    this->serverPlatforms = obj.serverPlatforms;
}

FullStackDev& FullStackDev::operator = (const FullStackDev& obj){
    if(this != &obj){
        FrontEndDev::operator = (obj);
        BackEndDev::operator = (obj);
        this->serverPlatforms = obj.serverPlatforms;
    }
    return *this;
}

istream& FullStackDev::citire(istream& in){
    WebDeveloper::citire(in);
    cout << "Este necesara cunoasterea unui design responsive?\n 1 -> Da\n 2 -> Nu\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 2){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        this->responsiveDesign = true;
    }
    else{
        this->responsiveDesign = false;
    }

    cout << "Experienta in urmatoarele baze de date: ";
    in.get();
    string baza;
    getline(in, baza);
    stringstream s(baza);
    while(getline(s, baza, ' ')){
        this->databases.push_back(baza);
    }

    cout << "Experienta in urmatoarele platforme: ";
    string platform;
    getline(in, platform);
    stringstream f(platform);
    while(getline(f, platform, ' ')){
        this->serverPlatforms.push_back(platform);
    }

    return in;
}

ostream& FullStackDev::afisare(ostream& out) const {
    WebDeveloper::afisare(out);

    out << "Este necesara cunoasterea design-ului responsive? ";
    if(this->responsiveDesign){
        out << "Da\n";
    }
    else{
        out << "Nu\n";
    }

    out << "Cunostinte in urmatoarele baze de date: ";
    for(auto it : this->databases){
        out << it << " ";
    }
    out << "\n";

    out << "Cunostinte in urmatoarele platforme: ";
    for(auto it : this->serverPlatforms){
        out << it << " ";
    }
    out << "\n";

    return out;
}

void FullStackDev::modificaAnunt(){
    bool updating = true;
    while(updating){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza (euro/luna)\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Bazele de date necesare\n";
        cout << "9 -> Platformele necesare\n";
        cout << "10 -> BACK\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 10){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza (euro/luna): ";
                int salariu;
                cin >> salariu;
                this->salariuDeBaza = salariu;
                break;
            }
            case 3:{
                cout << "Introduceti noua locatie a job-ului:\n";
                locatie newLocation;
                cout << " Nume Tara: ";
                cin >> newLocation.numeTara;
                this->locatieJob.numeTara = newLocation.numeTara;

                cout << " Nume Oras: ";
                cin >> newLocation.numeOras;
                this->locatieJob.numeOras = newLocation.numeOras;

                cout << " Nume Strada: ";
                cin >> newLocation.numeStrada;
                this->locatieJob.numeStrada = newLocation.numeStrada;
                
                cout << " Numar Strada: ";
                cin >> newLocation.nrStrada;
                this->locatieJob.nrStrada = newLocation.nrStrada;
                break;
            }
            case 4:{
                cout << "Introduceti numarul de ani de experienta minimi: ";
                int update;
                cin >> update;
                this->nrAniExperientaMin = update;
                break;
            }
            case 5:{
                this->limbajeCerute.clear();
                cout << "Introduceti limbajele de programare necesare: ";
                string limbaje;
                cin.get();
                getline(cin, limbaje);
                stringstream s(limbaje);
                while(getline(s, limbaje, ' ')){
                    this->limbajeCerute.push_back(limbaje);
                }
                break;
            }
            case 6:{
                cout << "Introduceti numarul de locuri disponibile: ";
                int update;
                cin >> update;
                this->nrLocuriDispon = update;
                break;
            }
            case 7:{
                this->frameworks.clear();
                cout << "Introduceti framework-urile necesare: ";
                string framework;
                cin.get();
                getline(cin, framework);
                stringstream s(framework);
                while(getline(s, framework, ' ')){
                    this->frameworks.push_back(framework);
                }
                break;
            }
            case 8:{
                this->databases.clear();
                cout << "Introduceti framework-urile necesare: ";
                string database;
                cin.get();
                getline(cin, database);
                stringstream s(database);
                while(getline(s, database, ' ')){
                    this->databases.push_back(database);
                }
                break;
            }
            case 9:{
                this->serverPlatforms.clear();
                cout << "Introduceti platformele necesare: ";
                string platform;
                cin.get();
                getline(cin, platform);
                stringstream s(platform);
                while(getline(s, platform, ' ')){
                    this->serverPlatforms.push_back(platform);
                }
                break;
            }
            case 10:{
                updating = false;
                break;
            }
        }
        if(response != 10){
            system("CLS");
            cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 2){
                updating = false;
            }
        }
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class SoftwareDev : public Job{
private:
    vector<string> sistemeOperare;

public:
    //------- CONSTRUCTORI -------//
    SoftwareDev();
    SoftwareDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& sistemeOperare);
    SoftwareDev(const SoftwareDev& obj);

    //------- OPERATORI -------//
    SoftwareDev& operator = (const SoftwareDev& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    vector<string> getsistemeOperare() const {return this->sistemeOperare;}

    void setsistemeOperare(const vector<string>& sistemeOperare){this->sistemeOperare = sistemeOperare;}

    //------- METODE -------//
    void modificaAnunt();

    //------- DESTRUCTOR -------//
    virtual ~SoftwareDev(){}
};

SoftwareDev::SoftwareDev() : Job() {
    this->sistemeOperare = {};
}

SoftwareDev::SoftwareDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& sistemeOperare) : 
    Job(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon){
        this->sistemeOperare = {};
    }

SoftwareDev::SoftwareDev(const SoftwareDev& obj) : Job(obj){
    this->sistemeOperare = obj.sistemeOperare;
}

SoftwareDev& SoftwareDev::operator = (const SoftwareDev& obj){
    if(this != &obj){
        Job::operator = (obj);
        this->sistemeOperare = obj.sistemeOperare;
    }
    return *this;
}

istream& SoftwareDev::citire(istream& in){
    Job::citire(in);
    cout << "Experienta in urmatoarele sisteme de operare: ";
    in.get();
    string update;
    getline(in, update);
    stringstream f(update);
    while(getline(f, update, ' ')){
        this->sistemeOperare.push_back(update);
    }

    return in;
}

ostream& SoftwareDev::afisare(ostream& out) const {
    Job::afisare(out);
    out << "Cunostinte in urmatoarele sisteme de operare: ";
    for(auto it : this->sistemeOperare){
        out << it << " ";
    }
    out << "\n";

    return out;
}

void SoftwareDev::modificaAnunt(){
    bool updating = true;
    while(updating){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza (euro/luna)\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Sisteme de operare necesare\n";
        cout << "8 -> BACK\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 8){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza (euro/luna): ";
                int salariu;
                cin >> salariu;
                this->salariuDeBaza = salariu;
                break;
            }
            case 3:{
                cout << "Introduceti noua locatie a job-ului:\n";
                locatie newLocation;
                cout << " Nume Tara: ";
                cin >> newLocation.numeTara;
                this->locatieJob.numeTara = newLocation.numeTara;

                cout << " Nume Oras: ";
                cin >> newLocation.numeOras;
                this->locatieJob.numeOras = newLocation.numeOras;

                cout << " Nume Strada: ";
                cin >> newLocation.numeStrada;
                this->locatieJob.numeStrada = newLocation.numeStrada;
                
                cout << " Numar Strada: ";
                cin >> newLocation.nrStrada;
                this->locatieJob.nrStrada = newLocation.nrStrada;
                break;
            }
            case 4:{
                cout << "Introduceti numarul de ani de experienta minimi: ";
                int update;
                cin >> update;
                this->nrAniExperientaMin = update;
                break;
            }
            case 5:{
                this->limbajeCerute.clear();
                cout << "Introduceti limbajele de programare necesare: ";
                string limbaje;
                cin.get();
                getline(cin, limbaje);
                stringstream s(limbaje);
                while(getline(s, limbaje, ' ')){
                    this->limbajeCerute.push_back(limbaje);
                }
                break;
            }
            case 6:{
                cout << "Introduceti numarul de locuri disponibile: ";
                int update;
                cin >> update;
                this->nrLocuriDispon = update;
                break;
            }
            case 7:{
                this->sistemeOperare.clear();
                cout << "Introduceti sistemele de operare necesare: ";
                string update;
                cin.get();
                getline(cin, update);
                stringstream s(update);
                while(getline(s, update, ' ')){
                    this->sistemeOperare.push_back(update);
                }
                break;
            }
        }
        if(response != 8){
            system("CLS");
            cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 2){
                updating = false;
            }
        }
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class MobileAppDev : public Job {
protected:
    vector<string> frameworks;

public:
    //------- CONSTRUCTORI -------//
    MobileAppDev();
    MobileAppDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks);
    MobileAppDev(const MobileAppDev& obj);

    //------- OPERATORI -------//
    MobileAppDev& operator = (const MobileAppDev& obj);

    //------- CITIRE SI AFISARE -------//
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    //------- GETTERS & SETTERS -------//
    vector<string> getFrameworks() const {return this->frameworks;}

    void setFrameworks(const vector<string>& frameworks){this->frameworks = frameworks;}

    //------- METODE -------//
    void modificaAnunt();

    //------- DESTRUCTOR -------//
    virtual ~MobileAppDev(){}
};

MobileAppDev::MobileAppDev() : Job() {
    this->frameworks = {};
}

MobileAppDev::MobileAppDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client*>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks) : 
    Job(numeJob, salariuDeBaza, locatieJob, nrAniExperientaMin, limbajeCerute, easyApply, jobApplicants, nrLocuriDispon){
        this->frameworks = frameworks;
}

MobileAppDev::MobileAppDev(const MobileAppDev& obj) : Job(obj){
    this->frameworks = obj.frameworks;
}

MobileAppDev& MobileAppDev::operator = (const MobileAppDev& obj){
    if(this != &obj){
        Job::operator = (obj);
        this->frameworks = obj.frameworks;
    }
    return *this;
}

istream& MobileAppDev::citire(istream& in){
    Job::citire(in);
    cout << "Framework-uri necesare: ";
    in.get();
    string framework;
    getline(in, framework);
    stringstream s(framework);
    while(getline(s, framework, ' ')){
        this->frameworks.push_back(framework);
    }

    return in;
}

ostream& MobileAppDev::afisare(ostream& out) const {
    Job::afisare(out);
    out << "Framework-uri necesare: ";
    for(auto it : this->frameworks){
        out << it << " ";
    }
    out << "\n";

    return out;
}

void MobileAppDev::modificaAnunt(){
    bool updating = true;
    while(updating){
        system("CLS");
        cout << "Ce doresti sa modifici?\n";
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza (euro/luna)\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> BACK\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 8){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza (euro/luna): ";
                int salariu;
                cin >> salariu;
                this->salariuDeBaza = salariu;
                break;
            }
            case 3:{
                cout << "Introduceti noua locatie a job-ului:\n";
                locatie newLocation;
                cout << " Nume Tara: ";
                cin >> newLocation.numeTara;
                this->locatieJob.numeTara = newLocation.numeTara;

                cout << " Nume Oras: ";
                cin >> newLocation.numeOras;
                this->locatieJob.numeOras = newLocation.numeOras;

                cout << " Nume Strada: ";
                cin >> newLocation.numeStrada;
                this->locatieJob.numeStrada = newLocation.numeStrada;
                
                cout << " Numar Strada: ";
                cin >> newLocation.nrStrada;
                this->locatieJob.nrStrada = newLocation.nrStrada;
                break;
            }
            case 4:{
                cout << "Introduceti numarul de ani de experienta minimi: ";
                int update;
                cin >> update;
                this->nrAniExperientaMin = update;
                break;
            }
            case 5:{
                this->limbajeCerute.clear();
                cout << "Introduceti limbajele de programare necesare: ";
                string limbaje;
                cin.get();
                getline(cin, limbaje);
                stringstream s(limbaje);
                while(getline(s, limbaje, ' ')){
                    this->limbajeCerute.push_back(limbaje);
                }
                break;
            }
            case 6:{
                cout << "Introduceti numarul de locuri disponibile: ";
                int update;
                cin >> update;
                this->nrLocuriDispon = update;
                break;
            }
            case 7:{
                this->frameworks.clear();
                cout << "Introduceti framework-urile necesare: ";
                string framework;
                cin.get();
                getline(cin, framework);
                stringstream s(framework);
                while(getline(s, framework, ' ')){
                    this->frameworks.push_back(framework);
                }
                break;
            }
            case 8:{
                updating = false;
                break;
            }
            default:{
                cout << "Index invalid!\n";
            }
        }
        if(response != 8){
            system("CLS");
            cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 2){
                updating = false;
            }
        }
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Angajator : public Client{
private:
    string numeCompanie;
    vector<Job*> anunturi;

public:
    //------- CONSTRUCTORI -------//
    Angajator();
    Angajator(const Angajator& obj);

    //------- OPERATORI -------//
    Angajator& operator = (const Angajator& obj);

    //------- GETTERS & SETTERS -------//
    string getNumeCompanie() const {return this->numeCompanie;}
    vector<Job*> getAnunturi() const {return this->anunturi;}

    void setNumeCompanie(string numeCompanie){this->numeCompanie = numeCompanie;}
    void setAnunturi(const vector<Job*>& anunturi){this->anunturi = anunturi;}

    //------- METODE -------//
    Job* posteazaAnunt();
    template<class T>
    void adaugaAnunt(T* anunt){
        this->anunturi.push_back(anunt);
    }
    istream& creeazaCont(istream& in);
    ostream& afisProfilUser(ostream& out) const;
    void afisAnunturi();

    //------- DESTRUCTOR -------//
    virtual ~Angajator(){}
};

Angajator::Angajator() : Client() {this->numeCompanie = "";}
Angajator::Angajator(const Angajator& obj) : Client(obj) {this->numeCompanie = obj.numeCompanie;}
Angajator& Angajator::operator = (const Angajator& obj) {
    if(this != &obj){
        Client::operator = (obj);
        this->numeCompanie = obj.numeCompanie;
    }
    return *this;
}

Job* Angajator::posteazaAnunt(){
    Job* anunt;
    cout << "Ce post vizeaza acest anunt?\n 1 -> Web Developer\n 2 -> Software Developer\n 3 -> Mobile Application Developer\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 3){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    switch(response){
        case 1:{
            system("CLS");
            cout << "Alegeti una dintre urmatoarele variante:\n 1 -> Front-End Developer\n 2 -> Back-End Developer\n 3 -> Full-Stack Developer\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 3){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 1){
                anunt = new FrontEndDev();
            }
            else if(response == 2){
                anunt = new BackEndDev();
            }
            else{
                anunt = new FullStackDev();
            }
            cin >> (*anunt);
            adaugaAnunt(anunt);
            break;
        }
        case 2:{
            anunt = new SoftwareDev();
            cin >> (*anunt);
            adaugaAnunt(anunt);
            break;
        }
        case 3:{
            anunt = new MobileAppDev();
            cin >> (*anunt);
            adaugaAnunt(anunt);
            break;
        }
    }
    system("CLS");
    cout << (*anunt) << "\n";
    cout << "\nConfirmati corectitudinea datelor?\n 1 -> Da\n 2 -> Nu\n";
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 2){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        cout << "Anunt postat cu succes!\n";
    }
    else{
        (*anunt).modificaAnunt();
        cout << "Anunt postat cu succes!\n";
    }
    return anunt;
}

istream& Angajator::creeazaCont(istream& in){
    Client::creeazaCont(in);
    cout << "Numele companiei: ";
    in >> this->numeCompanie;

    return in;
}

ostream& Angajator::afisProfilUser(ostream& out) const {
    Client::afisProfilUser(out);
    out << "Lucreaza la: " << this->numeCompanie << "\n";

    return out;
}

void Angajator::afisAnunturi(){
    for(int i = 0; i < this->anunturi.size(); ++i){
        cout << i + 1 << ". " << *this->anunturi[i] << "\n";
    }
}
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// template<class T>
// class Post {
// private:
//     string title;
//     T content;
//     list<pair<string, string>> comments;

// public:
//     void createPost();
//     void addComments(string);
//     void showComments();
// };

// template<class T> void Post<T>::createPost(){
//     cout << "Titlu: ";
//     getline(cin, this->title);

//     cout << "Subiect:\n";
//     cin >> this->content;
// }

// template<class T> void Post<T>::addComments(string username){
//     string comment;
//     cout << "Comentariu: ";
//     getline(cin, comment);
//     this->comments.push_back({username, comment});
// }

// template<class T> void Post<T>::showComments(){
//     for(auto comment : this->comments){
//         cout << comment.first << ": " << comment.second << "\n"
//     }
// }
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Meniu{
private:
    static Meniu* obiect;
    list<Client*> users;
    map<Client*, pair<string, string>> accDet;
    vector<Job*> anunturiGlobal;
    Client* currentUser;
    Meniu() = default;
    Meniu(const Meniu&) = delete;
    static int numberOfInstance;

public:
    static Meniu* getInstance(){
        numberOfInstance++;
        if(obiect == NULL){
            obiect = new Meniu();
        }
        return obiect;
    }
    void setTextColor(int colorCode);
    void clearScreen(){system("cls");}
    void welcome();
    void viewOptions(Client* user);
    void showJobs();
    ~Meniu(){
        numberOfInstance--;
        if(numberOfInstance == 0){
            if(obiect != NULL){
                delete obiect;
            }
        }
    }
};

Meniu* Meniu::obiect = 0;   
int Meniu::numberOfInstance = 0;

void Meniu::setTextColor(int colorCode){
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, colorCode);
}

void Meniu::welcome(){
    setTextColor(9);
    cout << "Bine ai venit!\n";
    cout << "Alege o actiune:\n 1 -> Creeaza cont\n 2 -> Autentifica-te\n 3 -> Close\n";
    int response;
    while(true){
        cout << "Raspuns: ";
        try{
            cin >> response;
            if(response < 1 || response > 3){
                throw IndexException();
            }
            else{
                break;
            }
        }
        catch(const IndexException& error){
            cout << error.what() << "\n";
        }
    }
    if(response == 1){
        clearScreen();
        cout << "Doresc sa:\n 1 -> Angajez\n 2 -> Fiu angajat\n";
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 2){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(response == 1){
            currentUser = new Angajator();
            (*currentUser).creeazaCont(cin);
            this->users.push_back(currentUser);
            this->accDet[this->currentUser] = {this->currentUser->getEmail(), this->currentUser->getParola()};
            g << this->currentUser->getNume() << " " << this->currentUser->getPrenume() << "\nEmail: " << this->currentUser->getEmail() << "\nParola: " << this->currentUser->getParola() << "\n\n";
            viewOptions(currentUser);
        }
        else{
            currentUser = new Client();
            (*currentUser).creeazaCont(cin);
            this->users.push_back(currentUser);
            this->accDet[this->currentUser] = {this->currentUser->getEmail(), this->currentUser->getParola()};
            g << this->currentUser->getNume() << " " << this->currentUser->getPrenume() << "\nEmail: " << this->currentUser->getEmail() << "\nParola: " << this->currentUser->getParola() << "\n\n";
            viewOptions(currentUser);
        }
    }
    else if(response == 2){
        string email, parola;
        clearScreen();
        cout << "Doresti sa completezi detaliile contului automat?\n 1 -> Da\n 2 -> Nu\n";
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 2){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(response == 1){
            f >> email;
            f >> parola;
        }
        else{
            cout << "Email: ";
            cin >> email;
            cout << "Parola: ";
            cin >> parola;
        }
        bool found = false;
        for(auto it : this->users){
            if((*it).getEmail() == email && (*it).getParola() == parola){
                viewOptions(it);
                found = true;
                break;
            }
        }
        if(!found){
            setTextColor(4);
            cout << "Date incorecte!\nDoresti sa creezi un cont nou?\n 1 -> Da\n 2 -> Nu\n";
            while(true){
                cout << "Raspuns: ";
                try{
                    cin >> response;
                    if(response < 1 || response > 2){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response == 1){
                clearScreen();
                setTextColor(9);
                cout << "Doresc sa:\n 1 -> Angajez\n 2 -> Fiu angajat\n";
                while(true){
                    cout << "Raspuns: ";
                    try{
                        cin >> response;
                        if(response < 1 || response > 2){
                            throw IndexException();
                        }
                        else{
                            break;
                        }
                    }
                    catch(const IndexException& error){
                        cout << error.what() << "\n";
                    }
                }
                if(response == 1){
                    currentUser = new Angajator();
                    (*currentUser).creeazaCont(cin);
                    this->users.push_back(currentUser);
                }
                else{
                    currentUser = new Client();
                    (*currentUser).creeazaCont(cin);
                    this->users.push_back(currentUser);
                }
            }
            else{
                setTextColor(9);
                int nrIncercari = 0;
                while(true){
                    nrIncercari++;
                    clearScreen();
                    cout << "Incearca inca o data:\n";
                    cout << "Email: ";
                    cin >> email;
                    cout << "Parola: ";
                    cin >> parola;
                    found = false;
                    for(auto it : this->users){
                        if((*it).getEmail() == email && (*it).getParola() == parola){
                            viewOptions(it);
                            found = true;
                            break;
                        }
                    }
                    if(found){
                        break;
                    }
                    if(nrIncercari == 3){
                        break;
                    }
                }
                if(nrIncercari == 3){
                    clearScreen();
                    setTextColor(4);
                    cout << "Ai atins numarul maxim de incercari! Incearca din nou mai tarziu.";
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else{
        exit(EXIT_SUCCESS);
    }
}

void Meniu::showJobs(){
    if(this->anunturiGlobal.size()){
        for(int i = 0; i < this->anunturiGlobal.size(); ++i){
            cout << i + 1 << ". " << (*this->anunturiGlobal[i]) << "\n";
        }
        cout << "Ati gasit un job interesant?\n 1 -> Da\n 2 -> Nu\n";
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 2){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(response == 1){
            cout << "Introduceti indicele corespunzator ofertei de job dorite: ";
            while(true){
                try{
                    cin >> response;
                    if(response < 1 || response > this->anunturiGlobal.size()){
                        throw IndexException();
                    }
                    else{
                        break;
                    }
                }
                catch(const IndexException& error){
                    cout << error.what() << "\n";
                }
            }
            if(response <= this->anunturiGlobal.size()){
                clearScreen();
                setTextColor(10);
                cout << "Ai aplicat cu succes!\n";
                Sleep(2000);
                (*this->anunturiGlobal[response - 1]).addJobApplicant(currentUser);
            }
        }
    }
    else{
        clearScreen();
        setTextColor(4);
        cout << "Ne pare rau, nu exista oferte disponibile momentan!\n";
        Sleep(2000);
    }
}

void Meniu::viewOptions(Client* user){
    while(true){
        setTextColor(10);
        clearScreen();
        bool angajator = false;
        cout << "Bine ai venit, " << (*user).getPrenume() << "\nAlege una dintre urmatoarele actiuni:\n";
        if(typeid(*user) == typeid(Angajator)){
            angajator = true;
            setTextColor(4);
            cout << " 1 -> Vizualizeaza profilul\n 2 -> Editeaza profilul\n 3 -> Cauta Job\n 4 -> Posteaza anunt\n 5 -> Modifica anunt\n 6 -> Vezi anunturile tale\n 7 -> Sterge anunt\n 8 -> Log Out\n";
        }
        else{
            setTextColor(4);
            cout << " 1 -> Vizualizeaza profilul\n 2 -> Editeaza profilul\n 3 -> Cauta Job\n 4 -> Log Out\n";
        }
        setTextColor(10);
        int response;
        while(true){
            cout << "Raspuns: ";
            try{
                cin >> response;
                if(response < 1 || response > 9 && typeid(*user) == typeid(Angajator)){
                    throw IndexException();
                }
                else if(response < 1 || response > 5 && typeid(*user) == typeid(Client)){
                    throw IndexException();
                }
                else{
                    break;
                }
            }
            catch(const IndexException& error){
                cout << error.what() << "\n";
            }
        }
        if(!angajator){
            switch(response){
                case 1:{
                    clearScreen();
                    setTextColor(9);
                    cout << (*user) << "\n";
                    cout << "Doresti sa faci o modificare?\n 1 -> Da\n 2 -> Nu\n";
                    while(true){
                        cout << "Raspuns: ";
                        try{
                            cin >> response;
                            if(response < 1 || response > 2){
                                throw IndexException();
                            }
                            else{
                                break;
                            }
                        }
                        catch(const IndexException& error){
                            cout << error.what() << "\n";
                        }
                    }
                    if(response == 1){
                        (*user).modificaProfil();
                    }
                    break;
                }
                case 2:{
                    clearScreen();
                    setTextColor(9);
                    (*user).modificaProfil();
                    break;
                }
                case 3:{
                    clearScreen();
                    setTextColor(9);
                    showJobs();
                    break;
                }
                case 4:{
                    setTextColor(9);
                    clearScreen();
                    welcome();
                    break;
                }
            }
        }
        else{
            switch(response){
                case 1:{
                    clearScreen();
                    setTextColor(9);
                    cout << (*user) << "\n";
                    cout << "Doresti sa faci o modificare?\n 1 -> Da\n 2 -> Nu\n";
                    while(true){
                        cout << "Raspuns: ";
                        try{
                            cin >> response;
                            if(response < 1 || response > 2){
                                throw IndexException();
                            }
                            else{
                                break;
                            }
                        }
                        catch(const IndexException& error){
                            cout << error.what() << "\n";
                        }
                    }
                    if(response == 1){
                        (*user).modificaProfil();
                    }
                    break;
                }
                case 2:{
                    clearScreen();
                    setTextColor(9);
                    (*user).modificaProfil();
                    break;
                }
                case 3:{
                    clearScreen();
                    setTextColor(9);
                    showJobs();
                    break;
                }
                case 4:{
                    clearScreen();
                    this->anunturiGlobal.push_back(dynamic_cast<Angajator*>(user)->posteazaAnunt());
                    break;
                }
                case 5:{
                    clearScreen();
                    setTextColor(9);
                    Angajator* aux = dynamic_cast<Angajator*>(user);
                    for(int i = 0; i < aux->getAnunturi().size(); ++i){
                        cout << i + 1 << " " << (*(*aux).getAnunturi()[i]) << "\n";
                    }
                    cout << "Introduceti indicele anuntului corespunzator: ";
                    while(true){
                        try{
                            cin >> response;
                            if(response < 1 || response > (*aux).getAnunturi().size()){
                                throw IndexException();
                            }
                            else{
                                break;
                            }
                        }
                        catch(const IndexException& error){
                            clearScreen();
                            setTextColor(4);
                            cout << "Anunt inexistent!" << "\n";
                            Sleep(2000);
                        }
                    }
                    if(response <= (*aux).getAnunturi().size()){
                        (*(*aux).getAnunturi()[response - 1]).modificaAnunt();
                    }
                    dynamic_cast<Angajator*>(user)->setAnunturi(aux->getAnunturi());
                    break;
                }
                case 6:{
                    clearScreen();
                    setTextColor(9);
                    if(dynamic_cast<Angajator*>(user)->getAnunturi().size()){
                        for(int i = 0; i < dynamic_cast<Angajator*>(user)->getAnunturi().size(); ++i){
                            cout << i + 1 << ". " << (*dynamic_cast<Angajator*>(user)->getAnunturi()[i]) << "\n";
                        }
                        cout << "1 -> Vezi cine a aplicat\n2 -> Back\n";
                        while(true){
                            cout << "Raspuns: ";
                            try{
                                cin >> response;
                                if(response < 1 || response > 2){
                                    throw IndexException();
                                }
                                else{
                                    break;
                                }
                            }
                            catch(const IndexException& error){
                                cout << error.what() << "\n";
                            }
                        }
                        if(response == 1){
                            cout << "Introduceti indicele corespunzator anuntului: ";
                            cin >> response;
                            int aux = response;
                            if(response <= dynamic_cast<Angajator*>(user)->getAnunturi().size()){
                                clearScreen();
                                dynamic_cast<Angajator*>(user)->getAnunturi()[aux - 1]->showJobApplicants();
                                cout << " 1 -> Back\n";
                                while(true){
                                    cout << "Raspuns: ";
                                    try{
                                        cin >> response;
                                        if(response != 1){
                                            throw IndexException();
                                        }
                                        else{
                                            break;
                                        }
                                    }
                                    catch(const IndexException& error){
                                        cout << error.what() << "\n";
                                    }
                                }
                            }
                            else{
                                cout << "Acest anunt nu exista!\n";
                                Sleep(2000);
                            }
                        }
                    }
                    else{
                        cout << "Inca nu exista anunturi postate!\n";
                        Sleep(2000);
                    }
                    break;
                }
                case 7:{
                    clearScreen();
                    if(dynamic_cast<Angajator*>(user)->getAnunturi().size()){
                        dynamic_cast<Angajator*>(user)->afisAnunturi();
                        cout << "Introduceti indicele corespunzator anuntului: ";
                        cin >> response;
                        if(response >= 1 && response <= dynamic_cast<Angajator*>(user)->getAnunturi().size()){
                            vector<Job*> anunturi = dynamic_cast<Angajator*>(user)->getAnunturi();
                            anunturi.erase(anunturi.begin() + response - 1);
                            dynamic_cast<Angajator*>(user)->setAnunturi(anunturi);
                        }
                        else{
                            cout << "Acest anunt nu exista!\n";
                            Sleep(2000);
                        }
                    }
                    else{
                        cout << "Inca nu exista anunturi postate!\n";
                        Sleep(2000);
                    }
                }
                case 8:{
                    setTextColor(9);
                    clearScreen();
                    welcome();
                    break;
                }
            }
        }
    }
}
///////////////////////////////////////////////////////


int main(){
    system("cls");
    Meniu* M = M->getInstance();
    M->welcome();
    if(M != NULL){
        delete M;
    }
    return 0;
}