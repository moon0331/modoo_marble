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
		cout << "데이터를 정상적으로 불러올 수 없습니다. 게임을 종료합니다." << endl;
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

	cout << "성대의 마블" << endl;
	cout << "ⓒ 2017. Lee Seung-won, Kin Jin-woo, Mun Kyung-jin All rights reserved." << endl;
	cout << endl;
	cout << "닉네임을 사용하시겠습니까? 기본 설정값은 1, 2, 3입니다. 사용하려면 1, 사용하지 않으려면 0를 입력하세요." << endl;
	nickname = getNumber(0, 1);

	if (nickname) {
		char temp[100];
		cout << "닉네임을 입력하세요." << endl;
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
	cout << "주사위 던질 순서를 정할게요." << endl;
	cout << endl;
	cout << "첫번째 차례: " << p[0] << endl;
	cout << "두번째 차례: " << p[1] << endl;
	cout << "세번째 차례: " << p[2] << endl;
	cout << endl;*/

	bool is_double;
	int turn = 20; //20으로 고치기
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
				cout << "님의 턴이에요." << endl;
				//cout << p[i] << "님의 턴이에요." << endl;
				cout << turn << "턴 남았어요!" << endl;

				if (p[i]->retPenalty() > 0)
				{
					cout << "현재 학사경고 칸에 있어요. 지금부터 " << p[i]->retPenalty() << "턴 동안은 움직일 수 없어요!" << endl;

					if (p[i]->retJailFree())
					{
						cout << "학사경고 면제권을 사용해서 탈출할 수 있어요. 사용하려면 1, 사용하지 않으려면 2를 입력하세요." << endl;
						key = getNumber(1, 2);
						if (key == 1)
						{
							cout << "학사경고 면제권을 사용했어요." << endl;
							p[i]->no_jail_free();
							p[i]->useJailFree();
						}
						else
						{
							cout << "주사위를 던져 더블이 나오면 탈출할 수 있어요." << endl;
							cout << "주사위를 던지려면 3을 입력하세요." << endl;
							key = getNumber(3, 3);
							cout << "주사위를 던지는 중이에요." << endl;
							int dice_value = p[i]->role(is_double, key);
							cout << dice_value << "! ";
							if (is_double)
							{
								cout << "더블!" << endl;
								cout << "성공!" << endl;
								is_double = false;
							}
							else
							{
								cout << "실패!" << endl;
								break;
							}
						}
					}
					else
					{
						cout << "주사위를 던져 더블이 나오면 탈출할 수 있어요." << endl;
						cout << "주사위를 던지려면 3을 입력하세요." << endl;
						key = getNumber(3, 3);
						cout << "주사위를 던지는 중이에요." << endl;
						int dice_value = p[i]->role(is_double, key);
						cout << dice_value << "! ";
						if (is_double)
						{
							cout << "더블!" << endl;
							cout << "성공!" << endl;
							is_double = false;
						}
						else
						{
							cout << "실패!" << endl;
							break;
						}
					}
				}

				if (p[i]->retOdd() > 0 && p[i]->retEven() > 0)
				{
					cout << "현재 홀수 카드를 " << p[i]->retOdd() << "장, 짝수 카드를 " << p[i]->retEven() << "장 가지고 있어요." << endl;
					cout << "홀수 카드를 사용하려면 1, 짝수 카드를 사용하려면 2, 카드를 사용하지 않으려면 3을 입력하세요." << endl;
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
					cout << "현재 홀수 카드를 " << p[i]->retOdd() << "장 가지고 있어요." << endl;
					cout << "홀수 카드를 사용하려면 1, 카드를 사용하지 않으려면 3을 입력하세요." << endl;
					int arr[2] = { 1, 3 };
					key = getNumber(arr, 2);
					if (key == 1)
					{
						p[i]->useDiceItem(1);
					}
				}
				else if (p[i]->retEven() > 0)
				{
					cout << "현재 짝수 카드를 " << p[i]->retEven() << "장 가지고 있어요." << endl;
					cout << "짝수 카드를 사용하려면 2, 카드를 사용하지 않으려면 3을 입력하세요." << endl;
					key = getNumber(2, 3);
					if (key == 2)
					{
						p[i]->useDiceItem(2);
					}
				}
				else
				{
					cout << "주사위를 던지려면 3을 입력하세요." << endl;
					key = getNumber(3, 3);
				}

				cout << "주사위를 던지는 중이에요." << endl;
				int dice_value = p[i]->role(is_double, key);
				cout << dice_value << "! ";
				if (is_double)
				{
					cout << "더블!";
					double_count++;
				}

				cout << endl;

				if (double_count == 3)
				{
					p[i]->gotoJail();
					cout << "학사경고 칸에 도착했어요. 지금부터 3턴 동안은 움직일 수 없어요!" << endl;

					break;
				}

				p[i]->move(dice_value);
				display(p, l);

				bool flag = true;
				while (flag) {
					flag = false;
					if (isHiddenCard(p[i]->myPosition())) {
						cout << "히든카드를 뽑아보아요!" << endl;
						flag = p[i]->makeHiddenCard(&l);
					}
					if (p[i]->myPosition() == GO_BACK)
					{
						cout << "거꾸로 갑니다~ 꽉 잡으세요!" << endl;
						cout << "주사위를 던지려면 3을 입력하세요." << endl;
						key = getNumber(3, 3);
						cout << "주사위를 던지는 중이에요." << endl;
						dice_value = p[i]->role(is_double, key);
						cout << dice_value << "만큼 뒤로 이동합니다. " << endl;
						p[i]->move(dice_value *= -1);
						display(p, l);
						flag = true;
					}
					if (p[i]->myPosition() == SPACE_SHIP) {
						cout << "셔틀버스를 이용할 수 있어요." << endl;
						cout << "이동하고 싶은 곳의 번호를 입력해주세요." << endl;
						key = getNumber(0, 19);
						p[i]->moveForced(key);
						display(p, l);
						flag = true;
					}

				}

				if (p[i]->myPosition() == START)
				{
					cout << "출발점에 도착했어요." << endl;
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
						cout << "추가 건설을 원하는 지역의 번호를 입력하세요." << endl;
						while (true)
						{
							temp = getNumber(0, 19);
							if (l[temp]->owner() == p[i] && !isDorm(temp) && !l[temp]->isLandmark())
							{
								break;
							}
							else
							{
								cout << "주인이 아닌 지역을 선택했어요. 다시 입력하세요." << endl;
							}
						}

						if (l[temp]->numOfAmenties() == 3)
						{
							cout << "랜드마크를 구입할까요? 랜드마크를 구입하려면 1, 건설하지 않으려면 2를 입력하세요. " << endl;
							cout << "랜드마크 구입비용은 " << l[temp]->costBuy(3) << "이에요." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								if (p[i]->myMoney() >= l[temp]->costBuy(3))
								{
									p[i]->buyLandMark(l[temp], key);
									cout << "랜드마크 건설!" << endl;
								}
								else
								{
									cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
								}
							}
						}
						else
						{
							if (l[temp]->numOfAmenties() == 0)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~3)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 소유권만 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[temp]->costBuy(1) << endl;
								cout << "부대시설 2개: " << l[temp]->costBuy(1) + l[temp]->costBuy(2) << endl;
								cout << "부대시설 3개: " << l[temp]->costBuy(1) + l[temp]->costBuy(2) + l[temp]->costBuy(3) << endl;
							}
							else if (l[temp]->numOfAmenties() == 1)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~2)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 부대시설을 1개 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[temp]->costBuy(2) << endl;
								cout << "부대시설 2개: " << l[temp]->costBuy(2) + l[temp]->costBuy(3) << endl;
							}
							else if (l[temp]->numOfAmenties() == 2)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 부대시설을 2개 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[temp]->costBuy(3) << endl;
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
									cout << l[temp] << "(을)를 구입했어요!" << endl;
								}
								else
								{
									cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
								}
							}
						}
					}
					else
					{
						cout << "가지고 있는 지역이 없어서 추가 건설을 할 수 없어요." << endl;
					}
				}
				if (p[i]->myPosition() == JAIL)
				{
					cout << "학사경고 칸에 도착했어요. 지금부터 3턴 동안은 움직일 수 없어요!" << endl;
				}

				if (p[i]->myPosition() == GAMBLE)
				{
					cout << "Gamble 칸에 도착했어요. 미니게임을 하려면 1, 하지 않으려면 2를 입력하세요." << endl;
					cout << "미니게임 비용은 1000이에요." << endl;
					key = getNumber(1, 2);
					if (key == 1)
					{
						p[i]->Gamble(COST);
					}
				}

				if (isDorm(p[i]->myPosition()))
				{
					cout << l[p[i]->myPosition()] << "에 도착했어요." << endl;
					if (l[p[i]->myPosition()]->owner() == NULL)
					{
						cout << "기숙사를 구입할까요? 구입하려면 0, 구입하지 않으려면 -1을 입력하세요." << endl;
						cout << "구매 비용은 " << l[p[i]->myPosition()]->costBuy() << "이에요." << endl;
						key = getNumber(-1, 0);
						if (key == 0)
						{
							if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy())
							{
								p[i]->buyLand(l[p[i]->myPosition()], 0);
								cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
							}
							else
							{
								cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
							}
						}
					}
					else if (l[p[i]->myPosition()]->owner() != p[i])
					{
						int fee = l[p[i]->myPosition()]->costFee(0);
						cout << l[p[i]->myPosition()] << "의 현재 주인은 ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(이)에요." << endl;
						cout << "통행료는 " << fee << "이에요. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "통행료 면제권을 사용해서 통행료를 면제받을 수 있어요. 통행료 면제권을 사용하려면 1, 사용하지 않으려면 2를 입력하세요." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "통행료를 면제받았어요!" << endl;
							}
						}
						else
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "통행료를 지불했어요." << endl;
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
									cout << "님이 파산했습니다." << endl;
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
										cout << "소지 금액이 부족해요. 매각을 원하는 지역의 번호를 선택하세요." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "주인이 아닌 땅을 선택했어요. 다시 입력하세요." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(을)를 매각했어요." << endl;
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

				cout << l[p[i]->myPosition()] << "에 도착했어요." << endl;

				if (!l[p[i]->myPosition()]->isLandmark())
				{
					if (l[p[i]->myPosition()]->owner() == NULL)
					{
						cout << "지역을 구입할까요? 구입할 부대시설의 수를 입력하세요(1~3). 지역만 구입하려면 0, 구입하지 않으려면 -1을 입력하세요." << endl;
						cout << endl;
						cout << "지역만: " << l[p[i]->myPosition()]->costBuy(0) << endl;
						cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) << endl;
						cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
						cout << "부대시설 3개: " << l[p[i]->myPosition()]->costBuy(0) + l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
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
								cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
							}
							else
							{
								cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
							}
						}
					}
					else if (l[p[i]->myPosition()]->owner() == p[i])
					{
						if (l[p[i]->myPosition()]->numOfAmenties() == 3)
						{
							cout << "랜드마크를 구입할까요? 랜드마크를 구입하려면 1, 구입하지 않으려면 2를 입력하세요. " << endl;
							cout << "랜드마크 구입비용은 " << l[p[i]->myPosition()]->costBuy(3) << "이에요." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy(3))
								{
									p[i]->buyLandMark(l[p[i]->myPosition()], key);
									cout << "랜드마크 건설!" << endl;
								}
								else
								{
									cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
								}
							}
						}
						else
						{
							if (l[p[i]->myPosition()]->numOfAmenties() == 0)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~3)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 소유권만 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(1) << endl;
								cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
								cout << "부대시설 3개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
							}
							else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~2)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 부대시설을 1개 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(2) << endl;
								cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
							}
							else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
							{
								cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
								cout << "현재 부대시설을 2개 가지고 있어요." << endl;
								cout << endl;
								cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(3) << endl;
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
									cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
								}
								else
								{
									cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
								}
							}
						}
					}
					else
					{
						int fee = l[p[i]->myPosition()]->costFee(l[p[i]->myPosition()]->numOfAmenties());
						int take_over = l[p[i]->myPosition()]->retValue() * 2;
						cout << l[p[i]->myPosition()] << "의 현재 주인은 ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(이)에요." << endl;
						cout << "통행료는 " << fee << "(이)에요. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "통행료 면제권을 사용해서 통행료를 면제받을 수 있어요. 통행료 면제권을 사용하려면 1, 사용하지 않으려면 2를 입력하세요." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "통행료를 면제받았어요!" << endl;
							}
							else
							{
								if (p[i]->myMoney() >= fee)
								{
									cout << "통행료를 지불했어요." << endl;
									p[i]->calMoney(-1 * fee);
									l[p[i]->myPosition()]->owner()->calMoney(fee);

									cout << "건물을 인수할까요? 인수를 원하시면 1, 원하지 않으시면 2를 입력하세요. 인수 비용은 " << take_over << "이에요. " << endl;
									key = getNumber(1, 2);
									if (key == 1)
									{
										cout << "도시를 인수했어요! 인수 증서: ";
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << " -> ";

										//인수: 판매
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << endl;

										//인수: 구매
										p[i]->buyLand(l[p[i]->myPosition()], 0);

										if (l[p[i]->myPosition()]->numOfAmenties() == 3)
										{
											cout << "랜드마크를 구입할까요? 랜드마크를 구입하려면 1, 구입하지 않으려면 2를 입력하세요. " << endl;
											cout << "랜드마크 구입비용은 " << l[p[i]->myPosition()]->costBuy(3) << "(이)에요." << endl;
											key = getNumber(1, 2);
											if (key == 1)
											{
												if (p[i]->myMoney() >= l[p[i]->myPosition()]->costBuy(3))
												{
													p[i]->buyLandMark(l[p[i]->myPosition()], key);
													cout << "랜드마크 건설!" << endl;
												}
												else
												{
													cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
												}
											}
										}
										else
										{
											if (l[p[i]->myPosition()]->numOfAmenties() == 0)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~3)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 소유권만 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(1) << endl;
												cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "부대시설 3개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~2)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 부대시설을 1개 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 부대시설을 2개 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(3) << endl;
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
													cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
												}
												else
												{
													cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
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
										cout << "님이 파산했습니다." << endl;
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
											cout << "매각을 원하는 지역의 번호를 선택하세요." << endl;
											while (true)
											{
												key = getNumber(0, 19);
												if (l[key]->owner() == p[i])
												{
													break;
												}
												else
												{
													cout << "주인이 아닌 땅을 선택했어요. 다시 입력하세요." << endl;
												}
											}
											p[i]->sellLand(l[key], 1);
											cout << l[key] << "(을)를 매각했어요." << endl;
										}
									}
								}
							}
						}
						else
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "통행료를 지불했어요." << endl;
								p[i]->calMoney(-1 * fee);
								l[p[i]->myPosition()]->owner()->calMoney(fee);

								cout << "건물을 인수할까요? 인수를 원하시면 1, 원하지 않으시면 2를 입력하세요. 인수 비용은 " << take_over << "이에요. " << endl;
								key = getNumber(1, 2);
								if (key == 1)
								{
									cout << "도시를 인수했어요! 인수 증서: ";
									PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
									cout << " -> ";

									//인수: 판매
									l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

									l[p[i]->myPosition()]->owner(p[i]);
									PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
									cout << endl;

									//인수: 구매
									p[i]->buyLand(l[p[i]->myPosition()], 0);

									if (l[p[i]->myPosition()]->numOfAmenties() == 3)
									{
										cout << "랜드마크를 구입할까요? 랜드마크를 구입하려면 1, 구입하지 않으려면 2를 입력하세요. " << endl;
										cout << "랜드마크 구입비용은 " << l[p[i]->myPosition()]->costBuy(3) << "이에요." << endl;
										key = getNumber(1, 2);
										if (key == 1)
										{
											cout << "랜드마크 건설!" << endl;
											p[i]->buyLandMark(l[p[i]->myPosition()], key);
										}
									}
									else
									{
										if (l[p[i]->myPosition()]->numOfAmenties() == 0)
										{
											cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~3)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
											cout << "현재 소유권만 가지고 있어요." << endl;
											cout << endl;
											cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(1) << endl;
											cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
											cout << "부대시설 3개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
										}
										else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
										{
											cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~2)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
											cout << "현재 부대시설을 1개 가지고 있어요." << endl;
											cout << endl;
											cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(2) << endl;
											cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
										}
										else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
										{
											cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
											cout << "현재 부대시설을 2개 가지고 있어요." << endl;
											cout << endl;
											cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(3) << endl;
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
												cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
											}
											else
											{
												cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
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
									cout << "님이 파산했습니다." << endl;
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
										cout << "소지 금액이 부족해요. 매각을 원하는 지역의 번호를 선택하세요." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "주인이 아닌 땅을 선택했어요. 다시 입력하세요." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(을)를 매각했어요." << endl;
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
						cout << l[p[i]->myPosition()] << "의 현재 주인은 ";
						PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
						cout << "(이)에요." << endl;
						cout << "통행료는 " << fee << "이에요. " << endl;

						if (p[i]->retFeeFree())
						{
							cout << "통행료 면제권을 사용해서 통행료를 면제받을 수 있어요. 통행료 면제권을 사용하려면 1, 사용하지 않으려면 2를 입력하세요." << endl;
							key = getNumber(1, 2);
							if (key == 1)
							{
								cout << "통행료를 면제받았어요!" << endl;
							}
							else
							{
								if (p[i]->myMoney() >= fee)
								{
									cout << "통행료를 지불했어요." << endl;
									p[i]->calMoney(-1 * fee);
									l[p[i]->myPosition()]->owner()->calMoney(fee);

									/*cout << "건물을 인수할까요? 인수를 원하시면 1, 원하지 않으시면 2를 입력하세요. 인수 비용은 " << take_over << "이에요. " << endl;
									key = getNumber(1, 2);
									if (key == 1)
									{
										cout << "도시를 인수했어요! 인수 증서: ";
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << " -> ";

										//인수: 판매
										l[p[i]->myPosition()]->owner()->sellLand(l[p[i]->myPosition()], 0);

										l[p[i]->myPosition()]->owner(p[i]);
										PP(l[p[i]->myPosition()]->owner()->num(), l[p[i]->myPosition()]->owner()->myName(), nickname);
										cout << endl;

										//인수: 구매
										p[i]->buyLand(l[p[i]->myPosition()], 0);

										if (l[p[i]->myPosition()]->numOfAmenties() == 3)
										{
											cout << "랜드마크를 건설할까요? 랜드마크를 건설하려면 1, 건설하지 않으려면 2를 입력하세요. " << endl;
											cout << "랜드마크 건설비용은 " << l[p[i]->myPosition()]->costBuy(3) << "이에요." << endl;
											key = getNumber(1, 2);
											if (key == 1)
											{
												cout << "랜드마크 건설!" << endl;
												p[i]->buyLandMark(l[p[i]->myPosition()], key);
											}
										}
										else
										{
											if (l[p[i]->myPosition()]->numOfAmenties() == 0)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~3)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 소유권만 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(1) << endl;
												cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "부대시설 3개: " << l[p[i]->myPosition()]->costBuy(1) + l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 1)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1~2)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 부대시설을 1개 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(2) << endl;
												cout << "부대시설 2개: " << l[p[i]->myPosition()]->costBuy(2) + l[p[i]->myPosition()]->costBuy(3) << endl;
											}
											else if (l[p[i]->myPosition()]->numOfAmenties() == 2)
											{
												cout << "부대시설을 구입할까요? 구입할 부대시설의 수(1)를 입력하세요. 구입하지 않으려면 0을 입력하세요." << endl;
												cout << "현재 부대시설을 2개 가지고 있어요." << endl;
												cout << endl;
												cout << "부대시설 1개: " << l[p[i]->myPosition()]->costBuy(3) << endl;
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
													cout << l[p[i]->myPosition()] << "(을)를 구입했어요!" << endl;
												}
												else
												{
													cout << "소지 금액이 부족해서 구입할 수 없어요." << endl;
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
										cout << "님이 파산했습니다." << endl;
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
											cout << "소지 금액이 부족해요. 매각을 원하는 지역의 번호를 선택하세요." << endl;
											while (true)
											{
												key = getNumber(0, 19);
												if (l[key]->owner() == p[i])
												{
													break;
												}
												else
												{
													cout << "주인이 아닌 땅을 선택했어요. 다시 입력하세요." << endl;
												}
											}
											p[i]->sellLand(l[key], 1);
											cout << l[key] << "(을)를 매각했어요." << endl;
										}
									}
								}
							}
						}
						else 
						{
							if (p[i]->myMoney() >= fee)
							{
								cout << "통행료를 지불했어요." << endl;
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
									cout << "님이 파산했습니다." << endl;
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
										cout << "소지 금액이 부족해요. 매각을 원하는 지역의 번호를 선택하세요." << endl;
										while (true)
										{
											key = getNumber(0, 19);
											if (l[key]->owner() == p[i])
											{
												break;
											}
											else
											{
												cout << "주인이 아닌 땅을 선택했어요. 다시 입력하세요." << endl;
											}
										}
										p[i]->sellLand(l[key], 1);
										cout << l[key] << "(을)를 매각했어요." << endl;
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
					cout << p[j] << "의 승리입니다!" << endl;
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
			cout << "의 승리입니다!" << endl;
		}
	}
	else
	{
		PP(p[isMonopoly(l) - 1]->num(), p[isMonopoly(l) - 1]->myName(), nickname);
		cout << "의 승리입니다!" << endl;
	}

	for (int i = 0; i < PERSON_NUM; i++)
	{
		delete p[i];
	}

	return 0;
}