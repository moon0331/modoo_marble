
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <iostream>
#include <cstring>
#include <ctime>
#include <vector> //list���� vector����? (���Ի��� ���� ������ �����ؾ�)
#include <random>
#include <queue>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef enum { X, dorm, Suwon, Seoul } Monopoly;
typedef enum { none, odd, even } Parity;

/*������ ���, ���Ǵ� �ҽ�����*/

const int MAXLAND = 20;
const int SALARY = 20000;
const int START_MONEY = 200000;
const int COST = 1000;

const int LANDMARK = 4;
const int START_AMENTIES = -1;

const int START = 0;
const int HIDDEN1 = 1;
const int HIDDEN2 = 8;
const int HIDDEN3 = 14;
const int JAIL = 5;
const int GO_BACK = 10;
const int SPACE_SHIP = 15;
const int GAMBLE = 17;

const int IN_GWAN = 4;
const int UI_GWAN = 9;
const int YE_GWAN = 13;
const int JI_GWAN = 16;

class Person;
class Land;

//int prev_event = -1;

void Po(Person*, Person*, Person*, int);
void Ow(Land*);
void Am(Land*);
void Print(vector<Person*>&, vector<Land*>&);
int getNumber(int, int);
int getNumber(int*, int);
void display(vector<Person*>&, vector<Land*>&);
bool isHiddenCard(int);
bool isDorm(int);
bool isSeoul(int i);
int loadData(vector<Land*>&, vector<Person*>&);
void displayLandData(vector<Land*>& l);
int isMonopoly(vector<Land*>&);


void usename(vector<Person*>&);

void PP(const int no, char* name, bool nickname);

template <typename T>
void PPP(T);

class Land {
protected:
	char* name; //����

public:
	virtual ~Land();

	friend ostream& operator<<(ostream&, const Land*); //�����Ϳ��� ������ ���۷����� �ٲٱ�

													   //RealLand���� ����Ǵ� �Լ�
	virtual Person* owner() const = 0;                  //������ �����ΰ�?                     (dorm, building)
	virtual void owner(Person* who) = 0;               //���ιٲٱ�                        (dorm, building)
	virtual int isOwner(const Person* who) const = 0;      //�� ����� �����ΰ�?                  (dorm, building)
	virtual int retValue() const = 0;                  //�� ���� ��ġ��?                     (dorm, building)
	virtual bool isLandmark() const = 0;                     //���Ⱑ ���帶ũ(���� �ٲ������)�ΰ�?      (dorm, building)
	virtual void setMonopoly(Monopoly mon) = 0;            //���� ���� ����                     (dorm, building)      
	virtual int numOfAmenties() const = 0;               //������ �δ�ü� ��                  (dorm, building)
	virtual int retFee() const = 0;                     //�� ������ �����                     (dorm, building)   
	virtual void destructAmenties(int) = 0;               //�δ�ü� ���� �μ���                  (dorm, building)   

														  //Dorm�� Building���� ����� �Լ�
	virtual void constAmenties(int n = 1) = 0;            //�δ�ü� �ø���                     (dorm, building)
	virtual int costBuy() const = 0;                  //��µ� ��� ��� ��ȯ                  (dorm)               //���� ����!!      
	virtual int costBuy(int num) const = 0;                  //num��°�� ��µ� ��� ���            (building)         
	virtual int costFee(int num) const = 0;                  //�δ�ü� ���� ���� �����               (dorm, building)      //dorm������ ���� ����
	virtual void offEvent() = 0;                     //���� ����                           (dorm, building)      
	virtual void holdEvent() = 0;                     //���� ����                           (dorm, building)
	virtual Monopoly getMonopoly() = 0;
};

class RealLand : public Land {
protected:
	//char* name; //����
	const int no; //��°
	int cost_buy[4];
	int cost_fee[4];
	Person* _owner;
	int num_of_amenties;
	int value; //��ġ ����
	int fee; // ����� ����.............................
	bool is_landmark;
	Monopoly monopoly;
	int trash;
	int event;

public:
	RealLand(char* name, int cost[4], int cost2[4], int num, Monopoly mon); //�̴ϼȶ�������?
	virtual ~RealLand(); //�����Ҵ� ����

	Person* owner() const;
	void owner(Person* who);
	int isOwner(const Person* who) const;
	int retValue() const;
	bool isLandmark() const;
	int retFee() const;

	virtual void setMonopoly(Monopoly mon);
	virtual int numOfAmenties() const;
	virtual void constAmenties(int n = 1); // �⺻�� �־ �ǳ�?
	virtual void destructAmenties(int);
	int costBuy() const;
	virtual int costBuy(int num) const;
	virtual int costFee(int num) const;
	virtual void offEvent();
	virtual void holdEvent();
	virtual Monopoly getMonopoly();
};

class Dorm : public RealLand {
public:
	Dorm(char* name, int cost[4], int cost2[4], int num, Monopoly mon = dorm);
	void constAmenties(int n = 1);
	//void destructAmenties();
	int costBuy() const;
	int costFee(int num) const;
};

class Building : public RealLand {
public:
	Building(char* name, int cost[4], int cost2[4], int num, Monopoly mon = X);
	//void setMonopoly(Monopoly mon);
	//int numOfAmenties() const;
	void constAmenties(int n = 1);
	//void destructAmenties();
	int costBuy(int num) const;
	int costFee(int num) const;
};

class Dice {
	int num;
	void setVal(int start, int end);
	int random(int start, int end);
public:
	Dice();
	int role(int start = 1, int end = 6);
};

class HiddenCard {
	int val;         //�̸� ������ ��
	Person* p;         //����
	vector<Land*>* l;
	bool oddEven();
	bool holdEvent();
	bool feeFree();
	bool gotoShuttle();
	bool changeLand();
	bool destroyLand();
	bool gotoGamble();
	bool jailFree();
public:
	HiddenCard();
	HiddenCard(int value, Person* point, vector<Land*>* v);
	HiddenCard(const HiddenCard& h);
	int retVal() const;
	bool exe();
};

class Person {
	char* name;
	const int no;
	int money;
	int property;
	int position;
	int penalty;
	bool feeFree;
	int Odd;
	int Even;
	Dice dice;
	HiddenCard hid;
	bool jailFree;
	typedef enum { buy, sell, salary, get } SellOrBuy;
	int line(int); //��Ÿ��
	int soccer(int); //���Ƽű
	int rcp(int); //����������
	bool bankrupt;
public:
	Person(int n, char* name);
	~Person();

	friend ostream& operator<<(ostream&, const Person*); //������ ���۷����� ��ġ��

	int myPosition() const;
	int num() const;
	char* myName() const;
	int myMoney() const;
	int myProperty() const;
	int retOdd() const;
	int retEven() const;
	void useDiceItem(int n);
	void useJailFree();
	void Gamble(int bet); //����!!
	bool makeHiddenCard(vector<Land*>*); //����ī�� �Լ���
	HiddenCard newHidden(vector<Land*>*); //����ī�� ���� ����
	void getOddEven(int, int);
	void fee_free();
	void jail_free();
	bool retFeeFree() const;
	bool retJailFree() const;
	void no_fee_free();
	void no_jail_free();

	void rename(char*);

	int role(bool& isDouble);
	int role(bool& isDouble, int parity);
	void move(int num);
	void moveForced(int num);
	void gotoJail();
	bool isJail() const;
	int retPenalty() const;
	void buyLand(Land*& L, int n);
	int buyLandMark(Land*& L, int n);
	void sellLand(Land*& L, int n = 0); //����������� ........... �μ����ϴ°��� �Ļ��ΰ���
	void calMoney(int _salary); //�̰� �̻���
	void calMoney(int cost, SellOrBuy A); //�̰ŵ�
	bool isBankrupt() const;
	void makeBankrupt();
};