#include "LinearLayout.h"

#include "math/math.h"

namespace potato {
	LinearLayout::LinearLayout(LayoutDirection dir)
		: m_Direction(dir)
	{
		m_Insets = { 0,0,0,0 };
	}

	void LinearLayout::updateLayout()
	{
		Size layoutSize = localbounds().size;

		//Available size (which we have to scale to)
		float availableSize = m_Direction == HORIZONTAL ? (float)layoutSize.width : (float) layoutSize.height;

		//The total weight of all elements that need weighting
		float totalWeight = 0;
		//Size of all elements that don't use weighting
		float totalSize = 0;

		//Find the total weights we have and all the exact measures we need.
		for (auto child : m_Children) {
			LayoutParams &pChild = child->layoutparams();

			//Horizontal stacking and stuff
			if (m_Direction == HORIZONTAL) {
				//if we should match parent
				if (pChild.m_WidthScaling == LayoutParams::MATCH_PARENT) {
					totalWeight += ftec::max(pChild.m_Weight, 0.0f); //Negative weights will fuck this up
				}
				//Exact 
				else if (pChild.m_WidthScaling == LayoutParams::EXACT) {
					totalSize += pChild.m_Size.width;
				}
				//wrap content
				else if (pChild.m_WidthScaling == LayoutParams::WRAP_CONTENT) {
					totalSize += child->getPreferredSize().x;
				}
			}
			//Vertical stacking and stuff (else case, but more readable
			else if (m_Direction == VERTICAL){
				//if we should match parent
				if (pChild.m_HeightScaling == LayoutParams::MATCH_PARENT) {
					totalWeight += pChild.m_Weight;
				}
				//Exact 
				else if (pChild.m_HeightScaling == LayoutParams::EXACT) {
					totalSize += pChild.m_Size.height;
				}
				//wrap content
				else if (pChild.m_HeightScaling == LayoutParams::WRAP_CONTENT) {
					totalSize += child->getPreferredSize().y;
				}
			}
		}
	
		//How much size / units do we have to spare
		float sizeLeft = availableSize - totalSize;
		
		//Calculate how much size we have per weight
		float sizePerWeight;
		if (sizeLeft > 0.0f)
			sizePerWeight = sizeLeft / totalWeight;
		else
			sizePerWeight = 0;

		//Offset, for positioning
		float offset = 0;

		//Set the actual sizes for all the children
		for (auto child : m_Children) {
			LayoutParams &pChild = child->layoutparams();
			
			Size s = child->getPreferredSize();

			//Horizontal stacking and stuff
			if (m_Direction == HORIZONTAL) {
				//if we should match parent
				if (pChild.m_WidthScaling == LayoutParams::MATCH_PARENT) {
					s.width = (int) (sizePerWeight * pChild.m_Weight);
				}
				//Exact 
				else if (pChild.m_WidthScaling == LayoutParams::EXACT) {
					s = pChild.m_Size;
				}
				//Wrap content is getPreferredSize, so that is already okay

				s.height = ftec::min(layoutSize.height, s.height);

				if (pChild.m_HeightScaling == LayoutParams::MATCH_PARENT)
					s.height = layoutSize.height;

				child->localbounds() = Bounds(
					(int)offset, 0,
					s.width, s.height
				);

				offset += s.width;
			}
			//Vertical stacking and stuff (else case, but more readable)
			else if (m_Direction == VERTICAL) {
				//if we should match parent
				if (pChild.m_HeightScaling == LayoutParams::MATCH_PARENT) {
					s.height = (int) (sizePerWeight * pChild.m_Weight);
				}
				//Exact 
				else if (pChild.m_HeightScaling == LayoutParams::EXACT) {
					s = pChild.m_Size;
				}
				//Wrap content is getPreferredSize, so that is already okay

				s.width = ftec::min(layoutSize.width, s.width);

				if (pChild.m_WidthScaling == LayoutParams::MATCH_PARENT)
					s.width = layoutSize.width;

				child->localbounds() = Bounds(
					0, (int)offset,
					s.width, s.height
				);

				offset += s.height;
			}

			//And ofcourse, alas, the child can update its layout as well
			child->updateLayout();
		}
	}

	void LinearLayout::addPanel(std::shared_ptr<Panel> panel)
	{
		this->m_Children.push_back(panel);
		panel->setUI(m_UI);
		panel->setParent(this);

		requestUpdateLayout();
	}

	Size LinearLayout::getPreferredSize()
	{
		Size s(0,0);
		
		for (auto child : m_Children){
			Size pref = child->getPreferredSize();

			if (m_Direction == HORIZONTAL) {
				s.x += pref.x;
				s.y = ftec::max(s.y, pref.y);
			}

			if (m_Direction == VERTICAL) {
				s.x = ftec::max(s.x, pref.x);
				s.y += pref.y;
			}
		}

		return s;
	}
}
