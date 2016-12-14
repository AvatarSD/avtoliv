#include "herbshandlersimpl.h"

HerbsHandlerSimpl::HerbsHandlerSimpl(HWiface * hardware,
                                     IPolivSettingsInt * settings): hdware(hardware), stngs(settings)
{
    this->stage = PolivStage::WaitForMinHumidity;

    PolivMode mode = stngs->getMode();
    if(mode == PolivMode::ManualOn)
        hdware->turnPumpOn();
    else
        hdware->turnPumpOff();
}

void HerbsHandlerSimpl::handleHerbs()
{
    if(stngs->getMode() == PolivMode::Auto)
        if(hdware->humidity() < stngs->getMinHumidity())
            while(hdware->humidity() < stngs->getMaxHumidity()) {
                hdware->turnPumpOn();
                this->stage = PolivStage::PumpOn;
                delay_s(stngs->getMinPumpOnTime());
                hdware->turnPumpOff();
                this->stage = PolivStage::AfterPumpWait;
                delay_s(stngs->getWaitTimeAfterpump());
            }
    this->stage = PolivStage::WaitForMinHumidity;
}


void HerbsHandlerSimpl::setMode(PolivMode mode)
{
    stngs->setMode(mode);
    if(mode == PolivMode::ManualOn)
        hdware->turnPumpOn();
    else
        hdware->turnPumpOff();
}

PolivMode HerbsHandlerSimpl::getPolivMode()
{
    return stngs->getMode();
}

PolivStage HerbsHandlerSimpl::getStatus()
{
    return this->stage;
}
