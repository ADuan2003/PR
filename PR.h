#ifndef prop
#define prop
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
class PR {
    public:
    vector<int> sets;
    int total;
    priority_queue<pair<int, pair<string, int>>> pq;
    PR (vector<string>& p, vector<int>& v, char type, double threshold, int numSeats) {
        total = 0;
        while (!pq.empty()) {
            pq.pop();
        }
        sets.clear();
        for (int count = 0; count < min(p.size(), v.size()); count++) {
            total+=v[count];
        }
        int temp = 0;
        for (int count = 0; count < min(p.size(), v.size()); count++) {
            sets.push_back(0);
            if (v[count] >= total*threshold/100) {
                temp+=v[count];
                pq.push({v[count], {p[count], count}}); //votes, party name, and position in array
            }
        }
        total = temp;
        //lists by which has the most votes
        switch (type) {
            case 'd':
            cout << "REPUBLICAN" << endl;
                DHondt(numSeats);
                break;
            case 's':
                SaintLague(numSeats);
                break;
            case 'h':
            cout << "DEMOCRATIC" << endl;
                Hare(numSeats);
                break;
            case 'o':
                Droop(numSeats);
                break;
            case 'i':
                Imperiali(numSeats);
                break;
            case 'a':
                Apportion(numSeats);
                break;
        }
        for (int count = 0; count < v.size(); count++) {
            cout << p[count] << " " << v[count] << " " << sets[count] << endl;
        }
    };
    void DHondt(int);
    void SaintLague(int);
    void Apportion(int);
    void Hare(int);
    void Droop(int);
    void Imperiali(int);
};
//highest averages
    void PR::DHondt(int seats) {
        for (int count = 1; count <= seats; count++) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            cout << count << " seat awarded to " << py << endl;
            sets[index]++;
            int numSeats = sets[index];
            vs = (vs*numSeats)/(numSeats+1);
            pq.push({vs, {py, index}});
        }
        return;
    }
    void PR::SaintLague(int seats) {
        for (int count = 1; count <= seats; count++) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            cout << count << " seat awarded to " << py << endl;
            sets[index]++;
            int numSeats = sets[index];
            vs = (vs*(2*numSeats-1))/(2*numSeats+1);
            pq.push({vs, {py, index}});
        }
        return;
    }
    void PR::Apportion(int seats) {
        if (pq.size() > seats) {
            cout << "too many states and too few seats" << endl;
            return;
        }
        priority_queue<pair<int, pair<string, int>>> pq2;
        int alloc = 0;
        while (!pq.empty()) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            sets[index]++;
            alloc++;
            cout << alloc << " seat awarded to " << py << endl;
            vs = vs/sqrt(2);
            pq2.push({vs, {py, index}});
        }
        while (alloc < seats) {
            int vs = pq2.top().first;
            string py = pq2.top().second.first;
            int index = pq2.top().second.second;
            pq2.pop();
            sets[index]++;
            alloc++;
            cout << alloc << " seat awarded to " << py << endl;
            int numSeats = sets[index];
            vs = (vs*sqrt(numSeats-1))/sqrt(numSeats+1);
            pq2.push({vs, {py, index}});
        }
        return;
    }
    //largest remainder
    void PR::Hare(int seats) {
        int quota = total/seats;
        int allocated = 0;
        while (allocated < seats) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota) {
                    vs-=quota;
                    sets[index]++;
                    allocated++;
                    cout << allocated << " seat awarded to " << py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else {
                allocated++;
                sets[index]++;
                cout << allocated << " seat awarded to " << py << endl;
            }
        }
        return;
    }
    void PR::Droop(int seats) {
        int quota = total/(seats+1);
        quota++;
        int allocated = 0;
        while (allocated < seats) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota) {
                    vs-=quota;
                    sets[index]++;
                    allocated++;
                    cout << allocated << " seat awarded to " << py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else{
                sets[index]++;
                allocated++;
                cout << allocated << " seat awarded to " << py << endl;
            }
        }
        return;
    }
    void PR::Imperiali(int seats) {
        int quota = total/(seats+2);
        int allocated = 0;
        while (allocated < seats && !pq.empty()) {
            int vs = pq.top().first;
            string py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota && allocated < seats) {
                    vs-=quota;
                    sets[index]++;
                    allocated++;
                    cout << allocated << " seat awarded to " << py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else {
                sets[index]++;
                allocated++;
                cout << allocated << " seat awarded to " << py << endl;
            }
        }
        return;
    }
#endif 
