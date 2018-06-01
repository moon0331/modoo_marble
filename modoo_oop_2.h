
#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <iostream>
#include <cstring>
#include <ctime>
#include <vector> //list일지 vector일지? (삽입삭제 빠른 것으로 선택해야)
#include <random>
#include <queue>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef enum { X, dorm, Suwon, Seoul } Monopoly;
typedef enum { none, odd, even } Parity;

/*선언은 헤더, 정의는 소스파일*/

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
	char* name; //지명

public:
	virtual ~Land();

	friend ostream& operator<<(ostream&, const Land*); //포인터에서 포인터 레퍼런스로 바꾸기

													   //RealLand에서 종결되는 함수
	virtual Person* owner() const = 0;                  //주인이 누구인가?                     (dorm, building)
	virtual void owner(Person* who) = 0;               //주인바꾸기                        (dorm, building)
	virtual int isOwner(const Person* who) const = 0;      //이 사람이 주인인가?                  (dorm, building)
	virtual int retValue() const = 0;                  //이 땅의 가치는?                     (dorm, building)
	virtual bool isLandmark() const = 0;                     //여기가 랜드마크(주인 바뀔수없음)인가?      (dorm, building)
	virtual void setMonopoly(Monopoly mon) = 0;            //독점 여부 설정                     (dorm, building)      
	virtual int numOfAmenties() const = 0;               //세워진 부대시설 수                  (dorm, building)
	virtual int retFee() const = 0;                     //총 내야할 통행료                     (dorm, building)   
	virtual void destructAmenties(int) = 0;               //부대시설 전부 부수기                  (dorm, building)   

														  //Dorm과 Building에서 사용할 함수
	virtual void constAmenties(int n = 1) = 0;            //부대시설 올리기                     (dorm, building)
	virtual int costBuy() const = 0;                  //사는데 드는 비용 반환                  (dorm)               //현재 없음!!      
	virtual int costBuy(int num) const = 0;                  //num번째를 사는데 드는 비용            (building)         
	virtual int costFee(int num) const = 0;                  //부대시설 수에 따른 통행료               (dorm, building)      //dorm에서는 변수 무시
	virtual void offEvent() = 0;                     //축제 해제                           (dorm, building)      
	virtual void holdEvent() = 0;                     //축제 열기                           (dorm, building)
	virtual Monopoly getMonopoly() = 0;
};

class RealLand : public Land {
protected:
	//char* name; //지명
	const int no; //번째
	int cost_buy[4];
	int cost_fee[4];
	Person* _owner;
	int num_of_amenties;
	int value; //가치 총합
	int fee; // 통행료 총합.............................
	bool is_landmark;
	Monopoly monopoly;
	int trash;
	int event;

public:
	RealLand(char* name, int cost[4], int cost2[4], int num, Monopoly mon); //이니셜라이저는?
	virtual ~RealLand(); //동적할당 해제

	Person* owner() const;
	void owner(Person* who);
	int isOwner(const Person* who) const;
	int retValue() const;
	bool isLandmark() const;
	int retFee() const;

	virtual void setMonopoly(Monopoly mon);
	virtual int numOfAmenties() const;
	virtual void constAmenties(int n = 1); // 기본값 넣어도 되나?
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
	int val;         //미리 굴려서 감
	Person* p;         //주인
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
	int line(int); //줄타기
	int soccer(int); //페널티킥
	int rcp(int); //가위바위보
	bool bankrupt;
public:
	Person(int n, char* name);
	~Person();

	friend ostream& operator<<(ostream&, const Person*); //포인터 레퍼런스로 고치기

	int myPosition() const;
	int num() const;
	char* myName() const;
	int myMoney() const;
	int myProperty() const;
	int retOdd() const;
	int retEven() const;
	void useDiceItem(int n);
	void useJailFree();
	void Gamble(int bet); //주의!!
	bool makeHiddenCard(vector<Land*>*); //히든카드 함수들
	HiddenCard newHidden(vector<Land*>*); //히든카드 실제 만듬
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
	void sellLand(Land*& L, int n = 0); //구분해줘야함 ........... 인수당하는건지 파산인건지
	void calMoney(int _salary); //이거 이상함
	void calMoney(int cost, SellOrBuy A); //이거도
	bool isBankrupt() const;
	void makeBankrupt();
};