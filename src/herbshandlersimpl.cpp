#include "herbshandlersimpl.h"

HerbsHandlerSimpl::HerbsHandlerSimpl(HWiface * hardware,
                                     IPolivSettingsInt * settings): hdware(hardware), stngs(settings)
{

}

void HerbsHandlerSimpl::handleHerbs()
{
    if(mode == PolivMode::Auto)
        if(hdware->humidity() < stngs->getMinHumidity())
            while(hdware->humidity() < stngs->getMaxHumidity()) {
                hdware->turnPumpOn();
                delay_s(stngs->getMinPumpOnTime());
                hdware->turnPumpOff();
                delay_s(stngs->getWaitTimeAfterpump());
            }
}


void HerbsHandlerSimpl::setMode(PolivMode mode)
{
    this->mode = mode;
    if(mode == PolivMode::ManualOn)
        hdware->turnPumpOn();
    else if(mode == PolivMode::ManualOff)
        hdware->turnPumpOff();
}

PolivMode HerbsHandlerSimpl::getPolivMode()
{
    return this->mode;
}

PolivStage HerbsHandlerSimpl::getStatus()
{
    return this->stage;
}
