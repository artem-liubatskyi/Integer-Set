#pragma once
#include <iostream>

class Integer_Set
{
	struct Node
	{
		int value;
		Node *Parent;
		Node *Left_Child;
		Node *Right_Child;
	};

	Node *Root;
	int Size;
	
private:

	void Inserter(Node *, int, Node*);
	void BstTransplant(Node *, Node *);
	void BstInsertKey(int);
	void BstDeleteKey(int);
	void CopyDataFrom(const Integer_Set &);
	void BstDestroy(Node *);

public:

	Integer_Set();
	Integer_Set(int *, int);
	Integer_Set(std::initializer_list<int>);
	
	int   getSize()   const;
	Node* getRoot()   const;

	bool operator ==(const Integer_Set &) const;
	bool operator !=(const Integer_Set &) const;

	Integer_Set & operator +=(int);
	Integer_Set & operator -=(int);

	friend std::ostream & operator << (std::ostream &, Integer_Set &);

	Integer_Set(const Integer_Set &);
	Integer_Set(Integer_Set &&);
	Integer_Set & operator = (const Integer_Set &);
	Integer_Set & operator = (Integer_Set &&);

	Integer_Set   operator & (const Integer_Set &) const;
	Integer_Set & operator &=(const Integer_Set &);

	Integer_Set   operator | (const Integer_Set &) const;
	Integer_Set & operator |=(const Integer_Set &);

	Integer_Set operator - (const Integer_Set &) const;
	Node* IntegerSetFindKey(int) const;

	~Integer_Set();

	class BstIterator
	{
		Node *pCurrent;

	public:

		BstIterator()
			:pCurrent(nullptr)
		{}
		BstIterator(Node* _Root) { pCurrent = _Root;}

		BstIterator operator++ ()
		{
			Node *p;

			if (pCurrent->Right_Child != NULL)
			{
				pCurrent = pCurrent->Right_Child;

				while (pCurrent->Left_Child != NULL) {
					pCurrent = pCurrent->Left_Child;
				}
			}
			else
			{
				p = pCurrent->Parent;
				while (p != NULL && pCurrent == p->Right_Child)
				{
					pCurrent = p;
					p = p->Parent;
				}

				pCurrent = p;
			}
			return *this;
		};

		bool operator ==(const BstIterator & _Some)
		{
			return pCurrent == _Some.pCurrent;
		};
		bool operator !=(const BstIterator & _Some)
		{
			return pCurrent != _Some.pCurrent;
		};
		int operator *()
		{
			return pCurrent->value;
		};
	};

	BstIterator begin() const
	{
		Node* pCurrent = Root;

		while (pCurrent && pCurrent->Left_Child)
			pCurrent = pCurrent->Left_Child;

		return BstIterator(pCurrent);
	};
	BstIterator end() const
	{
		return BstIterator(nullptr);
	};
};

