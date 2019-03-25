#include "testslib.hpp"
#include <cassert>
#include "Integer_Set.hpp"


DECLARE_TEST(test_deffult_constructor)
{
	Integer_Set a;
	assert(!a.getRoot());
	assert(!a.IntegerSetFindKey(5));
	assert(!a.IntegerSetFindKey(8));
	assert(a.getSize() == 0);
}

DECLARE_TEST(test_array_constructor)
{
	int arr[4] = { 3,2,1,4 };
	int arr1[1] = { 1 };

	Integer_Set b(arr, 4);
	assert(b.getRoot() != nullptr);
	assert(b.IntegerSetFindKey(3));
	assert(b.IntegerSetFindKey(2));
	assert(b.IntegerSetFindKey(1));
	assert(b.IntegerSetFindKey(4));
	assert(!b.IntegerSetFindKey(5));
	assert(!b.IntegerSetFindKey(8));
	assert(b.getSize() == 4);

	Integer_Set b1(arr1, 1);
	assert(b1.getRoot() != nullptr);
	assert(b1.IntegerSetFindKey(1));
	assert(!b1.IntegerSetFindKey(5));
	assert(b1.getSize() == 1);

	try
	{
		Integer_Set b2(nullptr, 2);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Invalid parameters!"));
	}

	try
	{
		Integer_Set b3(arr1, 0);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Invalid parameters!"));
	}

	try
	{
		Integer_Set b4(nullptr, 0);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception & e)
	{
		assert(!strcmp(e.what(), "Invalid parameters!"));
	}
}

DECLARE_TEST(test_list_constructor)
{
	Integer_Set c{ 5,8,7,3,3 };
	assert(c.getRoot() != nullptr);
	assert(c.IntegerSetFindKey(5));
	assert(c.IntegerSetFindKey(8));
	assert(c.IntegerSetFindKey(7));
	assert(c.IntegerSetFindKey(3));
	assert(!c.IntegerSetFindKey(22));
	assert(!c.IntegerSetFindKey(11));
	assert(c.getSize() == 4);

	Integer_Set c1{ 3 };
	assert(c1.getRoot() != nullptr);
	assert(c1.IntegerSetFindKey(3));
	assert(!c1.IntegerSetFindKey(22));
	assert(c1.getSize() == 1);

	Integer_Set c2{};
	assert(c2.getRoot() == nullptr);
	assert(!c2.IntegerSetFindKey(3));
	assert(!c2.IntegerSetFindKey(22));
	assert(c2.getSize() == 0);
}

DECLARE_TEST(test_intersect_operator)
{
	Integer_Set Inters, Inters1{ 1,2,3 }, Inters2{ 2,8,1 }, Inters_1_2{ 1,2 };
	Integer_Set Empty_Set;

	assert((Empty_Set & Inters1) == Empty_Set);
	assert((Inters1 & Empty_Set) == Empty_Set);
	assert((Empty_Set & Empty_Set) == Empty_Set);

	assert((Inters1 & Inters1) == Inters1);
	assert((Inters1 & Inters1) == Inters1);
	assert((Inters1 & Inters2) == Inters_1_2);
	assert((Inters2 & Inters1) == Inters_1_2);
	assert((Inters2 &= Inters1) == Inters_1_2);
	Integer_Set g1{ 55,11,22,33,44,66,77,88 }, g2{ 51,11,21,33,41,66,71,88 }, h{ 11,33,66,88 };
	assert(h == (g1 &= g2));
}

DECLARE_TEST(test_plus_minus_operators)
{
	Integer_Set Set, Set1{ 1 }, Set2{ 8 }, Set_1_2{ 1,2 };
	Integer_Set Empty_Set;

	assert((Empty_Set += 1) == Set1);
	assert(Empty_Set.IntegerSetFindKey(1));
	assert(!Empty_Set.IntegerSetFindKey(22));
	assert((Empty_Set.getSize()) == 1);

	assert((Set1 += 2) == Set_1_2);
	assert(!Set1.IntegerSetFindKey(3));
	assert(Set1.IntegerSetFindKey(1));
	assert(Set1.IntegerSetFindKey(2));
	assert((Set1.getSize()) == 2);

	assert((Set2 -= 8) == Set);
	assert(!Set2.IntegerSetFindKey(11));
	assert((Set2.getSize()) == 0);

	Set_1_2 -= 4;
	assert(!Set_1_2.IntegerSetFindKey(4));
	assert(Set_1_2.IntegerSetFindKey(1));
	assert(Set_1_2.IntegerSetFindKey(2));
	assert(Set_1_2.getSize()==2);

	assert(Set_1_2.IntegerSetFindKey(1));
	Set_1_2-=1;
	assert(!Set_1_2.IntegerSetFindKey(1));

	assert(Set_1_2.IntegerSetFindKey(2));
	Set_1_2 -= 2;
	assert(!Set_1_2.IntegerSetFindKey(2));
}

DECLARE_TEST(test_nion_operator)
{
	Integer_Set Union1{ 1,2,3 }, Union2{ 2,8,1 }, Union_1_2{ 2,1,3,8 }, Union3{ 1 };
	Integer_Set Empty_Set;

	assert((Empty_Set | Union1) == Union1);
	assert((Union1 | Empty_Set) == Union1);

	assert((Union1 | Union2) == Union_1_2);
	assert((Union2 | Union1) == Union_1_2);

	assert((Union3 | Union2) == Union2);
	assert((Union2 | Union3) == Union2);

	assert((Empty_Set | Union3) == Union3);
	assert((Union3 | Empty_Set) == Union3);

	assert((Empty_Set | Empty_Set) == Empty_Set);
}

DECLARE_TEST(test_differense_operator)
{
	Integer_Set Diff1{ 1,2,3 }, Diff2{ 2,8,1 }, Diff_1_2{ 8,3 }, Diff3{ 2 };
	Integer_Set Empty_Set;
	assert((Empty_Set - Diff1) == Diff1);
	assert((Diff1 - Empty_Set) == Diff1);
	assert((Diff1 - Diff2) == Diff_1_2);
	assert((Diff2 - Diff1) == Diff_1_2);
}

DECLARE_TEST(test_copying_moving)
{
	Integer_Set Set1{ 5,4,3,2,6 };

	Integer_Set Set2 = Set1;
	assert(Set2.IntegerSetFindKey(5));
	assert(Set2.IntegerSetFindKey(4));
	assert(Set2.IntegerSetFindKey(3));
	assert(Set2.IntegerSetFindKey(2));
	assert(Set2.IntegerSetFindKey(6));
	assert(Set2.getRoot() != nullptr);
	assert(Set2.getSize() == 5);

	assert(Set1.IntegerSetFindKey(5));
	assert(Set1.IntegerSetFindKey(4));
	assert(Set1.IntegerSetFindKey(3));
	assert(Set1.IntegerSetFindKey(2));
	assert(Set1.IntegerSetFindKey(6));
	assert(Set1.getRoot() != nullptr);
	assert(Set1.getSize() == 5);

	Integer_Set EmptySet;
	Integer_Set InitialEmpty = EmptySet;
	assert(!InitialEmpty.IntegerSetFindKey(5));
	assert(!InitialEmpty.IntegerSetFindKey(4));
	assert(!InitialEmpty.IntegerSetFindKey(3));
	assert(InitialEmpty.getRoot() == nullptr);
	assert(InitialEmpty.getSize() == 0);

	
	Integer_Set SetE1{ 7,12,6,8 };
	SetE1 = EmptySet;
	assert(!SetE1.IntegerSetFindKey(7));
	assert(!SetE1.IntegerSetFindKey(12));
	assert(!SetE1.IntegerSetFindKey(6));
	assert(!SetE1.IntegerSetFindKey(8));
	assert(!SetE1.IntegerSetFindKey(5));
	assert(SetE1.getRoot() == nullptr);
	assert(SetE1.getSize() == 0);

	assert(!EmptySet.IntegerSetFindKey(7));
	assert(!EmptySet.IntegerSetFindKey(12));
	assert(!EmptySet.IntegerSetFindKey(6));
	assert(!EmptySet.IntegerSetFindKey(8));
	assert(!EmptySet.IntegerSetFindKey(5));
	assert(EmptySet.getRoot() == nullptr);
	assert(EmptySet.getSize() == 0);

	
	Integer_Set Set3{ 4,5,6,8 };
	Set3 = Set2;

	assert(Set2.IntegerSetFindKey(5));
	assert(Set2.IntegerSetFindKey(4));
	assert(Set2.IntegerSetFindKey(3));
	assert(Set2.IntegerSetFindKey(2));
	assert(Set2.IntegerSetFindKey(6));
	assert(Set2.getRoot() != nullptr);
	assert(Set2.getSize() == 5);

	assert(Set3.IntegerSetFindKey(5));
	assert(Set3.IntegerSetFindKey(4));
	assert(Set3.IntegerSetFindKey(3));
	assert(Set3.IntegerSetFindKey(2));
	assert(Set3.IntegerSetFindKey(6));
	assert(Set3.getRoot() != nullptr);
	assert(Set3.getSize() == 5);

	Integer_Set Set4 = std::move(Set3);

	assert(Set4.IntegerSetFindKey(5));
	assert(Set4.IntegerSetFindKey(4));
	assert(Set4.IntegerSetFindKey(3));
	assert(Set4.IntegerSetFindKey(2));
	assert(Set4.IntegerSetFindKey(6));
	assert(Set4.getRoot() != nullptr);
	assert(Set4.getSize() == 5);

	assert(!Set3.IntegerSetFindKey(5));
	assert(!Set3.IntegerSetFindKey(4));
	assert(!Set3.IntegerSetFindKey(3));
	assert(!Set3.IntegerSetFindKey(2));
	assert(!Set3.IntegerSetFindKey(6));
	assert(Set3.getRoot() == nullptr);
	assert(Set3.getSize() == 0);

	Integer_Set _Set{ 1,2,3,4 };
	_Set = std::move(EmptySet);

	assert(!_Set.IntegerSetFindKey(1));
	assert(!_Set.IntegerSetFindKey(2));
	assert(!_Set.IntegerSetFindKey(3));
	assert(!_Set.IntegerSetFindKey(4));
	assert(_Set.getRoot() == nullptr);
	assert(_Set.getSize() == 0);

	assert(!EmptySet.IntegerSetFindKey(1));
	assert(!EmptySet.IntegerSetFindKey(2));
	assert(!EmptySet.IntegerSetFindKey(3));
	assert(!EmptySet.IntegerSetFindKey(4));
	assert(EmptySet.getRoot() == nullptr);
	assert(EmptySet.getSize() == 0);

	Integer_Set Empty_Set2 = std::move(EmptySet);

	assert(!Empty_Set2.IntegerSetFindKey(5));
	assert(!Empty_Set2.IntegerSetFindKey(4));
	assert(!Empty_Set2.IntegerSetFindKey(3));
	assert(Empty_Set2.getRoot() == nullptr);
	assert(Empty_Set2.getSize() == 0);

	assert(!EmptySet.IntegerSetFindKey(5));
	assert(!EmptySet.IntegerSetFindKey(4));
	assert(!EmptySet.IntegerSetFindKey(3));
	assert(!EmptySet.IntegerSetFindKey(2));
	assert(!EmptySet.IntegerSetFindKey(6));
	assert(EmptySet.getRoot() == nullptr);
	assert(EmptySet.getSize() == 0);

	Integer_Set Set5{ 1,2,3 };

	Set2 = std::move(Set5);
	assert(Set2.IntegerSetFindKey(1));
	assert(Set2.IntegerSetFindKey(2));
	assert(Set2.IntegerSetFindKey(3));
	assert(Set2.getRoot() != nullptr);
	assert(Set2.getSize() == 3);

	assert(!Set5.IntegerSetFindKey(1));
	assert(!Set5.IntegerSetFindKey(2));
	assert(!Set5.IntegerSetFindKey(3));
	assert(Set5.getRoot() == nullptr);
	assert(Set5.getSize() == 0);
}

DECLARE_TEST(test_copying_deleting_sets)
{
	Integer_Set Set{ 1,2,3 };
	{
		Integer_Set SetToDel{ 1,4,6 };
		Set=SetToDel ;
	}

	assert(Set.IntegerSetFindKey(1));
	assert(Set.IntegerSetFindKey(6));
	assert(Set.IntegerSetFindKey(4));
	assert(Set.getRoot() != nullptr);
	assert(Set.getSize() == 3);


	Integer_Set EmptySet;
	{
		Integer_Set SetToDel{ 1,4,6 };
		EmptySet = SetToDel;
	}

	assert(EmptySet.IntegerSetFindKey(1));
	assert(EmptySet.IntegerSetFindKey(6));
	assert(EmptySet.IntegerSetFindKey(4));
	assert(EmptySet.getRoot() != nullptr);
	assert(EmptySet.getSize() == 3);



	Integer_Set Set1{ 7,2,3 };
	{
		Integer_Set SetToDel{ 1,4,6 };
		Set1 = std::move(SetToDel);
	}

	assert(Set1.IntegerSetFindKey(1));
	assert(Set1.IntegerSetFindKey(6));
	assert(Set1.IntegerSetFindKey(4));
	assert(Set1.getRoot() != nullptr);
	assert(Set1.getSize() == 3);

	Integer_Set Set2;
	{
		Integer_Set SetToDel{ 1,4,6 };
		Set2 = std::move(SetToDel);
	}

	assert(Set2.IntegerSetFindKey(1));
	assert(Set2.IntegerSetFindKey(6));
	assert(Set2.IntegerSetFindKey(4));
	assert(Set2.getRoot() != nullptr);
	assert(Set2.getSize() == 3);
	
}
DECLARE_TEST(test_output_operator)
{
	std::cout << std::endl;
	Integer_Set out1;
	Integer_Set out2{ 5 };
	Integer_Set out3{ 5,8,7,3,3 };
	std::cout << out1 << std::endl << out2 << std::endl << out3;
}
