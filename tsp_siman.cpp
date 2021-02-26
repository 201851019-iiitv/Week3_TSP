#include <bits/stdc++.h>
using namespace std;

//#define fast_io ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define ll long long


/*
Tourist locations in Rajasthan

vector<string> cities = {"Jaisalmer", "Jaipur", "Jodhpur", "Bundi", "Bikaner", "Ajmer", "Pushkar", "Udaipur", "Mount Abu", "Sawai Madhopur", "Bharatpur", "Alwar", "Pali", "Chittorgarh", "Hanumangarh", "Jhunjhunu", "Jhalawar", "Churu", "Kota", "Sikar"};
*/
vector<string> cities = {"Jaisalmer", "Jaipur", "Jodhpur", "Bundi", "Bikaner", "Ajmer", "Pushkar", "Udaipur", "Mount Abu", "Sawai Madhopur", "Bharatpur", "Alwar", "Pali", "Chittorgarh", "Hanumangarh", "Jhunjhunu", "Jhalawar", "Churu", "Kota", "Sikar"};

unsigned long long iter = 100000;

class Graph{
    private:
        ll nodes;
        ll** a;
        vector<ll> tour;
        ll cost;
        long double T = 1000;
    
    public:
        Graph(ll n,ll** arr): nodes(n),a(arr)
        {}

        void formGraph(){
            for(int i=0;i<nodes;i++){
                for(int j=0;j<nodes;j++){
                    if(a[i][j]==-1){
                        if(i==j)
                            a[i][j]=0;
                        else
                            a[i][j] = rand()%400+1;
                            a[j][i] = a[i][j];
                    }
                }
            }
        }

        void getGraph(){
            for(ll i=0;i<nodes;i++){
                for(ll j=0;j<nodes;j++){
                    cout<<"| "<<a[i][j]<<"\t|";
                }
                cout<<"\n";
            }
        }

        long double getTemp(){
            return T;
        }

        //random starting tour:
        void tour_gen(){
            cost=0;
            tour.push_back(0);
            ll f[nodes] = {0};
            f[0] = 1;
            for(ll i=1;i<nodes;i++){
                ll temp;
                do{
                    temp = rand()%nodes;
                }
                while(f[temp]!=0);
                f[temp] = 1;
                cost+=a[*(tour.end()-1)][temp];
                tour.push_back(temp);
            }
        }

        void getTour(){
            for(int i=0;i<tour.size();i++){
                cout<<cities[tour[i]]<<" --> ";
            }
            cout<<cities[0]<<endl;
        }

        long double returnCost(){
            
            return cost;
        }


        ll getCost(vector<ll> t){
            ll c=0;
            for(int i=0;i<t.size()-1;i++){
                c+=a[t[i]][t[i+1]];
            }
            return c;
        }

        vector<ll> generateChild(vector<ll> t){
            vector<ll> temp;
                ll one,two;
                //calculate two random nodes:
                do{
                    one = rand()%nodes;
                    two = rand()%nodes;
                }
                while(one==two||one==0||two==0);

                temp = t;

                ll ex;
                ex = temp[one];
                temp[one] = temp[two];
                temp[two] = ex;

                return temp;
        }

        

        void anneling(){
            //cost = getCost(tour);
            //vector<ll> child_cost;
            // long double e =2.71812;
            
            while(iter>0){
                //generate child:
                vector<ll> temp = generateChild(tour);
                //calculate cost:

                //annealate:
               
                    //calculate probability:
                    ll newCost = getCost(temp);
                    ll diff = newCost - cost;
                    long double r = diff/T;
                    long double p = 1/(1+exp(-r));

                    if(diff<0){
                        //select
                        tour = temp;
                        cost = newCost;
                        T*=0.2;
                        //getTour();
                    }
                    else{
                        long double prob = 1 / rand();
                        if(prob > p){
                            //select
                            tour = temp;
                            cost = newCost;
                            T*=0.2;
                        }
                    }
                    iter--;
            }    
        }
        







};


int main() {
    srand(time(0));
    //fast_io;
    ll n = 20;
    // cout<<"enter the number of nodes:\n";
    // cin>>n;
    ll** a = new ll*[n];
    ll ex[5] = {0};
    for(ll i=0;i<n;i++){
        a[i] = new ll[n];
        for(ll j=0;j<n;j++){
            a[i][j] = -1;
        }
    }

    Graph g(n,a);
    cout<<"Initial Temperature = "<<g.getTemp()<<endl;
    cout<<"Number of Iterations = "<<iter<<endl;
    cout<<"\nCities are:"<<endl;
    for(auto i: cities){
        cout<<"| "<<i<<" ";
    }
    cout<<endl;
    g.formGraph();
    cout<<"Genrated graph is:\n";
    g.getGraph();
    cout<<"\n";
    g.tour_gen();
    cout<<"Initaial tour is:\n";
    g.getTour();
    cout<<"initial cost is:\n"<<g.returnCost()<<endl;
    g.anneling();
    cout<<"Final tour is:\n";
    g.getTour();
    cout<<"Final cost is:\n"<<g.returnCost()<<endl;
    //cout<<"\n"<<ttt<<endl;


}
