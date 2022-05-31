#pragma once
//Date : 2022-05-29
//Name : Jinseok Son
//Description: Simple Singleton class
#include"Printer.h"
#include<iostream>
template<typename T>
class SingleTon
{
public:
	static T* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new T();
		}
		else
			return mInstance;
		
	}
private:
	inline static T* mInstance=nullptr;

};
class Printer :public SingleTon<Printer>
{
public:
	void print()
	{
		std::cout << "Hello" << '\n';

	}
};




