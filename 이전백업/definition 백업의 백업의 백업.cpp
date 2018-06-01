#include "modoo_oop_2.h"

//생성자 잘 된건가?

//디폴트 매개변수는 선언에만 해야함..................지우기!

int prev_event = 1;

Land::~Land(){}

RealLand::RealLand(char* name, int cost[4], int cost2[4], int num, Monopoly mon) 
	:	no(num), monopoly(mon), _owner(NULL), num_of_amenties(START_AMENTIES), 
		value(0), fee(0), is_landmark(false), event(1)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name); //이름 복사
	for (int i = 0; i < 4; i++) {
		cost_buy[i] = cost[i], cost_fee[i] = cost2[i];
	}
} //value 초기화값??

RealLand::~RealLand() {
	delete[] name;
}

Dorm::Dorm(char* name, int cost[4], int cost2[4], int num, Monopoly mon) 
: RealLand(name, cost, cost2, num, mon) {}

Building::Building(char* name, int cost[4], int cost2[4], int num, Monopoly mon)
	: RealLand(name, cost, cost2, num, mon){}

Person* RealLand::owner() const {
	return _owner;
}

void RealLand::owner(Person* who) {
	_owner = who;
}

int RealLand::isOwner(const Person* who) const {
	if (_owner == who) return retValue();
	else return 0;
}

int RealLand::retValue() const {
	return value;
}

bool RealLand::isLandmark() const {
	return is_landmark;
}

void RealLand::setMonopoly(Monopoly mon) { //더 안내려가도 될듯?
	monopoly = mon;
}

int RealLand::numOfAmenties() const { //더이상 안내려가도 될듯?
	return num_of_amenties;
}

int RealLand::retFee() const {
	return fee; //총 내야할 금액
}

void RealLand::destructAmenties(int n) { //n==0이면 인수할때, n==1이면 파산할때
	if (n == 1) {
		num_of_amenties = START_AMENTIES;
	}
	_owner = NULL;
	is_landmark = false;
	value = 0;
}

void RealLand::holdEvent() {
	event = 2;
}

void RealLand::offEvent() {
	event = 1;
}
//-----------------------------------더 오버라이딩되는 함수들


void RealLand::constAmenties(int n) {
	cout << "ERROR of void constAmenties(int n-=1) of RealLand Class" << endl;
}

void Dorm::constAmenties(int n) {
	num_of_amenties = 1;
	is_landmark = true;
}

void Building::constAmenties(int n) {
	while (n--) {
		num_of_amenties++;
		value += cost_buy[num_of_amenties];
		fee += cost_fee[num_of_amenties];
	}
	if (num_of_amenties == LANDMARK) is_landmark = true;
}


//value는 0으로 초기화!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int RealLand::costBuy() const {
	cout << "ERROR of void constAmenties(int n-=1) of RealLand Class" << endl;
	return cost_buy[0];
}

int Dorm::costBuy() const {
	return cost_buy[0];
}

int RealLand::costBuy(int num) const {
	//cout << "ERROR of costFee(int) for RealLand class" << endl;
	return cost_buy[num];
}

int Building::costBuy(int num) const {
	return cost_buy[num];
}

int RealLand::costFee(int num) const {
	return cost_fee[num];
}

int Dorm::costFee(int num) const {
	return cost_fee[0];
}

int Building::costFee(int num) const {
	return cost_fee[num];
}

Monopoly RealLand::getMonopoly() {
	return monopoly;
}

/*이제 Dice 함수 옮기기*/

Dice::Dice() : num(0) {}

int Dice::role(int start, int end) {
	setVal(start, end);
	return num;
}

void Dice::setVal(int start, int end) {
	num = random(start, end);
}

int Dice::random(int start, int end) {
	random_device rn;
	mt19937_64 rnd(rn()); //여기까지 시드설정
	uniform_int_distribution<> range(start, end); //분포 설정
	return range(rnd); //값 추출
}


/*HiddenCard 함수 옮기기*/
HiddenCard::HiddenCard() {}

HiddenCard::HiddenCard(int value, Person* point, vector<Land*>* l) : val(value), p(point) {
	this->l = l;
}  // Person이 주사위 굴리고 그 값을 받음

HiddenCard::HiddenCard(const HiddenCard& h) {
	cout << "히든카드 획득!" << endl;
	val = h.val;
	p = h.p;
	l = h.l;
}

int HiddenCard::retVal() const { return val; }

bool HiddenCard::exe() {
	switch (val) {
	case 1: return oddEven();
	case 2: return holdEvent(); //안열기 됨
	case 3: return feeFree();
	case 4: return gotoShuttle();
	case 5: return changeLand();
	case 6: return destroyLand(); //안부수기 됨
	case 7: return gotoGamble();
	case 8: return jailFree();
	default: return false;
	}
	return false;
}

bool HiddenCard::oddEven() {
	cout << "홀짝 아이템 획득!" << endl;
	p->getOddEven(1, 1);                    //홀짝 하나 획득
	return true;
}

bool HiddenCard::holdEvent() {
	int n, go;
	int go_arr[2] = { -1,1 };

	cout << "축제 개최를 원한다면 1, 원하지 않는다면 -1을 입력하세요: ";
	go = getNumber(go_arr, 2); // -1 또는 1 입력 예외처리 완료
	if (go == -1) return false;

	displayLandData(*l);
	cout << "축제를 열 장소를 정해주세요(축제 개최를 원하지 않는다면 -1을 입력하세요): " << endl;
	n = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
	if (n == -1) return false;


	while ((*l)[n]->owner() != p) {

		displayLandData(*l);
		cout << "잘못 입력하셨습니다!" << endl;
		cout << "축제를 열 장소를 다시 정해주세요(축제 개최를 원하지 않는다면 -1을 입력하세요): " << endl;
		n = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
		if (n == -1) return false;
	}

	if (prev_event == -1) {
		((*l)[prev_event])->offEvent();
	}
	(*l)[n]->holdEvent();                                // 이벤트 처리 해주기!!!!!!!!!!!!!!!!!!!
	prev_event = n;

	return true;
}

bool HiddenCard::feeFree() {
	cout << "통행료 면제권을 얻었어요!" << endl;
	p->fee_free();                                            //feeFree=true 만들기
	return true;
}

bool HiddenCard::gotoShuttle() {
	cout << "우주선으로 이동해요!" << endl;
	p->moveForced(SPACE_SHIP);
	return true;
}

bool HiddenCard::changeLand() {
	int my; // 내 땅 번호
	int hers; // 상대 땅 번호
	int go;
	int go_arr[2] = { -1,1 };

	cout << "교환을 원한다면 1, 원하지 않는다면 -1을 입력하세요: ";
	go = getNumber(go_arr, 2);// -1 또는 1 입력 예외처리 완료
	if (go == -1) return false;

	displayLandData(*l);
	cout << "교환할 자신의 땅을 골라주세요(교환을 원하지 않는다면 -1을 입력하세요): " << endl;
	my = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
	if (my == -1) return false;
	cout << "교환할 상대의 땅을 골라주세요(교환을 원하지 않는다면 -1을 입력하세요): " << endl;
	hers = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
	if (hers == -1) return false;


	// 땅 my가 나의 땅이고, 땅 hers가 주인이 있으며, 그 주인이 내가 아닐 때 정상 작동
	while (!((*l)[my]->owner() == p && (*l)[hers]->owner() != NULL && (*l)[hers]->owner() != p)) {        //되는거 맞나?

		displayLandData(*l);
		cout << "잘못 입력하셨습니다!" << endl;
		cout << "교환할 자신의 땅을 골라주세요(교환을 원하지 않는다면 -1을 입력하세요): " << endl;
		my = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
		if (my == -1) return false;
		cout << "교환할 상대의 땅을 골라주세요(교환을 원하지 않는다면 -1을 입력하세요): " << endl;
		hers = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
		if (hers == -1) return false;
	}

	Person* me = (*l)[my]->owner();
	Person* she = (*l)[hers]->owner();

	(*l)[my]->owner(she);
	(*l)[hers]->owner(me);

	return true;
}

bool HiddenCard::destroyLand() {
	int n;
	int go;
	int go_arr[2] = { -1,1 };

	cout << "파괴을 원한다면 1, 원하지 않는다면 -1을 입력하세요: ";
	go = getNumber(go_arr, 2);// -1 또는 1 입력 예외처리 완료
	if (go == -1) return false;

	displayLandData(*l);
	cout << "파괴할 상대의 땅을 골라주세요(파괴를 원하지 않는다면 -1을 입력하세요): " << endl;
	n = getNumber(-1, 19); // -1 ~ 19 입력 예외처리 완료 (-1은 나가기)
	if (n == -1) return false;

	// 땅 n이 주인이 있고, 그 땅이 내 땅이 아닐 때 정상 작동
	while ((*l)[n]->owner() != NULL || (*l)[n]->owner() != p) {                    //맞나?

		displayLandData(*l);
		cout << "잘못 입력하셨습니다!" << endl;
		cout << "파괴할 상대의 땅을 골라주세요(파괴를 원하지 않는다면 -1을 입력하세요): " << endl;
		cin >> n;
		if (n == -1) return false;
		if (n < START || n >= MAXLAND) return false;
	}

	(*l)[n]->destructAmenties(1); //걍 파괴하는거니까

	return false;
}

bool HiddenCard::gotoGamble() {
	cout << "미니게임으로 이동해요!" << endl;
	p->moveForced(GAMBLE);

	return true;
}

bool HiddenCard::jailFree() {
	cout << "학사경고 면제권을 얻었어요!" << endl;
	p->jail_free();                                    //p->freeJail = true;                ??

	return true;

}


/*Person 함수 옮기기*/

Person::Person(int n, char* name) 
	: no(n), money(START_MONEY), property(START_MONEY), position(START), 
	penalty(0), feeFree(false), Odd(1), Even(1), jailFree(false), bankrupt(false) {				// 홀짝 기본 개수 1개
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

Person::~Person() {
	delete[] name;
}

int Person::myPosition() const {
	return position;
}

int Person::num() const {
	return no;
}

char* Person::myName() const {
	return name;
}

int Person::myMoney() const {
	return money;
}

int Person::myProperty() const {
	return this->property;
}

int Person::retOdd() const {
	return Odd;
}

int Person::retEven() const {
	return Even;
}

void Person::useDiceItem(int n) {
	if (n == 1) { //홀수
		if (retOdd()) {
			Odd--;
		}
	}
	else if (n == 2) { //짝수
		if (retEven()) {
			Even--;
		}
	}
	else {
		cout << "아이템이 없습니다!" << endl;
		return;
	}
}

void Person::useJailFree() {
	penalty = 0;
}

void Person::Gamble(int bet) {
	money -= bet;
	this->property -= bet;
	//짱중요!
	int rndValue = dice.role(1, 24);
	int which_game = dice.role(0, 2);
	int value;
	switch (which_game) {
	case 0: value = line(bet); break;
	case 1: value = soccer(bet); break;
	case 2: value = rcp(bet); break;
	}
	cout << value << "획득!" << endl;
	money += value;
	this->property += value; //획득
}

int Person::line(int bet) {
	int stage = 0;
	int line[5] = { -1,-1,-1,-1,-1 }; // 선택한 줄 0; 썩은 줄 1
	int line_num;
	bool will_continue = true;

	int  rotten_line = dice.role(1, 4); //1에서 4가 나오게 (랜덤 선택)
	line[rotten_line] = 1; //썩은동아줄

	int remain = 4; // 남은 줄 수
	int remain_arr[4];

	cout << "줄타기를 시작합니다!" << endl;
	//cout << "rotten: " << rotten_line << endl;
	while (will_continue) {
		bool line_num_correct = false; //맞는 줄 골랐나?
		//int* remain_arr = new int[remain]; // 남은 줄 저장소(예외처리에 쓰려고)

										   // "줄타기를 시작합니다! 1 2 3 4 중 하나를 선택해주세요
		
		for (int i = 1, j = 0; i<5; i++) {
			if (line[i] != 0) {
				cout << i << " ";
				remain_arr[j++] = i;
			}
		}
		cout << "중 하나를 선택해주세요: "; //-1인 줄만 골라주세요 아님 다시 고르게 함

		line_num = getNumber(remain_arr, remain);
		while (!line_num_correct) { // 유효한 줄 번호 입력 시까지 반복
			try {
				if (!(line_num >= 1 && line_num <= 4)) { //존재하지 않는 줄 선택 (excp 1)
					throw line_num;
				}
				else if (line[line_num] == 0) { //이미 선택한적 있는 줄 선택 (excp 2)
					char temp_num = line_num;
					throw temp_num;
				}
				line_num_correct = true;
			}
			catch (int wrong_num) { //excp1
				cout << wrong_num << "입력" << endl;
				cout << "다시 입력하세요: ";
				line_num = getNumber(remain_arr, remain);
			}
			// ************* 이거 지금 되는 건가???
			catch (char num_overlap) {  //excp2
				cout << (int)num_overlap << "는 이미 선택하신 줄입니다." << endl; //?
				cout << "다시 입력하세요: ";
				line_num = getNumber(remain_arr, remain);
			}
		} //여기서 유효한 줄을 잡게 함

		if (line[line_num] == 1) {
			cout << "썩은 줄을 고르셨습니다.. 실패!" << endl; //일단 순서 바꿔놈
			return 0;
		}

		line[line_num] = 0; //선택된 줄 처리

		stage++; //0탄 완료, 1탄 ㄱ / 1->2 / 2->3 세 단계 통과시 ㅃ져나오기

		cout << "튼튼한 줄을 고르셨습니다.. 성공!" << endl;
		if (stage == 3) {
			cout << "줄타기 성공~!!" << endl;
			break;
		} //수정

		cout << "계속 하시겠습니까?(예:1 아니오:0): ";
		will_continue = (bool)getNumber(0, 1); //0 누르면 빠져나옴, 나머지는 계속

		remain--; // 남은 줄 수 -1
	}
	// 성공하여 줄타기 종료
	cout << 1.5 * stage * bet << "획득!" << endl;
	return (int)(1.5 * stage * bet);
}

int Person::soccer(int bet) {
	int stage = 0;
	bool will_continue = true;
	int kick_dir;
	int protect_dir = dice.role(1, 3); //1~3 선택

	while (will_continue) {
		bool dir_correct = false;

		cout << "페널티킥을 시작합니다!" << endl;
		cout << "좌(1) 중앙(2) 우(3) 중 하나를 선택해주세요: ";

		kick_dir = getNumber(1, 3);

		while (!dir_correct) {// 맞는 줄 번호 입력 시까지 반복
			try {
				if (!(kick_dir >= 1 && kick_dir <= 3)) {
					throw kick_dir;
				}
				dir_correct = true;
			}
			catch (int wrong_dir) {
				cout << wrong_dir << "입력" << endl;
				cout << "다시 입력하세요: ";
				kick_dir = getNumber(1, 3);
			}

		}

		if (kick_dir == protect_dir) {
			cout << "골키퍼 선방합니다.. 실패!" << endl;
			return 0;
		}
		stage++;
		cout << "골~~ 성공!" << endl;
		if (stage == 3) break;
		cout << "계속 하시겠습니까?(예:1 아니오:0): ";
		will_continue = (bool)getNumber(0, 1);
	}
	// 성공하여 줄타기 종료
	cout << (int)pow(3, stage) * bet << "획득!" << endl;
	return (int)pow(3, stage) * bet;
}

int Person::rcp(int bet) {
	int stage = 0;
	bool will_continue = true;
	int your_rsp; // rock(1)_scissor(2)_paper(3)
	int com_rsp = dice.role(1, 3); //1~3 (가위,바위,보 랜덤 결정)

	while (will_continue) {
		bool rsp_correct = false;

		cout << "가위바위보를 시작합니다!" << endl;
		cout << "가위(1) 바위(2) 보(3) 중 하나를 선택해주세요: ";

		your_rsp = getNumber(1, 3);

		while (!rsp_correct) { // 맞는 줄 번호 입력 시까지 반복
			try {
				if (!(your_rsp >= 1 && your_rsp <= 3)) {
					throw your_rsp;
				}
				rsp_correct = true;
			}
			catch (int wrong_rsp) {
				cout << wrong_rsp << "입력" << endl;
				cout << "다시 입력하세요: ";
				your_rsp = getNumber(1, 3);
			}

		}

		switch (your_rsp) {
		case 1:     cout << "플레이어: 가위!";     break;
		case 2:     cout << "플레이어: 바위!";     break;
		case 3:     cout << "플레이어: 보!";     break;
		}

		switch (com_rsp) {
		case 1:     cout << "컴퓨터: 가위!";     break;
		case 2:     cout << "컴퓨터: 바위!";     break;
		case 3:     cout << "컴퓨터: 보!";     break;
		}

		if (your_rsp % 3 + 1 == com_rsp) { //가위-바위, 바위-보, 보-가위
			cout << " 패배!" << endl;
			return 0;
		}

		else if (your_rsp == com_rsp) {
			cout << " 무승부!" << endl;
			cout << (int)pow(2, stage) * bet << "획득!" << endl;
			return (int)pow(2, stage) * bet;
		}
		stage++;
		cout << "가위바위보 성공!" << endl;
		if (stage == 3) break;
		cout << "계속 하시겠습니까?(예:1 아니오:0): ";
		will_continue = (bool)getNumber(0, 1);
	}
	// 성공하여 가위바위보 종료

	cout << (int)pow(2, stage) * bet << "획득!" << endl;
	return (int)pow(2, stage) * bet;
}

bool Person::makeHiddenCard(vector<Land*>* l) { //메인함수에서 주소로 받게 바꾸기
	//int val=dice.role(1,8);
	hid = newHidden(l);
	/*HiddenCard::HiddenCard(const HiddenCard& h) {
	cout << "히든카드 획득!" << endl;
	val = h.val;
	p = h.p;
	l = h.l;
}*/
	//cout << "복사생성자 확인하기" << endl;
	hid.exe(); //실행 되나?
	return false; //true에서 false로 고침
}

HiddenCard Person::newHidden(vector<Land*>* l) {
	HiddenCard h(dice.role(1, 8), this, l);
	return h;
}

void Person::getOddEven(int a, int b) {
	Odd += a;
	Even += b;
}

void Person::fee_free() {
	feeFree = true;
}

void Person::jail_free() {
	jailFree = true;
}

bool Person::retFeeFree() const {
	return feeFree;
}

bool Person::retJailFree() const {
	return jailFree;
}

void Person::no_fee_free() {
	feeFree = false;
}

void Person::no_jail_free() {
	jailFree = false;
}

int Person::role(bool& isDouble) {
	int dice1 = dice.role();
	int dice2 = dice.role();
	if (dice1 == dice2) isDouble = true;
	cout << dice1 << " + " << dice2 << " = ";
	return dice1 + dice2;
}

int Person::role(bool& isDouble, int parity) {
	if (penalty) {
		penalty--;
	}
	if (parity < 1 || parity > 2) return role(isDouble); //1과 2만 받음
	int dice1 = dice.role();
	int dice2 = dice.role();
	Parity what = (Parity)parity;
	if (what == even) { //짝수
		cout << "짝수" << endl;
		while ((dice1 + dice2) % 2 != 0) {
			dice1 = dice.role();
			dice2 = dice.role();
		}
	}
	else { //홀수
		while ((dice1 + dice2) % 2 == 0) {
			dice1 = dice.role();
			dice2 = dice.role();
		}
	}
	if (dice1 == dice2) isDouble = true;
	cout << dice1 << " + " << dice2 << " = ";
	return dice1 + dice2;
}

void Person::move(int num) {
	position += num;
	if (position >= MAXLAND) position -= MAXLAND;
	else if (position < 0) position += MAXLAND; //goback 염두
	if (position == JAIL) gotoJail();
}

void Person::moveForced(int num) {											// 월급 주는게 맞나 모르겠
	if (num < position) money += SALARY, this->property += SALARY;
	position = num;
}

void Person::gotoJail() {
	this->position = JAIL;
	this->penalty = 3;
}

bool Person::isJail() const {
	return position == JAIL;
}

int Person::retPenalty() const {
	return penalty;
}

void Person::buyLand(Land*& L, int n) { //현재 건물에서 부대시설 n개 추가
        //건물 n개 추가로 올림 (예외처리는 메인에서) (현재건물수에서~n까지 총합을 지불해야)
        //n==0 : 건물 없을때는 땅만삼, 건물 있을때는 아무것도 안함
        
	int cost = 0; //금액
	int num_of_ament = L->numOfAmenties(); //기존 부대시설 개수(-1,0,1,2,3)

										   // 0일때 건물 없음, 1일때 건물하나있음, 2일때 건물두개있음,
										   // 3일때 건물세개있음
										   // 4일때는 거부(landmark이미존재)(메인에서 걸러주기)
										   //

	if (n == -1) //구입X
		return;

	if (n == 0 && num_of_ament > START_AMENTIES) return; //처리 맞나?

	try {
		if (n >= LANDMARK || n < 0) throw 1; //범위 오류
		else if (num_of_ament >= 0 && n==0) throw 2; //부대시설 수가 -1이 아니면, 0 입력 안됨
		else if (num_of_ament + n >= LANDMARK) throw 3; // 부대시설수 + 입력값이 4 이상이 될 수 없음.
	}
	catch (int k) {
		if (k == 1)
			cout << "Error " << k << " : 유효하지 않은 입력입니다. 구매하지 않습니다." << endl;
		else if (k == 2)
			cout << "Error " << k << " : 0개를 구입할 수는 없습니다. 구매하지 않습니다." << endl;
		else if (k == 3)
			cout << "Error " << k << " : 랜드마크를 바로 지을 수는 없습니다. 구매하지 않습니다." << endl;
		return;
	}


	/*      입력값   결과      입력값   결과      입력값   결과      입력값   결과      입력값   결과
	num
	-1      0      cost[0]      1      [0]+[1]      2      0+1+2      3      0+1+2+3      4      예외
	0      0      예외      1      1         2      1+2         3      1+2+3
	1      0      예외      1      2         2      3
	2      0      예외      1      3
	3      0      예외      1      랜드마크


	*/

	int idx, temp;
	(num_of_ament == -1) ? (idx = 0, temp = n + 1) : (idx = 1, temp = n);
	//(num_of_ament==-1)? k=
	while (idx <= n) {
		int t = L->costBuy(num_of_ament + (1+idx)); //건물있을때 계산맞는지 확인
		//cout << t << endl;
		cost += t;
		idx++;
	}

	/*for (int i = 0; i < n; i++) {
		if(num_of_ament+n<0) continue;
		int temp = L->costBuy(num_of_ament + i);
		cout << temp << endl;
		cost += temp;
	}*/
	//cost = L->retValue();						// cost 제대로 연산안됨!!!

	if (this->money > cost) {
		//calMoney(cost, buy); //변화?
		money -= (int)(0.5 * cost);
		this->property += (int)(0.5 * cost);
		L->constAmenties(temp);
		L->owner(this);
	}
	else {
		cout << "돈이 없어서 구매 불가" << endl;
	}

} //맞는지 확인 필요

int Person::buyLandMark(Land*& L, int n) {//이건 랜드마크 확정시키는거 땅땅, 제대로 구매됐으면 1, 구매실패시 0
	if (n != 1) {
		cout << n << "은 유효하지 않은 입력입니다." << endl;
		return 0;
	}
	if (n == 1) {
		int cost = L->costBuy(LANDMARK - 1);
		if (this->money > cost) {
			money -= cost;
			this->property -= cost;
			L->constAmenties(); //부대시설 1 증가 (확인필요)
			return 1;
		}
		else {
			cout << "돈이 없어서 구매 불가" << endl;
		}
	}
	return 0;
}

void Person::sellLand(Land*& L, int n) { //0이 인수, 1이 파산 .................. 
	int cost = L->retValue();
	if (n == 0) { //인수시
		//cout << "인수!" << endl;
		cost *= 2;
		L->destructAmenties(n); //인수할때 초기화되버림 수정필요......
	}
	else if (n == 1) { //파산시
		//cout << "저런...ㅠㅠ" << endl;
		cost /= 2;
		L->destructAmenties(n);
	}
	money += cost;
	this->property += cost;
}

void Person::calMoney(int cost) { //수정함
	money += cost;
	this->property += cost;
}

void Person::calMoney(int cost, SellOrBuy A) {
	cout << "ERROR of calMoney(int ,sel)" << endl;
}

void Person::makeBankrupt() {
	bankrupt = true;
}

bool Person::isBankrupt() const {
	return bankrupt;
}

//cout 오버룅

ostream& operator<<(ostream& os, const Person* p) {
	os << p->no;
	return os;
}

ostream& operator<<(ostream& os, const Land* l) {
	os << l->name;
	return os;
}

//전역함수

void usename(vector<Person*> p) {
	cout << "닉네임을 사용하시겠습니까? 사용하려면 1, 아니면 0을 입력하세요." << endl;
	int n;
	n = getNumber(0, 1);
	if (n == 1) {
		for (int i = 0; i < 3; i++) {
			char temp[100];
			cout << p[i] << "번째 사람의 이름을 입력해주세요" << endl;
			cin >> temp;
			p[i].rename(temp);
		}
	}
	else {

	}
}

void PP(const int no, char* name, bool nickname) {
	if (nickname == true) {
		PPP(name);
	}
	else {
		PPP(no);
	}
}

template <typename T>
void PPP(T a) { //person의 이름(char*)과 번호(const int)
	cout << a;
}

void Po(Person* P1, Person* P2, Person* P3, int n) {

	cout << "(  ";
	if (P1->myPosition() != n) cout << ' ';
	else cout << P1->num();
	cout << "  ";
	if (P2->myPosition() != n) cout << ' ';
	else cout << P2->num();
	cout << "  ";
	if (P3->myPosition() != n) cout << ' ';
	else cout << P3->num();
	cout << " )";

}

void Ow(Land* L) {
	if (L->owner() == NULL) cout << ' ';
	else cout << L->owner()->num();
}

void Am(Land* L) {
	if (L->owner() == NULL) cout << ' ';
	else cout << L->numOfAmenties();
}


// 이건 각자 가지고 있는 걸로 대체!!!
void Print(vector<Person*> &P, vector<Land*> &L) {
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "|(5)         |(6)         |(7)         |(8)         |(9)         |(10)        |" << endl;
	cout << "|            | Business   | Law Build  |            | Ui-Gwan    |            |" << endl;
	cout << "|            |            |            |   Hidden   |            |    Go      |" << endl;
	cout << "|   Probation|   ("; Ow(L[6]); cout << ", "; Am(L[6]); cout << ")   |   ("; Ow(L[7]); cout << ", "; Am(L[7]); cout << ")   |    Card    |    {"; Ow(L[9]); cout << "}     |    Back!   |" << endl;
	cout << "|            |            |            |            |            |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 5); cout << "|"; Po(P[0], P[1], P[2], 6); cout << "|"; Po(P[0], P[1], P[2], 7); cout << "|"; Po(P[0], P[1], P[2], 8); cout << "|"; Po(P[0], P[1], P[2], 9); cout << "|"; Po(P[0], P[1], P[2], 10); cout << "|" << endl;
	cout << "|-----------------------------------------------------------------------------|" << endl;
	cout << "|(4)         |                                                   |(11)        |" << endl;
	cout << "| In-Gwan    |                                                   | Engineer 1 |" << endl;
	cout << "|            |      |   |  |--  | |                              |            |" << endl;
	cout << "|    {"; Ow(L[4]); cout << "}     |      |\\ -|  |    |-|   0                          |   ("; Ow(L[11]); cout << ", "; Am(L[11]); cout << ")   |" << endl;
	cout << "|            |      | \\ |  |--  | |   _|                         |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 4); cout << "|         0        | |                              |"; Po(P[0], P[1], P[2], 11); cout << "|" << endl;
	cout << "|------------|                                                   |------------|" << endl;
	cout << "|(3)         |                       |---| |   |   |             |(12)        |" << endl;
	cout << "| Nat Sci 2  |                       |   | |-  |---|             | Engineer 2 |" << endl;
	cout << "|            |                       |---| |   |   |             |            |" << endl;
	cout << "|   ("; Ow(L[3]); cout << ", "; Am(L[3]); cout << ")   |                             |    ---              |   ("; Ow(L[12]); cout << ", "; Am(L[12]); cout << ")   |" << endl;
	cout << "|            |                                 ------            |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 3); cout << "|                                   --|             |"; Po(P[0], P[1], P[2], 12); cout << "|" << endl;
	cout << "|------------|                                   |-              |------------|" << endl;
	cout << "|(2)         |                                    --             |(13)        |" << endl;
	cout << "| Nat Sci 1  |                                                   | Ye-Gwan    |" << endl;
	cout << "|            |                                                   |            |" << endl;
	cout << "|   ("; Ow(L[2]); cout << ", "; Am(L[2]); cout << ")   |                                                   |    {"; Ow(L[13]); cout << "}     |" << endl;
	cout << "|            |                                                   |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 2); cout << "|                                                   |"; Po(P[0], P[1], P[2], 13); cout << "|" << endl;
	cout << "|------------|                   Developed by                    |------------|" << endl;
	cout << "|(1)         |                                                   |(14)        |" << endl;
	cout << "|            |                        2016312559  Lee Seungwon   |            |" << endl;
	cout << "|   Hidden   |                        2016314689  Kim Jinwoo     |   Hidden   |" << endl;
	cout << "|    Card    |                        2016312107  Mun Kyeongjin  |    Card    |" << endl;
	cout << "|            |                                                   |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 1); cout << "|                                                   |"; Po(P[0], P[1], P[2], 14); cout << "|" << endl;
	cout << "|-----------------------------------------------------------------------------|" << endl;
	cout << "|(0)         |(19)        |(18)        |(17)        |(16)        |(15)        |" << endl;
	cout << "| Welcome    | Digi Lib   | 600th Bui  |            | Ji-Gwan    |            |" << endl;
	cout << "|   to       |            |            |   Gamble   |            | Shuttle    |" << endl;
	cout << "|    SKKU    |   ("; Ow(L[19]); cout << ", "; Am(L[19]); cout << ")   |   ("; Ow(L[18]); cout << ", "; Am(L[18]); cout << ")   |            |    {"; Ow(L[16]); cout << "}     |      Bus   |" << endl;
	cout << "|     Marble |            |            |            |            |            |" << endl;
	cout << "|"; Po(P[0], P[1], P[2], 0); cout << "|"; Po(P[0], P[1], P[2], 19); cout << "|"; Po(P[0], P[1], P[2], 18); cout << "|"; Po(P[0], P[1], P[2], 17); cout << "|"; Po(P[0], P[1], P[2], 16); cout << "|"; Po(P[0], P[1], P[2], 15); cout << "|" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;


}

int getNumber(int i, int j) // 연속된 숫자 범위 입력
{
	while (true)
	{
		int key;
		cin >> key;
		if (cin.fail() || key<i || key>j)
		{
			cout << "잘못 입력했어요. 다시 입력해주세요." << endl;
		}
		else
		{
			return key;
		}
		cin.clear();
		cin.ignore(256, '\n');
	}
}

int getNumber(int* arr, int size) // 내가 필요한 숫자들 중 입력
{
	while (true)
	{
		int key;
		bool valid = true; // 값이 유효한지 체크
		cin >> key;
		if (cin.fail()) {
			valid = false;
		}
		for (int i = 0; i<size; i++) {
			if (key != arr[i]) {
				valid = false;
			}
			else {
				valid = true;
				break;
			}
		}
		if (valid) {
			return key;
		}
		else {
			cout << "잘못 입력했어요. 다시 입력해주세요." << endl;
		}
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void display(vector<Person*>& p, vector<Land*>& l)
{
	cout << p[0] << "\t\t\t" << p[1] << "\t\t\t" << p[2] << endl;
	cout << "보유 금액: " << p[0]->myMoney() << "\t보유 금액: " << p[1]->myMoney() << "       보유 금액: " << p[2]->myMoney() << endl;
	cout << "총자산: " << p[0]->myProperty() << "\t\t총자산: " << p[1]->myProperty() << "        총자산: " << p[2]->myProperty() << endl;
	Print(p, l);
}

/*const int START = 0;        const int HIDDEN1 = 1;        const int HIDDEN2 = 8;        const int HIDDEN3 = 14;
const int JAIL = 5;        const int GO_BACK = 10;        const int SPACE_SHIP = 15;        const int GAMBLE = 17;

const int IN_GWAN = 4;        const int UI_GWAN = 9;        const int YE_GWAN = 13;        const int JI_GWAN = 16;

Land* : 위의 모든 곳
RealLand* :
Dorm* : 인의예지 (4, 9 13, 16)
Building* : 나머지
*/

bool isHiddenCard(int i) {
	return i == HIDDEN1 || i == HIDDEN2 || i == HIDDEN3;
}

inline bool isLand(int i) {
	return i == START || i == HIDDEN1 || i == HIDDEN2 || i == HIDDEN3 || i == JAIL || i == GO_BACK || i == SPACE_SHIP || i == GAMBLE;
}

inline bool isDorm(int i) {
	return i == IN_GWAN || i == UI_GWAN || i == YE_GWAN || i == JI_GWAN;
}

inline bool isSeoul(int i) {
	return i == 6 || i == 7 || i == 18; //서울 3개 수원 5개 엌ㅋㅋㅋ
}

int loadData(vector<Land*>& l, vector<Person*>& p) {
	ifstream fin;
	fin.open("input.txt");
	if (!fin.is_open()) {
		throw 1;
	}
	int cost[4];
	int cost2[4];

	for (int i = 0; i < MAXLAND; i++)
	{
		char name[100];
		fin.getline(name, 100);
		for (int i = 0; i < 4; i++)
			fin >> cost[i];
		for (int i = 0; i < 4; i++)
			fin >> cost2[i];
		fin.ignore();
		if (isLand(i)) {
			l[i] = new RealLand(name, cost, cost2, i, X);
			cout << i << "번째 건물… " << name << " 으로 Land 적용" << endl;
		}
		else if (isDorm(i)) {
			l[i] = new Dorm(name, cost, cost2, i, dorm);
			cout << i << "번째 건물… " << name << " 으로 RealLand 적용" << endl;
		}
		else {
			l[i] = new Building(name, cost, cost2, i);
			cout << i << "번째 건물… " << name << " 으로 Building 적용" << endl;
			if (isSeoul(i)) {
				l[i]->setMonopoly(Seoul);
			}
			else {
				l[i]->setMonopoly(Suwon);
			}
		}
	}

	if (fin.is_open()) {
		fin.close();
		cout << "Land data 정상 적용.." << endl;
	}

	return 0;
}

void displayLandData(vector<Land*>& l)
{
	for (int i = 1; i<=3; i++) {
		cout << i << "P 소유 건물 >" << endl;
		for (int j = 0; j < 19; j++) {
			if (l[j]->owner() != NULL) {
				if (l[j]->owner()->num() == i) {
					cout << j << ". " << l[j] << endl;
				}
			}

		}
	}
}

int isMonopoly(vector<Land*>& l) {
	Person *p = NULL;
	bool flag = false;

	for (int i = 0; i<19; i++) { // 수원 독점
		if (l[i]->getMonopoly() == Suwon) {
			if (p == NULL) {
				p = l[i]->owner();
				flag = true;
			}
			else {
				if (p == l[i]->owner()) continue;
				else return 0;
			}
		}
	}
	if (flag) return p->num();

	for (int i = 0; i<19; i++) { // 서울 독점
		if (l[i]->getMonopoly() == Seoul) {
			if (p == NULL) {
				p = l[i]->owner();
				flag = true;
			}
			else {
				if (p == l[i]->owner()) continue;
				else return 0;
			}
		}
	}
	if (flag) return p->num();


	for (int i = 0; i<19; i++) { // 수원 독점
		if (l[i]->getMonopoly() == dorm) {
			if (p == NULL) {
				p = l[i]->owner();
				flag = true;
			}
			else {
				if (p == l[i]->owner()) continue;
				else return 0;
			}
		}
	}
	if (flag) return p->num();

	return 0;
}