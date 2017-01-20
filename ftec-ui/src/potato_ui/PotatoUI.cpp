#include "PotatoUI.h"
#include "Panel.h"
#include "logger/log.h"

#include "graphics/Window.h"
#include "graphics/Camera.h"

#include "engine/Engine.h"

namespace potato {
	//https://www.materialpalette.com/blue-grey/grey

	ftec::Color32 PotatoColor::primaryText =	ftec::Color32(0x21, 0x21, 0x21, 0xFF);
	ftec::Color32 PotatoColor::secondaryText =	ftec::Color32(0x75, 0x75, 0x75, 0xFF);

	ftec::Color32 PotatoColor::darkPrimary =	ftec::Color32(0x45, 0x5A, 0x64, 0xFF);
	ftec::Color32 PotatoColor::primary =		ftec::Color32(0x60, 0x7D, 0x8B, 0xFF);
	ftec::Color32 PotatoColor::lightPrimary =	ftec::Color32(0xCF, 0xD8, 0xDC, 0xFF);

	ftec::Color32 PotatoColor::divider =		ftec::Color32(0xBD, 0xBD, 0xBD, 0xFF);
	ftec::Color32 PotatoColor::accent =			ftec::Color32(0x9E, 0x9E, 0x9E, 0xFF);
	ftec::Color32 PotatoColor::iconsText =		ftec::Color32(0xFF, 0xFF, 0xFF, 0xFF);


	std::string PotatoClipboard::data = "";
	//TODO make this use the windows clipboard
	const std::string &PotatoClipboard::getData() {
		return data;
	}

	void PotatoClipboard::setData(const std::string &input) 
	{
		data = input;
	}

	PotatoUI::PotatoUI()
	{
		m_Graphics.m_Camera = ftec::Camera::orthagonal(ftec::Engine::getWindow().getHeight(), ftec::Engine::getWindow().getWidth() / ftec::Engine::getWindow().getHeight(), -100, 100, true);
		m_Graphics.m_Camera.m_Position = ftec::Vector3f(ftec::Engine::getWindow().getWidth() / 2.0f, ftec::Engine::getWindow().getHeight() / 2.0f);
	}

	PotatoUI::~PotatoUI()
	{
	}

	void PotatoUI::update()	
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		if (m_Root) {
			Event event(shared_from_this());

			if (ftec::Engine::getWindow().isResized()) {
				m_Root->localbounds() = ftec::Rectanglei(0, 0, (int)ftec::Engine::getWindow().getWidth(), (int)ftec::Engine::getWindow().getHeight());
				m_Root->updateLayout();
			}

			if(m_ContextMenu)
				m_ContextMenu->process(event);

			if(!event.isConsumed())
				m_Root->process(event);

			if (m_ContextMenu)
				m_ContextMenu->update();

			m_Root->update();
		}
	}

	void PotatoUI::render()
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		//Always set the right size and stuff
		m_Graphics.m_Camera = ftec::Camera::orthagonal(ftec::Engine::getWindow().getHeight(), ftec::Engine::getWindow().getWidth() / ftec::Engine::getWindow().getHeight(), -100, 100, true);
		m_Graphics.m_Camera.m_Position = ftec::Vector3f(ftec::Engine::getWindow().getWidth() / 2.0f, ftec::Engine::getWindow().getHeight() / 2.0f);

		m_Graphics.drawClear();
		m_Graphics.begin();

		if (m_Root) {
			m_Root->draw(m_Graphics);
		}
		if (m_ContextMenu) {
			m_ContextMenu->draw(m_Graphics);
		}

		m_Graphics.end();
	}

	void PotatoUI::setRoot(std::shared_ptr<Panel> root)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		m_Root = root;
		if (m_Root) {
			m_Root->setUI(shared_from_this());
			//Give this the full panel, this happens always, at all times
			m_Root->localbounds() = ftec::Rectanglei(0, 0, (int)ftec::Engine::getWindow().getWidth(), (int)ftec::Engine::getWindow().getHeight());
			m_Root->updateLayout();
		}
	}

	void PotatoUI::setContextMenu(std::shared_ptr<Panel> contextMenu)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		m_ContextMenu = contextMenu;
		if (m_ContextMenu) {
			m_ContextMenu->setUI(shared_from_this());
		}
	}

}
