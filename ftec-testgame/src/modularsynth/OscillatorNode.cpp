#include "OscillatorNode.h"

#include "potato_ui/LinearLayout.h"
#include "potato_ui/Dropdown.h"
#include "potato_ui/UILoader.h"

#include "math/math.h"

namespace modularsynth {

	OscillatorNode::OscillatorNode()
	{
		
	}

	void OscillatorNode::init() 
	{
		using namespace potato;

		auto layout = UILoader::load("layouts/nodes/OscillatorNode.xml");

		// Make the dropdown
		{
			auto dropdown = layout->findPanelById<Dropdown>("wavetype_dropdown");

			if (dropdown) {
				dropdown->getTextOptions().push_back("Sine");
				dropdown->getTextOptions().push_back("Square");
				dropdown->getTextOptions().push_back("Triangle");
				dropdown->getTextOptions().push_back("Sawtooth");
			}

		}

		setTitle("Oscillator");

		setInputs(2);
		setOutputs(1);

		setContent(layout);
	}


}
