#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    vector<Professional*> vect= getProfessionals();
    for(int i = 0; i < vect.capacity(); i++){
        if(vect.at(i)->name == name){
            cout<<name<<" found."<<endl;
            return;
        }
    }
    Professional* temp = new Professional;
    temp->name = name;
    vect.push_back(temp);
    professionals.push_back(temp);
}

void LinkedInNetwork::addConnection(string v1, string v2){
    vector<Professional*> vect= getProfessionals();
    Professional* one;
    Professional* two;
    for(int i = 0; i < vect.size(); i++){
        if(vect.at(i)->name == v1){
            one = professionals.at(i);
        }
        if(vect.at(i)->name == v2){
            two = professionals.at(i);
        }
    }
    neighbor* temp = new neighbor;
    temp->v = two;
    neighbor* tempTwo = new neighbor;
    tempTwo->v = one;
    one->neighbors.push_back(*temp);
    two->neighbors.push_back(*tempTwo);
}

void LinkedInNetwork::displayConnections(){
    vector<Professional*> vect= getProfessionals();
    for(int i = 0; i < professionals.size(); i++){
        cout<< professionals.at(i)->name << " -->";
        for(int j = 0; j < professionals.at(i)->neighbors.size(); j++){
            int size = professionals.at(i)->neighbors.size();
            neighbor temp = professionals.at(i)->neighbors.at(j);
            cout << " " << temp.v->name;
        }
        cout << " " << endl;
    }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    vector<Professional*> vect= getProfessionals();
    Professional* source;
    queue<Professional*> queue;
    Professional* temp;
    for(int i = 0; i < vect.size(); i++){
        if(vect.at(i)->name == sourceProfessional){
            source = vect.at(i);
        }
    }
    queue.push(source);
    cout << "Starting Professional (root):";
    temp = source;
    source -> visited = true;
    cout << " " << temp->name <<"-> ";
    for(int i = 0; i < temp->neighbors.size(); i++){
            if(!temp->neighbors.at(i).v->visited){
                temp->neighbors.at(i).v->visited = true;
                queue.push(temp->neighbors.at(i).v);
            }
        }
    int count = 0;
    int level = 0;
    queue.pop();
    while(!queue.empty()){
        level = queue.size();
        count = count + 1;
        while(level != 0){
            temp = queue.front();
            queue.pop();
            cout<< temp->name << "(" << count << ")"<< " ";
            for(int i = 0; i < temp->neighbors.size(); i++){
                if(!temp->neighbors.at(i).v->visited){
                    temp->neighbors.at(i).v->visited = true;
                    queue.push(temp->neighbors.at(i).v);
                }
            }
            level = level - 1;
        }
    }
}

void bfs_helper(string source, vector<Professional*> &professionals) {
    vector<Professional*> out;
    for(int i = 0; i < professionals.size(); i++){
        for(int j=0; j < professionals.at(i)->neighbors.size(); j++){
            if(!professionals.at(i)->neighbors.at(j).v->visited){
                professionals.at(i)->neighbors.at(j).v->visited = true;
                out.push_back(professionals.at(i)->neighbors.at(j).v);
            }
        }
    }
    professionals = out;
}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<Professional*> vect= getProfessionals();
    Professional* source;
    queue<Professional*> queue;
    Professional* temp;
    vector<string> name;
    for(int i = 0; i < vect.size(); i++){
        if(vect.at(i)->name == professionalName){
            source = vect.at(i);
        }
    }
    queue.push(source);
    temp = source;
    source -> visited = true;
    for(int i = 0; i < temp->neighbors.size(); i++){
            if(!temp->neighbors.at(i).v->visited){
                temp->neighbors.at(i).v->visited = true;
                queue.push(temp->neighbors.at(i).v);
            }
        }
    int count = 0;
    int level = 0;
    queue.pop();
    while(!queue.empty() && count < k){
        level = queue.size();
        count = count + 1;
        while(level != 0){
            temp = queue.front();
            queue.pop();
            name.push_back(temp->name);
            for(int i = 0; i < temp->neighbors.size(); i++){
                if(!temp->neighbors.at(i).v->visited){
                    temp->neighbors.at(i).v->visited = true;
                    queue.push(temp->neighbors.at(i).v);
                }
            }
            level = level - 1;
        }
    }
    vector<string> names;
    for(int i = name.size() - 1; i > -1; i--){
        names.push_back(name.at(i));
    }
    return names;
}