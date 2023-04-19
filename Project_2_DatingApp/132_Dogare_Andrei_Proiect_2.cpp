#include <bits/stdc++.h>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Job;

class Client{
private:
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
    Client(string nume, string prenume, int varsta, string ocupatie, int aniExperienta, bool licentiat, const vector<Job*>& jobOfferts);
    Client(const Client& obj);

    //------- OPERATORI -------//
    Client& operator = (const Client& obj);

    //------- CITIRE SI AFISARE -------//
    istream& autentificare(istream& in);
    ostream& afisProfilUser(ostream& out) const;

    //------- GETTERS -------//
    string getNume() const {return this->nume;}
    string getPrenume() const {return this->prenume;}
    int getVarsta() const {return this->varsta;}
    string getOcupatie() const {return this->ocupatie;}
    int getAniExperienta() const {return this->aniExperienta;}
    bool getLicence() const {return this->licentiat;}
    vector<Job*> getJobOfferts() const {return this->jobOfferts;}

    //------- METODE -------//

    //------- DESTRUCTOR -------//
    ~Client(){}
};

Client::Client(){
    this->nume = "";
    this->prenume = "";
    this->varsta = 0;
    this->ocupatie = "";
    this->aniExperienta = 0;
    this->licentiat = false;
    this->jobOfferts = {};
}

Client::Client(string nume, string prenume, int varsta, string ocupatie, int aniExperienta, bool licentiat, const vector<Job*>& jobOfferts){
    this->nume = nume;
    this->prenume = prenume;
    this->varsta = varsta;
    this->ocupatie = ocupatie;
    this->aniExperienta = aniExperienta;
    this->licentiat = licentiat;
    this->jobOfferts = jobOfferts;
}

Client::Client(const Client& obj){
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

istream& Client::autentificare(istream& in){
    cout << "Nume: ";
    in >> this->nume;

    cout << "Prenume: ";
    in >> this->prenume;

    cout << "Varsta: ";
    in >> this->varsta;

    cout << "Lucrez ca: ";
    in >> this->ocupatie;

    cout << "Ani de experienta: ";
    in >> this->aniExperienta;

    cout << "Ai terminat o facultate in domeniu?\n 1 -> Da\n 2 -> Nu\n";
    cout << "Raspuns: ";
    int response;
    in >> response;
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
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Job : public IOInterface{
protected:
    vector<Client> jobApplicants;
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
    Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon);
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
    vector<Client> getJobApplicants() const {return this->jobApplicants;}
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
    void addJobApplicant(const Client& user){this->jobApplicants.push_back(user);}

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

Job::Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon){
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
    in >> this->numeJob;

    cout << "Salariu: ";
    in >> this->salariuDeBaza;

    cout << "Locatia Job-ului:\n";
    cout << " Nume Tara: ";
    in >> this->locatieJob.numeTara;
    cout << " Nume Oras: ";
    in >> this->locatieJob.numeOras;
    cout << " Nume Strada: ";
    in >> this->locatieJob.numeStrada;
    cout << " Numarul Strazii: ";
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
    cout << "Raspuns: ";
    in >> response;
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
    out << "Salariu de baza: " << this->salariuDeBaza << "\n";
    out << "Locatie Job: " << this->locatieJob.numeTara << ", " << this->locatieJob.numeOras << ", Strada " << this->locatieJob.numeStrada << ", Numarul " << this->locatieJob.nrStrada << "\n";
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
    WebDeveloper(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks);
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

WebDeveloper::WebDeveloper(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks) : 
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
    string framework;
    in.get();
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
    FrontEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign);
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

FrontEndDev::FrontEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign) : 
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
    cout << "Raspuns: ";
    int response;
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
    cout << "Ce doresti sa modifici?\n";
    while(updating){
        system("CLS");
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Cunoasterea design-ului responsive\n";
        cout << "9 -> STOP\n";
        cout << "Raspuns: ";
        int response;
        cin >> response;
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza: ";
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
                cout << "Raspuns: ";
                int response;
                cin >> response;
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
        system("CLS");
        cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
        cout << "Raspuns: ";
        cin >> response;
        if(response == 2){
            updating = false;
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
    BackEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, const vector<string>& databases);
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

BackEndDev::BackEndDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, const vector<string>& databases) : 
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
    in.get();
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
    cout << "Ce doresti sa modifici?\n";
    while(updating){
        system("CLS");
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Bazele de date necesare\n";
        cout << "9 -> STOP\n";
        cout << "Raspuns: ";
        int response;
        cin >> response;
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza: ";
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
            default:{
                cout << "Index invalid!\n";
            }
        }
        system("CLS");
        cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
        cout << "Raspuns: ";
        cin >> response;
        if(response == 2){
            updating = false;
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
    FullStackDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign, const vector<string>& databases, const vector<string>& serverPlatforms);
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

FullStackDev::FullStackDev() : WebDeveloper() {
    this->serverPlatforms = {};
}

FullStackDev::FullStackDev(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply, const vector<Client>& jobApplicants, int nrLocuriDispon, const vector<string>& frameworks, bool responsiveDesign, const vector<string>& databases, const vector<string>& serverPlatforms) : 
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
    cout << "Raspuns: ";
    int response;
    in >> response;
    if(response == 1){
        this->responsiveDesign = true;
    }
    else{
        this->responsiveDesign = false;
    }

    cout << "Experienta in urmatoarele baze de date: ";
    string baza;
    in.get();
    getline(in, baza);
    stringstream s(baza);
    while(getline(s, baza, ' ')){
        this->databases.push_back(baza);
    }

    cout << "Experienta in urmatoarele platforme: ";
    string platform;
    in.get();
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
    cout << "Ce doresti sa modifici?\n";
    while(updating){
        system("CLS");
        cout << "1 -> Titlul job-ului\n";
        cout << "2 -> Salariul de baza\n";
        cout << "3 -> Locatia Job-ului\n";
        cout << "4 -> Numarul minim de ani de experienta\n";
        cout << "5 -> Limbajele de programare cerute\n";
        cout << "6 -> Numarul de locuri disponibile\n";
        cout << "7 -> Framework-urile necesare\n";
        cout << "8 -> Bazele de date necesare\n";
        cout << "9 -> Platformele necesare\n";
        cout << "10 -> STOP\n";
        cout << "Raspuns: ";
        int response;
        cin >> response;
        switch(response){
            case 1:{
                cout << "Introduceti noul titlu pentru job: ";
                string title;
                cin >> title;
                this->numeJob = title;
                break;
            }
            case 2:{
                cout << "Introduceti noul salariu de baza: ";
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
            default:{
                cout << "Index invalid!\n";
            }
        }
        system("CLS");
        cout << "Modificari realizate cu succes! Doriti sa mai modificati ceva?\n 1 -> Da\n 2 -> Nu\n";
        cout << "Raspuns: ";
        cin >> response;
        if(response == 2){
            updating = false;
        }
    }
}


int main(){
    
}