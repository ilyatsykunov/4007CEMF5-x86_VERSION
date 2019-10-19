#pragma once
#ifndef SHOPCLASS_H
#define SHOPCLASS_H

#include "Trainer.h"
#include "Item.h"
#include "Creep.h"
#include <iostream>

using namespace std;

class ShopClass
{
	public:

		vector<Item> buyingItems;
		vector<Item> sellingItems;

		void buyItem(Trainer& person, Item item, int quantity) {

			if (person.getTrainerMoney() >= (item.price * quantity))
			{
				for (int i = 0; i < quantity; i++)
				{
					person.Buy(item);
				}
			}
		}
		void sellItem(Trainer& person, Item item, int quantity) {

			for (int i = quantity; i > 0; i--)
			{
				person.Sell(item);
			}
		}
};


void shopTest()
{
	Trainer person(5000.00f);
	HealthPotion test("potion_1", 20.00, 20);
	HealthPotion test2("potion_2", 30.00, 20);
	HealthPotion test3("potion_3", 40.00, 20);
	HealthPotion test4("potion_4", 50.00, 20);
	HealthPotion test5("potion_5", 60.00, 20);
	ShopClass shop;

	shop.buyItem(person, test, 5);

	person.showInventory();
	cout << person.getTrainerMoney() << endl;

	char dontstop;
	cin >> dontstop;


}







#endif