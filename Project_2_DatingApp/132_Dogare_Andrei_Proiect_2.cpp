#include <bits/stdc++.h>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
class Client {
    
};
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

    //------- GETTERS -------//
    int getSalariu() const {return this->salariuDeBaza;}
    string getNumeJob() const {return this->numeJob;}
    locatie getLocatieJob() const {return this->locatieJob;}
    int getNrAniExperienta() const {return this->nrAniExperientaMin;}
    vector<string> getLimbajeNecesare() const {return this->limbajeCerute;}
    bool getEasyApply() const {return this->easyApply;}
    vector<Client> getJobApplicants() const {return this->jobApplicants;}
    int getNrLocuriDispon() const {return this->nrLocuriDispon;}

    //------- METODE -------//
    virtual void modificaAnunt() = 0;
    void addJobApplicant(const Client& user){this->jobApplicants.push_back(user);}
    void offerJob();

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

    cout << "Limbajele de programare necesare job-ului: ";
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

void Job::offerJob(){
    /// sorteaza lista de clienti dupa avgScore si apoi angajeaza primii this->nrLocuriDispon. restu vad ei ce fac
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

    //------- GETTERS -------//
    vector<string> getFrameworks() const {return this->frameworks;}

    //------- METODE -------//
    // virtual void test() = 0;

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

    //------- GETTERS -------//
    bool getResponsiveDesign() const {return this->responsiveDesign;}

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

    //------- GETTERS -------//
    vector<string> getDatabases() const {return this->databases;}

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
    cout << "Experienta in urmatoarele baze de date: ";
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

    //------- GETTERS -------//
    vector<string> getDatabases() const {return this->serverPlatforms;}

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


int main(){
    
}