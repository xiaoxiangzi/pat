//
//  PTAIntimacy.cpp
//  pat
//
//  Created by xiaoxiangzi on 2018/5/17.
//  Copyright © 2018年 xiaoxiangzi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <deque>
#include <math.h>
#include <sstream>
using namespace std;

struct Intimacy {
    string id;
    float intimacy;
};

struct Person {
    string id;
    unordered_map<string, Intimacy> intimacyMap;
};

void addIncimacyInList(vector<Person*>& persons) {
    int k = (int) persons.size();
    float intimacy = 1.0 / k;
    for (int i = 0; i < k; i++) {
        Person* a = persons[i];
        for (int j = 0; j < k; j++) {
            if (i == j) {
                continue;
            }
            Person* b = persons[j];
            auto iter = b->intimacyMap.find(a->id);
            if (iter != b->intimacyMap.end()) {
                iter->second.intimacy += intimacy;
            } else {
                Intimacy item;
                item.id = a->id;
                b->intimacyMap.insert(make_pair(a->id, item));
            }
        }
    }
}

bool compareIntimacy(Intimacy& a, Intimacy& b) {
    if (abs(a.intimacy - b.intimacy) < 0.0000001) {
        return abs(atoi(a.id.c_str())) < abs(atoi(b.id.c_str()));
    }
    return a.intimacy > b.intimacy;
}

void printIntimacyList(const Person& person, const vector<Intimacy>& intimacyList) {
    for (int i = 0; i < intimacyList.size(); i++) {
        cout << person.id << " " << intimacyList[i].id << endl;
    }
}

vector<Intimacy> findIntimacyList(string id, const unordered_map<string, Person>& personsMap, string checkId, bool& hasCheckId) {
    vector<Intimacy> result;
    auto& person = personsMap.at(id);
    for (auto iter = person.intimacyMap.begin(); iter != person.intimacyMap.end(); iter++) {
        result.push_back(iter->second);
    }
    sort(result.begin(), result.end(), compareIntimacy);
    float maxIntimacy = -1;
    int indexToDel = -1;
    for (int i = 0; i < result.size(); i++) {
        Intimacy& intimacy = result[i];
        if (maxIntimacy < 0) {
            maxIntimacy = intimacy.intimacy;
        } else if ((maxIntimacy - intimacy.intimacy) >= 0.0000001) {
            indexToDel = i;
            break;
        }
        if (intimacy.id == checkId) {
            hasCheckId = true;
        }
    }
    
    if (indexToDel > 0) {
        result.erase(result.begin() + indexToDel, result.end());
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    freopen("PTAIntimacy.txt", "r", stdin);
    int n = 0;
    int m = 0;
    cin >> n >> m;
    unordered_map<string, Person> persons;
    for (int i = 0; i < m; i++) {
        int k = 0;
        cin >> k;
        vector<Person*> personList;
        for (int j = 0; j < k; j++) {
            string id;
            cin >> id;
            auto iter = persons.find(id);
            Person* p = nullptr;
            if (iter != persons.end()) {
                p = &iter->second;
            } else {
                Person person;
                person.id = id;
                persons.insert(make_pair(id, person));
                p = &persons.at(id);
            }
            personList.push_back(p);
        }
        addIncimacyInList(personList);
    }
    
    string aId;
    string bId;
    cin >> aId >> bId;
    
    bool hasB = false;
    bool hasA = false;
    vector<Intimacy> aList = findIntimacyList(aId, persons, bId, hasB);
    vector<Intimacy> bList = findIntimacyList(bId, persons, aId, hasA);
    
    if (hasB && hasA) {
        cout << aId << " " << bId << endl;
    } else {
        printIntimacyList(persons.at(aId), aList);
        printIntimacyList(persons.at(bId), bList);
    }
    
    return 0;
}
