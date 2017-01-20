#pragma once

#include "math/Line2.h"

#include <assert.h>
#include <memory>
#include <vector>

namespace ftec
{
	template <typename T>
	struct BSP2;

	template <typename T>
	struct BSPNode {
		BSP2<T> *m_BSP;
		std::vector<int> m_Lines; // A vector because of shared lines.
		//TODO make these indices in the nodelist for the BSP, for more compact memory stuff
		std::unique_ptr<BSPNode<T>> m_Left = nullptr;
		std::unique_ptr<BSPNode<T>> m_Right = nullptr;

	public:
		BSPNode(BSP2<T> *bsp) : m_BSP(bsp) 
		{
			if (bsp == nullptr)
			{
				assert(false);
			}
		};

		void insert(int index)
		{
			//TODO assertions
			auto &selfLine = m_BSP->m_Lines[m_Lines[0]];
			auto &otherLine = m_BSP->m_Lines[index];

			//Calculate the sides
			int aRes = selfLine.distanceFrom(otherLine.a);
			int bRes = selfLine.distanceFrom(otherLine.b);

			//lambda for insertion
			auto insertSide = [this, index](std::unique_ptr<BSPNode<T>> &side) {

				//If this side does not exist yet
				if (side == nullptr){
					side = std::make_unique<BSPNode<T>>(m_BSP);
					side->m_Lines.push_back(index);
				}

				//Insert it into the child node, and let it handle the rest.
				else {
					side->insert(index);
				}
			};

			//On line, and parallel
			if (aRes == 0 && bRes == 0){
				assert(false);
				//TODO this is the only, very tricky one
				//In essense its pretty easy but it does weird stuff with the space its dividing.
			}
			//To the right
			else if (aRes >= 0 && bRes >= 0){
				insertSide(m_Right);
			}
			//To the left
			else if (aRes <= 0 && bRes <= 0){
				insertSide(m_Left);
			}
			//Its intersecting
			else {
				insertSide(m_Left);
				insertSide(m_Right);
			}
		}
	
		int cellcount()
		{
			int result = 0;

			if (m_Left)
				result += m_Left->cellcount();
			else
				result += 1;
			
			if (m_Right)
				result += m_Right->cellcount();
			else
				result += 1;

			return result;
		}
	};

	template <typename T>
	struct BSP2 {
		std::vector<Line2<T>> m_Lines;
		std::unique_ptr<BSPNode<T>> m_Node;
	public:
		BSP2() = default;
		BSP2(std::vector<Line2<T>> lines) : m_Lines(std::move(lines)) {};

		void build(std::vector<Line2<T>> lines) 
		{
			m_Lines = std::move(lines);
			build();
		}

		void build()
		{
			//Add the first node
			{
				m_Node = std::make_unique<BSPNode<T>>(this);
				m_Node->m_Lines.push_back(0);
			}

			//Add the rest
			for (int i = 1; i < m_Lines.size(); i++){
				m_Node->insert(i);
			}
		}

		int cellcount()
		{
			return m_Node->cellcount();
		}
	};

	typedef BSP2<int> BSP2i;
}