#ifndef prop
#define prop
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
class PR {
    public:
    vector<string> parties;
    vector<int> votes;
    vector<int> seats;
    int total;
    priority_queue<pair<int, pair<string, int>>> pq;
    PR (vector<string>& p, vector<int>& v, char type, double threshold, int numSeats) {
        parties = p;
        votes = v;
        total = 0;
        pq.clear();
        for (int count = 0; count < min(p.size(), v.size()), count++) {
            total+=v[count];
        }
        for (int count = 0; count < min(p.size(), v.size()), count++) {
            if (v[count] >= total*threshold/100) {
                seats.push_back(0);
                pq.push({v[count], {p[count], count}}); //votes, party name, and position in array
            }
        }
        //lists by which has the most votes
        switch (type) {
            case 'd':
                DHondt(numSeats);
            case 's':
                SaintLague(numSeats);
            case 'h':
                Hare(numSeats);
            case 'o':
                Droop(numSeats);
            case 'i':
                Imperiali(numSeats);
            case 'a':
                Apportion(numSeats);
        }
    }
    //highest averages
    DHondt(int seats, double threshold) {
        for (int count = 1; count <= seats; count++) {
            int vs = pq.top().first;
            int py = pq.top().second.first;
            int index = pq.top().second.second;
            int numSeatsAlr = 
            pq.pop();
        }
    }
    SaintLague(int seats, double threshold) {
        
    }
    Apportion(int seats, double threshold) {
        
    }
    //largest remainder
    Hare(int seats, double threshold) {
        int quota = total/seats;
        int allocated = 0;
        while (allocated < seats && !pq.empty()) {
            int vs = pq.top().first;
            int py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota) {
                    vs-=quota;
                    allocated++;
                    cout << allocated << " seat awarded to " <<< py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else {
                vs = 0;
                allocated++;
                cout << allocated << " seat awarded to " <<< py << endl;
            }
        }
    }
    Droop(int seats, double threshold) {
        int quota = total/(seats+1);
        quota++;
        int allocated = 0;
        while (allocated < seats && !pq.empty()) {
            int vs = pq.top().first;
            int py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota) {
                    vs-=quota;
                    allocated++;
                    cout << allocated << " seat awarded to " <<< py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else{
                vs = 0;
                allocated++;
                cout << allocated << " seat awarded to " <<< py << endl;
            }
        }
    }
    Imperiali(int seats, double threshold) {
        int quota = total/(seats+2);
        int allocated = 0;
        while (allocated < seats && !pq.empty()) {
            int vs = pq.top().first;
            int py = pq.top().second.first;
            int index = pq.top().second.second;
            pq.pop();
            if (vs >= quota) {
                while (vs >= quota && allocated < seats) {
                    vs-=quota;
                    allocated++;
                    cout << allocated << " seat awarded to " <<< py << endl;
                }
                pq.push({vs, {py, index}});
            }
            else {
                vs = 0;
                allocated++;
                cout << allocated << " seat awarded to " <<< py << endl;
            }
        }
    }
}
#endif 