/*
  ==============================================================================

    ThinButton.cpp
    Created: 30 May 2013 8:47:07pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ThinButton.h"

namespace teragon {

ThinButton::ThinButton(PluginParameter *parameter,
                       const char* normalImage, const int normalImageSize,
                       const char* pressedImage, const int pressedImageSize,
                       const ThinButton::Gravity gravity) :
ImageButton(String::empty),
PluginParameterObserver(),
parameter(parameter), gravity(gravity)
{
    parameter->addObserver(this);
    setImages(ImageCache::getFromMemory(pressedImage, pressedImageSize),
              ImageCache::getFromMemory(normalImage, normalImageSize));
    setState(parameter->getValue() ? Button::buttonDown : Button::buttonNormal);
}

ThinButton::~ThinButton() {
    parameter->removeObserver(this);
}

void ThinButton::clicked() {
    parameter->setValue(getToggleState());
}

void ThinButton::onParameterUpdated(const PluginParameter* parameter) {
    setState(parameter->getValue() ? Button::buttonDown : Button::buttonNormal);
}

void ThinButton::paint(Graphics &g) {
    const Image buttonStateImage = getImageForButtonState();
    int buttonY;
    if(gravity == kGravityTop) {
        buttonY = 0;
    }
    else if(gravity == kGravityBottom) {
        buttonY = getHeight() - buttonStateImage.getHeight();
    }
    g.drawImage(buttonStateImage, 0, buttonY, buttonStateImage.getWidth(), buttonStateImage.getHeight(),
                0, 0, buttonStateImage.getWidth(), buttonStateImage.getHeight());
}

void ThinButton::setImages(const Image &buttonDown, const Image &buttonUp) {
    juce::ImageButton::setImages(false, false, true,
                                 buttonUp, 1.0f, Colour(0x0),
                                 Image(), 1.0f, Colour(0x0),
                                 buttonDown, 1.0, Colour(0x0));
    this->buttonDown = buttonDown;
    this->buttonUp = buttonUp;
}
} // namespace teragon
