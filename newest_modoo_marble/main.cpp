#include "modoo_oop_2.h"

bool nickname;

int main()
{
	vector<Land*> l(MAXLAND);
	vector<Person*> p(PERSON_NUM);

	try {
		loadData(l, p);
	}
	catch (...) {
		cout << "�����͸� ���������� �ҷ��� �� �����ϴ�. ������ �����մϴ�." << endl;
		return 0;
	}

	/*int order[3];

	srand(int(time(NULL)));
	int count = 0;
	while (count < 3)
	{
	int is_checked = 0;
	int num = rand() % 3 + 1;
	for (int i = 0; i < 3; i++)
	{
	if (num == order[i])
	{
	is_checked = 1;
	}
	}
	if (is_checked == 0)
	{
	order[count] = num;
	count++;
	}
	}*/

	for (int i = 0; i < PERSON_NUM; i++)
	{
		p[i] = new Person(i + 1/*order[i]*/, "");
	}

	cout << "������ ����" << endl;
	cout << "�� 2017. Lee Seung-won, Kin Jin-woo, Mun Kyung-jin All rights reserved." << endl;
	cout << endl;
	cout << "�г����� ����Ͻðڽ��ϱ�? �⺻ �������� 1, 2, 3�Դϴ�. ����Ϸ��� 1, ������� �������� 0�� �Է��ϼ���." << endl;
	nickname = getNumber(0, 1);

	if (nickname) {
		char temp[100];
		cout << "�г����� �Է��ϼ���." << endl;
		cout << "1: " << endl;
		cin >> temp;
		cin.ignore();
		p[0]->rename(temp);
		cout << "2: " << endl;
		cin >> temp;
		cin.ignore();
		p[1]->rename(temp);
		cout << "3: " << endl;
		cin >> temp;
		cin.ignore();
		p[2]->rename(temp);
	}

	/*display(p, l);
	cout << "�ֻ��� ���� ������ ���ҰԿ�." << endl;
	cout << endl;
	cout << "ù��° ����: " << p[0] << endl;
	cout << "�ι�° ����: " << p[1] << endl;
	cout << "����° ����: " << p[2] << endl;
	cout << endl;*/

	bool is_double;
	int turn = 20; //20���� ��ġ��
	int alive = 3;

	while (turn >= 1 && isMonopoly(l) == 0 && alive>1)
	{
		for (int i = 0; i < PERSON_NUM; i++)
		{
			if (isMonopoly(l) > 0)
			{
				break;
			}
			if (alive == 1)
			{
				break;
			}
			if (p[i]->isBankrupt())
			{
				continue;
			}

			int double_count = 0;
			do
			{
				display(p, l);
				is_double = false;
				int key;
				PP(p[i]->num(), p[i]->myName(), nickname);
				cout << "���� ���̿���." << endl;
				//cout << p[i] << "���� ���̿���." << endl;
				cout << turn << "�� ���Ҿ��!" << endl;

				if (p[i]->retPenalty() > 0)
				{
					cout << "���� �л��� ĭ�� �־��. ���ݺ��� " << p[i]->retPenalty() << "�� ������ ������ �� �����!" << endl;

					if (p[i]->retJailFree())
					{
						cout << "�л��� �������� ����ؼ� Ż���� �� �־��. ����Ϸ��� 1, ������� �������� 2�� �Է��ϼ���." << endl;
						key = getNumber(1, 2);
						if (key == 1)
						{
							cout << "�л��� �������� ����߾��." << endl;
							p[i]->no_jail_free();
							p[i]->useJailFree();
						}
						else
						{
							cout << "�ֻ����� ���� ������ ������ Ż���� �� �־��." << endl;
							cout << "�ֻ����� �������� 3�� �Է��ϼ���." << endl;
							key = getNumber(3, 3);
							cout << "�ֻ����� ������ ���̿���." << endl;
							int dice_value = p[i]->role(is_double, key);
							cout << dice_value << "! ";
							if (is_double)
							{
								cout << "����!" << endl;
								cout << "����!" << endl;
								is_double = false;
							}
							else
							{
								cout << "����!" << endl;
								break;
							}
						}
					}
					else
					{
						cout << "�ֻ����� ���� ������ ������ Ż���� �� �־��." << endl;
						cout << "�ֻ����� �������� 3�� �Է��ϼ���." << endl;
						key = getNumber(3, 3);
						cout << "�ֻ����� ������ ���̿���." << endl;
						int dice_value = p[i]->role(is_double, key);
						cout << dice_value << "! ";
						if (is_double)
						{
							cout << "����!" << endl;
							cout << "����!" << endl;
							is_double = false;
						}
						else
						{
							cout << "����!" << endl;
							break;
						}
					}
				}

				if (p[i]->retOdd() > 0 && p[i]->retEven() > 0)
				{
					cout << "���� Ȧ�� ī�带 " << p[i]->retOdd() << "��, ¦�� ī�带 " << p[i]->retEven() << "�� ������ �־��." << endl;
					cout << "Ȧ�� ī�带 ����Ϸ��� 1, ¦�� ī�带 ����Ϸ��� 2, ī�带 ������� �������� 3�� �Է��ϼ���." << endl;
					key = getNumber(1, 3);
					if (key == 1)
					{
						p[i]->useDiceItem(1);
					}
					else if (key == 2)
					{
						p[i]->useDiceItem(2);
					}
				}
				else if (p[i]->retOdd() > 0)
				{
					cout << "���� Ȧ�� ī�带 " << p[i]->retOdd() << "�� ������ �־��." << endl;
					cout << "Ȧ�� ī�带 ����Ϸ��� 1, ī�带 ������� �������� 3�� �Է��ϼ���." << endl;
					int arr[2] = { 1, 3 };
					key = getNumber(arr, 2);
					if (key == 1)
					{
						p[i]->useDiceItem(1);
					}
				}
				else if (p[i]->retEven() > 0)
				{
					cout << "���� ¦�� ī�带 " << p[i]->retEven() << "�� ������ �־��." << endl;
					cout << "¦�� ī�带 ����Ϸ��� 2, ī�带 ������� �������� 3�� �Է��ϼ���." << endl;
					key = getNumber(2, 3);
					if (key == 2)
					{
						p[i]->useDiceItem(2);
					}
				}
				else
				{
					cout << "�ֻ����� �������� 3�� �Է��ϼ���." << endl;
					key = getNumber(3, 3);
				}

				cout << "�ֻ����� ������ ���̿���." << endl;
				int dice_value = p[i]->role(is_double, key);
				cout << dice_value << "! ";
				if (is_double)
				{
					cout << "����!";
					double_count++;
				}

				cout << endl;

				if (double_count == 3)
				{
					p[i]->gotoJail();
					cout << "�л��� ĭ�� �����߾��. ���ݺ��� 3�� ������ ������ �� �����!" << endl;

					break;
				}

				p[i]->move(dice_value);
				display(p, l);

				bool flag = true;
				while (flag) {
					flag = false;
					if (isHiddenCard(p[i]->myPosition())) {
						cout << "����ī�带 �̾ƺ��ƿ�!" << endl;
						flag = p[i]->makeHiddenCard(&l);
					}
					if (p[i]->myPosition() == GO_BACK)
					{
						cout << "�Ųٷ� ���ϴ�~ �� ��������!" << endl;
						cout << "�ֻ����� �������� 3�� �Է��ϼ���." << endl;
						key = getNumber(3, 3);
						cout << "�ֻ����� ������ ���̿���." << endl;
						dice_value = p[i]->role(is_double, key);
						cout << dice_value << "��ŭ �ڷ� �̵��մϴ�. " << endl;
						p[i]->move(dice_value *= -1);
						display(p, l);
						flag = true;
					}
					if (p[i]->myPosition() == SPACE_SHIP) {
						cout << "��Ʋ������ �̿��� �� �־��." << endl;
						cout << "�̵��ϰ� ���� ���� ��ȣ�� �Է����ּ���." << endl;
						key = getNumber(0, 19);
						p[i]->moveForced(key);
						display(p, l);
						flag = true;
					}

				}

				if (p[i]->myPosition() == START)
				{
					cout << "������� �����߾��." << endl;
					bool is_owned = false;
					for (int j = 0; j < 19; j++)
					{
						if (l[j]->owner() == p[i] && !isDorm(j))
						{
							is_owned = true;
							break;
						}
					}

					if (is_owned)
					{
						int temp;
						cout << "�߰� �Ǽ��� ���ϴ� ������ ��ȣ�� �Է��ϼ���." << endl;
						while (true)
						{
							temp = getNumber(0, 19);
							if (l[temp]->owner() == p[i] && !isDorm(temp) && !l[temp]->isLandmark())
							{
								break;
							}
							else
							{
								cout << "������ �ƴ� ������ �����߾��. �ٽ� �Է��ϼ���." << endl;
							}
						}

						if (l[temp]->numOfAmenties() == 3)
						{
							cout << "���帶ũ�� �����ұ��? ���帶ũ�� �����Ϸ��� 1, �Ǽ����� �������� 2�� �Է��ϼ���. " << endl;
							cout << "���帶ũ ���Ժ���� " << l[temp]->costBuy(3) << "�̿���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								if (p[i]->myMoney() >= l[temp]->costBuy(3))
								{
									p[i]->buyLandMark(l[temp], key);
									cout << "���帶ũ �Ǽ�!" << endl;
								}
								else
								{
									cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
								}
							}
						}
						else
						{
							if (l[temp]->numOfAmenties() == 0)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~3)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �����Ǹ� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[temp]->costBuy(1) << endl;
								cout << "�δ�ü� 2��: " << l[temp]->costBuy(1) + l[temp]->costBuy(2) << endl;
								cout << "�δ�ü� 3��: " << l[temp]->costBuy(1) + l[temp]->costBuy(2) + l[temp]->costBuy(3) << endl;
							}
							else if (l[temp]->numOfAmenties() == 1)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~2)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �δ�ü��� 1�� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[temp]->costBuy(2) << endl;
								cout << "�δ�ü� 2��: " << l[temp]->costBuy(2) + l[temp]->costBuy(3) << endl;
							}
							else if (l[temp]->numOfAmenties() == 2)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �δ�ü��� 2�� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[temp]->costBuy(3) << endl;
							}
							key = getNumber(0, 3);
							if (key >= 1)
							{
								int costvalue = 0;
								int amenties = l[temp]->numOfAmenties();
								for (int j = 1; j <= key; j++)
								{
									costvalue += l[temp]->costBuy(amenties + j);
								}

								if (p[i]->myMoney() >= costvalue)
								{
									p[i]->buyLand(l[temp], key);
									cout << l[temp] << "(��)�� �����߾��!" << endl;
								}
								else
								{
									cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
								}
							}
						}
					}
					else
					{
						cout << "������ �ִ� ������ ��� �߰� �Ǽ��� �� �� �����." << endl;
					}
				}
				if (p[i]->myPosition() == JAIL)
				{
					cout << "�л��� ĭ�� �����߾��. ���ݺ��� 3�� ������ ������ �� �����!" << endl;
				}

				if (p[i]->myPosition() == GAMBLE)
				{
					cout << "Gamble ĭ�� �����߾��. �̴ϰ����� �Ϸ��� 1, ���� �������� 2�� �Է��ϼ���." << endl;
					cout << "�̴ϰ��� ����� 1000�̿���." << endl;
					key = getNumber(1, 2);
					if (key == 1)
					{
						p[i]->Gamble(COST);
					}
				}

				if (isDorm(p[i]->myPosition()))
				{
					cout << l[p[i]->myPosition()] << "�� �����߾��." << endl;
					if (l[p[i]->myPosition()]->owner() == NULL)
					{
						cout << "����縦 �����ұ��? �����Ϸ��� 0, �������� �������� -1�� �Է��ϼ���." << endl;
						cout << "���� ����� " << l[p[i]->myPosition()]->costBuy() << "�̿���." << endl;
						key = getNumber(-1, 0);
						if (key == 0)
						{
							if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy())
							{
								p[i]->buyLand(l[p[i]->myPosition()], 0);
								cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
							}
							else
							{
								cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
							}
						}
					}
					else if (l[p[i]->myPosition()]->owner() != p[i])
					{
						int fee = l[p[i]->myPosition()]->costFee(0);
						cout << l[p[i]->myPosition()] << "�� ���� ������ ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(��)����." << endl;
						cout << "������ " << fee << "�̿���. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "����� �������� ����ؼ� ����Ḧ �������� �� �־��. ����� �������� ����Ϸ��� 1, ������� �������� 2�� �Է��ϼ���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "����Ḧ �����޾Ҿ��!" << endl;
							}
						}
						else
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "����Ḧ �����߾��." << endl;
								p[i]->calMoney(-1 * fee);
								l[p[i]->myPosition()]->owner()->calMoney(fee);
							}
							else
							{
								int sum = 0;
								for (int j = 0; j < 20; j++)
								{
									if (l[j]->owner() == p[i])
									{
										if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
										{
											sum += l[j]->costBuy();
										}
										else
										{
											sum += l[j]->retValue();
										}
									}
								}

								if (p[i]->myMoney() + sum*0.5 < fee)
								{
									PP(p[i]->num(), p[i]->myName(), nickname);
									cout << "���� �Ļ��߽��ϴ�." << endl;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											p[i]->sellLand(l[j], 1);
										}
									}
									p[i]->makeBankrupt();
									alive--;
								}
								else
								{
									while (p[i]->myMoney() < fee)
									{
										cout << "���� �ݾ��� �����ؿ�. �Ű��� ���ϴ� ������ ��ȣ�� �����ϼ���." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "������ �ƴ� ���� �����߾��. �ٽ� �Է��ϼ���." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(��)�� �Ű��߾��." << endl;
									}
								}
							}
						}
					}
				}

				if (l[p[i]->myPosition()]->costBuy(0) <= 0 || p[i]->myPosition() == IN_GWAN || p[i]->myPosition() == UI_GWAN || p[i]->myPosition() == YE_GWAN || p[i]->myPosition() == JI_GWAN)
				{
					break;
				}

				cout << l[p[i]->myPosition()] << "�� �����߾��." << endl;

				if (!l[p[i]->myPosition()]->isLandmark())
				{
					if (l[p[i]->myPosition()]->owner() == NULL)
					{
						cout << "������ �����ұ��? ������ �δ�ü��� ���� �Է��ϼ���(1~3). ������ �����Ϸ��� 0, �������� �������� -1�� �Է��ϼ���." << endl;
						cout << endl;
						cout << "������: " << l[p[i]->myPosition()]->costBuy(0) << endl;
						cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) << endl;
						cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
						cout << "�δ�ü� 3��: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
						key = getNumber(-1, 3);
						if (key >= 0)
						{
							int costvalue = 0;
							int amenties = l[p[i]->myPosition()]->numOfAmenties();
							for (int j = 1; j <= key; j++)
							{
								costvalue += l[p[i]->myPosition()]->costBuy(amenties + j);
							}

							if (p[i]->myMoney() >= costvalue)
							{
								p[i]->buyLand(l[p[i]->myPosition()], key);
								cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
							}
							else
							{
								cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
							}
						}
					}
					else if (l[p[i]->myPosition()]->owner() == p[i])
					{
						if (l[p[i]->myPosition()]->numOfAmenties() == 3)
						{
							cout << "���帶ũ�� �����ұ��? ���帶ũ�� �����Ϸ��� 1, �������� �������� 2�� �Է��ϼ���. " << endl;
							cout << "���帶ũ ���Ժ���� " << l[p[i]->myPosition()]->costBuy(3) << "�̿���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy(3))
								{
									p[i]->buyLandMark(l[p[i]->myPosition()], key);
									cout << "���帶ũ �Ǽ�!" << endl;
								}
								else
								{
									cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
								}
							}
						}
						else
						{
							if (l[p[i]->myPosition()]->numOfAmenties() == 0)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~3)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �����Ǹ� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(1) << endl;
								cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
								cout << "�δ�ü� 3��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
							}
							else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~2)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �δ�ü��� 1�� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(2) << endl;
								cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
							}
							else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
							{
								cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
								cout << "���� �δ�ü��� 2�� ������ �־��." << endl;
								cout << endl;
								cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(3) << endl;
							}
							key = getNumber(0, 3);
							if (key >= 1)
							{
								int costvalue = 0;
								int amenties = l[p[i]->myPosition()]->numOfAmenties();
								for (int j = 1; j <= key; j++)
								{
									costvalue += l[p[i]->myPosition()]->costBuy(amenties + j);
								}

								if (p[i]->myMoney() >= costvalue)
								{
									p[i]->buyLand(l[p[i]->myPosition()], key);
									cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
								}
								else
								{
									cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
								}
							}
						}
					}
					else
					{
						int fee = l[p[i]->myPosition()]->costFee(l[p[i]->myPosition()]->numOfAmenties());
						int take_over = l[p[i]->myPosition()]->retValue() * 2;
						cout << l[p[i]->myPosition()] << "�� ���� ������ ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(��)����." << endl;
						cout << "������ " << fee << "(��)����. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "����� �������� ����ؼ� ����Ḧ �������� �� �־��. ����� �������� ����Ϸ��� 1, ������� �������� 2�� �Է��ϼ���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "����Ḧ �����޾Ҿ��!" << endl;
							}
							else
							{
								if (p[i]->myMoney() >= fee)
								{
									cout << "����Ḧ �����߾��." << endl;
									p[i]->calMoney(-1 * fee);
									l[p[i]->myPosition()]->owner()->calMoney(fee);

									cout << "�ǹ��� �μ��ұ��? �μ��� ���Ͻø� 1, ������ �����ø� 2�� �Է��ϼ���. �μ� ����� " << take_over << "�̿���. " << endl;
									key = getNumber(1, 2);
									if (key == 1)
									{
										cout << "���ø� �μ��߾��! �μ� ����: ";
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << " -> ";

										//�μ�: �Ǹ�
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << endl;

										//�μ�: ����
										p[i]->buyLand(l[p[i]->myPosition()], 0);

										if (l[p[i]->myPosition()]->numOfAmenties() == 3)
										{
											cout << "���帶ũ�� �����ұ��? ���帶ũ�� �����Ϸ��� 1, �������� �������� 2�� �Է��ϼ���. " << endl;
											cout << "���帶ũ ���Ժ���� " << l[p[i]->myPosition()]->costBuy(3) << "(��)����." << endl;
											key = getNumber(1, 2);
											if (key == 1)
											{
												if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy(3))
												{
													p[i]->buyLandMark(l[p[i]->myPosition()], key);
													cout << "���帶ũ �Ǽ�!" << endl;
												}
												else
												{
													cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
												}
											}
										}
										else
										{
											if (l[p[i]->myPosition()]->numOfAmenties() == 0)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~3)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �����Ǹ� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(1) << endl;
												cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "�δ�ü� 3��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~2)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �δ�ü��� 1�� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �δ�ü��� 2�� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											key = getNumber(0, 3);
											if (key >= 1)
											{
												int costvalue = 0;
												int amenties = l[p[i]->myPosition()]->numOfAmenties();
												for (int j = 1; j <= key; j++)
												{
													costvalue += l[p[i]->myPosition()]->costBuy(amenties + j);
												}

												if (p[i]->myMoney() >= costvalue)
												{
													p[i]->buyLand(l[p[i]->myPosition()], key);
													cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
												}
												else
												{
													cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
												}
											}
										}
									}
								}
								else
								{
									int sum = 0;
									for (int j = 0; j < 20; j++)
									{
										if (l[j]->owner() == p[i])
										{
											if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
											{
												sum += l[j]->costBuy();
											}
											else
											{
												sum += l[j]->retValue();
											}
										}
									}

									if (p[i]->myMoney() + sum*0.5 < fee)
									{
										PP(p[i]->num(), p[i]->myName(), nickname);
										cout << "���� �Ļ��߽��ϴ�." << endl;
										for (int j = 0; j < 19; j++)
										{
											if (l[j]->owner() == p[i])
											{
												p[i]->sellLand(l[j], 1);
											}
										}
										p[i]->makeBankrupt();
										alive--;
									}
									else
									{
										while (p[i]->myMoney() < fee)
										{
											cout << "�Ű��� ���ϴ� ������ ��ȣ�� �����ϼ���." << endl;
											while (true)
											{
												key = getNumber(0, 19);
												if (l[key]->owner() == p[i])
												{
													break;
												}
												else
												{
													cout << "������ �ƴ� ���� �����߾��. �ٽ� �Է��ϼ���." << endl;
												}
											}
											p[i]->sellLand(l[key], 1);
											cout << l[key] << "(��)�� �Ű��߾��." << endl;
										}
									}
								}
							}
						}
						else
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "����Ḧ �����߾��." << endl;
								p[i]->calMoney(-1 * fee);
								l[p[i]->myPosition()]->owner()->calMoney(fee);

								cout << "�ǹ��� �μ��ұ��? �μ��� ���Ͻø� 1, ������ �����ø� 2�� �Է��ϼ���. �μ� ����� " << take_over << "�̿���. " << endl;
								key = getNumber(1, 2);
								if (key == 1)
								{
									cout << "���ø� �μ��߾��! �μ� ����: ";
									PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
									cout << " -> ";

									//�μ�: �Ǹ�
									l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

									l[p[i]->myPosition()]->owner(p[i]);
									PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
									cout << endl;

									//�μ�: ����
									p[i]->buyLand(l[p[i]->myPosition()], 0);

									if (l[p[i]->myPosition()]->numOfAmenties() == 3)
									{
										cout << "���帶ũ�� �����ұ��? ���帶ũ�� �����Ϸ��� 1, �������� �������� 2�� �Է��ϼ���. " << endl;
										cout << "���帶ũ ���Ժ���� " << l[p[i]->myPosition()]->costBuy(3) << "�̿���." << endl;
										key = getNumber(1, 2);
										if (key == 1)
										{
											cout << "���帶ũ �Ǽ�!" << endl;
											p[i]->buyLandMark(l[p[i]->myPosition()], key);
										}
									}
									else
									{
										if (l[p[i]->myPosition()]->numOfAmenties() == 0)
										{
											cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~3)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
											cout << "���� �����Ǹ� ������ �־��." << endl;
											cout << endl;
											cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(1) << endl;
											cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
											cout << "�δ�ü� 3��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
										}
										else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
										{
											cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~2)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
											cout << "���� �δ�ü��� 1�� ������ �־��." << endl;
											cout << endl;
											cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(2) << endl;
											cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
										}
										else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
										{
											cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
											cout << "���� �δ�ü��� 2�� ������ �־��." << endl;
											cout << endl;
											cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(3) << endl;
										}
										key = getNumber(0, 3);
										if (key >= 1)
										{
											int costvalue = 0;
											int amenties = l[p[i]->myPosition()]->numOfAmenties();
											for (int j = 1; j <= key; j++)
											{
												costvalue += l[p[i]->myPosition()]->costBuy(amenties + j);
											}

											if (p[i]->myMoney() >= costvalue)
											{
												p[i]->buyLand(l[p[i]->myPosition()], key);
												cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
											}
											else
											{
												cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
											}
										}
									}
								}
							}
							else
							{
								int sum = 0;
								for (int j = 0; j < 20; j++)
								{
									if (l[j]->owner() == p[i])
									{
										if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
										{
											sum += l[j]->costBuy();
										}
										else
										{
											sum += l[j]->retValue();
										}
									}
								}

								if (p[i]->myMoney() + sum*0.5 < fee)
								{
									PP(p[i]->num(), p[i]->myName(), nickname);
									cout << "���� �Ļ��߽��ϴ�." << endl;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											p[i]->sellLand(l[j], 1);
										}
									}
									p[i]->makeBankrupt();
									alive--;
								}
								else
								{
									while (p[i]->myMoney() < fee)
									{
										cout << "���� �ݾ��� �����ؿ�. �Ű��� ���ϴ� ������ ��ȣ�� �����ϼ���." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "������ �ƴ� ���� �����߾��. �ٽ� �Է��ϼ���." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(��)�� �Ű��߾��." << endl;
									}
								}
							}
						}
					}
				}
				else
				{
					if (l[p[i]->myPosition()]->owner() != p[i])
					{
						int fee = 0;
						for (int j = 0; j <= 3; j++)
						{
							fee += l[p[i]->myPosition()]->costFee(j);
						}
						int take_over = l[p[i]->myPosition()]->retValue() * 2;
						cout << l[p[i]->myPosition()] << "�� ���� ������ ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(��)����." << endl;
						cout << "������ " << fee << "�̿���. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "����� �������� ����ؼ� ����Ḧ �������� �� �־��. ����� �������� ����Ϸ��� 1, ������� �������� 2�� �Է��ϼ���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "����Ḧ �����޾Ҿ��!" << endl;
							}
							else
							{
								if (p[i]->myMoney() >= fee)
								{
									cout << "����Ḧ �����߾��." << endl;
									p[i]->calMoney(-1 * fee);
									l[p[i]->myPosition()]->owner()->calMoney(fee);

									/*cout << "�ǹ��� �μ��ұ��? �μ��� ���Ͻø� 1, ������ �����ø� 2�� �Է��ϼ���. �μ� ����� " << take_over << "�̿���. " << endl;
									key = getNumber(1, 2);
									if (key == 1)
									{
										cout << "���ø� �μ��߾��! �μ� ����: ";
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << " -> ";

										//�μ�: �Ǹ�
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << endl;

										//�μ�: ����
										p[i]->buyLand(l[p[i]->myPosition()], 0);

										if (l[p[i]->myPosition()]->numOfAmenties() == 3)
										{
											cout << "���帶ũ�� �Ǽ��ұ��? ���帶ũ�� �Ǽ��Ϸ��� 1, �Ǽ����� �������� 2�� �Է��ϼ���. " << endl;
											cout << "���帶ũ �Ǽ������ " << l[p[i]->myPosition()]->costBuy(3) << "�̿���." << endl;
											key = getNumber(1, 2);
											if (key == 1)
											{
												cout << "���帶ũ �Ǽ�!" << endl;
												p[i]->buyLandMark(l[p[i]->myPosition()], key);
											}
										}
										else
										{
											if (l[p[i]->myPosition()]->numOfAmenties() == 0)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~3)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �����Ǹ� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(1) << endl;
												cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "�δ�ü� 3��: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1~2)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �δ�ü��� 1�� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "�δ�ü� 2��: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
											{
												cout << "�δ�ü��� �����ұ��? ������ �δ�ü��� ��(1)�� �Է��ϼ���. �������� �������� 0�� �Է��ϼ���." << endl;
												cout << "���� �δ�ü��� 2�� ������ �־��." << endl;
												cout << endl;
												cout << "�δ�ü� 1��: " << l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											key = getNumber(0, 3);
											if (key >= 1)
											{
												int costvalue = 0;
												int amenties = l[p[i]->myPosition()]->numOfAmenties();
												for (int j = 1; j <= key; j++)
												{
													costvalue += l[p[i]->myPosition()]->costBuy(amenties + j);
												}

												if (p[i]->myMoney() >= costvalue)
												{
													p[i]->buyLand(l[p[i]->myPosition()], key);
													cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
												}
												else
												{
													cout << "���� �ݾ��� �����ؼ� ������ �� �����." << endl;
												}
											}
										}
									}*/
								}
								else
								{
									int sum = 0;
									for (int j = 0; j < 20; j++)
									{
										if (l[j]->owner() == p[i])
										{
											if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
											{
												sum += l[j]->costBuy();
											}
											else
											{
												sum += l[j]->retValue();
											}
										}
									}

									if (p[i]->myMoney() + sum*0.5 < fee)
									{
										PP(p[i]->num(), p[i]->myName(), nickname);
										cout << "���� �Ļ��߽��ϴ�." << endl;
										for (int j = 0; j < 19; j++)
										{
											if (l[j]->owner() == p[i])
											{
												p[i]->sellLand(l[j], 1);
											}
										}
										p[i]->makeBankrupt();
										alive--;
									}
									else
									{
										while (p[i]->myMoney() < fee)
										{
											cout << "���� �ݾ��� �����ؿ�. �Ű��� ���ϴ� ������ ��ȣ�� �����ϼ���." << endl;
											while (true)
											{
												key = getNumber(0, 19);
												if (l[key]->owner() == p[i])
												{
													break;
												}
												else
												{
													cout << "������ �ƴ� ���� �����߾��. �ٽ� �Է��ϼ���." << endl;
												}
											}
											p[i]->sellLand(l[key], 1);
											cout << l[key] << "(��)�� �Ű��߾��." << endl;
										}
									}
								}
							}
						}
						else 
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "����Ḧ �����߾��." << endl;
								p[i]->calMoney(-1 * fee);
								l[p[i]->myPosition()]->owner()->calMoney(fee);
							}
							else
							{
								int sum = 0;
								for (int j = 0; j < 20; j++)
								{
									if (l[j]->owner() == p[i])
									{
										if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
										{
											sum += l[j]->costBuy();
										}
										else
										{
											sum += l[j]->retValue();
										}
									}
								}

								if (p[i]->myMoney() + sum*0.5 < fee)
								{
									PP(p[i]->num(), p[i]->myName(), nickname);
									cout << "���� �Ļ��߽��ϴ�." << endl;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											p[i]->sellLand(l[j], 1);
										}
									}
									p[i]->makeBankrupt();
									alive--;
								}
								else
								{
									while (p[i]->myMoney() < fee)
									{
										cout << "���� �ݾ��� �����ؿ�. �Ű��� ���ϴ� ������ ��ȣ�� �����ϼ���." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "������ �ƴ� ���� �����߾��. �ٽ� �Է��ϼ���." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(��)�� �Ű��߾��." << endl;
									}
								}
							}
						}
					}
				}
			} while (is_double);
		}
		turn--;

	}

	display(p, l);

	if (isMonopoly(l) == 0)
	{
		if (alive == 1)
		{
			for (int j = 0; j<3; j++)
			{
				if (!p[j]->isBankrupt())
				{
					cout << p[j] << "�� �¸��Դϴ�!" << endl;
					break;
				}
			}
		}
		else
		{
			int best = 0;
			Person** winner = NULL;
			for (int i = 0; i < PERSON_NUM; i++) {
				int prop = p[i]->myProperty();
				if (prop > best) {
					winner = &p[i];
					best = prop;
				}
			}
			PP((*winner)->num(), (*winner)->myName(), nickname);
			cout << "�� �¸��Դϴ�!" << endl;
		}
	}
	else
	{
		PP(p[isMonopoly(l) - 1]->num(), p[isMonopoly(l) - 1]->myName(), nickname);
		cout << "�� �¸��Դϴ�!" << endl;
	}

	for (int i = 0; i < PERSON_NUM; i++)
	{
		delete p[i];
	}

	return 0;
}