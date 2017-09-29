#pragma once

#include <memory>
#include <vector>

#include "PotatoUI.h"

#include "Event.h"
#include "LayoutParams.h"

namespace ftec {
	class Graphics2D;
	class Font;
}

namespace potato {

	typedef ftec::Rectanglei Bounds;
	typedef ftec::Vector2i Size;

	struct Insets{
		int top, right, bottom, left;

		Insets() = default;
		Insets(int a, int b, int c, int d) : top(a), right(b), bottom(c), left(d){}

		static Insets defaultInsets() { return Insets(2, 2, 2, 2); }
		static Insets none() { return Insets(0, 0, 0, 0); }
	};

	class Panel;
	class Panel {
	public:
		Bounds m_LocalBounds;
	protected:

		ftec::Color32 m_BackgroundColor = ftec::Color32::white();
		ftec::Color32 m_ForegroundColor = ftec::Color32::black();

		std::shared_ptr<ftec::Font> m_Font;

		bool m_Focusable = false;
		bool m_Opaque = false;
		bool m_SwallowTab = false;

		LayoutParams m_LayoutParams = LayoutParams();
		Insets m_Insets = Insets::defaultInsets();

		//Optional parent
		//shared ptr from this? maybe?
		Panel *m_Parent = nullptr;
		PotatoUI *m_UI;

		std::string m_ID = "";

		//List of children
		std::vector<std::shared_ptr<Panel>> m_Children;

	public:
		Panel();

		void setOpaque(bool op) { m_Opaque = op; }
		bool isOpaque() const { return m_Opaque; }

		void setFocusable(bool f) { m_Focusable = f; }
		bool isFocusable() const { return m_Focusable; }

		Bounds &localbounds() { return m_LocalBounds; }
		const Bounds &localbounds() const { return m_LocalBounds; }

		//TODO some chaching in this
		Bounds getGlobalBounds() const;
		Bounds getGlobalOutline() const;
		Bounds getInnerBounds() const;

		ftec::Color32 &background() { return m_BackgroundColor; }
		const ftec::Color32 &background() const { return m_BackgroundColor; }

		ftec::Color32 &foreground() { return m_ForegroundColor; }
		const ftec::Color32 &foreground() const { return m_ForegroundColor; }

		LayoutParams &layoutparams() { return m_LayoutParams; }
		const LayoutParams &layoutparams() const { return m_LayoutParams; }

		inline const std::string &getID() const { return m_ID; }
		inline void setID(std::string s) { m_ID = std::move(s); }

		//Called each time the panel needs to be drawn
		virtual void draw(ftec::Graphics2D &graphics);
		virtual void drawSelf(ftec::Graphics2D &graphics);

		//Called each update (for animation, for everything)
		virtual void update();

		//Called each frame, before events are processed
		virtual void onPreEvents();
		virtual void onPostEvents();

		//Events that get fired from the panel
		virtual void onClick(Event &evt);

		virtual void onHoverEnter(Event &evt);
		virtual void onHoverLeave(Event &evt);
		virtual void onHover(Event &evt);

		virtual void onDrag(Event &evt);
		virtual void onHoverOrDrag(Event &evt);

		virtual void onMouseReleased(Event &evt);
		virtual void onMousePressed(Event &evt);

		virtual void onKeyTyped(Event &evt);
		virtual void onKeyPressed(Event &evt);
		virtual void onKeyReleased(Event &evt);

		virtual void onFocusGain(Event &evt);
		virtual void onFocusLose(Event &evt);

		void switchFocus();

		bool isFocused() const { return m_UI && m_UI->isFocused(this); }
		bool isPressed() const { return m_UI && m_UI->isPressed(this); }
		bool isPressed(int mb) const { return m_UI && m_UI->isPressed(this, mb); }

		// Ill have to look at these definitions...
		bool isHovering() const;
		bool isHoveringChild() const;
		bool isHoveringSelf() const;

		bool isChildFocused() const;

		virtual Size getPreferredSize() = 0;

		virtual bool inBounds(ftec::Vector2i point) const;

		//Should not be used? Maybe?
		bool inChildBounds(ftec::Vector2i point) const;
		bool inSelfBounds(ftec::Vector2i point) const;

		//Copies the list... Not sure if we want this
		virtual std::vector<std::shared_ptr<Panel>> getChildren() const { return m_Children; }

		//Layout stuff
		void requestUpdateLayout();
		virtual void updateLayout();

		void setParent(Panel *parent);
		Panel *getParent() { return m_Parent; }

		virtual void setUI(PotatoUI *ui);
		PotatoUI *getUI() { return this->m_UI; }

		template <typename T>
		std::shared_ptr<T> findPanelById(const std::string &id) {
			//Can't be itself, that might be a problem.

			for (auto p : getChildren()) {
				if (p->getID() == id)
					return p;
				auto c = p->findPanelById(id);
				if (c)
					return c;
			}

			//Can't return itself ):
			return nullptr;
		}

		std::shared_ptr<Panel> findPanelByPosition(ftec::Vector2i input) const;

		friend class PotatoUI;
	protected:
		void initChild(std::shared_ptr<Panel> child);
	};
}