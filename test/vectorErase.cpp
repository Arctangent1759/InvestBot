#include <iostream>
#include <vector>

using namespace std;

class foobar{
    public:
        foobar(int x, vector<foobar*> *v,int deletionIndex){
            this->x=x;
            this->v=v;
            this->deletionIndex=deletionIndex;
            cout << "Constructing foobar " << this->x << "..." << endl;
        }

        ~foobar(){
            cout << "Destroying foobar " << this->x << "..." << endl;
        }

        int x;
    protected:
        vector<foobar*> *v;
        int deletionIndex;

};
int main(){

    vector<foobar*> *v = new vector<foobar*>();
    v->push_back(new foobar(0,v,v->size()));
    v->push_back(new foobar(1,v,v->size()));
    v->push_back(new foobar(2,v,v->size()));
    v->push_back(new foobar(3,v,v->size()));
    v->push_back(new foobar(4,v,v->size()));
    v->push_back(new foobar(5,v,v->size()));

    foobar* foo = new foobar(1759, v, v->size());
    v->push_back(foo);

    v->push_back(new foobar(6,v,v->size()));
    v->push_back(new foobar(7,v,v->size()));
    v->push_back(new foobar(8,v,v->size()));
    v->push_back(new foobar(9,v,v->size()));
    v->push_back(new foobar(10,v,v->size()));
    v->push_back(new foobar(11,v,v->size()));
    v->push_back(new foobar(12,v,v->size()));

    cout << endl;
    cout << endl << "Contents of vector v: ";
    for (int i = 0; i < v->size(); i++){
        cout << (*v)[i]->x << " ";
    }
    cout << endl;

    for (vector<foobar*>::iterator  i = v->begin(); i != v->end(); i++){
        if ((*i)==foo){
            v->erase(i);
        }

        cout << endl;
        cout << endl << "Contents of vector v: ";
        for (int j = 0; j < v->size(); j++){
            cout << (*v)[j]->x << " ";
        }
        cout << endl;

    }
    delete v;

    return 0;

}
