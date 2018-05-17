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

struct Person {
    int id;
    Sex sex;
    unordered_map<int, float> intimacyMap;
};

struct Intimacy {
    const Person* p;
    float intimacy;
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
                iter->second += intimacy;
            } else {
                b->intimacyMap.insert(make_pair(a->id, intimacy));
            }
        }
    }
}

bool compareIntimacy(Intimacy& a, Intimacy& b) {
    if (abs(a.intimacy - b.intimacy) < 0.0000001) {
        return a.p->id < b.p->id;
    }
    return a.intimacy > b.intimacy;
}

string getPersonStr(const Person* p) {
    stringstream ss;
    if (p->sex == FEMALE) {
        ss << "-";
    }
    ss << p->id;
    return ss.str();
}

void printIntimacyList(const Person& person, const vector<Intimacy>& intimacyList) {
    string personStr = getPersonStr(&person);
    for (int i = 0; i < intimacyList.size(); i++) {
        cout << personStr << " " << getPersonStr(intimacyList[i].p) << endl;
    }
}

vector<Intimacy> findIntimacyList(int id, const unordered_map<int, Person>& personsMap, int checkId, bool& hasCheckId) {
    vector<Intimacy> result;
    auto& person = personsMap.at(id);
    for (auto iter = person.intimacyMap.begin(); iter != person.intimacyMap.end(); iter++) {
        Intimacy i;
        i.p = &personsMap.at(iter->first);
        i.intimacy = iter->second;
        result.push_back(i);
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
        if (intimacy.p->id == checkId) {
            hasCheckId = true;
        }
    }
    
    if (indexToDel > 0) {
        result.erase(result.begin() + indexToDel, result.end());
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
//    freopen("PTAIntimacy-1.txt", "r", stdin);
    int n = 0;
    int m = 0;
    cin >> n >> m;
    unordered_map<int, Person> persons;
    for (int i = 0; i < m; i++) {
        int k = 0;
        cin >> k;
        vector<Person*> personList;
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
        addIncimacyInList(personList);
    }
    
    int aId = 0;
    int bId = 0;
    cin >> aId >> bId;
    aId = abs(aId);
    bId = abs(bId);
    
    bool hasB = false;
    bool hasA = false;
    vector<Intimacy> aList = findIntimacyList(aId, persons, bId, hasB);
    vector<Intimacy> bList = findIntimacyList(bId, persons, aId, hasA);
    
    if (hasB && hasA) {
        cout << getPersonStr(&persons.at(aId)) << " " << getPersonStr(&persons.at(bId)) << endl;
    } else {
        printIntimacyList(persons.at(aId), aList);
        printIntimacyList(persons.at(bId), bList);
    }
    
    return 0;
}
