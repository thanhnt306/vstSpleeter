/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpleetervstAudioProcessorEditor::SpleetervstAudioProcessorEditor(
    SpleetervstAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p) {
    volume_sliders.push_back(std::make_pair("Vocals", &vocals_volume_slider));
    volume_sliders.push_back(std::make_pair("Drums", &drums_volume_slider));
    volume_sliders.push_back(std::make_pair("Bass", &bass_volume_slider));
    volume_sliders.push_back(std::make_pair("Piano", &piano_volume_slider));
    volume_sliders.push_back(std::make_pair("Other", &other_volume_slider));

    setSize(400, 300);
    setResizable(true, false);
    setResizeLimits(200, 150, 800, 600);

    for (auto& slider : volume_sliders) {
        addAndMakeVisible(slider.second);
        slider.second->setRange(Range<double>(0.0, 1.0), 0.01);
        setSliderEnable(slider.second, false);
        slider.second->setSliderStyle(Slider::SliderStyle::LinearVertical);
    }

    vocals_volume_slider.onValueChange = [this]() {
        processor.setVocalsVolume(vocals_volume_slider.getValue());
    };
    bass_volume_slider.onValueChange = [this]() {
        processor.setBassVolume(bass_volume_slider.getValue());
    };
    drums_volume_slider.onValueChange = [this]() {
        processor.setDrumsVolume(drums_volume_slider.getValue());
    };
    piano_volume_slider.onValueChange = [this]() {
        processor.setPianoVolume(piano_volume_slider.getValue());
    };
    other_volume_slider.onValueChange = [this]() {
        processor.setOtherVolume(other_volume_slider.getValue());
    };

    // init text button
    twoStemsButton.setButtonText("Two Stems");
    fourStemsButton.setButtonText("Four Stems");
    fiveStemsButton.setButtonText("Five Stems");
    addAndMakeVisible(twoStemsButton);
    addAndMakeVisible(fourStemsButton);
    addAndMakeVisible(fiveStemsButton);

    twoStemsButton.onClick = [this]() {
        for each (std::pair<std::string, juce::Slider*> var in volume_sliders)
        {
            if (var.first == "Vocals" || var.first == "Other")
                setSliderEnable(var.second, true);
            else {
                setSliderEnable(var.second, false);
            }
        }
    };

    fourStemsButton.onClick = [this]() {
        for each (std::pair<std::string, juce::Slider*> var in volume_sliders)
        {
            if (var.first != "Other")
                setSliderEnable(var.second, true);
            else {
                setSliderEnable(var.second, false);
            }
        }
    };

    fiveStemsButton.onClick = [this]() {
        for each (std::pair<std::string, juce::Slider*> var in volume_sliders)
        {
            setSliderEnable(var.second, true);
        }
    };

    twoStemsButton.onClick();

    //

    UpdateVolumes();
}

SpleetervstAudioProcessorEditor::~SpleetervstAudioProcessorEditor() {}

//==============================================================================
void SpleetervstAudioProcessorEditor::paint(Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with a
    // solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(15.0f);

    auto bounds = getLocalBounds();

    const int volume_slider_width = 10;
    const int volume_label_width = 40;
    const int volume_label_height = 20;
    const int padding = 10;

    int volume_slider_height = getHeight();
    volume_slider_height -= padding; // padding between label and bottom
    volume_slider_height -= volume_label_height; // label height
    volume_slider_height -= padding; // padding between label and slider
    volume_slider_height -= padding; // padding between slider and the top

    int volume_label_y = getHeight();
    volume_label_y -= padding;             // padding between label and bottom
    volume_label_y -= volume_label_height; // label height

    int volume_slider_y = volume_label_y;
    volume_slider_y -= padding;              // padding between label and slider
    volume_slider_y -= volume_slider_height; // slider height

    int block_width = bounds.getWidth() / (volume_sliders.size() + 1);

    int slider_index = 1;
    for (auto volume_slider : volume_sliders) {
        int block_x = block_width * slider_index;
        int block_center_x = block_x + block_width / 2;
        int slider_x = block_center_x - (volume_slider_width / 2);
        int label_x = block_center_x - (volume_label_width / 2);

        // Label
        g.drawFittedText(volume_slider.first, label_x, volume_label_y,
            volume_label_width, volume_label_height,
            Justification::centred, 1);
        // slider
        volume_slider.second->setBounds(slider_x, volume_slider_y,
            volume_slider_width, volume_slider_height);

        // keep the index
        slider_index += 1;
    }


    // TextButton
    twoStemsButton.setBounds(bounds.getTopLeft().x + padding, bounds.getTopLeft().y + padding, block_width, bounds.getHeight() / 4.0);
    fourStemsButton.setBounds(bounds.getTopLeft().x + padding, bounds.getTopLeft().y + padding + bounds.getHeight() / 4.0 + padding, block_width, bounds.getHeight() / 4.0);
    fiveStemsButton.setBounds(bounds.getTopLeft().x + padding, bounds.getTopLeft().y + padding + 2 * (bounds.getHeight() / 4.0 + padding), block_width, bounds.getHeight() / 4.0);
    //
}

void SpleetervstAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    UpdateVolumes();
}

void SpleetervstAudioProcessorEditor::UpdateVolumes() {
    vocals_volume_slider.setValue(processor.getVocalsVolume());
    bass_volume_slider.setValue(processor.getBassVolume());
    piano_volume_slider.setValue(processor.getPianoVolume());
    drums_volume_slider.setValue(processor.getDrumsVolume());
    other_volume_slider.setValue(processor.getOtherVolume());
}

void SpleetervstAudioProcessorEditor::setSliderEnable(Slider* slider, bool isEnable)
{
    slider->setEnabled(isEnable);
    if (isEnable) {
        slider->setColour(Slider::ColourIds::trackColourId, Colours::aqua);
        slider->setColour(Slider::ColourIds::thumbColourId, Colours::aqua);
    }
    else {
        slider->setColour(Slider::ColourIds::trackColourId, Colour::fromRGBA(100, 100, 100, 200));
        slider->setColour(Slider::ColourIds::thumbColourId, Colour::fromRGBA(100, 100, 100, 200));
    }
}
