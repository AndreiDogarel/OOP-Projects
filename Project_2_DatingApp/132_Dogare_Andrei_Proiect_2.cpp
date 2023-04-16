#include <bits/stdc++.h>

using namespace std;

class IOInterface {
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class Job : public IOInterface{
protected:
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
    Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply);
    Job(const Job& obj);

    //------- OPERATORI -------//
    Job& operator = (const Job& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator >> (istream &in, Job &obj)
    {
        return obj.citire(in);
    }
    friend ostream& operator << (ostream& out, const Job& obj){
        return obj.afisare(out);
    }

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
}

Job::Job(string numeJob, int salariuDeBaza, locatie locatieJob, int nrAniExperientaMin, const vector<string>& limbajeCerute, bool easyApply){
    this->numeJob = numeJob;
    this->salariuDeBaza = salariuDeBaza;
    this->locatieJob = locatieJob;
    this->nrAniExperientaMin = nrAniExperientaMin;
    this->limbajeCerute = limbajeCerute;
    this->easyApply = easyApply;
}

Job::Job(const Job& obj){
    this->numeJob = obj.numeJob;
    this->salariuDeBaza = obj.salariuDeBaza;
    this->locatieJob = obj.locatieJob;
    this->nrAniExperientaMin = obj.nrAniExperientaMin;
    this->limbajeCerute = obj.limbajeCerute;
    this->easyApply = obj.easyApply;
}

Job& Job::operator = (const Job& obj){
    if(this != &obj){
        this->numeJob = obj.numeJob;
        this->salariuDeBaza = obj.salariuDeBaza;
        this->locatieJob = obj.locatieJob;
        this->nrAniExperientaMin = obj.nrAniExperientaMin;
        this->limbajeCerute = obj.limbajeCerute;
        this->easyApply = obj.easyApply;
    }
    return *this;
}

istream& Job::citire(istream& in){
    cout << "Numele Job-ului: ";
    in >> this->numeJob;

    cout << "Salariu: ";
    in >> this->salariuDeBaza;

    cout << "Locatia Job-ului:\n";
    cout << " Tara: ";
    in >> this->locatieJob.numeTara;
    cout << " Oras: ";
    in >> this->locatieJob.numeOras;
    cout << " Strada: ";
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
}

int main(){
    Job j;
    cin >> j;
    cout << j;
}