#include "modoo_oop_2.h"

//������ �� �Ȱǰ�?

//����Ʈ �Ű������� ���𿡸� �ؾ���..................�����!

int prev_event = 1;

Land::~Land(){}

RealLand::RealLand(char* name, int cost[4], int cost2[4], int num, Monopoly mon) 
	:	no(num), monopoly(mon), _owner(NULL), num_of_amenties(START_AMENTIES), 
		value(0), fee(0), is_landmark(false), event(1)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name); //�̸� ����
	for (int i = 0; i < 4; i++) {
		cost_buy[i] = cost[i], cost_fee[i] = cost2[i];
	}
} //value �ʱ�ȭ��??

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

void RealLand::setMonopoly(Monopoly mon) { //�� �ȳ������� �ɵ�?
	monopoly = mon;
}

int RealLand::numOfAmenties() const { //���̻� �ȳ������� �ɵ�?
	return num_of_amenties;
}

int RealLand::retFee() const {
	return fee; //�� ������ �ݾ�
}

void RealLand::destructAmenties(int n) { //n==0�̸� �μ��Ҷ�, n==1�̸� �Ļ��Ҷ�
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
//-----------------------------------�� �������̵��Ǵ� �Լ���


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


//value�� 0���� �ʱ�ȭ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

/*���� Dice �Լ� �ű��*/

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
	mt19937_64 rnd(rn()); //������� �õ弳��
	uniform_int_distribution<> range(start, end); //���� ����
	return range(rnd); //�� ����
}


/*HiddenCard �Լ� �ű��*/
HiddenCard::HiddenCard() {}

HiddenCard::HiddenCard(int value, Person* point, vector<Land*>* l) : val(value), p(point) {
	this->l = l;
}  // Person�� �ֻ��� ������ �� ���� ����

HiddenCard::HiddenCard(const HiddenCard& h) {
	cout << "����ī�� ȹ��!" << endl;
	val = h.val;
	p = h.p;
	l = h.l;
}

int HiddenCard::retVal() const { return val; }

bool HiddenCard::exe() {
	switch (val) {
	case 1: return oddEven();
	case 2: return holdEvent(); //�ȿ��� ��
	case 3: return feeFree();
	case 4: return gotoShuttle();
	case 5: return changeLand();
	case 6: return destroyLand(); //�Ⱥμ��� ��
	case 7: return gotoGamble();
	case 8: return jailFree();
	default: return false;
	}
	return false;
}

bool HiddenCard::oddEven() {
	cout << "Ȧ¦ ������ ȹ��!" << endl;
	p->getOddEven(1, 1);                    //Ȧ¦ �ϳ� ȹ��
	return true;
}

bool HiddenCard::holdEvent() {
	int n, go;
	int go_arr[2] = { -1,1 };

	cout << "���� ���ָ� ���Ѵٸ� 1, ������ �ʴ´ٸ� -1�� �Է��ϼ���: ";
	go = getNumber(go_arr, 2); // -1 �Ǵ� 1 �Է� ����ó�� �Ϸ�
	if (go == -1) return false;

	displayLandData(*l);
	cout << "������ �� ��Ҹ� �����ּ���(���� ���ָ� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
	n = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
	if (n == -1) return false;


	while ((*l)[n]->owner() != p) {

		displayLandData(*l);
		cout << "�߸� �Է��ϼ̽��ϴ�!" << endl;
		cout << "������ �� ��Ҹ� �ٽ� �����ּ���(���� ���ָ� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
		n = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
		if (n == -1) return false;
	}

	if (prev_event == -1) {
		((*l)[prev_event])->offEvent();
	}
	(*l)[n]->holdEvent();                                // �̺�Ʈ ó�� ���ֱ�!!!!!!!!!!!!!!!!!!!
	prev_event = n;

	return true;
}

bool HiddenCard::feeFree() {
	cout << "����� �������� ������!" << endl;
	p->fee_free();                                            //feeFree=true �����
	return true;
}

bool HiddenCard::gotoShuttle() {
	cout << "���ּ����� �̵��ؿ�!" << endl;
	p->moveForced(SPACE_SHIP);
	return true;
}

bool HiddenCard::changeLand() {
	int my; // �� �� ��ȣ
	int hers; // ��� �� ��ȣ
	int go;
	int go_arr[2] = { -1,1 };

	cout << "��ȯ�� ���Ѵٸ� 1, ������ �ʴ´ٸ� -1�� �Է��ϼ���: ";
	go = getNumber(go_arr, 2);// -1 �Ǵ� 1 �Է� ����ó�� �Ϸ�
	if (go == -1) return false;

	displayLandData(*l);
	cout << "��ȯ�� �ڽ��� ���� ����ּ���(��ȯ�� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
	my = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
	if (my == -1) return false;
	cout << "��ȯ�� ����� ���� ����ּ���(��ȯ�� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
	hers = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
	if (hers == -1) return false;


	// �� my�� ���� ���̰�, �� hers�� ������ ������, �� ������ ���� �ƴ� �� ���� �۵�
	while (!((*l)[my]->owner() == p && (*l)[hers]->owner() != NULL && (*l)[hers]->owner() != p)) {        //�Ǵ°� �³�?

		displayLandData(*l);
		cout << "�߸� �Է��ϼ̽��ϴ�!" << endl;
		cout << "��ȯ�� �ڽ��� ���� ����ּ���(��ȯ�� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
		my = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
		if (my == -1) return false;
		cout << "��ȯ�� ����� ���� ����ּ���(��ȯ�� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
		hers = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
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

	cout << "�ı��� ���Ѵٸ� 1, ������ �ʴ´ٸ� -1�� �Է��ϼ���: ";
	go = getNumber(go_arr, 2);// -1 �Ǵ� 1 �Է� ����ó�� �Ϸ�
	if (go == -1) return false;

	displayLandData(*l);
	cout << "�ı��� ����� ���� ����ּ���(�ı��� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
	n = getNumber(-1, 19); // -1 ~ 19 �Է� ����ó�� �Ϸ� (-1�� ������)
	if (n == -1) return false;

	// �� n�� ������ �ְ�, �� ���� �� ���� �ƴ� �� ���� �۵�
	while ((*l)[n]->owner() != NULL || (*l)[n]->owner() != p) {                    //�³�?

		displayLandData(*l);
		cout << "�߸� �Է��ϼ̽��ϴ�!" << endl;
		cout << "�ı��� ����� ���� ����ּ���(�ı��� ������ �ʴ´ٸ� -1�� �Է��ϼ���): " << endl;
		cin >> n;
		if (n == -1) return false;
		if (n < START || n >= MAXLAND) return false;
	}

	(*l)[n]->destructAmenties(1); //�� �ı��ϴ°Ŵϱ�

	return false;
}

bool HiddenCard::gotoGamble() {
	cout << "�̴ϰ������� �̵��ؿ�!" << endl;
	p->moveForced(GAMBLE);

	return true;
}

bool HiddenCard::jailFree() {
	cout << "�л��� �������� ������!" << endl;
	p->jail_free();                                    //p->freeJail = true;                ??

	return true;

}


/*Person �Լ� �ű��*/

Person::Person(int n, char* name) 
	: no(n), money(START_MONEY), property(START_MONEY), position(START), 
	penalty(0), feeFree(false), Odd(1), Even(1), jailFree(false), bankrupt(false) {				// Ȧ¦ �⺻ ���� 1��
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
	if (n == 1) { //Ȧ��
		if (retOdd()) {
			Odd--;
		}
	}
	else if (n == 2) { //¦��
		if (retEven()) {
			Even--;
		}
	}
	else {
		cout << "�������� �����ϴ�!" << endl;
		return;
	}
}

void Person::useJailFree() {
	penalty = 0;
}

void Person::Gamble(int bet) {
	money -= bet;
	this->property -= bet;
	//¯�߿�!
	int rndValue = dice.role(1, 24);
	int which_game = dice.role(0, 2);
	int value;
	switch (which_game) {
	case 0: value = line(bet); break;
	case 1: value = soccer(bet); break;
	case 2: value = rcp(bet); break;
	}
	cout << value << "ȹ��!" << endl;
	money += value;
	this->property += value; //ȹ��
}

int Person::line(int bet) {
	int stage = 0;
	int line[5] = { -1,-1,-1,-1,-1 }; // ������ �� 0; ���� �� 1
	int line_num;
	bool will_continue = true;

	int  rotten_line = dice.role(1, 4); //1���� 4�� ������ (���� ����)
	line[rotten_line] = 1; //����������

	int remain = 4; // ���� �� ��
	int remain_arr[4];

	cout << "��Ÿ�⸦ �����մϴ�!" << endl;
	//cout << "rotten: " << rotten_line << endl;
	while (will_continue) {
		bool line_num_correct = false; //�´� �� �����?
		//int* remain_arr = new int[remain]; // ���� �� �����(����ó���� ������)

										   // "��Ÿ�⸦ �����մϴ�! 1 2 3 4 �� �ϳ��� �������ּ���
		
		for (int i = 1, j = 0; i<5; i++) {
			if (line[i] != 0) {
				cout << i << " ";
				remain_arr[j++] = i;
			}
		}
		cout << "�� �ϳ��� �������ּ���: "; //-1�� �ٸ� ����ּ��� �ƴ� �ٽ� ���� ��

		line_num = getNumber(remain_arr, remain);
		while (!line_num_correct) { // ��ȿ�� �� ��ȣ �Է� �ñ��� �ݺ�
			try {
				if (!(line_num >= 1 && line_num <= 4)) { //�������� �ʴ� �� ���� (excp 1)
					throw line_num;
				}
				else if (line[line_num] == 0) { //�̹� �������� �ִ� �� ���� (excp 2)
					char temp_num = line_num;
					throw temp_num;
				}
				line_num_correct = true;
			}
			catch (int wrong_num) { //excp1
				cout << wrong_num << "�Է�" << endl;
				cout << "�ٽ� �Է��ϼ���: ";
				line_num = getNumber(remain_arr, remain);
			}
			// ************* �̰� ���� �Ǵ� �ǰ�???
			catch (char num_overlap) {  //excp2
				cout << (int)num_overlap << "�� �̹� �����Ͻ� ���Դϴ�." << endl; //?
				cout << "�ٽ� �Է��ϼ���: ";
				line_num = getNumber(remain_arr, remain);
			}
		} //���⼭ ��ȿ�� ���� ��� ��

		if (line[line_num] == 1) {
			cout << "���� ���� ���̽��ϴ�.. ����!" << endl; //�ϴ� ���� �ٲ��
			return 0;
		}

		line[line_num] = 0; //���õ� �� ó��

		stage++; //0ź �Ϸ�, 1ź �� / 1->2 / 2->3 �� �ܰ� ����� ����������

		cout << "ưư�� ���� ���̽��ϴ�.. ����!" << endl;
		if (stage == 3) {
			cout << "��Ÿ�� ����~!!" << endl;
			break;
		} //����

		cout << "��� �Ͻðڽ��ϱ�?(��:1 �ƴϿ�:0): ";
		will_continue = (bool)getNumber(0, 1); //0 ������ ��������, �������� ���

		remain--; // ���� �� �� -1
	}
	// �����Ͽ� ��Ÿ�� ����
	cout << 1.5 * stage * bet << "ȹ��!" << endl;
	return (int)(1.5 * stage * bet);
}

int Person::soccer(int bet) {
	int stage = 0;
	bool will_continue = true;
	int kick_dir;
	int protect_dir = dice.role(1, 3); //1~3 ����

	while (will_continue) {
		bool dir_correct = false;

		cout << "���Ƽű�� �����մϴ�!" << endl;
		cout << "��(1) �߾�(2) ��(3) �� �ϳ��� �������ּ���: ";

		kick_dir = getNumber(1, 3);

		while (!dir_correct) {// �´� �� ��ȣ �Է� �ñ��� �ݺ�
			try {
				if (!(kick_dir >= 1 && kick_dir <= 3)) {
					throw kick_dir;
				}
				dir_correct = true;
			}
			catch (int wrong_dir) {
				cout << wrong_dir << "�Է�" << endl;
				cout << "�ٽ� �Է��ϼ���: ";
				kick_dir = getNumber(1, 3);
			}

		}

		if (kick_dir == protect_dir) {
			cout << "��Ű�� �����մϴ�.. ����!" << endl;
			return 0;
		}
		stage++;
		cout << "��~~ ����!" << endl;
		if (stage == 3) break;
		cout << "��� �Ͻðڽ��ϱ�?(��:1 �ƴϿ�:0): ";
		will_continue = (bool)getNumber(0, 1);
	}
	// �����Ͽ� ��Ÿ�� ����
	cout << (int)pow(3, stage) * bet << "ȹ��!" << endl;
	return (int)pow(3, stage) * bet;
}

int Person::rcp(int bet) {
	int stage = 0;
	bool will_continue = true;
	int your_rsp; // rock(1)_scissor(2)_paper(3)
	int com_rsp = dice.role(1, 3); //1~3 (����,����,�� ���� ����)

	while (will_continue) {
		bool rsp_correct = false;

		cout << "������������ �����մϴ�!" << endl;
		cout << "����(1) ����(2) ��(3) �� �ϳ��� �������ּ���: ";

		your_rsp = getNumber(1, 3);

		while (!rsp_correct) { // �´� �� ��ȣ �Է� �ñ��� �ݺ�
			try {
				if (!(your_rsp >= 1 && your_rsp <= 3)) {
					throw your_rsp;
				}
				rsp_correct = true;
			}
			catch (int wrong_rsp) {
				cout << wrong_rsp << "�Է�" << endl;
				cout << "�ٽ� �Է��ϼ���: ";
				your_rsp = getNumber(1, 3);
			}

		}

		switch (your_rsp) {
		case 1:     cout << "�÷��̾�: ����!";     break;
		case 2:     cout << "�÷��̾�: ����!";     break;
		case 3:     cout << "�÷��̾�: ��!";     break;
		}

		switch (com_rsp) {
		case 1:     cout << "��ǻ��: ����!";     break;
		case 2:     cout << "��ǻ��: ����!";     break;
		case 3:     cout << "��ǻ��: ��!";     break;
		}

		if (your_rsp % 3 + 1 == com_rsp) { //����-����, ����-��, ��-����
			cout << " �й�!" << endl;
			return 0;
		}

		else if (your_rsp == com_rsp) {
			cout << " ���º�!" << endl;
			cout << (int)pow(2, stage) * bet << "ȹ��!" << endl;
			return (int)pow(2, stage) * bet;
		}
		stage++;
		cout << "���������� ����!" << endl;
		if (stage == 3) break;
		cout << "��� �Ͻðڽ��ϱ�?(��:1 �ƴϿ�:0): ";
		will_continue = (bool)getNumber(0, 1);
	}
	// �����Ͽ� ���������� ����

	cout << (int)pow(2, stage) * bet << "ȹ��!" << endl;
	return (int)pow(2, stage) * bet;
}

bool Person::makeHiddenCard(vector<Land*>* l) { //�����Լ����� �ּҷ� �ް� �ٲٱ�
	//int val=dice.role(1,8);
	hid = newHidden(l);
	/*HiddenCard::HiddenCard(const HiddenCard& h) {
	cout << "����ī�� ȹ��!" << endl;
	val = h.val;
	p = h.p;
	l = h.l;
}*/
	//cout << "��������� Ȯ���ϱ�" << endl;
	hid.exe(); //���� �ǳ�?
	return false; //true���� false�� ��ħ
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
	if (parity < 1 || parity > 2) return role(isDouble); //1�� 2�� ����
	int dice1 = dice.role();
	int dice2 = dice.role();
	Parity what = (Parity)parity;
	if (what == even) { //¦��
		cout << "¦��" << endl;
		while ((dice1 + dice2) % 2 != 0) {
			dice1 = dice.role();
			dice2 = dice.role();
		}
	}
	else { //Ȧ��
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
	else if (position < 0) position += MAXLAND; //goback ����
	if (position == JAIL) gotoJail();
}

void Person::moveForced(int num) {											// ���� �ִ°� �³� �𸣰�
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

void Person::buyLand(Land*& L, int n) { //���� �ǹ����� �δ�ü� n�� �߰�
        //�ǹ� n�� �߰��� �ø� (����ó���� ���ο���) (����ǹ�������~n���� ������ �����ؾ�)
        //n==0 : �ǹ� �������� ������, �ǹ� �������� �ƹ��͵� ����
        
	int cost = 0; //�ݾ�
	int num_of_ament = L->numOfAmenties(); //���� �δ�ü� ����(-1,0,1,2,3)

										   // 0�϶� �ǹ� ����, 1�϶� �ǹ��ϳ�����, 2�϶� �ǹ��ΰ�����,
										   // 3�϶� �ǹ���������
										   // 4�϶��� �ź�(landmark�̹�����)(���ο��� �ɷ��ֱ�)
										   //

	if (n == -1) //����X
		return;

	if (n == 0 && num_of_ament > START_AMENTIES) return; //ó�� �³�?

	try {
		if (n >= LANDMARK || n < 0) throw 1; //���� ����
		else if (num_of_ament >= 0 && n==0) throw 2; //�δ�ü� ���� -1�� �ƴϸ�, 0 �Է� �ȵ�
		else if (num_of_ament + n >= LANDMARK) throw 3; // �δ�ü��� + �Է°��� 4 �̻��� �� �� ����.
	}
	catch (int k) {
		if (k == 1)
			cout << "Error " << k << " : ��ȿ���� ���� �Է��Դϴ�. �������� �ʽ��ϴ�." << endl;
		else if (k == 2)
			cout << "Error " << k << " : 0���� ������ ���� �����ϴ�. �������� �ʽ��ϴ�." << endl;
		else if (k == 3)
			cout << "Error " << k << " : ���帶ũ�� �ٷ� ���� ���� �����ϴ�. �������� �ʽ��ϴ�." << endl;
		return;
	}


	/*      �Է°�   ���      �Է°�   ���      �Է°�   ���      �Է°�   ���      �Է°�   ���
	num
	-1      0      cost[0]      1      [0]+[1]      2      0+1+2      3      0+1+2+3      4      ����
	0      0      ����      1      1         2      1+2         3      1+2+3
	1      0      ����      1      2         2      3
	2      0      ����      1      3
	3      0      ����      1      ���帶ũ


	*/

	int idx, temp;
	(num_of_ament == -1) ? (idx = 0, temp = n + 1) : (idx = 1, temp = n);
	//(num_of_ament==-1)? k=
	while (idx <= n) {
		int t = L->costBuy(num_of_ament + (1+idx)); //�ǹ������� ���´��� Ȯ��
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
	//cost = L->retValue();						// cost ����� ����ȵ�!!!

	if (this->money > cost) {
		//calMoney(cost, buy); //��ȭ?
		money -= (int)(0.5 * cost);
		this->property += (int)(0.5 * cost);
		L->constAmenties(temp);
		L->owner(this);
	}
	else {
		cout << "���� ��� ���� �Ұ�" << endl;
	}

} //�´��� Ȯ�� �ʿ�

int Person::buyLandMark(Land*& L, int n) {//�̰� ���帶ũ Ȯ����Ű�°� ����, ����� ���ŵ����� 1, ���Ž��н� 0
	if (n != 1) {
		cout << n << "�� ��ȿ���� ���� �Է��Դϴ�." << endl;
		return 0;
	}
	if (n == 1) {
		int cost = L->costBuy(LANDMARK - 1);
		if (this->money > cost) {
			money -= cost;
			this->property -= cost;
			L->constAmenties(); //�δ�ü� 1 ���� (Ȯ���ʿ�)
			return 1;
		}
		else {
			cout << "���� ��� ���� �Ұ�" << endl;
		}
	}
	return 0;
}

void Person::sellLand(Land*& L, int n) { //0�� �μ�, 1�� �Ļ� .................. 
	int cost = L->retValue();
	if (n == 0) { //�μ���
		//cout << "�μ�!" << endl;
		cost *= 2;
		L->destructAmenties(n); //�μ��Ҷ� �ʱ�ȭ�ǹ��� �����ʿ�......
	}
	else if (n == 1) { //�Ļ��
		//cout << "����...�Ф�" << endl;
		cost /= 2;
		L->destructAmenties(n);
	}
	money += cost;
	this->property += cost;
}

void Person::calMoney(int cost) { //������
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

//cout ������

ostream& operator<<(ostream& os, const Person* p) {
	os << p->no;
	return os;
}

ostream& operator<<(ostream& os, const Land* l) {
	os << l->name;
	return os;
}

//�����Լ�

void usename(vector<Person*> p) {
	cout << "�г����� ����Ͻðڽ��ϱ�? ����Ϸ��� 1, �ƴϸ� 0�� �Է��ϼ���." << endl;
	int n;
	n = getNumber(0, 1);
	if (n == 1) {
		for (int i = 0; i < 3; i++) {
			char temp[100];
			cout << p[i] << "��° ����� �̸��� �Է����ּ���" << endl;
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
void PPP(T a) { //person�� �̸�(char*)�� ��ȣ(const int)
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


// �̰� ���� ������ �ִ� �ɷ� ��ü!!!
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

int getNumber(int i, int j) // ���ӵ� ���� ���� �Է�
{
	while (true)
	{
		int key;
		cin >> key;
		if (cin.fail() || key<i || key>j)
		{
			cout << "�߸� �Է��߾��. �ٽ� �Է����ּ���." << endl;
		}
		else
		{
			return key;
		}
		cin.clear();
		cin.ignore(256, '\n');
	}
}

int getNumber(int* arr, int size) // ���� �ʿ��� ���ڵ� �� �Է�
{
	while (true)
	{
		int key;
		bool valid = true; // ���� ��ȿ���� üũ
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
			cout << "�߸� �Է��߾��. �ٽ� �Է����ּ���." << endl;
		}
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void display(vector<Person*>& p, vector<Land*>& l)
{
	cout << p[0] << "\t\t\t" << p[1] << "\t\t\t" << p[2] << endl;
	cout << "���� �ݾ�: " << p[0]->myMoney() << "\t���� �ݾ�: " << p[1]->myMoney() << "       ���� �ݾ�: " << p[2]->myMoney() << endl;
	cout << "���ڻ�: " << p[0]->myProperty() << "\t\t���ڻ�: " << p[1]->myProperty() << "        ���ڻ�: " << p[2]->myProperty() << endl;
	Print(p, l);
}

/*const int START = 0;        const int HIDDEN1 = 1;        const int HIDDEN2 = 8;        const int HIDDEN3 = 14;
const int JAIL = 5;        const int GO_BACK = 10;        const int SPACE_SHIP = 15;        const int GAMBLE = 17;

const int IN_GWAN = 4;        const int UI_GWAN = 9;        const int YE_GWAN = 13;        const int JI_GWAN = 16;

Land* : ���� ��� ��
RealLand* :
Dorm* : ���ǿ��� (4, 9 13, 16)
Building* : ������
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
	return i == 6 || i == 7 || i == 18; //���� 3�� ���� 5�� ��������
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
			cout << i << "��° �ǹ��� " << name << " ���� Land ����" << endl;
		}
		else if (isDorm(i)) {
			l[i] = new Dorm(name, cost, cost2, i, dorm);
			cout << i << "��° �ǹ��� " << name << " ���� RealLand ����" << endl;
		}
		else {
			l[i] = new Building(name, cost, cost2, i);
			cout << i << "��° �ǹ��� " << name << " ���� Building ����" << endl;
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
		cout << "Land data ���� ����.." << endl;
	}

	return 0;
}

void displayLandData(vector<Land*>& l)
{
	for (int i = 1; i<=3; i++) {
		cout << i << "P ���� �ǹ� >" << endl;
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

	for (int i = 0; i<19; i++) { // ���� ����
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

	for (int i = 0; i<19; i++) { // ���� ����
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


	for (int i = 0; i<19; i++) { // ���� ����
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