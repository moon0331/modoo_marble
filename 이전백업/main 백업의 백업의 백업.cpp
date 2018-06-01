/*
�� 2017. Lee Seung-won, Kim JIn-woo, Mun Kyeong-jin All rights reserved.
*/

#include "modoo_oop_2.h" //2�� ����

int main()
{
	vector<Land*> l(MAXLAND);
	vector<Person*> p(3);

	try {
		loadData(l, p);
	}
	catch (...) {
		cout << "�����͸� ���������� �ҷ��� �� �����ϴ�. ������ �����մϴ�." << endl;
		return 0;
	}

	cout << endl;
	cout << "������ ���� v1.0" << endl;
	cout << endl;
	cout << "�ֻ��� ���� ������ ���ҰԿ�." << endl;
	cout << endl;

	int order[3];

	/*srand(int(time(NULL)));
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

	for (int i = 0; i < 3; i++)
	{
		p[i] = new Person(i/*order[i]*/, "");
	}
	cout << "ù��° ����: " << p[0] << endl;
	cout << "�ι�° ����: " << p[1] << endl;
	cout << "����° ����: " << p[2] << endl;
	cout << endl;

	bool is_double;
	int turn = 1;

	//���� ������
	while (turn <= 20)
	{
		for (int i = 0; i < 3; i++)
		{
			int double_count = 0;
			do
			{
				display(p, l);
				is_double = false;
				int key;
				cout << p[i] << "���� ���̿���." << endl;

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
						cout << "����ī�带 �̵��� �غ��ô�" << endl;
						flag = p[i]->makeHiddenCard(&l);
					}
					if (p[i]->myPosition() == GO_BACK)
					{
						display(p, l);
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
						flag = true;
					}

				}

				if (p[i]->myPosition() == START)
				{
					cout << "������� �����߾��." << endl;
					bool is_owned = false;
					for (int j = 0; j < 19; j++)
					{
						if (l[j]->owner() == p[i])
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
							if (l[temp]->owner() == p[i])
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
							cout << "���帶ũ�� �Ǽ��ұ��? ���帶ũ�� �Ǽ��Ϸ��� 1, �Ǽ����� �������� 2�� �Է��ϼ���. " << endl;
							cout << "���帶ũ �Ǽ������ " << l[temp]->costBuy(3) << "�̿���." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "���帶ũ �Ǽ�!" << endl;
								p[i]->buyLandMark(l[temp], key);
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
								p[i]->buyLand(l[temp], key);
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
							p[i]->buyLand(l[p[i]->myPosition()], 0);
							cout << l[p[i]->myPosition()] << "(��)�� �����߾��!" << endl;
						}
					}
					else if (l[p[i]->myPosition()]->owner() != p[i])
					{
						int fee = l[p[i]->myPosition()]->costFee(0);
						cout << l[p[i]->myPosition()] << "�� ���� ������ " << l[p[i]->myPosition()]->owner() << "�̿���." << endl;
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
								}
								else
								{
									int sum = 0;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
											{
												sum += l[j]->costBuy();
											}
											else
											{
												sum += l[j]->costBuy(l[j]->numOfAmenties());
											}
										}
									}

									if (p[i]->myMoney() + sum*0.5 < fee)
									{
										cout << p[i] << "���� �Ļ��߽��ϴ�." << endl;
										for (int j = 0; j < 19; j++)
										{
											if (l[j]->owner() == p[i])
											{
												p[i]->sellLand(l[j], 1);
											}
										}

										//delete[] p[i];
										//p[i] ����
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
												p[i]->sellLand(l[key], 1);
												l[key]->owner(NULL);
												cout << l[key] << "(��)�� �Ű��߾��." << endl;
											}
										}
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
							p[i]->buyLand(l[p[i]->myPosition()], key);
						}
					}
					else if (l[p[i]->myPosition()]->owner() == p[i])
					{
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
								p[i]->buyLand(l[p[i]->myPosition()], key);
							}
						}
					}
					else
					{
						int fee = l[p[i]->myPosition()]->costFee(l[p[i]->myPosition()]->numOfAmenties());
						int take_over = l[p[i]->myPosition()]->retValue() * 2;
						cout << l[p[i]->myPosition()] << "�� ���� ������ " << l[p[i]->myPosition()]->owner() << "�̿���." << endl;
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
										cout << "���ø� �μ��߾��! �μ� ����: " << l[p[i]->myPosition()]->owner() << " -> ";

										//�μ�: �Ǹ�
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										cout << l[p[i]->myPosition()]->owner() << endl;

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
												p[i]->buyLand(l[p[i]->myPosition()], key);
											}
										}
									}
								}
								else
								{
									int sum = 0;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
											{
												sum += l[j]->costBuy();
											}
											else
											{
												sum += l[j]->costBuy(l[j]->numOfAmenties());
											}
										}
									}

									if (p[i]->myMoney() + sum*0.5 < fee)
									{
										cout << p[i] << "���� �Ļ��߽��ϴ�." << endl;
										for (int j = 0; j < 19; j++)
										{
											if (l[j]->owner() == p[i])
											{
												p[i]->sellLand(l[j], 1);
											}
										}

										//delete[] p[i];
										//p[i] ����
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
												//�Ű�: �Ǹ� ��� 0.5�� �ȸ���
												p[i]->sellLand(l[key], 1);
												l[key]->owner(NULL);
												cout << l[key] << "(��)�� �Ű��߾��." << endl;
											}
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
									cout << "���ø� �μ��߾��! �μ� ����: " << l[p[i]->myPosition()]->owner() << " -> ";

									//�μ�: �Ǹ�
									l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

									l[p[i]->myPosition()]->owner(p[i]);
									cout << l[p[i]->myPosition()]->owner() << endl;

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
											p[i]->buyLand(l[p[i]->myPosition()], key);
										}
									}
								}
							}
							else
							{
								int sum = 0;
								for (int j = 0; j < 19; j++)
								{
									if (l[j]->owner() == p[i])
									{
										if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
										{
											sum += l[j]->costBuy();
										}
										else
										{
											sum += l[j]->costBuy(l[j]->numOfAmenties());
										}
									}
								}

								if (p[i]->myMoney() + sum*0.5 < fee)
								{
									cout << p[i] << "���� �Ļ��߽��ϴ�." << endl;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											p[i]->sellLand(l[j], 1);
										}
									}

									//delete[] p[i];
									//p[i] ����
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
											p[i]->sellLand(l[key], 1);
											cout << l[key] << "(��)�� �Ű��߾��." << endl;
										}
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
						int fee = l[p[i]->myPosition()]->costFee(l[p[i]->myPosition()]->numOfAmenties());
						int take_over = l[p[i]->myPosition()]->retValue() * 2;
						cout << l[p[i]->myPosition()] << "�� ���� ������ " << l[p[i]->myPosition()]->owner() << "(��)����." << endl;
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

									cout << "�ǹ��� �μ��ұ��? �μ��� ���Ͻø� 1, ������ �����ø� 2�� �Է��ϼ���. �μ� ����� " << take_over << "�̿���. " << endl;
									key = getNumber(1, 2);
									if (key == 1)
									{
										cout << "���ø� �μ��߾��! �μ� ����: " << l[p[i]->myPosition()]->owner() << " -> ";

										//�μ�: �Ǹ�
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										cout << l[p[i]->myPosition()]->owner() << endl;

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
												p[i]->buyLand(l[p[i]->myPosition()], key);
											}
										}
									}
								}
								else
								{
									int sum = 0;
									for (int j = 0; j < 19; j++)
									{
										if (l[j]->owner() == p[i])
										{
											if (j == IN_GWAN || j == UI_GWAN || j == YE_GWAN || j == JI_GWAN)
											{
												sum += l[j]->costBuy();
											}
											else
											{
												sum += l[j]->costBuy(l[j]->numOfAmenties());
											}
										}
									}

									if (p[i]->myMoney() + sum*0.5 < fee)
									{
										cout << p[i] << "���� �Ļ��߽��ϴ�." << endl;
										for (int j = 0; j < 19; j++)
										{
											if (l[j]->owner() == p[i])
											{
												p[i]->sellLand(l[j], 1);
											}
										}

										//delete[] p[i];
										//p[i] ����
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
												p[i]->sellLand(l[key], 1);
												l[key]->owner(NULL);
												cout << l[key] << "(��)�� �Ű��߾��." << endl;
											}
										}
									}
								}
							}
						}
					}
				}
			} while (is_double);
		}
		turn++;
	}

	for (int i = 0; i < 3; i++)
	{
		delete[] p[i];
	}

	return 0;
}