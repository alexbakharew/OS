#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>
#include "figure.h"
#include "hexagon.h"
#include "octagon.h"
#include "triangle.h"
#include "item.h"
class TLList
{
public:
	TLList();
	~TLList();
	PTItem get_root();
	PTItem move_to(size_t);
	void insert(const PFig&, size_t);
	void print_i(size_t);
	bool remove(size_t);
	void print_all();
private:
	PTItem root;
};