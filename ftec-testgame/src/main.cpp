#include "logger/log.h"
#include "engine/Engine.h"
#include "game/Razura.h"

#include "io/XMLDocument.h"

int main(void)
{
	using namespace ftec;
	using namespace xml;

	XMLDocument doc;

	XMLNode body = node("body", {}, {
		text("Dit "),
		node("b", {},
		{
			text("is ")
		}),
		node("i",{},
		{
			text("een "),
			node("br")
		}),
		text("test!"),
		node("canvas", {
			attribute("width", "400"),
			attribute("height", "300")
		}, {
			text("Value!")
		})
	});

	doc.m_Root.addChild(body);

	doc.m_Root.setTag("HTML");

	LOG(doc);
	WAIT();
	if (true)
		return 0;

	ftec::Engine::create<ftec::Razura>();
	return 0;
}

