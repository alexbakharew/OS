#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include "figure.h"
#include "hexagon.h"
#include "octagon.h"
#include "triangle.h"
#include "item.h"
#include "llist.h"
TLList::TLList()
{
	std::cout << "Creation of List" << std::endl;
	root = nullptr;
	std::cout << "List created successfully" << std::endl;
}
TLList::~TLList()
{
	std::cout << "Deletion of list" << std::endl;
	while(!remove(0)){}
	std::cout << "list was deleted!" << std::endl;
}
PTItem TLList::get_root()
{
	return root;
}
PTItem TLList::move_to(size_t n) 
{
	PTItem curr = get_root();
	if (curr == nullptr) return curr;
	int i = 0;
	while (i != n)
	{
		if (curr.get()->get_next() != nullptr)
		{
			curr = (curr.get())->get_next();
			i++;
		}
		else
		{
			return curr;
		}
	}
	return curr;
}
void TLList::insert(const PFig& fig, size_t n)
{
	PTItem curr = move_to(n);
	PTItem item = PTItem(new TItem(fig));
	if (curr == nullptr)
	{
		root = item;
		return;
	}
	PTItem next = (curr.get())->get_next(); 
	(item.get())->set_next(next);
	(item.get())->set_prev(curr);
	(curr.get())->set_next(item);
	if (next == nullptr) return;
	else
	{
		next.get()->set_prev(item);
		return;
	}
}
void TLList::print_i(size_t n)
{
	PTItem curr = move_to(n);
	if (curr == nullptr)
	{
		std::cout << "List is empty!" << std::endl;
		return;
	}
	std::cout << curr << std::endl;
	return;
}
void TLList::print_all()
{
	PTItem curr = get_root();
	if (curr == nullptr)
	{
		std::cout << "List is empty!" << std::endl;
		return;
	}
	while (curr != nullptr)
	{
		std::cout << curr << std::endl;
		curr = curr.get()->get_next();
	}
	return;
}
bool TLList::remove(size_t n)
{
	PTItem curr = move_to(n);
	if (curr == nullptr)
	{
		std::cout << "List is empty!" << std::endl;
		return false;
	}
	PTItem next = curr.get()->get_next();
	PTItem prev = curr.get()->get_prev();
	if (prev == nullptr && next == nullptr)//only 1 elem in list!
	{
		root = nullptr;
		return true;
	}
	else if (prev == nullptr && next != nullptr)// we want to delete root
	{
		root = next;
		next.get()->set_prev(prev);
		return true;
	}
	else if (prev != nullptr && next == nullptr)
	{
		prev.get()->set_next(next);
		return true;
	}
	else
	{
		prev.get()->set_next(next);
		next.get()->set_prev(prev);
		return true;
	}
}