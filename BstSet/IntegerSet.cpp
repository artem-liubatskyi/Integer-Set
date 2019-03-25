#include "Integer_Set.hpp"

void Integer_Set::Inserter(Node * Temp, int _value, Node *Fp)
{
	Temp->value = _value;
	Temp->Left_Child = nullptr;
	Temp->Right_Child = nullptr;
	Temp->Parent = Fp;
	Size++;
	if (Root == nullptr)
		Root = Temp;
}
void Integer_Set::BstInsertKey(int _value)
{
	Node *pCurrent = Root;
	while (1)
	{
		if (pCurrent == nullptr)
		{
			Node *Temp = new Node;
			Inserter(Temp, _value,nullptr);
			Root = Temp;
			return;
		}
		else
		{
			if (pCurrent->value == _value)
				return;

			if (pCurrent->value<_value)
			{
				if (pCurrent->Right_Child == nullptr)
				{
					Node *Temp = new Node;
					Inserter(Temp, _value,pCurrent);
					pCurrent->Right_Child = Temp;
					return;
				}
				else
					pCurrent = pCurrent->Right_Child;
			}
			else
			{
				if (pCurrent->Left_Child == nullptr)
				{
					Node *Temp = new Node;
					Inserter(Temp, _value, pCurrent);
					pCurrent->Left_Child = Temp;
					return;
				}
				else
					pCurrent = pCurrent->Left_Child;
			}
		}
	}
	delete pCurrent;
}
void Integer_Set::BstDeleteKey(int _key)
{
	Node * Some = IntegerSetFindKey(_key);
	if (!Some)
		return;

	Size--;
	if (!Some->Left_Child)
		BstTransplant(Some, Some->Right_Child);
	else if (!Some->Right_Child)
		BstTransplant(Some, Some->Left_Child);
	else
	{
		Node * NextNode = Some->Right_Child;
		while (NextNode && NextNode->Left_Child)
			NextNode = NextNode->Left_Child;

		if (NextNode->Parent != Some)
		{
			BstTransplant(NextNode, NextNode->Right_Child);

			NextNode->Right_Child = Some->Right_Child;
			NextNode->Right_Child->Parent = NextNode;
		}

		BstTransplant(Some, NextNode);

		NextNode->Left_Child = Some->Left_Child;
		NextNode->Left_Child->Parent = NextNode;
	}
	delete Some;
}
void Integer_Set::BstTransplant(Node * node, Node * OtherNode)
{
	if (!node->Parent)
	{
		if (node != Root)
			throw std::logic_error("Fatal!");
		Root = OtherNode;
	}

	else if (node->Parent->Left_Child == node)
		node->Parent->Left_Child = OtherNode;
	else if (node->Parent->Right_Child == node)
		node->Parent->Right_Child = OtherNode;
	else
		throw std::logic_error("Fatal!");

	if (OtherNode)
		OtherNode->Parent = node->Parent;
}

Integer_Set::Integer_Set()
	:Root(nullptr)
	, Size(0)
{}
Integer_Set::Integer_Set(int *_arr, int _num)
{
	if (_num <= 0 || _arr == nullptr)
		throw std::logic_error("Invalid parameters!");

	for (int i = 0; i < _num; i++)
	{
		BstInsertKey(_arr[i]);
	}

}
Integer_Set::Integer_Set(std::initializer_list<int> l)
	:Integer_Set()
{
	if (l.begin() == nullptr)
		return;

	for (int i : l)
	{
		BstInsertKey(i);
	}
}

int Integer_Set::getSize() const
{
	return Size;
}
Integer_Set::Node *Integer_Set::getRoot() const
{
	return Root;
};

Integer_Set& Integer_Set::operator +=(int _key)
{
	BstInsertKey(_key);
	return *this;
};
Integer_Set & Integer_Set::operator -=(int _key)
{
	BstDeleteKey(_key);
	return *this;
}

std::ostream & operator << (std::ostream & os, Integer_Set & _Some)
{
	if (!_Some.getRoot())
		os << "Empty Set";
	else
	{
		os << "{";

		int k = 0;
		for (int i : _Some)
		{
			if (k != 0)
				os << ",";
			k++;
			os << i;
		}
		os << "}";
	}
	return os;
}

Integer_Set::Node* Integer_Set::IntegerSetFindKey(int _key) const
{
	Node *pCurrent = Root;

	while (pCurrent)
	{
		if (pCurrent->value == _key)
			return pCurrent;
		if (pCurrent->value > _key)
			pCurrent = pCurrent->Left_Child;
		else
			pCurrent = pCurrent->Right_Child;
	}
	return nullptr;
};
bool Integer_Set::operator == (const Integer_Set &Set) const
{
	if (Size != Set.getSize())
		return false;
	else
	{
		for (int i : Set)
		{
			if (!IntegerSetFindKey(i))
				return false;
		}
		return true;
	}
}
bool Integer_Set::operator != (const Integer_Set &Set) const
{
	return !(*this == Set);
}

void Integer_Set::CopyDataFrom(const Integer_Set &_Some)
{
	for (int i : _Some)
	{
		this->BstInsertKey(i);
	}
}

Integer_Set::Integer_Set(const Integer_Set &_Some)
	:Integer_Set()
{
	CopyDataFrom(_Some);
}
Integer_Set::Integer_Set(Integer_Set &&_Some)
	: Root(_Some.Root)
	, Size(_Some.Size)
{
	_Some.Root = nullptr;
	_Some.Size = 0;

}

Integer_Set & Integer_Set::operator = (const Integer_Set &_Some)
{
	if (&_Some == this)
		return *this;

	Integer_Set Temp = _Some;
	
	std::swap(Root, Temp.Root);
	std::swap(Size, Temp.Size);

	return *this;
}
Integer_Set & Integer_Set::operator = (Integer_Set &&_Some)
{
	if (&_Some == this)
		return *this;
	Integer_Set Temp;
	std::swap(Root, _Some.Root);
	std::swap(Size, _Some.Size);
	std::swap(Temp.Root, _Some.Root);
	std::swap(Temp.Size, _Some.Size);

	return *this;
}

Integer_Set Integer_Set::operator &  (const Integer_Set &_Some) const
{
	Integer_Set TargetSet;

	for (int i : _Some)
	{
		if (IntegerSetFindKey(i))
			TargetSet.BstInsertKey(i);
	}
	return TargetSet;
};

Integer_Set & Integer_Set::operator &= (const Integer_Set &_Some)
{
	return *this = (*this & _Some);
};

Integer_Set Integer_Set::operator |  (const Integer_Set &_Some) const
{
	Integer_Set TargetSet = (*this);;

	for (int i : _Some)
	{
		if (!TargetSet.IntegerSetFindKey(i))
				TargetSet.BstInsertKey(i);
	}
	return TargetSet;

};
Integer_Set & Integer_Set::operator |= (const Integer_Set &_Some)
{
	for (int i : _Some)
	{
		if (!IntegerSetFindKey(i))
			BstInsertKey(i);
	}
	return *this;
};

Integer_Set Integer_Set::operator - (const Integer_Set &_Some) const
{
	Integer_Set TargetSet;

	for (int i : *this)
	{
		if (!_Some.IntegerSetFindKey(i))
			TargetSet.BstInsertKey(i);
	}

	for (int i : _Some)
	{
		if (!IntegerSetFindKey(i))
			TargetSet.BstInsertKey(i);
	}
	return TargetSet;
};

void Integer_Set::BstDestroy(Node*_some)
{
	if (!_some)
		return;

	BstDestroy(_some->Left_Child);
	BstDestroy(_some->Right_Child);
	delete _some;
}
Integer_Set::~Integer_Set()
{
	BstDestroy(this->getRoot());
}
