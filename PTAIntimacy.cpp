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

typedef enum {
    MALE,
    FEMALE,
} Sex;

struct Intimacy {
    int id;
    float intimacy;
};

struct Person {
    int id;
    Sex sex;
    unordered_map<int, Intimacy> intimacyMap;
};

void readPersonInfo(int& id, Sex& sex) {
    string s;
    cin >> s;
    if (s[0] == '-') {
        sex = FEMALE;
    } else {
        sex = MALE;
    }
    id = abs(atoi(s.c_str()));
}

void addIncimacyInList(vector<Person*>& persons, const Person& pa, const Person& pb) {
    int k = (int) persons.size();
    float intimacy = 1.0 / k;
    for (int i = 0; i < k; i++) {
        Person* a = persons[i];
        if (a->id != pa.id && a->id != pb.id) {
            continue;
        }
        
        for (int j = 0; j < k; j++) {
            if (i == j) {
                continue;
            }
            
            Person* b = persons[j];
            if (a->sex == b->sex) {
                continue;
            }
            
            auto iter = a->intimacyMap.find(b->id);
            if (iter != a->intimacyMap.end()) {
                iter->second.intimacy += intimacy;
            } else {
                Intimacy item;
                item.id = b->id;
                item.intimacy = intimacy;
                a->intimacyMap.insert(make_pair(b->id, item));
            }
        }
    }
}

bool compareIntimacy(Intimacy& a, Intimacy& b) {
    if (abs(a.intimacy - b.intimacy) < 0.0000001) {
        return a.id < b.id;
    }
    return a.intimacy > b.intimacy;
}

void printPerson(const Person& p) {
    if (p.sex == FEMALE) {
        cout << "-";
    }
    cout << p.id;
}

void printIntimacyList(const Person& person, const vector<Intimacy>& intimacyList, const unordered_map<int, Person>& personsMap) {
    for (int i = 0; i < intimacyList.size(); i++) {
        auto& p = personsMap.at(intimacyList[i].id);
        printPerson(person);
        cout << " ";
        printPerson(p);
        cout << endl;
    }
}

vector<Intimacy> findIntimacyList(int id, const unordered_map<int, Person>& personsMap, int checkId, bool& hasCheckId) {
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
//    freopen("PTAIntimacy.txt", "r", stdin);
    int n = 0;
    int m = 0;
    cin >> n >> m;
    unordered_map<int, Person> persons;
    vector<vector<Person*>> pics;
    pics.resize(m);
    for (int i = 0; i < m; i++) {
        int k = 0;
        cin >> k;
        vector<Person*>& personList = pics[i];
        for (int j = 0; j < k; j++) {
            int id;
            Sex sex;
            readPersonInfo(id, sex);
            auto iter = persons.find(id);
            Person* p = nullptr;
            if (iter != persons.end()) {
                p = &iter->second;
            } else {
                Person person;
                person.id = id;
                person.sex = sex;
                persons.insert(make_pair(id, person));
                p = &persons.at(id);
            }
            personList.push_back(p);
        }
    }
    
    int aId;
    Sex aSex;
    readPersonInfo(aId, aSex);
    int bId;
    Sex bSex;
    readPersonInfo(bId, bSex);
    auto iter = persons.find(aId);
    if (iter == persons.end()) {
        Person person;
        person.id = aId;
        person.sex = aSex;
        persons.insert(make_pair(aId, person));
    }
    
    iter = persons.find(bId);
    if (iter == persons.end()) {
        Person person;
        person.id = bId;
        person.sex = bSex;
        persons.insert(make_pair(bId, person));
    }
    
    Person& pa = persons[aId];
    Person& pb = persons[bId];
    for (int i = 0; i < m; i++) {
        vector<Person*>& personList = pics[i];
        addIncimacyInList(personList, pa, pb);
    }
    
    bool hasB = false;
    bool hasA = false;
    vector<Intimacy> aList = findIntimacyList(aId, persons, bId, hasB);
    vector<Intimacy> bList = findIntimacyList(bId, persons, aId, hasA);
    
    if ((hasB && hasA) || (aList.empty() && bList.empty())) {
        printPerson(pa);
        cout << " ";
        printPerson(pb);
        cout << endl;
    } else {
        printIntimacyList(persons.at(aId), aList, persons);
        printIntimacyList(persons.at(bId), bList, persons);
    }
    
    return 0;
}
