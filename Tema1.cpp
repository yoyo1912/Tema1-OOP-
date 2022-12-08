#include <iostream>

using namespace std;
class Multime{
private:
    int nrElem; //numarul de elemente
    int* arr; //vectorul propriu zis
public:

    //constructor default fara parametri
    Multime(){
        nrElem=1;
        arr = new int[nrElem];
        arr[0]=0;
    }

    //constructor default cu parametri
    Multime(int nrElem_){

        nrElem = nrElem_;
        arr = new int[nrElem_];

    }

    //constructor de copiere
    Multime(const Multime& A){

        nrElem=A.nrElem;
        arr=new int[A.nrElem];
        for(int i=0;i<A.nrElem;i++)
            arr[i]=A.arr[i];
    }

    //destructor
    ~Multime(){

        delete[] arr;
    }

    //functie de filtrare a elementelor (adica sa nu existe 2 elemente identice)
    void filter(){

        int frev[100] = {0}; //creez un vector de frecventa
         for(int i=0;i<nrElem;i++){
            int val=arr[i];
             frev[val]++; //cresc vectorul de frecventa cu 1 pentru aparitia valorii val

            //daca valoarea a aparut din nou, o sterg din vector
            //apoi scad numarul de elemente cu 1 si valoarea lui i, pentru ca pe pozitia i avem alt element acum
            if(frev[val]>1){
                for(int j=i;j<nrElem-1;j++)
                    arr[j]=arr[j+1];
                nrElem--;
                i--;
            }
        }
    }

    //setter pentru numarul de elemente
    void setNrElem(int newNrElem){

        nrElem = newNrElem;
    }

    //setter pentru vectorul propriu zis
        void setArr(const int* newArr){

            delete[] arr;
            arr = new int[nrElem];
            for(int i=0;i<nrElem;i++){
                arr[i] = newArr[i];
            }
            this->filter();
        }

    //supraincarcarea operatorilor >>
    friend istream& operator>>(istream &is, Multime &A) {

        int buf[100], nrBuf;
        cout << "Numarul de elemente: ";
        is >> nrBuf;
        A.setNrElem(nrBuf);
        cout << "\n";
        cout << "Elementele multimii: ";
        for(int i=0;i<A.nrElem;i++){
            is >> buf[i];
            cout << " ";
        }
        cout << "\n";
        A.setArr(buf);
        return is;
    }

    //supraincarcarea operatorilor <<
    friend ostream& operator<<(ostream &os, Multime &A) {

        if (!A.arr) {
            os << "Multimea nu a fost initializata\n";
            return os;
        }
        os << "Multimea contine elementele:\n";
        for(int i=0;i<A.nrElem;i++){
            os << A.arr[i] << " ";
        }
        os <<"\n";
        os <<"Si are " << A.nrElem <<" elemente\n";
        return os;
    }
    //getter pentru numarul de elemente
    int getNrElem() const {

        return nrElem;
    }

    //getter pentru vectorul propriu zis
    int *getArr(){

        return arr;
    }

    //operator de atribuire "="
    Multime& operator=(const Multime &rhs) {

        setNrElem(rhs.nrElem);
        if (this != &rhs)
            this->setArr(rhs.arr);
        return *this;
    }

    //supraincarcarea elementului + pentru reuniunea a doua multimi
    Multime operator+(const Multime &rhs){

        Multime C(nrElem + rhs.nrElem);
        for(int i=0;i<nrElem;i++){
            C.arr[i]=arr[i];
        }
        for(int i=0;i<rhs.nrElem;i++){
            C.arr[nrElem+i] = rhs.arr[i];
        }
        return C;
    }

    //supraincarcarea elementului * pentru intersectia a doua multimi
    Multime operator*(const Multime &rhs){

        Multime C(nrElem);
        bool apar[100]={false};
        int k=-1;
        for(int i=0;i<nrElem;i++){
            int val=arr[i];
            apar[val]=true;
        }
        for(int i=0;i<rhs.nrElem;i++){
            int val=rhs.arr[i];
            if(apar[val])
                C.arr[++k]=val;
        }
        C.setNrElem(k+1);
        return C;
    }

    //supraincarcarea elementului - pentru diferenta a doua multimi
    Multime operator-(const Multime &rhs){

        Multime C(nrElem);
        bool apar[100]={false};
        int k=-1;
        for(int i=0;i<rhs.nrElem;i++){
            int val=rhs.arr[i];
            apar[val]=true;
        }
        for(int i=0;i<nrElem;i++){
            int val=arr[i];
            if(!apar[val])
                C.arr[++k]=val;
        }
        C.setNrElem(k+1);
        return C;
    }

    //obtinere numar de elemente ale multimii
    int len() const {

        return nrElem;
    }

};

int main() {
    int userInput, nrMultimi;
    cout<<"Numarul de multimi: ";
    cin>>nrMultimi;
    cout<<"\n";
    Multime M[nrMultimi],C;
    for(int i=0;i<nrMultimi;i++){
        cout<<"Informatii legate de multimea "<<i+1<<" :\n";
        cin>>M[i];
    }
    while(true){
        int mult1,mult2;
        bool ok=false;
        cout<<"Introduceti numarul corespunzator cerintei dorite:\n"
              "1.Reuniunea a doua multimi alese\n"
              "2.Intersectia a doua multimi alese\n"
              "3.Diferenta a doua multimi alese\n"
              "4.Obtinerea numarului de elemente al unei multimi alese\n"
              "5.Oprirea programului\n";
        cin>>userInput;
        switch (userInput) {
            case 1:
                cout<<"Introduceti numarul corespunzator multimilor alese: ";
                cin>>mult1>>mult2;
                cout<<"\n";
                C = M[mult1-1] + M[mult2-1];
                cout<<C<<"\n";
                break;
            case 2:
                cout<<"Introduceti numarul corespunzator multimilor alese: ";
                cin>>mult1>>mult2;
                cout<<"\n";
                C = M[mult1-1] * M[mult2-1];
                cout<<C<<"\n";
                break;
            case 3:
                cout<<"Introduceti numarul corespunzator multimilor alese: ";
                cin>>mult1>>mult2;
                cout<<"\n";
                C = M[mult1-1] - M[mult2-1];
                cout<<C<<"\n";
                break;
            case 4:
                cout<<"Introduceti numarul corespunzator multimi alese: ";
                cin>>mult1;
                cout<<"\n";
                cout<<M[mult1-1].len()<<"\n";
                break;
            case 5:
                cout<<"Va multumesc pentru timpul acordat!";
                ok=true;
                break;
            default:
                cout<<"Va rog sa introduceti un numar valid!";
                break;

        }
        if(ok)
            break;
    }

    return 0;
}
